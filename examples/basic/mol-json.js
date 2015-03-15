var ob = require('./../../');

var molSrc = new ob.Molecule.fromJSON(
    {
        "atoms": [{
            "index": 0,
            "atomicNumber": 6,
            "symbol": "C",
            "position": {"x": -0.901249287903782, "y": 2.8253448625079267, "z": -0.7141889785518059}
        }, {
            "index": 1,
            "atomicNumber": 6,
            "symbol": "C",
            "position": {"x": -0.41917068312628847, "y": 1.4838641513835928, "z": -1.6973208579423815}
        }], "bonds": [{"begin": 0, "end": 1, "order": 1}]
    }
);

var molDst = JSON.stringify(molSrc);

console.log(molDst);