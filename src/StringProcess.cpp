#include "StringProcess.h"
StringProcess::StringProcess()
{

}

StringProcess::~StringProcess()
{

}

std::string StringProcess::processString(const std::string& inString,const  std::regex& re)
{
    std::string output = "";
    if (inString.empty() || re._Empty()) {
        return output;
    }

    if (std::regex_search(inString, re)) {
        output = inString;
    }
    return output;
}

std::string StringProcess::processString(const std::string& string, const StringCondition& conditon)
{
    std::string output = "";
    if (string.empty() || conditon.m_str.empty()) {
        return output;
    }
    std::regex re(conditon.m_str);
    if (conditon.m_isExit) {
        if (std::regex_search(string, re)) {
            return string;
        }
    }
    else {
        if (!std::regex_search(string, re)) {
            return string;
        }
    }
   
    return output;
}

std::string StringProcess::processString(const std::string& string, const std::vector<StringCondition>& conditions)
{
    std::string output = "";
    if (string.empty() || conditions.empty()) {
        return output;
    }
    bool isOk = true;
    for (auto& conditon : conditions) {
         auto str = processString(string,conditon);
         if (str.empty()) {
             isOk = false;
             break;
         }
    }
    if (isOk) {
        return string;
    }
    return output;
}

