//Rahul Yadav 5th Sept 2018
#pragma once

#include "logger.hpp"

using namespace user;

void logger::registerHandler(std::string name, callback c)
{
	m_log_handlers.insert(std::pair<std::string, callback> {name, c });
}

void logger::deRegisterHandler(const std::string& name)
{
	auto it = m_log_handlers.find(name);
	if (it != m_log_handlers.end())
		m_log_handlers.erase(name);
}

void logger::setLogLevel(log_level l)
{
	m_level = l;
}

void logger::debug(const std::string& msg)
{
	if (m_level >= log_level::debug)
	{
		for (auto cb : m_log_handlers)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			cb.second(msg);
		}
	}
};

void logger::info(const std::string& msg)
{
	if (m_level >= log_level::info)
	{
		for (auto cb : m_log_handlers)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			cb.second(msg);
		}
	}
}

void logger::warn(const std::string& msg)
{
	if (m_level >= log_level::warn)
	{
		for (auto cb : m_log_handlers)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			cb.second(msg);
		}
	}
}

void logger::error(const std::string& msg)
{
	if (m_level >= log_level::error)
	{
		for (auto cb : m_log_handlers)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			cb.second(msg);
		}

	}
}







