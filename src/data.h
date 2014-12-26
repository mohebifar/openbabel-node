/* 
 * File:   atom.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 16, 2014, 03:15 AM
 */

#ifndef DATA_H
#define DATA_H

#include <nan.h>
#include <openbabel/base.h>
#include "common.h"
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {

    class Mol;

    class Data : public node::ObjectWrap {
    public:
        static void Init(Handle<Object> exports);

        static Local<Object> NewInstance(OBGenericData *atom);

        static Data *Unwrap(Local<Object> obj);

        OBGenericData *ob;

    private:
        Data();

        ~Data();

        static NAN_METHOD(New);

        static NAN_METHOD(GetValue);

        static NAN_METHOD(GetAttribute);

        static Persistent<Function> constructor;
        static Stack container;

    };

}


#endif	/* DATA_H */
