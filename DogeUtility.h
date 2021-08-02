#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <vector>

#define GUID_LEN 64
#define MAX_PATH          260

namespace Doge_Utility
{
	//bool __declspec(dllexport) copyFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags = FOF_NOCONFIRMATION);
	//bool __declspec(dllexport) renameFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags = FOF_NOCONFIRMATION);
	//bool __declspec(dllexport) deleteFile(const TCHAR* _pFrom, WORD flags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION);
	//bool __declspec(dllexport) moveFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags = FOF_NOCONFIRMATION);

	std::string utf8ToAnsi(const std::string & str);
	std::string ansiToUtf8(const std::string & str);
    std::wstring ansiToUtf16(const std::string& str);
    std::string utf16ToAnsi(const std::wstring& wstr);

//#ifdef UNICODE
//	wstring __declspec(dllexport) getMyDocumentPath();// 获取“我的文档”路径  
//#else
//	string __declspec(dllexport) getMyDocumentPath();
//#endif // UNICODE

    // vector -> string
    std::string vectorToString(std::vector<std::string> vec, std::string delimiter);
    // string -> vector
    void stringToVector(std::vector<std::string>& vec, std::string str, std::string delimiter);

    std::string getAppPath();
    std::string generateUuid();
    std::string getEndpoint(const std::string & protocol, const std::string& ip, const std::string& port);
}
