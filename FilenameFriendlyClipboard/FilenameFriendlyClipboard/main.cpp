/*

CHANGE CLIPBOARD CONTENTS (IF TEXT) TO BE USABLE AS FILENAME

*/



#include <stdint.h>
#include <string>
#include <Windows.h>

std::wstring FilenameFriendly(const wchar_t* sz)
{

	switch (sz[0])
	{
	case L'\\':
		return L"\uFF3C";
	case L'/':
		return L"\uFF0F";
	case L':':
		return L"\uFF1A";
	case L'*':
		return L"\uFF0A";
	case L'?':
		return L"\uFF1F";
	case L'"':
		return L"''";
	case L'<':
		return L"\uFF1C";
	case L'>':
		return L"\uFF1E";
	case L'|':
		return L"\uFF5C";

	default:
		if ((sz[0] & 0xFC) == 0b11011000)
			return std::wstring(sz, 2);
		else
			return std::wstring(sz, 1);
	}
}

uint8_t CodeUnitsOfFirstIn(const wchar_t* sz)
{
	if ((sz[0] & 0xFC) == 0b11011000)
		return 2;
	else
		return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR szCmdLine,
	_In_ int iCmdShow)
{
	//----------------------------------------------------------------------------------------------
	// Open and read clipboard

	if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
		return 1;
	if (!OpenClipboard(NULL))
		return 1;

	wchar_t* szIn = nullptr;

	HGLOBAL hClipboardData = GetClipboardData(CF_UNICODETEXT);
	if (hClipboardData == NULL)
	{
		CloseClipboard();
		return 1;
	}
	szIn = (wchar_t*)GlobalLock(hClipboardData);
	if (szIn == nullptr)
	{
		CloseClipboard();
		return 1;
	}



	//----------------------------------------------------------------------------------------------
	// Create filename friendly string

	const size_t lenIn = wcslen(szIn);

	std::wstring sOut;
	for (size_t i = 0; i < lenIn; i++)
	{
		sOut += FilenameFriendly(szIn + i);

		if (CodeUnitsOfFirstIn(szIn + i) == 2)
			i++;
	}



	//----------------------------------------------------------------------------------------------
	// Create global data + write to clipboard

	EmptyClipboard();

	const size_t lenOut = sOut.length();
	const size_t sizeOut = (lenOut + 1) * sizeof(wchar_t);
	hClipboardData = GlobalAlloc(GMEM_DDESHARE, sizeOut);

	bool bResult = true;
	if (hClipboardData == 0)
	{
		CloseClipboard();
		return 1;
	}
	wchar_t* const pchData = (wchar_t*)GlobalLock(hClipboardData);

	if (pchData != nullptr)
		memcpy(pchData, sOut.c_str(), sizeOut);
	else
		bResult = false;

	GlobalUnlock(hClipboardData);

	if (bResult)
		SetClipboardData(CF_UNICODETEXT, hClipboardData);
	else
		GlobalFree(hClipboardData);

	CloseClipboard();

	return 0;
}
