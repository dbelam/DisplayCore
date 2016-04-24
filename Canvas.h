#ifndef _CANVAS_H_
#define	_CANVAS_H_

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

#include "Scene.h"

#define SCREEN_WIDTH    240
#define SCREEN_HEIGHT   240
#define STRING_LENGTH   10

class Canvas
{
public:
	int height;
	int width;
	int sceneCount;
	int currentScene;
	Scene scenes[];

	vm_graphic_frame_t* g_frame_group[1];
	vm_graphic_frame_t frame;
	VMWCHAR g_wide_string[STRING_LENGTH];
	VMINT g_clock_x;
	VMINT g_clock_y;
	VM_TIMER_ID_PRECISE g_timer_id;
	VMUINT8* font_pool;

	void changeScene(int sceneNumber);
	void changeScene(VMWSTR sceneName);
	void initCanvas();
	void destroyCanvas();
	void drawCanvas();
	Canvas();
private:

};




void timer_callback();

#endif
