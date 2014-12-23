[![NPM version](http://img.shields.io/npm/v/openbabel.svg?style=flat)](https://www.npmjs.org/package/openbabel) [![npm](https://img.shields.io/codacy/5720fd610c5345299f03eb7dd6fc6184.svg?style=flat)](https://www.codacy.com/public/netfars/openbabel-node) [![Travis build status](http://img.shields.io/travis/mohebifar/openbabel-node/master.svg?style=flat)](https://travis-ci.org/mohebifar/openbabel-node) [![Dependency Status](https://david-dm.org/mohebifar/openbabel-node.svg?style=flat)](https://david-dm.org/mohebifar/openbabel-node) [![npm](https://img.shields.io/npm/dm/openbabel.svg?style=flat)](https://www.npmjs.com/package/openbabel) [![npm](https://img.shields.io/npm/l/openbabel.svg?style=flat)](http://www.gnu.org/copyleft/gpl.html)

**Open Babel** Binding for Node.js

Open Babel is a chemical toolbox designed to speak the many languages of chemical data written in C++. Now you can use the Open Babel features in node.js !

<h1 id="contents">Contents</h1>

* [Contents](#contents)
* [Installation](#installation)
    * [Linux / Mac OSX](#installation-linux-mac-osx)
    * [Windows](#installation-windows)
* [Usage](#usage)
    * [Conversion](#usage-conversion)
        * [Read chemical file formats](#usage-conversion-read-chemical-file-formats)
        * [Write chemical file formats](#usage-conversion-write-chemical-file-formats)
    * [ForceField](#usage-forcefield)
        * [Energy Calculation](#usage-forcefield-energy-calculation)
        * [Conformers search](#usage-forcefield-conformers-search)


<h1 id="installation">Installation</h1>

<h2 id="installation-linux-mac-osx">Linux / Mac OSX</h2>

First of all you should install `openbabel` with header files.

    sudo apt-get install libopenbabel-dev

Then you can easily install this package using `npm`

    npm install openbabel
    
<h2 id="installation-windows">Windows</h2>

Not configured yet, will be considered soon.

<h1 id="usage">Usage</h1>

Check the **[Documentation API](http://mohebifar.github.io/openbabel-node/api/)** for more details.

Use the `openbabel` module in your project.

    var ob = require('openbabel');
    

<h2 id="usage-conversion">Conversion</h2>

<h3 id="usage-conversion-read-chemical-file-formats">Read chemical file formats</h3>

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
    
<h3 id="usage-conversion-write-chemical-file-formats">Write chemical file formats</h3>

Use an `ob.Conversion` instance :

    var str = conversion.setOutFormat('mol').write(mol);
    console.log(str);
    
And also you can export it as a file :

    var str = conversion.setOutFormat('mol').write();
    fs.writeFileSync('methane.mol', str);

<h2 id="usage-forcefield">ForceField</h2>

<h3 id="usage-forcefield-energy-calculation">Energy Calculation</h3>

Create an instance of `ob.Conversion` using The `ob.Conversion.findForceField` factory :

    var ff = ob.Conversion.findForceField();
    ff.setup(mol);
    console.log(ff.energy);
    
<h3 id="usage-forcefield-conformers-search">Conformers search</h3>

Call one of `systematicRotorSearch`, `randomRotorSearch`, `weightedRotorSearch`. (Read more in [API](http://mohebifar.github.io/openbabel-node/api/))

    console.log(ff.energy); // Before getting conformer
    ff.systematicRotorSearch();
    console.log(ff.energy); // After getting conformer
