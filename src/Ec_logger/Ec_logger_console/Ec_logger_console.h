#ifndef EC_LOGGER_CONSOLE_H
#define EC_LOGGER_CONSOLE_H

#include <iostream>

#define LOG_CONSOLE(msg, next_line)         std::cout << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_INFO(msg, next_line)    std::cout << "INFO   : " << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_ERROR(msg, next_line)   std::cout << "ERROR  : " << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_WARNING(msg, next_line) std::cout << "WARNING: " << msg; if(next_line) {std::cout << std::endl;}

#define LOG_CONSOLE_SOURCE(msg_source, msg, next_line)         std::cout << "(" << msg_source << ") " msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_SOURCE_INFO(msg_source, msg, next_line)    std::cout << "INFO   : (" << msg_source << ") " << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_SOURCE_ERROR(msg_source, msg, next_line)   std::cout << "ERROR  : (" << msg_source << ") " << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_SOURCE_WARNING(msg_source, msg, next_line) std::cout << "WARNING: (" << msg_source << ") " << msg; if(next_line) {std::cout << std::endl;}

#endif // EC_LOGGER_CONSOLE_H
