//
// Created by kxe on 02.11.24.
//

#include <box/builder.hpp>
#include <vector>

#include <box/print.hpp>
#include <gtest/gtest.h>
#include <box/iterator/iterator.hpp>
#include <box/iterator/detect.hpp>


using BX = stepworks::bxa::box<int, std::vector> ;
using BX_T = typename stepworks::bxa::box<int, std::vector>::type ;
using BXA_T = typename stepworks::bxa::box<int, std::vector>::agg_t ;
using BXB = stepworks::bxa::builder<int, std::vector>;


/*
 #include <box/builder.hpp>
#include <vector>
#include <box/trace.hpp>

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


 * */


struct walker_test{
    int _sum=0;
    std::size_t sz=0;
    bool operator()(const int& a){
        return true;
    }
    bool operator()( BX_T& a){
        int x = a.index();
        if (!x){
            int k = std::get<0>(a);
            _sum+=k;
        }
        else{
            const BXA_T & bxa=std::get<1>(a);
            sz = bxa.size();
        }
        return true;
    }

    bool operator()( const BX_T* a){
        if (!a)
            return false;
        int x = a->index();
        if (!x){
            int k = std::get<0>(*a);
            std::cout << "walk(1): "<< k<< "("<<_sum<<")\n";
            _sum+=k;
        }
        else{
            const BXA_T & bxa=std::get<1>(*a);
            sz = bxa.size();
            std::cout << "walk(2): "<< sz<<"\n";
        }
        return true;
    }

    bool operator()(const BX_T& a, int level){

        return true;
    }
};


TEST(boxhiter_test, walk_lin){

    using stepworks::bxa::iter::cfwlx::iterator;
    using stepworks::bxa::iter::cfwlx::mk_iterator;

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
    auto resbx = bxb.deliver();

//    trace_box (resbx);

//    std::cout << " -----steptest--------\n ";
//    int i = 0;
//    const stepworks::bxa::box<int, std::vector> * ptr= nullptr;
    const auto& rb= std::get<1>(resbx);
    auto iter = mk_iterator<int, std::vector>(rb);

    static_assert( stepworks::bxa::iter::is_iterator<decltype(iter) >::value );

    walker_test wt;
    stepworks::bxa::iter::o_atom_f<int, std::vector> of{  wt};
    iter.apply(of );

}


TEST(boxhiter_test, walk_hier){

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
    auto resbx = bxb.deliver();

//    trace_box (resbx);

//    std::cout << " -----steptest--------\n ";
//    int i = 0;
//    const stepworks::bxa::box<int, std::vector> * ptr= nullptr;
    const auto& rb= std::get<1>(resbx);
    auto iter = mk_iterator<int, std::vector>(rb);

    static_assert( stepworks::bxa::iter::is_iterator<decltype(iter) >::value );

    walker_test wt;
    stepworks::bxa::iter::o_atom_f<int, std::vector> of{  wt};
    iter.apply(of );

}