#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <map>
#include <functional>
#include <deque>
#include <condition_variable>
#include <algorithm>

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

	void RegisterHandler(std::string name, callback c);

	void DeRegisterHandler(const std::string& name);

	void SetLogLevel(log_level l = log_level::debug);

	void Debug(const std::string& msg);

	void Info(const std::string& msg);

	void Warn(const std::string& msg);

	void Error(const std::string& msg);


	void AddMessage(const std::string&  msg ,log_level l);
	void WriteMessage();

private:
	log_level level_{log_level::info};
	std::mutex mutex_;
	std::deque<std::pair<std::string, log_level>> buffer_;
	std::condition_variable cv_;

	std::map<std::string,callback> m_log_handlers;
};
}
