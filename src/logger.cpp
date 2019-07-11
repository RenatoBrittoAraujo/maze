#include "logger.hpp"
#include <iostream>

void Logger::logError(std::string errorModule, std::string errorDescription, std::string sdlError)
{
	std::cout << " [ ERROR ] " << errorModule <<std::endl;
	std::cout << " ==> " << errorDescription << std::endl;
	if(sdlError != "")
	{
		std::cout << " ==> " << sdlError << std::endl;
	}
}

const void Logger::logInfo(std::string info)
{
	std::cout<<" [ INFO ] " << info << std::endl;
}