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
	__declspec(selectany) map<hstring, pair<PingMe::Monitor, PingMe::MonitorPreviewControl>> monitors;
	__declspec(selectany) PingMe::Settings settings;

	static Windows::Foundation::IAsyncAction saveMonitors() {
		json monitorsJson;

		for each (auto monitor in monitors)
		{
			json monitorJson;

			monitorJson["name"] = to_string(monitor.second.first.Name());
			monitorJson["host"] = to_string(monitor.second.first.Host());
			monitorJson["method"] = to_string(monitor.second.first.Method());
			monitorJson["body"] = to_string(monitor.second.first.Body());
			monitorJson["headers"] = to_string(monitor.second.first.Headers());
			monitorJson["cookies"] = to_string(monitor.second.first.Cookies());
			monitorJson["timeout"] = monitor.second.first.Timeout();

			auto events = monitor.second.first.Events();
			json eventsJson;
			for (int i = 0; i < events.Size(); i++)
			{
				json eventJson;

				eventJson["ping"] = events.GetAt(i).Ping();
				eventJson["statusCode"] = events.GetAt(i).StatusCode();
				eventJson["body"] = to_string(events.GetAt(i).Body());
				eventJson["headers"] = to_string(events.GetAt(i).Headers());
				eventJson["time"] = events.GetAt(i).Time();
				
				eventsJson.push_back(eventJson);
			}

			monitorJson["events"] = eventsJson;

			monitorsJson.push_back(monitorJson);
		}

		auto localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
		auto file = co_await localFolder.GetFileAsync(L"monitors.json");
		co_await winrt::Windows::Storage::FileIO::WriteTextAsync(file, to_hstring(monitorsJson.dump()));
	}

	static Windows::Foundation::IAsyncAction readMonitors() {
		auto localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
		auto file = co_await localFolder.GetFileAsync(L"monitors.json");
		hstring text = co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file);
		
		auto monitorsJson = json::parse(to_string(text));
		for each (auto monitorJson in monitorsJson)
		{
			auto name = monitorJson["name"].get<std::string>();
			auto host = monitorJson["host"].get<std::string>();
			auto method = monitorJson["method"].get<std::string>();
			auto body = monitorJson["body"].get<std::string>();
			auto headers = monitorJson["headers"].get<std::string>();
			auto cookies = monitorJson["cookies"].get<std::string>();
			auto timeout = monitorJson["timeout"].get<int>();

			auto monitor = PingMe::Monitor(to_hstring(name), to_hstring(host), to_hstring(method), to_hstring(body), to_hstring(headers), to_hstring(cookies), timeout);

			std::vector<PingMe::CheckEvent> values{};
			auto events = single_threaded_vector(std::move(values));

			auto eventsJson = monitorJson["events"].array();
			for each (auto eventJson in eventsJson)
			{
				auto ping = eventJson["ping"].get<int>();
				auto statusCode = eventJson["statusCode"].get<int>();
				auto body = eventJson["body"].get<std::string>();
				auto headers = eventJson["headers"].get<std::string>();
				auto time = eventJson["time"].get<long>();

				auto checkEvent = PingMe::CheckEvent(ping, statusCode, to_hstring(body), to_hstring(headers), time);
				events.Append(checkEvent);
			} 

			monitor.Events(events);

			monitors[monitor.Name()] = pair(monitor, PingMe::MonitorPreviewControl(nullptr));
		}
	}
}
