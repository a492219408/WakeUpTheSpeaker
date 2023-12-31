#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(nullptr);
    IMMDeviceEnumerator* device_enumerator = nullptr;
    CLSID clsid;
    CLSIDFromString(L"{BCDE0395-E52F-467C-8E3D-C4579291692E}", &clsid); // UUID for MMDeviceEnumerator
//     CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), reinterpret_cast<LPVOID*>(&device_enumerator));
    CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), reinterpret_cast<LPVOID*>(&device_enumerator));
    IMMDevice* default_device = nullptr;
    device_enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &default_device);
    device_enumerator->Release();
    device_enumerator = nullptr;

    IAudioEndpointVolume* endpoint_volume = nullptr;
    CLSIDFromString(L"{5CDF2C82-841E-4546-9722-0CF74078229A}", &clsid); // UUID for IAudioEndpointVolume
//     default_device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, reinterpret_cast<LPVOID*>(&endpoint_volume));
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
