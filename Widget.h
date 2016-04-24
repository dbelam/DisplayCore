#include "WidgetDimension.h"

class Widget
{
public:
	WidgetDimension widgetDimension;
	bool collosionDetection(WidgetDimension otherObject);
	bool touchDetection(int x, int y);
	void drawWidget();
	Widget();

};
