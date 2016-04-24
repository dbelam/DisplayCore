#pragma once
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
#include "lcd_sitronix_st7789s.h"
#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmdcl_pwm.h"
#include "vmres.h"
#include "vmtouch.h"
#include "Scene.h"
#include "vmpwr.h"

/*
 * Display handler class.
 * Including handling scenes, touch and button press events,
 * managing backlight.
 *
 * */

#if defined(__HDK_LINKIT_ASSIST_2502__)
#define BACKLIGHT_PIN VM_PIN_P1
#else
#error " Board not supported!"
#endif

extern void backlightTimer(VM_TIMER_ID_PRECISE timer_id, void* user_data);
extern void touchEvent(VM_TOUCH_EVENT event, VMINT x, VMINT y);

class Display {
public:
	void initBacklight();
	void deinitBacklight();
	void startTimer();
	void stopTimer();
	void setBacklightLevel(VMUINT32 backlightLevel);
	void setBacklightTimeout(VMUINT32 ds);
	void pokeBacklight();
	void pokeBacklight(VMUINT32 ds);
	VMUINT32 lockBacklight();
	void unlockBacklight(VMUINT32 lockId);
	void selectScene(int number);
	void selectScene(VMWSTR sceneName);
	void addScene(Scene& scene);
	void removeScene(Scene& scene);
	void removeScene(VMWSTR sceneName);
	void removeScene(int sceneNumber);
	void touchHandler(VM_TOUCH_EVENT event, VMINT32 x, VMINT32 y);
	void buttonHandler();
	void backlightOn();
	void backlightOff();
	void setBacklightPWM(VMUINT32 ulValue);
	bool isTimeoutOccurred();
	void timerTick();

	Display();
	~Display();
private:
	Scene scenes[];
	int activeScene;

	bool isBacklightInited;
	bool isBacklightOn;
	bool isBacklightLocked;
	bool isTimerActivated;
	VMUINT32 backlightLockId;
	VMUINT32 backlightCounter;
	VMUINT32 backlightTimeout;
	VMUINT32 backlightNextTimeout;
	VMUINT32 backlightLevel;
	VM_TIMER_ID_PRECISE g_precise_id;

};

extern Display display;
