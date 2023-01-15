#include <fstream>
#include <sstream>
#include"ModelManager.h"
#include "LogUtils.h"
#include "cJSON.h"
#include "cJSON_Utils.h"
#include "WindowsUtils.h"
#define  MAX_PATH 2048

ModelManager::ModelManager()
{
    wchar_t szCurPath[MAX_PATH] = L"D:\\Path";
    GetCurrentDirectoryW(sizeof(szCurPath), szCurPath);			//获取当前工作目录
    std::string path = WindowsUtils::WtoA(szCurPath, sizeof(szCurPath));
    m_jsonPath = path + "\\moudle.json";
    m_moudle.clear();
    init();
}

ModelManager::~ModelManager()
{
    save();
}

std::map<std::string, std::vector<StringCondition>> ModelManager::getMoudel() const
{
    return m_moudle;
}

bool ModelManager::insert(const std::string& str, const std::vector<StringCondition>& val)
{
    if (m_moudle.find(str) != m_moudle.end()) {
        LOGW("insert error beacese has same modul key");
        return false;
    }
    m_moudle.insert({ str , val});
    return true;
}

std::vector<StringCondition> ModelManager::get(const std::string& str) const
{
    auto iter = m_moudle.find(str);
    if (iter != m_moudle.end()) {
        return iter->second;
    }
    return {};
}

void ModelManager::init()
{
   
    std::fstream in(m_jsonPath,std::ios::in | std::ios::binary);
    if (!in.good()) {
       LOGW("read modul faild");
       return;
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string data(buffer.str());
    in.close();

    cJSON * root = cJSON_Parse(data.c_str());
    if (!root) {
        LOGW("don't have any module");
        return;
    }
    m_moudle.clear();
    cJSON* array_node = cJSON_GetObjectItem(root, "Model Size");
    while (array_node->next != NULL)
    {
        array_node = array_node->next;
        int arraySize = cJSON_GetArraySize(array_node);
        std::vector<StringCondition> conditions;
        for (int i = 0; i < arraySize; ++i) {
            auto item = cJSON_GetArrayItem(array_node,i);
            if (item) {
                auto key = cJSON_GetObjectItem(item, "m_str");
                auto val = cJSON_GetObjectItem(item, "m_isExit");
                if (key && val) {
                    bool boolVal = val->type & 0x03 ? (val->type & 0x01 ? false : true ) : false;
                    conditions.push_back({key->valuestring,boolVal });
                }
            }
        }
        if (conditions.empty()) {
            continue;
        }
        m_moudle.insert({array_node->string,conditions});
    }
}
void ModelManager::save()
{
    //创建空对象
    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root,"Model Size",m_moudle.size());
    for (auto& moudle : m_moudle) {
        cJSON* array = NULL;
        
        cJSON_AddItemToObject(root, moudle.first.c_str(), array = cJSON_CreateArray());
        for (auto& val : moudle.second) {
            //添加数组对象
            cJSON* obj = NULL;
            cJSON_AddItemToArray(array, obj = cJSON_CreateObject());
            cJSON_AddStringToObject(obj, "m_str", val.m_str.c_str());
            cJSON_AddBoolToObject(obj, "m_isExit", val.m_isExit);
        }
    }
    char* buf = cJSON_Print(root);
    if (!buf) {
        return;
    }
    std::fstream out(m_jsonPath, std::ios::out);
    out.write(buf,strlen(buf));
    out.close();
}

