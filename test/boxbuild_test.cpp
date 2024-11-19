//
// Created by karsten on 01.07.22.
//

#include <gtest/gtest.h>
#include <box/builder.hpp>
#include <vector>
#include <box/print.hpp>

using BX_T = stepworks::bxa::box<int,std::vector>;
using BXB = stepworks::bxa::builder<int, std::vector>;


TEST (boxbuild_test, impl){

   // BX_T abx;
    BXB bxb;

    bxb.add(42);
    bxb.add(11);
    bxb.open();
        bxb.add(69);
        bxb.add(11);
        bxb.open();
            bxb.add(-1);
            bxb.add(1);
        bxb.close();
       bxb.add(9);
    bxb.close();
    bxb.add(5);

    auto resbx = bxb.deliver();
    trace_box(resbx);


}