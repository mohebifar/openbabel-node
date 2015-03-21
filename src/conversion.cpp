#include "conversion.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent<Function> Conversion::constructor;

    Conversion::Conversion() {
        ob = new OBConversion();
    }

    Conversion::~Conversion() {
        delete ob;
    }

    Conversion *Conversion::Unwrap(Local<Object> obj) {
        Conversion *conversion = node::ObjectWrap::Unwrap<Conversion>(obj);
        return conversion;
    }

    void Conversion::Init(Handle<Object> exports) {
        NanScope();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);
        tpl->SetClassName(NanNew("Conversion"));
        tpl->InstanceTemplate()->SetInternalFieldCount(2);

        // Prototype
        NODE_SET_PROTOTYPE_METHOD(tpl, "read", Read);
        NODE_SET_PROTOTYPE_METHOD(tpl, "setInFormat", SetInFormat);
        NODE_SET_PROTOTYPE_METHOD(tpl, "setOutFormat", SetOutFormat);
        NODE_SET_PROTOTYPE_METHOD(tpl, "write", Write);

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Conversion"), tpl->GetFunction());
    }

    NAN_METHOD(Conversion::New) {
        NanScope();

        if (args.IsConstructCall()) {
            Conversion *obj = new Conversion();
            obj->Wrap(args.This());
        }

        NanReturnValue(args.This());
    }

    NAN_METHOD(Conversion::Read) {
        NanScope();

        std::string str = std::string(*v8::String::AsciiValue(args[0]->ToString()));

        Conversion *obj = Unwrap(args.Holder());
        if (args[1]->IsObject()) {
            Mol *molObj = Mol::Unwrap(args[1]->ToObject());
            obj->ob->ReadString(molObj->ob, str);
            NanReturnValue(args[1]->ToObject());
        } else {
            OBMol *mol = new OBMol();
            Handle<Object> instance = Mol::NewInstance(mol);
            obj->ob->ReadString(mol, str);

            NanReturnValue(instance);
        }
    }

    NAN_METHOD(Conversion::SetInFormat) {
        NanScope();

        Conversion *obj = Unwrap(args.Holder());
        const char *format = ToConstChar(args[0]->ToString());

        if (obj->ob->SetInFormat(format)) {
            NanReturnValue(args.This());
        } else {
            NanThrowError("The Input format is invalid.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Conversion::SetOutFormat) {
        NanScope();

        Conversion *obj = Unwrap(args.Holder());

        std::string str = std::string(*v8::String::AsciiValue(args[0]->ToString()));

        const char *format = str.c_str();

        if (obj->ob->SetOutFormat(format)) {
            NanReturnValue(args.This());
        } else {
            NanThrowError("The Input format is invalid.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Conversion::Write) {
        NanScope();

        bool trimWhitespace = false;

        Conversion *obj = Unwrap(args.Holder());

        if (args[0]->IsObject()) {
            if (args[1]->IsBoolean()) {
                trimWhitespace = args[1]->BooleanValue();
            }

            Mol *molObj = Mol::Unwrap(args[0]->ToObject());
            std::string str = obj->ob->WriteString(molObj->ob, trimWhitespace);
            NanReturnValue(NanNew(str));
        } else {
            NanThrowError("Invalid Arguments");
            NanReturnUndefined();
        }
    }

}