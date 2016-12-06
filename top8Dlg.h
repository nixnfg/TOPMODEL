// top8Dlg.h : header file








////////////////////////////////////////

#if !defined(AFX_TOP8DLG_H__CB76026E_DBA8_41FD_BEC7_49530EDABDFB__INCLUDED_)
#define AFX_TOP8DLG_H__CB76026E_DBA8_41FD_BEC7_49530EDABDFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTop8Dlg dialog

class CTop8Dlg : public CDialog
{
// Construction
public:
	CTop8Dlg(CWnd* pParent = NULL);	// standard constructor




//CString m_msg11;
//CString m_msg22;
//CString m_msg33;
//CString m_msg44;
/////////////////////////////////////////////////////////////////////////////
/*
 void TOPmod();
void Input1();
void Init();
void Results();
*/

// Dialog Data
	//{{AFX_DATA(CTop8Dlg)
	enum { IDD = IDD_TOP8_DIALOG };
    
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTop8Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTop8Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInput();
	afx_msg void OnParameter();
	virtual void OnOK();
	afx_msg void OnOptimizing();
	afx_msg void OnDraw();
	afx_msg void OnDemDraw();
	afx_msg void OnBUTTONwatertable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOP8DLG_H__CB76026E_DBA8_41FD_BEC7_49530EDABDFB__INCLUDED_)
