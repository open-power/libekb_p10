#!/usr/bin/env python

import sys
import xml.etree.ElementTree as ET

ignore_tags = ['description', 'platInit', 'writeable', 'overrideOnly',
               'persistRuntime', 'mssUnit', 'mssUnits', 'mssAccessorName',
               'odmVisable', 'odmChangeable', 'mssBlobStart', 'mssBlobLength',
               'privileged', 'platActionWrite', 'mrwHide', 'group' ]

data_types = ['uint8', 'uint16', 'uint32', 'uint64',
              'int8', 'int16', 'int32', 'int64']

target_map = {}

class AttributeError(Exception):
    def __init__(self, msg):
        self.__msg = msg

    def __str__(self):
        return self.__msg

    def __repr__(self):
        return str(self)


class Attribute:
    def __init__(self):
        self.__name = ''
        self.__array_dim = []
        self.__target = []
        self.__datatype = None
        self.__default_value = []
        self.__enum = {}
        self.__init_zero = False
        self.__ec_feature = False
        self.__size = 1
        self.__value = None

    def __str__(self):
        value = '%s: %s %s' % (self.__name, self.format(), self.__target)
        return value

    def __repr__(self):
        return str(self)

    def format(self):
        dim = len(self.__array_dim)
        if dim == 0:
            dim_str = '0'
        else:
            array_str = ' '.join([str(i) for i in self.__array_dim])
            dim_str = '%d %s' % (dim, array_str)
        enum_len = len(self.__enum)
        enum_str = ''
        for key in self.__enum:
            enum_str = enum_str + ' %s %s' % (key, self.__enum[key])
        value = self.value()
        if value is None:
            defined = 0
            value_str = ''
        else:
            defined = 1
            value_str = ' '.join(value)
        return '%s %s %d%s %d %s' % (self.__datatype, dim_str, enum_len, enum_str, defined, value_str)

    def parse(self, name, info):
        tmp = info.split()
        if len(tmp) < 3:
            raise AttributeError('Invalid record "%s"' % info)
        self.__name = name
        self.set_datatype(tmp[0])
        dim = int(tmp[1])
        for i in range(dim):
            n = int(tmp[2+i])
            self.__array_dim.append(n)
            self.__size = self.__size * n
        enum_len = int(tmp[2+dim])
        for i in range(enum_len):
            key = tmp[3+dim + i*2]
            value = tmp[3+dim + i*2 + 1]
            self.__enum[key] = value
        idx = 3+dim + 2*enum_len
        defined = int(tmp[idx])
        if defined == 1:
            if len(tmp) - (idx+1) > self.__size:
                print('  %s: instance attribute' % self.__name)
                self.__value = tmp[idx+1:]
            else:
                self.__value = tmp[idx+1:idx+1+self.__size]

    def parse_xml(self, xmlnode):
        if not isinstance(xmlnode, ET.Element):
            raise AttributeError("Wrong type for xml node")

        unknown = []
        for child in xmlnode:
            if child.tag == 'id':
                self.__name = child.text
            elif child.tag == 'targetType':
                self.__target = child.text.replace(',', ' ').split()
            elif child.tag == 'valueType':
                self.set_datatype(child.text)
            elif child.tag == 'array':
                tmp = child.text.replace(',', ' ').split()
                for v in tmp:
                    self.__array_dim.append(int(v))
                    self.__size = self.__size * int(v)
            elif child.tag == 'initToZero':
                self.__init_zero = True
            elif child.tag == 'default':
                self.__default_value = child.text.replace(',', ' ').split()
            elif child.tag == 'description':
                continue
            elif child.tag == 'enum':
                try:
                    tmp = child.text.split(',')
                    for v in tmp:
                        kv = v.split('=')
                        if len(kv) == 2:
                            self.__enum[kv[0].strip()] = kv[1].strip()
                except:
                    raise AttributeError('%s: Failed to parse enum %s' % (self.__name, child.text))
            elif child.tag == 'chipEcFeature':
                #self.__ec_feature = True
                self.set_datatype('uint8')
                self.__init_zero = True
            elif child.tag in ignore_tags:
                continue
            else:
                unknown.append(child.tag)

        if unknown:
            raise AttributeError('%s: Unknown tags %s' % (self.__name, unknown))

    def valid(self):
        if not self.__target or not self.__datatype:
            return False
        return True

    def name(self):
        return self.__name

    def target(self):
        tlist = []
        for t in set(self.__target):
            if t in target_map:
                tlist.append(target_map[t])
            else:
                tlist.append(t)
        return tlist

    def set_value(self, value):
        if self.__default_value:
            print('  %s: overriding default value' % self.__name)
        else:
            if len(value) != self.__size:
                if self.__target[0] == 'TARGET_TYPE_PERV':
                    print('  %s: multiple instance initialization' % self.__name)
                else:
                    raise AttributeError('%s: value size (%d) mismatch, expected %d' % (self.__name, len(value), self.__size))

            self.__init_zero = False
            self.__default_value = value

    def value(self):
        if self.__init_zero:
            val = [str(0) for i in range(self.__size)]
        elif self.__default_value:
            # Special case for PERV instance attributes
            if len(self.__default_value) > self.__size:
                val = self.__default_value
            else:
                val = [str(0) for i in range(self.__size)]
                n = len(self.__default_value)
                val[0:n] = self.__default_value
        else:
            val = None
        return val

    def set_datatype(self, datatype):
        if datatype in data_types:
            self.__datatype = datatype
        else:
            raise AttributeError('%s: Unknown data type %s' % (self.__name, datatype))

    def set_target(self, target):
        self.__target.append(target)


class AttributeCollection:
    def __init__(self):
        self.__attribute = {}
        self.__target = {}

    def __str__(self):
        msg = 'Total attributes = %d\n' % self.total()
        for a in self.__attribute:
            msg = msg + '%s\n' % str(self.__attribute[a])
        return msg

    def add_attribute(self, attr, force):
        if not isinstance(attr, Attribute):
            raise AttributeError('Instance of class Attribute required')
        if force or attr.valid():
            name = attr.name()
            if name in self.__attribute:
                print('Duplicate attribute "%s"' % name)
            else:
                self.__attribute[name] = attr
                for t in attr.target():
                    self.add_target(t, [name])
        else:
            print('Skipping attribute "%s"' % attr.name())

    def get_attribute(self, name):
        return self.__attribute[name]

    def add_target(self, target, alist):
        if target not in self.__target:
            self.__target[target] = []
        self.__target[target].extend(alist)

    def parse_xml(self, filename):
        tree = ET.parse(filename)
        root = tree.getroot()

        for child in root:
            if child.tag == 'attribute':
                attr = Attribute()
                attr.parse_xml(child)
                self.add_attribute(attr, False)
            elif child.tag == 'entry':
                name = ''
                value = []
                ignore = False

                for subchild in child:
                    if subchild.tag == 'name':
                        name = subchild.text
                    elif subchild.tag == 'value':
                        value.append(subchild.text)
                    elif subchild.tag == 'virtual':
                        ignore = True
                    else:
                        raise AttributeError('%s: Invalid tag %s' % (filename, subchild.tag))

                if not ignore and value:
                    try:
                        attr = self.get_attribute(name)
                    except:
                        print('Attribute %s not defined' % name)
                        continue
                    attr.set_value(value)

            else:
                raise AttributeError('%s: Invalid tag %s' % (filename, child.tag))

    def total(self):
        return len(self.__attribute)

    def attributes(self, target='all'):
        if target == 'all':
            return sorted(self.__attribute.keys())
        else:
            return self.__target[target]

    def targets(self):
        return self.__target.keys()

    def stats(self):
        print('Total attributes = %d' % self.total())
        for t in sorted(self.__target):
            print(' %4d  %s' % (len(self.__target[t]), t))

    def list_attributes(self, target):
        if target:
            if target in self.__target:
                tlist = [target]
            else:
                raise AttributeError('Target type %s does not exist\n' % target)
        else:
            tlist = sorted(self.__target)

        for t in tlist:
            print(t)
            for a in self.__target[t]:
                print('  %s' % a)


class AttributeDatabase:
    def __init__(self, filename):
        self.filename = filename
        self.fd = None

    def read_record(self, match_key=None):
        line = self.fd.readline()
        val = line.split(' ', 1)
        if match_key is not None:
            if val[0] != match_key:
                raise AttributeError('Expected %s, got %s\n' % (match_key, val[0]))
        return (val[0].strip(), val[1].strip())

    def write_all(self, all_attributes):
        self.fd.write('all %s\n' % (' '.join(all_attributes)))

    def read_all(self):
        key, value = self.read_record('all')
        return value.split()

    def write_attr(self, attr):
        self.fd.write('%s %s\n' % (attr.name(), attr.format()))

    def read_attr(self, name):
        key, value = self.read_record()
        attr = Attribute()
        attr.parse(key, value)
        return attr

    def write_targets(self, tlist):
        self.fd.write('targets %s\n' % (' '.join(tlist)))

    def read_targets(self):
        key, value = self.read_record('targets')
        return value.split()

    def write_target_rec(self, target, idlist):
        idlist_str = [str(i) for i in idlist]
        self.fd.write('%s %s\n' % (target, ' '.join(idlist_str)))

    def read_target_rec(self, target):
        key, value = self.read_record(target)
        idlist_str = value.split()
        return [int(i) for i in idlist_str]

    def read(self):
        self.fd = open(self.filename, 'r')
        ac = AttributeCollection()
        alist = self.read_all()
        for a in alist:
            attr = self.read_attr(a)
            ac.add_attribute(attr, True)
        tlist = self.read_targets()
        for t in tlist:
            idlist = self.read_target_rec(t)
            talist = [alist[i] for i in idlist]
            ac.add_target(t, talist)
        return ac

    def write(self, ac):
        self.fd = open(self.filename, 'w')
        alist = ac.attributes('all')
        tlist = ac.targets()
        self.write_all(alist)
        for a in alist:
            self.write_attr(ac.get_attribute(a))
        self.write_targets(tlist)
        for t in tlist:
            talist = ac.attributes(t)
            idlist = [alist.index(i) for i in talist]
            idlist.sort()
            self.write_target_rec(t, idlist)


def usage():
    print('Usage: attribute.py parse <db> <attrib-xml> [<attrib-xml>...]')
    sys.exit(1)


def do_list(dbfile, target):
    db = AttributeDatabase(dbfile)
    ac = db.read()
    ac.list_attributes(target)


def do_parse(dbfile, files):
    ac = AttributeCollection()
    for f in files:
        print('Processing %s' % f)
        ac.parse_xml(f)
    ac.stats()
    db = AttributeDatabase(dbfile)
    db.write(ac)


def do_read(dbfile):
    db = AttributeDatabase(dbfile)
    ac = db.read()
    ac.stats()


if __name__ == '__main__':

    if len(sys.argv) < 3:
        usage()

    if sys.argv[1] == 'list':
        if len(sys.argv) == 4:
            target = sys.argv[3]
        else:
            target = None
        do_list(sys.argv[2], target)
    elif sys.argv[1] == 'parse':
        do_parse(sys.argv[2], sys.argv[3:])
    elif sys.argv[1] == 'read':
        do_read(sys.argv[2])
    else:
        usage()
