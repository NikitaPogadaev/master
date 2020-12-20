// ConsoleApplication11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>

class String {
private:
    size_t sz = 0;
    size_t buffer = 8;
    char* str = new char[buffer];
    void grow_buffer() {
        buffer *= 2;
        char* new_string = new char[buffer];
        memcpy(new_string, str, sz);
        delete[] str;
        str = new_string;
    }
    void dec_buffer() {
        buffer = sz;
        char* new_string = new char[buffer];
        memcpy(new_string, str, sz);
        delete[] str;
        str = new_string;
    }
    void String_swap(String& s) {
        std::swap(sz, s.sz);
        std::swap(str, s.str);
    }

public:
    String() = default;
    String(char c) :sz(1), str(new char[1]) {
        memset(str, c, 1);
    }
    String(const char* c) {
        sz = strlen(c);
        delete[] str;
        char* str = new char[sz * 2];
        buffer = sz * 2;
        memcpy(str, c, strlen(c));
    }
    String(size_t n, char c = '\0') :sz(n), buffer(n + 1), str(new char[n+1]) {
        memset(str, c, n);
    }
    String(const String& s) : String(s.sz*2) {
        memcpy(str, s.str, sz);
    }
    ~String() {
        if (str)delete[] str;
    }

    void pop_back() {
        sz--;
        if (sz < buffer / 2) {
            dec_buffer();
        }
    }
    void push_back(char c) {
        if (sz + 1 == buffer)
            grow_buffer();
        str[sz++] = c;
    }

    char& front() {
        return str[0];
    }
    char& back() {
        return str[sz - 1];
    }
    char front() const {
        return str[0];
    }
    char back() const {
        return str[sz - 1];
    }

    String& operator=(String s) {
        String_swap(s);
        return *this;
    }
    String& operator=(char c) {
        String s(1, c);
        String_swap(s);
        return *this;
    }
    char& operator [](size_t i) {
        return str[i];
    }
    char operator [](size_t i) const {
        return str[i];
    }
    String& operator +=(const String& s) {
        for (size_t i = 0; i < s.sz; i++) {
            this->push_back(s[i]);
        }
        return *this;
    }
    String& operator +=(const char& c) {
        this->push_back(c);
        return *this;
    }

    size_t length() const {
        return sz;
    }

    bool empty() const {
        return (sz == 0);
    }

    void clear() {
        sz = 0;
        delete[] str;
        char* str = new char[8];
        buffer = 8;
    }

    String substr(const size_t nach, const size_t n) {
        String s(n);
        memcpy(s.str, str + nach, n);
        return s;
    }
    size_t find(const String& s) {
        for (size_t i = 0; i <= sz - s.sz; i++) {
            for (size_t j = i; j < s.sz + i; j++) {
                if (s[j - i] != (*this)[j])j = s.sz + i;
                if (j - i == s.sz - 1)
                    return i;
            }
        }
        return sz;
    }
    size_t rfind(const String& s) {
        for (size_t i = 0; i <= sz - s.sz; i++) {
            size_t i1 = sz - s.sz - i;
            for (size_t j = i1; j < s.sz + i1; j++) {
                if (s[j - i1] != (*this)[j])j = s.sz + i1;
                if (j - i1 == s.sz - 1)
                    return i1;
            }
        }
        return sz;
    }

    String substr(const size_t& nach, const size_t& n) const {
        String s(n);
        memcpy(s.str, str + nach, n);
        return s;
    }
    size_t find(const String& s) const {
        for (size_t i = 0; i <= sz - s.sz; i++) {
            for (size_t j = i; j < s.sz + i; j++) {
                if (s[j - i] != (*this)[j])j = s.sz + i;
                if (j - i == s.sz - 1)
                    return i;
            }
        }
        return sz;
    }
    size_t rfind(const String& s) const {

        for (size_t i = 0; i <= sz - s.sz; i++) {
            size_t i1 = sz - s.sz - i;
            for (size_t j = i1; j < s.sz + i1; j++) {
                if (s[j - i1] != (*this)[j])j = s.sz + i1;
                if (j - i1 == s.sz - 1)
                    return i1;
            }
        }
        return sz;
    }

    friend bool operator==(const String& s1, const String& s2);

};


bool operator ==(const String& s1, const String& s2) {
    if (s1.length() == s2.length()) {
        if (s1.length() == 0)
            return memcmp(s1.str, s2.str, s1.length()) == 0;
        else return true;
    }
    else return false;
}

String operator+(const String& s1, const String& s2)
{
    String temp = s1;
    return temp += s2;
}


String operator+(const String& s1, const char& s2) {
    String temp = s1;
    return temp += s2;
}

String operator+(const char& c, const String& s2) {
    String temp(1, c);
    return temp += s2;
}

std::istream& operator >> (std::istream& in, String& s) {
    char c;
    do {
        c = in.get();
    } while (isspace(c));
    while (!in.eof() && !isspace(c)) {
        s.push_back(c);
        c = in.get();
    }
    return in;
}

std::ostream& operator << (std::ostream& out, const String& s) {
    for (size_t i = 0; i < s.length(); i++)
        out << s[i];
    return out;
}
