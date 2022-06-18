#include "pch.h"
#include "PingChartControl.h"
#if __has_include("PingChartControl.g.cpp")
#include "PingChartControl.g.cpp"
#endif

#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>

#pragma warning(disable : 4996)

#include <Utils.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;

namespace winrt::PingMe::implementation
{
    PingChartControl::PingChartControl()
    {
        InitializeComponent();
    }

    void PingChartControl::Update(Collections::IVector<PingMe::CheckEvent> events)
    {
        struct CPoint {
            int x;
            int y;

            RGBA color;
        };

        ChartCanvas().Children().Clear();
        TimeCanvas().Children().Clear();
        PingCanvas().Children().Clear();

        auto hLine = Line();
        hLine.X1(-3);
        hLine.Y1(101);
        hLine.X2(290);
        hLine.Y2(101);
        hLine.StrokeThickness(1);
        hLine.Stroke(RGBA(0, 0, 0, 100).brush());

        auto vLine = Line();
        vLine.X1(-2);
        vLine.Y1(0);
        vLine.X2(-2);
        vLine.Y2(100);
        vLine.StrokeThickness(1);
        vLine.Stroke(RGBA(0, 0, 0, 100).brush());

        ChartCanvas().Children().Append(hLine);
        ChartCanvas().Children().Append(vLine);

		auto chartHours = time(0) - 60 * 60 * (settings.ChartHours());

        std::vector<CPoint> points;
        std::vector<CheckEvent> checkEvents;
        if (events == nullptr || events.Size() < 1) return;

        int maxPing = events.GetAt(0).Ping();
        int minPing = events.GetAt(0).Ping();

        for (int i = 0; i < events.Size(); i++) {
            if (difftime(events.GetAt(i).Time(), chartHours) < 0) continue;

            RGBA color = events.GetAt(i).color();

            points.push_back({ (int)(events.GetAt(i).Time() - chartHours) / 60, events.GetAt(i).Ping(), color});
            checkEvents.push_back(events.GetAt(i));

            if (events.GetAt(i).Ping() > maxPing) maxPing = events.GetAt(i).Ping();
            if (events.GetAt(i).Ping() < minPing) minPing = events.GetAt(i).Ping();
        }

        if (points.size() < 1) return;

        float maxY = points[0].y;
        for each (CPoint point in points) {
            if (point.y > maxY) maxY = point.y;
        }

        double scaleX = 60 * settings.ChartHours() / ChartCanvas().Width();
        double scaleY = maxY / ChartCanvas().Height();

        for (int i = 0; i < points.size(); i++) {
            points[i].x /= scaleX;
            points[i].y /= scaleY;
        }

        for (int i = 1; i < points.size(); i++) {
            if (checkEvents[i].StatusCode() / 100 == 0 || checkEvents[i].StatusCode() / 100 == 4 || checkEvents[i].StatusCode() / 100 == 5) {
                auto rectangle = Rectangle();
                rectangle.Width(points[i].x - points[i - 1].x);
                rectangle.Height(ChartCanvas().Height());

                Canvas::SetLeft(rectangle, points[i - 1].x);
                Canvas::SetTop(rectangle, 0);

                rectangle.Fill(points[i].color.brush());

                ChartCanvas().Children().Append(rectangle);
            }

            auto line = Line();
            line.X1(points[i - 1].x);
            line.Y1(ChartCanvas().Height() - points[i - 1].y);
            line.X2(points[i].x);
            line.Y2(ChartCanvas().Height() - points[i].y);

            line.StrokeThickness(2);
            line.Stroke(points[i].color.brush());

            ChartCanvas().Children().Append(line);
        }

        tm* timeCouner = localtime(&chartHours);

        timeCouner->tm_min = timeCouner->tm_min - timeCouner->tm_min % 60 + 60;
        timeCouner->tm_sec = 0;

        int marginStart = 60 / 2 - difftime(mktime(timeCouner), chartHours) / 60;

        TimeCanvas().Padding({ marginStart / scaleX, 0, 0, 0 });

        for (int i = 0; i < settings.ChartHours(); i++) {
            auto h = to_hstring(timeCouner->tm_hour);
            auto m = to_hstring(timeCouner->tm_min);

            if (m.size() == 1) m = L"0" + m;

            auto timeText = TextBlock();
            timeText.Width(60 / scaleX);
            timeText.Text(h + L":" + m);
            timeText.FontSize(8);
            timeText.Foreground(RGBA(0, 0, 0).brush());
            timeText.HorizontalTextAlignment(TextAlignment::End);

            TimeCanvas().Children().Append(timeText);

            timeCouner->tm_min += 60;

            auto t = mktime(timeCouner);
            timeCouner = localtime(&t);
        }

        for (int i = 0; i < maxPing; i += 100) {
            auto pingText = TextBlock();
            pingText.Width(20);
            pingText.Text(to_hstring(i));
            pingText.FontSize(8);
            pingText.Foreground(RGBA(0, 0, 0).brush());
            pingText.HorizontalTextAlignment(TextAlignment::End);

            Canvas::SetLeft(pingText, 0);
            Canvas::SetTop(pingText, ChartCanvas().Height() - i / scaleY);

            PingCanvas().Children().Append(pingText);
        }

        auto maxPingText = TextBlock();
        maxPingText.Width(20);
        maxPingText.Text(to_hstring(maxPing));
        maxPingText.FontSize(8);
        maxPingText.Foreground(RGBA(0, 0, 0).brush());
        maxPingText.HorizontalTextAlignment(TextAlignment::End);

        Canvas::SetLeft(maxPingText, 0);
        Canvas::SetTop(maxPingText, ChartCanvas().Height() - maxPing / scaleY);

        PingCanvas().Children().Append(maxPingText);

        auto minPingText = TextBlock();
        minPingText.Width(20);
        minPingText.Text(to_hstring(minPing));
        minPingText.FontSize(8);
        minPingText.Foreground(RGBA(0, 0, 0).brush());
        minPingText.HorizontalTextAlignment(TextAlignment::End);

        Canvas::SetLeft(minPingText, 0);
        Canvas::SetTop(minPingText, ChartCanvas().Height() - minPing / scaleY);

        PingCanvas().Children().Append(minPingText);
    }
}
