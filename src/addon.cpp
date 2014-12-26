#include <nan.h>
#include "conversion.h"
#include "mol.h"
#include "atom.h"
#include "forcefield.h"
#include "builder.h"
#include "bond.h"
#include "data.h"

using namespace v8;
using namespace OpenBabel;

void InitLineSearchType(Handle<Object> exports);

void InitAll(Handle<Object> exports) {
    OBBinding::Conversion::Init(exports);
    OBBinding::Mol::Init(exports);
    OBBinding::Atom::Init(exports);
    OBBinding::ForceField::Init(exports);
    OBBinding::Builder::Init(exports);
    OBBinding::Bond::Init(exports);
    OBBinding::Data::Init(exports);

    InitLineSearchType(exports);
}

void InitLineSearchType(Handle<Object> exports) {
    Local<Object> LineSearchType = NanNew<Object>();

    LineSearchType->Set(NanNew("Newton2Num"), NanNew(OpenBabel::LineSearchType::Newton2Num));
    LineSearchType->Set(NanNew("Simple"), NanNew(OpenBabel::LineSearchType::Simple));

    exports->Set(NanNew("LineSearchType"), LineSearchType);
}

NODE_MODULE(openbabel, InitAll)