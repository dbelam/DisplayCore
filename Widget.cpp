#include "Widget.h"

bool Widget::collosionDetection(WidgetDimension otherObject) {
	if (touchDetection(otherObject.x1, otherObject.y1)
			|| touchDetection(otherObject.x2, otherObject.y1)
			|| touchDetection(otherObject.x1, otherObject.y2)
			|| touchDetection(otherObject.x2, otherObject.y2)) {
		return true;
	} else {
		return false;
	}
}

bool Widget::touchDetection(int x, int y) {
	if ((this->widgetDimension.x1 <= x) && (this->widgetDimension.x2 >= x)
			&& (this->widgetDimension.y1 <= y)
			&& (this->widgetDimension.y2 >= y)) {
		return true;
	} else {
		return false;
	}
}

void Widget::drawWidget() {

}

Widget::Widget() {
	this->widgetDimension.x1 = 0;
	this->widgetDimension.x2 = 0;
	this->widgetDimension.y1 = 0;
	this->widgetDimension.y2 = 0;
}
