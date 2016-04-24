#include "Scene.h"

void Scene::addWidget(Widget widget)
{

}

void Scene::drawScene()
{
	for(int i = 0; i < this->widgetCount; i++)
	{
		widgets[i].drawWidget();
	}
}

void Scene::touchEventHandler(int x, int y)
{
	// send touch event to every Widget on the Scene
}

Scene::Scene()
{
	this->sceneName = 0;
	this->widgetCount = 0;
	this->constantBacklight = false;
	this->backlightTimeout = 0;
}

Scene::Scene(VMWSTR name)
{
	this->sceneName = name;
	this->widgetCount = 0;
}
