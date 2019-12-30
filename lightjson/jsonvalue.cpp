//
//  jsonvalue.cpp
//  lightjson
//
//  Created by Admin on 2019/12/30.
//  Copyright © 2019 Admin. All rights reserved.
//

#include "jsonvalue.hpp"
#include <assert.h>

namespace lightjson {


json_value::json_value()
{
    
}

json_value::~json_value()
{
    
}

json_array::json_array()
{
    type = JSON_ARRAY;
}

void json_array::add_member(json_value *member)
{
    assert(member != nullptr);
    array_members.push_back(member);
    size += 1;
}

json_array::~json_array()
{
    for(auto val = array_members.begin(); val != array_members.end(); val++)
    {
        delete *val;
    }
}

json_object::json_object()
{
    type = JSON_OBJECT;
}

void json_object::add_member(std::string key, json_value* member)
{
    assert(member != nullptr);
    keys.push_back(key);
    values.push_back(member);
    size += 1;
}

json_object::~json_object()
{
    for(auto val = values.begin(); val != values.end(); val++)
    {
        delete *val;
    }
}


char* parse_whitespace(char *p)
{
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        p++;
    }
    return p;
}



} // namespace lightjson
