#ifdef WIN32
#include "WindowsUtils.h"
wchar_t* WindowsUtils::AtoW(const char* str, size_t len)
{
    int wcLen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    wchar_t* newBuf = new wchar_t[wcLen + 1]{};
    MultiByteToWideChar(CP_ACP, 0, str, -1, newBuf, wcLen);
    if (len != NULL) {
        len = wcLen;
    }
    return newBuf;
}

char* WindowsUtils::WtoA(const wchar_t* str, size_t len)
{
    int cLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, 0, NULL);
    char* newBuf = new char[cLen + 1]{};
    WideCharToMultiByte(CP_ACP, 0, str, -1, newBuf, cLen, 0, NULL);
    if (len != NULL) {
        len = cLen;
    }
    return newBuf;
}

std::string WindowsUtils::getFileName()
{
    std::string output;
    OPENFILENAMEW ofn;
    WCHAR szFile[100];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"ÎÄ¼þ¼Ð\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileNameW(&ofn)) {
        output = WtoA(szFile,sizeof(szFile));
        return output;
    }
    return "";
}

std::string WindowsUtils::getFilePath()
{
    return std::string();
}

#else
wchar_t* WindowsUtils::AtoW(const char* str, size_t len){}
char* WindowsUtils::WtoA(const wchar_t* str, size_t len){}
std::string WindowsUtils::getFileName(){}
std::string WindowsUtils::getFilePath(){}
#endif


