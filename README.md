**Open Babel** Binding for Node.js

Open Babel is a chemical toolbox designed to speak the many languages of chemical data written in C++. Now you can use the OpenBabel features in node.js !

## Installation
First of all you should install `openbabel` with header files.

    sudo apt-get install libopenbabel-dev

Then you can easily install this package using `npm`

    npm install openbabel

## Usage

Use the `openbabel` module in your project.

    var ob = require('openbabel');

## Examples

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
