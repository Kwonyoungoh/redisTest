#include "redisTest.h"


int main()
{
	try
	{
		// Connection Option
		testRedis redis_;

		std::string input;
		while (true) {
			std::getline(std::cin, input);
			if (input == "quit") {
				break;
			}
			redis_.redis_->publish("test", input);
		}

	}
	catch (const Error& e)
	{
		std::cout << "ERROR : " << e.what() << std::endl;
	}

	return 0;
}