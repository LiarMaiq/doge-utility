//#include "stdafx.h"
// Windows
//#include <Windows.h>
//#include <shellapi.h>
//#include <tchar.h>
//#include <corecrt_io.h>
//#include <ShlObj.h>
// STL
#include <string>
#include <list>
#include <locale> 
#include <codecvt>
#include <stdio.h>
#include <errno.h>
#include <string.h>
// Project
#include "Utility.h"

#if defined(_WIN32)
#include <objbase.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <uuid/uuid.h>
#include <iconv.h>
#endif

using namespace std;


//bool Doge_Utility::copyFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags)
//{
//	TCHAR pTo[MAX_PATH] = { 0 };
//	_tcscpy_s(pTo, _pTo);
//	TCHAR pFrom[MAX_PATH] = { 0 };
//	_tcscpy_s(pFrom, _pFrom);
//
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pTo[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pTo[i + 1] = '\0';
//			break;
//		}
//	}
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pFrom[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pFrom[i + 1] = '\0';
//			break;
//		}
//	}
//
//	SHFILEOPSTRUCT FileOp = { 0 };
//	FileOp.fFlags = flags;
//	FileOp.pFrom = pFrom;
//	FileOp.pTo = pTo;
//	FileOp.wFunc = FO_COPY;
//	return SHFileOperation(&FileOp) == 0;
//}
//
//bool Doge_Utility::renameFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags)
//{
//	TCHAR pTo[MAX_PATH] = { 0 };
//	_tcscpy_s(pTo, _pTo);
//	TCHAR pFrom[MAX_PATH] = { 0 };
//	_tcscpy_s(pFrom, _pFrom);
//
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pTo[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pTo[i + 1] = '\0';
//			break;
//		}
//	}
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pFrom[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pFrom[i + 1] = '\0';
//			break;
//		}
//	}
//
//	SHFILEOPSTRUCT FileOp = { 0 };
//	FileOp.fFlags = flags;
//	FileOp.pFrom = pFrom;
//	FileOp.pTo = pTo;
//	FileOp.wFunc = FO_RENAME;
//	return SHFileOperation(&FileOp) == 0;
//}
//
///****************************************************************************
//删除文件或者文件夹,需要把路径添加2个/0/0
//****************************************************************************/
//bool Doge_Utility::deleteFile(const TCHAR* _pFrom, WORD flags)
//{
//	TCHAR pFrom[MAX_PATH] = { 0 };
//	_tcscpy_s(pFrom, _pFrom);
//
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pFrom[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pFrom[i + 1] = '\0';
//			break;
//		}
//	}
//
//	SHFILEOPSTRUCT FileOp = { 0 };
//	FileOp.pFrom = pFrom;
//	FileOp.pTo = NULL;                //一定要是NULL
//	FileOp.fFlags = flags;
//	FileOp.wFunc = FO_DELETE;//删除操作
//	return SHFileOperation(&FileOp) == 0;
//}
//
///****************************************************************************
//移动文件或者文件夹,需要把路径添加2个/0/0
//****************************************************************************/
//bool Doge_Utility::moveFile(const TCHAR *_pFrom, const TCHAR *_pTo, WORD flags)
//{
//	TCHAR pTo[MAX_PATH] = { 0 };
//	_tcscpy_s(pTo, _pTo);
//	TCHAR pFrom[MAX_PATH] = { 0 };
//	_tcscpy_s(pFrom, _pFrom);
//
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pTo[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pTo[i + 1] = '\0';
//			break;
//		}
//	}
//	for (size_t i = 0; i < MAX_PATH; i++)
//	{
//		if (pFrom[i] == '\0' && i + 1<MAX_PATH)
//		{
//			pFrom[i + 1] = '\0';
//			break;
//		}
//	}
//
//	SHFILEOPSTRUCT FileOp = { 0 };
//	FileOp.fFlags = flags;
//	FileOp.pFrom = pFrom;
//	FileOp.pTo = pTo;
//	FileOp.wFunc = FO_MOVE;
//	return SHFileOperation(&FileOp) == 0;
//}


std::string Doge_Utility::utf8ToAnsi(const std::string & str)
{
    std::string retStr;
#ifdef _WIN32
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	retStr = pBuf;
	delete[]pBuf;
	delete[]pwBuf;
	pBuf = NULL;
	pwBuf = NULL;
#else
    size_t nLen = str.length();
    size_t nLenOut = nLen + 1;
    char * pBuf = new char[nLenOut];
	memset(pBuf, 0, nLenOut);
    char * out = pBuf;
    char *in = (char*)str.c_str();
    iconv_t cd = iconv_open("gb2312", "utf-8");
    if (iconv(cd, &in, &nLen, &out, &nLenOut) != (size_t)-1)
	    retStr = pBuf;
    iconv_close(cd);
	delete[] pBuf;
	pBuf = NULL;

#endif
	return retStr;
}

//------------------------------------------------------------------------ 
std::string Doge_Utility::ansiToUtf8(const std::string & str)
{
    std::string retStr;
#ifdef _WIN32
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t * pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	retStr = pBuf;
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
#else
    size_t nLen = str.length();
    size_t nLenOut = nLen*2 + 1;
    char * pBuf = new char[nLenOut];
	memset(pBuf, 0, nLenOut);
    char * out = pBuf;
    char *in = (char*)str.c_str();
    iconv_t cd = iconv_open("utf-8", "gb2312");
    if (iconv(cd, &in, &nLen, &out, &nLenOut) != (size_t)-1)
	    retStr = pBuf;
    iconv_close(cd);
	delete[] pBuf;
	pBuf = NULL;

#endif
	return retStr;
}

std::wstring Doge_Utility::ansiToUtf16(const std::string& str)
{
    std::wstring wstr;
    if (str.empty())
        return wstr;
#ifdef _WIN32
    int wLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, NULL);
    wchar_t* ps = new wchar_t[wLen + 1];
    memset(ps, 0, 2 * (wLen + 1));
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), ps, wLen + 1);
    wstr = ps;
    delete[] ps;
#else
    std::string u8str = ansiToUtf8(str);
    std::wstring_convert<std::codecvt_utf16<wchar_t>> utf8_conv;
    wstr = utf8_conv.from_bytes(u8str);
#endif
    return wstr;
}


std::string Doge_Utility::utf16ToAnsi(const std::wstring& wstr)
{
    std::string str;
    if (wstr.empty())
        return str;
#ifdef _WIN32
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, NULL, NULL, NULL);
    char* ps = new char[len + 1];
    memset(ps, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), ps, len + 1, NULL, NULL);
    str = ps;
    delete[] ps;
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    std::string u8str = utf8_conv.to_bytes(wstr);
    str = utf8ToAnsi(u8str);
#endif
    return str;
}

//#ifdef UNICODE
//wstring Doge_Utility::getMyDocumentPath()      // 获取“我的文档”路径  
//{
//	WCHAR szDocument[MAX_PATH] = { 0 };
//	LPITEMIDLIST pidl = NULL;
//	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);
//	if (pidl && SHGetPathFromIDListW(pidl, szDocument))
//	{
//		return wstring(szDocument);
//	}
//	return wstring();
//}
//#else
//string BcgWL_Utility::getMyDocumentPath()
//{
//	CHAR szDocument[MAX_PATH] = { 0 };
//	LPITEMIDLIST pidl = NULL;
//	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);
//	if (pidl && SHGetPathFromIDListA(pidl, szDocument))
//	{
//		return string(szDocument);
//	}
//	return string();
//}
//#endif // UNICODE

std::string Doge_Utility::getAppPath()
{
    char path[MAX_PATH];
    std::string s_path;

#if defined(_WIN32)
    ::GetModuleFileNameA(::GetModuleHandleA(0), path, MAX_PATH);
    s_path = path;
    int slashIndex1 = s_path.rfind('\\');
    int slashIndex2 = s_path.rfind('/');
    int nLen = slashIndex1 > slashIndex2 ? slashIndex1 : slashIndex2;
    s_path = s_path.substr(0U, nLen);
    s_path += "/";
#else
    //获取当前程序绝对路径
    int cnt = readlink("/proc/self/exe", path, MAX_PATH);
    if (cnt < 0 || cnt >= MAX_PATH)
    {
        return "";
    }
    //获取当前目录绝对路径，即去掉程序名
    int i;
    for (i = cnt; i >= 0; --i)
    {
        if (path[i] == '/')
        {
            path[i + 1] = '\0';
            break;
        }
    }
    s_path = path;
#endif

    return s_path;
}

std::string Doge_Utility::generateUuid()
{
    char buf[GUID_LEN] = { 0 };

#if defined(_WIN32)
    GUID guid;

    if (!CoCreateGuid(&guid))
    {
        sprintf_s(buf,
            "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
            guid.Data1, guid.Data2, guid.Data3,
            guid.Data4[0], guid.Data4[1], guid.Data4[2],
            guid.Data4[3], guid.Data4[4], guid.Data4[5],
            guid.Data4[6], guid.Data4[7]);
    }
#else
    uuid_t uu;
    uuid_generate(uu);

    int32_t index = 0;
    for (int32_t i = 0; i < 16; i++)
    {
        int32_t len = i < 15 ?
            sprintf(buf + index, "%02X-", uu[i]) :
            sprintf(buf + index, "%02X", uu[i]);
        if (len < 0)
            return std::move(std::string(""));
        index += len;
    }
#endif

    return std::move(std::string(buf));
}

std::string Doge_Utility::getEndpoint(const std::string & protocol, const std::string & ip, const std::string & port)
{
    if (port.empty())
        return std::string(protocol + "://" + ip);
    return std::string(protocol + "://" + ip + ":" + port);
}

// vector -> string
std::string Doge_Utility::vectorToString(std::vector<std::string> vec, std::string delimiter)
{
    std::string str;
    if (vec.empty())
        return str;

    for (size_t i = 0; i < vec.size(); i++)
    {
        str += vec[i];
        if ((i + 1) < vec.size())
            str += delimiter;
    }

    return str;
}

// string -> vector
void Doge_Utility::stringToVector(std::vector<std::string>& vec, std::string str, std::string delimiter)
{
    if (str.empty())
        return;

    size_t index = str.find(delimiter);
    if (index != std::string::npos)
    {
        std::string strTemp = str.substr(0, index);
        vec.push_back(strTemp);
        str = str.substr(index + delimiter.length());
        stringToVector(vec, str, delimiter);
    }
    else
        vec.push_back(str);

    return;
}
