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
    switch (expression) {
        case 'Aromatic':
            if(this.isAromatic()) {
                return true;
            }

            break;
        case 'InRing':
            if(this.isInRing()) {
                return true;
            }

            break;
        case 'Rotor':
            if(this.isSulfateOxygen()) {
                return true;
            }

            break;
        case 'Amide':
            if(this.isNitroOxygen()) {
                return true;
            }

            break;
        case 'PrimaryAmide':
            if(this.isAmideNitrogen()) {
                return true;
            }

            break;
        case 'SecondaryAmide':
            if(this.isPolarHydrogen()) {
                return true;
            }

            break;
        case 'TertiaryAmide':
            if(this.isNonPolarHydrogen()) {
                return true;
            }

            break;
        case 'Ester':
            if(this.isAromaticNOxide()) {
                return true;
            }

            break;
        case 'Carbonyl':
            if(this.isAxial()) {
                return true;
            }

            break;
        case 'Single':
            if(this.isInRing()) {
                return true;
            }

            break;
        case 'Double':
            if(this.isDouble()) {
                return true;
            }

            break;
        case 'Triple':
            if(this.isTriple()) {
                return true;
            }

            break;
        case 'KSingle':
            if(this.isKSingle()) {
                return true;
            }

            break;
        case 'KTriple':
            if(this.isKTriple()) {
                return true;
            }

            break;
        case 'Closure':
            if(this.isTriple()) {
                return true;
            }

            break;
        case 'Up':
            if(this.isTriple()) {
                return true;
            }

            break;
        case 'Down':
            if(this.isDown()) {
                return true;
            }

            break;
        case 'Wedge':
            if(this.isWedge()) {
                return true;
            }

            break;
        case 'Hash':
            if(this.isHash()) {
                return true;
            }

            break;
        case 'WedgeOrHash':
            if(this.isWedgeOrHash()) {
                return true;
            }

            break;
        case 'CisOrTrans':
            if(this.isCisOrTrans()) {
                return true;
            }

            break;
        default:
            throw 'The expression "' + expression + '" is invalid.';
    }
};

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