#pragma once
#include "Logger.h"

#define LOG_DEBUG(fmt, ...) Logger::getInstance().log(LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  Logger::getInstance().log(LOG_LEVEL_INFO,  __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  Logger::getInstance().log(LOG_LEVEL_WARNING, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) Logger::getInstance().log(LOG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
