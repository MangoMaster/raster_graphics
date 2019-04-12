#include "../src/main.h"

int main()
{
    // Parameters
    const int width = 300;
    const int height = 200;

    // Build a canvas. Each element in the canvas is 3 unsigned char in the order of BGR.
    cv::Mat img(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat img_example(height, width, CV_8UC3, cv::Scalar(0, 0, 0));

    // Fill polygen using scan-line algorithm and cv::fillPoly.
    int n_contours = 8;
    cv::Point vertices[n_contours][8];
    vertices[0][0] = cv::Point(10, 10);
    vertices[0][1] = cv::Point(10, 90);
    vertices[0][2] = cv::Point(90, 90);
    vertices[0][3] = cv::Point(90, 10);

    vertices[1][0] = cv::Point(50, 110);
    vertices[1][1] = cv::Point(10, 150);
    vertices[1][2] = cv::Point(50, 190);
    vertices[1][3] = cv::Point(90, 150);

    vertices[2][0] = cv::Point(110, 10);
    vertices[2][1] = cv::Point(190, 10);
    vertices[2][2] = cv::Point(110, 90);
    vertices[2][3] = cv::Point(190, 90);

    vertices[3][0] = cv::Point(110, 110);
    vertices[3][1] = cv::Point(110, 190);
    vertices[3][2] = cv::Point(190, 110);
    vertices[3][3] = cv::Point(190, 190);

    vertices[4][0] = cv::Point(210, 10);
    vertices[4][1] = cv::Point(290, 10);
    vertices[4][2] = cv::Point(290, 90);
    vertices[4][3] = cv::Point(210, 90);

    vertices[5][0] = cv::Point(250, 20);
    vertices[5][1] = cv::Point(280, 50);
    vertices[5][2] = cv::Point(250, 80);
    vertices[5][3] = cv::Point(220, 50);

    vertices[6][0] = cv::Point(235, 35);
    vertices[6][1] = cv::Point(265, 35);
    vertices[6][2] = cv::Point(265, 65);
    vertices[6][3] = cv::Point(235, 65);

    vertices[7][0] = cv::Point(230, 110);
    vertices[7][1] = cv::Point(240, 140);
    vertices[7][2] = cv::Point(260, 120);
    vertices[7][3] = cv::Point(280, 190);
    vertices[7][4] = cv::Point(210, 190);
    vertices[7][5] = cv::Point(230, 150);
    vertices[7][6] = cv::Point(210, 150);

    const cv::Point *const_vertices[n_contours] = {vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7]};
    int n_vertices[n_contours] = {4, 4, 4, 4, 4, 4, 4, 7};

    polylinesBresenham(img, const_vertices, n_vertices, n_contours, true, cv::Scalar(255, 0, 0));
    cv::polylines(img_example, const_vertices, n_vertices, n_contours, true, cv::Scalar(255, 0, 0));

    cv::Point seed_point = cv::Point(50, 50);
    cv::Scalar new_color = cv::Scalar(0, 0, 255);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

    seed_point = cv::Point(30, 130);
    new_color = cv::Scalar(0, 0, 255);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

    seed_point = cv::Point(150, 30);
    new_color = cv::Scalar(0, 255, 0);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

    seed_point = cv::Point(150, 150);
    new_color = cv::Scalar(0, 255, 0);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

    seed_point = cv::Point(250, 50);
    new_color = cv::Scalar(0, 255, 255);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

    seed_point = cv::Point(250, 30);
    new_color = cv::Scalar(255, 0, 255);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

    seed_point = cv::Point(250, 150);
    new_color = cv::Scalar(0, 255, 255);
    floodFillScanLine(img, seed_point, new_color);
    cv::floodFill(img_example, seed_point, new_color);

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