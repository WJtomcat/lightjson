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


namespace lightjson {

struct json_value
{
    enum value_type{
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOL
    };
    
    value_type type;
    std::string value_string;
    double value_number;
    bool value_bool;
    
    explicit json_value();
    
    virtual ~json_value();
};


struct json_array: json_value
{
    size_t size;
    std::vector<json_value *> array_members;
    
    explicit json_array();
    
    void add_member(json_value* member);
    
    ~json_array() override;
};


struct json_object: json_value
{
    size_t size = 0;
    std::vector<std::string> keys;
    std::vector<json_value*> values;
    
    explicit json_object();
    
    void add_member(std::string key, json_value* member);
    ~json_object() override;
};

struct parse_object_string
{
    char* buffer;
    char* parse_top;
    
    char* filename;
    
    char* heap_top;
    char* heap_bottom;
    
    std::string heap_string;
    
    explicit parse_object_string(const char* fname);
    
    json_value* parse();
    
    ~parse_object_string();
};



} // namespace lightjson

#endif /* jsonvalue_hpp */
