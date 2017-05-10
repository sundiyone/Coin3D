#ifndef COIN_SBBASICP_H
#define COIN_SBBASICP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

#include <Inventor/misc/SoBase.h>

class SoAction;
class SoDetail;
class SoElement;
class SoEvent;
class SoPath;
class ScXMLObject;

#if !defined(_MSC_VER) || (_MSC_VER >= 1300) //coin_depointer does not work with MSVC 6
#define COIN_DEPOINTER_AVAILABLE
#endif

#ifdef COIN_DEPOINTER_AVAILABLE
template <typename Type>
struct coin_depointer {
  enum { valid = false };
};

template <typename Type>
struct coin_depointer<Type *> {
  enum { valid = true };
  typedef Type type;
};

template <typename Type>
struct coin_depointer<Type * const> {
  enum { valid = true };
  typedef Type type;
};

#endif //COIN_DEPOINTER_AVAILABLE

template<typename To,typename From>
To coin_internal_safe_cast2(From * ptr) {
#ifdef COIN_DEPOINTER_AVAILABLE
  if((ptr != nullptr) && ptr->getTypeId().isDerivedFrom(coin_depointer<To>::type::getClassTypeId()))
#else
  //FIXME Can we avoid declaring an unused variable also for MSVC6? - BFG 20080807
  To retVal = nullptr;
  if((ptr != nullptr) && ptr->getTypeId().isDerivedFrom(retVal->getClassTypeId()))
#endif //OLDMSVC
  return static_cast<To>(ptr);
  return nullptr;
}

template<typename To,typename From>
To
coin_internal_safe_cast(From * ptr) {
#ifdef COIN_DEPOINTER_AVAILABLE
  if((ptr != nullptr) && ptr->isOfType(coin_depointer<To>::type::getClassTypeId()))
#else
  if((ptr != nullptr) && ptr->isOfType(((To) nullptr)->getClassTypeId()))
#endif //OLDMSVC
    return static_cast<To>(ptr);
  return nullptr;
}

template<typename To>
To coin_safe_cast(const SoBase * ptr) { return coin_internal_safe_cast<To>(ptr); }
template<typename To>
To coin_safe_cast(SoBase * ptr) { return coin_internal_safe_cast<To>(ptr); }
template<typename To>
To coin_safe_cast(SoAction * ptr) { return coin_internal_safe_cast<To>(ptr); }
template<typename To>
To coin_safe_cast(SoDetail * ptr) { return coin_internal_safe_cast<To>(ptr); }
template<typename To>
To coin_safe_cast(const SoDetail * ptr) { return coin_internal_safe_cast<To>(ptr); }
template<typename To>
To coin_safe_cast(SoField * ptr) { return coin_internal_safe_cast<To>(ptr); }
template<typename To>
To coin_safe_cast(SoElement * ptr) { return coin_internal_safe_cast2<To>(ptr); }
template<typename To>
To coin_safe_cast(const SoElement * ptr) { return coin_internal_safe_cast2<To>(ptr); }
template<typename To>
To coin_safe_cast(SoEvent * ptr) { return coin_internal_safe_cast2<To>(ptr); }
template<typename To>
To coin_safe_cast(const SoEvent * ptr) { return coin_internal_safe_cast2<To>(ptr); }
template<typename To>
To coin_safe_cast(ScXMLObject * ptr) { return coin_internal_safe_cast2<To>(ptr); }
template<typename To>
To coin_safe_cast(const ScXMLObject * ptr) { return coin_internal_safe_cast2<To>(ptr); }

#include "coindefs.h"

template<typename To,typename From>
To
coin_internal_assert_cast(From * ptr) {
  To retVal = coin_safe_cast<To>(ptr);
  //NOTE if we ever get an assert here, the error is on the caller,
  //not here. Allthough it will be prudent to disable this assert in
  //any release before we have tested the calling code well enough. -
  //BFG 20080916
#ifdef COIN_BETA_VERSION // COIN_BETA_VERSION is not defined in release versions
  assert(retVal && "ptr was not of correct type");
#endif // COIN_BETA_VERSION
  return retVal;
}

template<typename To>
To coin_assert_cast(const SoBase * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(SoBase * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(SoAction * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(const SoDetail * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(SoField * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(SoElement * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(const SoElement * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(SoEvent * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(const SoEvent * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(ScXMLObject * ptr) { return coin_internal_assert_cast<To>(ptr); }
template<typename To>
To coin_assert_cast(const ScXMLObject * ptr) { return coin_internal_assert_cast<To>(ptr); }

//FIXME Should we remove this? - BFG 20080801
//Strictly for internal use, until we know exactly how to handle these
template <typename To>
To
reclassify_cast(SoPath * ptr) {
  return reinterpret_cast<To>(ptr);
}
template <typename To>
To
reclassify_cast(const SoPath * ptr) {
  return reinterpret_cast<To>(ptr);
}

//NOTE What we are doing here is strictly not supported by the C++
//standard. So we need to do some duck and dive between different
//compilers. BFG 20080814
template <typename To, typename From>
To
function_to_object_cast(From ptr) {
#if defined(__GNUC__) && ( __GNUC__ >= 4)
  //Add compilers which support this style explicitly
  return reinterpret_cast<To>(ptr);
#else
  //This is not C++ correct, but we default to this, as most compilers will accept it.
  return (To) ptr;
#endif
}

//Casting the other way of function_to_object_cast, implemented by
//calling function_to_object_cast.
template <typename To, typename From>
To
object_to_function_cast(From obj) {
  return function_to_object_cast<To>(obj);
}
#endif // !COIN_SBBASICP_H
