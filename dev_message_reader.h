/******************************************************************************
*                                                                             *
*   Program : Message processor                                               *
*                                                                             *
*   Date : 11 / 04 / 2021                                                     *
*                                                                             *
*   Programmer : Nikita Seliverstov (nikselko)                                *
*                                                                             *
*                                                                             *
******************************************************************************/

#pragma once

#include "dev_message_broker.h"
#include <fstream>

class Message_Reader						// Message reader class implementation: -file -buffer -file_name
{
private:
	ifstream list;
	std::string buffer;
	const std::string file_name;

public:
	Message_Reader(std::string m_file_name); // Constructor opens file

	bool has_next();						 // If next line is not readable closes file (tried to implement destructor with flcose() but it caused some errors)
	Message read_next();
};

