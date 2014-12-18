#include "conversion.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> Conversion::constructor;

    Conversion::Conversion() {
        ob = new OBConversion();
    }

    Conversion::~Conversion() {
    }

    void Conversion::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);
        tpl->SetClassName(NanNew("Conversion"));
        tpl->InstanceTemplate()->SetInternalFieldCount(2);

        // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "read", Read);
        NODE_SET_PROTOTYPE_METHOD(tpl, "setInFormat", SetInFormat);

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Conversion"), tpl->GetFunction());
    }

    NAN_METHOD(Conversion::New) {
            NanScope();

            if (args.IsConstructCall()) {
                // Invoked as constructor: `new Conversion(...)`
                //        double value = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
                Conversion *obj = new Conversion();
                obj->Wrap(args.This());
            }

            NanReturnValue(args.This());

    }

    NAN_METHOD(Conversion::Read) {
            NanScope();

            std::string str = std::string(*v8::String::AsciiValue(args[0]->ToString()));

            Conversion* obj = ObjectWrap::Unwrap<Conversion>(args.Holder());
            if (args[1]->IsObject()) {
                Mol *molObj = node::ObjectWrap::Unwrap<Mol>(args[1]->ToObject());
                obj->ob->ReadString(molObj->ob, str);
                NanReturnValue(args[1]->ToObject());
            } else {
                OBMol *mol = new OBMol();
                Local <Object> instance = Mol::NewInstance(mol);

                obj->ob->ReadString(mol, str);

                NanReturnValue(instance);
            }

    }

    NAN_METHOD(Conversion::SetInFormat) {
            NanScope();

            Conversion* obj = ObjectWrap::Unwrap<Conversion>(args.Holder());

            std::string str = std::string(*v8::String::AsciiValue(args[0]->ToString()));

            const char *format = str.c_str();
            obj->ob->SetInFormat(format);
            obj->_in_format = args[0]->ToString();

            NanReturnValue(args.This());
    }

}