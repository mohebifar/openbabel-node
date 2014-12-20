#include <v8.h>
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> Mol::constructor;

    Mol::Mol() {
        ob = new OBMol();
    }

    Mol::~Mol() {
        delete ob;
    }

    Mol* Mol::Unwrap(Local < Object > obj) {
        Mol *mol = node::ObjectWrap::Unwrap<Mol>(obj);
        return mol;
    }

    Local <Object> Mol::NewInstance(OBMol *mol) {
        NanEscapableScope();

        Local <Function> cons = NanNew < Function > (constructor);
        Local <Object> instance;

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        instance = cons->NewInstance(argc, argv);

        Mol *obj = Unwrap(instance);

        obj->ob = mol;


        return NanEscapeScope(instance);
    }

    void Mol::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);
        tpl->SetClassName(NanNew("Mol"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        tpl->PrototypeTemplate()->SetAccessor(NanNew("molWeight"), GetMolWeight);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("atomsCount"), GetAtomsCount);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("enery"), GetEnergy);
        tpl->PrototypeTemplate()->Set(NanNew("isChiral"), NanNew < FunctionTemplate > (IsChiral)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("addHydrogens"), NanNew < FunctionTemplate > (AddHydrogens)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getAtoms"), NanNew < FunctionTemplate > (GetAtoms)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Molecule"), tpl->GetFunction());
    }

    NAN_METHOD(Mol::New) {
        NanScope();

        Mol *obj = new Mol();
        obj->Wrap(args.This());

        NanReturnValue(args.This());
    }

    NAN_METHOD(Mol::AddHydrogens) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->AddHydrogens()));
    }

    NAN_METHOD(Mol::IsChiral) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->IsChiral()));
    }

    NAN_METHOD(Mol::GetAtoms) {
        NanScope();

        Mol *obj = Unwrap(args.This());

        Local<Array> list = Array::New(obj->ob->NumAtoms());

        FOR_ATOMS_OF_MOL (atom, obj->ob) {
            list->Set(atom->GetIdx() - 1, Atom::NewInstance(&*atom));
        }

        NanReturnValue(list);
    }

    NAN_GETTER(Mol::GetMolWeight) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetMolWt()));
    }

    NAN_GETTER(Mol::GetAtomsCount) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->NumAtoms()));
    }

    NAN_GETTER(Mol::GetEnergy) {
        NanScope();

        Mol *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetEnergy()));
    }

}