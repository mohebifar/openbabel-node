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
#include "bond.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    class Atom;
    class Bond;

    class Mol : public node::ObjectWrap {
    public:
        static void Init(Handle <Object> exports);
        static Local <Object> NewInstance(OBMol *mol);
        static Mol* Unwrap(Local<Object> obj);

        static std::vector< Local <Object> > container;

        OBMol *ob;

    private:
        Mol();
        ~Mol();

        static NAN_METHOD(New);
        static NAN_METHOD(Empty);
        static NAN_METHOD(IsChiral);
        static NAN_METHOD(HasNonZeroCoords);
        static NAN_METHOD(HasAromaticPerceived);
        static NAN_METHOD(HasSSSRPerceived);
        static NAN_METHOD(HasLSSRPerceived);
        static NAN_METHOD(HasRingAtomsAndBondsPerceived);
        static NAN_METHOD(HasAtomTypesPerceived);
        static NAN_METHOD(HasRingTypesPerceived);
        static NAN_METHOD(HasChiralityPerceived);
        static NAN_METHOD(HasPartialChargesPerceived);
        static NAN_METHOD(HasHybridizationPerceived);
        static NAN_METHOD(HasImplicitValencePerceived);
        static NAN_METHOD(HasKekulePerceived);
        static NAN_METHOD(HasClosureBondsPerceived);
        static NAN_METHOD(HasChainsPerceived);
        static NAN_METHOD(HasHydrogensAdded);
        static NAN_METHOD(HasAromaticCorrected);
        static NAN_METHOD(AddHydrogens);
        static NAN_METHOD(DeleteHydrogens);
        static NAN_METHOD(ForEachAtom);
        static NAN_METHOD(ForEachBond);
        static NAN_METHOD(CreateAtom);
        static NAN_METHOD(CreateBond);
        static NAN_METHOD(AddAtom);
        static NAN_METHOD(DeleteAtom);
        static NAN_METHOD(AddBond);
        static NAN_METHOD(DeleteBond);
        static NAN_METHOD(GetTorsion);
        static NAN_METHOD(GetAngle);
        static NAN_METHOD(GetTotalCharge);
        static NAN_METHOD(CorrectForPH);
        static NAN_METHOD(Has2D);
        static NAN_METHOD(Has3D);
        static NAN_METHOD(GetData);
        static NAN_GETTER(GetMolWeight);

        static NAN_GETTER(GetAtoms);
        static NAN_INDEX_GETTER(GetAtomByIndex);
        static NAN_INDEX_GETTER(GetBondByIndex);
        static NAN_GETTER(GetExactMass);
        static NAN_GETTER(GetAtomsCount);
        static NAN_GETTER(GetBondsCount);
        static NAN_GETTER(GetHeavyAtomsCount);
        static NAN_GETTER(GetEnergy);
        static NAN_GETTER(GetTotalCharge);
        static NAN_GETTER(NumConformers);

        static Persistent<ObjectTemplate> atomsTemplate;
        static Persistent<ObjectTemplate> bondsTemplate;
        static Persistent <Function> constructor;

    };

}
#endif	/* MOL_H */
