#include <nan.h>
#include "conversion.h"
#include "mol.h"
#include "atom.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    exports->Set(NanNew("hello"), NanNew("Hello World"));

    OBBinding::Conversion::Init(exports);
    OBBinding::Mol::Init(exports);
    OBBinding::Atom::Init(exports);
}

NODE_MODULE(openbabel, InitAll)