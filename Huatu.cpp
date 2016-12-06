// Huatu.cpp : implementation file
//

#include "stdafx.h"
#include "top8.h"
#include "Huatu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////
extern CString m_msg44;
float aa[2000],b[2000];
float dd,cc;
extern int cutp,cutr;
////////////////////////////////////////////
// Huatu dialog


Huatu::Huatu(CWnd* pParent /*=NULL*/)
	: CDialog(Huatu::IDD, pParent)
{
	//{{AFX_DATA_INIT(Huatu)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Huatu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Huatu)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Huatu, CDialog)
	//{{AFX_MSG_MAP(Huatu)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Huatu message handlers

void Huatu::OnOK() 
{
	// TODO: Add extra validation here
	if(cutp==0 || cutr==0)
	{
	MessageBox("没有参数和文件,返回主界面生成参并且输出结果文件");
	return;
	}
	 CWnd* p=GetDlgItem(IDC_huatukuang);   
      CDC* c=p->GetDC();   
      p->Invalidate();   
      p->UpdateWindow();   
      c->SelectStockObject(BLACK_BRUSH);  

//////////////////////////////////////
   c->SetViewportOrg(35,300);
   c->SetWindowOrg(0,0);
   c->SetWindowExt(1000,-1000);

   c->MoveTo(0,-250);
   c->LineTo(0,0);
   c->LineTo(860,0);
//////////画枪头/////////////
   c->MoveTo(-4,-240);
   c->LineTo(0,-253);
   c->LineTo(4,-240);
   c->MoveTo(852,-4);
   c->LineTo(860,0);
   c->LineTo(852,4);     
//////////////////////////////
   int x,y;
   for(x=50;x<250;x=x+50)
   {
   c->MoveTo(0,-x);
   c->LineTo(-5,-x);
   }
   for(y=100;y<860;y=y+100)
   {
   c->MoveTo(y,0);
   c->LineTo(y,5);
   }
	  if(m_msg44=="") return;
	FILE *fp;
	int i=0;
	fp = fopen(m_msg44,"r");//calib.txt
	if(!fp)
	{
    MessageBox("calib error");
	return;
	}
	rewind(fp);
	  	while(!feof(fp))
	{
		fscanf(fp,"%f %f %f %f",&cc,&aa[i],&b[i],&dd );//读降水 蒸散发 流量	
	    i++;
	}
	fclose(fp);

    CPen pen;
	float j=0;
	int a;
	pen.CreatePen(PS_SOLID,1,RGB(85,90,204));
	CPen *pOldPen=c->SelectObject(&pen);
	c->MoveTo(100,-270);
    c->LineTo(130,-270);
	for(a=0;a<=i-1;a++)
	{
	c->MoveTo(j,-aa[a]*4000);
	j=j+0.75;
	c->LineTo(j,-aa[a+1]*4000);
  	}  
	c->SelectObject(pOldPen);
	pen.DeleteObject();
	j=0;
	
pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen1=c->SelectObject(&pen);
	c->MoveTo(350,-270);
    c->LineTo(380,-270);
	for(a=0;a<=i-1;a++)
	{
	c->MoveTo(j,-b[a]*4000);
	j=j+0.75;
	c->LineTo(j,-b[a+1]*4000);
    } 
	c->SelectObject(pOldPen1);
	pen.DeleteObject();
	int text,jj;
	double ii=9.32;
	CString str,strz;
	for(text=0;text<j;text=text+100)
	{
	  str.Format("%d",text*4/3);
	  c->TextOut(text-8,5,str);
	}
	for(jj=50;jj<250;jj=jj+50)
	{
	   strz.Format("%2.2f",ii/100);
	   c->TextOut(-40,-jj-10,strz);
       ii=ii+9.32;
	}
    c->TextOut(150,-280,"Obseved Flows (mm)");
    c->TextOut(400,-280,"Simulated Flows (mm)");
    p->ReleaseDC(c);  
}

/*
void Huatu::OnButton1() 
{
	// TODO: Add your control notification handler code here
	 CString   StrFilter1="降雨数据(*.txt)|*.txt|所有文件(*.*)|*.*||";
	  CFileDialog  Dlg1(TRUE,NULL,NULL,NULL,StrFilter1,this);	
	  if(Dlg1.DoModal()==IDOK)
	  {
	  m_msg44=Dlg1.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.

	  }
	  else return;
	  cutr=1;
}*/

void Huatu::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    Huatu::OnOK();
	// Do not call CDialog::OnPaint() for painting messages
}
