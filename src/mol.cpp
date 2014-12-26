#include <v8.h>
#include <nan.h>
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent<Function> Mol::constructor;
    Persistent<ObjectTemplate> Mol::atomsTemplate;
    Persistent<ObjectTemplate> Mol::bondsTemplate;

    Mol::Mol() {
        ob = new OBMol();
    }

    Mol::~Mol() {
        delete ob;
    }

    Mol *Mol::Unwrap(Local<Object> obj) {
        Mol *mol = node::ObjectWrap::Unwrap<Mol>(obj);
        return mol;
    }

    Local<Object> Mol::NewInstance(OBMol *mol) {
        NanEscapableScope();

        Local<Function> cons = NanNew < Function > (constructor);
        Local<Object> instance;

        const unsigned argc = 0;
        Local<Value> argv[argc] = {};
        instance = cons->NewInstance(argc, argv);

        Mol *obj = Unwrap(instance);

        obj->ob = mol;


        return NanEscapeScope(instance);
    }

    void Mol::Init(Handle<Object> exports) {
        NanScope();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);
        tpl->SetClassName(NanNew("Mol"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        Local<ObjectTemplate> atoms = NanNew < ObjectTemplate > ();
        atoms->SetInternalFieldCount(1);
        atoms->SetIndexedPropertyHandler(GetAtomByIndex);
        NanAssignPersistent(atomsTemplate, atoms);

        Local<ObjectTemplate> bonds = NanNew < ObjectTemplate > ();
        bonds->SetInternalFieldCount(1);
        bonds->SetIndexedPropertyHandler(GetBondByIndex);
        NanAssignPersistent(bondsTemplate, bonds);

        // Prototype
        tpl->PrototypeTemplate()->SetAccessor(NanNew("molarMass"), GetMolWeight);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("exactMass"), GetExactMass);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("atomsCount"), GetAtomsCount);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("bondsCount"), GetBondsCount);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("heavyAtomsCount"), GetHeavyAtomsCount);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("enery"), GetEnergy);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("totalCharge"), GetTotalCharge);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("conformersCount"), NumConformers);

        tpl->PrototypeTemplate()->Set(NanNew("isChiral"), NanNew < FunctionTemplate > (IsChiral)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isEmpty"), NanNew < FunctionTemplate > (Empty)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("addHydrogens"), NanNew < FunctionTemplate > (AddHydrogens)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("deleteHydrogens"), NanNew < FunctionTemplate > (AddHydrogens)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("forEachAtom"), NanNew < FunctionTemplate > (ForEachAtom)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("forEachBond"), NanNew < FunctionTemplate > (ForEachBond)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("createAtom"), NanNew < FunctionTemplate > (CreateAtom)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("createBond"), NanNew < FunctionTemplate > (CreateBond)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("addAtom"), NanNew < FunctionTemplate > (AddAtom)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("deleteAtom"), NanNew < FunctionTemplate > (DeleteAtom)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("addBond"), NanNew < FunctionTemplate > (AddBond)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("deleteBond"), NanNew < FunctionTemplate > (DeleteBond)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getTorsion"), NanNew < FunctionTemplate > (GetTorsion)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getAngle"), NanNew < FunctionTemplate > (GetAngle)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setPH"), NanNew < FunctionTemplate > (CorrectForPH)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("has3D"), NanNew < FunctionTemplate > (Has3D)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("has2D"), NanNew < FunctionTemplate > (Has2D)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasNonZeroCoords"), NanNew < FunctionTemplate > (HasNonZeroCoords)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasAromaticPerceived"), NanNew < FunctionTemplate > (HasAromaticPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasAromaticPerceived"), NanNew < FunctionTemplate > (HasAromaticPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasLSSRPerceived"), NanNew < FunctionTemplate > (HasLSSRPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasRingAtomsAndBondsPerceived"), NanNew < FunctionTemplate > (HasRingAtomsAndBondsPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasAtomTypesPerceived"), NanNew < FunctionTemplate > (HasAtomTypesPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasRingTypesPerceived"), NanNew < FunctionTemplate > (HasRingTypesPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasChiralityPerceived"), NanNew < FunctionTemplate > (HasChiralityPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasPartialChargesPerceived"), NanNew < FunctionTemplate > (HasPartialChargesPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasHybridizationPerceived"), NanNew < FunctionTemplate > (HasHybridizationPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasImplicitValencePerceived"), NanNew < FunctionTemplate > (HasImplicitValencePerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasKekulePerceived"), NanNew < FunctionTemplate > (HasKekulePerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasClosureBondsPerceived"), NanNew < FunctionTemplate > (HasClosureBondsPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasChainsPerceived"), NanNew < FunctionTemplate > (HasChainsPerceived)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasHydrogensAdded"), NanNew < FunctionTemplate > (HasHydrogensAdded)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasAromaticCorrected"), NanNew < FunctionTemplate > (HasAromaticCorrected)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Molecule"), tpl->GetFunction());
    }

    NAN_METHOD(Mol::New) {
        NanScope();

        Handle<Object> self = args.This();

        Mol *obj = new Mol();
        obj->Wrap(self);

        Local<Object> atoms = atomsTemplate->NewInstance();
        NanSetInternalFieldPointer(atoms, 0, const_cast<Mol *>(obj));

        Local<Object> bonds = bondsTemplate->NewInstance();
        NanSetInternalFieldPointer(bonds, 0, const_cast<Mol *>(obj));

        self->Set(NanNew("atoms"), atoms);
        self->Set(NanNew("bonds"), bonds);

        NanReturnValue(args.This());
    }

    NAN_METHOD(Mol::Empty) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->Empty()));
    }

    NAN_METHOD(Mol::HasNonZeroCoords) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasNonZeroCoords()));
    }

    NAN_METHOD(Mol::HasAromaticPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasAromaticPerceived()));
    }

    NAN_METHOD(Mol::HasSSSRPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasSSSRPerceived()));
    }

    NAN_METHOD(Mol::HasLSSRPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasLSSRPerceived()));
    }

    NAN_METHOD(Mol::HasRingAtomsAndBondsPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasRingAtomsAndBondsPerceived()));
    }

    NAN_METHOD(Mol::HasAtomTypesPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasAtomTypesPerceived()));
    }

    NAN_METHOD(Mol::HasRingTypesPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasRingTypesPerceived()));
    }

    NAN_METHOD(Mol::HasChiralityPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasChiralityPerceived()));
    }

    NAN_METHOD(Mol::HasPartialChargesPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasPartialChargesPerceived()));
    }

    NAN_METHOD(Mol::HasHybridizationPerceived) {
        NanScope();


        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasHybridizationPerceived()));
    }

    NAN_METHOD(Mol::HasImplicitValencePerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasImplicitValencePerceived()));
    }

    NAN_METHOD(Mol::HasKekulePerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasKekulePerceived()));
    }

    NAN_METHOD(Mol::HasClosureBondsPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasClosureBondsPerceived()));
    }

    NAN_METHOD(Mol::HasChainsPerceived) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasChainsPerceived()));
    }

    NAN_METHOD(Mol::HasHydrogensAdded) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasHydrogensAdded()));
    }

    NAN_METHOD(Mol::HasAromaticCorrected) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->HasAromaticCorrected()));
    }

    NAN_METHOD(Mol::AddHydrogens) {
        NanScope();

        bool polaronly = false;

        if (args[0]->IsBoolean() && args[0]->BooleanValue()) {
            polaronly = true;
        }

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->AddHydrogens(polaronly)));
    }

    NAN_METHOD(Mol::DeleteHydrogens) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        if (args[0]->IsBoolean() && args[0]->BooleanValue()) {
            NanReturnValue(NanNew(obj->ob->DeleteNonPolarHydrogens()));
        } else {
            NanReturnValue(NanNew(obj->ob->DeleteHydrogens()));
        }

    }

    NAN_METHOD(Mol::IsChiral) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->IsChiral()));
    }

    NAN_GETTER(Mol::GetAtoms) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        Local<Array> list = Array::New(obj->ob->NumAtoms());

        FOR_ATOMS_OF_MOL (atom, obj->ob) {
            list->Set(atom->GetIdx() - 1, Atom::NewInstance(&*atom));
        }

        NanReturnValue(list);
    }

    NAN_METHOD(Mol::ForEachAtom) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        Local<Function> cb = args[0].As<Function>();

        FOR_ATOMS_OF_MOL (atom, obj->ob) {
            const unsigned argc = 1;
            Local<Value> argv[argc] = {Atom::NewInstance(&*atom)};
            NanMakeCallback(NanGetCurrentContext()->Global(), cb, argc, argv);
        }

        NanReturnUndefined();
    }

    NAN_INDEX_GETTER(Mol::GetAtomByIndex) {
        NanScope();

        Handle<Object> self = args.This();
        void *ptr = NanGetInternalFieldPointer(self, 0);
        Mol *obj = static_cast<Mol *>(ptr);

        int idx = index;
        OBAtom *atom = obj->ob->GetAtomById(idx);
        if (atom != NULL) {
            NanReturnValue(Atom::NewInstance(atom));
        } else {
            NanThrowError("Atom with given index not found.");
            NanReturnUndefined();
        }

    }

    NAN_INDEX_GETTER(Mol::GetBondByIndex) {
        NanScope();

        Handle<Object> self = args.This();
        void *ptr = NanGetInternalFieldPointer(self, 0);
        Mol *obj = static_cast<Mol *>(ptr);

        int idx = index;
        OBBond *bond = obj->ob->GetBond(idx);
        if (bond != NULL) {
            NanReturnValue(Bond::NewInstance(bond));
        } else {
            NanThrowError("Bond with given index not found.");
            NanReturnUndefined();
        }

    }

    NAN_METHOD(Mol::ForEachBond) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        Local<Function> cb = args[0].As<Function>();

        FOR_BONDS_OF_MOL (bond, obj->ob) {
            const unsigned argc = 1;
            Local<Value> argv[argc] = {Bond::NewInstance(&*bond)};
            NanMakeCallback(NanGetCurrentContext()->Global(), cb, argc, argv);
        }

        NanReturnUndefined();
    }

    NAN_METHOD(Mol::CreateAtom) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        Local<Object> atom = Atom::NewInstance(obj->ob->NewAtom());

        NanReturnValue(atom);
    }

    NAN_METHOD(Mol::AddAtom) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        if (args[0]->IsObject()) {

            Atom *atomObj = Atom::Unwrap(args[0]->ToObject());
            NanReturnValue(NanNew(obj->ob->AddAtom(*atomObj->ob)));

        } else {
            NanThrowError("1 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Mol::DeleteAtom) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        if (args[0]->IsObject()) {

            Atom *atomObj = Atom::Unwrap(args[0]->ToObject());
            NanReturnValue(NanNew(obj->ob->DeleteAtom(atomObj->ob)));

        } else {
            NanThrowError("1 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Mol::CreateBond) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        Local<Object> bond = Bond::NewInstance(obj->ob->NewBond());

        NanReturnValue(bond);
    }

    NAN_METHOD(Mol::AddBond) {
        NanScope();

        Mol *obj = Unwrap(args.This());


        if (args[0]->IsObject()) {

            Bond *bondObj = Bond::Unwrap(args[0]->ToObject());
            NanReturnValue(NanNew(obj->ob->AddBond(*bondObj->ob)));

        } else {
            NanThrowError("1 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Mol::DeleteBond) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        if (args[0]->IsObject()) {

            Bond *bondObj = Bond::Unwrap(args[0]->ToObject());
            NanReturnValue(NanNew(obj->ob->DeleteBond(bondObj->ob)));

        } else {
            NanThrowError("1 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Mol::GetTorsion) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        if (args[0]->IsObject() && args[1]->IsObject() && args[2]->IsObject() && args[3]->IsObject()) {
            Atom *atom0Obj = Atom::Unwrap(args[0]->ToObject());
            Atom *atom1Obj = Atom::Unwrap(args[1]->ToObject());
            Atom *atom2Obj = Atom::Unwrap(args[2]->ToObject());
            Atom *atom3Obj = Atom::Unwrap(args[3]->ToObject());
            NanReturnValue(NanNew(obj->ob->GetTorsion(atom0Obj->ob, atom1Obj->ob, atom2Obj->ob, atom3Obj->ob)));
        } else {
            NanThrowError("4 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Mol::GetAngle) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        if (args[0]->IsObject() && args[1]->IsObject() && args[2]->IsObject()) {
            Atom *atom0Obj = Atom::Unwrap(args[0]->ToObject());
            Atom *atom1Obj = Atom::Unwrap(args[1]->ToObject());
            Atom *atom2Obj = Atom::Unwrap(args[2]->ToObject());
            NanReturnValue(NanNew(obj->ob->GetAngle(atom0Obj->ob, atom1Obj->ob, atom2Obj->ob)));
        } else {
            NanThrowError("4 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Mol::CorrectForPH) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        double pH = 7.4;
        if (args[0]->IsNumber()) {
            pH = args[0]->NumberValue();
        }

        NanReturnValue(NanNew(obj->ob->CorrectForPH(pH)));
    }

    NAN_METHOD(Mol::Has2D) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->Has2D()));
    }

    NAN_METHOD(Mol::Has3D) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->Has3D()));
    }

    NAN_GETTER(Mol::GetMolWeight) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetMolWt()));
    }

    NAN_GETTER(Mol::GetExactMass) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetExactMass()));
    }

    NAN_GETTER(Mol::GetAtomsCount) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->NumAtoms()));
    }

    NAN_GETTER(Mol::GetBondsCount) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->NumBonds()));
    }

    NAN_GETTER(Mol::GetHeavyAtomsCount) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->NumHvyAtoms()));
    }

    NAN_GETTER(Mol::GetEnergy) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetEnergy()));
    }

    NAN_GETTER(Mol::GetTotalCharge) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetTotalCharge()));
    }

    NAN_GETTER(Mol::NumConformers) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->NumConformers()));
    }

    NAN_METHOD(Mol::GetData) {
        NanScope();

        if(args[0]->IsString()) {
            const char* name = ToConstChar(args[0]->ToString());
            Mol *obj = Unwrap(args.This());
            OBGenericData *d = obj->ob->GetData(name);
            if(d != NULL) {
                Local <Object> data = Data::NewInstance(d);
                NanReturnValue(data);
            } else {
                std::string error = "The given data is not set: " + std::string(name);
                NanThrowError(error.c_str());
                NanReturnUndefined();
            }
        } else {
            NanThrowError("1 Argument is required.");
            NanReturnUndefined();
        }
    }

}