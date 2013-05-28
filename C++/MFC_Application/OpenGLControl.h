#if !defined(AFX_OPENGLCONTROL_H__52A6B63B_01A2_449D_8691_1FF59EECAB71__INCLUDED_)
#define AFX_OPENGLCONTROL_H__52A6B63B_01A2_449D_8691_1FF59EECAB71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "OpenGLDevice.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include "SampleViewer.h"

extern SampleViewer sampleViewer;

class COpenGLControl : public CWnd
{

public:
	COpenGLControl();
	void Create(CRect rect,CWnd* parent);
	virtual ~COpenGLControl();

protected:
	void InitGL();
	void DrawGLScene();
	OpenGLDevice openGLDevice;
	CClientDC* dc;

	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	DECLARE_MESSAGE_MAP()
};

#endif 