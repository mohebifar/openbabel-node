## ForceField

### Energy Calculation

Create an instance of `ob.Conversion` using The `ob.Conversion.findForceField` factory :

    var ff = ob.Conversion.findForceField();
    ff.setup(mol);
    console.log(ff.energy);
    
### Conformers search

Call one of `systematicRotorSearch`, `randomRotorSearch`, `weightedRotorSearch`. (Read more in [API](https://mohebifar.github.io/openbabel-node/api/))

    console.log(ff.energy); // Before getting conformer
    ff.systematicRotorSearch();
    console.log(ff.energy); // After getting conformer