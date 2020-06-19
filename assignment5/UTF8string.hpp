//
// Created by sdmms on 2020/5/3.
//

#ifndef LAB101_UTF8STRING_HPP
#define LAB101_UTF8STRING_HPP
#include <cstring>
#include <iostream>
using namespace std;
class UTF8string {
    friend ostream& operator<<(ostream&,const UTF8string&);
    friend UTF8string operator*(int, const UTF8string&);
    friend UTF8string operator!(const UTF8string&);

private:
    string s;
public:
    UTF8string(string);
    UTF8string(const char*);

    int length();
    int bytes();
    int find(string substr);
    void replace(UTF8string to_remove, UTF8string replacement);
    UTF8string operator+(const UTF8string&);
    UTF8string operator+=(const UTF8string&);
    UTF8string operator*(int);
};


#endif //LAB101_UTF8STRING_HPP
