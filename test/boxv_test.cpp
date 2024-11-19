//
// Created by karsten on 16.12.21.
//

#include <gtest/gtest.h>
#include <box/visit.hpp>
#include <box/box.hpp>
#include <box/util.hpp>
#include <box/impl.hpp>


using stepworks::bxa::box;

using T= int;
using BOX = box<T, std::vector>;
using  stepworks::bxa::box_type;
//using stepworks::bxa::visit_box_v;
using stepworks::bxa::visit_box;
using BOX_T = box_type<T, std::vector>;

using stepworks::bxa::from_ist;



namespace {

    auto fsum(const int& a,  int&& b){return a+std::move(b);};

    auto fsum_even(const int& a, int&& b){return a%2? std::move(b):  a+std::move(b);};
}

TEST (boxv_test, sum){
    BOX b0({11, BOX({2, 3, 40}), -14});

    auto x = visit_box
            <int,int, std::vector>
            ( fsum, b0._as_type() );
    EXPECT_EQ(x,42);

}


TEST (boxv_test, sum_even){
    BOX b0({11, BOX({2, 3, 40}), -14});

    auto x = visit_box
            <int,int,std::vector>
            ( fsum_even,b0._as_type());
    EXPECT_EQ(x,28);
}

TEST (boxv_test, iotest){
    BOX b0({11, BOX({2, 3, 40}), -14});
    std::ostringstream  ost;
    ost << b0;
    auto str0 =ost.str();
    BOX b1;
    std::istringstream ist( str0 );

    std::cout << "\ns(in)  \n"<<str0<< "\n--------------s(in)--------------\n";

    try {
        auto &res = from_ist<int,std::vector>(ist, b1);

        std::ostringstream ost1;
        ost1 << b1;
        std::cout << str0 << "\n------------------ost0 vs ost1---------------------\n:>" << ost1.str() << "\n--------";
        EXPECT_EQ(ost1.str(), str0);
    }
    catch (std::invalid_argument& x){

        std::cout << "\n========================exception: " << x.what();

    }

}