#include <Windows.h>
#include <cstdio>
#include <iostream>
#define rebase(x) (x + (DWORD)GetModuleHandle(NULL))

DWORD main(HMODULE mod) {
    AllocConsole();
    SetConsoleTitle((LPCWSTR)"Assault Heck");

    FILE* idk;
    freopen_s(&idk, "CONOUT$", "w", stdout);

    bool godmode = false;
    int* p_health = reinterpret_cast<int*>(*(uintptr_t*)rebase(0x017E0A8) + 0xEC);

    printf(
        R"(
[1] Enable god mode.
)");
   
    while (true) {
        if (godmode) {
            *p_health = 100;
        }

        if (GetKeyState(VK_F6)) {
            printf("\nEnabled/disabled god mode.");
            godmode = !godmode;
        }
        else if (GetKeyState(VK_ESCAPE)) {
            printf("You've exited!");
            FreeLibraryAndExitThread(mod, 0);
            FreeConsole();
            break;
        }
    }
}

DWORD WINAPI DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), hModule, NULL, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}