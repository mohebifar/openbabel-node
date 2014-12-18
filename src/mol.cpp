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

    Local <Object> Mol::NewInstance(OBMol * mol) {
        NanEscapableScope();

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        Local <Function> cons = NanNew<Function>(constructor);
        Local <Object> instance = cons->NewInstance(argc, argv);

        Mol *obj = ObjectWrap::Unwrap<Mol>(instance);
        obj->ob = mol;

        return NanEscapeScope(instance);
    }

    void Mol::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
        tpl->SetClassName(NanNew("Mol"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        tpl->PrototypeTemplate()->SetAccessor(NanNew("molWeight"), GetMolWeight);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("atomsCount"), GetAtomsCount);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("enery"), GetEnergy);
        tpl->PrototypeTemplate()->Set(NanNew("isChiral"), NanNew<FunctionTemplate>(IsChiral)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("addHydrogens"), NanNew<FunctionTemplate>(AddHydrogens)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Molecule"), tpl->GetFunction());
    }

    NAN_METHOD(Mol::New) {
            NanScope();

            Mol* obj = new Mol();
            obj->Wrap(args.This());

            NanReturnValue(args.This());
    }

    NAN_METHOD(Mol::AddHydrogens) {
            NanScope();

            Mol* obj = ObjectWrap::Unwrap<Mol>(args.This());
            NanReturnValue(NanNew(obj->ob->AddHydrogens()));
    }

    NAN_METHOD(Mol::IsChiral) {
            NanScope();

            Mol* obj = ObjectWrap::Unwrap<Mol>(args.This());
            NanReturnValue(NanNew(obj->ob->IsChiral()));
    }

    NAN_GETTER(Mol::GetMolWeight) {
            NanScope();

            Mol* obj = ObjectWrap::Unwrap<Mol>(args.This());
            NanReturnValue(NanNew(obj->ob->GetMolWt()));
    }

    NAN_GETTER(Mol::GetAtomsCount) {
            NanScope();

            Mol* obj = ObjectWrap::Unwrap<Mol>(args.This());
            NanReturnValue(NanNew(obj->ob->NumAtoms()));
    }

    NAN_GETTER(Mol::GetEnergy) {
            NanScope();

            Mol* obj = ObjectWrap::Unwrap<Mol>(args.This());
            NanReturnValue(NanNew(obj->ob->GetEnergy()));
    }

}