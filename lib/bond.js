'use strict';

var ob = require('./../build/Release/openbabel');

/**
 * The Class for Bonds
 *
 * @class Bond
 * @constructor
 */

/**
 * Get Begin Atom
 *
 * @method getBegin
 * @return {Atom} The Atom
 */

/**
 * Set Begin Atom
 *
 * @method setBegin
 * @return {Atom} Returns this
 */

/**
 * Get End Atom
 *
 * @method getEnd
 * @return {Atom} The Atom
 */

/**
 * Set End Atom
 *
 * @method setEnd
 * @return {Atom} Returns this
 */

/**
 * Set Length of this bond
 *
 * @method setLength
 * @param {Number} length
 * @return {Atom} Returns this
 */

/**
 * Get Length of this bond
 *
 * @method getLength
 * @return {Atom} Returns the length value
 */

/**
 * Set this bond's order
 *
 * @method setOrder
 * @return {Atom} Returns this
 */

/**
 * Get this bond's order
 *
 * @method getOrder
 * @return {Atom} Returns the length value
 */

/**
 * Get this bond's molecule parent
 *
 * @method getParent
 * @return {Molecule} Returns the pranet
 */

/**
 * Check if this bond matches with given expression
 *
 * @method is
 * @param {String} expression
 * @return {Boolean} Returns the result
 * @example
 *     bond.is('Aromatic')
 *     bond.is('InRing')
 *     bond.is('Rotor')
 *     bond.is('Amide')
 *     bond.is('PrimaryAmide')
 *     bond.is('SecondaryAmide')
 *     bond.is('TertiaryAmide')
 *     bond.is('Ester')
 *     bond.is('Carbonyl')
 *     bond.is('Single')
 *     bond.is('Double')
 *     bond.is('Triple')
 *     bond.is('KSingle')
 *     bond.is('KTriple')
 *     bond.is('Closure')
 *     bond.is('Up')
 *     bond.is('Down')
 *     bond.is('Wedge')
 *     bond.is('Hash')
 *     bond.is('WedgeOrHash')
 *     bond.is('CisOrTrans')
 */
ob.Bond.prototype.is = function (expression) {
    if (ob.Bond.prototype.hasOwnProperty('is' + expression)) {
        return this['is' + expression]();
    } else {
        var error = 'The expression ' + expression + ' is invalid.';
        throw error;
    }
};

/**
 * Return any data matching the given attribute name
 *
 * @method getData
 * @param {String} The attribute key
 * @return {Data} Returns the data object
 * @throws error if nothing matches
 */

/**
 * Order of this bond (1=single, 2=double, ..., 5= aromatic)
 *
 * @property order
 * @type {Number}
 * @example
 *     console.log(bond.order);
 *     bond.order = 1; // Single bond
 */
Object.defineProperty(ob.Bond.prototype, 'order', {
    get: function () {
        return this.getOrder();
    },
    set: function (order) {
        return this.setOrder(order);
    }
});

/**
 * Index of this bond
 *
 * @property index
 * @type {Number}
 * @example
 *     mol.forEachBond(function(bond) {
 *         console.log(bond.index);
 *     });
 *
 *     console.log(mol.bonds[0].index); // Prints 1
 */
Object.defineProperty(ob.Bond.prototype, 'index', {
    get: function () {
        return this.getOrder();
    },
    set: function (order) {
        return this.setOrder(order);
    }
});