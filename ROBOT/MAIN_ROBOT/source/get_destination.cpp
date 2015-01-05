#include "../include/get_destination.hpp"

#include <string.h>
//#include <iostream> // #=# DEBUG #=#



/*----- initialize() -----*/
Destination::Destination() {
    std::string temp_pose_string[] = { "$MAJOKO",
                                       "$OBAKE_",
                                       "$KAIDAN",
                                       "$NEKO__",
                                       "$KING__",
                                       "$BRUNA_"  };
    //                         {M, O, K, N, K, B};
    int temp_pose_position[] = {1, 2, 3, 4, 5, 6};
    all_count = 8; // TODO count check
    fd = open(XBEE_SERIAL_PORT, O_RDWR);

    unsigned int size = sizeof(temp_pose_string) / sizeof(int);
    for (unsigned int i = 0; i < size; i++) {
        pose_string[i] = temp_pose_string[i];
        pose_position[i] = temp_pose_position[i];
    }
}

/*----- get_position() -----*/
int Destination::get_position() {
    int position;
    do {
        recive_serial(&string_destination);
        position = comv_destination_string2int(pose_string, &string_destination);
        //std::cout << "[return]: " << position << '\n'; #=# DEBUG #=#
    } while (!position);
    return position;
}

/*----- get_all_count() -----*/
int Destination::get_all_count() {
    return all_count;
}


/*----- recive_serial() -----*/
void Destination::recive_serial(std::string* string_destination) {
    char char_destination[10];
    read(fd, char_destination, 7);
    *string_destination = char_destination;
}

/*----- comv_destination_string2int() -----*/
int Destination::comv_destination_string2int(
        const std::string* pose_string, const std::string* string_destination) {
    //std::cout << ">'" << *string_destination << "'<" << '\n';     // #=# DEBUG #=#
    int return_position = 0;
    unsigned int size = sizeof(pose_position) / sizeof(int);
    for (unsigned int i = 0; i < size; i++) {
        if (string_destination[0][3] == pose_string[i][3]) {
            return_position = pose_position[i];
            //std::cout << "[[Find]]: " << pose_string[i] << " Char is: " << string_destination[0][3] << " and: " << pose_string[i][3];   // #=# DEBUG #=#
            //std::cout << "\t[Return]: " << return_position << "\n\n";   // #=# DEBUG #=#
        }
    }
    return return_position;
}
