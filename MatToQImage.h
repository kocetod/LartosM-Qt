#ifndef MATTOQIMAGE_H
#define MATTOQIMAGE_H

#include <QDialog>
#include <QDebug>
// OpenCV header files
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui_c.h>

using namespace cv;

QImage MatToQImage(const Mat&);

#endif // MATTOQIMAGE_H
