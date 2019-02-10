#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <vector>
#include <string>

#include "Constants.h"
#include "HTTPRequest.h"
#include "Files.h"

class Logger
{
public:
	Logger();
	virtual ~Logger();

	static void addSeparator();
	static void addTitle(std::string title);
	static void addSection(std::string title);
	static void addEntry(std::string entry);
	static void addError(std::string message);
	static void uploadReport();
	static void dumpToDisk();

	//i want it to be private, but too much bug
	static std::string m_report;

};

#endif // LOGGER_H
