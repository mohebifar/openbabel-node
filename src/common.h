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

    std::string ToString(Handle<String> str) {
        return std::string(*NanAsciiString(str));
    }

    const char* ToConstChar(Handle<String> str) {
        std::string a = ToString(str);
        return a.c_str();
    }
}

#endif /* COMMON_H */