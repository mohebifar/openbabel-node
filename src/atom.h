/* 
 * File:   mol.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 16, 2014, 03:15 AM
 */

#ifndef ATOM_H
#define ATOM_H

#include <nan.h>
#include <openbabel/atom.h>
#include "common.h"
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class Mol;

    class Atom : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);
        static Local <Object> NewInstance(OBAtom *atom);
        static Atom* Unwrap(Local<Object> obj);

        OBAtom *ob;
        Mol *parent;

    private:
        Atom();

        ~Atom();

        static NAN_METHOD(New);
        static NAN_GETTER(GetAtomicNumber);

        static Persistent <Function> constructor;

    };

}


#endif	/* ATOM_H */
