#include "kernel_cfg.h"
#include "app.h"
#include <stdio.h>
#include <serial/newlib.h>

#include <spike/hub/imu.h>
#include <pbio/imu.h>
#include <pbdrv/imu.h>

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  dly_tsk(5*1000*1000);

  FILE *fp = serial_open_newlib_file(SIO_USB_PORTID);
  fprintf(fp, "Start !!\n");
    
  hub_imu_init();
  pbio_imu_persistent_settings_t settings;
  pbio_imu_set_default_settings(&settings);

  while (1) {
    pbdrv_imu_dev_t *imu_dev;
    pbdrv_imu_config_t *imu_config;
    pbio_error_t err = pbdrv_imu_get_imu(&imu_dev, &imu_config);
    if (err != PBIO_SUCCESS) fprintf(fp, "imu_dev: %d\n", err);
    bool ready = pbio_imu_is_ready();
    bool pbio_q = pbio_imu_is_stationary();
    bool pbdrv_q = pbdrv_imu_is_stationary(imu_dev);
    fprintf(fp, "[%c%c%c] ", ready ? 'T' : 'F', pbio_q ? 'T' : 'F', pbdrv_q ? 'T' : 'F');
    float v[3],  a[3], t;
    int  iv[3], ia[3];
    hub_imu_get_angular_velocity(v);
    hub_imu_get_acceleration(a);
    t = hub_imu_get_temperature();
    for (int i = 0; i < 3; i++) {
      iv[i] = (int) v[i];
      ia[i] = (int) a[i];
    }
    fprintf(fp, "v = (%d %d %d), a = (%d %d %d), t = %f\n", iv[0], iv[1], iv[2], ia[0], ia[1], ia[2], t);
    dly_tsk(1000*1000);
  }
  
  /* タスク終了 */
  ext_tsk();
}
