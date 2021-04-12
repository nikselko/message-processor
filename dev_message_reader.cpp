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

#include "dev_message_reader.h"

Message_Reader::Message_Reader(std::string m_file_name) : file_name{ m_file_name }					// Constructor opens file and fills buffer with it
{
	list.open(m_file_name);

	if (list.is_open())
		buffer.assign((std::istreambuf_iterator<char>(list)), (std::istreambuf_iterator<char>()));

	//list.close();																					// For safety measures file closing can be added in the end of constructor
}

bool Message_Reader::has_next()																		// Bool functions check presence of target_id and whatever target_type, if line meets this requirements it considered valid
{
	auto tmp_line = buffer.substr(0, buffer.find("\n"));

	if (buffer.length() > 1)
	{
		auto id_check = tmp_line.substr(0, tmp_line.find(" "));
		auto long_id_check = stol(id_check);

		if (long_id_check > 0)
		{
			if (tmp_line.find("temperature_sensor")
				|| tmp_line.find("pressure_sensor")
				|| tmp_line.find("humidity_sensor")
				|| tmp_line.find("heater")
				|| tmp_line.find("air_purifier"))
			{
				return true;
			}
			else
			{
				if (list.is_open())																	// If line cannot be read the list considered empty and file is closed
					list.close();
				return false;
			}
		}
		else
		{
			if (list.is_open())
				list.close();
			return false;
		}
	}
	else
	{
		if (list.is_open())
			list.close();
		return false;
	}
}

Message Message_Reader::read_next()																	//PARSING ALGORYTHM DESCRIPTION (based on line deletion from buffer)
{
	auto tmp_line = buffer.substr(0, buffer.find("\n"));											// Temporary line for parsing a message
	auto tmp_line_init_length = tmp_line.length();													// Saving size of it, for deleting this line from the buffer in the end

	auto id_parsed = tmp_line.substr(0, tmp_line.find(" "));										// ID parse 
	long id_to_long = stol(id_parsed);																//
	tmp_line.erase(0, id_parsed.length() + 1);														// Clearing ID from Temporary line

	auto target_type_parsed = tmp_line.substr(0, tmp_line.find(" "));								// Target Type parse
	TargetType tmp_type = TargetType::UNKNOWN;														//
	for (auto i = TargetType::UNKNOWN; i >= TargetType::dev_temperature_sensor; i--)				//
	{																								//
		if (type_to_str(i) == target_type_parsed)													// Comparison is performed on full name, so no mismatches can be met
			tmp_type = i;																			//
	}																								//
	tmp_line.erase(0, target_type_parsed.length() + 1);												// Clearing Target type from Temporary line

	auto text_parsed = tmp_line.substr(0, tmp_line.length());										// Message Text parse
	buffer.erase(0, tmp_line_init_length + 1);														// Clearing initial size of Temporary Line from buffer ('+1' = \n)

	return Message(tmp_type, id_to_long, text_parsed);												// EXAMPLE MESSAGE: 756997 humidity_sensor MEASURE
}

