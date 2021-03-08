#include "logger.hpp"
#include <thread>
#include <mutex>
#include <utility>

using namespace user;

void logger::RegisterHandler(std::string name, callback c)
{
	m_log_handlers.insert(std::pair<std::string, callback> {name, c });
}

void logger::DeRegisterHandler(const std::string& name)
{
	auto it = m_log_handlers.find(name);
	if (it != m_log_handlers.end())
		m_log_handlers.erase(name);
}

void logger::SetLogLevel(log_level l)
{
	level_ = l;
}

void logger::AddMessage(const std::string&  msg ,logger::log_level l)
{
	std::lock_guard<std::mutex> lk{mutex_};
	auto val = std::make_pair(msg,l);
	buffer_.push_back(val);	
	cv_.notify_one();
}

void logger::WriteMessage()
{
	std::unique_lock<std::mutex> lk{mutex_};
	cv_.wait(lk,[this](){
		return this->buffer_.size() != 0;
	});

	auto msg_with_level = buffer_.front();
	buffer_.pop_front();

	const std::string& msg  = msg_with_level.first;
	logger::log_level l  = msg_with_level.second;

	if (level_ >= l)
	{
		for (auto cb : m_log_handlers)
		{
			cb.second(msg);
		}
	}
	
}

void logger::Debug(const std::string& msg)
{
	AddMessage(msg, log_level::debug);	
};

void logger::Info(const std::string& msg)
{
	AddMessage(msg, log_level::info);
}

void logger::Warn(const std::string& msg)
{
	AddMessage(msg, log_level::warn);
}

void logger::Error(const std::string& msg)
{
	AddMessage(msg, log_level::error);
}
