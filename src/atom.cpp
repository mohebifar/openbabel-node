#include "atom.h"

using namespace v8;
using namespace OpenBabel;

namespace OBBinding {
    Persistent <Function> Atom::constructor;

    Atom::Atom() {

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

        // Prototype
        tpl->PrototypeTemplate()->SetAccessor(NanNew("atomicNumber"), GetAtomicNumber);

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Atom"), tpl->GetFunction());
    }

    NAN_METHOD(Atom::New) {
        NanScope();

        Atom *obj = new Atom();
        obj->Wrap(args.This());

        NanReturnValue(args.This());
    }

    NAN_GETTER(Atom::GetAtomicNumber) {
        NanScope();

        Atom *obj = Unwrap(args.This());
        NanReturnValue(NanNew(obj->ob->GetAtomicNum()));
    }

}