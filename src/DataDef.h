/*!
 * \file DataDef.h
 *
 * \author dwy
 * \date 2023/1/14
 *
 * 
 */
 #pragma once
#include <string>
#include <vector>
struct LineInfo {
    std::string m_string = "";
    size_t m_line = -1;
    LineInfo() {}
    LineInfo(const std::string& str, const size_t& line) : m_string(str), m_line(line) {}
};
struct StringCondition
{
    std::string m_str;
    bool m_isExit;
    StringCondition() {}
    StringCondition(const std::string& str, bool exit) : m_str(str), m_isExit(exit) {}

};
