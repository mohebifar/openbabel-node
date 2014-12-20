var start = Date.now();
var openbabel = require('./build/Release/openbabel');
var fs = require('fs');

console.log("Require", Date.now() - start);
var conversion = new openbabel.Conversion();

console.log("Create Conversion", Date.now() - start);
var mol = conversion.setInFormat('smiles').read("CC");

console.log("Result is", mol.molWeight);

var atoms1 = mol.getAtoms();

var ff = openbabel.ForceField.findForceField("mmff94");
console.log("Energy", ff.energy);
ff.setup(mol);
console.log("Energy", ff.energy);
ff.systematicRotorSearch(1);
console.log("Energy", ff.energy);
fs.writeFileSync('a.mol', conversion.setOutFormat('mol').write(mol));
console.log("Read", Date.now() - start);