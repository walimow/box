//
// Created by karsten on 07.01.24.
//

#include <gtest/gtest.h>
#include <box/box.hpp>
#include <box/mkbox.hpp>
#include <box/append.hpp>

#include <box/util.hpp>
#include <box/trace_obsolete.hpp>


using stepworks::bxa::box;
using stepworks::bxa::box_type;
using T = int;
using BOX = box<T, std::vector>;
using BOX_T = box_type<T, std::vector>;

using stepworks::bxa::make::mk_box_v;
using stepworks::bxa::append_box;


TEST( boxappend_test, a2a){
    using stepworks::bxa::make::mk_box_v;
    auto v0= BOX( mk_box_v<int,std::vector>());

    EXPECT_EQ( BOX_T ::typex(v0),1);
    EXPECT_EQ( BOX_T ::count(v0),0);

    auto v1= BOX(mk_box_v<int,std::vector>(42));
    std::cout<<"append: ";
    trace_box(v1);
    std::cout<<"\n";


    auto aa= append_box<int,std::vector>(v1,1);
    EXPECT_EQ( BOX_T ::count(aa),2);

    trace_box(v1);



}
