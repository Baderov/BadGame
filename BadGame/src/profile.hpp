#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "pch.h"

class LogDuration
{
private:
	std::chrono::steady_clock::time_point start;
	std::string msg;
public:
	explicit LogDuration(const std::string& msg = "") : msg(msg + ": "), start(std::chrono::steady_clock::now()) {}
	~LogDuration()
	{
		auto finish = std::chrono::steady_clock::now();
		auto dur = finish - start;
		std::cout << "\n" << msg << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << " ms\n";
	}
};


#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#define LOG_DURATION(message) LogDuration UNIQ_ID (__LINE__){message};

#endif