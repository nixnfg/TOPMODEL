#if !defined(AFX_OPTIMIZING_H__8F9467FD_34F1_4008_AC7F_095A5CD85996__INCLUDED_)
#define AFX_OPTIMIZING_H__8F9467FD_34F1_4008_AC7F_095A5CD85996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Optimizing.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Optimizing dialog

class Optimizing : public CDialog
{
// Construction
public:
	Optimizing(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Optimizing)
	enum { IDD = IDD_Optimizing };
	int		m_random;
	double	m_OPI_CHV;
	double	m_OPI_SRmax;
	double	m_OPI_SZM;
	double	m_OPI_TO;
	double	m_OPI_TD;
	double	m_OPI_Efficiency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Optimizing)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Optimizing)
	afx_msg void OnChange_random();
	virtual void OnOK();
	afx_msg void On_Optimizing();
	afx_msg void OnChangeEEfficiency();
	afx_msg void OnChangeOpiSzm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIMIZING_H__8F9467FD_34F1_4008_AC7F_095A5CD85996__INCLUDED_)
