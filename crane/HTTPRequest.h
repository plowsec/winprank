#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <windows.h>
#include <wininet.h>
#include <iostream>

#include "Exception.h"

#define POST 1
#define GET 0
#define BUFFER_SIZE 1024
#define HTTP_CURRENT_VERSION  "HTTP/1.1"

#pragma comment(lib, "Wininet.lib")

/*
################

Function : send an HTTP Request

Usage GET :
char URL[1024];
char* geturi = "/index.php?user=%s&pass=%s";
wsprintfA(URL, geturi, user, pass);
HTTPRequest::sendRequest(GET, "perdu.com", URL, NULL, NULL);

Usage POST :
std::string content = "content";
char data[4096] = "";
HTTPRequest request;
char* payload = "content=%s";
wsprintfA(data, payload, content.c_str());
HTTPRequest::sendRequest(POST, "somehost", "/microsoft.php", "Content-Type: application/x-www-form-urlencoded", data);

OR :
//HTTPRequest::sendRequest("POST", Constants::URL_HOST.c_str(), Constants::URL_REPORTS_MANAGER.c_str(), "Content-Type: application/x-www-form-urlencoded", const_cast<char *>(data.c_str()));

TODO :
- Do something useful with the HTTP Response ?
- Refactoring ?

################
*/

class HTTPRequest
{
public:
	HTTPRequest();
	virtual ~HTTPRequest();
	static std::string sendRequest(std::string HTTPMethod, LPCSTR host, LPCSTR url, LPCSTR header, LPSTR data);
protected:
private:
};

#endif // HTTPREQUEST_H
