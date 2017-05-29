// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/detail/access_builder.hpp
/// \brief Define macros to help building metafunctions

#ifndef BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP
#define BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/support/member_with_tag.hpp>
#include <boost/bimap/relation/member_at.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>


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

namespace result_of {

template< class Tag, class SymmetricType >
struct NAME
{
    typedef -unspecified- type;
};

} // namespace result_of

******************************************************************************/

/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_RESULT_OF_BUILDER(                       \
                                                                              \
        NAME,                                                                 \
        METAFUNCTION_BASE                                                     \
    )                                                                         \
                                                                              \
    namespace result_of {                                                     \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    struct NAME                                                               \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME METAFUNCTION_BASE                      \
        <                                                                     \
            Tag,SymmetricType                                                 \
                                                                              \
        >::type value_type;                                                   \
                                                                              \
        typedef BOOST_DEDUCED_TYPENAME mpl::if_< is_const<SymmetricType>,     \
                                                                              \
            BOOST_DEDUCED_TYPENAME call_traits<value_type>::const_reference,  \
                                                                              \
            BOOST_DEDUCED_TYPENAME call_traits<value_type>::reference         \
                                                                              \
        >::type type;                                                         \
    };                                                                        \
                                                                              \
    }
/*===========================================================================*/



/******************************************************************************
                   BIMAP SYMMETRIC ACCESS IMPLEMENTATION
*******************************************************************************

namespace detail {

template< class Tag, class SymmetricType >
typename result_of::NAME<Tag,SymmetricType>::type
    NAME( Tag , const Relation & );

} // namespace detail

******************************************************************************/


/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_IMPLEMENTATION_BUILDER(                  \
                                                                              \
        NAME,                                                                 \
        TP_SYMMETRIC,                                                         \
        PARAMETER_NAME,                                                       \
        LEFT_BODY,                                                            \
        RIGHT_BODY                                                            \
    )                                                                         \
                                                                              \
    namespace detail {                                                        \
                                                                              \
                                                                              \
                                                                              \
    template< class TP_SYMMETRIC >                                            \
    BOOST_DEDUCED_TYPENAME result_of::NAME                                    \
    <                                                                         \
        ::boost::bimaps::relation::member_at::left,TP_SYMMETRIC               \
                                                                              \
    >::type                                                                   \
                                                                              \
    NAME( ::boost::bimaps::relation::member_at::left,                         \
                  TP_SYMMETRIC & PARAMETER_NAME )                             \
    {                                                                         \
        LEFT_BODY;                                                            \
    }                                                                         \
                                                                              \
    template< class TP_SYMMETRIC >                                            \
    BOOST_DEDUCED_TYPENAME result_of::NAME                                    \
    <                                                                         \
        ::boost::bimaps::relation::member_at::right,TP_SYMMETRIC              \
                                                                              \
    >::type                                                                   \
                                                                              \
    NAME( ::boost::bimaps::relation::member_at::right,                        \
                  TP_SYMMETRIC & PARAMETER_NAME )                             \
    {                                                                         \
        RIGHT_BODY;                                                           \
    }                                                                         \
                                                                              \
    }
/*===========================================================================*/


/******************************************************************************
                   BIMAP RELATION ACCESS INTERFACE
*******************************************************************************

template< class Tag, class SymmetricType >
typename result_of::NAME<Tag,SymmetricType>::type
    NAME( const SymmetricType & );

******************************************************************************/

/*===========================================================================*/
#define BOOST_BIMAP_SYMMETRIC_ACCESS_INTERFACE_BUILDER(                       \
                                                                              \
        NAME                                                                  \
    )                                                                         \
                                                                              \
    template< class Tag, class SymmetricType >                                \
    BOOST_DEDUCED_TYPENAME result_of::NAME<Tag,SymmetricType>::type           \
    NAME( SymmetricType & s )                                                 \
    {                                                                         \
        typedef BOOST_DEDUCED_TYPENAME ::boost::bimaps::relation::support::   \
            member_with_tag                                                   \
            <                                                                 \
                Tag,SymmetricType                                             \
                                                                              \
            >::type member_at_tag;                                            \
                                                                              \
        return detail::NAME(member_at_tag(),s);                               \
    }
/*===========================================================================*/


#endif // BOOST_BIMAP_RELATION_ACCESS_BUILDER_HPP

