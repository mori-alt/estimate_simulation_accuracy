//
// Created by wd230 on 2023/05/09.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_BRDF_H
#define ESTIMATE_SIMULATION_ACCURACY_BRDF_H


#include <Eigen/Dense>
#include <cmath>
#include "CsvData.h"
#include "random/random.h"

class BRDF{
private:
    // 光源情報
    const double wavelength_;
    const Eigen::Vector3d dl_;

    // 表面構造
    const double amplitude_;  // pdf right  output (depth
    const double pitch_;  // surface structure ( scratch frequency
    const Eigen::Vector3d dv_; // camera direction

    // rotation angle ( move light and camera in program
    const std::vector<double> rot_angle_;

    // calc value from initial value
    Eigen::MatrixXd rotation_matrix_y(const double phi_rad) const {
        // y軸が上向きのはずだからy軸中心の回転を定義しているけど問題があったら適宜修正を加えること
        Eigen::MatrixXd rotate(3, 3);
        rotate << cos(phi_rad), 0, -sin(phi_rad), 0, 1, 0, sin(phi_rad), 0, cos(phi_rad);
        return rotate;
    }

    Eigen::Vector3d rotate_pos(const Eigen::MatrixXd& rotate_matrix, const Eigen::Vector3d& current_position) const {
        return rotate_matrix * current_position;
    }

public:
    BRDF(const double wavelength, const  Eigen::Vector3d& dl, const  double amplitude, const  double pitch, const Eigen::Vector3d& dv, const std::vector<double>& rot_angle)
    : wavelength_(wavelength), dl_(dl.normalized()), amplitude_(amplitude), pitch_(pitch), dv_(dv.normalized()), rot_angle_(rot_angle){}

    double eval_sinusoidal_brdf( const Eigen::Vector2d& in_random_st ) const
    {
        using namespace std::complex_literals;

        const float g_c = 50.0; //[um]  表面構造の一辺の長さ
        const auto k = 2.0 * M_PI / (wavelength_ * 1.0e-9);
        const auto A = amplitude_ * 1.0e-9;
        const auto L = pitch_ * 1.0e-9;
        const auto c = g_c * 1.0e-6;

        const Eigen::Vector3d dh_bar = 0.5 * (dl_ + dv_);

        const auto factor = ( dh_bar.z() == 0.0 ) ? c : ( std::exp( k * c * dh_bar.z() * 1.0i ) - std::exp( -k * c * dh_bar.z() * 1.0i ) ) / ( 2.0i * k * dh_bar.z() );

        // 計算する点の指定　辺の長さで決めてる
        const auto _x1 = ( in_random_st.x() - 0.5 ) * c;
        const auto _x2 = ( in_random_st.y() - 0.5 ) * c;
        const auto _integral_x1_ = std::exp( -2.0i * k * ( _x1 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x1/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x1/L )*dh_bar.x()/L + dh_bar.y() );
        const auto _integral_x2_ = std::exp( -2.0i * k * ( _x2 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x2/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x2/L )*dh_bar.x()/L + dh_bar.y() );
        const auto iota_x1 = factor * _integral_x1_ * c;
        const auto iota_x2 = factor * _integral_x2_ * c;

        return k * k * ( iota_x1 * std::conj(iota_x2) ).real() / ( 4.0 * M_PI * M_PI * c * c * dl_.y() * dv_.y() );
    }

    // calc expected value
    double estimate_brdf_exp_value(const int loop_freq) const {
        auto total_brdf_value = 0.0;
#pragma omp parallel for
        for(int i = 0; i < loop_freq; i++){
            Eigen::Vector2d brdf_st;
            brdf_st << randomMT(), randomMT();
            const auto _brdf_value = eval_sinusoidal_brdf( brdf_st );
            total_brdf_value += _brdf_value;
        }
        auto brdf_exp_value = total_brdf_value / loop_freq;

        return brdf_exp_value;
    }

    std::vector<double> calc_all_frame_brdf() const {
        std::vector<double> brdfs;

        for(int i = 0; i < rot_angle_.size(); i++){
            brdfs.push_back(estimate_brdf_exp_value(pow(2, 15)));

            // 物体表面の回転に対応して周囲の要素を回転させる

        }

        return brdfs;

    }

    // for debug
    void show_member() {
        std::cout << "member" << std::endl;
        std::cout << "wavelength : " << wavelength_ << std::endl;
        std::cout << "dl\n" << dl_ << std::endl;
        std::cout << "amplitude : " << amplitude_ << std::endl;
        std::cout << "pitch : " << pitch_ << std::endl;
        std::cout << "dv : \n" << dv_ << std::endl;
        std::cout << "rot_angle size: " << rot_angle_.size() << std::endl;
        std::cout << "rot_angle[1]" << rot_angle_[1] << std::endl;

    }

    double getWavelength() const {
        return wavelength_;
    }


    const Eigen::Vector3d &getDl() const {
        return dl_;
    }


    double getAmplitude() const {
        return amplitude_;
    }


    double getPitch() const {
        return pitch_;
    }


    const Eigen::Vector3d &getDv() const {
        return dv_;
    }

    const std::vector<double> &getRotAngle() const {
        return rot_angle_;
    }
};

#endif //ESTIMATE_SIMULATION_ACCURACY_BRDF_H
