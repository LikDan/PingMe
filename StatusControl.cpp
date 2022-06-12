#include "pch.h"
#include "StatusControl.h"
#include "StatusControl.g.cpp"

#include <winrt/Windows.UI.Xaml.Media.h>

#include "Monitors.h"

namespace winrt::PingMe::implementation
{
	using namespace Windows::UI::Xaml;
	using namespace Controls;

	Windows::UI::Xaml::DependencyProperty StatusControl::m_colorProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Color",
			winrt::xaml_typename<winrt::Windows::UI::Xaml::Media::SolidColorBrush>(),
			winrt::xaml_typename<PingMe::StatusControl>(),
			Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(L"#424242"), Windows::UI::Xaml::PropertyChangedCallback{&StatusControl::OnChanged}
			}
		);

	Windows::UI::Xaml::DependencyProperty StatusControl::m_nameProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"MonitorName",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<PingMe::StatusControl>(),
			Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(L"Monitor"), Windows::UI::Xaml::PropertyChangedCallback{&StatusControl::OnChanged}
			}
		);

	Windows::UI::Xaml::DependencyProperty StatusControl::m_hostProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Host",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<PingMe::StatusControl>(),
			Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(L"Url"), Windows::UI::Xaml::PropertyChangedCallback{&StatusControl::OnChanged}
			}
		);

	Windows::UI::Xaml::DependencyProperty StatusControl::m_cooldownProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Cooldown",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<PingMe::StatusControl>(),
			Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(L"Cooldown"), Windows::UI::Xaml::PropertyChangedCallback{&StatusControl::OnChanged}
			}
		);

	Windows::UI::Xaml::DependencyProperty StatusControl::m_pointsProperty =
		Windows::UI::Xaml::DependencyProperty::Register(
			L"Points",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<PingMe::StatusControl>(),
			Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(L"[]"), Windows::UI::Xaml::PropertyChangedCallback{&StatusControl::OnChanged}
			}
		);

	void StatusControl::OnChanged(Windows::UI::Xaml::DependencyObject const& d,
	                              Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& /* e */)
	{
		if (PingMe::StatusControl theControl{d.try_as<PingMe::StatusControl>()})
		{
			// Call members of the projected type via theControl.

			PingMe::implementation::StatusControl* ptr{
				winrt::get_self<PingMe::implementation::StatusControl>(theControl)
			};
			// Call members of the implementation type via ptr.
		}
	}

	void StatusControl::ClickHandler(Windows::Foundation::IInspectable const& sender,
	                                                              Windows::UI::Xaml::RoutedEventArgs const& args)
	{
		
	}

	void StatusControl::OnApplyTemplate()
	{
		Button button = GetTemplateChild(L"button").as<Button>();
		button.Click({this, &StatusControl::ClickHandler});
	}

	void StatusControl::Update()
	{
		/*Monitor m = monitors[MonitorName()];

		json pingsJson;
		for each (Ping ping in m.pings) {
			json j = ping.serialize();

			pingsJson.push_back(j);
		}

		auto color = m.color.brush();

		SetValue(m_colorProperty, winrt::box_value(color));
		SetValue(m_hostProperty, winrt::box_value(winrt::to_hstring(m.host)));
		SetValue(m_cooldownProperty, winrt::box_value(winrt::to_hstring(m.cooldown)));
		SetValue(m_pointsProperty, winrt::box_value(winrt::to_hstring(pingsJson.dump())));*/
	}
}
