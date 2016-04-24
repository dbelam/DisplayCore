#include "Display.h"

Display display;

void backlightTimer(VM_TIMER_ID_PRECISE timer_id, void* user_data)
{
	display.timerTick();
	if(display.isTimeoutOccurred())
	{
		display.backlightOff();
	}
}

void touchEvent(VM_TOUCH_EVENT event, VMINT x, VMINT y)
{
	display.touchHandler(event, x, y);
}

Display::Display()
{
	this->isBacklightInited = false;
	this->isBacklightOn = false;
	this->isBacklightLocked = false;
	this->isTimerActivated = false;
	this->backlightLockId = 0;
	this->backlightCounter = 0;
	this->backlightTimeout = 50;
	this->backlightNextTimeout = 0;
	this->backlightLevel = 50;
	initBacklight();
}

Display::~Display() {
	deinitBacklight();
}

void Display::initBacklight() {
	vm_dcl_config_pin_mode(BACKLIGHT_PIN, VM_DCL_PIN_MODE_PWM);
	isBacklightInited = true;
}

void Display::deinitBacklight()
{
	backlightOff();
	stopTimer();
	isBacklightInited = false;
}

void Display::startTimer()
{
	if(this->isTimerActivated == false)
	{
		this->backlightCounter = 0;
		g_precise_id = vm_timer_create_precise(100, backlightTimer, NULL);
		this->isTimerActivated = true;
	}
}
void Display::stopTimer()
{
	if(this->isTimerActivated)
	{
		vm_timer_delete_precise(g_precise_id);
		this->isTimerActivated = false;
	}
}

void Display::setBacklightLevel(VMUINT32 backlightLevel)
{
	if((backlightLevel >= 0) && (backlightLevel <= 100))
	{
		this->backlightLevel = backlightLevel;
	}
	if(isBacklightOn)
	{
		setBacklightPWM(backlightLevel);
	}
}

void Display::setBacklightTimeout(VMUINT32 ds)
{
	backlightTimeout = ds;
}

void Display::pokeBacklight()
{
	backlightOn();
	backlightNextTimeout = backlightCounter + backlightTimeout;
}

void Display::pokeBacklight(VMUINT32 ds)
{
	backlightOn();
	backlightNextTimeout = backlightCounter + ds;
}

VMUINT32 Display::lockBacklight()
{
	if(isBacklightLocked == false)
	{
		isBacklightLocked = true;
		backlightOn();
		backlightLockId++;
		return backlightLockId;

	}
}
void Display::unlockBacklight(VMUINT32 lockId)
{
	if(isBacklightLocked && backlightLockId == lockId)
	{
		isBacklightLocked = false;
		pokeBacklight();
	}
}

void Display::selectScene(int number)
{
	// deactivate previous scene
	// getTimeout
	// activate scene
}

void Display::selectScene(VMWSTR sceneName) {}
void Display::addScene(Scene& scene) {}
void Display::removeScene(Scene& scene) {}
void Display::removeScene(VMWSTR sceneName) {}
void Display::removeScene(int sceneNumber) {}
void Display::touchHandler(VM_TOUCH_EVENT event, VMINT32 x, VMINT32 y)
{
	if (event == VM_TOUCH_EVENT_TAP) {
		pokeBacklight();
	} else if (event == VM_TOUCH_EVENT_RELEASE) {

	}

}

void Display::buttonHandler()
{
	if(!(this->isBacklightLocked))
	{
		if(this->isBacklightOn)
		{
			backlightOff();
		}
		else
		{
			//if(scene overrides backlight timeout)
			pokeBacklight();
		}
	}

}

void Display::backlightOn()
{
	if(isBacklightOn == false)
	{
		vm_pwr_lcd_sleep_out();
		startTimer();
		setBacklightPWM(backlightLevel);
		isBacklightOn = true;
	}

}
void Display::backlightOff()
{
	if(isBacklightOn)
	{
		vm_pwr_lcd_sleep_in();
		stopTimer();
		setBacklightPWM(0);
		isBacklightOn = false;
	}
}

void Display::setBacklightPWM(VMUINT32 ulValue) {
	if(isBacklightInited) {
		VM_DCL_HANDLE pwm_handle;
		vm_dcl_pwm_set_clock_t pwm_clock;
		vm_dcl_pwm_set_counter_threshold_t pwm_config_adv;

		pwm_handle = vm_dcl_open(PIN2PWM(BACKLIGHT_PIN),vm_dcl_get_owner_id());
		vm_dcl_control(pwm_handle,VM_PWM_CMD_START,0);
		pwm_config_adv.counter = 100;
		pwm_config_adv.threshold = ulValue;
		pwm_clock.source_clock = 0;
		pwm_clock.source_clock_division =3;
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_CLOCK,(void *)(&pwm_clock));
		vm_dcl_control(pwm_handle,VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD,(void *)(&pwm_config_adv));
		vm_dcl_close(pwm_handle);
		if(ulValue > 0)
		{
			isBacklightOn = true;
		}
		else
		{
			isBacklightOn = false;
		}

	}
}

bool Display::isTimeoutOccurred()
{
	if(this->isBacklightOn && (!this->isBacklightLocked) && (this->backlightCounter > this->backlightNextTimeout))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Display::timerTick()
{
	this->backlightCounter++;
}

}
