var start = Date.now();
var openbabel = require('./index');
var fs = require('fs');

var conversion = new openbabel.Conversion();
var mol = conversion
    .setInFormat('smiles')
    .read('CN');

var b = new openbabel.Builder();
b.build(mol);

console.log(mol.atoms[0].index);

//
conversion.setOutFormat('mol');
//
var str = conversion.write(mol);
console.log(str);