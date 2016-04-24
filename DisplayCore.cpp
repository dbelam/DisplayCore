
/*
 This sample code is in public domain.

 This sample code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 This sample draws a digital clock.
 It draws a color background with API vm_graphic_draw_solid_rectangle(),
 gets the time by vm_time_get_date_time(), and print the time text by API
 vm_graphic_draw_text().
 Modify the macro SCREEN_WIDTH and SCREEN_HEIGHT to fit your display device.
 */
#include "DisplayCore.h"
#include "vmtype.h"
#include "vmstdlib.h"
#include "vmlog.h"
#include "vmgraphic.h"
#include "vmsystem.h"
#include "ResID.h"
#include "vmchset.h"
#include "vmgraphic_font.h"
#include "vmtimer.h"
#include "vmdatetime.h"
#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmdcl_pwm.h"
#include "vmres.h"
#include "Display.h"
#include "globals.h"
#include "Canvas.h"
#include "vmkeypad.h"
#include "vmtouch.h"
#include "tp_goodix_gt9xx.h"

using namespace std;

#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   240
#define STRING_LENGTH   10

//Display display; 	// globally available Display object
Canvas canvas;// globally available Canvas object

void handle_sysevt(VMINT message, VMINT param) {
	switch (message) {
		case VM_EVENT_CREATE:
		vm_res_init(0);
		break;
		case VM_EVENT_PAINT:
		vm_log_info("Paint!");
		canvas.drawCanvas();
		break;
		case VM_EVENT_QUIT:
		canvas.destroyCanvas();
		vm_res_release();
		break;
	}
}

void handle_touchevt(VM_TOUCH_EVENT event, VMINT x, VMINT y) {
	display.touchHandler(event, x, y);
	vm_log_info("oooh, you touched my tralala");
}

VMINT handle_keypad_event(VM_KEYPAD_EVENT event, VMINT code) {
	/* output log to monitor or catcher */
	vm_log_info("key event=%d,key code=%d",event,code); /* event value refer to VM_KEYPAD_EVENT */

	if (code == 30) {
		if (event == 3) { // long pressed
			// turn off peripheral

		} else if (event == 2) { // down
			display.buttonHandler();

		} else if (event == 1) { // up
		}
	}
	return 0;
}

void vm_main(void) {
	vm_log_debug("System startup almost complete!");
	lcd_st7789s_init();
	tp_gt9xx_init();
	display.setBacklightLevel(50);
	display.setBacklightTimeout(10);
	display.pokeBacklight(10);
	vm_pmng_register_system_event_callback(handle_sysevt); //
	vm_touch_register_event_callback(handle_touchevt);
	vm_keypad_register_event_callback(handle_keypad_event);
	vm_log_debug("System startup complete!");
}
}

