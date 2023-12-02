#include <splinart/shapes.hpp>

#include <xtensor/xview.hpp>

namespace splinart
{

    Circle::Circle(const xt::xtensor_fixed<double, xt::xshape<2>>& center, double radius, std::size_t npoints)
    {
        theta                        = xt::linspace<double>(0., 2. * xt::numeric_constants<double>::PI, npoints);
        path                         = xt::empty<double>(std::array<std::size_t, 2>{npoints, 2});
        xt::view(path, xt::all(), 0) = center[0] + radius * xt::cos(theta);
        xt::view(path, xt::all(), 1) = center[1] + radius * xt::sin(theta);
        color                        = {0.61960784313725492, 0.41568627450980394, 0, 1.0};
    }
}
