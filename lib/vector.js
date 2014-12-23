'use strict';

var ob = require('./../build/Release/openbabel');

/**
 * The Class for Vector
 *
 * @class Vector
 * @constructor
 */
ob.Vector = function (atom) {
    this.atom = atom;
};

/**
 * The X dimension
 *
 * @property x
 * @type {Number}
 */
Object.defineProperty(ob.Vector.prototype, 'x', {
    set: function (x) {
        this.atom._x = x;
    },
    get: function () {
        return this.atom._x;
    }
});

/**
 * The Y dimension
 *
 * @property y
 * @type {Number}
 */
Object.defineProperty(ob.Vector.prototype, 'y', {
    set: function (y) {
        this.atom._y = y;
    },
    get: function () {
        return this.atom._y;
    }
});

/**
 * The Z dimension
 *
 * @property z
 * @type {Number}
 */
Object.defineProperty(ob.Vector.prototype, 'z', {
    set: function (z) {
        this.atom._z = z;
    },
    get: function () {
        return this.atom._z;
    }
});