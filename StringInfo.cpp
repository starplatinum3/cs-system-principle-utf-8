//
// Created by Lenovo on 2020/10/29.
//

#include "StringInfo.h"

#include <utility>

StringInfo::StringInfo(int startIndex, int len, std::string str) : startIndex(startIndex), len(len), str(std::move(str)) {}

int StringInfo::getStartIndex() const {
    return startIndex;
}

void StringInfo::setStartIndex(int startIndex) {
    StringInfo::startIndex = startIndex;
}

int StringInfo::getLen() const {
    return len;
}

void StringInfo::setLen(int len) {
    StringInfo::len = len;
}

const std::string &StringInfo::getStr() const {
    return str;
}

void StringInfo::setStr(const std::string &str) {
    StringInfo::str = str;
}

std::ostream &operator<<(std::ostream &os, const StringInfo &info) {
    os << "startIndex: " << info.startIndex << " len: " << info.len << " str: " << info.str;
    return os;
}
