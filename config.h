#ifndef CONFIG_H
#define CONFIG_H

#ifdef NY
    #define MAX_CHAR_ISSUING_AGENCY 36
    #define MAX_CHAR_INFRACTION_NAME 31
#else
    #define MAX_CHAR_ISSUING_AGENCY 14
    #define MAX_CHAR_INFRACTION_NAME 51
#endif

#endif // CONFIG_H
