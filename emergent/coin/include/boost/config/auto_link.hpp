//  (C) Copyright John Maddock 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         auto_link.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Automatic library inclusion for Borland/Microsoft compilers.
  */

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

#ifdef __cplusplus
#  ifndef BOOST_CONFIG_HPP
#     include <boost/config.hpp>
#  endif
#elif defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__EDG_VERSION__)
//
// C language compatability (no, honestly)
//
#  define BOOST_MSVC _MSC_VER
#  define BOOST_STRINGIZE(X) BOOST_DO_STRINGIZE(X)
#  define BOOST_DO_STRINGIZE(X) #X
#endif
//
// Only include what follows for known and supported compilers:
//
#if defined(BOOST_MSVC) \
    || defined(__BORLANDC__) \
    || (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) \
    || (defined(__ICL) && defined(_MSC_EXTENSIONS) && (_MSC_VER >= 1200))

#ifndef BOOST_VERSION_HPP
#  include <boost/version.hpp>
#endif

#ifndef BOOST_LIB_NAME
#  error "Macro BOOST_LIB_NAME not set (internal error)"
#endif

//
// error check:
//
#if defined(__MSVC_RUNTIME_CHECKS) && !defined(_DEBUG)
#  pragma message("Using the /RTC option without specifying a debug runtime will lead to linker errors")
#  pragma message("Hint: go to the code generation options and switch to one of the debugging runtimes")
#  error "Incompatible build options"
#endif
//
// select toolset if not defined already:
//
#ifndef BOOST_LIB_TOOLSET
// Note: no compilers before 1200 are supported
#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)

#  ifdef UNDER_CE
     // vc6:
#    define BOOST_LIB_TOOLSET "evc4"
#  else
     // vc6:
#    define BOOST_LIB_TOOLSET "vc6"
#  endif

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1300)

   // vc7:
#  define BOOST_LIB_TOOLSET "vc7"

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1310)

   // vc71:
#  define BOOST_LIB_TOOLSET "vc71"

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1400)

   // vc80:
#  define BOOST_LIB_TOOLSET "vc80"

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1500)

   // vc90:
#  define BOOST_LIB_TOOLSET "vc90"

#elif defined(BOOST_MSVC) && (BOOST_MSVC >= 1600)

   // vc10:
#  define BOOST_LIB_TOOLSET "vc100"

#elif defined(__BORLANDC__)

   // CBuilder 6:
#  define BOOST_LIB_TOOLSET "bcb"

#elif defined(__ICL)

   // Intel C++, no version number:
#  define BOOST_LIB_TOOLSET "iw"

#elif defined(__MWERKS__) && (__MWERKS__ <= 0x31FF )

   // Metrowerks CodeWarrior 8.x
#  define BOOST_LIB_TOOLSET "cw8"

#elif defined(__MWERKS__) && (__MWERKS__ <= 0x32FF )

   // Metrowerks CodeWarrior 9.x
#  define BOOST_LIB_TOOLSET "cw9"

#endif
#endif // BOOST_LIB_TOOLSET

//
// select thread opt:
//
#if defined(_MT) || defined(__MT__)
#  define BOOST_LIB_THREAD_OPT "-mt"
#else
#  define BOOST_LIB_THREAD_OPT
#endif

#if defined(_MSC_VER) || defined(__MWERKS__)

#  ifdef _DLL

#     if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && (defined(_STLP_OWN_IOSTREAMS) || defined(__STL_OWN_IOSTREAMS))

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-gdp"
#        elif defined(_DEBUG)
#            define BOOST_LIB_RT_OPT "-gdp"
#            pragma message("warning: STLPort debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-p"
#        endif

#     elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-gdpn"
#        elif defined(_DEBUG)
#            define BOOST_LIB_RT_OPT "-gdpn"
#            pragma message("warning: STLPort debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-pn"
#        endif

#     else

#        if defined(_DEBUG)
#            define BOOST_LIB_RT_OPT "-gd"
#        else
#            define BOOST_LIB_RT_OPT
#        endif

#     endif

#  else

#     if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && (defined(_STLP_OWN_IOSTREAMS) || defined(__STL_OWN_IOSTREAMS))

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-sgdp"
#        elif defined(_DEBUG)
#             define BOOST_LIB_RT_OPT "-sgdp"
#            pragma message("warning: STLPort debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-sp"
#        endif

#     elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-sgdpn"
#        elif defined(_DEBUG)
#             define BOOST_LIB_RT_OPT "-sgdpn"
#            pragma message("warning: STLPort debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-spn"
#        endif

#     else

#        if defined(_DEBUG)
#             define BOOST_LIB_RT_OPT "-sgd"
#        else
#            define BOOST_LIB_RT_OPT "-s"
#        endif

#     endif

#  endif

#elif defined(__BORLANDC__)

//
// figure out whether we want the debug builds or not:
//
#if __BORLANDC__ > 0x561
#pragma defineonoption BOOST_BORLAND_DEBUG -v
#endif
//
// sanity check:
//
#if defined(__STL_DEBUG) || defined(_STLP_DEBUG)
#error "Pre-built versions of the Boost libraries are not provided in STLPort-debug form"
#endif

#  ifdef _RTLDLL

#     ifdef BOOST_BORLAND_DEBUG
#         define BOOST_LIB_RT_OPT "-d"
#     else
#         define BOOST_LIB_RT_OPT
#     endif

#  else

#     ifdef BOOST_BORLAND_DEBUG
#         define BOOST_LIB_RT_OPT "-sd"
#     else
#         define BOOST_LIB_RT_OPT "-s"
#     endif

#  endif

#endif

//
// select linkage opt:
//
#if (defined(_DLL) || defined(_RTLDLL)) && defined(BOOST_DYN_LINK)
#  define BOOST_LIB_PREFIX
#elif defined(BOOST_DYN_LINK)
#  error "Mixing a dll boost library with a static runtime is a really bad idea..."
#else
#  define BOOST_LIB_PREFIX "lib"
#endif

//
// now include the lib:
//
#if defined(BOOST_LIB_NAME) \
      && defined(BOOST_LIB_PREFIX) \
      && defined(BOOST_LIB_TOOLSET) \
      && defined(BOOST_LIB_THREAD_OPT) \
      && defined(BOOST_LIB_RT_OPT) \
      && defined(BOOST_LIB_VERSION)

#ifndef BOOST_AUTO_LINK_NOMANGLE
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT "-" BOOST_LIB_VERSION ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT "-" BOOST_LIB_VERSION ".lib")
#  endif
#else
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_LIB_NAME) ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_STRINGIZE(BOOST_LIB_NAME) ".lib")
#  endif
#endif

#else
#  error "some required macros where not defined (internal logic error)."
#endif


#endif // _MSC_VER || __BORLANDC__

//
// finally undef any macros we may have set:
//
#ifdef BOOST_LIB_PREFIX
#  undef BOOST_LIB_PREFIX
#endif
#if defined(BOOST_LIB_NAME)
#  undef BOOST_LIB_NAME
#endif
// Don't undef this one: it can be set by the user and should be the 
// same for all libraries:
//#if defined(BOOST_LIB_TOOLSET)
//#  undef BOOST_LIB_TOOLSET
//#endif
#if defined(BOOST_LIB_THREAD_OPT)
#  undef BOOST_LIB_THREAD_OPT
#endif
#if defined(BOOST_LIB_RT_OPT)
#  undef BOOST_LIB_RT_OPT
#endif
#if defined(BOOST_LIB_LINK_OPT)
#  undef BOOST_LIB_LINK_OPT
#endif
#if defined(BOOST_LIB_DEBUG_OPT)
#  undef BOOST_LIB_DEBUG_OPT
#endif
#if defined(BOOST_DYN_LINK)
#  undef BOOST_DYN_LINK
#endif
#if defined(BOOST_AUTO_LINK_NOMANGLE)
#  undef BOOST_AUTO_LINK_NOMANGLE
#endif











