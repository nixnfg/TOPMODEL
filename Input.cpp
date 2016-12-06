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
 //全局变量,传递文件地址
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
	HBITMAP m_hbmp;  //定义对象句柄
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
   	if(m_msg1=="")  {MessageBox("没有输入降雨量数据文件*.dat");return;	}
    if(m_msg2=="")  {MessageBox("没有输入DEM分类文件*.dem");return ;}
    if(m_msg3=="")  {MessageBox("没有输入等流时线文件*.dlx");return ;}
	if(m_msg4=="")  {MessageBox("没有输入计算结果文件名*.txt");return ;}
	  CFileFind finder;   //再次判断输入的三个数据文件是否存在
      BOOL bWorking1=finder.FindFile(m_msg1);
	  BOOL bWorking2=finder.FindFile(m_msg2);
      BOOL bWorking3=finder.FindFile(m_msg3);
      
      if(!bWorking1)  { AfxMessageBox("文件"+m_msg1+"不存在！"); return; } 
	  if(!bWorking2)  { AfxMessageBox("文件"+m_msg2+"不存在！"); return; } 
	  if(!bWorking3)  { AfxMessageBox("文件"+m_msg3+"不存在！"); return; } 

         Input1();

	CDialog::OnOK();
cutinput=1;
}

void Input::Onsave() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter="文本文档(*.txt)|*.txt|所有文件(*.*)|*.*||";
	CFileDialog  Dlg(FALSE,NULL,NULL,NULL,StrFilter,this);	
	if (Dlg.DoModal()==IDOK)
	{
    m_msg4=Dlg.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.
     
	m_msg44=m_msg4;
	//dlg0.m_msg44=m_msg4;
	UpdateData(FALSE);
	}
}

void Input::Onrain() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter1="降雨数据(*.dat)|*.dat|所有文件(*.*)|*.*||";
	CFileDialog  Dlg1(TRUE,NULL,NULL,NULL,StrFilter1,this);	
	if (Dlg1.DoModal()==IDOK)
	{
    m_msg1=Dlg1.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.
	m_msg11=m_msg1;
	//dlg0.m_msg11=m_msg1;
	UpdateData(FALSE);
	}
}

void Input::Ondlx() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter3="等流时线(*.dlx)|*.dlx|所有文件(*.*)|*.*||";
	CFileDialog  Dlg3(TRUE,NULL,NULL,NULL,StrFilter3,this);	
	if (Dlg3.DoModal()==IDOK)
	{
     m_msg3=Dlg3.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.
    m_msg33=m_msg3;
	 //dlg0.m_msg33=m_msg3;
	UpdateData(FALSE);
	}
}

void Input::Ondem() 
{
	// TODO: Add your control notification handler code here
	CString   StrFilter2="CLASS DEM(*.dem)|*.dem|所有文件(*.*)|*.*||";
    CFileDialog  Dlg2(TRUE,NULL,NULL,NULL,StrFilter2,this);	
    if (Dlg2.DoModal()==IDOK)
	{
    m_msg2=Dlg2.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.
    m_msg22=m_msg2;
	//dlg0.m_msg22=m_msg2;
	UpdateData(FALSE);
	}
}
