
#include <iostream>
#include <string>
#include <vector>

class HashMap {
private:
    static const size_t InitialCapacity = 20000;

    struct HashNode {
        std::string filename;
        int count;

        HashNode() : count(0) {}
    };

    std::vector<HashNode> data;

    size_t hash(const std::string& key) const;
    size_t linearProbe(size_t index) const;

public:
    HashMap();
    void increment(const std::string& key);
    void sort_and_print() const;
    int count(const std::string& key) const;
    int total_count() const;
};