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

/*
 * We implement the IMU API by just wrapping functions in external/libpybricks/lib/pbio/src/imu.c.
 */

pbio_error_t hub_imu_init(void) {
  pbio_imu_init();
  return PBIO_SUCCESS;
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
