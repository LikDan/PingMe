#include "pch.h"
#include "Files.h"
#if __has_include("Files.g.cpp")
#include "Files.g.cpp"
#endif

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>

#include "json.hpp"
#include "Utils.h"

using namespace winrt::Windows::UI::Xaml;

using json = nlohmann::json;

namespace winrt::PingMe::implementation
{

	Windows::Foundation::IAsyncAction Files::ReadMonitors()
	{
		auto file = co_await getFile(L"monitors.json");
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


			std::vector<PingMe::CheckEvent> values{};
			auto events = single_threaded_vector(std::move(values));

			auto eventsJson = monitorJson["events"];
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

			auto monitor = PingMe::Monitor(to_hstring(name), to_hstring(host), to_hstring(method), to_hstring(body), to_hstring(headers), to_hstring(cookies), timeout, events);
			monitors[monitor.Name()] = monitor;
		}
	}

	Windows::Foundation::IAsyncAction Files::SaveMonitors()
    {
        json monitorsJson;

		for each (auto monitor in monitors)
		{
			json monitorJson;

			monitorJson["name"] = to_string(monitor.second.Name());
			monitorJson["host"] = to_string(monitor.second.Host());
			monitorJson["method"] = to_string(monitor.second.Method());
			monitorJson["body"] = to_string(monitor.second.Body());
			monitorJson["headers"] = to_string(monitor.second.Headers());
			monitorJson["cookies"] = to_string(monitor.second.Cookies());
			monitorJson["timeout"] = monitor.second.Timeout();

			auto events = monitor.second.Events();
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

		auto content = to_hstring(monitorsJson.dump());

		auto file = co_await getFile(L"monitors.json");
		co_await winrt::Windows::Storage::FileIO::WriteTextAsync(file, content);
		co_await getFile(L"monitors.json");
    }
}
