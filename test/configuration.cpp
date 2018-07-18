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
#include <boost/test/unit_test.hpp>
#include <bitprim/keoken.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(configuration_tests)

// constructors
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(configuration__construct1__none_context__expected)
{
    keoken::configuration instance(config::settings::none);
    BOOST_REQUIRE(!instance.help);
    BOOST_REQUIRE(!instance.initchain);
    BOOST_REQUIRE(!instance.settings);
    BOOST_REQUIRE(!instance.version);
    BOOST_REQUIRE_EQUAL(instance.node.sync_peers, 0u);
    BOOST_REQUIRE_EQUAL(instance.node.sync_timeout_seconds, 5u);
}

BOOST_AUTO_TEST_CASE(configuration__construct1__mainnet_context__expected)
{
    keoken::configuration instance(config::settings::mainnet);
    BOOST_REQUIRE(!instance.help);
    BOOST_REQUIRE(!instance.initchain);
    BOOST_REQUIRE(!instance.settings);
    BOOST_REQUIRE(!instance.version);
    BOOST_REQUIRE_EQUAL(instance.node.sync_peers, 0u);
    BOOST_REQUIRE_EQUAL(instance.node.sync_timeout_seconds, 5u);
}

BOOST_AUTO_TEST_CASE(configuration__construct1__testnet_context__expected)
{
    keoken::configuration instance(config::settings::testnet);
    BOOST_REQUIRE(!instance.help);
    BOOST_REQUIRE(!instance.initchain);
    BOOST_REQUIRE(!instance.settings);
    BOOST_REQUIRE(!instance.version);
    BOOST_REQUIRE_EQUAL(instance.node.sync_peers, 0u);
    BOOST_REQUIRE_EQUAL(instance.node.sync_timeout_seconds, 5u);
}

BOOST_AUTO_TEST_CASE(configuration__construct2__none_context__expected)
{
    keoken::configuration instance1(config::settings::none);
    instance1.help = true;
    instance1.initchain = true;
    instance1.settings = true;
    instance1.version = true;
    instance1.node.sync_peers = 42;
    instance1.node.sync_timeout_seconds = 24;

    keoken::configuration instance2(instance1);

    BOOST_REQUIRE(instance2.help);
    BOOST_REQUIRE(instance2.initchain);
    BOOST_REQUIRE(instance2.settings);
    BOOST_REQUIRE(instance2.version);
    BOOST_REQUIRE_EQUAL(instance2.node.sync_peers, 42u);
    BOOST_REQUIRE_EQUAL(instance2.node.sync_timeout_seconds, 24u);
}

BOOST_AUTO_TEST_SUITE_END()
