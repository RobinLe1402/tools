/*

DELETE ALL OF A FOLDER'S CONTENTS

Call syntax: StartupDelete.exe <Directory>
e.g. StartupDelete.exe C:\TEMP

*/



#include <filesystem>
#include <Windows.h>


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
	if (!std::filesystem::exists(szPath) || !std::filesystem::is_directory(szPath))
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

	// directory exists --> recursuvely delete all files and folders inside
	for (const auto& entry : std::filesystem::directory_iterator(szPath))
		std::filesystem::remove_all(entry.path());

	return 0;
}
