// encoding: utf-8
#ifndef MAIN_H_
#define MAIN_H_

#include <opencv2/opencv.hpp>

void lineBresenham(cv::Mat &image, cv::Point point1, cv::Point point2, const cv::Scalar &color);
void circleMidPoint(cv::Mat &image, cv::Point center, int radius, const cv::Scalar &color);
void polylinesBresenham(cv::Mat &image, const cv::Point **vertices, const int *n_vertices, int n_contours, bool is_closed, const cv::Scalar &color);
void fillPolyScanLine(cv::Mat &image, const cv::Point **vertices, const int *n_vertices, int n_contours, const cv::Scalar &color);
void floodFillScanLine(cv::Mat &image, cv::Point seed_point, const cv::Scalar &new_color);

// x和y为像素点的坐标
inline cv::Scalar getPixelColor(cv::Mat &image, int x, int y)
{
  cv::Scalar color;
  color[0] = image.at<cv::Vec3b>(y, x)[0];
  color[1] = image.at<cv::Vec3b>(y, x)[1];
  color[2] = image.at<cv::Vec3b>(y, x)[2];
  return color;
}

// x和y为像素点的坐标
inline void drawPixel(cv::Mat &image, int x, int y, const cv::Scalar &color)
{
  image.at<cv::Vec3b>(y, x)[0] = color[0];
  image.at<cv::Vec3b>(y, x)[1] = color[1];
  image.at<cv::Vec3b>(y, x)[2] = color[2];
}

// Node for edge table
struct EdgeTableNode
{
  double x;
  double delta_x;
  int y_max;
  EdgeTableNode(int x, int y_max, double delta_x)
      : x(x), y_max(y_max), delta_x(delta_x) {}
};

#endif // MAIN_H_