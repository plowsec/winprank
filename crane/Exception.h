#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
#include "StringUtils.h"

class Exception : public std::exception
{
public:
	Exception(std::string const& error = "", int errorCode = -1) throw() : m_message(error), m_errorCode(errorCode) {}
	virtual ~Exception() throw() {}

	virtual const char* what() const throw() {
		std::string returnedString = m_message + StringUtils::intToString(m_errorCode);
		return returnedString.c_str();
	}

private:
	std::string m_message;
	int m_errorCode;
};

#endif // EXCEPTION_H

