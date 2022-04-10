//
// Created by Lenovo on 2020/10/29.
//

#ifndef CS_SYSTEM_PRINCIPLE_STRINGINFO_H
#define CS_SYSTEM_PRINCIPLE_STRINGINFO_H

#include <string>
#include <ostream>

class StringInfo {
private:
    int startIndex;
    int len;
    std::string str;
public:
    StringInfo(int startIndex, int len, std::string str);

    int getStartIndex() const;

    void setStartIndex(int startIndex);

    int getLen() const;

    void setLen(int len);

    const std::string &getStr() const;

    void setStr(const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const StringInfo &info);
};


#endif //CS_SYSTEM_PRINCIPLE_STRINGINFO_H
