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

#ifndef TEST_TEST_FACTORY_H_
#define TEST_TEST_FACTORY_H_

#include "test/test_dtlz.h"
#include "test/test_fon.h"
#include "test/test_sch.h"
#include "test/test_kur.h"
#include "test/test_lz.h"
#include "test/test_uf.h"
#include "test/test_zdt.h"
#include "test/test_ctp.h"
#include "test/test_cf.h"


namespace moo {

/// Test Factory
class TestFactory {
public:
    static BasicTest* CreateTest(const std::string& name) {
        if (name == "SCH") {
            return new SCHTest();
        } else if (name == "FON") {
            return new FONTest();
        } else if (name == "KUR") {
            return new KURTest();
        } else if (name == "ZDT1") {
            return new ZDT1Test();
        } else if (name == "ZDT2") {
            return new ZDT2Test();
        } else if (name == "ZDT3") {
            return new ZDT3Test();
        } else if (name == "ZDT4") {
            return new ZDT4Test();
        } else if (name == "ZDT6") {
            return new ZDT6Test();
        } else if (name == "LZ1") {
            return new LZ1Test();
        } else if (name == "LZ2") {
            return new LZ2Test();
        } else if (name == "LZ3") {
            return new LZ3Test();
        } else if (name == "LZ4") {
            return new LZ4Test();
        } else if (name == "LZ5") {
            return new LZ5Test();
        } else if (name == "LZ6") {
            return new LZ6Test();
        } else if (name == "LZ7") {
            return new LZ7Test();
        } else if (name == "LZ8") {
            return new LZ8Test();
        } else if (name == "LZ9") {
            return new LZ9Test();
        } else if (name == "UF4") {
            return new UF4Test();
        } else if (name == "UF5") {
            return new UF5Test();
        } else if (name == "UF6") {
            return new UF6Test();
        } else if (name == "UF7") {
            return new UF7Test();
        } else if (name == "UF9") {
            return new UF9Test();
        } else if (name == "UF10") {
            return new UF10Test();
        }else if (name == "DTLZ1_3D") {
            return new DTLZ1_3DTest();
        } else if (name == "DTLZ2_3D") {
            return new DTLZ2_3DTest();
        } else if (name == "DTLZ3_3D") {
            return new DTLZ3_3DTest();
        } else if (name == "DTLZ4_3D") {
            return new DTLZ4_3DTest();
        } else if (name == "DTLZ5_3D") {
            return new DTLZ5_3DTest();
        } else if (name == "CTP1"){
            return new CTP1Test();
        } else if (name == "CF1") {
            return new CF1Test();
        } else if (name == "CF2") {
            return new CF2Test();
        } else if (name == "CF3") {
            return new CF3Test();
        } else if (name == "CF4") {
            return new CF4Test();
        } else if (name == "CF5") {
            return new CF5Test();
        } else {
            assert(false);
        }
        return NULL;
    }
};

} // namespace moo

#endif // TEST_TEST_FACTORY_H_
