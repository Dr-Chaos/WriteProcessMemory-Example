// author : Eray Arslan
// Dota 2 Radiant-Dire Score Fetch with Memory Hack

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <psapi.h>
#include <cstdio>
#include <tchar.h>
#include <TlHelp32.h>
#include <conio.h>

using namespace std;

DWORD getModuleBaseAddress(DWORD dwProcessIdentifier, TCHAR *lpszModuleName) {
   HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessIdentifier);
   DWORD dwModuleBaseAddress = 0;
   if(hSnapshot != INVALID_HANDLE_VALUE) {
      MODULEENTRY32 ModuleEntry32 = {0};
      ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
      if(Module32First(hSnapshot, &ModuleEntry32)) {
         do {
            if(_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0) {
               dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
               break;
            }
         } while(Module32Next(hSnapshot, &ModuleEntry32));
      } CloseHandle(hSnapshot);
   } return dwModuleBaseAddress;
}

int main() {
   DWORD radiantScore;
   DWORD direScore;
   
   DWORD numBytesRead;
   
   HWND window = FindWindow(0, "DOTA 2");
   if(window == 0) { return 0; }
   DWORD pID = 0;
   GetWindowThreadProcessId(window, &pID);

   DWORD baseAddr = getModuleBaseAddress(pID, _T("client.dll"));
   DWORD staticOffset = 0x130A7DC;
   DWORD applicationAddr;

   HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

   ReadProcessMemory(handle, (LPCVOID)(baseAddr + staticOffset), &applicationAddr, sizeof(DWORD), &numBytesRead);

   ReadProcessMemory(handle, (LPCVOID)(applicationAddr + 0x00000300 + (4 * 0x00000002)), &radiantScore, sizeof(DWORD), &numBytesRead);
   ReadProcessMemory(handle, (LPCVOID)(applicationAddr + 0x00000300 + (4 * 0x00000003)), &direScore, sizeof(DWORD), &numBytesRead);

   printf("Radiant Score : %d\n", radiantScore);
   printf("Dire Score : %d\n", direScore);

   getch();
}
