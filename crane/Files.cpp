#include "stdafx.h"
#include "Files.h"

Files::Files() {}
Files::~Files() {}

std::string Files::readFile(std::string path) {

	std::string content;
	std::string line;
	std::ifstream myfile(path.c_str());
	if (myfile.is_open()) {

		while (getline(myfile, line)) {
			content += line;
		}
		myfile.close();
		return content;
	}

	perror("is_open() failed, error state");
	return "error-file";
}

void Files::writeFile(std::string path, std::string content) {
	std::ofstream file(path.c_str());
	std::string my_string = content;
	file << my_string;
}
std::vector<std::string> Files::getFileNamesInDirectory(std::string directory) {

	std::vector<std::string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) {
			files.push_back(fileData.cFileName);
		}
	}

	FindClose(hFind);
	return files;
}

std::string Files::getPathFromCSIDL(int id) {

	TCHAR returnedPath[MAX_PATH];
	std::string returnedString = "";
	HRESULT hr = SHGetFolderPath(NULL, id | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, returnedPath);

	if (SUCCEEDED(hr)) {
		std::string tempReturnedPath = returnedPath;
		return tempReturnedPath;
	}

	return std::string();
}

std::string Files::getTempDir() {

	char *buffer = (char*)malloc(MAX_LENGTH);
	std::string temp_dir;

	if (GetTempPath(MAX_LENGTH, buffer) != 0) {
		temp_dir = std::string(buffer);
		free(buffer);
		return temp_dir;
	}

	free(buffer);
	throw std::string("getTempDir failed");
}
