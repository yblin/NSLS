#include <iostream>
#include <memory>

#include "codelibrary/visualization/plot.h"
#include "codelibrary/visualization/terminal/svg_terminal.h"

#include "solver/solver_nsls.h"
#include "test/test_zdt.h"
#include "test/test_lz.h"

using namespace std;

int main() {
    std::unique_ptr<moo::BasicTest> test(new moo::LZ1Test());

    moo::Population population;
    moo::SolverNSLS<> solver;
    solver.Initialize(*(test.get()), 100, &population);
    for (int i = 0; i < 100; ++i) {
        solver.SingleStep(&population);
    }

    // Draw results.
    std::vector<cl::RPoint2D> points;
    for (const moo::Individual& ind : population) {
        points.emplace_back(ind.objectives[0], ind.objectives[1]);
    }

    cl::plot::PointPlotter plotter;
    plotter.set_title(test->name);
    plotter.Plot(points);

    cl::SVGTerminal terminal;
    plotter.Show(&terminal);

    terminal.SaveToFile("result.svg");
    system("result.svg");

    return 0;
}

