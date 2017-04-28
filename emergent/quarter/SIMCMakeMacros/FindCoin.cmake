# FIXME: Caching of the result seems to be broken, causing cmake to re-search 
# for Coin every time it runs. kintel 20090114.

# FIXME: Rewrite this to be more standards compliant
# See http://www.cmake.org/cgi-bin/viewcvs.cgi/Modules/readme.txt?root=CMake&view=markup
# Look at FindVTK for an example of how to solve the location mess we have in Coin

# FIXME: Document. Returns Coin_INCLUDE_DIR, Coin_DEFINES, Coin_LIBRAR(Y|IES)
# Note: Due to limiting CMake support for Mac OS X, we cannot assume that Coin_INCLUDE_DIR
# is an actual path pointing to the actual header files (it usually points to the 
# framework itself), so don't use this to do anything fancy in client CMakeLists.txt files.

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS True)

# use coin-config
find_program(Coin_CONFIG_EXECUTABLE NAMES coin-config DOC "coin-config executable")
mark_as_advanced(Coin_CONFIG_EXECUTABLE)
MESSAGE("coin-config = ${Coin_CONFIG_EXECUTABLE}")

if(Coin_CONFIG_EXECUTABLE)
  set(Coin_LIBRARY_FOUND 1)

  #execute_process(COMMAND ${Coin_CONFIG_EXECUTABLE} --cppflags OUTPUT_VARIABLE CoinConf_cppflags)
  #string(REGEX REPLACE "[\r\n]" " " CoinConf_cppflags "${CoinConf_cppflags}")

  #execute_process(COMMAND ${Coin_CONFIG_EXECUTABLE} --includedir OUTPUT_VARIABLE CoinConf_includedir)
  #MESSAGE("${CoinConf_includedir}")
  #string(REGEX REPLACE "[\r\n]" " " CoinConf_includedir "${CoinConf_includedir}")

  #execute_process(COMMAND ${Coin_CONFIG_EXECUTABLE} --ldflags OUTPUT_VARIABLE CoinConf_ldflags)
  #MESSAGE("${CoinConf_ldflags}")
  #string(REGEX REPLACE "[\r\n]" " " CoinConf_ldflags "${CoinConf_ldflags}")

  #execute_process(COMMAND ${Coin_CONFIG_EXECUTABLE} --libs OUTPUT_VARIABLE CoinConf_libs)
  #MESSAGE("${CoinConf_libs}")
  #string(REGEX REPLACE "[\r\n]" " " CoinConf_libs "${CoinConf_libs}")

  #string(REGEX MATCHALL "(^| )-l([./+-_\\a-zA-Z]*)" CoinConf_libs "${CoinConf_libs}")
  #string(REGEX REPLACE "(^| )-l" "" CoinConf_libs "${CoinConf_libs}")

  #string(REGEX MATCHALL "(^| )-L([./+-_\\a-zA-Z]*)" CoinConf_ldirs "${CoinConf_ldflags}")
  #string(REGEX REPLACE "(^| )-L" "" CoinConf_ldirs "${CoinConf_ldirs}")

  #string(REGEX REPLACE "(^| )-l([./+-_\\a-zA-Z]*)" " " CoinConf_ldflags "${CoinConf_ldflags}")
  #string(REGEX REPLACE "(^| )-L([./+-_\\a-zA-Z]*)" " " CoinConf_ldflags "${CoinConf_ldflags}")

  #separate_arguments(CoinConf_includedir)

  #set( Coin_CXXFLAGS "${CoinConf_cppflags}" )
  #set( Coin_LINK_FLAGS "${CoinConf_ldflags}" )
  #set( Coin_INCLUDE_DIRS "${CoinConf_includedir}")
  #set( Coin_LINK_DIRS "${CoinConf_ldirs}")
  set( Coin_CXXFLAGS "-I/mingw64/include -I/mingw64/include/Inventor/annex -DCOIN_NOT_DLL")
  set( Coin_LINK_FLAGS "-L/mingw64/lib")
  set( Coin_INCLUDE_DIRS "/mingw64/include")
  set( Coin_LIBS "-lCoin -lopengl32 -lgdi32 -lwinmm -luser32 -lopengl32 -lgdi32 -lwinmm -luser32")
  set( Coin_LIBRARY ${Coin_LINK_FLAGS} ${Coin_LIBS})
  set( Coin_LIBRARY_RELEASE ${Coin_LIBRARY})
  set( Coin_LIBRARY_DEBUG ${Coin_LIBRARY})
  SET(Coin_LIBRARIES ${Coin_LIBRARY})
  SET(Coin_DEFINES -DCOIN_NOT_DLL)
  MESSAGE(STATUS "Found Coin" "${Coin_LIBRARY}")
ELSE(Coin_CONFIG_EXECUTABLE)
	IF(USE_SIM_FIND)
	  # FIXME: Experimental find mechanism. Should be tested on several platforms with several
	  # configurations and someone extended before becomming the one and only thing. 20081105 larsm
	  INCLUDE(SimFind)
	  SIM_FIND(Coin RELEASELIBNAMES Coin Coin3 Coin3s Coin4
			  DEBUGLIBNAMES Coind Coin3d Coin4d
			  INCLUDEFILE Inventor/SbLinear.h)
	ELSE(USE_SIM_FIND)
	  IF(NOT COINDIR)
	    SET(COINDIR $ENV{COINDIR})
	    IF(COINDIR)
	      MESSAGE(STATUS "Setting COINDIR to \"${COINDIR}\" from environment variable")
	    ENDIF(COINDIR)
	  ENDIF(NOT COINDIR)
	  
	  SET(COIN_NAMES Coin Coin3 Coin3s)
	  SET(COIN_NAMES_DEBUG Coind Coin3d)
	  
	  IF(APPLE)
	    # Coin installs as a framework named Inventor on MacOS
	    SET(COIN_NAMES ${COIN_NAMES} Inventor)
	  ENDIF(APPLE)

	  IF(COINDIR)
	    # Look for Coin in environment variable COINDIR
	    FIND_LIBRARY(Coin_LIBRARY_RELEASE NAMES ${COIN_NAMES} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)
	    FIND_LIBRARY(Coin_LIBRARY_DEBUG NAMES ${COIN_NAMES_DEBUG} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)

	    IF(Coin_LIBRARY_RELEASE AND NOT Coin_LIBRARY_DEBUG)
	      SET(Coin_LIBRARY_DEBUG ${Coin_LIBRARY_RELEASE})
	      SET(Coin_LIBRARY       ${Coin_LIBRARY_RELEASE})
	      SET(Coin_LIBRARIES     ${Coin_LIBRARY_RELEASE})
	    ENDIF()

	    IF(Coin_LIBRARY_DEBUG AND NOT Coin_LIBRARY_RELEASE)
	      SET(Coin_LIBRARY_RELEASE ${Coin_LIBRARY_DEBUG})
	      SET(Coin_LIBRARY       ${Coin_LIBRARY_DEBUG})
	      SET(Coin_LIBRARIES     ${Coin_LIBRARY_DEBUG})
	    ENDIF()

	    IF(Coin_LIBRARY_DEBUG AND Coin_LIBRARY_RELEASE)
	      IF(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
		#If the generator supports configuration types then set
		#optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
		SET(Coin_LIBRARY optimized ${Coin_LIBRARY_RELEASE} debug ${Coin_LIBRARY_DEBUG})
	      ELSE()
		#If there are no configuration types and CMAKE_BUILD_TYPE has no value
		#then just use the release libraries
		SET(Coin_LIBRARY ${Coin_LIBRARY_RELEASE})
	      ENDIF()
	      SET(Coin_LIBRARIES optimized ${Coin_LIBRARY_RELEASE} debug ${Coin_LIBRARY_DEBUG})
	    ENDIF()

	    SET(Coin_LIBRARY ${Coin_LIBRARY} CACHE FILEPATH "The Coin library")
	    MARK_AS_ADVANCED(Coin_LIBRARY_RELEASE Coin_LIBRARY_DEBUG)

	    FIND_PATH(Coin_INCLUDE_DIR Inventor/SbLinear.h PATHS ${COINDIR} PATH_SUFFIXES include . NO_DEFAULT_PATH)

	    IF (Coin_INCLUDE_DIR AND Coin_LIBRARY)
	      SET(Coin_FOUND TRUE)
	    ENDIF ()

	    IF (Coin_FOUND)
	      MESSAGE(STATUS "Found Coin" "${Coin_LIBRARY}")
	    ELSE (Coin_FOUND)
	      IF (Coin_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find Coin in ${COINDIR} - try changing the COINDIR environment variable.")
	      ENDIF (Coin_FIND_REQUIRED)
	    ENDIF (Coin_FOUND)

	  ELSE(COINDIR)
	    # pkgconfig supported?
	    INCLUDE(FindPkgConfig)

	    IF(PKG_CONFIG_FOUND)
	      IF (NOT Coin_FIND_QUIETLY)
		MESSAGE(STATUS "Using pkg-config to locate Coin.")
	      ENDIF(NOT Coin_FIND_QUIETLY)

	      pkg_search_module(Coin Coin)
	      IF(Coin_FOUND)
		SET(Coin_LIBRARY ${Coin_LIBRARIES} ${Coin_LDFLAGS})
		SET(Coin_INCLUDE_DIR ${Coin_INCLUDE_DIRS})
		MESSAGE(STATUS "Found Coin" "${Coin_LIBRARY}")
	      ENDIF(Coin_FOUND)
	    ENDIF(PKG_CONFIG_FOUND)

	    # Automatic find, if pkg-config fails
	    IF(NOT Coin_FOUND)
	      FIND_PATH(Coin_INCLUDE_DIR Inventor/SbLinear.h)

	      FIND_LIBRARY(Coin_LIBRARY NAMES ${COIN_NAMES})

	      IF (APPLE)
		FIND_LIBRARY(Ogl_LIBRARY OpenGL)
		SET(Coin_LIBRARY ${Coin_LIBRARY} ${Ogl_LIBRARY})
	      ENDIF(APPLE)
	      IF (Coin_INCLUDE_DIR AND Coin_LIBRARY)
		SET(Coin_FOUND TRUE)
	      ENDIF (Coin_INCLUDE_DIR AND Coin_LIBRARY)
	    ENDIF(NOT Coin_FOUND)


	    # Process stuff
	    IF (Coin_FOUND)
	      MESSAGE(STATUS "Found Coin" "${Coin_LIBRARY}")
	    ELSE (Coin_FOUND)
	      IF (Coin_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find Coin. Try setting the COINDIR environment variable to the root of the Coin 3 installation directory.")
	      ENDIF (Coin_FIND_REQUIRED)
	    ENDIF (Coin_FOUND)
	  ENDIF(COINDIR)

	  # Coin_DEFINES - only on WIN32
	  IF (Coin_FOUND AND WIN32)
	    FIND_FILE(Coin_pc NAMES Coin.pc PATHS ${Coin_INCLUDE_DIR}/../ PATH_SUFFIXES . lib/pkgconfig/ NO_DEFAULT_PATH)
	    MARK_AS_ADVANCED(Coin_pc)
	    IF(EXISTS ${Coin_pc})
	      FILE(READ ${Coin_pc} CoinPC)
	      IF (${CoinPC} MATCHES COIN_DLL)
		MESSAGE(STATUS "Found Coin.pc with -DCOIN_DLL")
		SET(Coin_DEFINES -DCOIN_DLL)
	      ELSE()
		MESSAGE(STATUS "Found Coin.pc with -DCOIN_NOT_DLL")
		SET(Coin_DEFINES -DCOIN_NOT_DLL)
	      ENDIF()
	    ELSE()
	      IF(COIN_NOT_DLL)
		SET(Coin_DEFINES -DCOIN_NOT_DLL)
	      ELSEIF(NOT COIN_DLL)
		SET(Coin_DEFINES -DCOIN_DLL)
		MESSAGE(STATUS "WARNING: Could not find Coin.pc, using -DCOIN_DLL=1. Override or remove this warning using cmake -DCOIN_NOT_DLL=1 or cmake -DCOIN_DLL=1.")
	      ENDIF(COIN_NOT_DLL)
	    ENDIF()
	  ENDIF()

	ENDIF(USE_SIM_FIND)
ENDIF(Coin_CONFIG_EXECUTABLE)
