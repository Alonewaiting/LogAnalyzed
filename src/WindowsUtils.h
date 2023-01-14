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
    //str:Ҫת����խ�ַ���
    //len:����ת���ɹ�����ַ��ĳ���,��ֱ����NULL,������
   static wchar_t* AtoW(const char* str, size_t len);

    //str:Ҫת���Ŀ��ַ���
    //len:����ת���ɹ���խ�ַ��ĳ���,��ֱ����NULL,������
   static char* WtoA(const wchar_t* str, size_t len);
   static std::string getFileName();
   static std::string getFilePath();


};



