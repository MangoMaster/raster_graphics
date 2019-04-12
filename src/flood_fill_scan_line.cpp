// encoding: utf-8
#include <opencv2/opencv.hpp>
#include <stack>
#include "main.h"

void floodFillScanLine(cv::Mat &image, cv::Point seed_point, const cv::Scalar &new_color)
{
    cv::Scalar old_color = getPixelColor(image, seed_point.x, seed_point.y);
    std::stack<cv::Point> seed_stack;
    seed_stack.push(seed_point);
    while (!seed_stack.empty())
    {
        cv::Point point = seed_stack.top();
        seed_stack.pop();
        int y = point.y;
        int x;

        // 向右填充
        for (x = point.x; getPixelColor(image, x, y) == old_color; ++x)
            drawPixel(image, x, y, new_color);
        int xr = x - 1;
        // 向左填充
        for (x = point.x - 1; getPixelColor(image, x, y) == old_color; --x)
            drawPixel(image, x, y, new_color);
        int xl = x + 1;
        // 处理上面一条扫描线
        for (x = xl, y += 1; x <= xr;)
        {
            while (getPixelColor(image, x, y) != old_color && x <= xr)
                ++x;
            if (getPixelColor(image, x, y) == old_color && x <= xr) // 压栈新种子
            {
                cv::Point new_seed_point(x, y);
                seed_stack.push(new_seed_point);
            }
            while (getPixelColor(image, x, y) == old_color && x <= xr)
                ++x;
        }
        // 处理下面一条扫描线
        for (x = xl, y -= 2; x <= xr;)
        {
            while (getPixelColor(image, x, y) != old_color && x <= xr)
                ++x;
            if (getPixelColor(image, x, y) == old_color && x <= xr) // 压栈新种子
            {
                cv::Point new_seed_point(x, y);
                seed_stack.push(new_seed_point);
            }
            while (getPixelColor(image, x, y) == old_color && x <= xr)
                ++x;
        }
    }
}