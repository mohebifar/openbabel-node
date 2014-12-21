#include <v8.h>
#include "builder.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> Builder::constructor;

    Builder::Builder() {
        ob = new OBBuilder();
    }

    Builder::~Builder() {
    }

    Builder* Builder::Unwrap(Local < Object > obj) {
        Builder *builder = node::ObjectWrap::Unwrap<Builder>(obj);
        return builder;
    }

    void Builder::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);
        tpl->SetClassName(NanNew("Builder"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Prototype
        tpl->PrototypeTemplate()->Set(NanNew("build"), NanNew < FunctionTemplate > (Build)->GetFunction());

        // Prototype Properties

        // Static Methods

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Builder"), tpl->GetFunction());
    }

    Local <Object> Builder::NewInstance(OBBuilder *builder) {
        NanEscapableScope();

        Local <Function> cons = NanNew < Function > (constructor);
        Local <Object> instance;

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        instance = cons->NewInstance(argc, argv);


        Builder *obj = Unwrap(instance);
        obj->ob = builder;

        return NanEscapeScope(instance);
    }

    NAN_METHOD(Builder::New) {
        NanScope();

        if (args.IsConstructCall()) {
            Builder *obj = new Builder();
            obj->Wrap(args.This());
        }

        NanReturnValue(args.This());
    }

    NAN_METHOD(Builder::Build) {
        NanScope();

        Builder *obj = Unwrap(args.Holder());
        if (args[0]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[0]->ToObject());
            obj->ob->Build(*molObj->ob);
            NanReturnValue(args.This());
        } else {

            NanReturnValue(NanNew("Error"));
        }
    }

}