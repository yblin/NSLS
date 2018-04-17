TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp

HEADERS += \
    solver/basic_solver.h \
    solver/solver_nsls.h \
    test/basic_test.h \
    test/test_zdt.h \
    solver/util/individual_util.h \
    solver/util/updater/nsls_updater.h \
    solver/util/initializer.h \
    solver/util/population_util.h \
    solver/util/selector.h \
    solver/util/updater.h \
    solver/util/selector/non_dominated_sorting_selector.h \
    codelibrary/visualization/plot.h \
    codelibrary/visualization/plot/plotter.h \
    codelibrary/visualization/plot/mix_plotter.h \
    codelibrary/visualization/plot/point_plotter.h \
    codelibrary/visualization/plot/line_plotter.h \
    codelibrary/visualization/plot/polygon_plotter.h \
    solver/util/selector/farthest_candidate.h \
    test/metrics.h \
    test/test_cf.h \
    test/test_ctp.h \
    test/test_dtlz.h \
    test/test_factory.h \
    test/test_fon.h \
    test/test_kur.h \
    test/test_lz.h \
    test/test_sch.h \
    test/test_uf.h
