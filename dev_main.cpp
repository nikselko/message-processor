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

int main()
{
    {                                                                                   /*  MANUAL INITIALIZATION TEST */
        Message_Broker broker_manual_init;

        Message msg0(TargetType::dev_air_purifier, 123, "SET ON");                      // Creations of Message objects
        Message msg1(TargetType::dev_temperature_sensor, 234, "SET ON");                //
        Message msg2(TargetType::dev_air_purifier, 123, "SET OFF");                     //
        Message msg3(TargetType::dev_air_purifier, 123, "SET ON");                      //
        Message msg4(TargetType::dev_temperature_sensor, 234, "MEASURE");               //
        Message msg5(TargetType::dev_air_purifier, 123, "SET MODE PURIFY");             //
        Message msg6(TargetType::dev_heater, 321, "SET ON");                            //

        broker_manual_init.add(msg0);                                                   // Adding Message objects to broker vector
        broker_manual_init.add(msg1);                                                   //
        broker_manual_init.add(msg2);                                                   //
        broker_manual_init.add(msg3);                                                   //
        broker_manual_init.add(msg4);                                                   //
        broker_manual_init.add(msg5);                                                   //
        broker_manual_init.add(msg6);                                                   //

        cout << "-MANUAL INITIALIZATION OUTPUT-" << endl;                               // Print all manual-initialized messages
        cout << "--ALL BROKER MESSAGES" << endl;                                        //
        broker_manual_init.print();                                                     //
        cout << "Messages printed: ";                                                   //
        cout << broker_manual_init.count();                                             //
        cout << "\n\n";                                                                 //

        cout << "--BROKER MESSAGES (target_id: 234)" << endl;                           // Print manual-initialized messages with target_id = 234
        broker_manual_init.print(234);                                                  //
        cout << "Messages printed (target_id: 234): ";                                  //
        cout << broker_manual_init.count(234);                                          //
        cout << "\n\n";                                                                 //

        cout << "--POP 1st MESSAGE IN BROKER " << " (target_id: 234)" << endl;          // Print popped messages with target_id = 234
        cout << broker_manual_init.pop_message_for(234).as_string() << endl;            //
        cout << "\n\n";                                                                 //

        cout << "--ALL BROKER MESSAGES AFTER POPING " << endl;                          // Print all manual-initialized messages after pop
        broker_manual_init.print();                                                     //
        cout << "Messages printed: ";                                                   //
        cout << broker_manual_init.count();                                             //
        cout << "\n\n\n";                                                               //
    }

    {                                                                                   /* FILE INITIALIZATION TEST */
        std::string file_name = "dev_messages.txt";                                     
        Message_Broker broker_file_init;                                                
        Message_Reader reader{ file_name };                                             
                                                                                        
        while (reader.has_next())                                                       // Fixed file-initialization, no more errors with const
        {                                                                               //
            auto msg = reader.read_next();                                              //
            broker_file_init.add(msg);                                                  //
        }                                                                               //
         
        cout << "-FILE INITIALIZATION OUTPUT-" << endl;                                 // Print all file-initialized messages
        cout << "--ALL BROKER MESSAGES FOR "<< file_name << endl;                       //
        broker_file_init.print();                                                       //
        cout << "Messages printed: ";                                                   //
        cout << broker_file_init.count();                                               //
        cout << "\n\n";                                                                 //
        
        cout << "--BROKER MESSAGES FOR " << file_name << " (target_id: 324)" << endl;   // Print file-initialized messages with target_id = 324
        broker_file_init.print(324);                                                    //
        cout << "Messages printed (target_id: 324): ";                                  //
        cout << broker_file_init.count(324);                                            //
        cout << "\n\n";                                                                 //
        
        cout << "--POP 1st MESSAGE FOR " << file_name << " (target_id: 324)" << endl;   // Print popped message with target_id = 324
        cout << broker_file_init.pop_message_for(324).as_string() << endl;              //
        cout << "\n\n";                                                                 //
        
        cout << "--ALL BROKER MESSAGES AFTER POPING " << file_name << endl;             // Print all file-initialized messages after pop
        broker_file_init.print();                                                       //
        cout << "Messages printed: ";                                                   //
        cout << broker_file_init.count();                                               //
        cout << "\n\n";                                                                 //
    }
}