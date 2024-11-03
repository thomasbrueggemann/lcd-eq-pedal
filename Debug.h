#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 0   // SET TO 0 OUT TO REMOVE TRACES

#if DEBUG
#define D_SerialBegin(...) Serial.begin(__VA_ARGS__);
#define D_print(...)    D_print(__VA_ARGS__)
#define D_println(...)  D_println(__VA_ARGS__)
#else
#define D_SerialBegin(...)
#define D_print(...)
#define D_write(...)
#define D_println(...)
#endif

#endif 