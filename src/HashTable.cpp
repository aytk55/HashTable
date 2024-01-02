
#include "../headers/HashTable.h"
#include <algorithm>

size_t HashMap::hash(const std::string& key) const {
    size_t hashValue = 0;
    for (char c : key) {
        hashValue = hashValue * 31 + static_cast<size_t>(c);
    }
    return hashValue % InitialCapacity;
}

size_t HashMap::linearProbe(size_t index) const {
    while (!data[index].filename.empty()) {
        index = (index + 1) % InitialCapacity;
    }
    return index;
}

HashMap::HashMap() : data(InitialCapacity) {}

void HashMap::increment(const std::string& key) {
    bool found = false;
    std::string filename;
    // Find GET  
    size_t start_pos = key.find("GET");
    // If GET not nil  search for " HTTP/1.0"
    if (start_pos != std::string::npos) {
        start_pos += 4; // Skip "GET"
        size_t end_pos = key.find(" HTTP/1.0", start_pos);
        if (end_pos != std::string::npos) {
            found = true;
            filename = key.substr(start_pos, end_pos - start_pos);
        }
    }

    if (!found) {
        // If found false find . and take between left and right the "."
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

    if (filename.empty()) {
        return;
    }

    // Hash ve linear probing işlemleri
    size_t index = hash(filename);
    while (!data[index].filename.empty() && data[index].filename != filename) {
        index = (index + 1) % InitialCapacity;
    }

    // Eğer bulunduysa artır, bulunamadıysa ekleyerek artır
    if (!data[index].filename.empty()) {
        data[index].count++;
    }
    else {
        data[index].filename = filename;
        data[index].count = 1;
    }
}

void HashMap::sort_and_print() const {
    int counter = 0;
    std::vector<HashNode> allElements;

    for (const auto& node : data) {
        if (!node.filename.empty()) {
            allElements.push_back(node);
        }
    }

    // sort the vector
    std::sort(allElements.begin(), allElements.end(), [&](const HashNode& a, const HashNode& b) -> bool {
        return a.count > b.count;
    });

    // print out sorted data
    for (const auto& node : allElements) {
        std::cout << node.filename << " : " << node.count << std::endl;
        counter++;
        if (counter >= 10)
            break;
    }
}
// We are giving value and it's returning count of that value
int HashMap::count(const std::string& key) const {
    size_t index = hash(key);
    while (!data[index].filename.empty() && data[index].filename != key) {
        index = (index + 1) % InitialCapacity;
    }
    return data[index].count;
}

int HashMap::total_count() const {
    int total = 0;
    for (const auto& node : data) {
        total += node.count;
    }
    return total;
}