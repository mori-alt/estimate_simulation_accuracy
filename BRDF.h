//
// Created by wd230 on 2023/05/09.
//

#ifndef ESTIMATE_SIMULATION_ACCURACY_BRDF_H
#define ESTIMATE_SIMULATION_ACCURACY_BRDF_H


#include <Eigen/Dense>
#include <cmath>
#include "CsvData.h"
#include "random/random.h"
#include "spectra/spectra_data.h"

class BRDF{
private:
    // light source
    static constexpr int DL = 25;
    static constexpr int NSPECT = 16;
    static constexpr int WAVELENGTHS[NSPECT] = { 375, 400, 425, 450, 475, 500, 525, 550, 575, 600, 625, 650, 675, 700, 725, 750 };
    static constexpr double light_intensity = 0.25;
    const double wavelength_;
    Eigen::Vector3d dl_;

    // surface structure
    const double amplitude_;  // pdf right  output (depth
    const double pitch_;  // surface structure ( scratch frequency
    Eigen::Vector3d dv_; // camera direction

    // rotation angle ( move light and camera in program
    const std::vector<double> rot_angle_;
    const int loop_;

    // calc value from initial value
    Eigen::MatrixXd rotation_matrix_y(const double phi_rad) const {
        // rotate with Y axis
        Eigen::MatrixXd rotate(3, 3);
        rotate << cos(phi_rad), 0, -sin(phi_rad), 0, 1, 0, sin(phi_rad), 0, cos(phi_rad);
        return rotate;
    }

    double radian2degree(const double radian)const {
        return radian * 180 / M_PI;
    }

    double degree2radian(const double degree)const {
        return degree * M_PI / 180;
    }

    void rotate_dl(const double rot_angle) {
        dl_ = rotation_matrix_y(degree2radian(rot_angle)) * dl_;
    }

    void rotate_dv(const double rot_angle) {
        dv_ = rotation_matrix_y(degree2radian(rot_angle)) * dv_;
    }

public:
    BRDF(const int loop, const double wavelength, const  Eigen::Vector3d& dl, const  double amplitude, const  double pitch, const Eigen::Vector3d& dv, const std::vector<double>& rot_angle)
    : loop_(loop), wavelength_(wavelength), dl_(dl.normalized()), amplitude_(amplitude), pitch_(pitch), dv_(dv.normalized()), rot_angle_(rot_angle){}

    static double eval_sinusoidal_brdf( const double _in_wave_length, const Eigen::Vector2d& in_random_st, const Eigen::Vector3d& in_dl, const Eigen::Vector3d& in_dv, const double amplitude, const double pitch )
    {
        using namespace std::complex_literals;

        const auto in_wave_length = _in_wave_length * 1.0e-9;
        const auto k = 2.0 * M_PI / in_wave_length;
        const auto A = amplitude * 1.0e-9;
        const auto L = pitch * 1.0e-9;
        const auto c = 50 * 1.0e-6;

        const Eigen::Vector3d dh_bar = ( in_dl + in_dv ) * 0.5;

        const auto factor = ( dh_bar.z() == 0.0 ) ? c : ( std::exp( k * c * dh_bar.z() * 1.0i ) - std::exp( -k * c * dh_bar.z() * 1.0i ) ) / ( 2.0i * k * dh_bar.z() );

        //the following way is probably buggy, as E[x^2] != E[x]^2
        //const auto _x = ( randomMT() - 0.5 ) * c;
        //const auto _integral_ = std::exp( -2.0i * k * ( _x * dh_bar.x() + A * std::sin( 2.0*std::numbers::pi*_x/L ) * dh_bar.y() ) ) * ( -2.0*std::numbers::pi*A*std::cos( 2.0*std::numbers::pi*_x/L )*dh_bar.x()/L + dh_bar.y() );
        //const auto iota = factor * _integral_ * c;
        //return k * k * ( std::conj(iota) * iota ).real() / ( 4.0 * std::numbers::pi * std::numbers::pi * c * c * in_dl.y() * in_dv.y() );

        //this is possibly correct
        const auto _x1 = ( in_random_st.x() - 0.5 ) * c;
        const auto _x2 = ( in_random_st.y() - 0.5 ) * c;
        const auto _integral_x1_ = std::exp( -2.0i * k * ( _x1 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x1/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x1/L )*dh_bar.x()/L + dh_bar.y() );
        const auto _integral_x2_ = std::exp( -2.0i * k * ( _x2 * dh_bar.x() + A * std::sin( 2.0*M_PI*_x2/L ) * dh_bar.y() ) ) * ( -2.0*M_PI*A*std::cos( 2.0*M_PI*_x2/L )*dh_bar.x()/L + dh_bar.y() );
        const auto iota_x1 = factor * _integral_x1_ * c;
        const auto iota_x2 = factor * _integral_x2_ * c;

        return k * k * ( iota_x1 * std::conj(iota_x2) ).real() / ( 4.0 * M_PI * M_PI * c * c * in_dl.y() * in_dv.y() );
    }

    static void set_spectra2XYZ_conversion(std::vector<Eigen::Vector3d>& spectra2XYZ_conversion) {
        for(auto i = 0; i < NSPECT; ++i){
//        wavelengths.push_back( WAVELENGTHS[i]);
            Eigen::Vector3d XYZ_data;
            getXYZForSpectraWindow(WAVELENGTHS[i], DL, XYZ_data);
            spectra2XYZ_conversion.push_back( XYZ_data);
        }
    }

    // calc expected value
    double estimate_brdf_exp_value(const int loop_freq) const {
        auto total_brdf_value = 0.0;
#pragma omp parallel for
        for(int i = 0; i < loop_freq; i++){
            Eigen::Vector2d brdf_st;
            brdf_st << randomMT(), randomMT();
            const auto _brdf_value = eval_sinusoidal_brdf(wavelength_, brdf_st, dl_, dv_, amplitude_, pitch_);
            total_brdf_value += _brdf_value;
        }
        auto brdf_exp_value = total_brdf_value / loop_freq;

        return brdf_exp_value;
    }

    double calc_accumulate_brdf_value(const int loop_freq, Eigen::Vector3d dl, Eigen::Vector3d dv) const {
        auto accumulate_brdf_value = 0.0;
#pragma omp parallel for
        for(int i = 0; i < loop_freq; ++i) {
            Eigen::Vector2d brdf_st;
            brdf_st << randomMT(), randomMT();
            const auto _brdf_value = eval_sinusoidal_brdf(wavelength_, brdf_st, dl, dv, amplitude_, pitch_);
            // todo add calc normal dot sequence
            accumulate_brdf_value += _brdf_value;
        }

        return accumulate_brdf_value;
    }

    void calc_accumulate_brdf_spectra(std::vector<std::array<double, 16>>, const int loop, const Eigen::Vector3d& dl, const Eigen::Vector3d& dv) {

    }

    std::vector<double> calc_all_frame_brdf() {
        std::vector<double> brdfs;
        // calculate brdf with rotating dl and dv
        for(double rot_angle : rot_angle_){
            rotate_dl(rot_angle);
            rotate_dv(rot_angle);
            brdfs.push_back(estimate_brdf_exp_value(pow(2, 15)));  // todo decide loop num
        }

        return brdfs;
    }

    void calc_accumulate_all_angle(std::vector<double>& spectra_accumulates, const int loop_freq) {
        for(double rotangle : rot_angle_) {
            // rotate scene each angle
            const Eigen::Vector3d dl = rotation_matrix_y(degree2radian(rotangle)) * dl_;
            const Eigen::Vector3d dv = rotation_matrix_y(degree2radian(rotangle)) * dv_;

            // save spectra
            spectra_accumulates.push_back(calc_accumulate_brdf_value(loop_freq, dl, dv));
        }
    }

    void _calc_accumulate_all_angle(std::vector<std::array<double, 16>>& spectra_accumulates, const int loop_freq) {
        for(double rotangle : rot_angle_) {
            // rotate scene each angle
            const Eigen::Vector3d dl = rotation_matrix_y(degree2radian(rotangle)) * dl_;
            const Eigen::Vector3d dv = rotation_matrix_y(degree2radian(rotangle)) * dv_;

            // save spectra
            // spectra_accumulates.push_back(calc_accumulate_brdf_value(loop_freq, dl, dv));

        }
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
