#pragma once
#include "Widget.h"
#include "vmtype.h"

/*
 * Class and superclass for scenes on the screen.
 * */

class Scene
{
public:
	VMWSTR sceneName;	// unique identifier
	int widgetCount;
	Widget widgets[];	// array of widgets (to be drawn)

	bool constantBacklight;
	VMUINT32 backlightTimeout;

	void addWidget(Widget widget);
	void drawScene();
	void activateScene();
	void deactivateScene();
	void touchEventHandler(int x, int y);
	Scene();
	Scene(VMWSTR name);
	/*
		 * WidgetArray
		 * WidgetCount
		 *
		 * addWidget()
		 * deleteWidgets()
		 * Widget[] getWidgets()
		 *
		 * void addToCanvas(canvas* c)
		 *
		 * */
private:
	bool isActive;
};
