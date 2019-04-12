#include "../src/main.h"

int main()
{
    // Parameters
    const int width = 200;
    const int height = 300;

    // Build a canvas. Each element in the canvas is 3 unsigned char in the order of BGR.
    cv::Mat img(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat img_example(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    // Draw lines using Bresenham algorithm and cv::line.
    lineBresenham(img, cv::Point(10, 10), cv::Point(90, 90), cv::Scalar(255, 0, 0));
    cv::line(img_example, cv::Point(10, 10), cv::Point(90, 90), cv::Scalar(255, 0, 0));
    lineBresenham(img, cv::Point(10, 10), cv::Point(90, 50), cv::Scalar(0, 255, 0));
    cv::line(img_example, cv::Point(10, 10), cv::Point(90, 50), cv::Scalar(0, 255, 0));
    lineBresenham(img, cv::Point(10, 10), cv::Point(50, 90), cv::Scalar(0, 0, 255));
    cv::line(img_example, cv::Point(10, 10), cv::Point(50, 90), cv::Scalar(0, 0, 255));

    lineBresenham(img, cv::Point(110, 90), cv::Point(190, 10), cv::Scalar(255, 0, 0));
    cv::line(img_example, cv::Point(110, 90), cv::Point(190, 10), cv::Scalar(255, 0, 0));
    lineBresenham(img, cv::Point(110, 90), cv::Point(190, 50), cv::Scalar(0, 255, 0));
    cv::line(img_example, cv::Point(110, 90), cv::Point(190, 50), cv::Scalar(0, 255, 0));
    lineBresenham(img, cv::Point(110, 90), cv::Point(150, 10), cv::Scalar(0, 0, 255));
    cv::line(img_example, cv::Point(110, 90), cv::Point(150, 10), cv::Scalar(0, 0, 255));

    lineBresenham(img, cv::Point(90, 110), cv::Point(10, 190), cv::Scalar(255, 0, 0));
    cv::line(img_example, cv::Point(90, 110), cv::Point(10, 190), cv::Scalar(255, 0, 0));
    lineBresenham(img, cv::Point(90, 110), cv::Point(10, 150), cv::Scalar(0, 255, 0));
    cv::line(img_example, cv::Point(90, 110), cv::Point(10, 150), cv::Scalar(0, 255, 0));
    lineBresenham(img, cv::Point(90, 110), cv::Point(50, 190), cv::Scalar(0, 0, 255));
    cv::line(img_example, cv::Point(90, 110), cv::Point(50, 190), cv::Scalar(0, 0, 255));

    lineBresenham(img, cv::Point(190, 190), cv::Point(110, 110), cv::Scalar(255, 0, 0));
    cv::line(img_example, cv::Point(190, 190), cv::Point(110, 110), cv::Scalar(255, 0, 0));
    lineBresenham(img, cv::Point(190, 190), cv::Point(110, 150), cv::Scalar(0, 255, 0));
    cv::line(img_example, cv::Point(190, 190), cv::Point(110, 150), cv::Scalar(0, 255, 0));
    lineBresenham(img, cv::Point(190, 190), cv::Point(150, 110), cv::Scalar(0, 0, 255));
    cv::line(img_example, cv::Point(190, 190), cv::Point(150, 110), cv::Scalar(0, 0, 255));

    lineBresenham(img, cv::Point(10, 230), cv::Point(90, 230), cv::Scalar(0, 255, 0));
    cv::line(img_example, cv::Point(10, 230), cv::Point(90, 230), cv::Scalar(0, 255, 0));
    lineBresenham(img, cv::Point(90, 270), cv::Point(10, 270), cv::Scalar(0, 0, 255));
    cv::line(img_example, cv::Point(90, 270), cv::Point(10, 270), cv::Scalar(0, 0, 255));

    lineBresenham(img, cv::Point(130, 210), cv::Point(130, 290), cv::Scalar(0, 255, 0));
    cv::line(img_example, cv::Point(130, 210), cv::Point(130, 290), cv::Scalar(0, 255, 0));
    lineBresenham(img, cv::Point(170, 290), cv::Point(170, 210), cv::Scalar(0, 0, 255));
    cv::line(img_example, cv::Point(170, 290), cv::Point(170, 210), cv::Scalar(0, 0, 255));

    // Save the image
    cv::imwrite("output.png", img);
    cv::imwrite("output_example.png", img_example);

    // Show the image, wait for user keystroke and quit
    cv::imshow("output", img);
    cv::imshow("output_example", img_example);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}