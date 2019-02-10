#include "stdafx.h"

#include "HTTPRequest.h"

HTTPRequest::HTTPRequest() {}
HTTPRequest::~HTTPRequest() {}

std::string HTTPRequest::sendRequest(std::string HTTPMethod, LPCSTR host, LPCSTR url, LPCSTR header, LPSTR data) {

	//source : http://securityblog.gr/1823/http-post-and-get-requests-with-wininet-and-c/

	/*
	std::string HTTPMethod : GET | POST
	LPCSTR host : perdu.com
	LPCSTR url : /index.php?blablabla
	LPCSTR header : HTTP Headers
	LPSTR data : POST DATA
	*/

	HINTERNET hInternet = InternetOpenW(L"curl", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (hInternet == NULL) {
		throw Exception("InternetOpenW failed with error code ", GetLastError());
	}

	else {
		HINTERNET hConnect = InternetConnectA(hInternet, host, INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

		if (hConnect == NULL) {
			throw Exception("InternetConnectW failed with error code ", GetLastError());
		}

		else {
			//const wchar_t* parrAcceptTypes[] = { L"text/*", NULL };
			HINTERNET hRequest = HttpOpenRequestA(hConnect, HTTPMethod.c_str(), url, HTTP_CURRENT_VERSION, NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_HYPERLINK | INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
				INTERNET_FLAG_IGNORE_CERT_DATE_INVALID |
				INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
				INTERNET_FLAG_NO_AUTH |
				INTERNET_FLAG_NO_CACHE_WRITE |
				INTERNET_FLAG_NO_UI |
				INTERNET_FLAG_PRAGMA_NOCACHE |
				INTERNET_FLAG_RELOAD, NULL);

			if (hRequest == NULL) {
				throw Exception("HttpOpenRequestW failed with error code ", GetLastError());
			}
			else {
				int datalen = 0;

				if (data != NULL)
					datalen = strlen(data);

				int headerlen = 0;
				if (header != NULL)
					headerlen = strlen(header);

				BOOL bRequestSent = HttpSendRequestA(hRequest, header, headerlen, data, datalen);

				if (!bRequestSent) {
					throw Exception("HttpSendRequestW failed with error code ", GetLastError());
				}
				else {
					std::string strResponse;
					const int nBuffSize = BUFFER_SIZE;
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0) {
						bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
						strResponse.append(buff, dwBytesRead);
					}
					return strResponse;
				}
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}
}
