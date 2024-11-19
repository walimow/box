//
// Created by kxe on 09.10.24.
//

#include <gtest/gtest.h>
#include <box/iterator/iterator.hpp>
#include <box/boxbuild.hpp>
#include <box/mkbox.hpp>
#include <box/predefined.hpp>
#include <box/print.hpp>
#include <vector>

using stepworks::bxa::iter::cfwl::iterator;
using stepworks::bxa::make::mk_box_v;
using stepworks::bxa::iter::cfwl::mk_iterator;
using stepworks::types::vint_box;

using stepworks::bxa::build::builder;
using stepworks::bxa::build::mk_builder;


TEST(bxiter_test, mkiter){

    auto  testv= mk_box_v<int,std::vector>({1,2, mk_box_v<int,std::vector>( {21,22}),3});
    auto test_it = mk_iterator<int, std::vector>(std::get<1>(testv));

}

TEST(bxiter_test, mkbuilder){
    auto  buildbx= mk_builder<int,std::vector>();
}

TEST(bxiter_test, add){

    auto  buildbx= mk_builder<int,std::vector>();
    buildbx.add_element(42);
    buildbx.add_element( mk_box_v<int,std::vector>({45,1,66}));
    auto b2 = stepworks::bxa::box<int, std::vector> (buildbx._base); // mk_box_v<int, std::vector>(buildbx._base);
  std::cout<<" build 42 / 45,1,66\n";
    trace_box( b2 );

}