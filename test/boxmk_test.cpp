//
// Created by karsten on 25.11.20.
//
#include <gtest/gtest.h>
#include <box/def.hpp>
#include <box/box.hpp>
#include <box/util.hpp>
#include <box/mkbox.hpp>
#include <box/mkagg.hpp>
#include <box/cmp.hpp>
#include <vector>

#include <box/trace_obsolete.hpp>
#include <box/print.hpp>

using stepworks::bxa::box;
using stepworks::bxa::box_type;
using T = int;
using BOX = box<T, std::vector>;
using BOX_T = box_type<T, std::vector>;

using stepworks::bxa::make::mk_box_v;

//using stepworks::bxa::util::trace;
//using stepworks::bxa::util::trace_form;
//using stepworks::bxa::util::trace;


TEST (boxmake_test, test0) {

    auto r0 = mk_box_v<int, std::vector>(1);

    auto r1 = mk_box_v<int, std::vector>(41+1);

    int v =45;
    int z =v;
    EXPECT_EQ(v,z);

    auto r2 = mk_box_v<int, std::vector>( v );

     z =v;
    EXPECT_EQ(v,z);

}


//using  INL = stepworks::bxa::make::mk_aggregate;

TEST (boxmake_test, test_inl0) {
    auto v2= mk_box_v<int,std::vector>(BOX {42});
}


TEST (boxmake_test, test_inl) {

    using stepworks::bxa::make::mk_box_v;
    auto v0= mk_box_v<int,std::vector>();

    EXPECT_EQ( BOX_T ::typex(v0),1);
    EXPECT_EQ( BOX_T ::count(v0),0);

    auto v1= mk_box_v<int,std::vector>(42);

    EXPECT_EQ( BOX_T ::typex(v1),0);
    EXPECT_EQ( BOX_T ::count(v1),1);

    auto v2= mk_box_v<int,std::vector>(42);    ///will be interpreted as atom ! (?)
    EXPECT_EQ( BOX_T ::typex(v2),0);
    EXPECT_EQ( BOX_T ::count(v2),1);
    {
        auto v2= mk_box_v<int,std::vector>(BOX{42});    ///has to be explicit ...
        EXPECT_EQ( BOX_T ::typex(v2),1);
        EXPECT_EQ( BOX_T ::count(v2),1);
        //trace_box<int,std::vector>( std::get< typename BOX::agg_t>(v2)," < ", " > ");
        trace_box<int,std::vector>( std::get< typename BOX::agg_t>(v2));
    }

    auto v3= mk_box_v<int,std::vector>({42,666});
    EXPECT_EQ( BOX_T ::typex(v3),1);
    EXPECT_EQ( BOX_T ::count(v3),2);

}

//using stepworks::bxa::print::trace_box;

TEST (boxmake_test, test_inl2) {

    using stepworks::bxa::make::mk_box_v;
    auto v4= mk_box_v<int,std::vector>({42,1,666});

    ///BOX bb(v4);
    std::cout<< " (3?)--> " << BOX_T ::count(v4)<<"\n";
    //using stepworks::bxa::util::trace_box;
    trace_box<int,std::vector>( std::get< typename BOX::agg_t>(v4) );
}


TEST (boxmake_test, test_out_in_0) {

    using stepworks::bxa::make::mk_box_v;
    auto v4= mk_box_v<int,std::vector>({42,1,666});

    ///BOX bb(v4);

}


TEST (boxmake_test, test_out_in_2) {

///the problem:
    auto v4= mk_box_v< unsigned  int,std::vector>({(unsigned int) 42, (unsigned int)1,
                                                   (unsigned int)
                                                   666});

   // auto v5= typename box< int,std::vector>::type {42,666};

    ///BOX bb(v4);

}

using stepworks::bxa::_cmp_;

/////
TEST (boxmake_test, test_inl_cmp) {

    using stepworks::bxa::make::mk_box_v;
    auto v0= BOX( mk_box_v<int,std::vector>());

    EXPECT_EQ( BOX_T ::typex(v0),1);
    EXPECT_EQ( BOX_T ::count(v0),0);

    auto v1= BOX(mk_box_v<int,std::vector>(42));

    //auto cmv =

    auto rr=stepworks::bxa:: cmp_bx_num<int,std::vector>(v0,v1._as_type());
    bool b= rr < 0; //  v0<v1;

    ///TODO ...    auto bb= v0<=>v1;

    EXPECT_TRUE(b);   ///() < 42

    EXPECT_EQ( BOX_T ::typex(v1),0);
    EXPECT_EQ( BOX_T ::count(v1),1);

    auto v2= mk_box_v<int,std::vector>(42);    ///will be interpreted as atom ! (?)
    EXPECT_EQ( BOX_T ::typex(v2),0);
    EXPECT_EQ( BOX_T ::count(v2),1);
    {
        auto v2= mk_box_v<int,std::vector>(BOX{42});    ///has to be explicit ...
        EXPECT_EQ( BOX_T ::typex(v2),1);
        EXPECT_EQ( BOX_T ::count(v2),1);
        trace_box<int,std::vector>( std::get< typename BOX::agg_t>(v2)); //," < ", " > ");
    }

    auto v3= mk_box_v<int,std::vector>({42,666});

    bool b2=  _cmp_ ( BOX {v0} , {v3})<0; //.__cmp( v3)<0; // . _as_type()<v3;
    EXPECT_TRUE(b2);

    EXPECT_EQ( BOX_T ::typex(v3),1);
    EXPECT_EQ( BOX_T ::count(v3),2);

}

TEST (boxmake_test, test_ilist_transfer) {

    using stepworks::bxa::make::mk_box_v_init;
    auto res = mk_box_v_init<int, std::pmr::vector>({1,2,3});
    std::cout<< " test_ilist_transfer: ";
    trace_box<int,std::pmr::vector>(res);


}