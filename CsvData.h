//
// Created by wd230 on 2023/05/01.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
#define ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H

#include <string>
#include <iostream>

class CsvData{
private:
    std::string file_path;

public:
    CsvData(std::string csv_path);
};

// 読み込んでデータを分割
CsvData::CsvData(std::string csv_path) {
    file_path = csv_path;
    std::cout << file_path << std::endl;
}

#endif //ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
