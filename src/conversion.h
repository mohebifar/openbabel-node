/* 
 * File:   conversion.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 17, 2014, 11:21 AM
 */

#ifndef CONVERSION_H
#define    CONVERSION_H

#include <nan.h>
#include <openbabel/obconversion.h>
#include "common.h"
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class Conversion : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);
        static Conversion* Unwrap(Local<Object> obj);

        OBConversion *ob;

    private:
        explicit Conversion();
        ~Conversion();

        static NAN_METHOD(New);
        static NAN_METHOD(Read);
        static NAN_METHOD(SetInFormat);
        static NAN_METHOD(SetOutFormat);
        static NAN_METHOD(Write);

        static Persistent <Function> constructor;

    };
}

#endif	/* CONVERSION_H */