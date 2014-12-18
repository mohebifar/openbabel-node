var openbabel = require('./build/Release/openbabel');
var result = new openbabel.Conversion().setInFormat("smiles").read("C(N)(P)");


console.log(result.molWeight);
console.log(result.atomsCount);

console.log(result.energy);
console.log(result.isChiral());
console.log(result.addHydrogens());
console.log(result.atomsCount);