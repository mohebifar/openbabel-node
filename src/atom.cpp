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

    Local <Object> Atom::NewInstance(OBAtom * atom) {
        NanEscapableScope();

        const unsigned argc = 0;
        Local <Value> argv[argc] = {};
        Local <Function> cons = NanNew<Function>(constructor);
        Local <Object> instance = cons->NewInstance(argc, argv);

        Atom *obj = ObjectWrap::Unwrap<Atom>(instance);
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
//    tpl->PrototypeTemplate()->SetAccessor(NanNew("molWeight"), GetMolWeight);

        NanAssignPersistent(constructor, tpl->GetFunction());
        exports->Set(NanNew("Atom"), tpl->GetFunction());
    }

    NAN_METHOD(Atom::New) {
            NanScope();

            Atom* obj = new Atom();
            obj->Wrap(args.This());

            NanReturnValue(args.This());
    }
}