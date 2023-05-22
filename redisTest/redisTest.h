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

class testRedis
{
public:
	// 생성자
	testRedis();
	std::unique_ptr <Redis> redis_;
	// 구독 객체
	std::unique_ptr <Subscriber> sub_;

};

testRedis::testRedis()
{
	try
	{
		// Connection Option
		ConnectionOptions opt_;
		opt_.host = "127.0.0.1";
		opt_.port = 6379;

		redis_ = std::unique_ptr<Redis>(new Redis(opt_));

		sub_ = std::unique_ptr<Subscriber>(new Subscriber(redis_->subscriber()));

		sub_->on_message([](const std::string& channel, const std::string& msg) {
			std::cout << "channel : " << channel << std::endl;
			std::cout << "msg : " << msg << std::endl;
			});
		sub_->on_meta([](Subscriber::MsgType type, OptionalString channel, long long num) {
			if (type == Subscriber::MsgType::SUBSCRIBE) {
				std::cout << "Successfully subscribe channel: " << *channel << std::endl;
			}
			else if (type == Subscriber::MsgType::UNSUBSCRIBE && num == 0) {
				std::cout << "Successfully unsubscribed channel :" << *channel << std::endl;
			}
			});

		sub_->subscribe("test");
	}
	catch (const Error& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}

	boost::thread consume_thread([this] {
		while (true) {
			try {
				sub_->consume();
				std::cout << "Successfully consumed messages from Redis." << std::endl;
			}
			catch (const TimeoutError& timeout_err) {
			}
			catch (const Error& e) {
				std::cout << "ComsumeErr :" << e.what() << std::endl;
			}
		}
		});
	consume_thread.detach();

}