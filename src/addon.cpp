#include <nan.h>
#include "conversion.h"
#include "mol.h"
#include "atom.h"
#include "forcefield.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    exports->Set(NanNew("hello"), NanNew("Hello World"));

    OBBinding::Conversion::Init(exports);
    OBBinding::Mol::Init(exports);
    OBBinding::Atom::Init(exports);
    OBBinding::ForceField::Init(exports);
}

NODE_MODULE(openbabel, InitAll)