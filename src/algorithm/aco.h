/*****************************************************************************
 *   Copyright (C) 2004-2013 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#ifndef PAGMO_ALGORITHM_ACO_H
#define PAGMO_ALGORITHM_ACO_H

#include "../config.h"
#include "../serialization.h"
#include "../population.h"
#include "../problem/tsp.h"
#include "base.h"

namespace pagmo { namespace algorithm {

/// Ant Colony Optimization (ACO) - Simple Ant System
/**
 * All ACO algorithms can be characterized by three parameters as follows: 
 * - Number of ants N > 0;
 * The ants are randomly initialized to a starting point in the graph.
 * Each ant, as it travels deposits pheromone proportionally to the length of
 * it's tour along the graph. Pheromone is deposited only if the ant has made
 * a valid tour. An ant must visit all cities, to complete a valid tour.
 * 
 * - Pheromone evaporation level P \in (0, 1)
 * As time passes, the pheromone on the least (longest) tours traveled
 * evaporates according to a pheromone evaporation constant.
 * 
 * - Number of cycles C > 0;
 * After all ants are initialized, the pheromone levels are updated and we have
 * a list of valid tours from the ants that have managed to complete a tour,
 * the shortest tour is remembered and the ants are re-initialized in different
 * starting points and the process is repeated.
 * 
 * This class is the Simple Ant System algorithm.
 * 
 * @author Florin Schimbinschi (florinsch@gmail.com)
 */
class __PAGMO_VISIBLE aco: public base
{
    public:
        aco(int cycle = 1, int ants = 100, double rho = 0.2);
        int get_cycle() const;
        int get_ants() const;
        double get_rho() const;
        base_ptr clone() const;
        void evolve(population &) const;
        std::string get_name() const;
        
    protected:
        std::string human_readable_extra() const;
        
        void make_tour_consistent(std::vector<size_t>&) const;
        
        std::vector<size_t> greedy_nn_trip(size_t, const std::vector<std::vector<double> >) const;
        
        std::vector<std::vector<double> > initialize_pheromone(size_t) const;
        std::vector<std::vector<double> > initialize_pheromone(size_t, double) const;
        std::vector<std::vector<double> > initialize_pheromone(size_t, const std::vector<std::vector<double> >) const;
//        void initialize_pheromone(int, const population&) const;
        
    private:
        static std::vector<bool> list2decision_vector(const std::vector<size_t>);
        
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive &ar, const unsigned int)
        {
                ar & boost::serialization::base_object<base>(*this);
                ar & m_cycle;
                ar & m_ants;
                ar & m_rho;
        }

        int m_cycle;
        int m_ants;
        double m_rho;
};

}} //namespaces

BOOST_CLASS_EXPORT_KEY(pagmo::algorithm::aco)

#endif // PAGMO_ALGORITHM_ACO_H