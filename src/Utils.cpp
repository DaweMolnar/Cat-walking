#include "Utils.h"
#include <fstream>
#include <time.h>
#define MAX_DATE 12

const std::string
Utils::currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char	buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

const std::string
Utils::get_date()
{
	time_t now;
	char the_date[MAX_DATE];
	the_date[0] = '\0';
	now = time(NULL);
	
	if (now != -1) {
		strftime(the_date, MAX_DATE, "%d_%m_%Y", gmtime(&now));
	}
	
	return std::string(the_date);
}

void
Utils::log_to_file(const std::string &text)
{
	std::string use = text; //Ifndef DEBUG, without this unused variable warning
#ifdef DEBUG
	std::string filename = "log_" + get_date() + ".txt";
	std::ofstream log_file(filename, std::ios_base::out | std::ios_base::app );
	log_file << currentDateTime() << " : " << text << std::endl;
#endif
}
