#include "gtest/gtest.h"
#include <string>
#include <box/boxm.hpp>
#include <exception>
//#include <map>
#include <box/selector.hpp>


using stepworks::bxm::boxm;

TEST (boxm_test_case, impl_m) {
    //   std::vector< boxm<std::string, std::string, std::map> > vgehtdas;
}


using stepworks::bxm::to_string;


using stepworks::bxm::mk_box;


using stepworks::bxm::mk_box_value;


TEST (boxm_test_case, impl_initializer_list) {

    try {
        std::cout << "mk_box(Ty a ) ==1\n";
        auto res1 = mk_box<std::string, std::string, std::map>({{"kk", "jl"}});

    }
    catch (const std::exception &x) {
        std::cout << "x--here1x<< \n" << x.what() << "\n";
    }

    std::cout << "mk_box(Ty a ) ==2\n";
    {
        //    auto x = mk_box<std::string, std::string, std::map>({"aaaa","hkjhkhkh"} );
    }
    std::cout << "xxxx-here1x<< \n" << "\n";
}


TEST (boxm_test_case, impl_initializer_list2) {

    boxm<std::string, std::string, std::map> bxm0({{"aaaa", "hkjhkhkh"},
                                                   {"aaab", "hkhkh"}});
//      auto x = mk_box<std::string, std::string, std::map>( {{"aaaa","hkjhkhkh"}, {"aaab","hkhkh"} } );

}


TEST (boxm_test_case, impl_initializer_list1) {
    std::cout << "\nTRY===============\n";

    boxm<std::string, std::string, std::map> bxm0({{"aaaa", "hkjhkhkh"},
                                                   {"aaab", "hkhkh"}});


    std::cout << "\nBOX(r) to_string([==2==]): " << to_string(bxm0, "[ ", "]\n", " : ");
    std::cout << "\n===============\n";
}



/*

TEST (boxm_test_case, impl_initializer_list2)
{
    auto res1 = mk_box<unsigned long , std::vector>(1);
    {
        using _B=stepworks::bx::box<unsigned long, std::vector>;

        _B x = mk_box<unsigned long , std::vector> ({ 1, _B{2,3},4 } );
    }
}

TEST (boxm_test_case, impl_initializer_list_per_value)
{
    auto m2 = box<unsigned long int, std::vector>{  mk_box_value<unsigned long int, std::vector>( {1,
                                                                                                   mk_box<unsigned long int, std::vector>({2,3})
                                                                                                          ,4} )};
    std::cout<< "\nBOX(per impl_initializer_list_per_value) to_string: "<< to_string(m2,"[ ","]\n"," : ");
}

using stepworks::bx::l2r::move_box;

TEST (boxm_test_case, move_box)
{
    std::cout<< "\n===============================================================================================\n";
    auto bx0 = mk_box<int, std::vector>( {1} );
    std::cout<< "\nBOX(r) to_string: "<< to_string(bx0);

    auto bx2 = move_box< int, std::vector,std::vector>( std::move( bx0 ));
    std::cout<< "\nBOX(rmoved) to_string: "<< to_string(bx2);

}
 */

TEST(boxm_test, sel_bx) {

    auto bm = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {1,  0},
                    {10, 10},
                    {11, 101}
            }

    );
    //auto& test =std::get<0>(bm._value);
    auto &agg = std::get<1>(bm._value());
    auto res = stepworks::bxa::sel_key(agg, 7, stepworks::util::gl);
    ASSERT_TRUE(res.first);
    EXPECT_EQ(res.first->_key, 10);
};

using stepworks::bxa::sel_list_type;

//std::function<bool(const M &m, key_t, util::sel_mode, unsigned int)>;

TEST(boxm_test, sel_bx2egl_f) {

    //std::function<bool()> ffail

    auto bm = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {1,  0},
                    {10, 42},
                    {11, 101}
            }
    );

    auto bms = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {3,   30},
                    {30,  310},
                    {31,  bm._value()},
                    {301, 3101}
            }
    );

    auto sl = sel_list_type<decltype(bms)>::make_sel_list(
            {
                    {34},
                    sel_list_type<decltype(bms)>::key_entry(9, stepworks::util::eq)
            }
    );

    sel_list_type<decltype(bms)>::fail_f ff{[](const decltype(bms) &src,
                                               int k, stepworks::util::sel_mode sm, unsigned int level
    ) {
        std::cout << "\nfail: key: " << k << ", sm: " << (int) sm << ", level: " << level << "\n";
        return false;
    }};

    auto ret
            = sel_list_type<decltype(bms)>::select_t::select(std::get<1>(bms._value()), sl, ff, 0,
                                                             stepworks::util::egl);
    if (ret) {
        EXPECT_TRUE(false);
    }


};

TEST(boxm_test, sel_bx2egl_t) {

    auto bm = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {1,  0},
                    {10, 42},
                    {11, 101}
            }
    );

    auto bms = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {3,   30},
                    {30,  310},
                    {31,  bm._value()},
                    {301, 3101}
            }
    );

    auto sl = sel_list_type<decltype(bms)>::make_sel_list(
            {
                    {34},
                    sel_list_type<decltype(bms)>::key_entry(9, stepworks::util::gt)
            }
    );

    auto ret
            = sel_list_type<decltype(bms)>::select_t::select(std::get<1>(bms._value()), sl, nullptr, 0,
                                                             stepworks::util::egl);
    if (ret) {
        auto k = ret->_key;
        auto v = ret->_value._value();
        auto xx = ret->_value._value().index();
        auto x = ret->_value.index();
        ASSERT_TRUE(ret->_value._value().index() == 0);
        EXPECT_EQ(std::get<int>(ret->_value._value()), 42);
    } else
        EXPECT_TRUE(false);

    //detect
    static_assert(stepworks::detect::is_mbox<decltype(bms)>::value);
};

TEST(boxm_test, sel_bx2eg) {

    auto bm = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {1,  0},
                    {10, 42},
                    {11, 101}
            }
    );
    auto bms = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {3,   30},
                    {30,  310},
                    {31,  bm._value()},
                    {301, 3101}
            }
    );

    auto sl = sel_list_type<decltype(bms)>::make_sel_list({{31},
                                                           {10}});
    auto ret = sel_list_type<decltype(bms)>::select_t::select(std::get<1>(bms._value()), sl);
    if (ret) {
        auto k = ret->_key;
        auto v = ret->_value._value();
        auto xx = ret->_value._value().index();
        auto x = ret->_value.index();
        ASSERT_TRUE(ret->_value._value().index() == 0);
        EXPECT_EQ(std::get<int>(ret->_value._value()), 42);
    }
};

template<stepworks::detect::MapBox M>
auto test_m(const M &m) {
    return 1;
}


TEST(boxm_test, sel_bx_m_2eg) {

    auto bm = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {1,  0},
                    {10, 42},
                    {11, 101}
            }
    );
    auto bms = stepworks::bxm::mk_box<int, int, std::map>(
            {
                    {3,   30},
                    {30,  310},
                    {31,  bm._value()},
                    {301, 3101}
            }
    );

    auto sl = sel_list_type<decltype(bms)>::make_sel_list({{31},
                                                           {10}});
    int rc = test_m(bms);   // concept applicable?

    auto ret = stepworks::bxa::select_bx(bms, sl);

    if (ret) {
        auto k = ret->_key;

        ASSERT_TRUE(ret->_value.index() == 0);
        EXPECT_EQ(std::get<int>(ret->_value._value()), 42);
    }
};

///no map!

TEST(boxm_test, sel_bx_v) {

    using bx_t = stepworks::bxa::box<int,std::vector>;

    bx_t bx= stepworks::bxa::make::mk_box_v<int, std::vector>({
        11,
        stepworks::bxa::make::mk_box_v<int, std::vector>({221,222,223}),
        33,44,55,66
    } );

    auto sel =  stepworks::bxa::vsel_t{
          {1,{}}
        , { 2,{} }
    };

    const auto bbx =std::get<1>(bx);

    auto [res,pos] = stepworks::bxa::sel_ix(  bbx, sel );
    ASSERT_TRUE( res);
    EXPECT_EQ(*res, 223);

}


TEST(boxm_test, sel_bx_v_less) {

    using bx_t = stepworks::bxa::box<int,std::vector>;

    bx_t bx= stepworks::bxa::make::mk_box_v<int, std::vector>({
                                                                      11,
                                                                      stepworks::bxa::make::mk_box_v<int, std::vector>({221,222,223}),
                                                                      33,44,55,66
                                                              } );

    auto sel =  stepworks::bxa::vsel_t{
              {1,{}}
            , { 2,{stepworks::util::ls } }
    };

    const auto bbx =std::get<1>(bx);

    auto [res,pos] = stepworks::bxa::sel_ix(  bbx, sel );
    ASSERT_TRUE( res);
    EXPECT_EQ(*res, 222);

}