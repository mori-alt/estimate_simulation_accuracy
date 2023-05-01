//
// Created by wd230 on 2023/05/01.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
#define ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H

#include <string>
#include <iostream>
#include <fstream>

class CsvData {
private:
    std::string file_path_;

public:
    CsvData(std::string csv_path) {
//        ファイルの読み込み
        file_path_ = csv_path;
        std::cout << file_path_ << std::endl;
        std::ifstream file(file_path_, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error("file cannot be opened");
        }

    }
};

#endif //ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
