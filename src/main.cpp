
#include <iostream>
#include <fstream>
#include <string>
#include "../headers/HashTable.h"
#include "../headers/Timer.h"
#include <unordered_map>
#include <algorithm>
#include <regex>



bool sortByValue(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return (a.second > b.second);
}


// Find Get first if it is not founded search for HTPP/1.0
// if you haven't find this to search "." and take left and right side of "." 
std::string addToHash(const std::string& key) {
    bool found = false;
    std::string filename;

    size_t start_pos = key.find("GET");
    if (start_pos != std::string::npos) {
        start_pos += 4; // Skip "GET"
        size_t end_pos;
        end_pos = key.find(" HTTP/1.0", start_pos);
        if (end_pos != std::string::npos) {
            found = true;
            filename = key.substr(start_pos, end_pos - start_pos);
        }
    }

    if (!found) {
        size_t dot_pos = key.find('.');
        if (dot_pos != std::string::npos) {
            size_t start_pos = key.rfind(' ', dot_pos);
            if (start_pos != std::string::npos)
                ++start_pos;
            else
                start_pos = 0;

            size_t end_pos = key.find(' ', dot_pos);
            if (end_pos == std::string::npos)
                end_pos = key.find('"', dot_pos);
            if (end_pos == std::string::npos)
                end_pos = key.length();

            filename = key.substr(start_pos, end_pos - start_pos);

            filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
            filename.erase(std::remove(filename.begin(), filename.end(), '"'), filename.end());
        }
    }

    return filename;
}

int main() {
    HashMap wordCount;
    std::ifstream inFile("../logs/access_log.txt");

    Timer timer;
    timer.start();
    if (inFile.is_open()) {
        std::string line;

        while (std::getline(inFile, line)) {
            wordCount.increment(line);
        }
        inFile.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
    wordCount.sort_and_print();

    std::cout << timer.elapsed() << std::endl;


    timer.stop();
    // Starts unordered
    std::unordered_map<std::string, int> unorderedWordCount;
    std::ifstream inFile2("../logs/access_log.txt");
    Timer timer2;
    timer2.start();
    if (inFile2.is_open()) {
        std::string line2;

        while (std::getline(inFile2, line2)) {
            std::string x = addToHash(line2);
            if (unorderedWordCount.find(x) != unorderedWordCount.end()) {
                unorderedWordCount[x]++;
            }
            else {
                unorderedWordCount[x] = 1;
            }
        }
        inFile2.close();  // Close the correct file stream
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }


    std::vector<std::pair<std::string, int>> sortedEntries(unorderedWordCount.begin(), unorderedWordCount.end());
    std::sort(sortedEntries.begin(), sortedEntries.end(), sortByValue);
    std::cout << "Top 10 from std::unordered_map:" << std::endl;
    for (int i = 0; i < std::min(10, static_cast<int>(sortedEntries.size())); ++i) {
        std::cout << sortedEntries[i].first << ": " << sortedEntries[i].second << " times" << std::endl;
    }

    std::cout << timer2.elapsed() << " seconds" << std::endl;

}