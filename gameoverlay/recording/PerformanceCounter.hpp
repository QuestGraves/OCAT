//
// Copyright(c) 2016 Advanced Micro Devices, Inc. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#pragma once

#include <chrono>
#include <cstdint>
#include <vector>

namespace gameoverlay {
class PerformanceCounter {
 public:
  struct FrameInfo {
    std::int32_t fps = 0;
    float ms = 0.0f;
  };

  struct CaptureResults {
    float averageFPS = 0.0f;
    float averageMS = 0.0f;
    float frameTimePercentile = 0.0f;
  };

  PerformanceCounter();

  const FrameInfo& NextFrame();
  const CaptureResults& GetLastCaptureResults() const;
  void Start();
  void Stop();

 private:
  const static std::chrono::duration<double, std::milli> refreshRate_;

  std::chrono::high_resolution_clock::time_point lastFrame_;
  std::chrono::high_resolution_clock::time_point recordingStart_;
  std::chrono::duration<double, std::milli> deltaTime_;

  FrameInfo currentFrameInfo_;
  CaptureResults prevCaptureResults_;
  std::int64_t currentFrameCount_ = 0;
  std::int64_t totalFrameCount_ = 0;

  std::vector<double> frameTimes_;
};
}
