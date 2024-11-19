//
// Created by kh on 03.02.22.
//

#include <gtest/gtest.h>
#include <box/mkbox.hpp>
#include <box/trace_obsolete.hpp>
#include <vector>
#include <initializer_list>

using BXI = typename stepworks::bxa::box<int, std::vector> ;
using BXO = typename stepworks::bxa::box<unsigned long, std::vector>;

using stepworks::bxa::box;
//using stepworks::bxa::box_transform;
using stepworks::bxa::make::box_trans;
using stepworks::bxa::make::mk_box_v;
//using stepworks::bxa::util::trace;

TEST( boxtrans_test, impl ){
        BXI bx1  {1,2,3,4,5};
        BXI bxi2 {1,2,3,BXI{44,45,46},5};
}
/*
TEST( boxtrans_test, initlist2bx_ulvc0 ){
    BXI bx1 {1,2,3,4,5};
    BXO bxo;
    auto && bxov= std::move(bxo._value);

    const auto& bx1t=bx1._value;
  //  const auto & bx0v;
    auto ret
        = stepworks::bxa::box_transform
                < unsigned long, std::vector,
                int, std::vector>
                (
                bx1t
                , std::move(bxov)
                );
        std::cout<<"\n----->  ";
      trace_form<unsigned long,std::vector>(  ret, " ","\n " );
    std::cout<<"\t<~~~~~<<<  ";
    //BXI bxi2 {1,2,3,BXI{44,45,46},5};
}


TEST( boxtrans_test, initlist2bx_ulvc1 ){
    BXI bx1 {1,2,3,4,5};
    BXO bxo;
    auto && bxov= std::move(bxo._value);

    const auto& bx1t=bx1._value;
    auto ret
            = stepworks::bxa::box_transform
                    < unsigned long, std::vector,
                            int, std::vector>
                    (
                            bx1t
//                            , std::move(bxov)
                    );

    //BXI bxi2 {1,2,3,BXI{44,45,46},5};
}

*/
TEST( boxtrans_test, initlist2bx_ulvc1_s ){
    BXI bx1 {1,2,3,4,5};
    BXO bxo;
    auto && bxov= std::move(bxo._as_type());

    const auto& bx1t=bx1._as_type();
    auto ret
    = box_trans
            < unsigned long, std::vector,
            int, std::vector>
            ::apply
            (
                    bx1t
                                           , BXO{} // std::forward< typename BXO::type&& >(bxov)
                                                   );

    std::cout<< "\n---transfer---\n";
    trace_box<unsigned long, std::vector>(ret);

    //BXI bxi2 {1,2,3,BXI{44,45,46},5};
}