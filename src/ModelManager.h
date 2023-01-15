/*!
 * \file ModulManager.h
 *
 * \author dwy
 * \date 2023/1/15
 *
 * 
 */
 #pragma once
#include <map>
#include "DataDef.h"
class ModelManager {
public:
    ModelManager();
    ~ModelManager();
    std::map<std::string, std::vector<StringCondition>> getMoudel() const;
    bool insert(const std::string& , const std::vector<StringCondition>& );
    std::vector<StringCondition> get(const std::string&) const;
private:
    void init();
    void save();
private:
    std::map<std::string,std::vector<StringCondition>> m_moudle;
    std::string m_jsonPath;

};
