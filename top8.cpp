// top8.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "top8.h"
#include "top8Dlg.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString path;//定义一个全局变量来存储本程序所在路径


/////////////////////////////////////////////////////////////////////////////
// CTop8App

BEGIN_MESSAGE_MAP(CTop8App, CWinApp)
	//{{AFX_MSG_MAP(CTop8App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTop8App construction

CTop8App::CTop8App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTop8App object

CTop8App theApp;

/////////////////////////////////////////////////////////////////////////////
// CTop8App initialization

BOOL CTop8App::InitInstance()
{
	CTop8Dlg dlg;
	/////获取程序当前路径//////
    char buf[100];
    path=getcwd(buf,100);
   // AfxMessageBox("本程序工作目录:"+path);
	////////////////
    m_pMainWnd=&dlg;//先于DoModal()调用，将对话框设置为下面设置的背景色、文本色
	SetDialogBkColor(RGB(248,248,255),RGB(0,0,0));
    int nResponse=dlg.DoModal(); 
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
