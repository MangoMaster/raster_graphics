// encoding: utf-8
#include <opencv2/opencv.hpp>
#include "main.h"

// 利用圆的八对称性并平移，一次显示圆上8个点
// (x, y)为以原点为圆心、半径为radius的圆弧上一点的坐标
void circle8Translation(cv::Mat &image, int x, int y, cv::Point center, const cv::Scalar &color)
{
    drawPixel(image, center.x + x, center.y + y, color);
    drawPixel(image, center.x + y, center.y + x, color);
    drawPixel(image, center.x - x, center.y + y, color);
    drawPixel(image, center.x + y, center.y - x, color);
    drawPixel(image, center.x + x, center.y - y, color);
    drawPixel(image, center.x - y, center.y + x, color);
    drawPixel(image, center.x - x, center.y - y, color);
    drawPixel(image, center.x - y, center.y - x, color);

    // drawPixel(image, x, y, color);
    // drawPixel(image, y - center.y + center.x, x - center.x + center.y, color);
    // drawPixel(image, 2 * center.x - x, y, color);
    // drawPixel(image, y - center.y + center.x, center.x - x + center.y, color);
    // drawPixel(image, x, 2 * center.y - y, color);
    // drawPixel(image, center.y - y + center.x, x - center.x + center.y, color);
    // drawPixel(image, 2 * center.x - x, 2 * center.y - y, color);
    // drawPixel(image, center.y - y + center.x, center.x - x + center.y, color);
}

// 中点画圆算法
void circleMidPoint(cv::Mat &image, cv::Point center, int radius, const cv::Scalar &color)
{
    assert(image.type() == CV_8UC3);
    assert(radius >= 0);

    // (x, y)在以原点为圆心、半径为radius的圆上
    int x = 0;
    int y = radius;
    // e = 4 * d, d = (x+1)^2 + (y-0.5)^2 - radius^2
    // 改用整数以加速
    int e = 5 - 4 * radius;
    while (x <= y)
    {
        // Draw pixel
        circle8Translation(image, x, y, center, color);
        // Update x, y and d
        if (e < 0)
        {
            e += 8 * x + 12;
        }
        else
        {
            e += 8 * (x - y) + 20;
            --y;
        }
        ++x;
    }
}
