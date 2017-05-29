
//  (C) Copyright Rani Sharoni 2003.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.
 
#ifndef BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED
#define BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED

#include <boost/type_traits/intrinsics.hpp>
#ifndef BOOST_IS_BASE_OF
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/detail/ice_and.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#endif

// should be the last #include
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace boost {

namespace detail {

#ifndef BOOST_IS_BASE_OF
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x581)) \
 && !BOOST_WORKAROUND(__SUNPRO_CC , <= 0x540) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 243) \
 && !BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))

                             // The EDG version number is a lower estimate.
                             // It is not currently known which EDG version
                             // exactly fixes the problem.

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

template <typename B, typename D>
struct bd_helper
{
   //
   // This VC7.1 specific workaround stops the compiler from generating
   // an internal compiler error when compiling with /vmg (thanks to
   // Aleksey Gurtovoy for figuring out the workaround).
   //
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    template <typename T>
    static type_traits::yes_type check_sig(D const volatile *, T);
    static type_traits::no_type  check_sig(B const volatile *, int);
#else
    static type_traits::yes_type check_sig(D const volatile *, long);
    static type_traits::no_type  check_sig(B const volatile * const&, int);
#endif
};

template<typename B, typename D>
struct is_base_and_derived_impl2
{
#if BOOST_WORKAROUND(_MSC_FULL_VER, >= 140050000)
#pragma warning(push)
#pragma warning(disable:6334)
#endif
    //
    // May silently do the wrong thing with incomplete types
    // unless we trap them here:
    //
    BOOST_STATIC_ASSERT(sizeof(B) != 0);
    BOOST_STATIC_ASSERT(sizeof(D) != 0);

    struct Host
    {
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1310)
        operator B const volatile *() const;
#else
        operator B const volatile * const&() const;
#endif
        operator D const volatile *();
    };

    BOOST_STATIC_CONSTANT(bool, value =
        sizeof(bd_helper<B,D>::check_sig(Host(), 0)) == sizeof(type_traits::yes_type));
#if BOOST_WORKAROUND(_MSC_FULL_VER, >= 140050000)
#pragma warning(pop)
#endif
};

#else

//
// broken version:
//
template<typename B, typename D>
struct is_base_and_derived_impl2
{
    BOOST_STATIC_CONSTANT(bool, value =
        (::boost::is_convertible<D*,B*>::value));
};

#define BOOST_BROKEN_IS_BASE_AND_DERIVED

#endif

template <typename B, typename D>
struct is_base_and_derived_impl3
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <bool ic1, bool ic2, bool iss>
struct is_base_and_derived_select
{
   template <class T, class U>
   struct rebind
   {
      typedef is_base_and_derived_impl3<T,U> type;
   };
};

template <>
struct is_base_and_derived_select<true,true,false>
{
   template <class T, class U>
   struct rebind
   {
      typedef is_base_and_derived_impl2<T,U> type;
   };
};

template <typename B, typename D>
struct is_base_and_derived_impl
{
    typedef typename remove_cv<B>::type ncvB;
    typedef typename remove_cv<D>::type ncvD;

    typedef is_base_and_derived_select<
       ::boost::is_class<B>::value,
       ::boost::is_class<D>::value,
       ::boost::is_same<B,D>::value> selector;
    typedef typename selector::template rebind<ncvB,ncvD> binder;
    typedef typename binder::type bound_type;

    BOOST_STATIC_CONSTANT(bool, value = bound_type::value);
};
#else
template <typename B, typename D>
struct is_base_and_derived_impl
{
    BOOST_STATIC_CONSTANT(bool, value = BOOST_IS_BASE_OF(B,D));
};
#endif
} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF2(
      is_base_and_derived
    , Base
    , Derived
    , (::boost::detail::is_base_and_derived_impl<Base,Derived>::value)
    )

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_and_derived,Base&,Derived,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_and_derived,Base,Derived&,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_and_derived,Base&,Derived&,false)
#endif

#if BOOST_WORKAROUND(__CODEGEARC__, BOOST_TESTED_AT(0x610))
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_1(typename Base,is_base_and_derived,Base,Base,false)
#endif

} // namespace boost

#include <boost/type_traits/detail/bool_trait_undef.hpp>

#endif // BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED
