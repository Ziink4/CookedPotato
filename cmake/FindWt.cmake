# FindWt.cmake
# From https://gist.github.com/mologie/6755150 with some modifications
# Copyright 2013 Oliver Kuckertz <oliver.kuckertz@mologie.de>
# Licensed under the MIT license:
# http://opensource.org/licenses/MIT
#
# Please note that this script is NOT interchangeable with Wt's original FindWt.cmake.
#
# Usage:
#   FIND_PACKAGE(Wt [REQUIRED] [COMPONENTS ...])
#
# - The component names equal the Wt library names, EXCLUDING THE SERVER LIBRARIES:
#     wt
#     wtdbo
#     wtdbosqlite3
#     wtdbopostgres
#     and other Wt/DBO extensions, as long as they follow the naming scheme
# - Select your server library using the Wt_SERVER variable. You can leave this to the user.
#   Defaults to wthttp.
# - Omitting COMPONENTS selects a few reasonable defaults: wt, wtdbo, wtdbosqlite3
# - It is possible to only select DBO components by setting Wt_DBO_EXCLUSIVE to TRUE
# - In order to use a different set of components for multiple projects, pass a list of all
#   required components to FIND_PACKAGE, and compose a list of libraries required by each of
#   your projects manually. Use the special Wt_SERVER_LIBRARY variable in order to include
#   the server library selected by the user:
#   SET(PROJECT1_WT_LIBRARIES ${Wt_WT_LIBRARY} ${Wt_WTDBO_LIBRARY} ${Wt_SERVER_LIBRARY})
#
# Quick start:
#   FIND_PACKAGE(Wt REQUIRED COMPONENTS wt wtdbo wtdbosqlite3)
#   INCLUDE_DIRECTORIES(${Wt_INCLUDE_DIRS})
#   ADD_EXECUTABLE(app main.cpp)
#   TARGET_LINK_LIBRARIES(app ${Wt_LIBRARIES})
#
# Input variables:
#   Wt_SERVER        - Server implementation library
#
# Output variables:
#   Wt_INCLUDE_DIRS  - Include directories
#   Wt_LIBRARIES     - All requested components

FIND_PATH(Wt_INCLUDE_DIR NAMES Wt/WObject.h PATH_SUFFIXES include)
MARK_AS_ADVANCED(Wt_INCLUDE_DIR)

# Input variables
SET(Wt_SERVER "wthttp" CACHE STRING "Wt server implementation (wthttp, wtfcgi, or wtisapi)")
MARK_AS_ADVANCED(Wt_SERVER)

# Output variables
SET(Wt_INCLUDE_DIRS ${Wt_INCLUDE_DIR})
SET(Wt_LIBRARIES)
SET(Wt_LIBRARIES_FOUND)
SET(Wt_LIBRARIES_MISSING)

# Select the components to find
IF(Wt_FIND_COMPONENTS)
	SET(Wt_LIBRARIES_REQUESTED ${Wt_FIND_COMPONENTS})
ELSE()
	SET(Wt_LIBRARIES_REQUESTED wt)
ENDIF()

IF(NOT Wt_DBO_EXCLUSIVE)
	LIST(APPEND Wt_LIBRARIES_REQUESTED ${Wt_SERVER})
ENDIF()

# Attempt to find each component
FOREACH(_Wt_LIB_NAME ${Wt_LIBRARIES_REQUESTED})
	STRING(TOUPPER "${_Wt_LIB_NAME}" _Wt_LIB_VAR)
	SET(_Wt_LIB_VAR "Wt_${_Wt_LIB_VAR}_LIBRARY")
	SET(${_Wt_LIB_VAR})
	FIND_LIBRARY(${_Wt_LIB_VAR}_DEBUG ${_Wt_LIB_NAME}d HINTS ${Wt_ROOT} PATH_SUFFIXES lib)
	FIND_LIBRARY(${_Wt_LIB_VAR}_RELEASE ${_Wt_LIB_NAME} HINTS ${Wt_ROOT} PATH_SUFFIXES lib)
	MARK_AS_ADVANCED(${_Wt_LIB_VAR}_DEBUG ${_Wt_LIB_VAR}_RELEASE)
	IF(${_Wt_LIB_VAR}_DEBUG)
		SET(${_Wt_LIB_VAR}_DEBUG_FOUND TRUE)
		LIST(APPEND ${_Wt_LIB_VAR} debug ${${_Wt_LIB_VAR}_DEBUG})
	ENDIF()
	IF(${_Wt_LIB_VAR}_RELEASE)
		SET(${_Wt_LIB_VAR}_RELEASE_FOUND TRUE)
		LIST(APPEND ${_Wt_LIB_VAR} optimized ${${_Wt_LIB_VAR}_RELEASE})
	ENDIF()
	IF(${_Wt_LIB_VAR})
		MESSAGE(STATUS "${_Wt_LIB_VAR} = ${${_Wt_LIB_VAR}}")
		SET(${_Wt_LIB_VAR}_FOUND TRUE)
		LIST(APPEND Wt_LIBRARIES_FOUND ${_Wt_LIB_NAME})
		LIST(APPEND Wt_LIBRARIES ${${_Wt_LIB_VAR}})
	ELSE()
		LIST(APPEND Wt_LIBRARIES_MISSING ${_Wt_LIB_NAME})
	ENDIF()
ENDFOREACH(_Wt_LIB_NAME ${Wt_LIBRARIES_REQUESTED})
MESSAGE(STATUS "Wt_LIBRARIES = ${Wt_LIBRARIES}")

# Store the server library's configuration in a separate variable
STRING(TOUPPER "${Wt_SERVER}" _Wt_SERVER_UPPER)
SET(Wt_SERVER_LIBRARY ${Wt_${_Wt_SERVER_UPPER}_LIBRARY})
MESSAGE(STATUS "Wt_SERVER_LIBRARY = ${Wt_SERVER_LIBRARY}")

# Determine the version number from WConfig.h
IF(EXISTS "${Wt_INCLUDE_DIR}/Wt/WConfig.h")
	FILE(STRINGS "${Wt_INCLUDE_DIR}/Wt/WConfig.h" Wt_VERSION_LINE REGEX "^#define WT_VERSION_STR")
	STRING(REGEX REPLACE ".*\"(.*)\".*" "\\1" Wt_VERSION "${Wt_VERSION_LINE}")
ELSE()
	SET(Wt_VERSION "unknown")
ENDIF()

# Report success
IF(NOT Wt_FIND_QUIETLY AND Wt_LIBRARIES_FOUND)
	STRING(REPLACE ";" ", " _Wt_LIBRARIES_FOUND_STR "${Wt_LIBRARIES_FOUND}")
	MESSAGE(STATUS "Found Wt, version ${Wt_VERSION}, with the following libraries: ${_Wt_LIBRARIES_FOUND_STR}")
ENDIF()

# ...and failure
IF((NOT Wt_FIND_QUIETLY OR Wt_FIND_REQUIRED) AND Wt_LIBRARIES_MISSING)
	STRING(REPLACE ";" ", " _Wt_LIBRARIES_MISSING_STR "${Wt_LIBRARIES_MISSING}")
	IF(Wt_FIND_REQUIRED)
		MESSAGE(SEND_ERROR "The following Wt libraries are required but could not be found: ${_Wt_LIBRARIES_MISSING_STR}")
	ELSE()
		MESSAGE("The following Wt libraries could not be found: ${_Wt_LIBRARIES_MISSING_STR}")
	ENDIF()
ENDIF()

# Succeed if all requested libraries have been found
IF(NOT _Wt_LIBRARIES_MISSING)
	SET(Wt_FOUND TRUE)
ENDIF()