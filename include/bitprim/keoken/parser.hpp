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
#ifndef BITPRIM_KEOKEN_PARSER_HPP
#define BITPRIM_KEOKEN_PARSER_HPP

#include <ostream>
#include <bitcoin/bitcoin.hpp>
#include <bitprim/keoken/define.hpp>
#include <bitprim/keoken/configuration.hpp>

namespace bitprim { namespace keoken {

/// Parse configurable values from environment variables, settings file, and
/// command line positional and non-positional options.
class BCK_API parser
    : public config::parser
{
public:
    parser(config::settings context);
    parser(configuration const& defaults);

    /// Parse all configuration into member settings.
    virtual 
    bool parse(int argc, char const* argv[], std::ostream& error);

    virtual 
    bool parse_from_file(boost::filesystem::path const& config_path, std::ostream& error);
    
    /// Load command line options (named).
    virtual 
    options_metadata load_options();

    /// Load command line arguments (positional).
    virtual 
    arguments_metadata load_arguments();

    /// Load configuration file settings.
    virtual 
    options_metadata load_settings();

    /// Load environment variable settings.
    virtual 
    options_metadata load_environment();

    /// The populated configuration settings values.
    configuration configured;
};

}} // namespace bitprim::keoken

#endif
