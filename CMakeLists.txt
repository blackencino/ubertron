##-*****************************************************************************
## Copyright (c) 2001-2013, Christopher Jon Horvath. All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are met:
##
## 1. Redistributions of source code must retain the above copyright notice,
## this list of conditions and the following disclaimer.
##
## 2. Redistributions in binary form must reproduce the above copyright notice,
## this list of conditions and the following disclaimer in the documentation
## and/or other materials provided with the distribution.
##
## 3. Neither the name of Christopher Jon Horvath nor the names of his
## contributors may be used to endorse or promote products derived from this
## software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
## ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
## LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
## CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
## SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
## INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
## CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
## POSSIBILITY OF SUCH DAMAGE.
##-*****************************************************************************

# This is the top level of the ubertron project. Bins and then libs!
# Also, this top level should include any "global" build configurations
CMAKE_MINIMUM_REQUIRED( VERSION 2.9 )

# Declare an ubertron Project
PROJECT( UBERTRON )

IF (NOT DEFINED QUIET)
  SET(CMAKE_VERBOSE_MAKEFILE TRUE)
ENDIF()

#-******************************************************************************
# RPATH STUFF
#-******************************************************************************

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

#-******************************************************************************
#-******************************************************************************
# UBERTRON
#-******************************************************************************
#-******************************************************************************


# Declare the version
SET( PROJECT_VERSION_MAJOR 1 )
SET( PROJECT_VERSION_MINOR 0 )
SET( PROJECT_VERSION_PATCH 0 )
SET( PROJECT_VERSION
     ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )
SET( VERSION ${PROJECT_VERSION} )

MESSAGE(STATUS "CMAKE SYSTEM NAME = ${CMAKE_SYSTEM_NAME}" )

# Set some debug vs opt flags
IF ( "${CMAKE_BUILD_TYPE}" MATCHES "DebugHard" )
  ADD_DEFINITIONS( -DDEBUG=1 -DDEBUG_HARD=1 -UNDEBUG -O0 -g )
ELSEIF ( "${CMAKE_BUILD_TYPE}" MATCHES "Debug" )
  ADD_DEFINITIONS( -DDEBUG=1 -UDEBUG_HARD -UNDEBUG -O0 -g )
ELSEIF ( "${CMAKE_BUILD_TYPE}" MATCHES "Release" )
  #ADD_DEFINITIONS( -DNDEBUG=1 -UDEBUG_HARD -UDEBUG -O3 -g )
  ADD_DEFINITIONS( -DNDEBUG=1 -UDEBUG_HARD -UDEBUG -O3 )
ENDIF()

# FAST MATH
ADD_DEFINITIONS( -ffast-math )

# Windows flag
SET( WINDOWS FALSE )
IF( "${CMAKE_SYSTEM_NAME}" MATCHES "Windows" )
  MESSAGE( FATAL_ERROR "Windows not supported." )
ENDIF()

# Darwin flag
SET( DARWIN FALSE )
IF( "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin" )
  SET( DARWIN TRUE )
ENDIF()

# Linux flag
SET( LINUX FALSE )
IF( "${CMAKE_SYSTEM_NAME}" MATCHES "Linux" )
  SET( LINUX TRUE )
ENDIF()

#-******************************************************************************
#-******************************************************************************
# SPECIFY C++ 14
#-******************************************************************************
#-******************************************************************************
ADD_DEFINITIONS( "-std=c++1y" )

#-******************************************************************************
#-******************************************************************************
# SPECIFY PLATFORM DEFINES
#-******************************************************************************
#-******************************************************************************

IF( ${DARWIN} )
  ADD_DEFINITIONS( -DPLATFORM_DARWIN -DPLATFORM=DARWIN )
ELSE()
  ADD_DEFINITIONS( -DPLATFORM_LINUX -DPLATFORM=LINUX )
ENDIF()

#-******************************************************************************
#-******************************************************************************
# CMAKE MODULE STUFF
#-******************************************************************************
#-******************************************************************************

# check in the source directory
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/build )

#-******************************************************************************
#-******************************************************************************
# TESTING STUFF
#-******************************************************************************
#-******************************************************************************
# Globally enable testing.
INCLUDE(CTest)
ENABLE_TESTING()
IF(BUILD_TESTING)
  SET(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  MARK_AS_ADVANCED(BUILDNAME)
ENDIF(BUILD_TESTING)
MESSAGE( STATUS "Enabled Testing" )

#-******************************************************************************
#-******************************************************************************
# FPIC STUFF
#-******************************************************************************
#-******************************************************************************

ADD_DEFINITIONS( -fPIC )

#-******************************************************************************
#-******************************************************************************
# WARNINGS MANAGEMENT
#-******************************************************************************
#-******************************************************************************

# Imath and Boost make fairly heavy use of the register keyword, which makes
# for quite a bit of warnings.
ADD_DEFINITIONS( "-Wno-deprecated-register" )


#-******************************************************************************
#-******************************************************************************
# THREAD BUILDING BLOCKS
# We handle these separately from the 'needs', because it's hard to
# use more than one of them on a system at any given time.
#-******************************************************************************
#-******************************************************************************

SET( TBB_ROOT $ENV{TBBROOT} )
SET( TBB_INCLUDE_PATH "${TBB_ROOT}/include" )
SET( TBB_LINK_PATH "${TBB_ROOT}/lib" )
FIND_LIBRARY( UBERTRON_TBB_LIB tbb
	      PATHS
	      ${TBB_LINK_PATH}
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH )
FIND_LIBRARY( UBERTRON_TBBMALLOC_LIB tbbmalloc
	      PATHS
	      ${TBB_LINK_PATH}
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH  )

FIND_LIBRARY( UBERTRON_TBB_DEBUG_LIB tbb_debug
	      PATHS
	      ${TBB_LINK_PATH}
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH  )
FIND_LIBRARY( UBERTRON_TBBMALLOC_DEBUG_LIB tbbmalloc_debug
	      PATHS
	      ${TBB_LINK_PATH}
        NO_DEFAULT_PATH
        NO_CMAKE_ENVIRONMENT_PATH
        NO_SYSTEM_ENVIRONMENT_PATH
        NO_CMAKE_SYSTEM_PATH  )

SET( UBERTRON_TBB_OPT_LIBS
     ${UBERTRON_TBBMALLOC_LIB}
     ${UBERTRON_TBB_LIB} )

SET( UBERTRON_TBB_DEBUG_LIBS
     ${UBERTRON_TBBMALLOC_DEBUG_LIB}
     ${UBERTRON_TBB_DEBUG_LIB} )

IF ( "${CMAKE_BUILD_TYPE}" MATCHES "Debug" )
   SET( UBERTRON_TBB_LIBS ${UBERTRON_TBB_DEBUG_LIBS} )
ELSE()
   SET( UBERTRON_TBB_LIBS ${UBERTRON_TBB_OPT_LIBS} )
ENDIF()

MESSAGE( STATUS "TBB libs: ${UBERTRON_TBB_LIBS}" )

INCLUDE_DIRECTORIES( ${TBB_INCLUDE_PATH} )

#-******************************************************************************
#-******************************************************************************
#-******************************************************************************
# SUBDIRS
#-******************************************************************************
#-******************************************************************************
#-******************************************************************************

# Recurse into src, then bins.
INCLUDE_DIRECTORIES( "${UBERTRON_SOURCE_DIR}/src" )
ADD_SUBDIRECTORY( src )


