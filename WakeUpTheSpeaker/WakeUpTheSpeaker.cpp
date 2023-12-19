// WakeUpTheSpeaker.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

/**
 * \brief 
 * \return 
 */
// int main()
// {
// }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(nullptr);
    IMMDeviceEnumerator* device_enumerator = nullptr;
    CLSID clsid;
    CLSIDFromString(L"{BCDE0395-E52F-467C-8E3D-C4579291692E}", &clsid); // UUID for MMDeviceEnumerator
    // CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), reinterpret_cast<LPVOID*>(&device_enumerator));
    CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), reinterpret_cast<LPVOID*>(&device_enumerator));
    IMMDevice* default_device = nullptr;
    device_enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &default_device);
    device_enumerator->Release();
    device_enumerator = nullptr;

    IAudioEndpointVolume* endpoint_volume = nullptr;
    CLSIDFromString(L"{5CDF2C82-841E-4546-9722-0CF74078229A}", &clsid); // UUID for IAudioEndpointVolume
    // default_device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, reinterpret_cast<LPVOID*>(&endpoint_volume));
    default_device->Activate(clsid, CLSCTX_INPROC_SERVER, nullptr, reinterpret_cast<LPVOID*>(&endpoint_volume));
    default_device->Release();
    default_device = nullptr;

    float current_volume = 0;
    endpoint_volume->GetMasterVolumeLevelScalar(&current_volume);

    // Set volume to 30%
    endpoint_volume->SetMasterVolumeLevelScalar(static_cast<float>(0.3), nullptr);

    // Play sound
    Beep(500, 300);

    // Restore original volume
    endpoint_volume->SetMasterVolumeLevelScalar(current_volume, nullptr);

    endpoint_volume->Release();

    CoUninitialize();

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
