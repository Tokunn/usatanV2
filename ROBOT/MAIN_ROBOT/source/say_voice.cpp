#include "../include/say_voice.hpp"

/*----- talk_usatan() -----*/
void talk_usatan(int p_vn) {
    char cmd[CMD_LEN];

    system(QUIET_CMD);
    sprintf(cmd, VOICE_CMD, p_vn);
    system(cmd);
}

// TODO find pin (4)
