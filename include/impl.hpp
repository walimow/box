
#ifndef BOX_IMPL_HPP
#define BOX_IMPL_HPP

//#include <detect/>
#include <sstream>
#include <iomanip>

#include "def.hpp"
#include "mkagg.hpp"

#include "loader.hpp"
#include <concepts>


using stepworks::bxa::make::mk_aggregate;

namespace stepworks::bxa {


    template<typename Ty, template<typename...> typename Aggregation>
    box<Ty, Aggregation>::box(std::initializer_list<      typename box<Ty, Aggregation>::type    > il ) {
        ///TODO Modules   _value =   stepworks::bx::make::mk_aggregate<box< Ty,Aggregation  >>apply<>
        (type&) (*this) = mk_aggregate<box<Ty, Aggregation>>::apply_inl  (il);
    }

    template<typename Ty, template<typename...> typename Aggregation>
    template<typename I, typename>
    box<Ty, Aggregation>::box(std::initializer_list<box<Ty, Aggregation>::type> il, const I &a) {}


    template<typename Ty, template<typename...> typename Aggregation>
    template<typename Foreign>
    requires( !std::is_same<Foreign, Ty>::value && std::is_convertible<Ty, Foreign>::value)
    box<Ty, Aggregation>::box(const box<Foreign, Aggregation> &v)
// /*: _value(Ty(v))*/
    {}

    std::ostream &atom_str(std::ostream &ost, ::std::integral auto i) {
        if (sizeof (i)==1)
            ost <<std::hex<<std::setfill('0') << std::setw(2) << std::right ;
        ost << (int) i;
        return ost;
    }

    template  <std::integral N>
    std::ostream &atom_str(std::ostream &ost, std::vector<N> vi) {
        ost << " { ";
        for(const auto& e: vi)
            atom_str( ost, e)<< ' ';
        ost<< " } ";
        return ost;
    }

    std::ostream &atom_str(std::ostream &ost, auto i) {
        ost << i;
        return ost;
    }

    template<typename L, typename R>
    std::ostream &atom_str(std::ostream &ost, const std::pair<L,R>& x) {
        ost << x.first << " : "<< x.second;
        return ost;
    }

    template<typename Ty, template<typename ...> typename Aggregation
//*    ,typename Compare , Allocator
    >
    std::string to_string(const box<Ty, Aggregation
// *
    > &o, const std::string &boxon = "{", const std::string &boxoff = "} ", const std::string &delim = " , ") {

        struct vis {

            const std::string &_bxon;
            const std::string &_bxoff;
            const std::string &_delim;

            auto operator()(const Ty &a) const {
                std::ostringstream ost;
                atom_str(ost, a) << ' ';
                return ost.str();
            }

            auto operator()(const Aggregation<box<Ty, Aggregation
// *  ---agg_t?
            > > &o) const {
                std::ostringstream ost;
                ost << _bxon << ' ';
                for (const auto &v: o) {
                    ost << to_string(v, _bxon, _bxoff, _delim) << ' ' << _delim << ' ';
                }
                ost << _bxoff << ' ';
                return ost.str();
            }
        };

        return std::visit(vis{boxon, boxoff, delim}, o);
    }

    template<typename Ty, template<typename ...> typename Aggregation
            // *  ,class Compare = std::less<K>, typename Allocator = std::allocator<std::pair<const K, Ty>>
    >
    std::string to_string(const typename box<Ty, Aggregation
            // *                       ,Compare,Allocator
    >::agg_t &o, const std::string &boxon = "{", const std::string &boxoff = "} ", const std::string &delim = ", ") {
        std::ostringstream ost;
        ost << "agg_t (" << o.size() << "){ ";
        for (const auto &e: o) {
            ost << to_string(e) << " \n";
        }
        ost << " }";
        return ost.str();
    }

    template<typename Ty, template<typename ...> typename Aggregation  //*    ,typename Compare , Allocator
    >
    auto &from_ist(std::istream &ist, typename box<Ty, Aggregation>::type &o, const std::string &boxon = "{",
                   const std::string &boxoff = "}", const char delim = ',') {
        loader<box<Ty, Aggregation >> l{boxon, boxoff, delim};
        return l.load(o, ist);
    }

}

#endif
