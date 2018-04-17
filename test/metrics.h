//
// Copyright 2013 Yangbin Lin and Bili Chen. All Rights Reserved.
//
// Author: yblin.xmu@qq.com (Yangbin Lin)
//
// To use this code, please cite the follow paper:
//
// Chen B, Zeng W, Lin Y, et al. A New Local Search-Based Multiobjective
// Optimization Algorithm[J]. IEEE Transactions on Evolutionary Computation,
// 2014, 19(1):1-1.
//

#ifndef TEST_METRICS_H_
#define TEST_METRICS_H_

#include <cfloat>

#include "codelibrary/util/array/array_2d.h"

#include "core/population.h"
#include "solver/util/non_dominated_sort.h"

namespace moo {

/// Metrics for population.
class Metrics {
public:

    /**
     * Get Non-dominated solutions from the final population.
     */
    static const Population GetNondominated(const Population& population){
        std::vector<Population> fronts;
        NonDominatedSort(population, &fronts);
        return fronts[0];
    }

    /**
     * Get GDPS metrics.
     */
    static double GDPS(const Population& population) {
        Population nondominated_solutions = GetNondominated(population);

        double gdps = 0.0;

        for (size_t j = 0; j < nondominated_solutions.size(); ++j){
            double t = 0.0;
            const Individual& ind = nondominated_solutions[j];
            for (unsigned int k = 1; k < ind.variables.size(); ++k){
                t += ind.variables[k] * ind.variables[k];
            }
            gdps += sqrt(t);
        }
        return gdps / nondominated_solutions.size();
    }

    /**
     * Get IGD metrics.
     */
    static double IGD(const Population& population,
                      const cl::Array2D<double>& pareto_fronts) {
        Population nondominated_solutions = GetNondominated(population);

        double igd = 0.0;

        for (int i = 0; i < pareto_fronts.rows(); ++i){
            double min_igd = DBL_MAX;
            for (size_t j = 0; j < nondominated_solutions.size(); ++j){
                const Individual& ind = nondominated_solutions[j];
                double temp = 0.0;
                for (int k = 0; k < pareto_fronts.columns(); ++k){
                    temp += (pareto_fronts(i,k) - ind.objectives[k]) *
                            (pareto_fronts(i,k) - ind.objectives[k]);
                }
                min_igd = std::min(min_igd, temp);
            }
            igd += std::sqrt(min_igd);
        }

        return igd / pareto_fronts.rows();
    }

    /**
     * Get GD metrics.
     */
    static double GD(const Population& population,
                     const cl::Array2D<double>& pareto_fronts) {
        Population nondominated_solutions = GetNondominated(population);
        double convergences = 0.0;
        for (size_t i = 0; i < nondominated_solutions.size(); ++i){
            double min_convergences = DBL_MAX;
            const Individual& ind = nondominated_solutions[i];
            for (int j = 0; j < pareto_fronts.rows(); ++j){
                double temp = 0.0;
                for (int k = 0; k < pareto_fronts.columns(); ++k){
                    temp += Sqr(pareto_fronts(j, k) - ind.objectives[k]);
                }
                temp = std::sqrt(temp);
                min_convergences = std::min(min_convergences, temp);
            }
            convergences += min_convergences * min_convergences;
        }
        return std::sqrt(convergences) / nondominated_solutions.size();
    }


    /**
     * Get convergences metrics.
     */
    static double Convergences(const Population& population,
                               const cl::Array2D<double>& pareto_fronts) {
        Population nondominated_solutions = GetNondominated(population);

        double convergences = 0.0;
        for (size_t i = 0; i < nondominated_solutions.size(); ++i){
            double min_convergences = DBL_MAX;
            const Individual& ind = nondominated_solutions[i];
            for (int j = 0; j < pareto_fronts.rows(); ++j){
                double temp = 0.0;
                for (int k = 0; k < pareto_fronts.columns(); ++k){
                    temp += Sqr(pareto_fronts(j, k) - ind.objectives[k]);
                }
                temp = std::sqrt(temp);
                min_convergences = std::min(min_convergences, temp);
            }
            convergences += min_convergences;
        }
        return convergences / nondominated_solutions.size();
    }

    /**
     * Get of Diversity metrics.
     */
    static double Diversity(const Population& population,
                            const cl::Array2D<double>& pareto_fronts) {
        Population nondominated_solutions = GetNondominated(population);

        int col = pareto_fronts.columns();
        int row = pareto_fronts.rows();
        cl::Array2D<double> extreme_solutions(col, col);

        for (int i = 0; i < col; ++i) {
            double min_i = DBL_MAX;
            int min_pos = 0;
            for (int j = 0; j < row; ++j) {
                if (pareto_fronts(j,i) < min_i) {
                    min_i = pareto_fronts(j,i);
                    min_pos = j;
                }
            }
            for (int k = 0; k < col; ++k) {
                extreme_solutions(i, k) = pareto_fronts(min_pos, k);
            }
        }
        int pop_size = nondominated_solutions.size();

        double sum1 = 0.0;
        double sum2 = 0.0;
        for (int i = 0; i < col; ++i) {
            double min_sum1_i = DBL_MAX;
            for (int j = 0; j < pop_size; ++j) {
                double temp = 0.0;
                for (int k = 0; k < col; ++k) {
                    temp += Sqr(extreme_solutions(i,k) -
                                nondominated_solutions[j].objectives[k]);
                }
                temp = std::sqrt(temp);
                if (temp < min_sum1_i && temp > 0.0)
                    min_sum1_i = temp;
            }
            sum1 += min_sum1_i;
        }

        double d = 0.0;
        for (int i = 0; i < pop_size; ++i) {
            double min_d_i = DBL_MAX;
            for (int j = 0; j < pop_size; ++j) {
                double temp = 0.0;
                for (int k = 0; k < col; ++k) {
                    temp += Sqr(nondominated_solutions[i].objectives[k] -
                                nondominated_solutions[j].objectives[k]);
                }
                temp = std::sqrt(temp);
                if (temp < min_d_i && i != j)
                    min_d_i = temp;
            }
            d += min_d_i;
        }
        d = d / pop_size;

        for (int i = 0; i < pop_size; ++i) {
            double min_d_i = DBL_MAX;
            for (int j = 0; j < pop_size; ++j) {
                double temp = 0.0;
                for (int k = 0; k < col; ++k) {
                    temp += Sqr(nondominated_solutions[i].objectives[k] -
                                nondominated_solutions[j].objectives[k]);
                }
                temp = std::sqrt(temp);
                if (temp < min_d_i && i != j)
                    min_d_i = temp;
            }
            sum2 += (min_d_i - d >= 0 ? (min_d_i - d) : (d - min_d_i));
        }

        double result = (sum1 + sum2) / (sum1 + (pop_size - col) * d);

        return result;
    }
};

} // namespace moo

#endif // TEST_METRICS_H_
