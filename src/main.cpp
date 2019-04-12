#include <opencv2/opencv.hpp>
#include "main.h"

int main()
{
    // Parameters
    const int width = 400;
    const int height = 200;

    // Build a canvas. Each element in the canvas is 3 unsigned char in the order of BGR.
    cv::Mat img(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    // Draw a smile face
    // Face
    circleMidPoint(img, cv::Point(100, 100), 80, cv::Scalar(0, 255, 255));
    // Eyes
    circleMidPoint(img, cv::Point(75, 73), 11, cv::Scalar(0, 255, 255));
    circleMidPoint(img, cv::Point(125, 73), 11, cv::Scalar(0, 255, 255));
    // Nose
    int n_contours_nose = 1;
    int n_vertices_nose[n_contours_nose] = {3};
    cv::Point vertices_nose[n_contours_nose][3];
    vertices_nose[0][0] = cv::Point(100, 90);
    vertices_nose[0][1] = cv::Point(91, 120);
    vertices_nose[0][2] = cv::Point(109, 120);
    const cv::Point *const_vertices_nose[n_contours_nose] = {vertices_nose[0]};
    polylinesBresenham(img, const_vertices_nose, n_vertices_nose, n_contours_nose, true, cv::Scalar(0, 255, 255));
    // Mouth
    int n_contours_mouth = 1;
    int n_vertices_mouth[n_contours_mouth] = {11};
    cv::Point vertices_mouth[n_contours_mouth][11];
    vertices_mouth[0][0] = cv::Point(74, 139);
    vertices_mouth[0][1] = cv::Point(79, 144);
    vertices_mouth[0][2] = cv::Point(85, 147);
    vertices_mouth[0][3] = cv::Point(88, 148);
    vertices_mouth[0][4] = cv::Point(93, 149);
    vertices_mouth[0][5] = cv::Point(100, 150);
    vertices_mouth[0][6] = cv::Point(107, 149);
    vertices_mouth[0][7] = cv::Point(112, 148);
    vertices_mouth[0][8] = cv::Point(115, 147);
    vertices_mouth[0][9] = cv::Point(121, 144);
    vertices_mouth[0][10] = cv::Point(126, 139);
    const cv::Point *const_vertices_mouth[n_contours_mouth] = {vertices_mouth[0]};
    polylinesBresenham(img, const_vertices_mouth, n_vertices_mouth, n_contours_mouth, false, cv::Scalar(0, 255, 255));

    // Fill nested squares
    int n_contours_square = 3;
    int n_vertices_square[n_contours_square] = {4, 4, 4};
    cv::Point vertices_square[n_contours_square][4];
    vertices_square[0][0] = cv::Point(220, 20);
    vertices_square[0][1] = cv::Point(380, 20);
    vertices_square[0][2] = cv::Point(380, 180);
    vertices_square[0][3] = cv::Point(220, 180);
    vertices_square[1][0] = cv::Point(300, 25);
    vertices_square[1][1] = cv::Point(375, 100);
    vertices_square[1][2] = cv::Point(300, 175);
    vertices_square[1][3] = cv::Point(225, 100);
    vertices_square[2][0] = cv::Point(270, 70);
    vertices_square[2][1] = cv::Point(330, 70);
    vertices_square[2][2] = cv::Point(330, 130);
    vertices_square[2][3] = cv::Point(270, 130);
    const cv::Point *const_vertices_square[n_contours_square] = {vertices_square[0], vertices_square[1], vertices_square[2]};
    fillPolyScanLine(img, const_vertices_square, n_vertices_square, n_contours_square, cv::Scalar(240, 207, 137));
    floodFillScanLine(img, cv::Point(300, 100), cv::Scalar(0, 200, 0));

    // // Use cv as control group
    // cv::Mat img_example(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    // // Draw a smile face
    // // Face
    // cv::circle(img_example, cv::Point(100, 100), 80, cv::Scalar(0, 255, 255));
    // // Eyes
    // cv::circle(img_example, cv::Point(75, 73), 11, cv::Scalar(0, 255, 255));
    // cv::circle(img_example, cv::Point(125, 73), 11, cv::Scalar(0, 255, 255));
    // // Nose
    // cv::polylines(img_example, const_vertices_nose, n_vertices_nose, n_contours_nose, true, cv::Scalar(0, 255, 255));
    // // Mouth
    // cv::polylines(img_example, const_vertices_mouth, n_vertices_mouth, n_contours_mouth, false, cv::Scalar(0, 255, 255));
    // // Fill nested squares
    // cv::fillPoly(img_example, const_vertices_square, n_vertices_square, n_contours_square, cv::Scalar(240, 207, 137));
    // cv::floodFill(img_example, cv::Point(300, 100), cv::Scalar(0, 200, 0));
    // // Save the image
    // cv::imwrite("output_example.png", img_example);
    // // Show the image
    // cv::imshow("output_example", img_example);

    // Save the image
    cv::imwrite("output.png", img);

    // Show the image, wait for user keystroke and quit
    cv::imshow("output", img);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}