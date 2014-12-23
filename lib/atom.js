'use strict';

var ob = require('./../build/Release/openbabel');

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
 * @param {Atom} atom
 * @param {Number} distance
 * @return {Boolean} Returns the result
 */
ob.Atom.prototype.isConnectedWith = function (atom, distance) {

    if (distance === 1) {
        return this.isConnected(atom);
    } else {
        this.forEachNeighbour(function (neighbour) {
            if (neighbour.isConnectedWith(atom, distance - 1)) {
                return true;
            }
        });
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
    switch (expression) {
        case 'Hydrogen':
            if(this.atomicNumber === 1) {
                return true;
            }

            break;
        case 'Carbon':
            if(this.atomicNumber === 6) {
                return true;
            }

            break;
        case 'Nitrogen':
            if(this.atomicNumber === 7) {
                return true;
            }

            break;
        case 'Oxygen':
            if(this.atomicNumber === 8) {
                return true;
            }

            break;
        case 'Phosphorus':
            if(this.atomicNumber === 15) {
                return true;
            }

            break;
        case 'Sulfur':
            if(this.atomicNumber === 16) {
                return true;
            }

            break;
        case 'CarboxylOxygen':
            if(this.isCarboxylOxygen()) {
                return true;
            }

            break;
        case 'PhosphateOxygen':
            if(this.isPhosphateOxygen()) {
                return true;
            }

            break;
        case 'SulfateOxygen':
            if(this.isSulfateOxygen()) {
                return true;
            }

            break;
        case 'NitroOxygen':
            if(this.isNitroOxygen()) {
                return true;
            }

            break;
        case 'AmideNitrogen':
            if(this.isAmideNitrogen()) {
                return true;
            }

            break;
        case 'PolarHydrogen':
            if(this.isPolarHydrogen()) {
                return true;
            }

            break;
        case 'NonPolarHydrogen':
            if(this.isNonPolarHydrogen()) {
                return true;
            }

            break;
        case 'AromaticNOxide':
            if(this.isAromaticNOxide()) {
                return true;
            }

            break;
        case 'Axial':
            if(this.isAxial()) {
                return true;
            }

            break;
        case 'InRing':
            if(this.isInRing()) {
                return true;
            }

            break;
        default:
            throw 'The expression "' + expression + '" is invalid.';
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
 * Index of this atom in the molecule
 *
 * @property index
 * @type {Number}
 * @readonly
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