#include "log.h"
#if defined(_DEBUG)
unsigned char run_level = LOG_DEBUG;
#else
unsigned char run_level = LOG_INFO;
#endif

const char* log_strings[] = {
    "ERR", // 0
    "WRN", // 1
    "INF", // 2
    "DBG"  // 3
};