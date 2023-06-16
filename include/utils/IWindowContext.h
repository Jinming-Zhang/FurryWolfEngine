#pragma once
/// <summary>
/// Responsible for creating a window context for opengl to attach to
/// Features include 
/// - detect window operations
/// - swap buffers
/// </summary>
class IWindowContext
{
public:
	virtual ~IWindowContext() {};
	virtual	bool Initialize(int width, int height) = 0;
	virtual	void SwapBuffers() = 0;
	virtual bool WindowShouldClose() = 0;
	virtual int GetBufferWidth() = 0;
	virtual int GetBufferHeight() = 0;
	// inputs
	virtual bool* GetKeys() = 0;
	virtual float GetXChange() = 0;
	virtual float GetYChange() = 0;
};

