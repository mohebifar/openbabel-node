{"gitdown": "badge", "name": "npm-version"} {"gitdown": "badge", "name": "travis"} {"gitdown": "badge", "name": "david"}

**Open Babel** Binding for Node.js

Open Babel is a chemical toolbox designed to speak the many languages of chemical data written in C++. Now you can use the Open Babel features in node.js !

# Contents

{"gitdown": "contents", "maxDepth": 3}

# Installation

## Linux / Mac OSX

First of all you should install `openbabel` with header files.

    sudo apt-get install libopenbabel-dev

Then you can easily install this package using `npm`

    npm install openbabel
    
## Windows

Not configured yet, will be considered soon.

# Usage

Check the **[Documentation API](https://mohebifar.github.io/openbabel-node/api/)** for more details.

Use the `openbabel` module in your project.

    var ob = require('openbabel');
    

{"gitdown": "include", "file": ".gitdown/include/conversion.md"}

{"gitdown": "include", "file": ".gitdown/include/forcefield.md"}
