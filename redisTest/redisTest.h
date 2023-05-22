#pragma once

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>

using json = nlohmann::json;
using boost::asio::ip::udp;
using namespace sw::redis;