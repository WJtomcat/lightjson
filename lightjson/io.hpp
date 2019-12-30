//
//  io.hpp
//  lightjson
//
//  Created by Admin on 2019/12/30.
//  Copyright © 2019 Admin. All rights reserved.
//

#ifndef io_hpp
#define io_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <cstdio>

namespace lightjson {


struct IOReader {
    // name that can be used in error messages
    std::string name;
    
    // fread
    virtual size_t operator()(void *ptr, size_t size, size_t nitems) = 0;
    
    virtual int fileno() = 0;
    
    virtual ~IOReader() {}
};

struct IOWriter {
    // name that can be used in error messages
    std::string name;

    // fwrite
    virtual size_t operator()(
         const void *ptr, size_t size, size_t nitems) = 0;

    // return a file number that can be memory-mapped
    virtual int fileno () = 0;

    virtual ~IOWriter() {}
};

struct FileIOReader: IOReader {
    FILE *f = nullptr;
    bool need_close = false;
    
    FileIOReader(FILE *rf);
    
    FileIOReader(const char * fname);
    
    ~FileIOReader() override;
    
    size_t operator()(void *ptr, size_t size, size_t nitems) override;
    
    int fileno() override;
};


struct FileIOWriter: IOWriter {
    FILE *f = nullptr;
    bool need_close = false;

    FileIOWriter(FILE *wf);

    FileIOWriter(const char * fname);

    ~FileIOWriter() override;

    size_t operator()(const void *ptr, size_t size, size_t nitems) override;

    int fileno() override;
};

void getfilechar();






} // namespace lightjson

#endif /* io_hpp */
