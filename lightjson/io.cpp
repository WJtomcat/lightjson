//
//  io.cpp
//  lightjson
//
//  Created by Admin on 2019/12/30.
//  Copyright © 2019 Admin. All rights reserved.
//

#include "io.hpp"
#include <iostream>


namespace lightjson {

FileIOReader::FileIOReader(FILE *rf): f(rf) {}

FileIOReader::FileIOReader(const char * fname)
{
    name = fname;
    f = fopen(fname, "r");
    
    need_close = true;
}

size_t FileIOReader::operator()(void *ptr, size_t size, size_t nitems) {
    return fread(ptr, size, nitems, f);
}

FileIOReader::~FileIOReader() {
    if (need_close) {
        int ret = fclose(f);
        if (ret != 0) {
            // todo
        }
    }
}

int FileIOReader::fileno() {
    return ::fileno(f);
}


void getfilechar()
{
    char filename[100] = "/Users/admin/Desktop/cpp_test/lightjson/lightjson/test";
    std::cout << filename << std::endl;
    FileIOReader reader(filename);
    size_t nitems = 2;
    char *buffer = new char[100];
    size_t ret = reader(buffer, sizeof(char), nitems);
    std::cout << ret << std::endl;
    std::cout << buffer << std::endl;
}


}  // namespace lightjson
