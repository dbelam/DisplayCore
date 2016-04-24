#include "Canvas.h"
using namespace std;


void Canvas::changeScene(int sceneNumber)
{
	if((this->sceneCount > 0) && (sceneNumber < this->sceneCount) && (sceneNumber > 0) && (this->scenes != NULL))
	{
		this->currentScene = sceneNumber;
	}
}

void Canvas::changeScene(VMWSTR sceneName)
{
	if((this->sceneCount > 0) && (this->scenes != NULL))
	{
		for(int i = 0; i < sceneCount; i++)
		{
			if(vm_wstr_compare(scenes[i].sceneName, sceneName) == 0)
			{
				this->changeScene(i);
				return;
			}
		}
	}
}

void Canvas::initCanvas()
{

}

void Canvas::destroyCanvas()
{

}

void Canvas::drawCanvas() {
	// scene validity check
	if((this->sceneCount > 0) && (this->currentScene < this->sceneCount) && (this->currentScene > 0) && (this->scenes != NULL))
	{
		this->scenes[currentScene].drawScene();
	}
}

Canvas::Canvas()
{
	this->height = SCREEN_HEIGHT;
	this->width = SCREEN_WIDTH;
	this->sceneCount = -1;
	this->currentScene = -1;
}
}
