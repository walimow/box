
#ifndef BOX_IMPL_HPP
#define BOX_IMPL_HPP

//#include <detect/>
#include "def.hpp"
#include "mkagg.hpp"

using  stepworks::bxx::make::mk_aggregate;

namespace stepworks::bxx{





    template <typename Ty , template <typename...> typename Aggregation>
    box<Ty, Aggregation>::box( std::initializer_list<
               // std::variant < Ty,
               typename box<Ty,Aggregation>::type
                > il
    ){
            _value = mk_aggregate<  box<   Ty, Aggregation>>::apply_inl
              // <std::initializer_list <  typename           box<Ty,Aggregation  >::agg_t  >
                        (il );

    }




template<typename Ty,template <typename...>  typename Aggregation>
template<typename I, typename>
box<Ty, Aggregation>::box(std::initializer_list<box<Ty, Aggregation>::type> il, const I &a) {}



}

#endif
