//
// immer - immutable data structures for C++
// Copyright (C) 2016, 2017 Juan Pedro Bolivar Puente
//
// This file is part of immer.
//
// immer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// immer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with immer.  If not, see <http://www.gnu.org/licenses/>.
//

#pragma once

#include <immer/config.hpp>

#include <cstddef>
#include <new>
#include <type_traits>

namespace immer {
namespace detail {

template <class T, class Size>
void destroy_n(T* p, Size n)
{
    auto e = p + n;
    for (; p != e; ++p)
        p->~T();
}

inline void* check_alloc(void* p)
{
    if (IMMER_UNLIKELY(!p))
        throw std::bad_alloc{};
    return p;
}

constexpr auto log2(std::size_t x)
{
    static_assert(std::is_same<std::size_t, unsigned long>{},
                  "fix me");
    return x == 0 ? 0 : sizeof(std::size_t) * 8 - 1 - __builtin_clzl(x);
}

struct empty_t {};

template <bool b, typename F>
auto static_if(F&& f) -> std::enable_if_t<b>
{ std::forward<F>(f)(empty_t{}); }
template <bool b, typename F>
auto static_if(F&& f) -> std::enable_if_t<!b>
{}

template <bool b, typename R=void, typename F1, typename F2>
auto static_if(F1&& f1, F2&& f2) -> std::enable_if_t<b, R>
{ return std::forward<F1>(f1)(empty_t{}); }
template <bool b, typename R=void, typename F1, typename F2>
auto static_if(F1&& f1, F2&& f2) -> std::enable_if_t<!b, R>
{ return std::forward<F2>(f2)(empty_t{}); }

} // namespace detail
} // namespace immer
