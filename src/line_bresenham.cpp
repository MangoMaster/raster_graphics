// encoding: utf-8
#include <opencv2/opencv.hpp>
#include "main.h"

// x与y的增长方向相同
void lineBresenhamPlus(cv::Mat &image, cv::Point point_start, cv::Point point_end, const cv::Scalar &color)
{
    // dx为两点横坐标之差>=0, dy为两点纵坐标之差>=0
    int dx = point_end.x - point_start.x;
    int dy = point_end.y - point_start.y;
    assert(dx >= 0 && dy >= 0);
    // (x, y)为起点坐标
    int x = point_start.x;
    int y = point_start.y;
    if (dx >= dy)
    {
        // e = 2*dx*(d-0.5), d为误差项, d∈[-0.5, 0.5)
        // 改用整数以加速
        int e = -dx;
        for (int i = 0; i <= dx; ++i)
        {
            // Draw pixel
            drawPixel(image, x, y, color);
            // Update x, y and e
            ++x;
            e += 2 * dy; // d += k
            if (e >= 0)
            {
                ++y;
                e -= 2 * dx; // d -= 1
            }
        }
    }
    else // dx < dy
    {
        // e = 2*dy*(d-0.5), d为误差项, d∈[-0.5, 0.5)
        // 改用整数以加速
        int e = -dy;
        for (int j = 0; j <= dy; ++j)
        {
            // Draw pixel
            drawPixel(image, x, y, color);
            // Update x, y and e
            ++y;
            e += 2 * dx; // d += 1/k
            if (e >= 0)
            {
                ++x;
                e -= 2 * dy; // d -= 1
            }
        }
    }
}

// x与y的增长方向相反
void lineBresenhamMinus(cv::Mat &image, cv::Point point_start, cv::Point point_end, const cv::Scalar &color)
{
    // dx为两点横坐标之差>=0, dy为两点纵坐标之差<=0
    int dx = point_end.x - point_start.x;
    int dy = point_end.y - point_start.y;
    assert(dx >= 0 && dy <= 0);
    if (dx + dy >= 0) // dx >= -dy
    {
        // (x, y)为起点坐标
        int x = point_start.x;
        int y = point_start.y;
        // e = 2*dx*(d+0.5), d为误差项, d∈(-0.5, 0.5]
        // 改用整数以加速
        int e = dx;
        for (int i = 0; i <= dx; ++i)
        {
            // Draw pixel
            drawPixel(image, x, y, color);
            // Update x, y and e
            ++x;
            e += 2 * dy; // d += k
            if (e <= 0)
            {
                --y;
                e += 2 * dx; // d += 1
            }
        }
    }
    else // dx < -dy
    {
        dx = -dx;
        dy = -dy;
        // (x, y)为原终点坐标，现起点坐标
        int x = point_end.x;
        int y = point_end.y;
        // e = 2*dy*(d+0.5), d为误差项, d∈(-0.5, 0.5]
        // 改用整数以加速
        int e = dy;
        for (int j = 0; j <= dy; ++j)
        {
            // Draw pixel
            drawPixel(image, x, y, color);
            // Update x, y and e
            ++y;
            e += 2 * dx; // d += 1/k
            if (e <= 0)
            {
                --x;
                e += 2 * dy; // d += 1
            }
        }
    }
}

// Bresenham画线算法
void lineBresenham(cv::Mat &image, cv::Point point1, cv::Point point2, const cv::Scalar &color)
{
    assert(image.type() == CV_8UC3);

    if (point1.x <= point2.x)
    {
        if (point1.y <= point2.y)
            lineBresenhamPlus(image, point1, point2, color);
        else
            lineBresenhamMinus(image, point1, point2, color);
    }
    else // point1.x > point2.x
    {
        if (point1.y <= point2.y)
            lineBresenhamMinus(image, point2, point1, color);
        else
            lineBresenhamPlus(image, point2, point1, color);
    }
}