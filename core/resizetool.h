#pragma once

#include <stdint.h>

namespace cv {
class Mat;
}

class ResizeTool {
public:
  ResizeTool() = default;

  cv::Mat resize(const cv::Mat &imageToResize);

private:
  uint16_t m_width = 700;
  uint16_t m_height = 700;
};
