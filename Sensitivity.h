#if !defined(AFX_SENSITIVITY_H__E5DF9766_073E_4E8F_84D3_B2C540FEB2BB__INCLUDED_)
#define AFX_SENSITIVITY_H__E5DF9766_073E_4E8F_84D3_B2C540FEB2BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sensitivity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Sensitivity dialog

class Sensitivity : public CDialog
{
// Construction
public:
	Sensitivity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Sensitivity)
	enum { IDD = IDD_Sensitivity };
	double	m_S_SZM;
	double	m_S_SZMMIN;
	double	m_S_SZMMAX;
	double	m_S_T0;
	double	m_S_T0MIN;
	double	m_S_T0MAX;
	double	m_S_TD;
	double	m_S_TDMIN;
	double	m_S_TDMAX;
	double	m_S_SR;
	double	m_S_SRMIN;
	double	m_S_SRMAX;
	double	m_S_CHV;
	double	m_S_CHVMIN;
	double	m_S_CHVMAX;
	double	m_S_E;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Sensitivity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Sensitivity)
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeST0();
	afx_msg void OnChangeST0min();
	afx_msg void OnChangeST0max();
	afx_msg void OnChangeSTd();
	afx_msg void OnChangeSTdmin();
	afx_msg void OnChangeSTdmax();
	afx_msg void OnChangeSSr();
	afx_msg void OnChangeSSrMin();
	afx_msg void OnChangeSrMax();
	afx_msg void OnChangeSChv();
	afx_msg void OnChangeSChvmin();
	afx_msg void OnChangeSChvmax();
	afx_msg void OnSensitivityanalysis();
	afx_msg void OnButtonT0();
	afx_msg void OnButtonTD();
	afx_msg void OnButtonSRMAX();
	afx_msg void OnButtonchv();
	afx_msg void OnButton_CHV();
	afx_msg void OnButtonOutputPara();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENSITIVITY_H__E5DF9766_073E_4E8F_84D3_B2C540FEB2BB__INCLUDED_)
