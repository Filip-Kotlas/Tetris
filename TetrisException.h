#ifndef __TETRISEXCEPTION_H__
#define __TETRISEXCEPTION_H__

#include <exception>
#include <iostream>
#include <sstream>

class TetrisException : std::exception
{
private:
	std::string message;
public:
	TetrisException(std::string s) : message(s) {}
	virtual const char* what() const noexcept { return message.c_str(); }
};

#endif