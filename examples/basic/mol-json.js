var ob = require('./../../');

var mol = new ob.Conversion().setInFormat('smiles').read('CCCC');

var builder = new ob.Builder();
builder.build(mol);

var json = JSON.stringify(mol);
var object = JSON.parse(json);

var newMol = ob.Molecule.fromJSON(object);

console.log(newMol.atomsCount);