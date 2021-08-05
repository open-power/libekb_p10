// IBM_PROLOG_BEGIN_TAG
/*
 * Copyright 2017 IBM International Business Machines Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// IBM_PROLOG_END_TAG
#pragma once

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <utility>
#include <vector>
namespace fapi2
{

using PELData = std::vector<std::pair<std::string, std::string>>;

/** @class Hardware procedure error FFDC PEL data
 *
 * @brief Capture failure data from HWP for PEL creation

 * This class captures the failure data returned from the
 * hardware procedure to key, value format so that
 * it can be used in the creation of PEL.
 */
class HwpPelData
{
  public:
    HwpPelData() = default;
    virtual ~HwpPelData() = default;
    HwpPelData(const HwpPelData&) = default;
    HwpPelData& operator=(const HwpPelData&) = default;
    HwpPelData(HwpPelData&&) = default;
    HwpPelData& operator=(HwpPelData&&) = default;

    const PELData& getData() const
    {
        return data;
    }

    void append(const std::string& key, const uint8_t* buffer, uint32_t len)
    {
        std::stringstream str;
        str << std::hex << std::setfill('0');
        const uint8_t* buf = buffer;
        while (len > 0)
        {
            if (len >= 4)
            {
                str << std::setw(8);
                const uint32_t* value = reinterpret_cast<const uint32_t*>(buf);
                str << (*value);
                buf += 4;
                len -= 4;
            }
            else if (len >= 2)
            {
                str << std::setw(4);
                const uint16_t* value = reinterpret_cast<const uint16_t*>(buf);
                str << (*value);
                buf += 2;
                len -= 2;
            }
            else if (len >= 1)
            {
                str << std::setw(2);
                const uint8_t* value = reinterpret_cast<const uint8_t*>(buf);
                str << (static_cast<uint16_t>(*value));
                buf += 1;
                len -= 1;
            }
            str << " ";
        }
        std::string retstr = str.str();
        retstr.erase(std::find_if(retstr.rbegin(), retstr.rend(),
                                  [](int ch) { return !std::isspace(ch); })
                         .base(),
                     retstr.end());
        data.push_back(std::make_pair(key, retstr));
    }

    template <typename T>
    void append(const std::string& key, T value)
    {
        std::stringstream str;
        str << value;
        data.push_back(std::make_pair(key, str.str()));
    }

    void append(const std::string& key, uint8_t value)
    {
        std::stringstream str;
        str << static_cast<uint16_t>(value);
        data.push_back(std::make_pair(key, str.str()));
    }

  private:
    PELData data;
};
} // namespace fapi2
