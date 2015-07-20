// Reaktoro is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <string>

// Reaktoro includes
#include <Reaktoro/Common/Index.hpp>
#include <Reaktoro/Common/Matrix.hpp>

namespace Reaktoro {

// Forward declarations
class ChemicalState;
class ChemicalSystem;

/// A class used to interface other codes with Reaktoro.
class Interface
{
public:
    /// Virtual destructor
    virtual ~Interface() = 0;

    /// Set the temperature and pressure of the interfaced code.
    /// This method should be used to update all thermodynamic properties
    /// that depend only on temperature and pressure, such as standard thermodynamic
    /// properties of the species.
    /// @param T The temperature (in units of K)
    /// @param P The pressure (in units of Pa)
    auto set(double T, double P) -> void = 0;

    /// Set the temperature, pressure and species composition of the interfaced code.
    /// This method should be used to update all thermodynamic properties
    /// that depend only on temperature and pressure, such as standard thermodynamic
    /// properties of the species, as well as chemical properties that depend on the
    /// composition of the species.
    /// @param T The temperature (in units of K)
    /// @param P The pressure (in units of Pa)
    /// @param n The composition of the species (in units of mol)
    auto set(double T, double P, const Vector& n) -> void = 0;

    /// Return the temperature (in units of K)
    auto temperature() const -> double = 0;

    /// Return the pressure (in units of Pa)
    auto pressure() const -> double = 0;

    /// Return the amount of a species (in units of mol)
    auto speciesAmount(Index ispecies) const -> double = 0;

    /// Return the number of elements
    auto numElements() const -> unsigned = 0;

    /// Return the number of species
    auto numSpecies() const -> unsigned = 0;

    /// Return the number of phases
    auto numPhases() const -> unsigned = 0;

    /// Return the number of species in a phase
    auto numSpeciesInPhase(Index iphase) const -> unsigned = 0;

    /// Return the name of an element
    auto elementName(Index ielement) const -> std::string = 0;

    /// Return the molar mass of an element (in units of kg/mol)
    auto elementMolarMass(Index ielement) const -> double = 0;

    /// Return the stoichiometry of an element in a species
    auto elementStoichiometry(Index ispecies, Index ielement) const -> double = 0;

    /// Return the name of a species
    auto speciesName(Index ispecies) const -> std::string = 0;

    /// Return the molar mass of a species (in units of kg/mol)
    auto speciesMolarMass(Index ispecies) const -> double = 0;

    /// Return the electrical charge of a species
    auto speciesCharge(Index ispecies) const -> double = 0;

    /// Return the name of a phase
    auto phaseName(Index iphase) const -> std::string = 0;

    /// Return the standard reference state of a phase (`"IdealGas"` or `"IdealSolution`)
    auto phaseReferenceState(Index iphase) const -> std::string = 0;

    /// Return the standard molar Gibbs free energy of a species (in units of J/mol)
    auto standardMolarGibbsEnergy(Index ispecies) const -> double = 0;

    /// Return the standard molar enthalpy of a species (in units of J/mol)
    auto standardMolarEnthalpy(Index ispecies) const -> double = 0;

    /// Return the standard molar volume of a species (in units of m3/mol)
    auto standardMolarVolume(Index ispecies) const -> double = 0;

    /// Return the standard molar isobaric heat capacity of a species (in units of J/(mol*K))
    auto standardMolarHeatCapacityConstP(Index ispecies) const -> double = 0;

    /// Return the standard molar isochoric heat capacity of a species (in units of J/(mol*K))
    auto standardMolarHeatCapacityConstV(Index ispecies) const -> double = 0;

    /// Return the ln activity coefficients of the species in a phase.
    auto lnActivityCoefficients(Index iphase) const -> Vector = 0;

    /// Return the ln activities of the species in a phase
    auto lnActivities(Index iphase) const -> Vector = 0;

    /// Return the molar volume of a phase
    auto phaseMolarVolume(Index iphase) const -> double = 0;

    /// Return the residual molar Gibbs energy of a phase
    auto phaseResidualMolarGibbsEnergy(Index iphase) const -> double = 0;

    /// Return the residual molar enthalpy of a phase
    auto phaseResidualMolarEnthalpy(Index iphase) const -> double = 0;

    /// Return the residual molar isobaric heat capacity of a phase
    auto phaseResidualMolarHeatCapacityConstP(Index iphase) const -> double = 0;

    /// Return the residual molar isochoric heat capacity of a phase
    auto phaseResidualMolarHeatCapacityConstV(Index iphase) const -> double = 0;

    /// Return the amounts of the species (in units of mol)
    auto speciesAmounts() const -> Vector;

    /// Return the amounts of the species in a given phase (in units of mol)
    auto speciesAmountsInPhase(Index iphase) const -> Vector;

    /// Return the formula matrix of the species
    auto formulaMatrix() const -> Matrix;

    /// Return the index of the first species in a phase
    auto indexFirstSpeciesInPhase(Index iphase) const -> Index;

    /// Convert the classes derived from Interface into a ChemicalSystem instance
    operator ChemicalSystem() const;

    /// Convert the classes derived from Interface into a ChemicalState instance
    operator ChemicalState() const;
};

} // namespace Reaktoro
