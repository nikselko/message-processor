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

#include "dev_message.h"
#include <vector>

class Message_Broker																// Message broker class implementation: -count -messages_vector
{
private:
	int _count;
	std::vector<Message> Messages;

	void remove_at_index(std::vector<Message>& vec, int index);
public:
	Message_Broker();

	void add(const Message&);
	void add(TargetType m_target_type, long m_target_id, std::string m_text);

	const int count();
	const int count(long target_id);

	Message& peek_message_for(long m_target_id);
	Message& peek_message_for(std::vector<Message>& m_vec, long m_target_id) const;	// Overloaded const function cannot operate non const declared vector, so we pass it as argument

	Message pop_message_for(long target_id);


	const void print(long m_target_id);
	const void print();
};

