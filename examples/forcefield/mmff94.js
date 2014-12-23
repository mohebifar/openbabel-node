var ob = require('./../../index');

var conversion = new ob.Conversion();
var ff = ob.ForceField.findForceField('mmff94');

console.log('Calculation Energy for Cyclopentane');

var mol = conversion
    .setInFormat('smiles')
    .read('C1CCCC1');

ff.setup(mol);

console.log('Energy before conformers search: ', ff.energy);

ff.systematicRotorSearch(mol);

console.log('Energy after conformers search: ', ff.energy);
