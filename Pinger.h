#pragma once

#include "pch.h"
#include "Pinger.g.h"

namespace winrt::PingMe::implementation
{
	struct Pinger : PingerT<Pinger>
	{
		Pinger();
		Pinger(PingMe::Monitor monitor, Windows::Foundation::EventHandler<PingMe::CheckEvent> const& handler);

		void Pause();
		void Continue();

		void Check();

		bool IsLaunching();
	private:
		Windows::UI::Xaml::DispatcherTimer timer;

		PingMe::Monitor monitor = PingMe::Monitor(nullptr);
		Windows::Foundation::EventHandler<PingMe::CheckEvent> handler;
	};
}

namespace winrt::PingMe::factory_implementation
{
	struct Pinger : PingerT<Pinger, implementation::Pinger>
	{
	};
}
