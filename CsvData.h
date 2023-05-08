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

public:
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

        //　ヘッダ行の標準出力
        std::cout << lines.size() << std::endl;
        for(int i = 0; i < 7; i++){
            std::cout << lines[i] << std::endl;
        }

        // eye posの格納
        for(int i = 0; i < eye_pos_.size(); i++){
            eye_pos_[i] = std::stod(split(lines[0], ',')[i + 1]);
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
};

#endif //ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
