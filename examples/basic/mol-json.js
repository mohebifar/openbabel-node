var ob = require('./../../');

var mol = new ob.Conversion().setInFormat('smiles').read('CCCC');

var builder = new ob.Builder();
builder.build(mol);

console.log(JSON.stringify(mol));