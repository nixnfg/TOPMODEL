// Input.cpp : implementation file
//

#include "stdafx.h"
#include "top8.h"
#include "top8Dlg.h"
#include "Input.h"

extern CString m_msg11,m_msg22,m_msg33,m_msg44;
extern CString path;
extern int cutinput;

//////////////////////////////////////////////////////////////
CString m_msg1,m_msg2,m_msg3,m_msg4; 
 //ȫ�ֱ���,�����ļ���ַ
//////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Input dialog
extern void Input1();

Input::Input(CWnd* pParent /*=NULL*/)
	: CDialog(Input::IDD, pParent)
{
	//{{AFX_DATA_INIT(Input)
	m_msg1 = _T("");
	m_msg2 = _T("");
	m_msg3 = _T("");
	m_msg4 = _T("");
	//}}AFX_DATA_INIT
     m_msg1=path+"\\Rain Fall.dat";
	 m_msg2=path+"\\Class Dem.dem";
     m_msg3=path+"\\Distance.dlx";
	 m_msg4=path+"\\result.txt";
	 m_msg11=m_msg1;
	 m_msg22=m_msg2;
     m_msg33=m_msg3;
     m_msg44=m_msg4;
}


void Input::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Input)
	DDX_Control(pDX, IDC_save, m_save);
	DDX_Control(pDX, IDC_rain, m_rain);
	DDX_Control(pDX, IDC_dlx, m_dlx);
	DDX_Control(pDX, IDC_dem, m_dem);
	DDX_Text(pDX, IDC_EDIT1, m_msg1);
	DDX_Text(pDX, IDC_EDIT2, m_msg2);
	DDX_Text(pDX, IDC_EDIT3, m_msg3);
	DDX_Text(pDX, IDC_EDIT4, m_msg4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Input, CDialog)
	//{{AFX_MSG_MAP(Input)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_save, Onsave)
	ON_BN_CLICKED(IDC_rain, Onrain)
	ON_BN_CLICKED(IDC_dlx, Ondlx)
	ON_BN_CLICKED(IDC_dem, Ondem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Input message handlers

void Input::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	HBITMAP m_hbmp;  //���������
	m_hbmp=::LoadBitmap(HINSTANCE(GetModuleHandle(0)),MAKEINTRESOURCE(IDB_BITMAP1));
	m_dem.SetBitmap(m_hbmp);
	//m_hbmp=::LoadBitmap(HINSTANCE(GetModuleHandle(0)),MAKEINTRESOURCE(IDB_BITMAP1));
	m_dlx.SetBitmap(m_hbmp);
	//m_hbmp=::LoadBitmap(HINSTANCE(GetModuleHandle(0)),MAKEINTRESOURCE(IDB_BITMAP1));
	m_rain.SetBitmap(m_hbmp);
    m_hbmp=::LoadBitmap(HINSTANCE(GetModuleHandle(0)),MAKEINTRESOURCE(IDB_BITMAP2));
    m_save.SetBitmap(m_hbmp);
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}


void Input::OnOK() 
{
	// TODO: Add extra validation here
cutinput=0;
   	if(m_msg1=="")  {MessageBox("û�����뽵���������ļ�*.dat");return;	}
    if(m_msg2=="")  {MessageBox("û������DEM�����ļ�*.dem");return ;}
    if(m_msg3=="")  {MessageBox("û���������ʱ���ļ�*.dlx");return ;}
	if(m_msg4=="")  {MessageBox("û������������ļ���*.txt");return ;}
	  CFileFind finder;   //�ٴ��ж���������������ļ��Ƿ����
      BOOL bWorking1=finder.FindFile(m_msg1);
	  BOOL bWorking2=finder.FindFile(m_msg2);
      BOOL bWorking3=finder.FindFile(m_msg3);
      
      if(!bWorking1)  { AfxMessageBox("�ļ�"+m_msg1+"�����ڣ�"); return; } 
	  if(!bWorking2)  { AfxMessageBox("�ļ�"+m_msg2+"�����ڣ�"); return; } 
	  if(!bWorking3)  { AfxMessageBox("�ļ�"+m_msg3+"�����ڣ�"); return; } 

         Input1();

	CDialog::OnOK();
cutinput=1;
}

void Input::Onsave() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter="�ı��ĵ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||";
	CFileDialog  Dlg(FALSE,NULL,NULL,NULL,StrFilter,this);	
	if (Dlg.DoModal()==IDOK)
	{
    m_msg4=Dlg.GetPathName();//��ֵ������ڴ����.˵��:Ҫ����ļ���,������"dlg.GetFileName()"��ʵ��.
     
	m_msg44=m_msg4;
	//dlg0.m_msg44=m_msg4;
	UpdateData(FALSE);
	}
}

void Input::Onrain() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter1="��������(*.dat)|*.dat|�����ļ�(*.*)|*.*||";
	CFileDialog  Dlg1(TRUE,NULL,NULL,NULL,StrFilter1,this);	
	if (Dlg1.DoModal()==IDOK)
	{
    m_msg1=Dlg1.GetPathName();//��ֵ������ڴ����.˵��:Ҫ����ļ���,������"dlg.GetFileName()"��ʵ��.
	m_msg11=m_msg1;
	//dlg0.m_msg11=m_msg1;
	UpdateData(FALSE);
	}
}

void Input::Ondlx() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter3="����ʱ��(*.dlx)|*.dlx|�����ļ�(*.*)|*.*||";
	CFileDialog  Dlg3(TRUE,NULL,NULL,NULL,StrFilter3,this);	
	if (Dlg3.DoModal()==IDOK)
	{
     m_msg3=Dlg3.GetPathName();//��ֵ������ڴ����.˵��:Ҫ����ļ���,������"dlg.GetFileName()"��ʵ��.
    m_msg33=m_msg3;
	 //dlg0.m_msg33=m_msg3;
	UpdateData(FALSE);
	}
}

void Input::Ondem() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter2="CLASS DEM(*.dem)|*.dem|�����ļ�(*.*)|*.*||";
    CFileDialog  Dlg2(TRUE,NULL,NULL,NULL,StrFilter2,this);	
    if (Dlg2.DoModal()==IDOK)
	{
    m_msg2=Dlg2.GetPathName();//��ֵ������ڴ����.˵��:Ҫ����ļ���,������"dlg.GetFileName()"��ʵ��.
    m_msg22=m_msg2;
	//dlg0.m_msg22=m_msg2;
	UpdateData(FALSE);
	}
}
