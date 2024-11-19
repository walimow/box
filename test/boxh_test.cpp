//
// Created by karsten on 10.04.23.
//
#include <box/box.hpp>
#include <gtest/gtest.h>
#include <box/boxh.hpp>
#include <map>

using stepworks::bxa::make::mk_box_v;
using stepworks::bxa::make::mk_box;

TEST(hbox_test, impl0){
    stepworks::bxa::hbox_t<int,std::vector,
    long long>  h0;
}



TEST(hbox_test, impl1){
    stepworks::bxa::hbox_t<int,std::vector,
            long long>  h0;


    h0._map[
            decltype(h0)::key_t
                    {
                            mk_box<int, std::vector>(42)
                    }
                            ]=100;
    h0._map[ mk_box_v<int,std::vector>({12,1,7}) ]=200;
    h0._map[mk_box_v<int,std::vector>({28
                                      , mk_box<int,std::vector>({1, 0,2 ,3})
                                       ,9})
                                       ]=300;
    h0._map[mk_box_v<int,std::vector>({31,7})]=400;
    //near:


}