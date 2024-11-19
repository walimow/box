//
// Created by karsten on 24.11.20.
//

#ifndef BOX_DEF_HPP
#define BOX_DEF_HPP

#include <variant>
#include <detect/detect_allocator.hpp>
#include <ostream>
#include <concepts>



using stepworks::detect::has_allocator;



namespace stepworks::bxa {

    template<typename Ty, template<typename ...> typename Aggregation>
    struct box;

    template<typename Ty, template<typename ...> typename Aggregation>
    constexpr auto operator<=>(const box<Ty, Aggregation> &l, const box<Ty, Aggregation> &r) noexcept;

    template<typename Ty, template<typename ...> typename Aggregation>
    bool
    operator==(const typename box<Ty, Aggregation>::type &l, const typename box<Ty, Aggregation>::type &r) noexcept;

    template<typename Ty, template<typename ...> typename Aggregation>
    struct less_bx;

    template<typename Ty, template<typename ...> typename Aggregation>
    struct box;

    template<typename Ty, template<typename...> typename Form>
    constexpr bool eq_bx(const typename stepworks::bxa::box<Ty, Form>::type& l, const typename stepworks::bxa::box<Ty, Form>::type& r);

    template <typename Ty, template <typename...> typename Aggregation>
    constexpr auto operator<=>(const typename  box<Ty, Aggregation>::type & l, const typename box<Ty, Aggregation>::type & r)  noexcept ;


    template<typename Ty, template<typename ...> typename Aggregation
//            template Allocator = std::allocator<std::variant<Ty, >   >
            >
      struct  box:  std::variant<Ty, Aggregation<box<Ty, Aggregation> >>
            {
            public:
        using base_t = Ty;
        using agg_t = Aggregation<box<base_t, Aggregation>  >;
        using type = std::variant<Ty, agg_t>;
        using init_t = std::initializer_list<type>;
        using cmp_t =  less_bx<Ty, Aggregation>;



        using type_enum = enum {
            eatom = 0, eaggregate = 1
        };

        struct agg_position {
            const agg_t &_container;
            typename agg_t::const_iterator _it;
        };

//        type _value;

        box(type v) {     //   std::cout<<"-1-";
            (type &) (*this) = v;
        }


        template<typename Foreign>
        requires( !std::is_same<Foreign, Ty>::value && std::is_convertible<Ty, Foreign>::value)
        box(const box<Foreign, Aggregation> &v); // /*: _value(Ty(v))*/ {}

        box(agg_t &&a) {      //   std::cout<<"-3-";
            (type &) (*this) = std::move(a);
        }

        box(const agg_t &a) {      //   std::cout<<"-3-";
            (type &) (*this) = a;
        }

        box() {
            (type &) (*this) = agg_t{};
        }

        box(std::initializer_list< //std::variant<Ty,
                typename box<Ty, Aggregation>::type> il);

        template<typename B =  typename box<Ty, std::initializer_list>::type, typename =     typename std::enable_if_t
                <
                        !std::is_same<B, type>::value>::type>

        box(const B &b) {
            (type &) (*this) = b;
        }

        template<typename I = const typename box<Ty, Aggregation>::agg_t, typename =     typename std::enable_if_t
                <has_allocator<I>::value> >
        box(
                std::initializer_list<
                        typename box<Ty, Aggregation>::type> il, const I &a
        );

        box(type_enum e) {
            (type &) (*this) = (e) ? type(agg_t{}) : type(base_t{});
        }

        operator type() const {
            return *this;
        }


        const auto &_as_type() const {
            return (type &) (*this);
        }

        bool operator==(const typename box<Ty, Aggregation>::type &other) const noexcept{
            struct {
                auto operator()(const Ty &la, const Ty &ra)const { return la == ra; };

                auto operator()(const Ty &la, const typename box<Ty, Aggregation>::agg_t &rc) const { return false; };

                auto operator()(const typename box<Ty, Aggregation>::agg_t &lc, const Ty &ra) const{ return false; };

                auto operator()(const typename box<Ty, Aggregation>::agg_t &lc,
                                const typename box<Ty, Aggregation>::agg_t &rc) const {
                    if (lc.size() != rc.size())
                        return false;
                    auto itl = lc.begin();
                    auto itr = rc.begin();
                    while (itl != lc.cend() && itr != rc.cend()) {
                        if (eq_bx<Ty,Aggregation>(*itl,*itr)){
                            itl++;
                            itr++;
                        }
                        else
                            return false;

                    }
                    return true;
                };
            } vis;
            return std::visit(vis, *this, other);
        }

        constexpr auto operator<=>(const box<Ty, Aggregation> & other) const noexcept {
            return box<Ty,Aggregation>::__wo(*this, other) ;
        }


        static inline std::weak_ordering __wo(const typename box<Ty, Aggregation>::type &l, const typename box<Ty, Aggregation>::type &r) noexcept {

            struct {
                auto operator()(const Ty &la, const Ty &ra)->std::weak_ordering { return la <=> ra; };

                auto operator()(const Ty &la, const typename box<Ty, Aggregation>::agg_t &rc)->std::weak_ordering  {
                    return rc.size() ? std::weak_ordering::greater : std::weak_ordering::less;
                };

                auto operator()(const typename box<Ty, Aggregation>::agg_t &lc, const Ty &ra) ->std::weak_ordering {
                    return lc.size() ? std::weak_ordering::greater : std::weak_ordering::less;
                };


                auto operator()(const typename box<Ty, Aggregation>::agg_t &lc,
                                const typename box<Ty, Aggregation>::agg_t &rc) ->std::weak_ordering {
                    if (lc.size() != rc.size())
                        return  lc.size() <=> rc.size();
                    auto itl = lc.begin();
                    auto itr = rc.begin();
                    while (itl != lc.cend() && itr != rc.cend()) {

                        if (!(itl->_as_type() == itr->_as_type())) {
                            return itl->_as_type() < itr->_as_type() ? std::weak_ordering::less : std::weak_ordering::greater;
                        }
                        itl++;
                        itr++;
                    }
                    return std::weak_ordering::equivalent;
                };
            } vis;
            return std::visit(vis, l, r);
        }



        friend std::ostream &operator<<(std::ostream &s, const box<Ty, Aggregation> &o) {
            s << to_string(o);
            return s;
        };

        friend std::istream &operator>>(std::istream &s, box<Ty, Aggregation>::type &o) {
            return from_ist<Ty, Aggregation>(s, o);
        };

    };


    /*
    template<typename Ty, template<typename ...> typename Aggregation>
    constexpr auto operator<=>(const box<Ty, Aggregation> & l, const box<Ty, Aggregation> & r)  noexcept {
        return box<Ty,Aggregation>::__wo(l, r) ;
    }
     */

    template<typename Ty, template<typename ...> typename Aggregation>
    bool
    operator==(const typename box<Ty, Aggregation>::type &l, const typename box<Ty, Aggregation>::type &r) noexcept {
        struct {
            auto operator()(const Ty &la, const Ty &ra) const { return la == ra; };

            auto operator()(const Ty &la, const typename box<Ty, Aggregation>::agg_t &rc) const { return false; };

            auto operator()(const typename box<Ty, Aggregation>::agg_t &lc, const Ty &ra) const { return false; };

            auto operator()(const typename box<Ty, Aggregation>::agg_t &lc,
                            const typename box<Ty, Aggregation>::agg_t &rc) const {
                if (lc.size() != rc.size())
                    return false;
                auto itl = lc.begin();
                auto itr = rc.begin();
                while (itl != lc.cend() && itr != rc.cend()) {
                    if (eq_bx<Ty, Aggregation>(*itl, *itr)) {
                        // if ( *itl  ==*itr ) { //        if (cmp_bx<Ty,Form>{l[k], r[k]}()!= std::strong_ordering::equal)
                        itl++;
                        itr++;
                    } else
                        return false;
                }
                return true;
            };
        } vis;
        return std::visit(vis, l, r);
    }

}


#endif //BOX_DEF_HPP
