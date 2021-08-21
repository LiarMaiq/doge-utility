#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <vector>

#define GUID_LEN 64
#define MAX_PATH          260
#ifdef _WIN32
    #define DOGE_EXPORT __declspec(dllexport)
#else
    #define DOGE_EXPORT
#endif // _WIN32


namespace Doge_Utility
{
	//bool __declspec(dllexport) copyFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags = FOF_NOCONFIRMATION);
	//bool __declspec(dllexport) renameFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags = FOF_NOCONFIRMATION);
	//bool __declspec(dllexport) deleteFile(const TCHAR* _pFrom, WORD flags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION);
	//bool __declspec(dllexport) moveFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags = FOF_NOCONFIRMATION);

	std::string DOGE_EXPORT utf8ToAnsi(const std::string & str);
	std::string DOGE_EXPORT ansiToUtf8(const std::string & str);
    std::wstring DOGE_EXPORT ansiToUtf16(const std::string& str);
    std::string DOGE_EXPORT utf16ToAnsi(const std::wstring& wstr);

//#ifdef UNICODE
//	wstring __declspec(dllexport) getMyDocumentPath();// 获取“我的文档”路径  
//#else
//	string __declspec(dllexport) getMyDocumentPath();
//#endif // UNICODE

    // vector -> string
    std::string DOGE_EXPORT vectorToString(std::vector<std::string> vec, std::string delimiter);
    // string -> vector
    void DOGE_EXPORT stringToVector(std::vector<std::string>& vec, std::string str, std::string delimiter);

    std::string DOGE_EXPORT getAppPath();
    std::string DOGE_EXPORT generateUuid();
    std::string DOGE_EXPORT getEndpoint(const std::string & protocol, const std::string& ip, const std::string& port);

    void DOGE_EXPORT sleep(uint32_t ms);

    const std::string encrypt(const std::string key, const std::string plain);
    const std::string decrypt(const std::string key, const std::string cipher);
}
