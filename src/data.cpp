#include <v8.h>
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> Data::constructor;
    Stack Data::container;

    Data::Data() {

    }

    Data::~Data() {
        delete ob;
    }

    Data* Data::Unwrap(Local < Object > obj) {
        Data *data = node::ObjectWrap::Unwrap<Data>(obj);
        return data;
    }

    Local <Object> Data::NewInstance(OBGenericData *data) {
        NanEscapableScope();
        for(unsigned int i = 0; i < container.size(); i++) {
            Local<Object> ins = Local<Object>::New(container.at(i));
            if(Unwrap(ins)->ob == data) {
                return NanEscapeScope(ins);
            }
        }
        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        Local <Function> cons = NanNew<Function>(constructor);
        Local <Object> instance = cons->NewInstance(argc, argv);

        Data *obj = Unwrap(instance);
        obj->ob = data;

        return NanEscapeScope(instance);
    }

    void Data::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);

        tpl->SetClassName(NanNew("Data"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Methods
        tpl->PrototypeTemplate()->Set(NanNew("getValue"), NanNew < FunctionTemplate > (GetValue)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getAttribute"), NanNew < FunctionTemplate > (GetAttribute)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Data"), tpl->GetFunction());
    }

    NAN_METHOD(Data::New) {
        NanScope();

        Data *obj = new Data();
        obj->Wrap(args.This());
        container.push_back(Persistent<Object>::New(args.This()));

        NanReturnValue(args.This());
    }

    NAN_METHOD(Data::GetValue) {
        NanScope();

        Data *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetValue()));
    }

    NAN_METHOD(Data::GetAttribute) {
        NanScope();

        Data *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetAttribute()));
    }
}