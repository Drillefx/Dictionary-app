#include "dictionary_manager.h"
#include "logger.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

static std::string normalize(const std::string& word) {
    std::string result;
    for (char ch : word) {
        if (std::isalpha(ch)) result += std::tolower(ch);
    }
    return result;
}

void DictionaryManager::loadWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        Logger::log(LogLevel::ERROR, "Failed to open file: " + filename);
        throw std::runtime_error("File not found");
    }

    std::string line, word;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        while (ss >> word) {
            std::string clean = normalize(word);
            if (!clean.empty()) {
                wordMap[clean]++;
            }
        }
    }

    Logger::log(LogLevel::INFO, "Words loaded from file: " + filename);
}

void DictionaryManager::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        Logger::log(LogLevel::ERROR, "Failed to save file: " + filename);
        throw std::runtime_error("Cannot write to file");
    }

    for (const auto& [word, count] : wordMap) {
        out << word << " " << count << "\n";
    }

    Logger::log(LogLevel::INFO, "Dictionary saved to file: " + filename);
}

void DictionaryManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        Logger::log(LogLevel::ERROR, "Failed to open saved dictionary: " + filename);
        throw std::runtime_error("Saved dictionary not found");
    }

    wordMap.clear();
    std::string word;
    int count;
    while (in >> word >> count) {
        wordMap[word] = count;
    }

    Logger::log(LogLevel::INFO, "Dictionary loaded from saved file: " + filename);
}

std::vector<std::pair<std::string, int>> DictionaryManager::getAlphabeticallySorted() const {
    return std::vector<std::pair<std::string, int>>(wordMap.begin(), wordMap.end());
}

std::vector<std::pair<std::string, int>> DictionaryManager::getFrequencySorted() const {
    std::vector<std::pair<std::string, int>> vec(wordMap.begin(), wordMap.end());
    std::sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return b.second < a.second; // descending
    });
    return vec;
}
