﻿#pragma once

#include "pch.h"
#include "Pinger.g.h"

namespace winrt::PingMe::implementation
{
	struct Pinger : PingerT<Pinger>
	{
		Pinger();
		Pinger(hstring host, int timeout, Windows::Foundation::EventHandler<PingMe::CheckEvent> const& handler);

		void Pause();
		void Continue();

		void Check();
	private:
		Windows::UI::Xaml::DispatcherTimer timer;

		hstring host;
		Windows::Foundation::EventHandler<PingMe::CheckEvent> handler;
	};
}

namespace winrt::PingMe::factory_implementation
{
	struct Pinger : PingerT<Pinger, implementation::Pinger>
	{
	};
}