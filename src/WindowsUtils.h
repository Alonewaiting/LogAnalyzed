/*!
 * \file WindowsUtils.h
 *
 * \author dwy
 * \date 2023/1/14
 *
 * 
 */
 #pragma once
#ifdef WIN32
#include "windows.h"
#endif
#include <string>
class WindowsUtils {
public:
    //str:要转换的窄字符串
    //len:接受转换成功后宽字符的长度,可直接填NULL,不接收
   static wchar_t* AtoW(const char* str, size_t len);

    //str:要转换的宽字符串
    //len:接受转换成功后窄字符的长度,可直接填NULL,不接收
   static char* WtoA(const wchar_t* str, size_t len);
   static std::string getFileName();
   static std::string getFilePath();


};



