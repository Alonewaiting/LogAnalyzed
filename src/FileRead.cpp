#include "FileRead.h"
#include "LogUtils.h"
FileReader::FileReader(const std::string& fileName)
{
    if (m_file.is_open()) {
        LOGE("file is open");
        return;
    }
    m_file.open(fileName,std::ios::in);
    m_lineIndex = 0;
}

FileReader::FileReader()
{
}

FileReader::~FileReader()
{
    close();
}

LineInfo FileReader::readOneLine()
{
    char line[1024] = {};
    if (m_file.is_open()) {
        m_file.getline(line,1024);
        return { line, m_lineIndex++ };
    }
    return {};
}

std::vector<LineInfo> FileReader::readAll()
{
    if (!m_file.is_open()) {
        return {};
    }
    
    m_file.seekg(0, std::ios::beg);
    m_lineIndex = 0;
    std::vector<LineInfo> output;
    output.reserve(1024);
    char buf[1024];
    while (m_file.getline(buf,1024))
    {
        output.push_back({buf,m_lineIndex++});
    }
    return output;
}

std::vector<LineInfo> FileReader::readLine(size_t lines, bool seek)
{
    if (!m_file.is_open()) {
        return {};
    }
    if (seek) {
        m_file.seekg(0, std::ios::beg);
        m_lineIndex = 0;
    }
    std::vector<LineInfo> output;
    output.reserve(lines);
    char buf[1024];
    while (m_file.getline(buf, 1024) && lines--)
    {
        output.push_back({ buf,m_lineIndex++ });
    }
    return output;
}

LineInfo FileReader::readIndexLine(size_t lineIndex)
{
    if (!m_file.is_open()) {
        LOGE("file is open");
        return {};
    }
    seekToLine(lineIndex);
    char buf[1024];
    m_file.getline(buf, 1024);
    return {buf, m_lineIndex++};
}

bool FileReader::close()
{
    if (m_file.is_open()) {
        m_file.close();
    }
    return true;
}

bool FileReader::open(const std::string& fileName)
{
    if (m_file.is_open()) {
        m_file.close();
      
    }
    m_file.open(fileName, std::ios::in);
    return !m_file.fail();
}

bool FileReader::isOpen() const
{
    return m_file.is_open();
}

void FileReader::seekToLine(size_t line)
{
    if (!m_file.is_open()) {
        return;
    }
    int i;
    char buf[1024];
    m_file.seekg(0, std::ios::beg);  //定位到文件开始。
    m_lineIndex = 0;
    for (i = 0; i < line; i++)
    {
        m_file.getline(buf, sizeof(buf));//读取行。
        m_lineIndex++;
    }
    return;
}

