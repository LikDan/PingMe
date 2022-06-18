#pragma once

#include "Monitor.g.h"
#include <Utils.h>

namespace winrt::PingMe::implementation
{
	struct Monitor : MonitorT<Monitor>
	{
		Monitor(hstring name, hstring host, hstring method, hstring body, hstring headers, hstring cookies, int timeout)
		{
			this->name = name;
			this->host = host;
			this->timeout = timeout;
			this->method = method;
			this->body = body;
			this->headers = headers;
			this->cookies = cookies;

			std::vector<PingMe::CheckEvent> values{};
			this->events = single_threaded_vector(std::move(values));

			this->pinger = PingMe::Pinger(*this, { this, &Monitor::PingCheck });
		};

		Monitor(hstring name, hstring host, hstring method, hstring body, hstring headers, hstring cookies, int timeout, Windows::Foundation::Collections::IVector<PingMe::CheckEvent> events)
		{
			this->name = name;
			this->host = host;
			this->timeout = timeout;
			this->method = method;
			this->body = body;
			this->headers = headers;
			this->cookies = cookies;
			this->events = events;

			this->pinger = PingMe::Pinger(*this, { this, &Monitor::PingCheck });
		};

		Monitor() = default;

		PingMe::MonitorPreviewControl Parent() { return this->parent; }
		void Parent(PingMe::MonitorPreviewControl parent) { this->parent = parent; }

		void Check()
		{
			this->pinger.Check();
		};

		void Continue()
		{
			this->pinger.Continue();
		};

		void Pause()
		{
			this->pinger.Pause();
		};

		bool IsLaunching()
		{
			return this->pinger.IsLaunching();
		};

		void LogHandler(Windows::Foundation::EventHandler<PingMe::CheckEventControl> const& handler) {
			this->handler = handler;

			if (this->events.Size() < 1) this->Check();
		};

		hstring Name() { return this->name; }
		hstring Host() { return this->host; }
		hstring Method() { return this->method; }
		hstring Body() { return this->body; }
		hstring Headers() { return this->headers; }
		hstring Cookies() { return this->cookies; }
		int Timeout() { return this->timeout; }
		Windows::Foundation::Collections::IVector<PingMe::CheckEvent> Events() { return this->events; }
		void Events(Windows::Foundation::Collections::IVector<PingMe::CheckEvent> events) { this->events = events; }

		void PingCheck(IInspectable const& sender, PingMe::CheckEvent const& e)
		{
			this->events.Append(e);
			if (parent != nullptr) parent.Update();

			auto checkEventControl = PingMe::CheckEventControl(this->name, e);
			handler(nullptr, checkEventControl);

			PingMe::Files().SaveMonitors();
		}

	private:
		hstring name, host, method, body, headers, cookies;
		int timeout;
		Windows::Foundation::Collections::IVector<PingMe::CheckEvent> events;

		PingMe::Pinger pinger;
		PingMe::MonitorPreviewControl parent = PingMe::MonitorPreviewControl(nullptr);

		Windows::Foundation::EventHandler<PingMe::CheckEventControl> handler;
	};
}

namespace winrt::PingMe::factory_implementation
{
	struct Monitor : MonitorT<Monitor, implementation::Monitor>
	{
	};
}
