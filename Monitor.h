#pragma once
#include <string>
#include <map>
#include <time.h> 

#include "json.hpp"

using json = nlohmann::json;

using namespace std;


struct RGB {
	int r;
	int g;
	int b;

	int a = 255;

	winrt::Windows::UI::Color color() {
		return winrt::Windows::UI::ColorHelper::FromArgb(a, r, g, b);
	}

	winrt::Windows::UI::Xaml::Media::SolidColorBrush brush() {
		return winrt::Windows::UI::Xaml::Media::SolidColorBrush(color());
	}

	json serialize() {
		json j;
		j["r"] = r;
		j["g"] = g;
		j["b"] = b;
		j["a"] = a;

		return j;
	}

	RGB deserialize(json j) {
		return { j["r"].get<int>(), j["g"].get<int>(), j["b"].get<int>(), j["a"].get<int>() };
	}
};

 
struct Ping {
	int ping;
	time_t time;

	int statusCode;

	RGB color() {
		if (statusCode == 200) {
			return { 50, 255, 50 };
		}
		if (statusCode == 400) {
			return { 255, 50, 50 };
		}

		return { 0, 0, 0, 0 };
	}

	json serialize() {
		json j;
		j["ping"] = ping;
		j["time"] = time;
		j["statusCode"] = statusCode;

		return j;
	}

	Ping deserialize(json j) {
		return { j["ping"].get<int>(), j["time"].get<time_t>(), j["statusCode"].get<int>() };
	}

};

struct Monitor {
	string name;
	string host;
	string cooldown;

	RGB color;
	vector<Ping> pings;

	void event() {
		color = { 255, 50, 50 };

		pings.push_back({ 40, time(0), 400 });
	}

	json serialize() {
		json j;
		j["name"] = name;
		j["host"] = host;
		j["cooldown"] = cooldown;

		j["color"] = color.serialize();

		vector<json> pingsJson;
		for each (Ping ping in pings) {
			pingsJson.push_back(ping.serialize());
		}
		
		j["pings"] = pingsJson;

		return j;
	}

	Monitor deserialize(json j) {
		RGB color;
		color = color.deserialize(j["color"]);

		vector<Ping> pings;
		for each (json pingJson in j["pings"]) {
			Ping ping;
			ping = ping.deserialize(pingJson);

			pings.push_back(ping);
		}

		return { j["name"].get<string>(), j["host"].get<string>(), j["cooldown"].get<string>(), color, pings };
	}
};
__declspec(selectany) map<winrt::hstring, Monitor> monitors;
