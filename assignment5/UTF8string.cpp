//
// Created by sdmms on 2020/5/3.
//

#include "UTF8string.hpp"
#include "utf8.h"

using namespace std;
UTF8string::UTF8string(string s) {
    this->s = move(s);
}

UTF8string::UTF8string(const char* s) {
    this->s = s;
}

int UTF8string::length() {
    auto* p = (unsigned char*)s.c_str();
    return utf8_charlen(p);
}

int UTF8string::bytes() {
    return s.length();
}

int UTF8string::find(string substr) {
    auto* p = (unsigned char*)s.c_str();
    auto* q = (unsigned char*)substr.c_str();
    auto* pos = utf8_search(p,q);
    return pos == nullptr?
                -1 : utf8_charlen(p) - utf8_charlen(pos);
}

void UTF8string::replace(UTF8string to_remove, UTF8string replacement) {
    int pos;
    while((pos = s.find(to_remove.s)) != string::npos)
        this->s.replace(pos, to_remove.bytes(),replacement.s);
}

ostream& operator<<(ostream& os, const UTF8string& a){
    os << a.s;
    return os;
}

UTF8string UTF8string::operator+(const UTF8string &a) {
    return UTF8string(s + a.s);
}

UTF8string UTF8string::operator+=(const UTF8string &a) {
    s.append(a.s);
    return *this;
}

UTF8string UTF8string::operator*(int t) {
    int i;
    string str;
    for(i = 0; i < t; i++)
        str.append(s);
    return UTF8string(str);
}

UTF8string operator*(const int t, const UTF8string& a){
    int i;
    string s;
    for(i = 0; i < t; i++)
        s.append(a.s);
    return UTF8string(s);
}

UTF8string operator!(const UTF8string& a){
    string str1 = a.s, str2;
    auto* p = (unsigned char*) a.s.c_str();
    int pos = 0,len;

    while(*p != '\0'){
        len = isutf8(p);
        if(len == 0){
            str2 = str1.substr(pos,1) + str2;
            ++pos;
            ++p;
        }else{
            str2 = str1.substr(pos,len) + str2;
            pos += len;
            p += len;
        }
    }

    return UTF8string(str2);
}
