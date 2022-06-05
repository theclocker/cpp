/**
 * Author: Yonatan Vega
 * Id: 318233616
 */
#include "str.h"

Str::Str() {
    m_str = new char[4];
    strcpy(m_str, "none");
}

Str::Str( const Str& other ) {
    m_str = new char[strlen(other.getStr()) + 1];
    strcpy(m_str, other.getStr());
}

Str::Str( const char* str ) {
    m_str = new char[strlen(str) + 1];
    strcpy(m_str, str);
}

Str::~Str() {
    delete [] m_str;
}

bool Str::operator==( const Str& other ) const {
    if (strlen(m_str) != strlen(other.getStr())) return false;
    for (int i = 0; i < strlen(m_str); i++) {
        if (m_str[i] != other.getStr()[i]) return false;
    }
    return true;
}

bool Str::operator!=( const Str& other ) const {
    return !(*this == other);
}

bool Str::operator>( const Str& other ) const {
    if (*this == other) return false;
    const char* otherStr = other.getStr();
    int i = 0;
    while (i < strlen(otherStr) && i < strlen(m_str)) {
        if (otherStr[i] > m_str[i]) return false;
        i++;
    }
    return true;
}

bool Str::operator<( const Str& other ) const {
    if (*this == other) return false;
    const char* otherStr = other.getStr();
    int i = 0;
    while (i < strlen(otherStr) && i < strlen(m_str)) {
        if (otherStr[i] < m_str[i]) return false;
        i++;
    }
    return true;
}

const Str& Str::operator=( const Str& other ) {
    if (&other != this) {
        delete[] m_str;
        m_str = new char[strlen(other.getStr()) + 1];
        strcpy(m_str, other.getStr());
    }
    return *this;
}

const Str& Str::operator=( const char* str ) {
    delete[] m_str;
    m_str = new char[strlen(str) + 1];
    strcpy(m_str, str);
    return *this;
}
char& Str::operator[]( int index ) const {
    if (m_str == nullptr || index > (strlen(m_str) - 1) || index < 0) {
        return *(new char);
    }
    return m_str[index];
}

// Prefix incrementation
const Str& Str::operator++() {
    for (int i = 0; i < strlen(m_str); i++) {
        m_str[i]++;
    }
    return *this; // No need for temp here, just return the value after the incrementation
}

// Postfix incrementation
Str Str::operator++( int ) {
    if (m_str == nullptr) return nullptr;
    char * tmp = new char[strlen(m_str) + 1];
    strcpy(tmp, m_str);
    for (int i = 0; i < strlen(m_str); i++) {
        m_str[i]++;
    }
    return {tmp}; // Return the value before the increment and then increment
}

Str::operator int() const {
    if (m_str == nullptr) return 0;
    return strlen(m_str);
}

int Str::operator()( char ch ) const {
    if (m_str == nullptr) return -1;
    for (int i = 0; i < strlen(m_str); i++) {
        if (m_str[i] == ch) return i;
    }
    return -1;
}

Str Str::operator+( const Str& other ) const {
    char * tmp = new char[strlen(m_str) + strlen(other.getStr()) + 1];
    strcpy(tmp, m_str);
    char * pos = tmp + strlen(m_str);
    strcpy(pos, other.getStr());
    return {tmp};
}

const Str& Str::operator+=( const Str& other ) {
    char * tmp = new char[strlen(m_str) + strlen(other.getStr()) + 1];
    strcpy(tmp, m_str);
    char * tmpPointer = tmp + strlen(m_str);
    strcpy(tmpPointer, other.getStr());
    m_str = tmp;
    return *this;
}

Str operator+( const char* str, const Str& other ) {
    char * tmp = new char[strlen(str) + strlen(other.getStr()) + 1];
    strcpy(tmp, str);
    char * tmpPointer = tmp + strlen(other.getStr());
    strcpy(tmpPointer, other.getStr());
    return {tmp};
}

Str operator*( int num, const Str& other ) {
    char * tmp = new char[num * strlen(other.getStr()) + 1];
    char * tmpPointer = tmp;
    strcpy(tmpPointer, other.getStr());
    for (int i = 0; i < num - 1; i++) {
        tmpPointer += strlen(other.getStr());
        strcpy(tmpPointer, other.getStr());
    }
    return {tmp};
}
