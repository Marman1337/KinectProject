
#ifndef OPENGL_DEVICE_H
#define OPENGL_DEVICE_H

#if _MSC_VER > 1000
#pragma once
#endif 

#include <windows.h>

class OpenGLDevice
{
public:
	OpenGLDevice(HDC& deviceContext,int stencil = 0);
	OpenGLDevice(HWND& window,int stencil = 0);
	OpenGLDevice();

	bool create(HDC& deviceContext,int  stencil = 0);
	bool create(HWND& window,int stencil = 0);

	void destroy();
	void makeCurrent(bool disableOther = true);

	
	virtual ~OpenGLDevice();

protected:
	bool setDCPixelFormat(HDC& deviceContext,int stencil);
	
	HGLRC renderContext;
	HDC deviceContext;
};

#endif 
