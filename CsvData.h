//
// Created by wd230 on 2023/05/01.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
#define ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <regex>
#include <Eigen/Dense>

// fixme want to use cmath M_PI, problem in visual studio compiler??
const double M_PI = 3.141592653589793;

class CsvData {
private:
    std::filesystem::path input_file_path_;
    std::filesystem::path output_file_path_;
    std::array<double, 3> eye_pos_;
    std::array<double, 3> look_at_;
    double dist_to_look_at_;
    double camera_theta_;
    double camera_phi_;
    double camera_psi_;
    double omega_;
    std::vector<std::string> header_;
    std::vector<std::vector<double>> data_;
    std::vector<double> time_;
    std::vector<double> rot_angle_;
    Eigen::Vector3d camera_pos_;
    std::vector<std::string> initial_row_;

    // split string each ,
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

    double radian2degree(const double radian)const {
        return radian * 180 / M_PI;
    }

    double degree2radian(const double degree)const {
        return degree * M_PI / 180;
    }

    Eigen::Vector3d polar_unit_vec(const double theta_degree, const double phi_degree) const {
        return Eigen::Vector3d(std::sin(degree2radian(theta_degree))*std::cos(degree2radian(phi_degree)), std::cos(
                degree2radian(theta_degree)), std::sin(degree2radian(theta_degree))*std::sin(degree2radian(phi_degree))).normalized();
    }

    // pick up number from string -> double
    // only use absolute(value) > 1
    std::vector<double> extractNumbers(const std::string& str) const {
        std::vector<double> numbers;
        std::regex e("(\\d+)"); // get num

        std::sregex_iterator begin = std::sregex_iterator(str.begin(), str.end(), e); // 数値型と一致するイテレータを出力？　処理の理解怪しいかも
        std::sregex_iterator end;
        for (std::sregex_iterator i = begin; i != end; ++i) {
            std::smatch match = *i; // save number type
            numbers.push_back(std::stod(match.str())); //to double
        }

        return numbers;
    }

public:
    CsvData() { }
    CsvData(std::filesystem::path csv_path, std::filesystem::path output_path) {
        // read csv
        input_file_path_ = csv_path;
        output_file_path_ = output_path;
        std::ifstream file(input_file_path_, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error("file cannot be opened");
        }

        // read all lines
        std::string str = "";
        std::vector<std::string> lines;
        while(getline(file, str)){
            lines.push_back(str);
        }

        // set initial row
        for(int i = 0; i < 8; ++i){
            initial_row_.push_back(lines[i]);
        }

        // split strings each ,
        std::vector<std::vector<std::string>> string_data;
        for(int i = 8; i < lines.size(); i++){
            string_data.push_back(split(lines[i], ','));
        }

        // string -> double
        for(int i = 0; i < string_data.size(); i++){
            std::vector<double> double_value;
            for(int j = 0; j < 2+5*75; j++){
                double_value.push_back(std::stod(string_data[i][j]));
            }
            data_.push_back(double_value);
        }

        std::cout << "csv_data column size : " << data_.size() << std::endl;
        std::cout << "csv_data row size    : " << data_[0].size() << std::endl;

        // save member
        for(int i = 0; i < eye_pos_.size(); i++) eye_pos_[i] = std::stod(split(lines[0], ',')[i + 1]);
        for(int i = 0; i < look_at_.size(); i++) look_at_[i] = std::stod(split(lines[1], ',')[i + 1]);
        dist_to_look_at_ = std::stod(split(lines[2], ',')[1]);
        camera_theta_ = std::stod(split(lines[3], ',')[1]);
        camera_phi_ = std::stod(split(lines[4], ',')[1]);
        camera_psi_ = std::stod(split(lines[5], ',')[1]);
        omega_ = std::stod(split(lines[6], ',')[1]);
        header_ = split(lines[7], ',');
        header_.erase(header_.end() - 1); // remove end extra count
        time_ = read_column(0);
        rot_angle_ = read_column(1);
        camera_pos_ = polar_unit_vec(camera_theta_, camera_phi_);
        file.close();
    }

    std::vector<double> read_column(int read_column_num) const {
        std::vector<double> row;
        for(int i = 0; i < data_.size(); i++){
            row.push_back(data_[i][read_column_num]);
        }

        if(read_column_num == 0) {
            std::cout << "read column [time], size : " << row.size() << std::endl;
        }
        else if(read_column_num == 1) {
            std::cout << "read column [rot], size  : " << row.size() << std::endl;
        }
        else {
            std::cout << "read column [RGB, angle], size : " << row.size() << std::endl;
        }

        return row;
    }

    std::vector<std::vector<double>> read_camera_solid_angles(int surface_num) const {
        std::vector<std::vector<double>> camera_solid_angle;
        camera_solid_angle.push_back(read_column(2 + surface_num * 5));
        camera_solid_angle.push_back(read_column(2 + surface_num * 5 + 1));

        return camera_solid_angle;
    }

    void output_csv() const {
        std::ofstream output_csv(output_file_path_);

        for(std::string init_row : initial_row_) {
            output_csv << init_row << std::endl;
        }

        for(std::vector<double> row_data : data_) {
            for(double value : row_data) {
                output_csv << value << ',';
            }
            output_csv << std::endl;
        }
    }

    void update_RGB(const std::vector<Eigen::Vector3d>& RGB, const int surface_num) {
        std::cout << "update csv RGB data" << std::endl;
        const int r_row = 2 + 5 * surface_num + 2;
        const int g_row = 2 + 5 * surface_num + 3;
        const int b_row = 2 + 5 * surface_num + 4;

        for(int i = 0; i < data_.size(); ++i) {
            data_[i][r_row] = RGB[i].x();
            data_[i][g_row] = RGB[i].y();
            data_[i][b_row] = RGB[i].z();
        }
        std::cout << "finished" << std::endl;
    }

    // only take amplitude
    // surface_num 0 ~ 74
    // todo want to take out the spacing of the lines
    std::vector<double> getSurfaceGeo(int surface_num) const {
        return extractNumbers(header_[2 + surface_num * 5]);
    }

    std::filesystem::path getFilePath() const {
        return input_file_path_;
    }

    void setFilePath(const std::string &filePath) {
        input_file_path_ = filePath;
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

    const std::vector<double> &getTime() const {
        return time_;
    }

    void setTime(const std::vector<double> &time) {
        time_ = time;
    }

    const std::vector<double> &getRotAngle() const {
        return rot_angle_;
    }

    void setRotAngle(const std::vector<double> &rotAngle) {
        rot_angle_ = rotAngle;
    }

    const Eigen::Vector3d &getCameraPos() const {
        return camera_pos_;
    }

    void setCameraPos(const Eigen::Vector3d &cameraPos) {
        camera_pos_ = cameraPos;
    }

    const std::vector<std::string> &getInitialRow() const {
        return initial_row_;
    }
};

#endif //ESTIMATE_SIMULATION_ACCURACY_CSVDATA_H
