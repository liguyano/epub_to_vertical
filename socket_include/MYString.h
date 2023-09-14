//
// Created by kurum on 西暦2023年6月20日.
//

#ifndef WBUILDER_STRING_H
#define WBUILDER_STRING_H

#include <iostream>
#include <vector>

namespace String {


    std::vector<std::string> split(std::string input, std::string delimiters) {
        std::vector<std::string> result;
        size_t pos = 0;
        size_t prev = 0;

        while ((pos = input.find_first_of(delimiters, prev)) != std::string::npos) {
            if (pos > prev) {
                result.push_back(input.substr(prev, pos - prev));
            }
            prev = pos + 1;
        }

        if (prev < input.length()) {
            result.push_back(input.substr(prev));
        }
        return result;
    }

    std::string getExtensionAfterLastDot(const std::string &input, char what = '.') {

        auto lastDotPos = input.rfind(what);
        if (lastDotPos != std::string::npos) {

            return input.substr(lastDotPos + 1);
        } else {

            return "";
        }
    }

    std::string getExtensionBeforLastDot(const std::string &input, char what = '.') {

        size_t lastDotPos = input.rfind(what);

        if (lastDotPos != std::string::npos) {

            return input.substr(0, lastDotPos);
        } else {

            return "";
        }
    }
}
#endif //WBUILDER_STRING_H
