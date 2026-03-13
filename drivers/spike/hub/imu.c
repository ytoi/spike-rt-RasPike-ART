/*
 * SPDX-License-Identifier: MIT
 *
 * API for the hub built-in IMU.
 *
 * Copyright (c) 2022 Embedded and Real-Time Systems Laboratory,
 *            Graduate School of Information Science, Nagoya Univ., JAPAN
 */
#include <t_syslog.h>
#include <spike/hub/imu.h>

#include <pbio/imu.h>
#include <math.h>

/*
 * We implement the IMU API by just wrapping functions in external/libpybricks/lib/pbio/src/imu.c.
 */

pbio_error_t hub_imu_init(void) {
  pbio_imu_init();
  pbio_imu_persistent_settings_t settings;
  if (pbio_imu_get_settings(&settings) == PBIO_SUCCESS) {
    pbio_imu_apply_loaded_settings(&settings);
  } else {
    pbio_imu_set_default_settings(&settings);
  }
  return PBIO_SUCCESS;
}

bool hub_imu_is_ready(void) {
  return pbio_imu_is_ready();
}

bool hub_imu_is_stationary(void) {
  return pbio_imu_is_stationary();
}

void hub_imu_set_tilt(float angle) {
  double T = (double) angle * M_PI / 180.0f;
  double sinT = sin(T);
  double cosT = cos(T);
  pbio_geometry_xyz_t front = { .x = +cosT, .y = 0.0f, .z = +sinT };
  pbio_geometry_xyz_t top   = { .x = -sinT, .y = 0.0f, .z = +cosT };
  pbio_imu_set_base_orientation(&front, &top);
}

void hub_imu_get_acceleration(float accel[3]) {
  pbio_imu_get_acceleration((pbio_geometry_xyz_t *) accel, true);
}

void hub_imu_get_angular_velocity(float angv[3]) {
  pbio_imu_get_angular_velocity((pbio_geometry_xyz_t *) angv, true);
}

float hub_imu_get_temperature(void) {
  return 0.0;
}

float hub_imu_get_heading(void) {
  return pbio_imu_get_heading(PBIO_IMU_HEADING_TYPE_3D);
}

void hub_imu_reset_heading(void) {
  pbio_imu_set_heading(0.0f);
}
