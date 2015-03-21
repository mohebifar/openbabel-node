#include <v8.h>
#include "forcefield.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent<Function> ForceField::constructor;

    ForceField::ForceField() {

    }

    ForceField::~ForceField() {
        delete ob;
    }

    ForceField *ForceField::Unwrap(Local<Object> obj) {
        ForceField *forcefield = node::ObjectWrap::Unwrap<ForceField>(obj);
        return forcefield;
    }

    void ForceField::Init(Handle<Object> exports) {
        NanScope();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);
        tpl->SetClassName(NanNew("ForceField"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        tpl->PrototypeTemplate()->Set(NanNew("setForceField"), NanNew < FunctionTemplate > (FindForceField)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setup"), NanNew < FunctionTemplate > (Setup)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("systematicRotorSearch"), NanNew < FunctionTemplate > (SystematicRotorSearch)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("systematicRotorSearchInitialize"), NanNew < FunctionTemplate > (SystematicRotorSearchInitialize)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("systematicRotorSearchNextConformer"), NanNew < FunctionTemplate > (SystematicRotorSearchNextConformer)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("randomRotorSearch"), NanNew < FunctionTemplate > (RandomRotorSearch)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("randomRotorSearchInitialize"), NanNew < FunctionTemplate > (RandomRotorSearchInitialize)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("randomRotorSearchNextConformer"), NanNew < FunctionTemplate > (RandomRotorSearchNextConformer)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("weightedRotorSearch"), NanNew < FunctionTemplate > (WeightedRotorSearch)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setLineSearchType"), NanNew < FunctionTemplate > (SetLineSearchType)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getLineSearchType"), NanNew < FunctionTemplate > (GetLineSearchType)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("prepareAtomTypes"), NanNew < FunctionTemplate > (GetAtomTypes)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("preparePartialCharges"), NanNew < FunctionTemplate > (GetPartialCharges)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getCoordinates"), NanNew < FunctionTemplate > (GetCoordinates)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getConformers"), NanNew < FunctionTemplate > (GetConformers)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setCoordinates"), NanNew < FunctionTemplate > (GetCoordinates)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setConformers"), NanNew < FunctionTemplate > (GetConformers)->GetFunction());

        // Prototype Properties
        tpl->PrototypeTemplate()->SetAccessor(NanNew("energy"), GetEnergy);

        // Static Methods
        tpl->Set("findForceField", NanNew < FunctionTemplate > (FindForceField)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("ForceField"), tpl->GetFunction());
    }

    Local<Object> ForceField::NewInstance(OBForceField *forcefield) {
        NanEscapableScope();

        Local<Function> cons = NanNew < Function > (constructor);
        Local<Object> instance;

        const unsigned argc = 0;
        Local<Value> argv[argc] = {};
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

    NAN_METHOD(ForceField::SystematicRotorSearch) {
        NanEscapableScope();

        unsigned int steps;

        if (args[0]->IsNumber()) {
            steps = args[1]->NumberValue();
        } else {
            steps = 2500;
        }

        ForceField *obj = Unwrap(args.Holder());
        obj->ob->SystematicRotorSearch(steps);

        NanReturnThis();
    }

    NAN_METHOD(ForceField::SystematicRotorSearchInitialize) {
        NanEscapableScope();

        unsigned int steps;

        if (args[0]->IsNumber()) {
            steps = args[1]->NumberValue();
        } else {
            steps = 2500;
        }

        ForceField *obj = Unwrap(args.Holder());

        NanReturnValue(NanNew(obj->ob->SystematicRotorSearchInitialize(steps)));
    }

    NAN_METHOD(ForceField::SystematicRotorSearchNextConformer) {
        NanEscapableScope();

        unsigned int steps;

        if (args[0]->IsNumber()) {
            steps = args[1]->NumberValue();
        } else {
            steps = 2500;
        }

        ForceField *obj = Unwrap(args.Holder());

        NanReturnValue(NanNew(obj->ob->SystematicRotorSearchNextConformer(steps)));
    }

    NAN_METHOD(ForceField::RandomRotorSearch) {
        NanEscapableScope();

        if (args[0]->IsNumber()) {
            unsigned int conformers = args[0]->NumberValue();
            unsigned int steps;

            if (args[1]->IsNumber()) {
                steps = args[1]->NumberValue();
            } else {
                steps = 2500;
            }

            ForceField *obj = Unwrap(args.Holder());
            obj->ob->RandomRotorSearch(conformers, steps);

            NanReturnThis();
        } else {
            NanThrowError("First argument is required and should be a number.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::RandomRotorSearchInitialize) {
        NanEscapableScope();

        unsigned int steps;

        if (args[0]->IsNumber()) {
            steps = args[1]->NumberValue();
        } else {
            steps = 2500;
        }

        ForceField *obj = Unwrap(args.Holder());
        obj->ob->RandomRotorSearchInitialize(steps);

        NanReturnThis();
    }

    NAN_METHOD(ForceField::RandomRotorSearchNextConformer) {
        NanEscapableScope();

        unsigned int steps;

        if (args[0]->IsNumber()) {
            steps = args[1]->NumberValue();
        } else {
            steps = 2500;
        }

        ForceField *obj = Unwrap(args.Holder());

        NanReturnValue(NanNew(obj->ob->RandomRotorSearchNextConformer(steps)));
    }

    NAN_METHOD(ForceField::WeightedRotorSearch) {
        NanEscapableScope();

        if (args[0]->IsNumber()) {
            unsigned int conformers = args[0]->NumberValue();
            unsigned int steps;

            if (args[1]->IsNumber()) {
                steps = args[1]->NumberValue();
            } else {
                steps = 2500;
            }

            ForceField *obj = Unwrap(args.Holder());
            obj->ob->WeightedRotorSearch(conformers, steps);

            NanReturnThis();
        } else {
            NanThrowError("First argument is required and should be a number.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::SetLineSearchType) {
        NanEscapableScope();

        if (args[0]->IsNumber()) {
            int type = args[0]->NumberValue();

            ForceField *obj = Unwrap(args.Holder());
            obj->ob->SetLineSearchType(type);

            NanReturnThis();
        } else {
            NanThrowError("First argument is required and should be a number.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::GetLineSearchType) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());

        NanReturnValue(NanNew(obj->ob->GetLineSearchType()));
    }

    NAN_METHOD(ForceField::GetAtomTypes) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());

        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->GetAtomTypes(*molObj->ob)));
        } else {
            NanThrowError("1 Argument of type Mol is required.");
            NanReturnUndefined();
        }

    }

    NAN_METHOD(ForceField::GetPartialCharges) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());

        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->GetPartialCharges(*molObj->ob)));
        } else {
            NanThrowError("1 Argument of type Mol is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::GetCoordinates) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());


        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->GetCoordinates(*molObj->ob)));
        } else {
            NanThrowError("1 Argument of type Mol is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::GetConformers) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());


        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->GetConformers(*molObj->ob)));
        } else {
            NanThrowError("1 Argument of type Mol is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::SetCoordinates) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());


        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->SetCoordinates(*molObj->ob)));
        } else {
            NanThrowError("1 Argument of type Mol is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::SetConformers) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());


        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->SetConformers(*molObj->ob)));
        } else {
            NanThrowError("1 Argument of type Mol is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::EnableCutOff) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());

        if (args[0]->IsBoolean()) {
            obj->ob->EnableCutOff(args[0]->BooleanValue());
            NanReturnThis();
        } else {
            NanThrowError("1 Argument is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(ForceField::IsCutOffEnabled) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());

        NanReturnValue(NanNew(obj->ob->IsCutOffEnabled()));
    }

    NAN_METHOD(ForceField::DistanceGeometry) {
        NanEscapableScope();

        ForceField *obj = Unwrap(args.Holder());

        obj->ob->DistanceGeometry();
        NanReturnThis();
    }

    NAN_METHOD(ForceField::FindForceField) {
        NanEscapableScope();

        std::string str = std::string(*v8::String::AsciiValue(args[0]->ToString()));

        OBForceField *forcefield = OBForceField::FindForceField(str.c_str());
        Handle<Object> instance = NewInstance(forcefield);

        NanReturnValue(instance);
    }

    NAN_GETTER(ForceField::GetEnergy) {
        NanScope();

        ForceField *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->Energy()));

    }
}