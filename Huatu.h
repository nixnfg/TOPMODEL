#if !defined(AFX_HUATU_H__A15B4EEC_CA00_461D_B29A_675ED92D70FE__INCLUDED_)
#define AFX_HUATU_H__A15B4EEC_CA00_461D_B29A_675ED92D70FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Huatu.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Huatu dialog

class Huatu : public CDialog
{
// Construction
public:
	Huatu(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Huatu)
	enum { IDD = IDD_Huatu };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Huatu)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Huatu)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HUATU_H__A15B4EEC_CA00_461D_B29A_675ED92D70FE__INCLUDED_)
