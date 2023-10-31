#include <stdint.h>
#include <stdio.h>

#ifndef VC_EXTRA_LEAN
#define VC_EXTRA_LEAN
#include <windows.h>
#endif // VC_EXTRA_LEAN

static const uintptr_t schmoney_addr = 0x20800870;

DWORD WINAPI MainThread(HINSTANCE hInstance)
{
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);

    *(int *)schmoney_addr = 0x6FFFFFFF;

    while (!GetAsyncKeyState(VK_HOME))
    {
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            
        }
    }

    fclose(fp);
    FreeConsole();
    FreeLibraryAndExitThread(hInstance, 0);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    static HANDLE handle = NULL;

    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hInstance);
            handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hInstance, 0, NULL);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            CloseHandle(handle);
            break;
        }
        default:
            break;
    }

    return TRUE;
}
