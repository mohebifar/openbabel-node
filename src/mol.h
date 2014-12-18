/* 
 * File:   mol.h
 * Author: Mohamad Mohebifar
 *
 * Created on December 17, 2014, 11:21 AM
 */

#ifndef MOL_H
#define MOL_H

#include <nan.h>
#include <openbabel/mol.h>
#include "common.h"
#include "atom.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class Atom;

    class Mol : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);

        static Local <Object> NewInstance(OBMol *mol);

        OBMol *ob;
        std::vector<Atom*> _atoms;

    private:
        Mol();
        ~Mol();

        static NAN_METHOD(New);
        static NAN_METHOD(IsChiral);
        static NAN_METHOD(AddHydrogens);
        static NAN_GETTER(GetMolWeight);
        static NAN_GETTER(GetAtomsCount);
        static NAN_GETTER(GetEnergy);

        static Persistent <Function> constructor;

    };
}
#endif	/* MOL_H */
