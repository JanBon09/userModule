#include<ctime>
#include<string>

std::string currentDate() {
	std::time_t cd = time(NULL);

	std::tm data;
	localtime_s(&data, &cd);

	return std::to_string(data.tm_mday) + '.' + std::to_string(data.tm_mon + 1) + '.' + std::to_string(data.tm_year + 1900);
}