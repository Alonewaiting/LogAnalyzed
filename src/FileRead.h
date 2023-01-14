/*!
 * \file FileRead.h
 *
 * \author dwy
 * \date 2023/1/14
 *
 * 
 */
 #pragma once
#include <string>
#include <vector>
#include <fstream>
#include "DataDef.h"
class FileReader {
public:
    FileReader(const std::string& fileName);
    ~FileReader();
    LineInfo readOneLine();
    std::vector<LineInfo> readAll();
    std::vector<LineInfo> readLine(size_t lines,bool seek = false);
    LineInfo readIndexLine(size_t lineIndex);
    bool close();
    bool open(const std::string& fileName);
    bool isOpen() const;
private:
    void seekToLine(size_t line);

private:
    std::ifstream m_file;
    size_t m_lineIndex;

};
