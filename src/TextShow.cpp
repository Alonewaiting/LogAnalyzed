#include "TextShow.h"

TextShow::TextShow(const std::string& windowName /*= "Text Show"*/)
{
    m_winName = windowName;
}

TextShow::~TextShow()
{

}

void TextShow::init(const std::string& windowName /*= "Text Show"*/)
{

}

bool TextShow::showData(const std::vector<LineInfo>& inputDatas)
{
    if (inputDatas.empty()) {
        return false;
    }

    ImGui::Checkbox("Track", &enable_track);
    ImGui::PushItemWidth(100);
    ImGui::SameLine(140); enable_track |= ImGui::DragInt("##line", &track_item, 0.25f, 0, 99, "line = %d");
    ImGui::PopItemWidth();

    ImGuiStyle& style = ImGui::GetStyle();

    
    ImVec2 size = { ImGui::GetContentRegionAvail().x * m_sizeRatio.x , ImGui::GetContentRegionAvail().y * m_sizeRatio.y};
    const char* names = "Center";
    ImGui::TextUnformatted(names);

    const ImGuiWindowFlags child_flags = 0;
    const ImGuiID child_id = ImGui::GetID((void*)(intptr_t)2);
    const bool child_is_visible = ImGui::BeginChild(child_id, size, true, child_flags);
    if (ImGui::BeginMenuBar())
    {
        ImGui::TextUnformatted("abc");
        ImGui::EndMenuBar();
    }
    
    if (child_is_visible) // Avoid calling SetScrollHereY when running with culled items
    {
        for (int item = 0; item < inputDatas.size(); item++)
        {
            auto data = inputDatas[item];
            if (enable_track && item == track_item)
            {
                ImGui::TextColored(ImVec4(1, 1, 0, 1), "Line %d %s", data.m_line,data.m_string.c_str());
                ImGui::SetScrollHereY(2 * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
            }
            else
            {
                ImGui::Text("Line %d %s", data.m_line, data.m_string.c_str());
            }
        }
    }
    float scroll_y = ImGui::GetScrollY();
    float scroll_max_y = ImGui::GetScrollMaxY();
    ImGui::EndChild();
    ImGui::Text("%d/%d", track_item, inputDatas.size());
   

}

void TextShow::setSizeRatio(const ImVec2& SizeRatio)
{
    m_sizeRatio = SizeRatio;
}
