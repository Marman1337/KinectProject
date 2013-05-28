// OpenGLControl.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ComputerizedDanceClassroomApplication.h"
#include "OpenGLControl.h"
#include "GlutSkeletonDialog.h"
#include "SkeletonDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLControl

COpenGLControl::COpenGLControl()
{
	dc = NULL;
}

COpenGLControl::~COpenGLControl()
{
	if (dc)
	{
		delete dc;
	}
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

END_MESSAGE_MAP()

void COpenGLControl::InitGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);							
	//glEnable(GL_DEPTH_TEST);					
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void COpenGLControl::Create(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH),
		NULL);

	CreateEx(
		0,
		className,
		L"OpenGL",
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		rect,
		parent,
		0);
}

void COpenGLControl::OnPaint()
{	
	bool error = false;
	openGLDevice.makeCurrent();

	sampleViewer.renderOpenGL(OptionSelect, error);
	if (error == true)
	{
		exit(1);
	}
	SwapBuffers(dc->m_hDC);
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cy == 0)								
	{
		cy = 1;						
	}

	glViewport(0,0,cx,cy);
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();
	glOrtho(-1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f);
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();
}


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	dc = new CClientDC(this);
	openGLDevice.create(dc->m_hDC);
	return 0;
}

BOOL COpenGLControl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}