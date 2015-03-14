[![NPM version](http://img.shields.io/npm/v/openbabel.svg?style=flat)](https://www.npmjs.org/package/openbabel) [![npm](https://img.shields.io/codacy/5720fd610c5345299f03eb7dd6fc6184.svg?style=flat)](https://www.codacy.com/public/netfars/openbabel-node) [![Travis build status](http://img.shields.io/travis/mohebifar/openbabel-node/master.svg?style=flat)](https://travis-ci.org/mohebifar/openbabel-node) [![Dependency Status](https://david-dm.org/mohebifar/openbabel-node.svg?style=flat)](https://david-dm.org/mohebifar/openbabel-node) [![npm](https://img.shields.io/npm/dm/openbabel.svg?style=flat)](https://www.npmjs.com/package/openbabel) [![npm](https://img.shields.io/npm/l/openbabel.svg?style=flat)](http://www.gnu.org/copyleft/gpl.html) [![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/mohebifar/openbabel-node?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

**Open Babel** Binding for Node.js

Open Babel is a chemical toolbox designed to speak the many languages of chemical data written in C++. Now you can use the Open Babel features in node.js !

<h1 id="contents">Contents</h1>

* [Contents](#contents)
* [Installation](#installation)
    * [Linux](#linux)
    * [OS X](#osx)
* [Usage](#usage)
    * [Conversion](#usage-conversion)
        * [Read chemical file formats](#usage-conversion-read-chemical-file-formats)
        * [Write chemical file formats](#usage-conversion-write-chemical-file-formats)
    * [ForceField](#usage-forcefield)
        * [Energy calculation](#usage-forcefield-energy-calculation)
        * [Conformers search](#usage-forcefield-conformers-search)
        * [Atom types](#atom-types)


<h1 id="installation">Installation</h1>

<h2 id="linux">Linux</h2>

First of all you should install `openbabel` with header files.

```bash
sudo apt-get install libopenbabel-dev
```

Then you can easily install this package using `npm`

```bash
npm install openbabel
```

<h2 id="linux">OS X</h2>

Install `openbabel` using `brew`

```bash
brew install open-babel
npm install openbabel
```

<h1 id="usage">Usage</h1>

Check the **[Documentation API](http://mohebifar.github.io/openbabel-node/api/)** for more details.

Use the `openbabel` module in your project.

```js
var ob = require('openbabel');
```

<h2 id="usage-conversion">Conversion</h2>

<h3 id="usage-conversion-read-chemical-file-formats">Read chemical file formats</h3>

Create an instance of `ob.Conversion` :

```js
var conversion = new ob.Conversion();
var mol = conversion.setInFormat('smiles').read('C1CCCC1');
console.log(mol.atomsCount);
```

And you can use `fs` to read chimcal data from files :

```js
var fs = require('fs');

var data = readFileSync('methane.smiles');
var conversion = new ob.Conversion();
var mol = conversion.setInFormat('smiles').read(data);
console.log(mol.atomsCount);
```

<h3 id="usage-conversion-write-chemical-file-formats">Write chemical file formats</h3>

Use an `ob.Conversion` instance :

```js
var str = conversion.setOutFormat('mol').write(mol);
console.log(str);
```

And also you can export it as a file :

```js
var str = conversion.setOutFormat('mol').write();
fs.writeFileSync('methane.mol', str);
```

<h2 id="usage-forcefield">ForceField</h2>

<h3 id="usage-forcefield-energy-calculation">Energy Calculation</h3>

Create an instance of `ob.Conversion` using The `ob.Conversion.findForceField` factory :

```js
var ff = ob.Conversion.findForceField('mmff94');
ff.setup(mol);
console.log(ff.energy);
```

<h3 id="usage-forcefield-conformers-search">Conformers search</h3>

Call one of `systematicRotorSearch`, `randomRotorSearch`, `weightedRotorSearch`. (Read more in [API](http://mohebifar.github.io/openbabel-node/api/))

```js
console.log(ff.energy); // Before getting conformer
ff.systematicRotorSearch();
console.log(ff.energy); // After getting conformer
```

<h3 id="atom-types">Atom types</h3>

You can get data which is set for an atom by calling `getData` method such as `FFAtomType`.

```js
ff.prepareAtomTypes();
console.log(mol.atoms[0].getData('FFAtomType'));
```
