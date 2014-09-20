/*
 * Copyright 2014 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TANGO_DATA_H
#define TANGO_DATA_H
#define GLM_FORCE_RADIANS

#include <tango_client_api.h>
#include <sys/time.h>

#include "gl_util.h"

class TangoData {
 public:
  static TangoData& GetInstance() {
    static TangoData instance;
    return instance;
  }
  TangoData();
  ~TangoData();

  bool Initialize();
  bool SetConfig();
  bool LockConfig();
  bool UnlockConfig();
  bool Connect();
  void Disconnect();

  float* GetDepthBuffer();
  void SetDepthBuffer(float *buffer);
  int GetDepthBufferSize();
  void SetDepthBufferSize(int size);
  char* GetVersonString();
  glm::mat4 GetOC2OWMat(bool is_depth);
  void GetPoseAtTime(double timestamp);
  
  float average_depth;
  float depth_fps;
  float depth_frame_delta_time;
  float previous_frame_time_;
  
//  glm::mat4 oc_2_ow_mat_motion;
//  glm::mat4 oc_2_ow_mat_depth;
  
  // Start service to opengl world matrix.
  glm::mat4 ss_2_ow_mat;
  // Device to start service matrix.
  glm::mat4 d_2_ss_mat_depth;
  // Device to start service matrix.
  glm::mat4 d_2_ss_mat_motion;
  // Device to IMU matrix.
  glm::mat4 d_2_imu_mat;
  // Color camera to IMU matrix.
  glm::mat4 c_2_imu_mat;
  
  // Opengl camera to color camera matrix.
  glm::mat4 oc_2_c_mat;
private:
  void SetExtrinsicsMatrics();
  
  TangoConfig* config_;
  double pointcloud_timestamp_;
  float* depth_data_buffer_;
  int depth_buffer_size_;
  char* lib_version_;
  
};

#endif  // TANGO_DATA_H
