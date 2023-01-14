/*!
 * \file StringProcess.h
 *
 * \author dwy
 * \date 2023/1/14
 *
 * 
 */
 #pragma once
#include <vector>
#include <string>
#include <regex>
#include "DataDef.h"
class StringProcess {
public:
    StringProcess();
    ~StringProcess();
    std::string processString(const std::string & string,const std::regex& match);
    std::string processString(const std::string& string,const StringCondition & conditon);
    std::string processString(const std::string & string, const std::vector<StringCondition> & condition);



};