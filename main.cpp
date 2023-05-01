#include <iostream>
#include "CsvData.h"

int main() {
    try {
        CsvData csv("./csv/result_3.csv");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
