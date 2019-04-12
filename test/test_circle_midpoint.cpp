#include "../src/main.h"

int main()
{
    // Parameters
    const int width = 200;
    const int height = 200;

    // Build a canvas. Each element in the canvas is 3 unsigned char in the order of BGR.
    cv::Mat img(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat img_example(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    // Draw circles using mid-point algorithm and cv::circle.
    circleMidPoint(img, cv::Point(100, 100), 50, cv::Scalar(255, 0, 0));
    cv::circle(img_example, cv::Point(100, 100), 50, cv::Scalar(255, 0, 0));

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