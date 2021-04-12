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

#include "dev_includes.h"

#if __cplusplus < 199711L										// Cpp version check

template <typename def, typename inner = typename def::type>	// Safe enum for < (C++ < 11)
class safe_enum : public def
{
	typedef inner type;
	inner val;

public:
	safe_enum() {}
	safe_enum(type v) : val(v) {}
	type underlying() const { return val; }

	friend bool operator == (const safe_enum& lhs, const safe_enum& rhs) { return lhs.val == rhs.val; }
	friend bool operator != (const safe_enum& lhs, const safe_enum& rhs) { return lhs.val != rhs.val; }
	friend bool operator <  (const safe_enum& lhs, const safe_enum& rhs) { return lhs.val < rhs.val; }
	friend bool operator <= (const safe_enum& lhs, const safe_enum& rhs) { return lhs.val <= rhs.val; }
	friend bool operator >  (const safe_enum& lhs, const safe_enum& rhs) { return lhs.val > rhs.val; }
	friend bool operator >= (const safe_enum& lhs, const safe_enum& rhs) { return lhs.val >= rhs.val; }
};

class TargetType												// Safe enum implementation for (C++ < 11)
{
	enum type {
		dev_temperature_sensor,
		dev_pressure_sensor,
		dev_humidity_sensor,
		dev_heater,
		dev_air_purifier,
		UNKNOWN
	};
};
typedef safe_enum<TargetType, int> Target_Type;

#else

enum class TargetType											// Enum-Class aka Scoped-Enumeration. Makes it both strongly typed and strongly scoped (C++ > 11)
{
	dev_temperature_sensor,
	dev_pressure_sensor,
	dev_humidity_sensor,
	dev_heater,
	dev_air_purifier,
	UNKNOWN
};

inline TargetType& operator ++ (TargetType& to_increment)		// Scoped-enumeration incrementing operator for Prefix
{
	to_increment = TargetType(unsigned(to_increment) + 1);
	return to_increment;
}

inline TargetType operator ++ (TargetType& to_increment, int)	// Scoped-enumeration incrementing operator for Postfix
{
	TargetType tmp_result = to_increment;
	++to_increment;
	return tmp_result;
}

inline TargetType& operator -- (TargetType& to_increment)		// Scoped-enumeration decrementing operator for Prefix
{
	to_increment = TargetType(unsigned(to_increment) - 1);
	return to_increment;
}

inline TargetType operator -- (TargetType& to_increment, int)	// Scoped-enumeration decrementing operator for Postfix
{
	TargetType tmp_result = to_increment;
	--to_increment;
	return tmp_result;
}

#endif

std::string type_to_str(TargetType m_type);						// Translate function (non class)

class Message													// Message class implementation: -msg_id -trg_id -trg_t -ts -txt
{
private:
	long  message_id; 
	long target_id; 
	TargetType target_type;
	long long timestamp;
	std::string text;

	static long new_id();
	long long generate_timestamp();

public:
	Message();
	Message(TargetType m_target_type, long m_target_id, std::string m_text);

	const long get_message_id();
	const long get_target_id();

	const TargetType get_target_type();
	const long long get_timestamp();

	const std::string get_text();
	void set_text(std::string m_text);

	bool is_valid();
	std::string as_string();
};
