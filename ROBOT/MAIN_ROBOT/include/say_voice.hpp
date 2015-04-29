#ifndef HEAD_SAY_VOICE
#define HEAD_SAY_VOICE


//standard
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define QUIET_CMD "killall mpg123"  // Stop voice command
#define VOICE_CMD "mpg123 /usr/share/voices/voice%d.mp3 &"    // file path
//#define VOICE_CMD "ls"
#define CMD_LEN   50


void talk_usatan(int p_vn);

#endif // HEAD_SAY_VOICE
