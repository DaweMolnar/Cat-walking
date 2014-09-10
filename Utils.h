#ifndef LOGGER_H
#define LOGGER_H
#include <string>
class Utils
{
public:
	static const std::string currentDateTime();
	static const std::string get_date();
	static void log_to_file(const std::string &text);
};
#endif
