// top8.h : main header file for the TOP8 application
//

#if !defined(AFX_TOP8_H__C5E3CD5C_CDAA_44CE_A827_664BAA826BC3__INCLUDED_)
#define AFX_TOP8_H__C5E3CD5C_CDAA_44CE_A827_664BAA826BC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTop8App:
// See top8.cpp for the implementation of this class
//

class CTop8App : public CWinApp
{
public:
	CTop8App();
    
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTop8App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTop8App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOP8_H__C5E3CD5C_CDAA_44CE_A827_664BAA826BC3__INCLUDED_)
