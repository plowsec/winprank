#include "stdafx.h"
#include "Logger.h"

Logger::Logger() {}
Logger::~Logger() {}

std::string Logger::m_report = "";


void Logger::addSeparator() {

	//appends a single separator to improve visibility in the log file

	Logger::m_report += "<br><br>" + std::string(12, '-') + "<br><br>";
}

void Logger::addTitle(std::string title) {

	//appends a title to the log file

	Logger::m_report += "<h1>" + title + std::string(5, '-') + "</h1>";

}

void Logger::addSection(std::string title) {

	// a section is not as big as a title :P
	Logger::m_report += "<br><h3>" + title + "</h3><br>";
}

void Logger::addEntry(std::string entry) {
	//in case we need to format something before adding it to the log file

	Logger::m_report += entry + "<br>";
}

void Logger::addError(std::string message) {

	//in case something went wrong, log it
	Logger::m_report += "<p style='color:red;'>" + message + "</p>";

}

void Logger::uploadReport() {

	//uploads the log file  to the server (specified in Constants.h)
	//std::string data = Constants::URL_REPORTS_PARAM + Logger::m_report;

	try {
		//HTTPRequest::sendRequest("POST", Constants::URL_HOST.c_str(), Constants::URL_REPORTS_MANAGER.c_str(), "Content-Type: application/x-www-form-urlencoded", const_cast<char *>(data.c_str()));

		std::string content = Logger::m_report;
		char data[8096] = "";
		HTTPRequest request;
		char* payload = "file_content=%s";
		wsprintfA(data, payload, content.c_str());
		HTTPRequest::sendRequest(std::string("POST"), Constants::URL_HOST.c_str(), Constants::URL_REPORTS_MANAGER.c_str(), "Content-Type: application/x-www-form-urlencoded", data);
	}

	catch (std::exception const& e) {

		//obviously the report cannot be uploaded for x reasons, so print the error and dump log file to disk (TODO)

		std::cout << e.what() << std::endl;
		std::cout << "REPORT\n" << std::endl;
		std::cout << Logger::m_report << std::endl;
	}
}

void Logger::dumpToDisk() {
	std::string temp_path = Files::getTempDir();
	Files::writeFile(temp_path + "\\scout_report.txt", Logger::m_report);
	//TODO exception
}
