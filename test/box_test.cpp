
#include "gtest/gtest.h"
#include <box/box.hpp>
#include <box/cmp.hpp>


//#include <util/boxm.hpp>
#include <map>
#include <list>
#include <detect/detect_box.hpp>
#include <box/cmp.hpp>
#include <compare>


using stepworks::bxa::box;
using stepworks::bxa::_cmp_;

TEST(box_test_case, detect_f) {
    auto f = stepworks::detect::is_box<int>::value;
    EXPECT_FALSE(f);
}

TEST(box_test_case, detect_t) {
    auto bx0 = box<int, std::vector>({1});

    auto t = stepworks::detect::is_box<decltype(bx0)>::value;
    EXPECT_TRUE(t);
}

TEST(box_test_case, mk_box_v_cmp_test) {
    auto bx0 = box<int, std::vector>({1});
    auto bx1 = box<int, std::vector>({});


    auto t = _cmp_(bx0 , bx1)>0;
    //   auto rr=stepworks::bxa::cmp_bx_num<int,std::vector>( bx0 , bx1);
    //  auto t =  rr>0;
    EXPECT_TRUE(t);
}

TEST(box_test_case, mk_box_v_cmp2_test) {
    {
        auto bx0 = box<int, std::vector>({1});
        auto bx1 = box<int, std::vector>(1);


        auto t = bx0._as_type() != bx1._as_type();
        EXPECT_TRUE(t);
    }

    {
        auto bx0 = box<int, std::vector>({1});
        auto bx1 = box<int, std::vector>(1);


        auto t = _cmp_( bx0 , bx1)>0;
        //  auto t = (rr >0);  //  ._as_type() > bx1._as_type();
        EXPECT_TRUE(t);
    }

    {
        auto bx0 = box<int, std::vector>({1});
        auto bx1 = box<int, std::vector>(2);

        auto t  = _cmp_( bx0,  bx1)>0; //.__cmp(bx1); bx0 > bx1; //.__cmp(bx1);
        //auto t = rr > 0; //bx1;
        EXPECT_TRUE(t);
    }

    {  ///even the empty list is greater then any atom value !
        auto bx0 = box<int, std::vector>({});
        auto bx1 = box<int, std::vector>(2);

        {
            auto t = _cmp_(bx0 , bx1)>0;
            EXPECT_FALSE(t);
        }
        {
            auto t = _cmp_( bx0 , bx1)>0;
         //   EXPECT_FALSE(t);
        }
    }


}
