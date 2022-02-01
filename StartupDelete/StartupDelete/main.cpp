/*

DELETE ALL OF A FOLDER'S CONTENTS

Call syntax: StartupDelete.exe <Directory>
e.g. StartupDelete.exe C:\TEMP

*/


#include <Windows.h>

void ClearDir(const wchar_t* szPath);
void DeleteDir(const wchar_t* szPath);


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR szCmdLine,
	_In_ int iCmdShow)
{
	const wchar_t* szPath = nullptr;

	// get commandline params
	{
		const wchar_t* const szCmdLineW = GetCommandLineW();
		int iParamCount = 0;
		const auto pParams = CommandLineToArgvW(szCmdLineW, &iParamCount);

		// no path parameter --> error
		if (iParamCount == 1)
		{
			MessageBoxA(NULL,
				"Invalid call to StartupDelete!\n\nUsage:\nStartupDelete.exe <Path>",
				"StartupDelete", MB_ICONERROR);
			return 1;
		}

		// save paths param
		szPath = pParams[1];
	}


	// length check (must be shorter than MAX_PATH)
	const size_t len = wcslen(szPath);
	if (len > MAX_PATH)
	{
		MessageBoxA(NULL, "Path was too long", "StartupDelete", MB_ICONERROR);
		return 1;
	}

	// directory doesn't exist
	DWORD dwFileAttribs = GetFileAttributesW(szPath);

	if (dwFileAttribs == INVALID_FILE_ATTRIBUTES || !(dwFileAttribs & FILE_ATTRIBUTE_DIRECTORY))
	{
		const wchar_t szErrorPrefix[] = L"Directory doesn't exist:\n\"";
		const wchar_t szErrorSuffix[] = L"\"";

		const size_t len = wcslen(szErrorPrefix) + wcslen(szPath) + wcslen(szErrorSuffix) + 1;
		wchar_t* szError = new wchar_t[len] {};

		wcscat_s(szError, len, szErrorPrefix);
		wcscat_s(szError, len, szPath);
		wcscat_s(szError, len, szErrorSuffix);

		MessageBoxW(NULL, szError, L"StartupDelete", MB_ICONERROR);
		delete[] szError;
		return 1;
	}

	ClearDir(szPath);

	return 0;
}

void ClearDir(const wchar_t* szPath)
{
	size_t iPathLen = wcslen(szPath);
	bool bTrailingBackslash = false;
	if (szPath[iPathLen - 1] == L'\\')
	{
		bTrailingBackslash = true;
		--iPathLen;
	}
	const size_t iMaskLen = wcslen(szPath) + 3;
	wchar_t* szMask = new wchar_t[iMaskLen];
	wcscpy_s(szMask, iMaskLen, szPath);
	if (!bTrailingBackslash)
		wcscat_s(szMask, iMaskLen, L"\\");
	wcscat_s(szMask, iMaskLen, L"*");

	WIN32_FIND_DATAW wfd = {};
	HANDLE hFind = FindFirstFileW(szMask, &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return; // no files

	wchar_t szFullPath[MAX_PATH + 1] = {};
	wcscpy_s(szFullPath, szPath);
	if (!bTrailingBackslash)
		wcscat_s(szFullPath, L"\\");
	do
	{
		if (wcscmp(wfd.cFileName, L".") == 0 || wcscmp(wfd.cFileName, L"..") == 0)
			continue;

		szFullPath[iPathLen + 1] = L'\0';
		wcscat_s(szFullPath, wfd.cFileName);

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		{
			if (!SetFileAttributesW(szFullPath, wfd.dwFileAttributes & ~FILE_ATTRIBUTE_READONLY))
				continue;
		}

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			DeleteDir(szFullPath);
		else
			DeleteFileW(szFullPath);
	} while (FindNextFileW(hFind, &wfd));
	FindClose(hFind);

}

void DeleteDir(const wchar_t* szPath)
{
	ClearDir(szPath);
	RemoveDirectoryW(szPath);
}
