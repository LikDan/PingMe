#pragma once
#include <string>
#include <map>

#include "Pinger.h"
#include <json.hpp>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>

using namespace std;
using namespace winrt::Windows::UI::Xaml;

using json = nlohmann::json;

namespace winrt::PingMe::implementation
{
	__declspec(selectany) map<hstring, PingMe::Monitor> monitors;
	__declspec(selectany) PingMe::Settings settings;
}
