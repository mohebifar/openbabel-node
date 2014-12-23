var ob = require('./../../index');

var conversion = new ob.Conversion();

// Read SMILES
var mol = conversion
    .setInFormat('smiles')
    .read('CCNCC');

// Write CML
var cml = conversion
    .setOutFormat('cml')
    .write(mol);

console.log(cml);