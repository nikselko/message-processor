#include <stdlib.h>
#include <stdio.h>

#include "message.h"
#include "message_api.h"
#include "message_broker.h"
#include "message_list.h"

int main(){
    printf("Hello, old C implementation!\n");
    message_t msg0 = create_message(123, dev_air_purifier, "SET ON");
    message_t msg1 = create_message(234, dev_temperature_sensor, "SET ON");
    message_t msg2 = create_message(123, dev_air_purifier, "SET OFF");
    message_t msg3 = create_message(123, dev_air_purifier, "SET ON");
    message_t msg4 = create_message(234, dev_temperature_sensor, "MEASURE");
    message_t msg5 = create_message(123, dev_air_purifier, "SET MODE PURIFY");
    message_t msg6 = create_message(321, dev_heater, "SET ON");

    message_broker_t broker = create_broker();

    push(&broker, &msg0);
    push(&broker, &msg1);
    push(&broker, &msg2);
    push(&broker, &msg3);
    push(&broker, &msg4);
    push(&broker, &msg5);
    push(&broker, &msg6);

    int count = print_messages_for(&broker, 321);
    printf("Printed %d messages.\n", count);

    message_t* msg = NULL;
    long target_id = 123;
    printf("Extracting messages for target_id=%ld\n", target_id);
    while((msg = next_message_for(&broker, target_id))){
        print_message(msg);
        free(msg);
    }
    printf("There are %d messages left fot target_id=%ld\n", count_messages_for(&broker, target_id), target_id);
    printf("THere are %ld messages left in broker\n", broker._count);


    target_id = 321;
    printf("Extracting messages for target_id=%ld\n", target_id);
    while((msg = next_message_for(&broker, target_id))){
        print_message(msg);
        free(msg);
    }
    printf("There are %d messages left fot target_id=%ld\n", count_messages_for(&broker, target_id), target_id);
    printf("There are %ld messages left in broker\n", broker._count);

    const char* file_name = "messages.in";
    printf("\n\nReading the file %s\n\n", file_name);

    if (!lst_open(file_name)){
        printf("Coudn't open file!\n");
        return EXIT_FAILURE;
    }

    const message_t* pmessage = NULL;
    count = 0;
    while((pmessage = lst_read_next())){
        // FIXME: there's some error here about mixing const and non-const
        push(&broker, pmessage);
        ++count;
    }

    lst_close();
    printf("Finished reading the file with %d messages.\n", count);

    printf("There are %ld messages in broker\n", broker._count);



    return EXIT_SUCCESS;
}