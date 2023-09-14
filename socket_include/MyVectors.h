//
// Created by kurum on 2023/9/14.
//

#ifndef EPUBTORIGHT_MYVECTORS_H
#define EPUBTORIGHT_MYVECTORS_H
#include <iostream>
template <typename T>
bool containsElement(const std::vector<T>& vec, const T& target) {
    auto it = std::find(vec.begin(), vec.end(), target);
    return it != vec.end();
}
template <typename T>
std::vector<T> removeDuplicates(const std::vector<T>& inputVec) {
    std::vector<T> resultVec = inputVec;
    std::sort(resultVec.begin(), resultVec.end());
    auto it = std::unique(resultVec.begin(), resultVec.end());
    resultVec.erase(it, resultVec.end());
    return resultVec;
}
#endif //EPUBTORIGHT_MYVECTORS_H
