## Conversion

### Read chemical file formats

Create an instance of `ob.Conversion` :

    var conversion = new ob.Conversion();
    var mol = conversion.setInFormat('smiles').read('C1CCCC1');
    console.log(mol.atomsCount);
    
And you can use `fs` to read chimcal data from files :
    
    var fs = require('fs');
    
    var data = readFileSync('methane.smiles');
    var conversion = new ob.Conversion();
    var mol = conversion.setInFormat('smiles').read(data);
    console.log(mol.atomsCount);
    
### Write chemical file formats

Use an `ob.Conversion` instance :

    var str = conversion.setOutFormat('mol').write(mol);
    console.log(str);
    
And also you can export it as a file :

    var str = conversion.setOutFormat('mol').write();
    fs.writeFileSync('methane.mol', str);