#pragma once

#include <opencv2/opencv.hpp>
#include <xtensor/xtensor.hpp>

namespace splinart
{
    inline void imshow(const xt::xtensor<double, 3>& img)
    {
        auto width  = img.shape(0);
        auto height = img.shape(1);
        cv::Mat M(width, height, CV_64FC4, cv::Scalar::all(0));

        for (std::size_t i = 0; i < width; ++i)
        {
            for (std::size_t j = 0; j < height; ++j)
            {
                cv::Vec4d& elem = M.at<cv::Vec4d>(i, j);
                for (int k = 0; k < 4; ++k)
                {
                    elem[k] = img(i, j, k);
                }
            }
        }
        cv::imshow("splinart", M);
        cv::waitKey(0);
    }
}