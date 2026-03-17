#include "kernel_cfg.h"
#include "app.h"

#include <stdio.h>
#include <spike/hub/display.h>
#include <spike/hub/speaker.h>
#include <spike/hub/system.h>
#include <serial/serial.h>
#include <serial/newlib.h>
#include <syssvc/serial.h>

#define beep() hub_speaker_play_tone(NOTE_C4, 100)

/* メインタスク(起動時にのみ関数コールされる) */
void main_task(intptr_t unused) {

  // Connect to BT
  pbio_error_t err = serial_opn_por(SIO_BLUETOOTH_PORTID);
  if (err != E_OK) {
    beep();
    hub_display_text_scroll("PAIRING FAILED", 100);
    dly_tsk(5*1000*1000);
    hub_system_shutdown();
  }
  FILE *fp = serial_open_newlib_file(SIO_BLUETOOTH_PORTID);
  if (fp == NULL) {
    beep();
    hub_display_text_scroll("INVALID PORTID", 100);
    dly_tsk(5*1000*1000);
    hub_system_shutdown();
  }
  while (1) {
    char buffer[100];
    hub_display_char('?');
    fprintf(fp, "\n? ");
    fscanf(fp, "%s", buffer);
    hub_display_text_scroll(buffer, 100);
    fprintf(fp, "\n%s\n", buffer);
  }

  hub_system_shutdown();

  /* タスク終了 */
  ext_tsk();
}
