//
// Created by karsten on 17.08.22.
//

#include <gtest/gtest.h>
#include <util/bxtransform.hpp>
#include <box/print.hpp>

using stepworks::util::bxtrans::mk_text_list;
using stepworks::util::bxtrans::load_text_list;


TEST(bxtransform_test, impl){

    unsigned long long v = 0x99affe01;
    auto bret = mk_text_list<uint8_t >(v);
  //  stepworks::bxa::util::trace<uint8_t ,std::vector>(bret);

    trace_box(bret);

    unsigned long long x;
    int ret = load_text_list<uint8_t, unsigned long long >( x, std::get<1>(bret) );
    EXPECT_EQ(ret,0);
    EXPECT_EQ(x,v);
}

TEST(bxtransform_test, tupel_impl){
    auto v =std::make_tuple(1,"Hallo?");
    ///incomplete!
//    auto bret = mk_text_list<uint8_t >(v);

//    trace_box(bret);

}