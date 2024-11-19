//
// Created by kxe on 15.10.24.
//

#include <gtest/gtest.h>

#include <box/mkbox.hpp>
#include "box/iterator/iterator.hpp"

#include <box/builder.hpp>
#include <vector>
#include <box/trace_obsolete.hpp>

#include <box/print.hpp>

using BXA_T = typename stepworks::bxa::box<int, std::vector>::agg_t ;
using BXB = stepworks::bxa::builder<int, std::vector>;

TEST (boxstep_test, steptest_cfwhx) {

    using stepworks::bxa::iter::cfwhx::iterator;
    using stepworks::bxa::iter::cfwhx::mk_iterator;

    // BX_T abx;
    BXB bxb;
    bxb.open();
    bxb.add(1);
    bxb.add(2);
    bxb.close();
    bxb.open();
    bxb.add(3);
    bxb.add(4);
    bxb.close();
    bxb.open();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.close();
    bxb.open();
    bxb.add(7);
    bxb.add(8);
    bxb.close();

    int test=0;
    auto resbx = bxb.deliver();
    trace_box (resbx);

    std::cout << " -----steptest--------\n ";
    int i = 0;
    const stepworks::bxa::box<int, std::vector>::type * ptr= nullptr;


    const auto& rb= std::get<1>(resbx);
    auto iter = mk_iterator<int, std::vector>(rb);
  //  iter.step_a(0, false); // _eval_
    do {
        {
            if ( (ptr = iter._get_object_()) ) {
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " \nval: " << std::get<0>(*ptr) << " (" << i++ << ")\n";
                    auto k= std::get<0>(*ptr
);
                    std::cout<< "k: "<< k;
                    EXPECT_GT(k,test);
                    EXPECT_EQ(k,1+test);
                    test=k;
               //     iter.step_a();
                }
            }
            else{
                std::cout << "\n  ptr invalid ";
            }
        }
    } while (*iter != nullptr && i < 20);
}

TEST (boxstep_test, steptest_cfwh) {

    using stepworks::bxa::iter::cfwh::iterator;
    using stepworks::bxa::iter::cfwh::mk_iterator;


    // BX_T abx;
    BXB bxb;
    bxb.open();
    bxb.add(1);
    bxb.add(2);
    bxb.close();
    bxb.open();
    bxb.add(3);
    bxb.add(4);
    bxb.close();
    bxb.open();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.close();
    bxb.open();
    bxb.add(7);
    bxb.add(8);
    bxb.close();



    int test=0;



    auto resbx = bxb.deliver();

    trace_box (resbx);

    std::cout << " -----steptest--------\n ";
    int i = 0;
    const stepworks::bxa::box<int, std::vector>::type * ptr= nullptr;
    const auto& rb= std::get<1>(resbx);
    auto iter = mk_iterator<int, std::vector>(rb);
  //  iter.step_a(0, false); // _eval_
    do {
        {
            if ( (ptr = iter._get_object_()) ) {
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " \nval: " << std::get<0>(*ptr) << " (" << i++ << ")\n";
                    auto k= std::get<0>(*ptr);
                    std::cout<< "k: "<< k;
                    EXPECT_GT(k,test);
                    EXPECT_EQ(k,1+test);
                    test=k;
          //          iter.step_a();
                }
            }
            else{
                std::cout << "\n  ptr invalid ";
            }
        }
    } while (*iter != nullptr && i < 20);
}

TEST (boxstep_test, steptest_cfwl) {

    using stepworks::bxa::iter::cfwl::iterator;
    using stepworks::bxa::iter::cfwl::mk_iterator;


    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);
    bxb.open();
    bxb.add(-1);
    bxb.add(-2);
    bxb.close();
    bxb.add(3);
    bxb.add(4);
    bxb.open();
    bxb.add(-3);
    bxb.add(-4);
    bxb.close();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.open();
    bxb.add(-5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(-6);
    bxb.close();
    bxb.add(7);
    bxb.add(8);
    bxb.open();
    bxb.add(-7);
    bxb.add(-8);
    bxb.close();

    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    std::cout << " -----steptest--------\n ";
    int i = 0;
    const typename stepworks::bxa::box<int, std::vector>::type * ptr= nullptr;
    const auto& rb= std::get<1>(resbx);
    auto iter = mk_iterator<int, std::vector>(rb);
    iter.step_a(0, false); // _eval_
 //   bool btest=false;
 int sum=0;
    do {

            if (  (ptr = *iter)
            ) {
                iter++;
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " \nval: " << std::get<0>(*ptr) << " (" << i++ << ")\n";
                    auto k= std::get<0>(*ptr);
                    std::cout<< "k: "<< k;
                    EXPECT_GT(k,test);
                    test=k;
                    sum+=k;
               //     iter.step_a();
                }
            }
            else{
                std::cout << "\n  ptr invalid ";
                break;
            }

        //auto [_,valid_pos]=iter.step_a();

        //btest= valid_pos;
    } while ( ptr && i < 20);
    EXPECT_EQ(sum,36);
}


TEST (boxstep_test, steptest_cfwlx) {

    using stepworks::bxa::iter::cfwlx::iterator;
    using stepworks::bxa::iter::cfwlx::mk_iterator;


    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);
    bxb.open();
    bxb.add(-1);
    bxb.add(-2);
    bxb.close();
    bxb.add(3);
    bxb.add(4);
    bxb.open();
    bxb.add(-3);
    bxb.add(-4);
    bxb.close();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.open();
    bxb.add(-5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(-6);
    bxb.close();
    bxb.add(7);
    bxb.add(8);
    bxb.open();
    bxb.add(-7);
    bxb.add(-8);
    bxb.close();

    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    std::cout << " -----steptest--------\n ";
    int i = 0;
    const typename stepworks::bxa::box<int, std::vector>::type * ptr= nullptr;
    const auto& rb= std::get<1>(resbx);
    auto iter = mk_iterator<int, std::vector>(rb, stepworks::bxa::iter::it_atom);
    iter.step_a(0, false); // _eval_
    do {
        {
            if ( (ptr = iter._get_object_()) ) {
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " \nval: " << std::get<0>(*ptr) << " (" << i++ << ")\n";
                    auto k= std::get<0>(*ptr);
                    std::cout<< "k: "<< k;
                    EXPECT_GT(k,test);
                    test=k;
                    //       iter.step_a();
                }
            }
            else{
                std::cout << "\n  ptr invalid ";
            }
        }
    } while (*iter != nullptr && i < 20);
}

TEST (boxstep_test, test_crx ) {
    using stepworks::bxa::iter::crx::iterator;
    using stepworks::bxa::iter::crx::mk_iterator;

    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);

    bxb.add(3);
    bxb.add(4);

    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);

    bxb.add(7);
    bxb.add(8);

    bxb.add(9);
    bxb.add(10);

    bxb.add(11);
    bxb.add(12);

    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    auto it= mk_iterator<int, std::vector>( std::get<BXA_T> (resbx));
    {
        EXPECT_EQ(it._it, 0);
        const auto *o = it._object_(it._it);
        ASSERT_TRUE(o);
        EXPECT_EQ(std::get<0>(*o), 1);
    }
    {
        auto dist = it.count_of(2);
        if (dist) {
            it.move_position(*dist);

            const auto *o = *it;
            ASSERT_TRUE(o);
            EXPECT_EQ(std::get<0>(*o), 3);
        }
        else
            EXPECT_TRUE(false);
    }

}


TEST (boxstep_test, test_cr ) {
    using stepworks::bxa::iter::cr::iterator;
    using stepworks::bxa::iter::cr::mk_iterator;

    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);

    bxb.add(3);
    bxb.add(4);

    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);

    bxb.add(7);
    bxb.add(8);

    bxb.add(9);
    bxb.add(10);

    bxb.add(11);
    bxb.add(12);

    int k=0;
    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    auto it= mk_iterator<int, std::vector>( std::get<BXA_T> (resbx));
    EXPECT_EQ(it._it, it._base.begin() );
    const auto* o= *it;
    ASSERT_TRUE(o);
    EXPECT_EQ( std::get<0>(*o), 1 );
    do {


    }while (o && test>0 && k<20);
}

TEST (boxstep_test, test_cr2 ) {
    using stepworks::bxa::iter::cr::iterator;
    using stepworks::bxa::iter::cr::mk_iterator;

    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);
    bxb.open();
    bxb.add(-3);
    bxb.add(-4);
    bxb.close();
    bxb.add(3);
    bxb.add(4);

    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);

    bxb.add(7);
    bxb.add(8);

    bxb.add(9);
    bxb.add(10);

    bxb.add(11);
    bxb.add(12);

    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    auto it= mk_iterator<int, std::vector>( std::get<BXA_T> (resbx), stepworks::bxa::iter::iteration_mode::it_atom);
    EXPECT_EQ(it._it, it._base.begin() );
    {
        const auto *o = *it;
        ASSERT_TRUE(o);
        EXPECT_EQ(std::get<0>(*o), 1);
    }

    //it.move_position(2);

}

TEST (boxstep_test, test_vr ) {
    using stepworks::bxa::iter::vr::iterator;
    using stepworks::bxa::iter::vr::mk_iterator;

    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);

    bxb.add(3);
    bxb.add(4);

    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);

    bxb.add(7);
    bxb.add(8);

    bxb.add(9);
    bxb.add(10);

    bxb.add(11);
    bxb.add(12);

    int k=0;
    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    auto it= mk_iterator<int, std::vector>( std::get<BXA_T> (resbx));
    EXPECT_EQ(it._it, it._base.begin() );
    const auto* o= *it;
    ASSERT_TRUE(o);
    EXPECT_EQ( std::get<0>(*o), 1 );
    do {


    }while (o && test>0 && k<20);

}


TEST (boxstep_test, test_vrx ) {
    using stepworks::bxa::iter::vrx::iterator;
    using stepworks::bxa::iter::vrx::mk_iterator;

    // BX_T abx;
    BXB bxb;
    bxb.add(1);
    bxb.add(2);

    bxb.add(3);
    bxb.add(4);

    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);

    bxb.add(7);
    bxb.add(8);

    bxb.add(9);
    bxb.add(10);

    bxb.add(11);
    bxb.add(12);

    int test=0;
    auto resbx = bxb.deliver();

    trace_box (resbx);

    auto it= mk_iterator<int, std::vector>( std::get<BXA_T> (resbx));
    {
     //   EXPECT_EQ(it._it, 0);
        const auto *o = *it;
        ASSERT_TRUE(o);
        EXPECT_EQ(std::get<0>(*o), 1);
    }
    {
        auto dist = it.count_of(2);
        if (dist) {
            it.move_position(*dist);

            const auto *o = *it;
            ASSERT_TRUE(o);
            EXPECT_EQ(std::get<0>(*o), 3);
        }
        else
            EXPECT_TRUE(false);
    }

}


TEST (boxstep_test, test_fwh ) {
    using stepworks::bxa::iter::vrx::iterator;
    using stepworks::bxa::iter::vrx::mk_iterator;
}

/*

TEST (boxstep_test, steptestsym) {

    // BX_T abx;
    BXB bxb;
    bxb.open();
    bxb.add(1);
    bxb.add(2);
    bxb.close();
    bxb.open();
    bxb.add(3);
    bxb.add(4);
    bxb.close();
    bxb.open();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.close();
    bxb.open();
    bxb.add(7);
    bxb.add(8);
    bxb.close();

    int test=0;

    auto resbx = bxb.deliver_at_least();
    stepworks::bxa::util::trace_form(resbx, " ", "\n");
    std::cout << " -----steptest--------\n ";
    int i = 0;
    const stepworks::bxa::box<int, std::vector> * ptr= nullptr;
    auto iter = mk_iterator<int, std::vector>(std::get<1>(resbx));
    iter.step_a(0, false); // _eval_
    do {
        {
            if ( (ptr = *iter) ) {
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " \nval: " << std::get<0>(*ptr) << " (" << i << ")\n";
                    auto k= std::get<0>(*ptr);
                    EXPECT_GT(k,test);
                    test=k;
                }
            }
            else{
                std::cout << "\n  ptr invalid ";
            }
            i++;
            {
                //can_next
                auto [level, ok] = iter.step_a();
                std::cout << "level: " << level << " sel: " << ok;
                if ( (ptr = *iter) ) {
                    auto x = ptr->index();
                    std::cout << " (POST) index: " << x;
                    if (!x) {
                        std::cout << " val: " << std::get<0>(*ptr) << " (" << i << ")\n";
                        auto k= std::get<0>(*ptr);
                        EXPECT_GT(k,test);
                        test=k;

                    }else{ ///
                        std::cout << " (POST) index(agg): " << x;
                    }
                }
            }
        }
    } while (*iter != nullptr && i < 20);
}



TEST (boxstep_test, steptestsym_x) {

    // BX_T abx;
    BXB bxb;
    bxb.open();
    bxb.add(1);
    bxb.add(2);
    bxb.close();
    bxb.open();
    bxb.add(3);
    bxb.add(4);
    bxb.close();
    bxb.open();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.close();
    bxb.open();
    bxb.add(7);
    bxb.add(8);
    bxb.close();

    int test=5;

    auto resbx = bxb.deliver_at_least();
    stepworks::bxa::util::trace_form(resbx, " ", "\n");
    std::cout << " -----steptest--------\n ";
    int i = 0;
    const stepworks::bxa::box<int, std::vector> * ptr= nullptr;
    auto iter = mk_iteratorx<int, std::vector>(std::get<1>(resbx));
    iter.step_a(0, false); // _eval_
    do {
        {
            if ( (ptr = *iter) ) {
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " \nval: " << std::get<0>(*ptr) << " (" << i << ")\n";
                    auto k= std::get<0>(*ptr);
                    EXPECT_GT(k,test);
                    test=k;
                } else
                    std::cout << "\n (a: ) : " << std::get<1>(*ptr)<<"\n";

            }
            else{
                std::cout << "\n  ptr invalid ";
            }
            i++;
            {
                //can_next
                auto [level, ok] = iter.step_a();
                std::cout << "level: " << level << " sel: " << ok;
                if ( (ptr = *iter) ) {
                    auto x = ptr->index();
                    std::cout << " (POST) index: " << x;
                    if (!x) {
                        std::cout << " val: " << std::get<0>(*ptr) << " (" << i << ")\n";
                        auto k= std::get<0>(*ptr);
                        EXPECT_GT(k,test);
                        test=k;

                    }else{ ///
                        std::cout << " (POST) index(agg): " << x;
                    }
                }
            }
        }
    } while (*iter != nullptr && i < 20);
}



TEST (boxstep_test, steptest_asym) {

    // BX_T abx;
    BXB bxb;

    bxb.add(1);
    bxb.add(2);
    bxb.open();
    bxb.add(3);
    bxb.add(4);
    bxb.open();
    bxb.add(5);    //bxb.open();bxb.close();  //empty agg
    bxb.add(6);
    bxb.close();
    bxb.add(7);
    bxb.close();
    bxb.add(8);
    int i = 0;

    auto resbx = bxb.deliver();
    stepworks::bxa::util::trace_form(resbx, " ", "\n");
    std::cout << " -----steptest--------\n ";
    const stepworks::bxa::box<int, std::vector> * ptr= nullptr;
    auto iter = mk_iterator<int, std::vector>(std::get<1>(resbx));
    std::cout<<" > " <<iter.eval()<< " \n"; // _eval_
    do {
        {
            if ( (ptr = *iter) ) {
                auto x = ptr->index();
                std::cout << "\n (PRE) index: " << x;
                if (!x) {
                    std::cout << " val: " << std::get<0>(*ptr) << " (" << i << ")\n";
                }
                else{
                    std::cout << "\n (a: ) : " << std::get<1>(*ptr)<<"\n";

                }
            }
            i++;
            {
                //can_next
                auto [level, ok] = iter.step_a();
                std::cout << "level: " << level << " sel: " << ok;
                if ( (ptr = *iter) ) {
                    auto x = ptr->index();
                    std::cout << " (POST) index: " << x;
                    if (!x) {
                        std::cout << " val: " << std::get<0>(*ptr) << " (" << i << ")\n";
                    }else{ ///
                        std::cout << " (POST) index(agg): " << x;
                    }
                }
            }
        }
    } while (*iter != nullptr && i < 20);
}
*/