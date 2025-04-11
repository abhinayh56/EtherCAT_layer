#ifndef EC_LOGGER_CONSOLE_H
#define EC_LOGGER_CONSOLE_H

#include <iostream>

#define LOG_CONSOLE(msg, next_line)         std::cout << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_INFO(msg, next_line)    std::cout << "INFO   : " << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_ERROR(msg, next_line)   std::cout << "ERROR  : " << msg; if(next_line) {std::cout << std::endl;}
#define LOG_CONSOLE_WARNING(msg, next_line) std::cout << "WARNING: " << msg; if(next_line) {std::cout << std::endl;}

#endif // EC_LOGGER_CONSOLE_H
