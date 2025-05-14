#pragma once
#include <map>
#include <vector>
#include <string>

class DictionaryManager {
private:
    std::map<std::string, int> wordMap;

public:
    void loadWordsFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    
    std::vector<std::pair<std::string, int>> getAlphabeticallySorted() const;
    std::vector<std::pair<std::string, int>> getFrequencySorted() const;
};
