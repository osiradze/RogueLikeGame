//
// Created by oto_9 on 18.03.2026.
//

class SSBOReader  {
public:
    static unsigned int ssbo;

    SSBOReader();
    void read();
private:
    static const unsigned int SIZE = 3;
    float cleanData[SIZE] = {0.0f};

    float* readData  = nullptr;

    void writeCleanData();

};