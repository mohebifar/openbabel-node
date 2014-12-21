/* 
 * File:   conversion.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 20, 2014, 13:13 PM
 */

#ifndef BUILDER_H
#define    BUILDER_H

#include <nan.h>
#include <openbabel/builder.h>
#include "common.h"
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class Builder : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);
        static Local <Object> NewInstance(OBBuilder *builder);
        static Builder* Unwrap(Local<Object> obj);

        OBBuilder *ob;

    private:
        explicit Builder();
        ~Builder();

        static NAN_METHOD(New);
        static NAN_METHOD(Build);

        static Persistent <Function> constructor;

    };
}

#endif	/* BUILDER_H */