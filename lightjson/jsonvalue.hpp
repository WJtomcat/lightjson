//
//  jsonvalue.hpp
//  lightjson
//
//  Created by Admin on 2019/12/30.
//  Copyright © 2019 Admin. All rights reserved.
//

#ifndef jsonvalue_hpp
#define jsonvalue_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>


namespace lightjson {

struct json_value
{
    enum value_type{
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOL,
        JSON_NULL
    };
    
    value_type type;
    std::string value_string;
    double value_number;
    bool value_bool;
    
    std::vector<json_value *> array_vector;
    
    std::map<std::string, json_value> object_map;
    
    char* begin;
    char* end;
    
    bool parse_finished = false;
    
    explicit json_value();
    json_value(char* begin, char* end);
    json_value(std::string value_string);
    json_value(const char* begin);
    json_value(double value_number);
    json_value(bool value_bool);
    json_value(value_type type);
    
    void add_array_item(json_value* item);
    void add_object_item(std::string key, json_value* value);
    
    void parse_value();
    
    ~json_value();
};


const char* parse_whitespace(const char* &p);

json_value* parse_bool(const char* begin);

json_value* parse_string(const char* begin);

json_value* parse_array(const char* begin);

json_value* parse_object(const char* begin);

json_value* parse_number(const char* begin);

json_value* parse_value(const char* begin);

} // namespace lightjson

#endif /* jsonvalue_hpp */
