#include "dictionary_manager.h"
#include "logger.h"
#include <iostream>
#include <string>

void showMenu() {
    std::cout << YELLOW << "\n==== Dictionary App ====\n" << RESET;
    std::cout << "1. " << GREEN << "Load words from file" << RESET << "\n";
    std::cout << "2. " << GREEN << "Show dictionary (A-Z)" << RESET << "\n";
    std::cout << "3. " << GREEN << "Show dictionary (by frequency)" << RESET << "\n";
    std::cout << "4. " << GREEN << "Save dictionary to file" << RESET << "\n";
    std::cout << "5. " << GREEN << "Load dictionary from file" << RESET << "\n";
    std::cout << "6. " << GREEN << "Search for a word" << RESET << "\n";
    std::cout << "0. " << RED   << "Exit" << RESET << "\n";
    std::cout << YELLOW << "Choose an option: " << RESET;
}



void displayWords(const std::vector<std::pair<std::string, int>>& words) {
    for (const auto& [word, count] : words) {
        std::cout << BLUE << word << RESET << " : "
                  << GREEN << count << RESET << "\n";
    }
}


int main() {
    DictionaryManager dict;
    Logger::log(LogLevel::INFO, "Program started.");
    
    int choice;
    std::string filename;

    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // flush newline

        try {
            switch (choice) {
                case 1:
                    std::cout << "Enter path to text file: ";
                    std::getline(std::cin, filename);
                    dict.loadWordsFromFile(filename);
                    break;

                case 2:
                    displayWords(dict.getAlphabeticallySorted());
                    break;

                case 3:
                    displayWords(dict.getFrequencySorted());
                    break;

                case 4:
                    std::cout << "Enter path to save dictionary: ";
                    std::getline(std::cin, filename);
                    dict.saveToFile(filename);
                    break;

                case 5:
                    std::cout << "Enter path to load saved dictionary: ";
                    std::getline(std::cin, filename);
                    dict.loadFromFile(filename);
                    break;

                case 6: {
                        std::cout << "Enter word to search: ";
                        std::string searchWord;
                        std::getline(std::cin, searchWord);
                        
                        // Normalize like we did when loading
                        std::string clean;
                        for (char ch : searchWord) {
                            if (std::isalpha(ch)) clean += std::tolower(ch);
                        }
                    
                        if (clean.empty()) {
                            std::cout << RED << "Please enter a valid word.\n" << RESET;
                            break;
                        }
                    
                        const auto& wordMap = dict.getAlphabeticallySorted(); // reuse sorted list
                        auto it = std::find_if(wordMap.begin(), wordMap.end(), [&](const auto& p) {
                            return p.first == clean;
                        });
                    
                        if (it != wordMap.end()) {
                            std::cout << GREEN << "Word found: " << RESET
                                      << BLUE << it->first << RESET
                                      << " appears " << GREEN << it->second << RESET << " times.\n";
                        } else {
                            std::cout << RED << "Word not found in the dictionary.\n" << RESET;
                        }
                        break;
                    }
                        
                case 0:
                    Logger::log(LogLevel::INFO, "Program exited.");
                    std::cout << "Bye!\n";
                    return 0;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}

