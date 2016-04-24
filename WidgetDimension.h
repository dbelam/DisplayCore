class WidgetDimension {
public:
	int x1;
	int x2;
	int y1;
	int y2;
	WidgetDimension() {
		this->x1 = 0;
		this->x2 = 0;
		this->y1 = 0;
		this->y2 = 0;
	}
	WidgetDimension(int x1, int x2, int y1, int y2) {
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
	}
};
