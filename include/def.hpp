//
// Created by karsten on 24.11.20.
//

#ifndef BOX_DEF_HPP
#define BOX_DEF_HPP

#include <variant>
#include <detect/detect_allocator.hpp>

using stepworks::bxx::detect::has_allocator;

namespace stepworks::bxx{

   // template <typename ...> struct box;

   ///we assmume not to need a allocator specification here:  pmr-Types may declared by its convinient std::pmr::Container

    template <typename Ty, template<typename ...> typename Aggregation>
    struct box{

        using base_t = Ty;
        using agg_t = Aggregation<box<base_t, Aggregation> >;
        using type = std::variant<Ty, agg_t>;

        using type_enum=enum{eatom=0, eaggregate=1};

        type _value;


        box(type v) : _value(std::forward<type>(v)) {     //   std::cout<<"-1-";
        }

     //   using is_allocable_container = typename has_allocator<typename box<Ty, Aggregation>::agg_t>::type;

        box(agg_t&& a) : _value(std::move(a)) {      //   std::cout<<"-3-";
        }

        box(const agg_t& a) : _value(a) {      //   std::cout<<"-3-";
        }

        box() {
            _value=agg_t {};
        }

///empty with allocator
        template <template <typename... > typename Agg_=Aggregation>
        requires (has_allocator<typename box<Ty, Agg_>::agg_t>::value)
        box( const typename box<Ty, Agg_>::agg_t::allocator_type & alloc ){
            _value= typename box<Ty, Agg_>::agg_t(
                    alloc
                    );
        }

        box(std::initializer_list< //std::variant<Ty,
                typename   box<Ty, Aggregation>::type  > il);



        template<typename B =  typename  box<Ty,std::initializer_list>::type, typename =     typename std::enable_if_t
                <
                       ! std::is_same<B, type>::value>::type>

        box( const  B& b ){
            _value=b;
        }

        template<typename I = const typename box<Ty, Aggregation>::agg_t, typename =     typename std::enable_if_t
                <  has_allocator<I>::value> >
        box(
                std::initializer_list<
                        typename box<Ty, Aggregation>::type> il, const I &a
        );

        box(type_enum  e) {
            _value= (e) ? type (agg_t {}) : type(base_t{});
        }

        operator type () const{
            return _value;
        }

    };


    };






#endif //BOX_DEF_HPP
