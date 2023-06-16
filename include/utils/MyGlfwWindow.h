#pragma once
#include "IWindowContext.h"
#include "GLFW/glfw3.h"
class MyGlfwWindow :public IWindowContext
{
public:
	MyGlfwWindow();
	virtual ~MyGlfwWindow();
	virtual	bool Initialize(int width, int height) override;
	virtual	void SwapBuffers() override;
	virtual bool WindowShouldClose() override;
	virtual int GetBufferWidth()override;
	virtual int GetBufferHeight()override;
	virtual bool* GetKeys() override;
	virtual float GetXChange()override;
	virtual float GetYChange() override;
	/// <summary>
	/// Callback for glfw key events
	/// </summary>
	void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	/// <summary>
	/// Callback for glfw mouse events
	/// </summary>
	void handleMouse(GLFWwindow* window, double xPos, double yPos);
private:
	GLFWwindow* window;
	int bufferWidth;
	int bufferHeight;
	// keyboard events
	bool keys[1024];
	// mouse events
	GLfloat lastMouseX;
	GLfloat lastMouseY;
	GLfloat mouseXChange;
	GLfloat mouseYChange;

};
