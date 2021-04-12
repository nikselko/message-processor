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

#include "dev_message_broker.h"

Message_Broker::Message_Broker() : _count(0) {}

void Message_Broker::add(const Message& m_Message)
{
	Messages.push_back(m_Message);																		// Vector push_back is used with count incrementing
	_count++;
}

void Message_Broker::add(TargetType m_target_type, long m_target_id, std::string m_text)
{
	auto tmp_Message = Message::Message(m_target_type, m_target_id, m_text);
	Messages.push_back(tmp_Message);																	// Vector push_back is used with count incrementing
	_count++;
}

const int Message_Broker::count()
{
	return _count;
}

const int Message_Broker::count(long m_target_id)
{
	int tmp_counter = 0;																				// Temporary variable was used to avoid warnings about empty return-cases

	for (int i = 0; i < count(); i++)
	{
		if (Messages.at(i).get_target_id() == m_target_id)
			tmp_counter++;
	}

	return tmp_counter;
}

Message& Message_Broker::peek_message_for(long m_target_id)
{
	size_t tmp_position{};																				// Temporary variable was used to avoid warnings about empty return-cases

	if (count() != 0)
	{
		for (int i = 0; i < count(); i++)
		{
			if (Messages.at(i).get_target_id() == m_target_id)
				tmp_position = i;
		}
	}
	
	return Messages.at(tmp_position);
}

Message& Message_Broker::peek_message_for(std::vector<Message>& m_vec, long m_target_id) const
{
	size_t tmp_position{};																				// Temporary variable was used to avoid warnings about empty return-cases

	for (size_t i = 0; i < m_vec.size(); i++)
	{
		if (m_vec.at(i).get_target_id() == m_target_id)
			tmp_position = i;
	}

	return m_vec.at(tmp_position);
}

Message Message_Broker::pop_message_for(long m_target_id)
{
	Message* tmp_Message = new Message;																	// Temporary Message object for return 

	if (count() != 0)
	{
		for (int i = 0; i < count(); i++)
		{
			if (Messages.at(i).get_target_id() == m_target_id)
			{
				*tmp_Message = Messages.at(i);
				remove_at_index(Messages, i);															// Delete message object
				_count--;
				break;
			}
		}
	}

	return *tmp_Message;
}

void Message_Broker::remove_at_index(std::vector<Message>& vec, int index)								// Proper way to vector remove element
{
	auto to_remove = vec.begin();
	std::advance(to_remove, index);
	vec.erase(to_remove);
}

const void Message_Broker::print()
{
	for (int i = 0; i < count(); i++)
		cout << Messages.at(i).as_string() << endl;
}

const void Message_Broker::print(long m_target_id)
{
	for (int i = 0; i < count(); i++)
	{
		if (Messages.at(i).get_target_id() == m_target_id)
			cout << Messages.at(i).as_string() << endl;
	}
}
