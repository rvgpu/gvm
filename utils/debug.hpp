/*
 * Copyright © 2024 Sietium Semiconductor.
 */

#pragma once

#include <cstdint>

#define GVM_LOG         0

namespace gvm {

enum class LogLevel {LOG_NONE = 0, LOG_ERROR = 1, LOG_WARNING = 2, LOG_INFO = 3, LOG_DEBUG = 4};

enum LogMask {
    LOG_API       = 1,      //!< (0x1)     API call
    LOG_CMD       = 2,      //!< (0x2)     Kernel and Copy Commands and Barriers
    LOG_WAIT      = 4,      //!< (0x4)     Synchronization and waiting for commands to finish
    LOG_AQL       = 8,      //!< (0x8)     Decode and display AQL packets
    LOG_QUEUE     = 16,     //!< (0x10)    Queue commands and queue contents
    LOG_SIG       = 32,     //!< (0x20)    Signal creation, allocation, pool
    LOG_LOCK      = 64,     //!< (0x40)    Locks and thread-safety code.
    LOG_KERN      = 128,    //!< (0x80)    Kernel creations and arguments, etc.
    LOG_COPY      = 256,    //!< (0x100)   Copy debug
    LOG_COPY2     = 512,    //!< (0x200)   Detailed copy debug
    LOG_RESOURCE  = 1024,   //!< (0x400)   Resource allocation, performance-impacting events.
    LOG_INIT      = 2048,   //!< (0x800)   Initialization and shutdown
    LOG_MISC      = 4096,   //!< (0x1000)  Misc debug, not yet classified
    LOG_AQL2      = 8192,   //!< (0x2000)  Show raw bytes of AQL packet
    LOG_CODE      = 16384,  //!< (0x4000)  Show code creation debug
    LOG_CMD2      = 32768,  //!< (0x8000)  More detailed command info, including barrier commands
    LOG_LOCATION  = 65536,  //!< (0x10000) Log message location
    LOG_MEM       = 131072, //!< (0x20000) Memory allocation
    LOG_MEM_POOL  = 262144, //!< (0x40000) Memory pool allocation, including memory in graphs
    LOG_ALWAYS    = -1,     //!< (0xFFFFFFFF) Log always even mask flag is zero
};

extern void log_printf(LogLevel level, const char *fname, int lineno, const char *format, ...);
extern void log_printf(LogLevel level, const char *fname, int lineno, uint64_t *start, const char *format, ...);

};

// 定义 Log_Print的宏，在GVM_LOG为1的时候可以输出log
#if GVM_LOG

#define GVM_LOG_MASK    gvm::LogMask::LOG_ALWAYS
#define GVM_LOG_LEVEL   gvm::LogLevel::LOG_DEBUG

#define Log_Print(level, mask, format, ...)                                         \
    do {                                                                            \
        if (level <= GVM_LOG_LEVEL) {                                               \
            if ((GVM_LOG_MASK & mask) ||                                            \
                (mask == gvm::LogMask::LOG_ALWAYS)) {                               \
                gvm::log_printf(level, __FILE__, __LINE__, format, ##__VA_ARGS__);  \
            }                                                                       \
        }                                                                           \
    } while (false)

#else

#define Log_Print(level, mask, format, ...)  (void)(0)

#endif // GVM_DEBUG
// {LOG_NONE = 0, LOG_ERROR = 1, LOG_WARNING = 2, LOG_INFO = 3, LOG_DEBUG = 4};
#define Log_Warn(format, ...)   Log_Print(gvm::LogLevel::LOG_WARNING, gvm::LogMask::LOG_ALWAYS, format, ##__VA_ARGS__)
#define Log_Info(format, ...)   Log_Print(gvm::LogLevel::LOG_INFO, gvm::LogMask::LOG_ALWAYS, format, ##__VA_ARGS__)
#define Log_Debug(format, ...)  Log_Print(gvm::LogLevel::LOG_DEBUG, gvm::LogMask::LOG_ALWAYS, format, ##__VA_ARGS__)

#define API_ENTRY()             Log_Print(gvm::LogLevel::LOG_INFO, gvm::LogMask::LOG_API, "[API Entry] %s", __func__)