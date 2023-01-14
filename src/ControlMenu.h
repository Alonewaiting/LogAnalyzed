/*!
 * \file ControlMenu.h
 *
 * \author dwy
 * \date 2023/1/14
 *
 * 
 */
 #pragma once

#include "imgui.h"
#include "DataDef.h"
class ControlMenu {

public:
    ControlMenu();
    ~ControlMenu();
    void show();
    std::vector<StringCondition> getFilterConditon();

private:
    struct MenuGroup
    {
        char m_str[500] = "hello world";
        size_t m_strSize = 500;
        bool m_check = false;
    }; 
    std::vector<StringCondition> m_stringCondition;
    std::vector<MenuGroup> m_group;
   
};
