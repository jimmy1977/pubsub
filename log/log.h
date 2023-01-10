/*
 * Created on Thu Jan 05 2023
 * Copyright (c) 2023 
 * Owner : Jimmy Bhaktha 
 */
#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum {
    LOG_ERROR,   // 1
    LOG_WARNING, // 2
    LOG_INFO,    // 3
    LOG_DEBUG,   // 4
};

#ifndef LOG_LEVEL
#if defined(_DEBUG)
#define LOG_LEVEL LOG_DEBUG
#else
#define LOG_LEVEL LOG_INFO
#endif
#endif

#define RED   "\x1B[91m"
#define GRN   "\x1B[92m"
#define YEL   "\x1B[93m"
#define BLU   "\x1B[94m"
#define CYN   "\x1B[96m"
#define RESET "\x1B[0m"

extern unsigned char log_level;
extern const char* log_strings[];

// The BUILD_LOG_LEVEL defines what will be compiled in the executable, in production
// it should be set to LVL_NOTICE

#ifndef LOG_FP
#ifdef stderr
#define LOG_FP stderr
#endif
#endif

#define LOG_SHOULD_I(level) (level <= LOG_LEVEL && level <= log_run_level)

#if defined(_DEBUG)
#define LOG(level, fmt, arg...)                                                                       \
    do {                                                                                              \
        if (LOG_SHOULD_I(level)) {                                                                    \
            time_t t = time(NULL);                                                                    \
            struct tm m = *localtime(&t);                                                             \
            switch (level) {                                                                          \
            case LOG_ERROR:                                                                       \
                fprintf(LOG_FP, RED "%04d-%02d-%02d %02d:%02d:%02d [%s-%s]\t %s:%d: " fmt "\n" RESET, \
                        m.tm_year + 1900, m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec,     \
                        log_strings[level], __FILE__, __FUNCTION__, __LINE__, ##arg);           \
                break;                                                                                \
            case LOG_WARNING:                                                                     \
                fprintf(LOG_FP, YEL "%04d-%02d-%02d %02d:%02d:%02d [%s-%s]\t %s:%d: " fmt "\n" RESET, \
                        m.tm_year + 1900, m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec,     \
                        log_strings[level], __FILE__, __FUNCTION__, __LINE__, ##arg);           \
                break;                                                                                \
            case LOG_INFO:                                                                        \
                fprintf(LOG_FP, GRN "%04d-%02d-%02d %02d:%02d:%02d [%s-%s]\t %s:%d: " fmt "\n" RESET, \
                        m.tm_year + 1900, m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec,     \
                        log_strings[level], __FILE__, __FUNCTION__, __LINE__, ##arg);           \
                break;                                                                                \
            case LOG_DEBUG:                                                                       \
                fprintf(LOG_FP, CYN "%04d-%02d-%02d %02d:%02d:%02d [%s-%s]\t %s:%d: " fmt "\n" RESET, \
                        m.tm_year + 1900, m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec,     \
                        log_strings[level], __FILE__, __FUNCTION__, __LINE__, ##arg);           \
                break;                                                                                \
            }                                                                                         \
            fflush(LOG_FP);                                                                           \
        }                                                                                             \
    } while (0)
#else
#define LOG(level, fmt, arg...)                                                                                      \
    do {                                                                                                             \
        if (LOG_SHOULD_I(level)) {                                                                                   \
            time_t t = time(NULL);                                                                                   \
            struct tm m = *localtime(&t);                                                                            \
            switch (level) {                                                                                         \
            case LOG_ERROR:                                                                                          \
                fprintf(LOG_FP, RED "%04d-%02d-%02d %02d:%02d:%02d [%s]\t %s:%d: " fmt "\n" RESET, m.tm_year + 1900, \
                        m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec, log_strings[level],                  \
                        __FUNCTION__, __LINE__, ##arg);                                                              \
                break;                                                                                               \
            case LOG_WARNING:                                                                                        \
                fprintf(LOG_FP, YEL "%04d-%02d-%02d %02d:%02d:%02d [%s]\t %s:%d: " fmt "\n" RESET, m.tm_year + 1900, \
                        m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec, log_strings[level],                  \
                        __FUNCTION__, __LINE__, ##arg);                                                              \
                break;                                                                                               \
            case LOG_INFO:                                                                                           \
                fprintf(LOG_FP, GRN "%04d-%02d-%02d %02d:%02d:%02d [%s]\t %s:%d: " fmt "\n" RESET, m.tm_year + 1900, \
                        m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec, log_strings[level],                  \
                        __FUNCTION__, __LINE__, ##arg);                                                              \
                break;                                                                                               \
            case LOG_DEBUG:                                                                                          \
                fprintf(LOG_FP, CYN "%04d-%02d-%02d %02d:%02d:%02d [%s]\t %s:%d: " fmt "\n" RESET, m.tm_year + 1900, \
                        m.tm_mon + 1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec, log__strings[level],                 \
                        __FUNCTION__, __LINE__, ##arg);                                                              \
                break;                                                                                               \
            }                                                                                                        \
            fflush(LOG_FP);                                                                                          \
        }                                                                                                            \
    } while (0)
#endif

#define DEBUG(fmt, arg...)   LOG(LOG_DEBUG, fmt, ##arg)
#define INFO(fmt, arg...)    LOG(LOG_INFO, fmt, ##arg)
#define WARNING(fmt, arg...) LOG(LOG_WARNING, fmt, ##arg)
#define ERROR(fmt, arg...)   LOG(LOG_ERROR, fmt, ##arg)

#ifdef __cplusplus
}
#endif
#endif