#include "ControlMenu.h"
#include "LogUtils.h"


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

