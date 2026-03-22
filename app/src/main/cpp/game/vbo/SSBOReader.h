//
// Created by oto_9 on 18.03.2026.
//

#include <string>
#include <unordered_map>
#include <vector>


class SSBOReader  {
public:
    SSBOReader();
    void allocate(const std::string& key, int length);
    void init();
    void read();
    std::vector<float> getData(const std::string& key);
private:
    std::unordered_map<std::string, std::pair<unsigned int, unsigned int>> buffers;
    float* cleanData = nullptr;
    float* readData  = nullptr;
    unsigned int size = 0;

    unsigned int ssbo;
};