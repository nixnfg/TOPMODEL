#if !defined(AFX_INPUT_H__6B070D58_9482_49A6_920E_378BCD6C7C79__INCLUDED_)
#define AFX_INPUT_H__6B070D58_9482_49A6_920E_378BCD6C7C79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Input.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Input dialog

class Input : public CDialog
{
// Construction
public:
	Input(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Input)
	enum { IDD = IDD_Input };
	CButton	m_save;
	CButton	m_rain;
	CButton	m_dlx;
	CButton	m_dem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Input)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Input)
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void Onsave();
	afx_msg void Onrain();
	afx_msg void Ondlx();
	afx_msg void Ondem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUT_H__6B070D58_9482_49A6_920E_378BCD6C7C79__INCLUDED_)


