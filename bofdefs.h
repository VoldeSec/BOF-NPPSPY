#pragma once
#include <windows.h>



WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(void);
WINADVAPI LONG WINAPI ADVAPI32$RegConnectRegistryA(LPCSTR, HKEY, PHKEY);
WINADVAPI LONG WINAPI ADVAPI32$RegCreateKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD Reserved, LPSTR lpClass, DWORD dwOptions, REGSAM samDesired, LPSECURITY_ATTRIBUTES lpSecurityAttributes, PHKEY phkResult, LPDWORD lpdwDisposition);
WINADVAPI LONG WINAPI ADVAPI32$RegOpenKeyExA(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
WINADVAPI LONG WINAPI ADVAPI32$RegSetValueExA(HKEY hKey, LPCSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData);
WINADVAPI LONG WINAPI ADVAPI32$RegCloseKey(HKEY hKey);
WINADVAPI LONG WINAPI ADVAPI32$RegDeleteTreeA(HKEY hKey, LPCSTR lpSubKey);
WINADVAPI LONG WINAPI ADVAPI32$RegDeleteValueA(HKEY hKey, LPCSTR lpValueName);
WINADVAPI LONG WINAPI ADVAPI32$RegGetValueA(HKEY hKey, LPCSTR lpSubKey, LPCSTR lpValue, DWORD dwFlags, LPDWORD pdwType, PVOID pvData, LPDWORD pcbData);

WINBASEAPI BOOL WINAPI KERNEL32$WriteFile(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
WINBASEAPI HANDLE WINAPI KERNEL32$CreateFileA(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
WINBASEAPI BOOL WINAPI KERNEL32$CloseHandle(HANDLE hObject);
WINBASEAPI DWORD WINAPI KERNEL32$GetFileAttributesA(LPCSTR lpFileName);
WINBASEAPI DWORD WINAPI KERNEL32$DeleteFileA(LPCSTR lpFileName);
WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(VOID);


DECLSPEC_IMPORT char* WINAPI MSVCRT$strcat(char*, const char*);
DECLSPEC_IMPORT size_t WINAPI MSVCRT$strlen(const char*);
DECLSPEC_IMPORT int WINAPI MSVCRT$strcmp(const char*, const char*);





