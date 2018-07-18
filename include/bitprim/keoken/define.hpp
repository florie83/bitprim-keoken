/**
 * Copyright (c) 2017-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BITPRIM_KEOKEN_DEFINE_HPP
#define BITPRIM_KEOKEN_DEFINE_HPP

#include <bitcoin/bitcoin.hpp>

// We use the generic helper definitions in Bitprim to define BCK_API
// and BCK_INTERNAL. BCK_API is used for the public API symbols. It either DLL
// imports or DLL exports (or does nothing for static build) BCK_INTERNAL is
// used for non-api symbols.

#if defined BCK_STATIC
    #define BCK_API
    #define BCK_INTERNAL
#elif defined BCK_DLL
    #define BCK_API      BC_HELPER_DLL_EXPORT
    #define BCK_INTERNAL BC_HELPER_DLL_LOCAL
#else
    #define BCK_API      BC_HELPER_DLL_IMPORT
    #define BCK_INTERNAL BC_HELPER_DLL_LOCAL
#endif

// Log name.
#define LOG_KEOKEN "keoken"

#endif
