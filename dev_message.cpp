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

#include "dev_message.h"

long Message::new_id()
{
	static long id = 0x1000;
	return ++id;
}

std::string type_to_str(TargetType m_type)
{
	switch (m_type)																		// Wwitch was used to write less code,
	{
		case TargetType::dev_temperature_sensor: return "temperature_sensor"; break;
		case TargetType::dev_pressure_sensor: return "pressure_sensor"; break;
		case TargetType::dev_humidity_sensor: return "humidity_sensor"; break;
		case TargetType::dev_heater: return "heater"; break;
		case TargetType::dev_air_purifier: return "air_purifier"; break;
		case TargetType::UNKNOWN: return "UNKNOWN"; break;
	}

	return "UNKNOWN";																	// Enumerated logic: if(m_type < TargetType::UNKNOWN) return type_name[m_type]; - was tested and works well
}

long long Message::generate_timestamp()
{
	long long l_time;

	if (time(&l_time))
		return l_time;
	else
		return 0;
}

Message::Message() :
	timestamp{ generate_timestamp() },
	target_type{ TargetType::UNKNOWN },
	target_id{ 0 },
	message_id{ new_id() },
	text{ "" } {}

Message::Message(TargetType m_target_type, long m_target_id, std::string m_text) :
	timestamp{ generate_timestamp() },
	target_type{ m_target_type },
	target_id{ m_target_id },
	message_id{ new_id() },
	text{ m_text } {}

const long Message::get_message_id()
{
	return message_id;
}

const long Message::get_target_id()
{
	return target_id;
}

const TargetType Message::get_target_type()
{
	return target_type;
}

const long long Message::get_timestamp()
{
	return timestamp;
}

const std::string Message::get_text()
{
	return text;
}

void Message::set_text(std::string m_text)
{
	text = m_text;
}

bool Message::is_valid()
{
	if (target_type != TargetType::UNKNOWN)
	{
		if (text != "")
			return true;
		else
			return false;
	}
	else
		return false;
}

std::string Message::as_string()
{
	std::string tmp_return = "[message_id: "
		+ std::to_string(message_id)
		+ ", timestamp: "
		+ std::to_string(timestamp)
		+ ", target_id: "
		+ std::to_string(target_id)
		+ ", target_type: "
		+ type_to_str(target_type)
		+ "]: "
		+ text;

	return tmp_return;
}