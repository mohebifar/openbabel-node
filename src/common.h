/* 
 * File:   common.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 17, 2014, 2:24 AM
 */

#ifndef COMMON_H
#define COMMON_H
namespace {

    void logger(std::string str) {
        std::string a = std::string("console.log('") + std::string(str) + std::string("');");
        
        const char *sourceStringC = a.c_str();

        v8::Local<v8::String> sourceStringV8 = v8::String::New(sourceStringC);

        v8::Local<v8::Script> script = v8::Script::Compile(sourceStringV8);
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
}

#endif /* COMMON_H */