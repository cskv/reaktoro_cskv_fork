// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright © 2014-2022 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#pragma once

// C++ includes
#include <type_traits>

// Reaktoro includes
#include <Reaktoro/Common/Types.hpp>
#include <Reaktoro/Core/Reaction.hpp>

namespace Reaktoro {

/// The function type for the generation of reactions with a given chemical system.
using ReactionGenerator = Fn<Vec<Reaction>(ChemicalSystem const&)>;

/// The class used to represent a collection of reactions controlled kinetically.
/// @ingroup Core
class Reactions
{
public:
    /// Construct a Reactions object.
    Reactions();

    /// Construct a Reactions object with given generic reactions.
    /// @param reaction_generators The ReactionGenerator objects that will be converted into Reaction objects.
    template<typename... ReactionGenerators>
    Reactions(const ReactionGenerators&... reaction_generators)
    {
        static_assert(sizeof...(reaction_generators) > 0);
        addAux(reaction_generators...);
    }

    /// Add a reaction generator into the Reactions container.
    template<typename T>
    auto add(T const& item) -> void
    {
        static_assert(std::is_convertible_v<T, ReactionGenerator> || std::is_convertible_v<T, Reaction>);

        if constexpr(std::is_convertible_v<T, ReactionGenerator>)
        {
            rgenerators.push_back([=](ChemicalSystem const& system) -> Vec<Reaction> {
                return item(system); // item is a ReactionGenerator object
            });
        }
        else
        {
            rgenerators.push_back([=](ChemicalSystem const& system) -> Vec<Reaction> {
                return { Reaction(item) }; // item is convertible to Reaction object
            });
        }
    }

    /// Convert this Reactions object into a vector of Reaction objects.
    /// @param system The intermediate chemical system without attached reactions in which the reactions take place.
    auto convert(ChemicalSystem const& system) const -> Vec<Reaction>;

private:
    /// The ReactionGenerator objects collected so far with each call to Reactions::add method.
    Vec<ReactionGenerator> rgenerators;

    /// Add one or more ReactionGenerator or Reaction objects into the Reactions container.
    template<typename Arg, typename... Args>
    auto addAux(const Arg& arg, const Args&... args) -> void
    {
        add(arg);
        if constexpr (sizeof...(Args) > 0)
            addAux(args...);
    }
};

} // namespace Reaktoro