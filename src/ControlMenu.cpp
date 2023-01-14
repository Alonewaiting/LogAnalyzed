#include "ControlMenu.h"
#include "LogUtils.h"

#ifdef WIN32
#include "windows.h"
//str:要转换的窄字符串
//len:接受转换成功后宽字符的长度,可直接填NULL,不接收
wchar_t* AtoW(const char* str, size_t len)
{
    int wcLen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    wchar_t* newBuf = new wchar_t[wcLen + 1]{};
    MultiByteToWideChar(CP_ACP, 0, str, -1, newBuf, wcLen);
    if (len != NULL) {
        len = wcLen;
    }
    return newBuf;
}
//str:要转换的宽字符串
//len:接受转换成功后窄字符的长度,可直接填NULL,不接收
char* WtoA(const wchar_t* str, size_t len)
{
    int cLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, 0, NULL);
    char* newBuf = new char[cLen + 1]{};
    WideCharToMultiByte(CP_ACP, 0, str, -1, newBuf, cLen, 0, NULL);
    if (len != NULL) {
        len = cLen;
    }
    return newBuf;
}   

#endif
ControlMenu::ControlMenu():m_stringCondition({}),m_group({})
{
    m_stringCondition.clear();
    m_group.clear();
}

ControlMenu::~ControlMenu()
{

}

void ControlMenu::show()
{
    ImGui::Text("Add Filter Condition");
    bool append = ImGui::Button("+");ImGui::SameLine(100);bool sub = ImGui::Button("-");
    if (append && m_group.size() < 1000) {
        m_group.push_back({});
        m_stringCondition.push_back({});
    }
    if (sub && m_group.size() > 0) {
        m_group.pop_back();
        m_stringCondition.pop_back();
    }
    if (m_group.size() != m_stringCondition.size()) {
        LOGE("size not equal");
        return;
    }
    for (size_t i = 0; i < m_group.size();++i) {
        std::string index = "Include String_" + std::to_string(i);
        std::string inputString ="Input String_" +std::to_string(i);
        ImGui::Checkbox(index.c_str(), &m_group[i].m_check);
        ImGui::SameLine(200); 
        ImGui::InputText(inputString.c_str(), m_group[i].m_str, IM_ARRAYSIZE(m_group[i].m_str));
        m_stringCondition[i].m_isExit = m_group[i].m_check;
        m_stringCondition[i].m_str = m_group[i].m_str;
        LOGW("check = %d, str = %s", m_stringCondition[i].m_isExit, m_stringCondition[i].m_str.c_str());
    }
   

}

std::vector<StringCondition> ControlMenu::getFilterConditon()
{
    return m_stringCondition;
}

