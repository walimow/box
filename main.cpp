#include <iostream>

#include <box.hpp>
#include <trace.hpp>
#include <vector>
#include <trace.hpp>

int main() {


    using stepworks::bxx::box;
    using stepworks::bxx::box_type;
    using T = int;
    using BOX = box<T, std::vector>;
    using BOX_T = box_type<T, std::vector>;

    using stepworks::bxx::make::mk_box_v;

    using stepworks::bxx::util::trace;
    using stepworks::bxx::util::trace_form;


    {

        using stepworks::bxx::make::mk_box_v;
        auto v4= mk_box_v<int,std::vector>({42,{1},666});

        ///BOX bb(v4);
        std::cout<< " (3?)--> " << BOX_T ::count(v4)<<"\n";
        trace<int,std::vector>( std::get< typename BOX::agg_t>(v4) );

    }


    auto v4= mk_box_v<int,std::vector>({42,{1},666});

    ///BOX bb(v4);
    std::cout<< " (--3?---)--> " << BOX_T ::count(v4)<<"\n";
    trace<int,std::vector>( std::get< typename BOX::agg_t>(v4) );

    //  auto v5= mk_box_v<int,std::vector>({42,{1,2,3},666});

    return 0;
}
