#include <v8.h>
#include "forcefield.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> ForceField::constructor;

    ForceField::ForceField() {

    }

    ForceField::~ForceField() {
    }

    ForceField* ForceField::Unwrap(Local < Object > obj) {
        ForceField *forcefield = node::ObjectWrap::Unwrap<ForceField>(obj);
        return forcefield;
    }

    void ForceField::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);
        tpl->SetClassName(NanNew("ForceField"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        tpl->PrototypeTemplate()->Set(NanNew("setForceField"), NanNew < FunctionTemplate > (FindForceField)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setup"), NanNew < FunctionTemplate > (Setup)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("systematicRotorSearch"), NanNew < FunctionTemplate > (SystematicRotorSearch)->GetFunction());

        // Prototype Properties
        tpl->PrototypeTemplate()->SetAccessor(NanNew("energy"), GetEnergy);

        // Static Methods
        tpl->Set("findForceField", NanNew<FunctionTemplate>(FindForceField)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("ForceField"), tpl->GetFunction());
    }

    Local <Object> ForceField::NewInstance(OBForceField *forcefield) {
        NanEscapableScope();

        Local <Function> cons = NanNew < Function > (constructor);
        Local <Object> instance;

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        instance = cons->NewInstance(argc, argv);


        ForceField *obj = Unwrap(instance);
        obj->ob = forcefield;

        return NanEscapeScope(instance);
    }

    NAN_METHOD(ForceField::New) {
        NanScope();

        if (args.IsConstructCall()) {
            ForceField *obj = new ForceField();
            obj->Wrap(args.This());
        }

        NanReturnValue(args.This());
    }

    NAN_METHOD(ForceField::Setup) {
        NanScope();

        ForceField *obj = Unwrap(args.Holder());
        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());
            obj->ob->Setup(*molObj->ob);
            NanReturnValue(args.This());
        } else {

            NanReturnValue(NanNew("Error"));
        }
    }

    NAN_METHOD(ForceField::FindForceField) {
        NanEscapableScope();

        std::string str = std::string(*v8::String::AsciiValue(args[0]->ToString()));

        OBForceField *forcefield = OBForceField::FindForceField(str.c_str());
        Handle <Object> instance = NewInstance(forcefield);

        NanReturnValue(instance);

    }

    NAN_METHOD(ForceField::SystematicRotorSearch) {
        NanEscapableScope();

        int steps = args[0]->NumberValue();

        ForceField *obj = Unwrap(args.Holder());
        obj->ob->SystematicRotorSearch(steps);

        NanReturnThis();
    }

    NAN_GETTER(ForceField::GetEnergy) {
        NanScope();

        ForceField *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->Energy()));

    }
}