// encoding: utf-8
#include <opencv2/opencv.hpp>
#include "main.h"

// Bresenham画线算法绘制多边形
// is_closed == true -> draws a line from the last vertex to the first vertex of each contour.
void polylinesBresenham(cv::Mat &image, const cv::Point **vertices, const int *n_vertices, int n_contours, bool is_closed, const cv::Scalar &color)
{
    for (int i = 0; i < n_contours; ++i)
    {
        if (is_closed)
            lineBresenham(image, vertices[i][0], vertices[i][n_vertices[i] - 1], color);
        for (int j = 1; j < n_vertices[i]; ++j)
            lineBresenham(image, vertices[i][j - 1], vertices[i][j], color);
    }
}