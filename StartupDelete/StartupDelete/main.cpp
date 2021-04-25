/*

EMPTY FOLDER CONTENTS

Call syntax: StartupDelete.exe <Directory 1>|<Directory 2>|<...>
e.g. StartupDelete.exe C:\TEMP|C:\deleteme

*/



#include <filesystem>
#include <Windows.h>


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR szCmdLine,
	_In_ int iCmdShow)
{
	// get commandline params
	auto szCmdLineW = GetCommandLineW();

	{
		int iParamCount = 0;
		const auto pParams = CommandLineToArgvW(szCmdLineW, &iParamCount);

		// no path parameter --> error
		if (iParamCount == 1)
		{
			MessageBoxA(NULL,
				"Invalid call to StartupDelete!\n\nUsage:\nStartupDelete.exe <Path 1>|<Path 2>...",
				"StartupDelete", MB_ICONERROR);
			return 1;
		}

		// save paths param
		szCmdLineW = pParams[1];
	}


	const auto lenParams = wcslen(szCmdLineW);

	// go through paths
	wchar_t szPath[MAX_PATH + 1]{};
	size_t index = 0;
	for (size_t i = 0; i <= lenParams; i++)
	{
		if (szCmdLineW[i] == L'|' || i == lenParams) // path separator or end of arguments
		{
			// directory doesn't exist
			if (!std::filesystem::exists(szPath) || !std::filesystem::is_directory(szPath))
			{
				const wchar_t szErrorPrefix[] = L"Directory doesn't exist:\n\"";
				const wchar_t szErrorSuffix[] = L"\"\nIt will be skipped.";

				const size_t len = wcslen(szErrorPrefix) + wcslen(szPath) + wcslen(szErrorSuffix) +
					1;
				wchar_t* szError = new wchar_t[len]{};

				wcscat_s(szError, len, szErrorPrefix);
				wcscat_s(szError, len, szPath);
				wcscat_s(szError, len, szErrorSuffix);

				MessageBoxW(NULL, szError, L"StartupDelete", MB_ICONERROR);

				delete[] szError;



				// clear path
				memset(szPath, 0, (MAX_PATH) * 2);
				continue;
			}

			// path exists --> recursuvely delete all files and folders inside
			for (const auto& entry : std::filesystem::directory_iterator(szPath))
				std::filesystem::remove_all(entry.path());

			// clear path
			memset(szPath, 0, (MAX_PATH) * 2);
		}
		else // regular character
		{
			szPath[index] = szCmdLineW[i];
			index++;
		}
	}

	return 0;
}
