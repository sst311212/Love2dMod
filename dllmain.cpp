#include <Windows.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include "detours/detours.h"

typedef const char* (*t_luaL_checklstring)(void* L, int arg, size_t* l);
static t_luaL_checklstring o_luaL_checklstring;

void HijackDLL();
const char* luaL_checklstring(void* L, int arg, size_t* l);

CHAR hookRequireLua[1024];
CHAR hookReplaceLua[1024];

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInstance);
		HijackDLL();

		WCHAR pszDllPath[MAX_PATH];
		GetModuleFileName(hInstance, pszDllPath, MAX_PATH);
		PathRemoveFileSpec(pszDllPath);

		WCHAR pszIniPath[MAX_PATH];
		PathCombine(pszIniPath, pszDllPath, L"Love2dHook.ini");

		WCHAR pszBuff[1024];
		GetPrivateProfileString(L"Love2dHook", L"RequireLua", L"null_string", pszBuff, 1024, pszIniPath);
		WideCharToMultiByte(CP_ACP, 0, pszBuff, -1, hookRequireLua, 1024, NULL, NULL);
		GetPrivateProfileString(L"Love2dHook", L"ReplaceLua", L"null_string", pszBuff, 1024, pszIniPath);
		WideCharToMultiByte(CP_ACP, 0, pszBuff, -1, hookReplaceLua, 1024, NULL, NULL);

		HMODULE hModule = LoadLibrary(L"lua51.dll");
		o_luaL_checklstring = (t_luaL_checklstring)GetProcAddress(hModule, "luaL_checklstring");
		if (o_luaL_checklstring != NULL) {
			DetourTransactionBegin();
			DetourAttach(&o_luaL_checklstring, luaL_checklstring);
			DetourTransactionCommit();
		}
	}
	return TRUE;
}

FARPROC fpAddr[17];

void HijackDLL()
{
	WCHAR pszDllPath[MAX_PATH];
	GetSystemDirectory(pszDllPath, MAX_PATH);
	lstrcat(pszDllPath, L"\\version.dll");
	HMODULE hModule = LoadLibrary(pszDllPath);
	if (hModule == NULL)
		return;
	fpAddr[0] = GetProcAddress(hModule, "GetFileVersionInfoA");
	fpAddr[1] = GetProcAddress(hModule, "GetFileVersionInfoByHandle");
	fpAddr[2] = GetProcAddress(hModule, "GetFileVersionInfoExA");
	fpAddr[3] = GetProcAddress(hModule, "GetFileVersionInfoExW");
	fpAddr[4] = GetProcAddress(hModule, "GetFileVersionInfoSizeA");
	fpAddr[5] = GetProcAddress(hModule, "GetFileVersionInfoSizeExA");
	fpAddr[6] = GetProcAddress(hModule, "GetFileVersionInfoSizeExW");
	fpAddr[7] = GetProcAddress(hModule, "GetFileVersionInfoSizeW");
	fpAddr[8] = GetProcAddress(hModule, "GetFileVersionInfoW");
	fpAddr[9] = GetProcAddress(hModule, "VerFindFileA");
	fpAddr[10] = GetProcAddress(hModule, "VerFindFileW");
	fpAddr[11] = GetProcAddress(hModule, "VerInstallFileA");
	fpAddr[12] = GetProcAddress(hModule, "VerInstallFileW");
	fpAddr[13] = GetProcAddress(hModule, "VerLanguageNameA");
	fpAddr[14] = GetProcAddress(hModule, "VerLanguageNameW");
	fpAddr[15] = GetProcAddress(hModule, "VerQueryValueA");
	fpAddr[16] = GetProcAddress(hModule, "VerQueryValueW");
}

const char* luaL_checklstring(void* L, int arg, size_t* l)
{
	static bool injected = false;
	const char* value = o_luaL_checklstring(L, arg, l);
	if (!injected && lstrcmpA(value, hookRequireLua) == 0) {
		injected = true;
		return hookReplaceLua;
	}
	return value;
}

void ExpFunc001() { fpAddr[0](); }
void ExpFunc002() { fpAddr[1](); }
void ExpFunc003() { fpAddr[2](); }
void ExpFunc004() { fpAddr[3](); }
void ExpFunc005() { fpAddr[4](); }
void ExpFunc006() { fpAddr[5](); }
void ExpFunc007() { fpAddr[6](); }
void ExpFunc008() { fpAddr[7](); }
void ExpFunc009() { fpAddr[8](); }
void ExpFunc010() { fpAddr[9](); }
void ExpFunc011() { fpAddr[10](); }
void ExpFunc012() { fpAddr[11](); }
void ExpFunc013() { fpAddr[12](); }
void ExpFunc014() { fpAddr[13](); }
void ExpFunc015() { fpAddr[14](); }
void ExpFunc016() { fpAddr[15](); }
void ExpFunc017() { fpAddr[16](); }
