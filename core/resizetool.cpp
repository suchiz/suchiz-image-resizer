#include "resizetool.h"
#include <algorithm>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>


cv::Mat ResizeTool::resize(const cv::Mat &imageToResize) {
  cv::Size imageSize = imageToResize.size();
  cv::Size resizedSize;
  if (imageSize.height > imageSize.width) {
    float ratio = m_height / float(imageSize.height);
    resizedSize = cv::Size(static_cast<int>(imageSize.width * ratio), m_height);
  } else {
    float ratio = m_width / float(imageSize.width);
    resizedSize = cv::Size(m_width, static_cast<int>(imageSize.height * ratio));
  }
  cv::Mat resizedImage;
  cv::resize(imageToResize, resizedImage, resizedSize, cv::INTER_AREA);

  int maxSize = std::max(resizedSize.width, resizedSize.height);
  cv::Size centeredPosition((maxSize - resizedSize.width)/2,
                            (maxSize - resizedSize.height)/2);
  cv::Mat newImage(cv::Mat::ones(cv::Size(m_width, m_height), CV_8UC3));
  newImage.setTo(cv::Scalar(255,255,255));
  cv::Mat mask;
  inRange(resizedImage, cv::Scalar(0, 0, 0), cv::Scalar(0, 0, 0), mask);
  resizedImage.setTo(cv::Scalar(255, 255, 255), mask);
  resizedImage.copyTo(newImage(cv::Rect(0, centeredPosition.height, resizedSize.width, resizedSize.height)));
  return newImage;
}
