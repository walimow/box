//
// Created by karsten on 18.11.20.
//

#ifndef STEPWORKS_MKBOX_HPP
#define STEPWORKS_MKBOX_HPP

#include "box.hpp"
#include <memory_resource>

using stepworks::bxa::box;

namespace stepworks::bxa::make {


///the variant (elementary)

///empty
    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v() -> typename box<Ty, Aggregation>::type {
        return typename box<Ty, Aggregation>::type(
                typename box<Ty, Aggregation>::agg_t{}
        );
    }


    template<typename Ty, typename Allocation, template<typename...> typename Aggregation>
    auto mk_box_v(const Allocation &alloc) -> typename box<Ty, Aggregation>::type {
        return typename box<Ty, Aggregation>::type(
                typename box<Ty, Aggregation>::agg_t(alloc)
        );
    }

///base
/*
    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(Ty  a )->  typename box<Ty,Aggregation>::type {
        return  typename   box<Ty,Aggregation>::type ( a );
    }
*/
    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(Ty a) -> typename box<Ty, Aggregation>::type {
        return typename box<Ty, Aggregation>::type(std::forward<Ty>(a));
    }

    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(typename box<Ty, Aggregation>::type &&a) -> typename box<Ty, Aggregation>::type {
        return typename box<Ty, Aggregation>::type( std::move(a) );
    }

    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box(Ty a) -> typename box<Ty, Aggregation>::type {
        return  box<Ty, Aggregation>(std::forward<Ty>(a));
    }

    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box(typename box<Ty, Aggregation>::type &&a) -> typename box<Ty, Aggregation>::type {
        return  box<Ty, Aggregation>( std::move(a) );
    }

/*
    ///agg

    template <typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v( typename  box<Ty,Aggregation>::agg_t a )->  typename box<Ty,Aggregation>::type {
        return box<Ty,Aggregation> { std::forward<Ty>(a) };
    }
*/
///copy / move
    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box_v(box<Ty, Aggregation> &&a) -> typename box<Ty, Aggregation>::type {
        return typename box<Ty, Aggregation>::type{
                std::forward<typename box<Ty, Aggregation>::type>(a)
        };
    }

    template<typename Ty, template<typename...> typename Aggregation>
    auto mk_box(box<Ty, Aggregation> &&a) -> typename box<Ty, Aggregation>::type {
        return typename box<Ty, Aggregation>::type{
                std::forward< box<Ty, Aggregation>>(a)
        };
    }

///  initializer_list -> aggregate-> box
/*
    template<typename Base, template<typename...> typename Aggregation
    >
    auto mk_box_v(
            //const
            typename box<const Base, std::initializer_list>::agg_t &&il) -> box<Base, Aggregation> {
        return box<Base, Aggregation>(il);
    }
*/

    template<typename Base,
            template<typename...> typename Aggregation,
            typename Allocation
    >
    auto mk_box_va(
            const Allocation& alloc,
            typename box<  const Base, std::initializer_list>::agg_t
            il) -> box<Base, Aggregation> {
        return box<Base, Aggregation>(alloc, il);
    }

    template<typename Base, template<typename...> typename Aggregation
    >
    auto mk_box_v_init(
            //const
            std::initializer_list<Base> il, typename box<Base, Aggregation>::agg_t agg=typename box<Base, Aggregation>::agg_t{}) -> box<Base, Aggregation> {
        //typename box<Base, Aggregation>::agg_t agg;
        for (auto x: il)
            agg.push_back(mk_box_v<Base, Aggregation>(x));
        return box<Base, Aggregation>(agg);
    }


    template<typename Base, template<typename...> typename Aggregation
    >
    auto mk_box_v_init(
            //const
            std::initializer_list<typename box<Base, Aggregation>::type> il,
            typename box<Base, Aggregation>::agg_t agg=typename box<Base, Aggregation>::agg_t{}) -> box<Base, Aggregation>
    {

        for (auto x: il)
            agg.push_back(mk_box_v<Base, Aggregation>(x));
        return box<Base, Aggregation>(agg);
    }

    template<typename Base, template<typename...> typename Aggregation
    >
    auto mk_box_v_init(
            //const
            std::initializer_list<typename box<Base, Aggregation>::type> il, typename box<Base, Aggregation>::agg_t&& agg) -> box<Base, Aggregation>
//            typename box<Base,std::initializer_list>::type    il   )->box<Base,Aggregation>
    {
        for (auto x: il)
            agg.push_back(mk_box_v<Base, Aggregation>(x));
        return box<Base, Aggregation>(agg);
    }

    template<typename Base, template<typename...> typename Aggregation,
    template<typename...> typename AggregationS,
    typename Bs=Base

    >
    auto mk_box_v(
            const
            AggregationS<Bs>& il) -> box<Base, Aggregation>
    {
        typename box<Base, Aggregation>::agg_t agg;
        for (auto x: il)
            agg.push_back(mk_box_v<Base, Aggregation>(x));
        return box<Base, Aggregation>(agg);
    }

    using Foreign = int;

    ////////////////////////////////////////////////////////

    ////*******
    ////  transform box_t <Base1, Agg1> -> box_t<Base3, Agg2>
    template<
            typename Base_d, template<typename ...> typename Aggregation_d,
            typename Base_s=Base_d,
            template<typename ...> typename Aggregation_s=Aggregation_d
    >
    struct
    box_trans //<Base_d, Aggregation_d, Base_s,Aggregation_s>
    {
        static auto apply( const typename box<Base_s, Aggregation_s>::type& src,
                           typename box<Base_d, Aggregation_d>::type && dest
                //= typename box<Base_d, Aggregation_d >::type {}
        )
        -> typename box<Base_d, Aggregation_d >::type {

            struct vist {
                typename box<Base_d, Aggregation_d>::type &&dest;

                auto operator()(const Base_s &v ) {
                    auto d = std::move(dest);
                    d = mk_box_v<Base_d, Aggregation_d>(v);
                    return d;
                }

                auto operator()(const typename box<Base_s, Aggregation_s>::agg_t &vs) {
                    auto lst = typename box<Base_d, Aggregation_d>::agg_t{};

                    for (const auto &v: vs) {
                        lst.push_back(
                              //  box_transform<Base_d, Aggregation_d, Base_s, Aggregation_s>(v));
                              box_trans::apply(v,typename box<Base_d, Aggregation_d >::type {}));
                    }
                    auto d = std::move(dest);
                    d = std::move(lst);
                    return d;
                }
            };
            return std::visit(vist{std::move(dest)}, src);

        }
    };

    ////*******
    ////  transform box_t <Base1, Agg1> -> box_t<Base3, Agg2>  + mem!
    template<
            typename Base_d, template<typename ...> typename Aggregation_d,
            typename Base_s=Base_d,
            template<typename ...> typename Aggregation_s=Aggregation_d
    >
    struct box_trans2 //<Base_d, Aggregation_d, Base_s,Aggregation_s>
    {
        static auto apply( const typename box<Base_s, Aggregation_s>::type& src,
                           typename box<Base_d, Aggregation_d>::type && dest,
                           std::pmr::memory_resource * mem= nullptr
                //= typename box<Base_d, Aggregation_d >::type {}
        )
        -> typename box<Base_d, Aggregation_d >::type {

            struct vist {
                typename box<Base_d, Aggregation_d>::type &&dest;
                std::pmr::memory_resource * _memptr= nullptr;

                auto operator()(const Base_s &v ) {
                    auto d = std::move(dest);
                    d = mk_box_v<Base_d, Aggregation_d>(v);
                    return d;
                }

                auto operator()(const typename box<Base_s, Aggregation_s>::agg_t &vs) {
                    auto lst = typename box<Base_d, Aggregation_d>::agg_t{_memptr};

                    for (const auto &v: vs) {
                        lst.push_back(
                                //  box_transform<Base_d, Aggregation_d, Base_s, Aggregation_s>(v));
                                box_trans2::apply(v,typename box<Base_d, Aggregation_d >::type {}, _memptr));
                    }
                    auto d = std::move(dest);
                    d = std::move(lst);
                    return d;
                }
            };
            return std::visit(vist{std::move(dest), mem}, src);

        }
    };


    ////////////////////////////////////////////////////////
/// ? what for ?

    //    template <typename Foreign>
    //   requires( !  std::is_same<   Foreign, Ty>::value  &&  std::is_convertible<Ty,Foreign>::value)
    template<typename Base, template<typename...> typename Aggregation
    >
    requires (!std::is_same<    Foreign, Base>::value && std::is_convertible<Base, Foreign>::value)
    auto mk_box_v_init(
            box<Foreign, Aggregation> il, stepworks::bxa::box<Base,Aggregation>&& dest=stepworks::bxa::box<Base,Aggregation>{}  )//->box<Base,Aggregation>
    {

        return box_trans<Base, Aggregation, Foreign,Aggregation>::apply(il._value, dest );  // box_transform<Base,Aggregation,Foreign >(il);

    }

}


#endif //STEPWORKS_MKBOX_HPP
