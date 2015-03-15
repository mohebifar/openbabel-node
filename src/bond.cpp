#include <v8.h>
#include "bond.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent<Function> Bond::constructor;
    Stack Bond::container;

    Bond::Bond() {
        ob  = new OBBond();
    }

    Bond::~Bond() {
        delete ob;
    }

    Bond* Bond::Unwrap(Local < Object > obj) {
        Bond *bond = node::ObjectWrap::Unwrap<Bond>(obj);
        return bond;
    }

    Local <Object> Bond::NewInstance(OBBond *bond) {
        NanEscapableScope();

        for(unsigned int i = 0; i < container.size(); i++) {
            Local<Object> ins = NanNew<Object>(container.at(i));
            if(Unwrap(ins)->ob == bond) {
                return NanEscapeScope(ins);
            }
        }

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        Local <Function> cons = NanNew<Function>(constructor);
        Local <Object> instance = cons->NewInstance(argc, argv);

        Bond *obj = Unwrap(instance);
        obj->ob = bond;

        return NanEscapeScope(instance);
    }

    void Bond::Init(Handle<Object> exports) {
        NanScope();

        // Prepare constructor template
        Local<FunctionTemplate> tpl = NanNew < FunctionTemplate > (New);

        tpl->SetClassName(NanNew("Bond"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Methods
        tpl->PrototypeTemplate()->Set(NanNew("getBegin"), NanNew < FunctionTemplate > (GetBeginAtom)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getEnd"), NanNew < FunctionTemplate > (GetEndAtom)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setBegin"), NanNew < FunctionTemplate > (SetBegin)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setEnd"), NanNew < FunctionTemplate > (SetEnd)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setLength"), NanNew < FunctionTemplate > (SetLength)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getLength"), NanNew < FunctionTemplate > (SetLength)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("setOrder"), NanNew < FunctionTemplate > (SetOrder)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getOrder"), NanNew < FunctionTemplate > (GetOrder)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getParent"), NanNew < FunctionTemplate > (GetParent)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isAromatic"), NanNew < FunctionTemplate > (IsAromatic)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isInRing"), NanNew < FunctionTemplate > (IsInRing)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isRotor"), NanNew < FunctionTemplate > (IsRotor)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isAmide"), NanNew < FunctionTemplate > (IsAmide)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isPrimaryAmide"), NanNew < FunctionTemplate > (IsPrimaryAmide)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isSecondaryAmide"), NanNew < FunctionTemplate > (IsSecondaryAmide)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isTertiaryAmide"), NanNew < FunctionTemplate > (IsTertiaryAmide)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isEster"), NanNew < FunctionTemplate > (IsEster)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isCarbonyl"), NanNew < FunctionTemplate > (IsCarbonyl)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isSingle"), NanNew < FunctionTemplate > (IsSingle)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isDouble"), NanNew < FunctionTemplate > (IsDouble)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isTriple"), NanNew < FunctionTemplate > (IsTriple)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isKSingle"), NanNew < FunctionTemplate > (IsKDouble)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isKTriple"), NanNew < FunctionTemplate > (IsKTriple)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isClosure"), NanNew < FunctionTemplate > (IsClosure)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isUp"), NanNew < FunctionTemplate > (IsUp)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isDown"), NanNew < FunctionTemplate > (IsDown)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isWedge"), NanNew < FunctionTemplate > (IsWedge)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isHash"), NanNew < FunctionTemplate > (IsHash)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isWedgeOrHash"), NanNew < FunctionTemplate > (IsWedgeOrHash)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isCisOrTrans"), NanNew < FunctionTemplate > (IsCisOrTrans)->GetFunction());

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Bond"), tpl->GetFunction());
    }

    NAN_METHOD(Bond::New) {
        NanScope();

        Bond *obj = new Bond();
        obj->Wrap(args.This());
        container.push_back(Persistent<Object>::New(args.This()));

        NanReturnValue(args.This());
    }

    NAN_METHOD(Bond::SetLength) {
        NanScope();

        if (args[0]->IsNumber()) {
            Bond *obj = Unwrap(args.This());

            obj->ob->SetLength(args[0]->NumberValue());

            NanReturnThis();
        } else {
            NanThrowError("1 Argument of type double is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Bond::GetLength) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetLength()));
    }

    NAN_METHOD(Bond::SetBegin) {
        NanScope();

        if (args[0]->IsObject()) {
            Bond *obj = Unwrap(args.This());

            Atom *atom = Atom::Unwrap(args[0]->ToObject());
            obj->ob->SetBegin(atom->ob);

            NanReturnThis();
        } else {
            NanThrowError("1 Argument of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Bond::SetEnd) {
        NanScope();

        if (args[0]->IsObject()) {
            Bond *obj = Unwrap(args.This());

            Atom *atom = Atom::Unwrap(args[0]->ToObject());
            obj->ob->SetEnd(atom->ob);

            NanReturnThis();
        } else {
            NanThrowError("1 Argument of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Bond::GetParent) {
        NanScope();

        Bond *obj = Unwrap(args.This());
        NanReturnValue(Mol::NewInstance(obj->ob->GetParent()));
    }

    NAN_METHOD(Bond::GetBeginAtom) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        OBAtom *atom = obj->ob->GetBeginAtom();


        NanReturnValue(Atom::NewInstance(atom));
    }

    NAN_METHOD(Bond::GetEndAtom) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        OBAtom *atom = obj->ob->GetEndAtom();

        NanReturnValue(Atom::NewInstance(atom));
    }

    NAN_METHOD(Bond::IsAromatic) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsAromatic()));
    }

    NAN_METHOD(Bond::IsInRing) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsInRing()));
    }

    NAN_METHOD(Bond::IsRotor) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsRotor()));
    }

    NAN_METHOD(Bond::IsAmide) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsAmide()));
    }

    NAN_METHOD(Bond::IsPrimaryAmide) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsPrimaryAmide()));
    }

    NAN_METHOD(Bond::IsSecondaryAmide) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsSecondaryAmide()));
    }

    NAN_METHOD(Bond::IsTertiaryAmide) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsTertiaryAmide()));
    }

    NAN_METHOD(Bond::IsEster) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsEster()));
    }

    NAN_METHOD(Bond::IsCarbonyl) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsCarbonyl()));
    }

    NAN_METHOD(Bond::IsSingle) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsSingle()));
    }

    NAN_METHOD(Bond::IsDouble) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsDouble()));
    }

    NAN_METHOD(Bond::IsTriple) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsTriple()));
    }

    NAN_METHOD(Bond::IsKSingle) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsKSingle()));
    }

    NAN_METHOD(Bond::IsKDouble) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsKDouble()));
    }

    NAN_METHOD(Bond::IsKTriple) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsKTriple()));
    }

    NAN_METHOD(Bond::IsClosure) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsClosure()));
    }

    NAN_METHOD(Bond::IsUp) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsUp()));
    }

    NAN_METHOD(Bond::IsDown) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsDown()));
    }

    NAN_METHOD(Bond::IsWedge) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsWedge()));
    }

    NAN_METHOD(Bond::IsHash) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsHash()));
    }

    NAN_METHOD(Bond::IsWedgeOrHash) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsWedgeOrHash()));
    }

    NAN_METHOD(Bond::IsCisOrTrans) {
        NanScope();

        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsCisOrTrans()));
    }

    NAN_METHOD(Bond::SetOrder) {
        NanScope();

        if (args[0]->IsNumber()) {
            Bond *obj = Unwrap(args.This());

            int order = args[0]->NumberValue();
            obj->ob->SetBondOrder(order);
            NanReturnThis();
        } else {
            NanThrowError("1 Argument of type integer is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Bond::GetOrder) {
        NanScope();
        Bond *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetBondOrder()));
    }

    NAN_METHOD(Bond::GetData) {
        NanScope();

        if (args[0]->IsString()) {
            const char *name = ToConstChar(args[0]->ToString());
            Bond *obj = Unwrap(args.This());
            OBGenericData *d = obj->ob->GetData(name);
            if (d != NULL) {
                Local<Object> data = Data::NewInstance(d);
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