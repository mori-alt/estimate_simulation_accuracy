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
    BRDF(const int loop, const  Eigen::Vector3d& dl, const  double amplitude, const  double pitch, const Eigen::Vector3d& dv, const std::vector<double>& rot_angle)
    : loop_(loop), dl_(dl.normalized()), amplitude_(amplitude), pitch_(pitch), dv_(dv.normalized()), rot_angle_(rot_angle)
    {
        show_member();
    }

    static double eval_sinusoidal_brdf( const double _in_wave_length, const Eigen::Vector2d& in_random_st, const Eigen::Vector3d& in_dl, const Eigen::Vector3d& in_dv, const double amplitude, const double pitch )
    {
        using namespace std::complex_literals;

        const auto in_wave_length = _in_wave_length * 1.0e-9;
        const auto k = 2.0 * M_PI / in_wave_length;
        const auto A = amplitude * 1.0e-9;
        const auto L = pitch * 1.0e-9;
        const auto c = 50 * 1.0e-6;
//        const auto c = 1.0;

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
        spectra2XYZ_conversion.clear();
        for(auto i = 0; i < NSPECT; ++i){
            Eigen::Vector3d XYZ_data;
            getXYZForSpectraWindow(WAVELENGTHS[i], DL, XYZ_data);
            spectra2XYZ_conversion.push_back( XYZ_data);
        }
    }

    static void set_out_RGB(std::vector<Eigen::Vector3d>& out_RGB, const int loop_num, const std::vector<Eigen::Vector3d>& spectra2XYZ_conversion, const std::vector<std::array<double, 16>>& accumulation_spectra) {
        for(auto spectra : accumulation_spectra) {
            Eigen::Vector3d rgb = Eigen::Vector3d::Zero();
            convertSpectraData2RGB(rgb, NSPECT, spectra2XYZ_conversion, spectra, light_intensity / loop_num);
            out_RGB.push_back(rgb);
        }
    }

    void calc_accumulate_brdf_spectra(std::array<double, 16>& brdf_spectra, const Eigen::Vector3d& dl, const Eigen::Vector3d& dv) {
        for(int i = 0; i < loop_; ++i) {
            // make light spectra
            const auto k = std::clamp(int(randomMT() * NSPECT), 0, NSPECT - 1);
            const auto wavelength = WAVELENGTHS[k];
            Eigen::Vector2d brdf_st;
            brdf_st << randomMT(), randomMT();
            const auto f = eval_sinusoidal_brdf(wavelength, brdf_st, dl, dv, amplitude_, pitch_);
            brdf_spectra[k] += f;
        }
    }

    void calc_accumulate_all_angle(std::vector<std::array<double, 16>>& spectra_accumulates) {
        for(double rotangle : rot_angle_) {
            // rotate scene each angle
            const Eigen::Vector3d dl = rotation_matrix_y(degree2radian(rotangle)) * dl_;
            const Eigen::Vector3d dv = rotation_matrix_y(degree2radian(rotangle)) * dv_;

            // save spectra
            std::array<double, 16> brdf_spectra{0};
            calc_accumulate_brdf_spectra(brdf_spectra, dl, dv);
            spectra_accumulates.push_back(brdf_spectra);
        }
    }

    // for debug
    void show_member() {
        std::cout << '\n' << "### member ###" << std::endl;
        std::cout << "loop : " << loop_ << std::endl;
        std::cout << "dl : " << dl_.transpose() << std::endl;
        std::cout << "amplitude (surface): " << amplitude_ << std::endl;
        std::cout << "pitch (surface): " << pitch_ << std::endl;
        std::cout << "dv (surface): " << dv_.transpose() << std::endl;
        std::cout << "rot_angle size: " << rot_angle_.size() << std::endl;
        std::cout << "rot_angle[1]" << rot_angle_[1] << std::endl;
        std::cout << "##############"<< '\n' << std::endl;
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

    static const double getLightIntensity() {
        return light_intensity;
    }

    const int getLoop() const {
        return loop_;
    }
};

#endif //ESTIMATE_SIMULATION_ACCURACY_BRDF_H
