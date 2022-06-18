#pragma once

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>

#include "Files.g.h"

namespace winrt::PingMe::implementation
{
    struct Files : FilesT<Files>
    {
        Files() = default;

        Windows::Foundation::IAsyncAction ReadMonitors();
        Windows::Foundation::IAsyncAction SaveMonitors();

    private: 
        Windows::Foundation::IAsyncOperation<Windows::Storage::StorageFile> getFile(hstring name) {
            Windows::Storage::StorageFolder localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();

            try
            {
                co_return co_await localFolder.GetFileAsync(name);
            }
            catch (winrt::hresult_error const& ex) {
            }

            co_return co_await localFolder.CreateFileAsync(name);
        }
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct Files : FilesT<Files, implementation::Files>
    {
    };
}
