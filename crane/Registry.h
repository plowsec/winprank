/**
* \file Registry.h
* \brief Registry module for manipulating Windows registry
* \version 0.2
* \date 02.09.2015
*
* Module to access registry and allow to read, write and modify key
*
*/

#ifndef REGISTRY_H_
#define REGISTRY_H_

#include <windows.h>
#include <string>

// \def MAX_VALUE_LENGTH Define maximum value length
#define MAX_VALUE_LENGTH 2048

/**
* \class Registry Registry.h
* \brief class offering registry key access functionalities
*/
class Registry
{
private:

public:

	/**
	* \brief Function to set a value in a specific hkex, subkey ans key name
	* \param[in] HK 		Is the HKEY to access
	* \param[in] key		Is the subkey to access
	* \param[in] name		Is the keyname to read
	* \param[in] value		Is the value to set
	* \return PROCESS_SUCCEED in case of success and PROCESS_FAILED in other cases
	*/
	static int setStringValue(HKEY HK, const std::string& key, const std::string& name, const std::string& value);

	/**
	* \brief Function to get a value in a specific hkex, subkey ans key name
	* \param[in] HK 		Is the HKEY to access
	* \param[in] key		Is the subkey to access
	* \param[in] name		Is the keyname to read
	* \param[out] value	Is the destination string for getted value
	* \return PROCESS_SUCCEED in case of success and PROCESS_FAILED in other cases
	*/
	static int getStringValue(HKEY HK, const std::string& key, const std::string& name, std::string& value);
	static long removeAppFromStartup(std::string appName);
};

#endif /* REGISTRY_H_ */
