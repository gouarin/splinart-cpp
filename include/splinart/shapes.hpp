#pragma once

#include <array>
#include <utility>
#include <xtensor/xfixed.hpp>
#include <xtensor/xtensor.hpp>

namespace splinart
{
    struct Circle
    {
        Circle(const xt::xtensor_fixed<double, xt::xshape<2>>& center, double radius, std::size_t npoints = 50);

        xt::xtensor<double, 1> theta;
        xt::xtensor<double, 2> path;
        xt::xtensor_fixed<double, xt::xshape<4>> color{0.61960784313725492, 0.41568627450980394, 0, 1.0};
    };
}

// auto line(double beg, double end, double ypos=0.5, std::size_t npoints=50):

//     x = np.linspace(begin, end, npoints)
//     y = ypos * np.ones(npoints)
//     return np.c_[x, y]
