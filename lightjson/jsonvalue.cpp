//
//  jsonvalue.cpp
//  lightjson
//
//  Created by Admin on 2019/12/30.
//  Copyright © 2019 Admin. All rights reserved.
//

#include "jsonvalue.hpp"
#include <assert.h>
#include <cerrno>

namespace lightjson {


inline bool is_expect(const char* c, char ch)
{
    return (*c == ch);
}

inline bool is_digit(const char* c)
{
    return (*c >= '0' && *c <= '9');
}

inline bool is_digit1to9(const char* c)
{
    return (*c >= '1' && *c <= '9');
}

json_value* parse_number(const char* begin)
{
    const char* p = begin;
    if (*p == '-') p++;
    if (*p == '0') p++;
    else {
        if (!is_digit1to9(p)) return nullptr;
        for (p++; is_digit(p); p++);
    }
    if (*p == '.') {
        p++;
        if (!is_digit(p)) return nullptr;
    }
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!is_digit(p)) return nullptr;
        for (p++; is_digit(p); p++);
    }
    errno = 0;
    double value = strtod(begin, NULL);
    if (errno == ERANGE) return nullptr;
    
    return new json_value(value);
}


char* get_char(const char* begin)
{
    const char* p = begin;
    if (!is_expect(p, '\"')) return nullptr;
    size_t size = 0;
    char *output;
    while(true) {
        p++;
        if (*p == '\"') break;
        size++;
    }
    output = new char[size + 1];
    memcpy(output, begin, size);
    return output;
}


json_value* parse_string(const char* begin)
{
    const char* p = begin;
    if (!is_expect(p, '\"')) return nullptr;
    size_t size = 0;
    char *output;
    while(true) {
        p++;
        if (*p == '\"') break;
        size++;
    }
    output = new char[size + 1];
    memcpy(output, begin, size);
    return new json_value(output);
}


json_value* parse_array(const char* begin)
{
    const char* p = begin;
    
    if (!is_expect(p, '[')) return nullptr;
    parse_whitespace(p);
    if (*p == ']')
    {
        return new json_value(json_value::JSON_ARRAY);
    }
    
    json_value * output_value = new json_value(json_value::JSON_ARRAY);
    while (true) {
        json_value * element_value = parse_value(p);
        output_value->add_array_item(element_value);
        parse_whitespace(p);
        if (*p == ']') break;
    }
    return output_value;
}

json_value* parse_object(const char* begin)
{
    const char* p;
    if (!is_expect(p, '{')) return nullptr;
    parse_whitespace(p);
    if (*p == '}') return new json_value(json_value::JSON_OBJECT);
    
    json_value *output_value = new json_value(json_value::JSON_OBJECT);
    while(true)
    {
        if (*p != '"')
        {
            delete output_value;
            return nullptr;
        }
        const char* key_char = get_char(p);
        std::string key_string = key_char;
        delete[] key_char;
        parse_whitespace(p);
        if (*p != ':')
        {
            delete output_value;
            return nullptr;
        }
        p++;
        parse_whitespace(p);
        json_value *value = parse_value(p);
        output_value->add_object_item(key_string, value);
        if (*p == ',')
        {
            p++;
            parse_whitespace(p);
        }
        else if (*p == '}')
        {
            p++;
            break;
        }
    }
    return output_value;
}


json_value* parse_bool(const char* begin)
{
    const char* p = begin;
    if (*p == 't' && *(p+1) == 'r' && *(p+2) == 'u' && *(p+3) == 'e')
        return new json_value(true);
    if (*p == 'f' && *(p+1) == 'a' && *(p+2) == 'l' && *(p+3) == 's' && *(p+4) == 'e')
        return new json_value(false);
    if (*p == 'n' && *(p+1) == 'u' && *(p+2) == 'l' && *(p+3) == 'l')
        return new json_value();
    return nullptr;
}


json_value::json_value()
{
    
}

json_value::json_value(char* begin, char* end)
{
    this->begin = begin;
    this->end = end;
}


json_value* parse_value(const char* begin)
{
    begin = parse_whitespace(begin);
    switch (*begin) {
        case 't': return parse_bool(begin);
        case 'f': return parse_bool(begin);
        case 'n': return parse_bool(begin);
        case '"': return parse_string(begin);
        case '[': return parse_array(begin);
        case '{': return parse_object(begin);
        default: return parse_number(begin);
    }
}

json_value::json_value(std::string value_string)
{
    type = JSON_STRING;
    this->value_string = value_string;
    parse_finished = true;
}

json_value::json_value(double value_number)
{
    type = JSON_NUMBER;
    this->value_number = value_number;
    parse_finished = true;
}

json_value::json_value(bool value_bool)
{
    type = JSON_BOOL;
    this->value_bool = value_bool;
    parse_finished = true;
}

json_value::~json_value()
{
    
}



const char* parse_whitespace(const char* &p)
{
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        p++;
    }
    return p;
}



} // namespace lightjson
