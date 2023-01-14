/*!
 * \file TextShow.h
 *
 * \author dwy
 * \date 2023/1/14
 *
 * 
 */
 #pragma once
#include <string>
#include <vector>
#include "DataDef.h"
#include "imgui.h"
class TextShow {
public:
    TextShow(const std::string& windowName = "Text Show");
    ~TextShow();
    void init(const std::string& windowName = "Text Show");
    bool showData(const std::vector<LineInfo> & data);
    void setSizeRatio(const ImVec2 &SizeRatio = {1.0f,1.0f});
private:
    std::string m_winName;
    int track_item = 100;
    bool enable_track = true;
    ImVec2 m_sizeRatio;
};
