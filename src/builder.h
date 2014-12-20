/* 
 * File:   conversion.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 20, 2014, 11:01 AM
 */

#ifndef FORCEFIELD_H
#define    FORCEFIELD_H

#include <nan.h>
#include <openbabel/forcefield.h>
#include "common.h"
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class ForceField : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);
        static Local <Object> NewInstance(OBForceField *forcefield);
        static ForceField* Unwrap(Local<Object> obj);

        OBForceField *ob;

    private:
        explicit ForceField();
        ~ForceField();

        static NAN_METHOD(New);
        static NAN_METHOD(FindForceField);
        static NAN_METHOD(Setup);
        static NAN_METHOD(SystematicRotorSearch);

        static NAN_GETTER(GetEnergy);

        static Persistent <Function> constructor;

    };
}

#endif	/* FORCEFIELD_H */