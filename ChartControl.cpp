#define _CRT_SECURE_NO_WARNINGS //for std::localtime also see https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4996?f1url=%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(C4996)%26rd%3Dtrue&view=msvc-170 

#include "pch.h"
#include "ChartControl.h"
#include "ChartControl.g.cpp"

#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>

#include <ctime> 
#include <set>
#include "json.hpp"

#include "Monitor.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media::Imaging;


using json = nlohmann::json;

struct CPoint {
    int x;
    int y;

    //RGB color;
};

namespace winrt::PingMe::implementation
{

    using namespace Windows::UI::Xaml;
    using namespace Shapes;
    using namespace Controls;

    Windows::UI::Xaml::DependencyProperty ChartControl::m_pointsJsonProperty =
        Windows::UI::Xaml::DependencyProperty::Register(
            L"PointsJson",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<PingMe::ChartControl>(),
            Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(L"[]"), Windows::UI::Xaml::PropertyChangedCallback{ &ChartControl::OnChanged } }
    );
   
    void ChartControl::OnChanged(Windows::UI::Xaml::DependencyObject const& d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&){
        if (PingMe::ChartControl theControl{ d.try_as<PingMe::ChartControl>() }) {
            PingMe::implementation::ChartControl* ptr{ winrt::get_self<PingMe::implementation::ChartControl>(theControl) };
            ptr->OnApplyTemplate();
        }
    }


    void ChartControl::OnApplyTemplate() {
        chart = GetTemplateChild(L"chart").as<Canvas>();
        timePanel = GetTemplateChild(L"time").as<StackPanel>();
        pingPanel = GetTemplateChild(L"ping").as<Canvas>();
       
        if (chart == NULL || timePanel == NULL || pingPanel == NULL) {
            return;
        }

        chart.Children().Clear();
        timePanel.Children().Clear();
        pingPanel.Children().Clear();

        /*auto hLine = Line();
        hLine.X1(-3);
        hLine.Y1(101);
        hLine.X2(290);
        hLine.Y2(101);
        hLine.StrokeThickness(1);
        hLine.Stroke(RGB{ 0, 0, 0, 100 }.brush());

        auto vLine = Line();
        vLine.X1(-2);
        vLine.Y1(0);
        vLine.X2(-2);
        vLine.Y2(100);
        vLine.StrokeThickness(1);
        vLine.Stroke(RGB{ 0, 0, 0, 100 }.brush());

        chart.Children().Append(hLine);
        chart.Children().Append(vLine);

        auto _11hAgo = time(0) - 60 * 60 * 11;

        vector<Ping> pings;
        vector<CPoint> points;
        auto pointsJson = json::parse(PointsJson());
        if (pointsJson.size() < 2) return;

        int maxPing = 0;

        for (int i = 0; i < pointsJson.size(); i++) {
            Ping ping;
            ping = ping.deserialize(pointsJson[i]);

            if (difftime(ping.time, _11hAgo) < 0) continue;

            RGB color;
            switch (ping.statusCode / 100) {
            case 2: 
                color = { 50, 255, 50 };
                break;
            case 4: 
                color = { 255, 50, 50, 100 };
                break;
            default:
                color = { 255, 255, 50 };
                break;
            }

            pings.push_back(ping);
            points.push_back({ (int)(ping.time - _11hAgo) / 60, ping.ping, color });

            if (ping.ping > maxPing) maxPing = ping.ping;
        }
        

        float maxY = points[0].y;
        for each (CPoint point in points) {
            if (point.y > maxY) maxY = point.y;
        }

        double scaleX = 60 * 12 / chart.Width();
        double scaleY = maxY / chart.Height();

        for (int i = 0; i < points.size(); i++) {
            points[i].x /= scaleX;
            points[i].y /= scaleY;
        }

        for (int i = 1; i < points.size(); i++) {
            if (pings[i].statusCode / 100 == 4) {
                auto rectangle = Rectangle();
                rectangle.Width(points[i].x - points[i - 1].x);
                rectangle.Height(chart.Height());

                Canvas::SetLeft(rectangle, points[i - 1].x);
                Canvas::SetTop(rectangle, 0);

                rectangle.Fill(points[i].color.brush());

                chart.Children().Append(rectangle);
            }

            auto line = Line();
            line.X1(points[i - 1].x);
            line.Y1(chart.Height() - points[i - 1].y);
            line.X2(points[i].x);
            line.Y2(chart.Height() - points[i].y);

            line.StrokeThickness(2);
            line.Stroke(points[i].color.brush());

            chart.Children().Append(line);
        }

        tm* timeCouner = localtime(&_11hAgo);
        
        timeCouner->tm_min = timeCouner->tm_min - timeCouner->tm_min % 60 + 60;
        timeCouner->tm_sec = 0;

        int marginStart = 60 / 2 - difftime(mktime(timeCouner), _11hAgo) / 60;

        timePanel.Padding({ marginStart / scaleX, 0, 0, 0 });

        for (int i = 0; i < 12; i++) {
            auto h = to_hstring(timeCouner->tm_hour);
            auto m = to_hstring(timeCouner->tm_min);

            if (h.size() == 1) h = L"0" + h;
            if (m.size() == 1) m = L"0" + m;

            auto timeText = TextBlock();
            timeText.Width(60 / scaleX);
            timeText.Text(h + L":" + m);
            timeText.FontSize(8);
            timeText.Foreground(RGB{ 0, 0, 0 }.brush());

            timePanel.Children().Append(timeText);

            timeCouner->tm_min += 60;

            auto t = mktime(timeCouner);
            timeCouner = localtime(&t);
        }

        for (int i = 0; i < maxPing; i += 100) {
            auto pingText = TextBlock();
            pingText.Width(20);
            pingText.Text(to_hstring(i));
            pingText.FontSize(8);
            pingText.Foreground(RGB{ 0, 0, 0 }.brush());
            pingText.HorizontalTextAlignment(TextAlignment::End);

            Canvas::SetLeft(pingText, 0);
            Canvas::SetTop(pingText, chart.Height() - i / scaleY);

            pingPanel.Children().Append(pingText);
        }*/
    }
}
