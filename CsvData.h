//
// Created by wd230 on 2023/05/01.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
#define ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H

#include <string>
#include <iostream>
#include <fstream>
#include <array>

class CsvData {
private:
    std::string file_path_;
    std::array<double, 3> eye_pos_;
    std::array<double, 3> look_at_;
    double dist_to_look_at_;
    double camera_theta_;
    double camera_phi_;
    double camera_psi_;
    double omega_;
    std::vector<std::string> header_;
    std::vector<std::vector<double>> data_;

public:
    CsvData(){

    }
    CsvData(std::string csv_path) {
        file_path_ = csv_path;
        std::ifstream file(file_path_, std::ios::in);
        if (!file.is_open()) {  // ちゃんと拾うかは置いといて失敗したらエラー投げさせる
            throw std::runtime_error("file cannot be opened");
        }

        // 全ての行の内容を読み込み
        std::string str = "";
        std::vector<std::string> lines;
        while(getline(file, str)){
            lines.push_back(str);
        }

        // メンバ変数を格納
        for(int i = 0; i < eye_pos_.size(); i++){
            eye_pos_[i] = std::stod(split(lines[0], ',')[i + 1]);
        }

        for(int i = 0; i < look_at_.size(); i++){
            look_at_[i] = std::stod(split(lines[1], ',')[i + 1]);
        }

        dist_to_look_at_ = std::stod(split(lines[2], ',')[1]);
        camera_theta_ = std::stod(split(lines[3], ',')[1]);
        camera_phi_ = std::stod(split(lines[4], ',')[1]);
        camera_psi_ = std::stod(split(lines[5], ',')[1]);
        omega_ = std::stod(split(lines[6], ',')[1]);
        header_ = split(lines[7], ',');
        header_.erase(header_.end() - 1); // 末尾余計にカウントしてしまうので削除しておく

        // csv各データの格納
        // string 型で文字列格納 一文から分離する
        std::vector<std::vector<std::string>> string_data;
        for(int i = 8; i < lines.size(); i++){
            string_data.push_back(split(lines[i], ','));
        }


        // 分離した文字列を数値型に書き換える
        for(int i = 0; i < string_data.size(); i++){
            std::vector<double> double_value;
            for(int j = 0; j < 2+5*75; j++){
                double_value.push_back(std::stod(string_data[i][j]));
            }
            data_.push_back(double_value);
        }

        file.close();
    }

    // csv読み込むとき用のカンマ区切り関数
    std::vector<std::string> split(const std::string& input, char delimiter)
    {
        std::istringstream stream(input);

        std::string field;
        std::vector<std::string> result;
        while (std::getline(stream, field, delimiter)) {
            result.push_back(field);
        }
        return result;
    }

    std::string getFilePath() const {
        return file_path_;
    }

    void setFilePath(const std::string &filePath) {
        file_path_ = filePath;
    }

    const std::array<double, 3> &getEyePos() const {
        return eye_pos_;
    }

    void setEyePos(const std::array<double, 3> &eyePos) {
        eye_pos_ = eyePos;
    }

    const std::array<double, 3> &getLookAt() const {
        return look_at_;
    }

    void setLookAt(const std::array<double, 3> &lookAt) {
        look_at_ = lookAt;
    }

    double getDistToLookAt() const {
        return dist_to_look_at_;
    }

    void setDistToLookAt(double distToLookAt) {
        dist_to_look_at_ = distToLookAt;
    }

    double getCameraTheta() const {
        return camera_theta_;
    }

    void setCameraTheta(double cameraTheta) {
        camera_theta_ = cameraTheta;
    }

    double getCameraPhi() const {
        return camera_phi_;
    }

    void setCameraPhi(double cameraPhi) {
        camera_phi_ = cameraPhi;
    }

    double getCameraPsi() const {
        return camera_psi_;
    }

    void setCameraPsi(double cameraPsi) {
        camera_psi_ = cameraPsi;
    }

    double getOmega() const {
        return omega_;
    }

    void setOmega(double omega) {
        omega_ = omega;
    }

    const std::vector<std::string> &getHeader() const {
        return header_;
    }

    void setHeader(std::vector<std::string> header) {
        header_ = header;
    }

    const std::vector<std::vector<double>> &getData() const {
        return data_;
    }

    void setData(std::vector<std::vector<double>> data) {
        data_ = data;
    }
};

#endif //ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
