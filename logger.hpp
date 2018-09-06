/*
	Thread-safe simple logger
	
*/
#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <map>

namespace user {


class logger 
{
public:

	using callback = std::function<void(const std::string&)>;

	enum class log_level 
	{
		error = 0,
		warn = 1,
		info = 2,
		debug = 3
	};

	logger(void) = default;

	~logger(void) = default;

	logger(const logger&) = default;

	logger& operator=(const logger&) = default;

	
	void registerHandler(std::string name, callback c);

	void logger::deRegisterHandler(const std::string& name);

	void setLogLevel(log_level l = log_level::debug);

	void debug(const std::string& msg);

	void info(const std::string& msg);

	void warn(const std::string& msg);

	void error(const std::string& msg);


private:
	log_level m_level;
	std::mutex m_mutex;
	std::map<std::string,callback> m_log_handlers;
};



} // namespace cpp_redis
