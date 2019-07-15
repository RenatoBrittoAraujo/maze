#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger
{
public:

	/*
		Logs an error message in terminal
	 */
	static void logError(std::string errorModule, std::string errorDescription, std::string sdlError = "");

	/*
		Logs an Info message in terminal
	 */
	static const void logInfo(std::string info);

private:

};

#endif