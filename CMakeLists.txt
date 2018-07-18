#
# Copyright (c) 2017 Bitprim developers (see AUTHORS)
#
# This file is part of Bitprim.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.4)

# bitprim-keoken
#==============================================================================
project(bitprim-keoken
        VERSION 0
        LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++11 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process options.
#==============================================================================

# Implement --use-conan
#------------------------------------------------------------------------------
option(USE_CONAN "Use Conan Build Tool." OFF)
option(NO_CONAN_AT_ALL "Conan totally disabled." OFF)

if (NO_CONAN_AT_ALL)
  set(USE_CONAN OFF)
endif()

# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" OFF)

# Implement POSITION_INDEPENDENT_CODE
#------------------------------------------------------------------------------
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)


# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)


set(BITPRIM_PROJECT_VERSION "-" CACHE STRING "Specify the Bitprim Project Version.")
# message(${BITPRIM_PROJECT_VERSION})


set(MICROARCHITECTURE "x86_64" CACHE STRING "Specify the Cryptocurrency (x86_64|...).")
message( STATUS "Bitprim: Compiling for ${MICROARCHITECTURE}")
# add_definitions(-DBITPRIM_MICROARCHITECTURE=${MICROARCHITECTURE})
# add_definitions(-DBITPRIM_MICROARCHITECTURE_STR="${MICROARCHITECTURE}")


set(CURRENCY "BCH" CACHE STRING "Specify the Cryptocurrency (BCH|BTC|LTC).")

if (${CURRENCY} STREQUAL "BCH")
  add_definitions(-DBITPRIM_CURRENCY_BCH)
elseif (${CURRENCY} STREQUAL "BTC")
  add_definitions(-DBITPRIM_CURRENCY_BTC)
elseif (${CURRENCY} STREQUAL "LTC")
  add_definitions(-DBITPRIM_CURRENCY_LTC)
else()
  message(FATAL_ERROR "Invalid Cryptocurrency: ${CURRENCY}")
endif()

message(STATUS "Bitprim: Cryptocurrency: ${CURRENCY}")


# Conan infrastructure
#==============================================================================
if(EXISTS ${CMAKE_SOURCE_DIR}/ci_utils/cmake/bitprimbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/ci_utils/cmake/bitprimbuildinfo.cmake)
else()
    message( STATUS "bitprimbuildinfo doent exists")
endif()



# Check dependencies.
#==============================================================================
#------------------------------------------------------------------------------
if (NO_CONAN_AT_ALL)
  # Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
  #------------------------------------------------------------------------------
  if (NOT ENABLE_SHARED)
    set(Boost_USE_STATIC_LIBS ON)
  endif()

  if (MSVC)
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS atomic chrono date_time filesystem iostreams locale log log_setup program_options regex system thread unit_test_framework
    )
  else()
    find_package(
      Boost 1.56.0 REQUIRED
      COMPONENTS chrono date_time filesystem iostreams locale log program_options regex system thread unit_test_framework
    )
  endif()
endif()

if (NOT USE_CONAN)
  # Require bitprim-blockchain of at least version 0 and output ${bitprim_keoken_CPPFLAGS/LIBS/PKG}.
  #------------------------------------------------------------------------------
  if (NOT TARGET bitprim-blockchain)
    find_package(bitprim-blockchain 0 REQUIRED)
  endif()
endif()


# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)

# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)

include(BitprimTools)


# Warn on all stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Warn on extra stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

# Be really annoying.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

# Conform to style.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)

# Conflict in stdlib under clang. Enabled in clang only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)

# Clean up boost 1.55 headers. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)

# Protect stack.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector _has_stack_protector_flag)

# Protect stack comprehensively.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)

# Hide internal functions from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)

# Hide inlines from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

# Target Windows Vista. Enabled in msvc only.
#------------------------------------------------------------------------------
if (MSVC) # OR MINGW)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# Build
#==============================================================================

# src/bitprim-keoken.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
    set(MODE SHARED)
endif()

add_library(bitprim-keoken ${MODE}
        src/configuration.cpp
        src/full_node.cpp
        src/parser.cpp
        src/settings.cpp
        src/version.cpp

        src/protocols/protocol_block_in.cpp
        src/protocols/protocol_block_out.cpp
        src/protocols/protocol_block_sync.cpp
        src/protocols/protocol_header_sync.cpp
        src/protocols/protocol_transaction_in.cpp
        src/protocols/protocol_transaction_out.cpp

        src/sessions/session_block_sync.cpp
        src/sessions/session_header_sync.cpp
        src/sessions/session_inbound.cpp
        src/sessions/session_manual.cpp
        src/sessions/session_outbound.cpp


        src/utility/check_list.cpp
        src/utility/header_list.cpp
        src/utility/performance.cpp
        src/utility/reservation.cpp
        src/utility/reservations.cpp
)


if (ENABLE_POSITION_INDEPENDENT_CODE) 
  set_property(TARGET bitprim-keoken PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)

  
target_include_directories(bitprim-keoken PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)


target_compile_definitions(bitprim-keoken PUBLIC -DBITPRIM_PROJECT_VERSION="\\"${BITPRIM_PROJECT_VERSION}\\"") #TODO(fernando): manage with Conan????

if (NOT ENABLE_SHARED)
  target_compile_definitions(bitprim-keoken PUBLIC -DBCK_STATIC -DBCB_STATIC -DBCD_STATIC -DBCT_STATIC -DBC_STATIC)
endif()

if (NOT MSVC)
  target_compile_definitions(bitprim-keoken PUBLIC -DSYSCONFDIR=\"${SYSCONFDIR}\")
endif()




if (NOT USE_CONAN)
  target_link_libraries(bitprim-keoken PUBLIC bitprim-blockchain bitprim-network)
endif()

if (NOT NO_CONAN_AT_ALL)
  target_link_libraries(bitprim-keoken PUBLIC ${CONAN_LIBS})
endif()



if (USE_CONAN)
  if (MINGW)
    target_link_libraries(bitprim-keoken PUBLIC ws2_32 wsock32) #TODO(fernando): manage with Conan
  endif()
endif()

_group_sources(bitprim-keoken "${CMAKE_CURRENT_LIST_DIR}")


# Tests
#==============================================================================
if (WITH_TESTS)
  enable_testing()
endif()

# local: test/bitprim_keoken_test
#------------------------------------------------------------------------------
if (WITH_TESTS)
  add_executable(bitprim_keoken_test
          test/check_list.cpp
          test/configuration.cpp
          test/header_list.cpp
          test/main.cpp
          test/node.cpp
          test/performance.cpp
          test/reservation.cpp
          test/reservations.cpp
          test/settings.cpp
          test/utility.cpp
          test/utility.hpp)
  target_link_libraries(bitprim_keoken_test PUBLIC bitprim-keoken)
  _group_sources(bitprim_keoken_test "${CMAKE_CURRENT_LIST_DIR}/test")

  _add_tests(bitprim_keoken_test
          configuration_tests
          node_tests
          #header_queue_tests
          performance_tests
          #reservation_tests
          #reservations_tests
          settings_tests)
endif()


# Install
#==============================================================================
install(TARGETS bitprim-keoken
        EXPORT bitprim-keoken
        ARCHIVE DESTINATION lib)


set(_bitprim_headers
        # include_bitcoin_HEADERS =
        bitprim/keoken.hpp
        # include_bitprim_keoken_HEADERS =
        bitprim/keoken/configuration.hpp
        bitprim/keoken/define.hpp
        bitprim/keoken/full_node.hpp
        bitprim/keoken/parser.hpp
        bitprim/keoken/settings.hpp
        bitprim/keoken/version.hpp
        # include_bitprim_keoken_protocols_HEADERS =
        bitprim/keoken/protocols/protocol_block_in.hpp
        bitprim/keoken/protocols/protocol_block_out.hpp
        bitprim/keoken/protocols/protocol_block_sync.hpp
        bitprim/keoken/protocols/protocol_header_sync.hpp
        bitprim/keoken/protocols/protocol_transaction_in.hpp
        bitprim/keoken/protocols/protocol_transaction_out.hpp
        # include_bitprim_keoken_sessions_HEADERS =
        bitprim/keoken/sessions/session.hpp
        bitprim/keoken/sessions/session_block_sync.hpp
        bitprim/keoken/sessions/session_header_sync.hpp
        bitprim/keoken/sessions/session_inbound.hpp
        bitprim/keoken/sessions/session_manual.hpp
        bitprim/keoken/sessions/session_outbound.hpp
        # include_bitprim_keoken_utility_HEADERS =
        bitprim/keoken/utility/check_list.hpp
        bitprim/keoken/utility/header_list.hpp
        bitprim/keoken/utility/performance.hpp
        bitprim/keoken/utility/reservation.hpp
        bitprim/keoken/utility/reservations.hpp)
foreach (_header ${_bitprim_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT bitprim-keoken
        FILE "${CMAKE_CURRENT_BINARY_DIR}/bitprim-keokenTargets.cmake")
export(PACKAGE bitprim-keoken)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT bitprim-keoken
        FILE bitprim-keokenTargets.cmake
        DESTINATION ${_config_package_location})

configure_file(bitprim-keokenConfig.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-keokenConfig.cmake"
        @ONLY)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-keokenConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)

install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-keokenConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/bitprim-keokenConfigVersion.cmake"
        DESTINATION ${_config_package_location})
