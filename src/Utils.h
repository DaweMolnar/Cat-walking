#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#define DEBUG
class Utils
{
public:
	static const std::string currentDateTime();
	static const std::string get_date();
	static void log_to_file(const std::string &text);
};
#define LOG(X) Utils::log_to_file(X)
#endif
