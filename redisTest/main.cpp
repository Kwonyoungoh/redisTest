#include "redisTest.h"


int main()
{
	try
	{
		// Connection Option
		ConnectionOptions opt_;
		opt_.host = "127.0.0.1";
		opt_.port = 6379;
		opt_.socket_timeout = std::chrono::milliseconds(200);

		auto redis_ = Redis(opt_);

		auto sub_ = redis_.subscriber();

		sub_.on_message([](const std::string& channel, const std::string& msg) {
			std::cout << "channel : " << channel << std::endl;
			std::cout << "msg : " << msg << std::endl;
		});

		sub_.on_meta([](Subscriber::MsgType type, OptionalString channel, long long num) {
			if (type == Subscriber::MsgType::SUBSCRIBE) {
				std::cout << "Successfully subscribe channel: " << *channel << std::endl;
			}
			else if (type == Subscriber::MsgType::UNSUBSCRIBE && num == 0) {
				std::cout << "Successfully unsubscribed channel :" << *channel << std::endl;
			}
			});

		sub_.subscribe("test");

		boost::thread consume_thread([&sub_] {
			while (true) {
				try {
					sub_.consume();
				}
				catch (const Error& e) {
					std::cout << "ComsumeErr :" << e.what() << std::endl;
				}
			}
		});

		std::string input;
		while (true) {
			std::getline(std::cin, input);
			if (input == "quit") {
				break;
			}
		}

	}
	catch (const Error& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}




	return 0;
}
