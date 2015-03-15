/* 
 * File:   atom.h
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
#include "data.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {

    class Mol;

    class Atom : public node::ObjectWrap {
    public:
        static void Init(Handle<Object> exports);

        static Local<Object> NewInstance(OBAtom *atom);

        static Atom *Unwrap(Local<Object> obj);

        OBAtom *ob;

    private:
        Atom();

        ~Atom();

        static NAN_METHOD(New);

        static NAN_METHOD(GetDistance);

        static NAN_METHOD(IsInRing);

        static NAN_METHOD(IsConnected);

        static NAN_METHOD(IsCarboxylOxygen);

        static NAN_METHOD(IsPhosphateOxygen);

        static NAN_METHOD(IsSulfateOxygen);

        static NAN_METHOD(IsNitroOxygen);

        static NAN_METHOD(IsAmideNitrogen);

        static NAN_METHOD(IsPolarHydrogen);

        static NAN_METHOD(IsNonPolarHydrogen);

        static NAN_METHOD(IsAromaticNOxide);

        static NAN_METHOD(IsAxial);

        static NAN_METHOD(ForEachBond);

        static NAN_METHOD(ForEachNeighbour);

        static NAN_METHOD(HasBondOfOrder);

        static NAN_METHOD(CountBondsOfOrder);

        static NAN_METHOD(MatchesSMARTS);

        static NAN_METHOD(GetData);

        static NAN_GETTER(GetIndex);

        static NAN_SETTER(SetIndex);

        static NAN_GETTER(GetAtomicNumber);

        static NAN_SETTER(SetAtomicNumber);

        static NAN_GETTER(GetX);

        static NAN_SETTER(SetX);

        static NAN_GETTER(GetY);

        static NAN_SETTER(SetY);

        static NAN_GETTER(GetZ);

        static NAN_SETTER(SetZ);

        static Persistent<Function> constructor;
        static Stack container;

    };

}


#endif	/* ATOM_H */
