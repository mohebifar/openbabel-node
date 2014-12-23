var
    ob = require('../'),
    assert = require("assert");

describe('Conversion', function () {
    describe('#setInFormat', function () {
        it('smiles input format should be set', function (done) {
            var conversion = new ob.Conversion();

            conversion.setInFormat('smiles');
            done();
        });

        it('mol input format should be set', function (done) {
            var conversion = new ob.Conversion();

            conversion.setInFormat('mol');
            done();
        });

        it('cml input format should be set', function (done) {
            var conversion = new ob.Conversion();

            conversion.setInFormat('cml');
            done();
        });

        it('xyz input format should be set', function (done) {
            var conversion = new ob.Conversion();

            conversion.setInFormat('xyz');
            done();
        });
    });

    describe('#read', function () {
        it('should read a smiles for cyclohexane', function (done) {
            var conversion = new ob.Conversion();

            var mol = conversion.setInFormat('smiles').read('C1CCCCC1');
            assert.equal(mol.atomsCount, 6);
            done();
        });

        it('should read a smiles for benzene', function (done) {
            var conversion = new ob.Conversion();

            var mol = conversion.setInFormat('smiles').read('c1ccccc1');
            assert.equal(mol.atomsCount, 6);
            done();
        });
    });
});