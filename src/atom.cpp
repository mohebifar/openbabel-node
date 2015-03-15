#include <v8.h>
#include "mol.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> Atom::constructor;
    Stack Atom::container;

    Atom::Atom() {
        ob = new OBAtom();
    }

    Atom::~Atom() {
        delete ob;
    }

    Atom* Atom::Unwrap(Local < Object > obj) {
        Atom *atom = node::ObjectWrap::Unwrap<Atom>(obj);
        return atom;
    }

    Local <Object> Atom::NewInstance(OBAtom *atom) {
        NanEscapableScope();
        for(unsigned int i = 0; i < container.size(); i++) {
            Local<Object> ins = NanNew<Object>(container.at(i));
            if(Unwrap(ins)->ob == atom) {
                return NanEscapeScope(ins);
            }
        }

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        Local <Function> cons = NanNew<Function>(constructor);
        Local <Object> instance = cons->NewInstance(argc, argv);

        Atom *obj = Unwrap(instance);
        obj->ob = atom;

        return NanEscapeScope(instance);
    }

    void Atom::Init(Handle < Object > exports) {
        NanScope();

        // Prepare constructor template
        Local <FunctionTemplate> tpl = NanNew<FunctionTemplate>(New);

        tpl->SetClassName(NanNew("Atom"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Methods
        tpl->PrototypeTemplate()->Set(NanNew("isConnected"), NanNew < FunctionTemplate > (IsConnected)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isCarboxylOxygen"), NanNew < FunctionTemplate > (IsCarboxylOxygen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isPhosphateOxygen"), NanNew < FunctionTemplate > (IsPhosphateOxygen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isSulfateOxygen"), NanNew < FunctionTemplate > (IsSulfateOxygen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isNitroOxygen"), NanNew < FunctionTemplate > (IsNitroOxygen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isAmideNitrogen"), NanNew < FunctionTemplate > (IsAmideNitrogen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isPolarHydrogen"), NanNew < FunctionTemplate > (IsPolarHydrogen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isNonPolarHydrogen"), NanNew < FunctionTemplate > (IsNonPolarHydrogen)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isAromaticNOxide"), NanNew < FunctionTemplate > (IsAromaticNOxide)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isAxial"), NanNew < FunctionTemplate > (IsAxial)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("isInRing"), NanNew < FunctionTemplate > (IsInRing)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("hasBondOfOrder"), NanNew < FunctionTemplate > (HasBondOfOrder)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("countBondsOfOrder"), NanNew < FunctionTemplate > (CountBondsOfOrder)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("forEachBond"), NanNew < FunctionTemplate > (ForEachBond)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("forEachNeighbour"), NanNew < FunctionTemplate > (ForEachNeighbour)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getDistance"), NanNew < FunctionTemplate > (GetDistance)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("matchesSMARTS"), NanNew < FunctionTemplate > (MatchesSMARTS)->GetFunction());
        tpl->PrototypeTemplate()->Set(NanNew("getData"), NanNew < FunctionTemplate > (GetData)->GetFunction());

        // Properties
        tpl->PrototypeTemplate()->SetAccessor(NanNew("atomicNumber"), GetAtomicNumber, SetAtomicNumber);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("_x"), GetX, SetX);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("_y"), GetY, SetY);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("_z"), GetZ, SetZ);
        tpl->PrototypeTemplate()->SetAccessor(NanNew("index"), GetIndex, SetIndex);

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Atom"), tpl->GetFunction());

    }

    NAN_METHOD(Atom::New) {
        NanScope();

        Atom *obj = new Atom();
        obj->Wrap(args.This());
        container.resize(container.size() + 1);
        NanAssignPersistent(container.at(container.size() - 1), args.This());

        NanReturnValue(args.This());
    }

    NAN_METHOD(Atom::GetDistance) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        if(args[0]->IsObject()) {
            Atom *atomObj = Atom::Unwrap(args[0]->ToObject());
            NanReturnValue(NanNew(obj->ob->GetDistance(atomObj->ob)));
        } else {
            NanThrowError("1 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Atom::HasBondOfOrder) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        if(args[0]->IsNumber()) {
            unsigned int order = args[0]->NumberValue();

            NanReturnValue(NanNew(obj->ob->HasBondOfOrder(order)));
        } else {
            NanThrowError("1 Arguments is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Atom::CountBondsOfOrder) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        if(args[0]->IsNumber()) {
            unsigned int order = args[0]->NumberValue();

            NanReturnValue(NanNew(obj->ob->CountBondsOfOrder(order)));
        } else {
            NanThrowError("1 Arguments is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Atom::IsInRing) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsInRing()));
    }

    NAN_METHOD(Atom::GetData) {
        NanScope();

        if(args[0]->IsString()) {
            const char* name = ToConstChar(args[0]->ToString());
            Atom *obj = Unwrap(args.This());
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

    NAN_METHOD(Atom::IsCarboxylOxygen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsCarboxylOxygen()));
    }

    NAN_METHOD(Atom::IsPhosphateOxygen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsPhosphateOxygen()));
    }

    NAN_METHOD(Atom::IsSulfateOxygen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsSulfateOxygen()));
    }

    NAN_METHOD(Atom::IsNitroOxygen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsNitroOxygen()));
    }

    NAN_METHOD(Atom::IsAmideNitrogen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsAmideNitrogen()));
    }

    NAN_METHOD(Atom::IsPolarHydrogen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsPolarHydrogen()));
    }

    NAN_METHOD(Atom::IsNonPolarHydrogen) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsNonPolarHydrogen()));
    }

    NAN_METHOD(Atom::IsAromaticNOxide) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsAromaticNOxide()));
    }

    NAN_METHOD(Atom::IsAxial) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->IsAxial()));
    }

    NAN_METHOD(Atom::IsConnected) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        if(args[0]->IsObject()) {
            Atom *atomObj = Atom::Unwrap(args[0]->ToObject());

            NanReturnValue(NanNew(obj->ob->IsConnected(atomObj->ob)));
        } else {
            NanThrowError("1 Arguments of type Atom is required.");
            NanReturnUndefined();
        }
    }

    NAN_METHOD(Atom::MatchesSMARTS) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        if(args[0]->IsString()) {
            const char *str = ToConstChar(args[0]->ToString());
            NanReturnValue(NanNew(obj->ob->MatchesSMARTS(str)));
        } else {
            NanThrowError("1 Arguments of type string is required.");
            NanReturnUndefined();
        }
    }

    NAN_GETTER(Atom::GetAtomicNumber) {
        NanScope();

        Atom *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetAtomicNum()));
    }

    NAN_SETTER(Atom::SetAtomicNumber) {
        NanScope();

        if(value->IsNumber()) {
            Atom *obj = Unwrap(args.This());
            int atomicNum = value->NumberValue();
            obj->ob->SetAtomicNum(atomicNum);
        }
    }

    NAN_GETTER(Atom::GetIndex) {
        NanScope();

        Atom *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetIdx()));
    }

    NAN_SETTER(Atom::SetIndex) {
        NanScope();

        if(value->IsNumber()) {
            Atom *obj = Unwrap(args.This());
            const int v = value->NumberValue();
            obj->ob->SetIdx(v);
        }
    }

    NAN_METHOD(Atom::ForEachBond) {
        NanScope();

        Atom *obj = Unwrap(args.This());
        Local<Function> cb = args[0].As<Function>();

        FOR_BONDS_OF_ATOM (bond, obj->ob) {
            const unsigned argc = 1;

            Local<Value> argv[argc] = { Bond::NewInstance(&*bond) };
            NanMakeCallback(NanGetCurrentContext()->Global(), cb, argc, argv);
        }

        NanReturnUndefined();
    }

    NAN_METHOD(Atom::ForEachNeighbour) {
        NanScope();

        Atom *obj = Unwrap(args.This());
        Local<Function> cb = args[0].As<Function>();

        FOR_NBORS_OF_ATOM (atom, obj->ob) {
            const unsigned argc = 1;
            Local<Value> argv[argc] = { Atom::NewInstance(&*atom) };
            NanMakeCallback(NanGetCurrentContext()->Global(), cb, argc, argv);
        }

        NanReturnUndefined();
    }

    NAN_GETTER(Atom::GetX) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetX()));
    }

    NAN_SETTER(Atom::SetX) {
        NanScope();

        if(value->IsNumber()) {
            Atom *obj = Unwrap(args.This());
            const double v = value->NumberValue();
            obj->ob->SetVector(v, obj->ob->y(), obj->ob->z());
        }
    }

    NAN_GETTER(Atom::GetY) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetY()));
    }

    NAN_SETTER(Atom::SetY) {
        NanScope();

        if(value->IsNumber()) {
            Atom *obj = Unwrap(args.This());
            const double v = value->NumberValue();
            obj->ob->SetVector(obj->ob->x(), v, obj->ob->z());
        }
    }

    NAN_GETTER(Atom::GetZ) {
        NanScope();

        Atom *obj = Unwrap(args.This());

        NanReturnValue(NanNew(obj->ob->GetZ()));
    }

    NAN_SETTER(Atom::SetZ) {
        NanScope();

        if(value->IsNumber()) {
            Atom *obj = Unwrap(args.This());
            const double v = value->NumberValue();
            obj->ob->SetVector(obj->ob->x(), obj->ob->y(), v);
        }
    }
}