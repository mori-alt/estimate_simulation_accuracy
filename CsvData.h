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
        std::ifstream file(file_path_, std::ios::in);
        if (!file.is_open()) {  // ちゃんと拾うかは置いといて失敗したらエラー投げさせる
            throw std::runtime_error("file cannot be opened");
        }

        std::string str = "";
        std::vector<std::string> lines;
        while(getline(file, str)){
            lines.push_back(str);
            std::cout << str << std::endl;
        }

        std::cout << lines.size() << std::endl;
        std::cout << lines[0] << std::endl;

        file.close();
    }

    std::string getFilePath() const {
        return file_path_;
    }
};

#endif //ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
