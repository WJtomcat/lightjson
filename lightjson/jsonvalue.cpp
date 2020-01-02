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

json_value* parse_number(const char* begin, json_value* output_value)
{
    const char* p = begin;
    if (*p == '-') p++;
    if (*p == '0') p++;
    else {
        if (!is_digit1to9(p)) return output_value;
        for (p++; is_digit(p); p++);
    }
    if (*p == '.') {
        p++;
        if (!is_digit(p)) return output_value;
    }
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '+' || *p == '-') p++;
        if (!is_digit(p)) return output_value;
        for (p++; is_digit(p); p++);
    }
    errno = 0;
    double value = strtod(begin, NULL);
    if (errno == ERANGE) return output_value;
    
    output_value->set_number(value);
    return output_value;
}


json_value* parse_string(const char* begin, json_value* output_value)
{
    const char* p = begin;
    std::string value;
    if (!is_expect(p, '\"')) return output_value;
    while(true) {
        p++;
        if (*p == '\"') break;
    }
    // todo!
    return output_value;
}

json_value* parse_array(const char* begin, json_value* output_value)
{
    size_t i = 0;
    size_t size = 0;
    const char* p = begin;
    
    if (!is_expect(p, '[')) return output_value;
    parse_whitespace(p);
    if (*p == ']') return output_value;
    
    while (true) {
        json_value * element_value = parse_value(p);
        output_value->array_vector.push_back(element_value);
        i++;
        size++;
        parse_whitespace(p);
        if (*p == ']') break;
    }
    output_value->type = json_value::JSON_ARRAY;
    return output_value;
}

json_value* parse_object(const char* begin, json_value* output_value)
{
//    size_t i = 0;
//    size_t size = 0;
//    const char *p = begin;
//
//    if (!is_expect(p, '{')) return output_value;
//    parse_whitespace(p);
//    if (*p == '}')
//    {
//        output_value->type = json_value::JSON_OBJECT;
//        return output_value;
//    }
//    while(true) {
//
//        i++;
//        size++;
//        parse_whitespace(p);
//        if (*p == '}')
//        {
//            break;
//        }
//
//    }
    
    // todo!
    
    return output_value;
}


json_value* parse_bool(const char* begin, json_value* output_value)
{
    const char* p = begin;
    if (*p == 't' && *(p+1) == 'r' && *(p+2) == 'u' && *(p+3) == 'e')
        output_value->set_bool(true);
    if (*p == 'f' && *(p+1) == 'a' && *(p+2) == 'l' && *(p+3) == 's' && *(p+4) == 'e')
        output_value->set_bool(false);
    if (*p == 'n' && *(p+1) == 'u' && *(p+2) == 'l' && *(p+3) == 'l')
        output_value->set_null();
    return output_value;
}


void json_value::set_number(double value)
{
    value_number = value;
    type = JSON_NUMBER;
    parse_finished = true;
}


void json_value::set_bool(bool value)
{
    value_bool = value;
    type = JSON_BOOL;
    parse_finished = true;
}


void json_value::set_null()
{
    type = JSON_NULL;
    parse_finished = true;
}


void json_value::set_string(std::string value)
{
    value_string = value;
    type = JSON_STRING;
    parse_finished = true;
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
    json_value* output_value = new json_value();
    begin = parse_whitespace(begin);
    switch (*begin) {
        case 't': return parse_bool(begin, output_value);
        case 'f': return parse_bool(begin, output_value);
        case 'n': return parse_bool(begin, output_value);
        case '"': return parse_string(begin, output_value);
        case '[': return parse_array(begin, output_value);
        case '{': return parse_object(begin, output_value);
        default: return parse_number(begin, output_value);
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
