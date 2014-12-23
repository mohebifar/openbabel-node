/* 
 * File:   common.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 17, 2014, 2:24 AM
 */

#ifndef COMMON_H
#define COMMON_H

#include <v8.h>
#include <typeinfo>

using namespace v8;

namespace {

    typedef std::vector<Persistent<Object> > Stack;

    void logger(std::string str) {
        std::string a = std::string("console.log('") + std::string(str) + std::string("');");
        
        const char *sourceStringC = a.c_str();

        Local<String> sourceStringV8 = String::New(sourceStringC);

        Local<Script> script = Script::Compile(sourceStringV8);
        script->Run();
    }

    char* itoa(int val, int base) {
        static char buf[32] = {0};

        int i = 30;

        for (; val && i; --i, val /= base)

            buf[i] = "0123456789abcdef"[val % base];

        return &buf[i + 1];
    }
    
    void logger(int a) {
        logger(std::string(itoa(a, 10)));
    }

    std::string ToString(Handle<String> str) {
        return std::string(*String::AsciiValue(str));
    }

    const char* ToConstChar(Handle<String> str) {
        std::string a = std::string(*String::AsciiValue(str));
        return a.c_str();
    }
}

#endif /* COMMON_H */