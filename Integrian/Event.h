#pragma once

#ifndef INTEGRIAN_EVENT_H
#define INTEGRIAN_EVENT_H

#include <tuple> // std::tuple
#include <string> // std::string
#include <memory> // std::shared_ptr

namespace Integrian
{
	class IEventData abstract
	{
	public:
		virtual ~IEventData() = default;
	};

	template<typename ... Args>
	class EventData final : public IEventData
	{
	public:
		EventData(Args... args)
			: m_Data{ std::make_tuple(args...) }
		{
		}
		virtual ~EventData() = default;

		const std::tuple<Args...>& GetData() const
		{
			return m_Data;
		}

	private:
		std::tuple<Args...> m_Data;
	};

	class Event final
	{
	public:
		template<typename ... Args>
		Event(const std::string& event, Args... args)
			: m_Event{ event }
			, m_pData{ new EventData<Args...>{args...} }
		{
		}
		Event(const Event& other) noexcept;
		Event(Event&& other) noexcept;

		~Event();

		const std::string GetEvent() const;

		template<typename ... Args>
		const std::tuple<Args...> GetData() const
		{
			return static_cast<EventData<Args...>*>(m_pData.get())->GetData();
		}

	private:
		std::string m_Event;
		std::shared_ptr<IEventData> m_pData{};
	};
}

#endif // !INTEGRIAN_EVENT_H
