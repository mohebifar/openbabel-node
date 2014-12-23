'use strict';

/**
 * The Class for Force Field
 *
 * @class ForceField
 * @constructor
 */

/**
 * Setup the forcefield for mol (assigns atom types, charges, etc.).
 * Keep current constraints.
 *
 * @method setup
 * @param {Molecule} mol The molecule to be set up
 * @return {Boolean} Returns the result
 */

/**
 * Generate conformers for the molecule
 * (systematicaly rotating torsions).
 *
 *  The initial starting structure here is important,
 *  this structure should be minimized for the best results.
 *  systematicRotorSearch works by rotating around the rotatable
 *  bond in a molecule. This rotating generates multiple conformers.
 *  The energy for all these conformers is then evaluated and the
 *  lowest energy conformer is selected.
 *
 * @method systematicRotorSearch
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {ForceField} Returns this
 */

/**
 * Generate conformers for the molecule by systematicaly rotating torsions.
 * To be used in combination with systematicRotorSearchNexConformer().
 *
 * @method systematicRotorSearchInitialize
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {Number} The number of conformers
 * @example
 *     ff.systematicRotorSearchInitialize(300);
 *     while (ff.systematicRotorSearchNextConformer(300)) {
 *       // do some updating (show last generated conformer, ...)
 *     }
 */

/**
 * Evaluate the next conformer.
 *
 * @method systematicRotorSearchNextConformer
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {Boolean} Returns true if there are more conformers
 */

/**
 * Generate conformers for the molecule (randomly rotating torsions).
 *
 * The initial starting structure here is important, this structure should be
 * minimized for the best results.
 * randomRotorSearch works by randomly rotating around the rotatable bonds in
 * a molecule.
 *
 * @method randomRotorSearch
 * @param {Number} conformers Number of random conformers to consider.
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {ForceField} Returns this
 */

/**
 * Generate conformers for the molecule by randomly rotating torsions.
 * To be used in combination with randomRotorSearchNexConformer().
 *
 * @method randomRotorSearchInitialize
 * @param {Number} conformers Number of random conformers to consider.
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {ForceField} Returns this
 * @example
 *     ff.randomRotorSearchInitialize(300);
 *     while (ff.randomRotorSearchNexConformer(300)) {
 *       // do some updating (show last generated conformer, ...)
 *     }
 */

/**
 * Evaluate the next conformer
 *
 * @method randomRotorSearchNextConformer
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {Boolean} Returns true if there are more conformers
 */

/**
 * Generate conformers for the molecule (randomly rotating torsions).
 *
 * @method weightedRotorSearch
 * @param {Number} conformers Number of random conformers to consider.
 * @param {Number} [steps=2500] Number of steps during geometry optimization.
 * @return {ForceField} Returns this
 */

/**
 * Generate conformers for the molecule (randomly rotating torsions).
 *
 * @method setLineSearchType
 * @param {Number} type The LineSearchType to be used.
 * @return {ForceField} Returns this
 * @example
 *     ff.setLineSearchType(ob.LineSearchType.Newton2Num)
 */

/**
 * Get the LineSearchType
 *
 * @method getLineSearchType
 * @return {Number} The current LineSearchType
 */

/**
 * Get the force atom types. The atom types will be added to the atoms data.
 *
 * @method prepareAtomTypes
 * @return {Boolean} Returns true on success
 */

/**
 * Get the force field formal charges. The formal charges will be added to
 * the atoms of mol as data.
 *
 * @method preparePartialCharges
 * @return {Boolean} Returns true on success
 */

/**
 * Get coordinates for current conformer and attach data to molecule.
 *
 * @method getCoordinates
 * @param {Molecule} mol
 * @return {Boolean} Returns true on success
 */

/**
 * Get coordinates for all conformers and attach data to molecule.
 *
 * @method getConformers
 * @param {Molecule} mol
 * @return {Boolean} Returns true on success
 */
