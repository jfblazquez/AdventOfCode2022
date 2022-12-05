//from https://github.com/Diego-Urbina/Advent-of-Code-2022/blob/main/src/utils/string.h  commit c724876 
#pragma once

#include <string>
#include <vector>

namespace utils
{
    namespace string
    {
        inline std::vector<std::string> split(const std::string& string, char delimiter)
        {
            std::vector<std::string> list;

            size_t last = 0;
            size_t next = 0;
            while ((next = string.find(delimiter, last)) != std::string::npos) {
                list.push_back(string.substr(last, next - last));
                last = next + 1;
            }
            if (last < string.size()) {
                list.push_back(string.substr(last));
            }

            return list;
        }
    }
}