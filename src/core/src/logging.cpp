#include "logging.h"

// TODO I want to write logging
#include <fmt/core.h>

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cassert>

namespace mxc::core
{
	auto printLog(LogLevel level, char const* file, int32_t const line, char const* outMessage) -> void;

	auto stringFormat_v(char* dest, const char* format, va_list* va_listp)  -> int32_t
	{
		if (dest) {
			// Big, but can fit on the stack.
			char buffer[32000];
			int32_t written = vsnprintf(buffer, 32000, format, *va_listp);
			buffer[written] = 0;
			memcpy(dest, buffer, written + 1);

			return written;
		}
		return -1;
	}

    auto logOutput(LogLevel level, char const* file, int32_t const line, char const* message, ...) -> void
	{
		va_list args;
		va_start(args, message);

		// hard limit of 32k characters on log entry
		char outMessage[32000] = {'\0'};

		// format the output string
		stringFormat_v(outMessage, message, &args);
		va_end(args);
		
		printLog(level, file, line, outMessage);
	}

	auto assertCondition(char const* file, int32_t const line, bool condition, char const* message, ...) -> void
	{
		if (!condition)
		{
			va_list args;
			va_start(args, message);
			
			char outMessage[32000] = {'\0'};

			stringFormat_v(outMessage, message, &args);
			va_end(args);
			
			printLog(LogLevel::error, file, line, outMessage);
			
			assert(false);
		}
	}

	// TODO: file should be logged as a "relative path" composed by loglevel, library name, filename, line, 
	// 	     [<loglevel>] mcore/logging.cpp[<line>]: <message>
	auto printLog(LogLevel level, char const* file, int32_t const line, char const* outMessage) -> void
	{
		// set output color according to level and print formatted
		switch (level)
		{
			case LogLevel::info:  fmt::print("\033[37m{} {} [{}]: ", file, line, "INFO");  break; // white info 
			case LogLevel::debug: fmt::print("\033[32m{} {} [{}]: ", file, line, "DEBUG"); break; // green debug
			case LogLevel::warn:  fmt::print("\033[33m{} {} [{}]: ", file, line, "WARN");  break; // yellow warn
			case LogLevel::error: fmt::print("\033[31m{} {} [{}]: ", file, line, "ERROR"); break; // red error
			case LogLevel::trace: fmt::print("\033[37m{} {} [{}]: ", file, line, "TRACE"); break; // white trace
		}
		
		// actually print the stuff
		fmt::print("{}", outMessage);

		// reset output color according to level
		switch (level)
		{
			case LogLevel::debug: [[fallthrough]];
			case LogLevel::warn:  [[fallthrough]];
			case LogLevel::error: [[fallthrough]];
			case LogLevel::info:  [[fallthrough]];
			case LogLevel::trace: fmt::print("\033[37m\n");
		}
	}
}
