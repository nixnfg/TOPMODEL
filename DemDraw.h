#if !defined(AFX_DEMDRAW_H__C8DAEF49_43F5_4AAA_B9BE_177D93FA3633__INCLUDED_)
#define AFX_DEMDRAW_H__C8DAEF49_43F5_4AAA_B9BE_177D93FA3633__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DemDraw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DemDraw dialog

class DemDraw : public CDialog
{
// Construction
public:
	DemDraw(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DemDraw)
	enum { IDD = IDD_DemDraw };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DemDraw)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DemDraw)
	afx_msg void OnBopen();
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSelendokColor();
	afx_msg void OnDEMfill();
	afx_msg void OnButtonFlowdirection();
	afx_msg void OnButtonArea();
	afx_msg void OnButtonTopindex();
	afx_msg void OnButtonWatertable();
	afx_msg void OnButtonRivernet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMDRAW_H__C8DAEF49_43F5_4AAA_B9BE_177D93FA3633__INCLUDED_)
