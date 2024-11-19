//
// Created by kxe on 28.03.23.
//

#include <box/box.hpp>
#include <box/cmp.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <compare>



using stepworks::bxa::box;
//using stepworks::bxa::box_type;
using T = int;
using BOX = box<T, std::vector>;
//using BOX_T = box_type<T, std::vector>;

using stepworks::bxa::make::mk_box_v;
using stepworks::bxa::cmp_bx_num_ff;
using stepworks::bxa::_cmp_;
using stepworks::bxa::cmp_bx;

TEST (boxcmp_test, cmp_ee){

    {   ///box_test
        auto bx0 = box<int, std::vector>({1});
        auto bx1 = box<int, std::vector>(1);

        {
/*
            auto t = cmp_bx
                    //<int, std::vector<int>>
                    { bx0, bx1 }(); //.__cmp( bx1)>0;
            EXPECT_TRUE(t>0);
*/
        }

        auto t = _cmp_( bx0, bx1); //.__cmp( bx1)>0;
        EXPECT_TRUE(t>0);
    }

    {
        auto bx0 = box<int, std::vector>({1});
        auto bx1 = box<int, std::vector>(1);
        auto lsf=cmp_bx_num_ff<int, std::vector>(0, bx1);
        EXPECT_TRUE( lsf );

    }


}

