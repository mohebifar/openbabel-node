/**
 * The Class for Molecules
 *
 * @class Molecule
 * @constructor
 */

/**
 * Check if the molecule is chiral
 *
 * @method isChiral
 * @return {Boolean} Returns the result
 */

/**
 * Check if the molecule contains no atom
 *
 * @method isEmpty
 * @return {Boolean} Returns the result
 */

/**
 * Add Hydrogens to the entire molecule to fill out implicit valence spots
 *
 * @method addHydrogens
 * @param {Boolean} [polarOnly=false] Whether to add Hydrogens only to polar atoms
 * @return {Boolean} Returns true on success
 */

/**
 * Delete Hydrogens from the molecule
 *
 * @param {Boolean} [polarOnly=false] Whether to delete Hydrogens only to polar atom
 * @method deleteHydrogens
 * @return {Boolean} Returns true on success
 */

/**
 * Executes a callback for each atom
 *
 * @method forEachAtom
 * @param {Function} callback The callback to call for each atom
 * @return {Molecule} Returns this
 * @example
 *     mol.forEachAtom(function(atom) {
 *         console.log(atom.atomicNumber);
 *     });
 */

/**
 * Executes a callback for each bond
 *
 * @method forEachBond
 * @param {Function} callback The callback to call for each bond
 * @return {Molecule} Returns this
 * @example
 *     mol.forEachBond(function(bond) {
 *         console.log(bond.getOrder());
 *     });
 */

/**
 * Creates a new atom and appends it to this molecule
 *
 * @method createAtom
 * @return {Atom} Returns the created Atom
 */

/**
 * Creates a new bond and appends it to this molecule
 *
 * @method createBond
 * @return {Bond} Returns the created bond
 */

/**
 * Adds the given atom to this molecule
 *
 * @method addAtom
 * @param {Atom} atom The Atom to be added to this molecule
 * @return {Boolean} Returns true on success
 */

/**
 * Deletes the given atom from this molecule
 *
 * @method deleteAtom
 * @param {Atom} atom The Atom to be deleted from this molecule
 * @return {Boolean} Returns true on success
 */

/**
 * Adds the given bond to this molecule
 *
 * @method addBond
 * @param {Bond} atom The Bond to be added to this molecule
 * @return {Boolean} Returns true on success
 */

/**
 * Deletes the given bond from this molecule
 *
 * @method deleteBond
 * @param {Bond} bond The Bond to be deleted from this molecule
 * @return {Boolean} Returns true on success
 */

/**
 * Get Torsion angle between 4 atoms of this molecule
 *
 * @method getTorsion
 * @param {Atom} atom1
 * @param {Atom} atom2
 * @param {Atom} atom3
 * @param {Atom} atom4
 * @return {Number} Returns the torsion angle
 */

/**
 * Get angle between 3 atoms of this molecule
 *
 * @method getAngle
 * @param {Atom} atom1
 * @param {Atom} atom2
 * @param {Atom} atom3
 * @return {Number} Returns the angle
 */

/**
 * Sets the pH. The pH affects on Hydrogens to be added to this molecule
 *
 * @method setPH
 * @param {Number} [pH=7.4]
 * @return {Boolean} Returns true on success
 */

/**
 * Checks if the molecule has 3D Coordinates
 *
 * @method has3D
 * @return {Boolean} Returns the result
 */

/**
 * Checks if the molecule has 2D Coordinates
 *
 * @method has2D
 * @return {Boolean} Returns the result
 */

/**
 * Checks if the there are any non-zero coordinates
 *
 * @method hasNonZeroCoords
 * @return {Boolean} Returns the result
 */

/**
 * Checks if aromatic perception has been performed
 *
 * @method hasAromaticPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if the smallest set of smallest rings (FindSSSR) has been performed
 *
 * @method hasSSSRPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if the largest set of smallest rings (FindLSSR) has been performed
 *
 * @method hasLSSRPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if ring atoms and bonds has been assigned
 *
 * @method hasRingAtomsAndBondsPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if atom types have been assigned
 *
 * @method hasAtomTypesPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if ring types have been assigned
 *
 * @method hasRingTypesPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if atom chirality have been assigned
 *
 * @method hasChiralityPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if atomic Gasteiger partial charges have been assigned
 *
 * @method hasPartialChargesPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if atomic hybridization has been assigned
 *
 * @method hasHybridizationPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if implicit hydrogen valence has been assigned
 *
 * @method hasImplicitValencePerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if aromaticity and Kekule forms has been assigned
 *
 * @method hasKekulePerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if ring "closure" bonds has been assigned
 *
 * @method hasClosureBondsPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if Biomolecule chains and residues have been assigned.
 *
 * @method hasChainsPerceived
 * @return {Boolean} Returns the result
 */

/**
 * Checks if Hydrogens have been added to the molecule
 *
 * @method hasHydrogensAdded
 * @return {Boolean} Returns the result
 */

/**
 * Checks if aromatic Nitrogens have been corrected
 *
 * @method hasAromaticCorrected
 * @deprecated
 * @return {Boolean} Returns the result
 */

/**
 * The Standard Molar Mass given bye IUPAC Atomic Masses (amu)
 *
 * @property molarMass
 * @type {Number}
 */

/**
 * The mass given by isotopes
 *
 * @property exactMass
 * @type {Number}
 */

/**
 * Count of atoms in this molecule
 *
 * @property atomsCount
 * @type {Number}
 */

/**
 * Count of bonds in this molecule
 *
 * @property bondsCount
 * @type {Number}
 */

/**
 * Count of heavy atoms in this molecule
 *
 * @property heavyAtomsCount
 * @type {Number}
 */

/**
 * Count of conformers for this molecule
 *
 * @property conformersCount
 * @type {Number}
 */

/**
 * The value of energy for this molecule
 *
 * @property enery
 * @type {Number}
 */

/**
 * Total chrage of this molecule
 *
 * @property totalCharge
 * @type {Number}
 */

/**
 * Get atoms by given index.
 * It's not iterable. Only can be accessed via given index.
 * Indexes start from 0.
 *
 * @property atoms
 * @type {Atom[]}
 * @example
 *     mol.atoms[1].atomicNumber
 */

/**
 * Get bonds by given index.
 * It's not iterable. Only can be accessed via given index.
 * Indexes start from 0.
 *
 * @property bonds
 * @type {Bond[]}
 * @example
 *     mol.bonds[0].order
 */