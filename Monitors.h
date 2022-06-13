#pragma once
#include <string>
#include <map>

#include "Pinger.h"

using namespace std;
using namespace winrt::Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
	__declspec(selectany) map<hstring, pair<PingMe::Monitor, PingMe::MonitorPreviewControl>> monitors;
	__declspec(selectany) PingMe::Settings settings;
}
