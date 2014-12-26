/* 
 * File:   bond.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 21, 2014, 03:25 PM
 */

#ifndef BOND_H
#define BOND_H

#include <nan.h>
#include <openbabel/bond.h>
#include "common.h"
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class Bond : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);
        static Local <Object> NewInstance(OBBond *bond);
        static Bond* Unwrap(Local<Object> obj);

        OBBond *ob;

    private:
        Bond();
        ~Bond();

        static NAN_METHOD(New);
        static NAN_METHOD(SetBegin);
        static NAN_METHOD(GetBeginAtom);
        static NAN_METHOD(SetEnd);
        static NAN_METHOD(GetEndAtom);
        static NAN_METHOD(SetLength);
        static NAN_METHOD(GetLength);
        static NAN_METHOD(SetOrder);
        static NAN_METHOD(GetOrder);
        static NAN_METHOD(GetParent);

        static NAN_METHOD(IsAromatic);
        static NAN_METHOD(IsInRing);
        static NAN_METHOD(IsRotor);
        static NAN_METHOD(IsAmide);
        static NAN_METHOD(IsPrimaryAmide);
        static NAN_METHOD(IsSecondaryAmide);
        static NAN_METHOD(IsTertiaryAmide);
        static NAN_METHOD(IsEster);
        static NAN_METHOD(IsCarbonyl);
        static NAN_METHOD(IsSingle);
        static NAN_METHOD(IsDouble);
        static NAN_METHOD(IsTriple);
        static NAN_METHOD(IsKSingle);
        static NAN_METHOD(IsKDouble);
        static NAN_METHOD(IsKTriple);
        static NAN_METHOD(IsClosure);
        static NAN_METHOD(IsUp);
        static NAN_METHOD(IsDown);
        static NAN_METHOD(IsWedge);
        static NAN_METHOD(IsHash);
        static NAN_METHOD(IsWedgeOrHash);
        static NAN_METHOD(IsCisOrTrans);

        static NAN_METHOD(GetData);

        static Persistent <Function> constructor;
        static Stack container;

    };

}


#endif	/* BOND_H */
