#include <iostream>
#include "ModelSettings.h"
#include "Target.h"

__CUDA__ double getDouble(){
    return 0.0;
}

int main() {
    Target t;
    t.name = std::string{"LOL"};
    t.num = LONG_MAX;
    t.v = std::vector<std::string>();
    t.v.push_back("this");
    t.v.push_back("is");
    t.v.push_back("sparta");

    std::stringstream ss; // any stream can be used

    {
        cereal::JSONOutputArchive oarchive(ss); // Create an output archive
        oarchive(t); // Write the data to the archive
    }

    std::cout << "Hello, World! "<< getDouble() << ": "<<ss.str()<< std::endl;
    return 0;
}