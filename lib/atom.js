'use strict';

var ob = require('./../build/Release/openbabel');

var elements = {
    Hydrogen: 1,
    Carbon: 6,
    Nitrogen: 7,
    Oxygen: 8,
    Phosphorus: 15,
    Sulfur: 16
};

/**
 * The Class for Atoms
 *
 * @class Atom
 * @constructor
 */

/**
 * Checks if this atom is connected to given atom
 *
 * @method isConnected
 * @param {Atom} atom The atom to be checked
 * @return {Boolean} Returns the result
 */

/**
 * Check if this atom is connected with another atom by given distance
 *
 * @method isConnectedWith
 * @param {Atom} atom The target atom
 * @param {Number} distance The distance between two atoms
 * @param {Atom} [exclude=null] The atom to be excluded from searching path
 * @return {Boolean} Returns the result
 */
ob.Atom.prototype.isConnectedWith = function (atom, distance, exclude) {

    if (distance === 1) {
        return atom.index !== this.index && this.isConnected(atom);
    } else {
        var result = false;
        var _this = this;

        this.forEachNeighbour(function (neighbour) {
            if(typeof exclude !== 'undefined' && neighbour.index === exclude.index) {
                return;
            }

            if (exclude !== neighbour && neighbour.isConnectedWith(atom, distance - 1, _this)) {
                result = true;
            }
        });

        return result;
    }

};

/**
 * Check if this atom is in one-three position with the given atom
 *
 * @method isOneThree
 * @param {Atom} atom
 * @return {Boolean} Returns the result
 */
ob.Atom.prototype.isOneThree = function (atom) {

    return this.isConnectedWith(atom, 2);

};

/**
 * Check if this atom is in one-four position with the given atom
 *
 * @method isOneFour
 * @param {Atom} atom
 * @return {Boolean} Returns the result
 */
ob.Atom.prototype.isOneFour = function (atom) {

    return this.isConnectedWith(atom, 4);

};

/**
 * Check if this atom matches with given expression
 *
 * @method is
 * @param {String} expression
 * @return {Boolean} Returns the result
 * @example
 *     atom.is('Hydrogen')
 *     atom.is('Carbon')
 *     atom.is('Nitrogen')
 *     atom.is('Oxygen')
 *     atom.is('Phosphorus')
 *     atom.is('Sulfur')
 *     atom.is('CarboxylOxygen')
 *     atom.is('PhosphateOxygen')
 *     atom.is('SulfateOxygen')
 *     atom.is('NitroOxygen')
 *     atom.is('AmideNitrogen')
 *     atom.is('PolarHydrogen')
 *     atom.is('NonPolarHydrogen')
 *     atom.is('AromaticNOxide')
 *     atom.is('Axial')
 *     atom.is('InRing')
 */
ob.Atom.prototype.is = function (expression) {
    if (typeof elements[expression] !== 'undefined') {
        return this.atomicNumber === elements[expression];
    } else if (ob.Atom.prototype.hasOwnProperty('is' + expression)) {
        return this['is' + expression]();
    } else {
        var error = 'The expression ' + expression + ' is invalid.';
        throw error;
    }
};

/**
 * Check if this atom has any bond with given order
 *
 * @method hasBondOfOrder
 * @param {Number} order
 * @return {Boolean} Returns the result
 */

/**
 * Returns count of Bonds with given order
 *
 * @method countBondsOfOrder
 * @param {Number} order
 * @return {Number} Returns count of bonds
 */

/**
 * Calls given callback for each bond
 *
 * @method forEachBond
 * @param {Function} callback The callback to be called for each bond
 * @return {Atom} Returns this
 * @example
 *     atom.forEachBond(function(bond) {
 *         console.log(atom.getOrder());
 *     });
 */

/**
 * Calls given callback for each neighbor of this atom
 *
 * @method forEachNeighbour
 * @param {Function} callback The callback to be called for each neighbour
 * @return {Atom} Returns this
 * @example
 *     atom.forEachNeighbour(function(atom) {
 *         console.log(atom.atomicNumber);
 *     });
 */

/**
 * Computes the distance between two atoms
 *
 * @method getDistance
 * @param {Atom} The atom to distance being compute with
 * @return {Number} Returns distance
 */

/**
 * Checks if given SMARTS matches with this atom
 *
 * @method matchesSMARTS
 * @param {String} smart The SMARTS expression
 * @return {Boolean} Returns the result
 */

/**
 * Return any data matching the given attribute name
 *
 * @method getData
 * @param {String} The attribute key
 * @return {Data} Returns the data object
 * @throws error if nothing matches
 */

/**
 * Index of this atom in the molecule
 *
 * @property index
 * @type {Number}
 */

/**
 * Atomic number of this atom
 *
 * @property atomicNumber
 * @type {Number}
 */

/**
 * Vector of coordinates for this atom
 *
 * @property vector
 * @type {Vector}
 */
Object.defineProperty(ob.Atom.prototype, 'vector', {
    get: function () {
        if (typeof this._vector === 'undefined') {
            this._vector = new ob.Vector(this);
        }

        return this._vector;
    }
});