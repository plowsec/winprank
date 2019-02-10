/**
* \file Registry.cpp
* \brief Registry module for manipulating Windows registry
* \version 0.2
* \date 02.09.2015
*
* Module to access registry and allow to read, write and modify key
*
*/
#include "stdafx.h"

#include "Registry.h"
#include <iostream>

#define PROCESS_FAILED -1
#define PROCESS_SUCCEED 0

int Registry::setStringValue(HKEY HK, const std::string& key, const std::string& name, const std::string& value)
{
	DWORD lRv, dwDisposition;
	HKEY hKey;

	//UNDEFINE YOUR UNICODE PLEASE

	/*// Convert key from string to WCHAR string
	std::wstring wKey;
	wKey.assign(key.begin(), key.end());

	// Convert name from string to WCHAR string
	std::wstring wName;
	wName.assign(name.begin(), name.end());

	// Convert value from string to WCHAR string
	std::wstring wValue;
	wValue.assign(value.begin(), value.end());*/

	// Open given key and check if succeed
	lRv = RegOpenKeyEx(HK, key.c_str(), 0, KEY_WRITE, &hKey);
	if (lRv != ERROR_SUCCESS)
	{
		// Create a key if it did not exist
		lRv = RegCreateKeyEx(HK, key.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);

		// Check if creation succeed
		if (lRv != ERROR_SUCCESS)
		{
			return PROCESS_FAILED;
		}
	}

	// Write name, value in registry key
	lRv = RegSetValueEx(hKey, name.c_str(), 0, REG_SZ, (const BYTE *)value.c_str(), value.length()*sizeof(DWORD));

	// Close regitry key
	lRv = RegCloseKey(hKey);

	return PROCESS_SUCCEED;
}

int Registry::getStringValue(HKEY HK, const std::string& key, const std::string& name, std::string& value)
{
	DWORD lRv;
	HKEY hKey;
	WCHAR buffer[MAX_VALUE_LENGTH];
	DWORD bufLen = sizeof(buffer);

	// Convert key from string to WCHAR string
	std::wstring wKey;
	wKey.assign(key.begin(), key.end());

	// Convert name from string to WCHAR string
	std::wstring wName;
	wName.assign(name.begin(), name.end());

	// Open given key and check if succeed
	lRv = RegOpenKeyEx(HK, key.c_str(), 0, KEY_READ, &hKey);
	if (lRv != ERROR_SUCCESS)
	{
		return PROCESS_FAILED;
	}

	// Read key
	lRv = RegQueryValueEx(hKey, name.c_str(), 0, NULL, (LPBYTE)buffer, &bufLen);
	if (lRv != ERROR_SUCCESS)
	{
		return PROCESS_FAILED;
	}

	// Close regitry key
	lRv = RegCloseKey(hKey);

	// Convert WCHAR string to string
	value = "";
	std::wstring wValue(buffer);
	value.assign(wValue.begin(), wValue.end());

	return PROCESS_SUCCEED;
}

long Registry::removeAppFromStartup(std::string appName) {
	HKEY hkey = HKEY_LOCAL_MACHINE;
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
	long result = RegDeleteValue(hkey, appName.c_str());
	RegCloseKey(hkey);
	return result;
}