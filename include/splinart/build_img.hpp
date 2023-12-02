#pragma once

#include <xtensor/xfixed.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor/xtensor.hpp>

#include "shapes.hpp"
#include "spline.hpp"

namespace splinart
{
    inline void draw_pixel(xt::xtensor<double, 3>& img, const xt::xtensor<double, 2>& spline, xt::xtensor_fixed<double, xt::xshape<4>> color)
    {
        std::size_t width  = img.shape(0);
        std::size_t height = img.shape(1);

        auto xs      = xt::view(spline, xt::all(), 0);
        auto ys      = xt::view(spline, xt::all(), 1);
        auto newxs   = xt::floor(xs * width);
        auto xs_mask = newxs >= 0 && newxs < width;
        auto newys   = xt::floor(ys * height);
        auto ys_mask = newys >= 0 && newys < height;
        auto mask    = xs_mask && ys_mask;

        for (std::size_t i = 0; i < xs.size(); ++i)
        {
            if (mask[i])
            {
                auto x              = newxs[i];
                auto y              = newys[i];
                double alpha        = 1 - color(3);
                xt::view(img, x, y) = color + xt::view(img, x, y) * alpha;
            }
        }
    }

    inline void update_path(xt::xtensor<double, 2>& path, double scale_value = 0.00001, bool periodic = false)
    {
        auto n      = path.shape(0);
        auto scale  = xt::arange(n) * scale_value;
        auto radius = 1.0 - 2.0 * xt::random::rand<double>({n});
        auto noise  = radius * scale;
        auto pi     = xt::numeric_constants<double>::PI;

        auto phi = xt::random::rand<double>({n}) * 2 * pi;

        std::array<std::size_t, 2> shape{n, 2};
        xt::xtensor<double, 2> rnd  = xt::empty<double>(shape);
        xt::view(rnd, xt::all(), 0) = xt::cos(phi);
        xt::view(rnd, xt::all(), 1) = xt::sin(phi);
        path += rnd * xt::view(noise, xt::all(), xt::newaxis());
        if (periodic)
        {
            xt::view(path, n - 1) = xt::view(path, 0);
        }
    }

    inline auto build_img(const std::array<std::size_t, 2>& img_size,
                          std::vector<Circle>& circles,
                          std::size_t rep    = 300,
                          bool periodic      = true,
                          double scale_color = 0.005,
                          double scale_value = 0.00001)
    {
        std::array<std::size_t, 3> shape{img_size[0], img_size[1], 4};
        xt::xtensor<double, 3> img = xt::ones<double>(shape);

        auto xs_func = []()
        {
            std::size_t nsamples = 500;
            double pi            = xt::numeric_constants<double>::PI;
            return xt::eval(xt::fmod(xt::random::rand<double>({1})[0] + xt::linspace<double>(0, 2 * pi, nsamples), 2 * pi));
        };

        xt::xtensor<double, 1> xspline = xs_func();

        for (auto& circle : circles)
        {
            std::array<std::size_t, 2> spline_shape{xspline.size(), 2};
            xt::xtensor<double, 2> yspline = xt::zeros<double>(spline_shape);
            for (std::size_t r = 0; r < rep; ++r)
            {
                auto yder2 = spline(circle.theta, circle.path);
                xspline    = xs_func();
                splint(circle.theta, circle.path, yder2, xspline, yspline);
                draw_pixel(img, yspline, circle.color * scale_color);
                update_path(circle.path, scale_value, periodic);
            }
        }
        return img;
    }
}
