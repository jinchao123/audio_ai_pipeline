
#ifndef SHERPA_ONNX_CSRC_VOICE_ACTIVITY_DETECTOR_H_
#define SHERPA_ONNX_CSRC_VOICE_ACTIVITY_DETECTOR_H_

#include <memory>
#include <vector>

 
#include "vad-model-config.h"

namespace sherpa_onnx {

struct SpeechSegment {
  int32_t start;  // in samples
  std::vector<float> samples;
};

class VoiceActivityDetector {
 public:
  explicit VoiceActivityDetector(const VadModelConfig &config,
                                 float buffer_size_in_seconds = 60);
 
  ~VoiceActivityDetector();

  void AcceptWaveform(const float *samples, int32_t n);
  bool Empty() const;
  void Pop();
  void Clear();
  const SpeechSegment &Front() const;

  bool IsSpeechDetected() const;

  void Reset();

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace sherpa_onnx

#endif  // SHERPA_ONNX_CSRC_VOICE_ACTIVITY_DETECTOR_H_
