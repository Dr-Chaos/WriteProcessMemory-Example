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

int main() {
   DWORD numBytesRead;
   DWORD result;
   HWND window = FindWindow(0, "VICTIM");
   if(window == 0){ return 0; }
   DWORD pID = 0;
   GetWindowThreadProcessId(window, &pID);
   DWORD applicationAddr;
   HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
   ReadProcessMemory(handle, (LPCVOID)(0x0028FE98), &applicationAddr, sizeof(DWORD), &numBytesRead);
   ReadProcessMemory(handle, (LPCVOID)(applicationAddr-0x1C), &result, sizeof(DWORD), &numBytesRead);
   printf("%d\n",result);
   getch();
}
