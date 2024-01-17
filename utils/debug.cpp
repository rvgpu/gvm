#include <cstdio>
#include <cstdarg>
#include <sstream>
#include <thread>

#include <unistd.h>

#include "debug.hpp"

namespace gvm {

static const char * to_string(gvm::LogLevel level) {
    switch (level) {
        case gvm::LogLevel::LOG_DEBUG: 
            return "  DEBUG";
        case gvm::LogLevel::LOG_WARNING:
            return "WARNING";
        case gvm::LogLevel::LOG_INFO:
            return "   INFO";
        case gvm::LogLevel::LOG_ERROR:
            return "  ERROR";
        default:
            return "   None";
    }
} 

static uint64_t timeNanos() {
    struct timespec tp;
    ::clock_gettime(CLOCK_MONOTONIC, &tp);
    return (uint64_t)tp.tv_sec * (1000ULL * 1000ULL * 1000ULL) + (uint64_t)tp.tv_nsec;
}

void log_printf(LogLevel level, const char* file, int line, const char* format, ...) {
    va_list ap;
    std::stringstream str_thrd_id;
    str_thrd_id << std::hex << std::this_thread::get_id();
    va_start(ap, format);
    char message[4096];
    vsnprintf(message, sizeof(message), format, ap);
    va_end(ap);
    uint64_t timeUs = timeNanos() / 1000ULL;
    fprintf(stdout, "%-7s:%-25s:%-4d:%010lld us: [pid:%-5d tid:0x%s] ==> %s\n", to_string(level), file, line,
        timeUs/1ULL, getpid(), str_thrd_id.str().c_str(), message);
    fflush(stdout);
}

void log_printf(LogLevel level, const char* file, int line, uint64_t* start, const char* format, ...) {
    va_list ap;
    std::stringstream str_thrd_id;
    str_thrd_id << std::hex << std::this_thread::get_id();
    va_start(ap, format);
    char message[4096];
    vsnprintf(message, sizeof(message), format, ap);
    va_end(ap);
    uint64_t timeUs = timeNanos() / 1000ULL;
    if (start == 0 || *start == 0) {
        fprintf(stdout, "%-7s:%-25s:%-4d:%010lld us: [pid:%-5d tid:0x%s] ==>%s\n", to_string(level), file, line,
                timeUs/1ULL, getpid(), str_thrd_id.str().c_str(), message);
    } else {
        fprintf(stdout, "%-7s:%-25s:%-4d:%010lld us: [pid:%-5d tid:0x%s] ==>%s\n: duration: %lld us\n",
                to_string(level), file, line, timeUs/1ULL, getpid(), str_thrd_id.str().c_str(), message,
                (timeUs - *start)/1ULL);
    }
    
    fflush(stdout);
    if (*start == 0) {
        *start = timeUs;
    }
}
};