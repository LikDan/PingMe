#pragma once

#include "Pinger.g.h"

namespace winrt::PingMe::implementation
{
	struct Pinger : PingerT<Pinger>
	{
		Pinger(hstring host, int timeout, Windows::Foundation::EventHandler<int> const& handler);

		void Pause()
		{
			
		};
		void Continue();
		

	private:
		Windows::UI::Xaml::DispatcherTimer timer;
	};
}

namespace winrt::PingMe::factory_implementation
{
	struct Pinger : PingerT<Pinger, implementation::Pinger>
	{
	};
}
