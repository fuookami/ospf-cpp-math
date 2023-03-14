#pragma once

#include <ospf/math/algebra/value_range/interval.hpp>
#include <ospf/math/algebra/value_range/value_wrapper.hpp>
#include <ospf/string/format.hpp>

namespace ospf
{
    inline namespace math
    {
        inline namespace algebra
        {
            namespace value_range
            {
                enum class BoundSide : u8
                {
                    Lower,
                    Upper,
                };

                template<Arithmetic T, Interval itv>
                class Bound
                {
                public:
                    using ValueType = OriginType<T>;
                    using WrapperType = ValueWrapper<ValueType>;

                public:
                    Bound(BoundSide side, ArgCLRefType<WrapperType> value)
                        : _side(side), _value(value) {}

                    template<typename = void>
                        requires ReferenceFaster<WrapperType> && std::movable<WrapperType>
                    Bound(BoundSide side, ArgRRefType<WrapperType> value)
                        : _side(side), _value(move<WrapperType>(value)) {}

                    template<typename... Args>
                        requires std::constructible_from<WrapperType, Args...>
                    Bound(BoundSide side, Args&&... args)
                        : _side(side), _value(std::forward<Args>(args)...) {}

                public:
                    Bound(const Bound& ano) = default;
                    Bound(Bound&& ano) noexcept = default;
                    Bound& operator=(const Bound& rhs) = default;
                    Bound& operator=(Bound&& rhs) noexcept = default;
                    ~Bound(void) noexcept = default;

                public:
                    inline const BoundSide side(void) const noexcept
                    {
                        return _side;
                    }

                    inline WrapperType& value(void) noexcept
                    {
                        return _value;
                    }

                    inline const WrapperType& value(void) const noexcept
                    {
                        return _value;
                    }

                private:
                    BoundSide _side;
                    WrapperType _value;
                };

                template<Arithmetic T>
                class DynBound
                {
                public:
                    using ValueType = OriginType<T>;
                    using WrapperType = ValueWrapper<ValueType>;

                public:
                    DynBound(BoundSide side, Interval interval, ArgCLRefType<WrapperType> value)
                        : _side(side), _interval(interval), _value(value) {}

                    template<typename = void>
                        requires ReferenceFaster<WrapperType>&& std::movable<WrapperType>
                    DynBound(BoundSide side, Interval interval, ArgRRefType<WrapperType> value)
                        : _side(side), _interval(interval), _value(move<WrapperType>(value)) {}

                    template<typename... Args>
                        requires std::constructible_from<WrapperType, Args...>
                    DynBound(BoundSide side, Interval interval, Args&&... args)
                        : _side(side), _interval(interval), _value(std::forward<Args>(args)...) {}

                public:
                    DynBound(const DynBound& ano) = default;
                    DynBound(DynBound&& ano) noexcept = default;
                    DynBound& operator=(const DynBound& rhs) = default;
                    DynBound& operator=(DynBound&& rhs) noexcept = default;
                    ~DynBound(void) noexcept = default;

                public:
                    inline const BoundSide side(void) const noexcept
                    {
                        return _side;
                    }

                    inline WrapperType& value(void) noexcept
                    {
                        return _value;
                    }

                    inline const WrapperType& value(void) const noexcept
                    {
                        return _value;
                    }

                private:
                    BoundSide _side;
                    Interval _interval;
                    WrapperType _value;
                };
            };
        };
    };
};

namespace std
{
    template<ospf::Arithmetic T, ospf::Interval itv>
    struct formatter<ospf::value_range::Bound<T, itv>, char>
        : public formatter<std::string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(ospf::ArgCLRefType<ospf::value_range::Bound<T, itv>> bound, FormatContext& fc)
        {
            static const formatter<std::string_view, char> _formatter{};
            if (bound.side() == ospf::value_range::BoundSide::Lower)
            {
                return _formatter.format(std::format("{}{}", ospf::value_range::IntervalTrait<itv>::lower_bound_sign(), bound.value()), fc);
            }
            else
            {
                return _formatter.format(std::format("{}{}", bound.value(), ospf::value_range::IntervalTrait<itv>::upper_bound_sign()), fc);
            }
        }
    };

    template<ospf::Arithmetic T, ospf::Interval itv>
    struct formatter<ospf::value_range::Bound<T, itv>, ospf::wchar>
        : public formatter<std::string_view, ospf::wchar>
    {
        template<typename FormatContext>
        inline decltype(auto) format(ospf::ArgCLRefType<ospf::value_range::Bound<T, itv>> bound, FormatContext& fc)
        {
            static const formatter<std::wstring_view, ospf::wchar> _formatter{};
            if (bound.side() == ospf::value_range::BoundSide::Lower)
            {
                const auto sign = boost::locale::conv::to_utf<ospf::wchar>(ospf::value_range::IntervalTrait<itv>::lower_bound_sign(), std::locale{});
                return _formatter.format(std::format(L"{}{}", sign, bound.value()), fc);
            }
            else
            {
                const auto sign = boost::locale::conv::to_utf<ospf::wchar>(ospf::value_range::IntervalTrait<itv>::upper_bound_sign(), std::locale{});
                return _formatter.format(std::format(L"{}{}", bound.value(), sign), fc);
            }
        }
    };

    template<ospf::Arithmetic T>
    struct formatter<ospf::value_range::DynBound<T>, char>
        : public formatter<std::string_view, char>
    {
        template<typename FormatContext>
        inline decltype(auto) format(ospf::ArgCLRefType<ospf::value_range::DynBound<T>> bound, FormatContext& fc)
        {
            static const formatter<std::string_view, CharT> _formatter{};
            const ospf::value_range::DynIntervalTrait trait{ bound.interval() };
            if (bound.side() == ospf::value_range::BoundSide::Lower)
            {
                return _formatter.format(std::format("{}{}", trait.lower_bound_sign(), bound.value()), fc);
            }
            else
            {
                return _formatter.format(std::format("{}{}", bound.value(), trait.upper_bound_sign()), fc);
            }
        }
    };

    template<ospf::Arithmetic T>
    struct formatter<ospf::value_range::DynBound<T>, ospf::wchar>
    {
        template<typename FormatContext>
        inline decltype(auto) format(ospf::ArgCLRefType<ospf::value_range::DynBound<T>> bound, FormatContext& fc)
        {
            static const formatter<std::wstring_view, ospf::wchar> _formatter{};
            const ospf::value_range::DynIntervalTrait trait{ bound.interval() };
            if (bound.side() == ospf::value_range::BoundSide::Lower)
            {
                const auto sign = boost::locale::conv::to_utf<ospf::wchar>(trait.lower_bound_sign(), std::locale{});
                return _formatter.format(std::format("L{}{}", sign, bound.value()), fc);
            }
            else
            {
                const auto sign = boost::locale::conv::to_utf<ospf::wchar>(trait.upper_bound_sign(), std::locale{});
                return _formatter.format(std::format("L{}{}", bound.value(), sign), fc);
            }
        }
    };
};
