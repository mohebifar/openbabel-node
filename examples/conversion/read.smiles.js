var ob = require('./../../index');

var conversion = new ob.Conversion();

var mol = conversion
    .setInFormat('smiles')
    .read('CCNCC');

console.log('The molecule contains ' + mol.atomsCount + ' atoms.');

mol.forEachAtom(function (atom) {
    console.log('Atom ' + atom.index + '\'s atomic number: ' + atom.atomicNumber);
});