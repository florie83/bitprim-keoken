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
#include <bitprim/keoken/settings.hpp>

#include <bitcoin/bitcoin.hpp>

namespace bitprim {
namespace keoken {

using namespace bc::asio;

settings::settings()
  : sync_peers(0),
    sync_timeout_seconds(5),
    block_latency_seconds(60),
    refresh_transactions(true),
    rpc_port(8332),
    testnet(false),
    subscriber_port(5556),
    compact_blocks_high_bandwidth(true)
{
    rpc_allow_ip.push_back("127.0.0.1");
}

// There are no current distinctions spanning chain contexts.
settings::settings(config::settings context)
  : settings()
{
}

duration settings::block_latency() const
{
    return seconds(block_latency_seconds);
}

} // namespace keoken
} // namespace bitprim
