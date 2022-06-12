#pragma once

#include "Monitor.g.h"
#include <CheckEvent.g.h>

namespace winrt::PingMe::implementation
{
	struct Monitor : MonitorT<Monitor>
	{
		Monitor(hstring name, hstring host, int timeout)
		{
			this->name = name;
			this->host = host;
			this->timeout = timeout;

			std::vector<PingMe::CheckEvent> values{};
			this->events = single_threaded_vector(std::move(values));

			this->pinger = Pinger(host, timeout, { this, &Monitor::PingCheck });
		};

		Monitor() = default;

		PingMe::MonitorPreviewControl Parent() { return this->parent; }
		void Parent(PingMe::MonitorPreviewControl parent) { this->parent = parent; }

		void Check()
		{
			this->pinger;
		};

		void Continue()
		{
			this->pinger.Continue();
		};

		void Pause()
		{
			this->pinger.Pause();
		};

		hstring Name() { return this->name; }
		hstring Host() { return this->host; }
		int Timeout() { return this->timeout; }
		Windows::Foundation::Collections::IVector<winrt::PingMe::CheckEvent> Events() { return this->events; }

		void PingCheck(IInspectable const& sender, PingMe::CheckEvent const& e)
		{
			this->events.Append(e);
			if (parent != nullptr) parent.Update();
		}

	private:
		hstring name, host;
		int timeout;
		Windows::Foundation::Collections::IVector<winrt::PingMe::CheckEvent> events;

		Pinger pinger;
		PingMe::MonitorPreviewControl parent = PingMe::MonitorPreviewControl(nullptr);
	};
}

namespace winrt::PingMe::factory_implementation
{
	struct Monitor : MonitorT<Monitor, implementation::Monitor>
	{
	};
}
