//
// Created by kxe on 02.04.23.
//


#include <box/boxh.hpp>
#include <box/mkbox.hpp>
#include <box/algebra.hpp>
#include <box/trace_obsolete.hpp>
#include <box/cmp.hpp>

#include <gtest/gtest.h>
#include <vector>

using std::vector;
using stepworks::bxa::box;
//using stepworks::bxa::algebra;
using stepworks::bxa::make::mk_box_v;
using stepworks::bxa::to_string;
using stepworks::bxa::cmp_bx_num;



using stepworks::bxa::alg::num_z;
using numZ = stepworks::bxa::alg::num_z<int, std::vector>;


TEST(boxalgebra_numZ_test, addaa) {
    std::cout << "numZ  1+41";
    auto v41 = mk_box_v<int, vector>(41);


    auto res = numZ::addr(v41, 1);
    auto test = std::get<int>(v41);
    EXPECT_EQ(42, test);
}

TEST(boxalgebra_numZ_test, addaA) {
    std::cout << "numZ  {41,10} +1";
    auto v41 = mk_box_v<int, vector>({41, 10});

    std::cout << v41 << "   ->   ";

    auto res = numZ::addr(v41, 1);
    //auto  test = std::get<int>(v41);
    std::cout << "= v:a =  " << res;
}

TEST(boxalgebra_numZ_test, addAA) {
    std::cout << "numZ  {41,10} +{100,1}";
    auto v41 = mk_box_v<int, vector>({41, 10});

    std::cout << v41 << " ...  ->   ";

    auto res = numZ::addr(v41, mk_box_v<int, vector>({100, 1}));
    //auto  test = std::get<int>(v41);
    std::cout << "= v:v =  " << res;
}


TEST(boxalgebra_numZ_test, addAA2) {
    std::cout << "numZ  {41,10} +{100,1}";
    auto v41 = mk_box_v<int, vector>({41, 10, 1, 2, 3});

    std::cout << "\n trace_box (before):  ";
    trace_box(box<int, std::vector>{v41});
    std::cout << " \n______________________________________________________";

    std::cout << v41 << " ...  ->   ";

    auto res = numZ::addr(v41, mk_box_v<int, vector>({100, 1}));
    //auto  test = std::get<int>(v41);
    std::cout << "= v:v =  " << res;
    std::cout << "\n trace_box (after):  ";
    trace_box(box<int, std::vector>{res});
    std::cout << " \n______________________________________________________";

}


TEST(boxalgebra_numZ_test, add2aa) {
    std::cout << "numZ  1+41";
    auto v41 = mk_box_v<int, vector>(41);


    auto res = numZ::add2(v41, 1);
    auto test = std::get<int>(res);
    EXPECT_EQ(42, test);
}


TEST(boxalgebra_test, add2AaA) {

    std::cout << "numZ add2 {41,10} +1";
    auto v41 = mk_box_v<int, vector>({41, 10, mk_box_v<int, vector>({1, 3})});
    trace_box(box<int, std::vector>{41});

    std::cout << "numZ  {41,10} +{100,1}";
    auto v41b = mk_box_v<int, vector>({41, 10, 1, 2, 3});

    std::cout << "\n trace_box (before):  ";
    trace_box(box<int, std::vector>{v41});
    std::cout << " \n______________________________________________________";

    std::cout << v41 << " ...  ->   ";

    auto res = numZ::addr(v41, mk_box_v<int, vector>({0x100, 1}));
    //auto  test = std::get<int>(v41);
    std::cout << "= v:v =  " << res;
    std::cout << "\n trace_box (after):  ";
    trace_box(box<int, std::vector>{res});
    std::cout << " \n______________________________________________________";
}

TEST(boxalgebra_test, neg)
{
    {
        auto at42 = mk_box_v<int, vector>(42);
        auto minus = numZ::neg(at42);
        auto test = std::get<int>(minus);
        EXPECT_EQ(-42, test);
//        std::cout << " neg(-42?): ";
//        stepworks::bxa::util::trace_box<int, std::vector>(minus);
    }
    {
        auto v41 =   box<int, vector>{ mk_box_v<int, vector>({41, 10, mk_box_v<int, vector>({1, 3})})};
        trace_box<int, std::vector>(v41);
        auto minus = numZ::neg(v41);
        std::cout << " neg(-41, -10 {-1,-3})?: ";
        trace_box<int, std::vector>(minus);
        std::cout << " \nNeg_____________________________________________";
        auto minus1 = numZ::neg(minus);
        std::cout << " \nNNeg _____________________________________________";
        trace_box<int, std::vector>(minus1);
        std::cout << " \n_____________________________________________";

        auto minus2 = numZ::neg(minus1);
        std::cout << " \nNNeg2 _____________________________________________";
        trace_box<int, std::vector>(minus2);
        std::cout << " \n_____________________________________________";
        auto vcmp= cmp_bx_num<int, vector>(minus,minus2);
        EXPECT_EQ(vcmp,0);

        auto beq=v41== minus1;
        EXPECT_TRUE( beq);
    }
}


TEST(boxalgebra_test, sub_aA)
{
  //  auto v41 =   box<int, vector>{ mk_box_v<int, vector>({1, 10, mk_box_v<int, vector>({1, 3})})};
    auto res = numZ::sub2(53,  mk_box_v<int, vector>({0xa, 1}));
    auto test = std::get<int>(res);
    EXPECT_EQ(42, test);
}

TEST(boxalgebra_test, sub_Aa)
{
    //  auto v41 =   box<int, vector>{ mk_box_v<int, vector>({1, 10, mk_box_v<int, vector>({1, 3})})};
    auto res = numZ::sub2(  mk_box_v<int, vector>({53,0xa, 11}),11);
  //  auto test = std::get<int>(res);
  //  EXPECT_EQ(42, test);
    std::cout << " \nsub _____(42,-1,0)?________________________________________";
    trace_box<int, std::vector>(res);
    std::cout << " \n _____________________________________________";
}

TEST(boxalgebra_test, sub_aa)
{
    auto res = numZ::sub2(53,  11);
    auto test = std::get<int>(res);
    EXPECT_EQ(42, test);
}

TEST(boxalgebra_test, sub_AA0)
{
    auto l = mk_box_v<int, vector>({53, 0xa, 11});
    auto r = mk_box_v<int, vector>({11, -32, -31});
    auto res = numZ::sub2(l,r);
    std::cout << " \n subAA (0)_____(42,42,42)?________________________________________\n";
    trace_box<int, std::vector>(res);
    std::cout << " \n _____________________________________________ AA0\n";
}


TEST(boxalgebra_test, sub_AA)
{
    {
        auto l = mk_box_v<int, vector>({53, 0xa, 11});
        auto r = mk_box_v<int, vector>({11, -32, -31});
        auto res = numZ::sub2(l,r);
        std::cout << " \n subAA (0)_____(42,42,42)?________________________________________\n";
        trace_box<int, std::vector>(res);
        std::cout << " \n _____________________________________________ AA0\n";
    }
    {
        auto l = mk_box_v<int, vector>({53, 0xa, 11, 42});
        auto r = mk_box_v<int, vector>({11, -32, -31});
        auto res = numZ::sub2(l,r);
        std::cout << " \n subAA (1)_____(42,42,42,42)?________________________________________\n";
        trace_box<int, std::vector>(res);
        std::cout << " \n _____________________________________________ AA1\n";
    }

    {
        auto l = mk_box_v<int, vector>({53, 0xa, 11});
        auto r = mk_box_v<int, vector>({11, -32, -31,-42});
        auto res = numZ::sub2(l,r);
        std::cout << " \n subAA (2) _____(42,42,42,42)?________________________________________";
        trace_box<int, std::vector>(res);
        std::cout << " \n _____________________________________________ AA2\n";
    }
}