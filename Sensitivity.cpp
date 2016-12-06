// Sensitivity.cpp : implementation file
//

#include "stdafx.h"
#include "top8.h"
#include "Sensitivity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern float SZM,TD,T0,chv,SR0,E,SBAR,SRMAX;
extern int NSTEP,NOWTIME;
extern void TOPmod();
extern void Input1();
extern void Init();
extern void Results();
/////////////////////////////////////////////////////////////////////////////
// Sensitivity dialog

CString tt;//////////////
Sensitivity::Sensitivity(CWnd* pParent /*=NULL*/)
	: CDialog(Sensitivity::IDD, pParent)
{ 
	//{{AFX_DATA_INIT(Sensitivity)

		 
   
	m_S_SZM = SZM;
    m_S_SZMMIN = 0.01;
	m_S_SZMMAX = 0.05;
	m_S_T0 = T0;
	m_S_T0MIN = 1;
	m_S_T0MAX = 5;
	m_S_TD = TD;
	m_S_TDMIN = 2;
	m_S_TDMAX = 50;
	m_S_SR = SRMAX;
	m_S_SRMIN = 0.01;
	m_S_SRMAX = 0.05;
	m_S_CHV = chv;
	m_S_CHVMIN = 100.0;
	m_S_CHVMAX = 3600;
	m_S_E = E;
	//}}AFX_DATA_INIT
   tt.Format("%.9f",SZM);
   m_S_SZM =atof(tt);
   tt.Format("%.9f",T0);
   m_S_T0 =atof(tt);	
   tt.Format("%.9f",TD);
   m_S_TD =atof(tt);
   tt.Format("%.9f",SRMAX);
   m_S_SR =atof(tt);
   tt.Format("%.9f",chv);
   m_S_CHV =atof(tt);
   tt.Format("%.9f",E);
   m_S_E=atof(tt);
}


void Sensitivity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Sensitivity)
	DDX_Text(pDX, IDC_EDIT1, m_S_SZM);
	DDX_Text(pDX, IDC_EDIT2, m_S_SZMMIN);
	DDX_Text(pDX, IDC_EDIT3, m_S_SZMMAX);
	DDX_Text(pDX, IDC_S_T0, m_S_T0);
	DDX_Text(pDX, IDC_S_T0MIN, m_S_T0MIN);
	DDX_Text(pDX, IDC_S_T0MAX, m_S_T0MAX);
	DDX_Text(pDX, IDC_S_TD, m_S_TD);
	DDX_Text(pDX, IDC_S_TDMIN, m_S_TDMIN);
	DDX_Text(pDX, IDC_S_TDMAX, m_S_TDMAX);
	DDX_Text(pDX, IDC_S_SR, m_S_SR);
	DDX_Text(pDX, IDC_S_SR_MIN, m_S_SRMIN);
	DDX_Text(pDX, IDC_SR_MAX, m_S_SRMAX);
	DDX_Text(pDX, IDC_S_CHV, m_S_CHV);
	DDX_Text(pDX, IDC_S_CHVMIN, m_S_CHVMIN);
	DDX_Text(pDX, IDC_S_CHVMAX, m_S_CHVMAX);
	DDX_Text(pDX, IDC_S_E, m_S_E);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Sensitivity, CDialog)
	//{{AFX_MSG_MAP(Sensitivity)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_S_T0, OnChangeST0)
	ON_EN_CHANGE(IDC_S_T0MIN, OnChangeST0min)
	ON_EN_CHANGE(IDC_S_T0MAX, OnChangeST0max)
	ON_EN_CHANGE(IDC_S_TD, OnChangeSTd)
	ON_EN_CHANGE(IDC_S_TDMIN, OnChangeSTdmin)
	ON_EN_CHANGE(IDC_S_TDMAX, OnChangeSTdmax)
	ON_EN_CHANGE(IDC_S_SR, OnChangeSSr)
	ON_EN_CHANGE(IDC_S_SR_MIN, OnChangeSSrMin)
	ON_EN_CHANGE(IDC_SR_MAX, OnChangeSrMax)
	ON_EN_CHANGE(IDC_S_CHV, OnChangeSChv)
	ON_EN_CHANGE(IDC_S_CHVMIN, OnChangeSChvmin)
	ON_EN_CHANGE(IDC_S_CHVMAX, OnChangeSChvmax)
	ON_BN_CLICKED(Sensitivityanalysis, OnSensitivityanalysis)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonT0)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonTD)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonSRMAX)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonchv)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonOutputPara)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Sensitivity message handlers

void Sensitivity::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
   UpdateData();
   SZM=m_S_SZM;
}

void Sensitivity::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeST0() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
	 T0=m_S_T0;
}

void Sensitivity::OnChangeST0min() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeST0max() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeSTd() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
	 TD=m_S_TD;
}

void Sensitivity::OnChangeSTdmin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeSTdmax() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeSSr() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
	 SRMAX=m_S_SR;
}

void Sensitivity::OnChangeSSrMin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeSrMax() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeSChv() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
	 chv=m_S_CHV;
}

void Sensitivity::OnChangeSChvmin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnChangeSChvmax() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	 UpdateData();
}

void Sensitivity::OnSensitivityanalysis() 
{
	// TODO: Add your control notification handler code here
CString tt9;
  // double SRZinit=0.002;
             double Emax=E;
	       for(double j=m_S_SZMMIN;j<=m_S_SZMMAX;j=j+(m_S_SZMMAX-m_S_SZMMIN)/1000.0)
			 {
			      SZM=j; /////////  注意， 这是原来少的一行程序代码
	             
				  SR0=0.002;
                  SBAR=0.05;

			   	Init(); //初始化 *SRZ=SR0;
             
				for(int i = 0; i <NSTEP; i++)
				{	
				NOWTIME = i;
				TOPmod();		//在每个时间上全流域应用模型
				}

				Results();


					if(E>Emax) 
				{
				 Emax=E;
				 m_S_SZM=SZM;
				}
			 }
              
	          E=Emax;
              m_S_E=E;
			/////////////////////////////////
			tt9.Format("%.9f",m_S_E);
			m_S_E=atof(tt9);
			/////////////////////////////////
            SZM=m_S_SZM;
			///////////////////////////////
		    tt9.Format("%.9f",m_S_SZM);
			m_S_SZM=atof(tt9);
			//////////////////////////////
            UpdateData(FALSE);
			MessageBox("参数SZM分析结束");
	
}

void Sensitivity::OnButtonT0() 
{
	CString tt9;
	// TODO: Add your control notification handler code here
	  double Emax=E;
	       for(double j=m_S_T0MIN;j<=m_S_T0MAX;j=j+(m_S_T0MAX-m_S_T0MIN)/1000.0)
			 {
			     T0=j;
	             SR0=0.002;
                  SBAR=0.05;

			   	Init(); //初始化 *SRZ=SR0;
             
				for(int i = 0; i <NSTEP; i++)
				{	
				NOWTIME = i;
				TOPmod();		//在每个时间上全流域应用模型
				}

				Results();


					if(E>Emax) 
				{
				 Emax=E;
				 m_S_T0=T0;
				}
			 }
              
	          E=Emax;
			  m_S_E=E;
			  tt9.Format("%.9f",m_S_E);
			 m_S_E=atof(tt9);
             T0=m_S_T0;
			  tt9.Format("%.9f",m_S_T0);
			 m_S_T0=atof(tt9);
            UpdateData(FALSE);

          MessageBox("参数T0分析结束");


}

void Sensitivity::OnButtonTD() 
{
	// TODO: Add your control notification handler code here
	CString tt9;
          	double Emax=E;
	       for(double j=m_S_TDMIN;j<=m_S_TDMAX;j=j+(m_S_TDMAX-m_S_TDMIN)/1000.0)
			 {
			      TD=j;
	             SR0=0.002;
                  SBAR=0.05;

			   	Init(); //初始化 *SRZ=SR0;
             
				for(int i = 0; i <NSTEP; i++)
				{	
				NOWTIME = i;
				TOPmod();		//在每个时间上全流域应用模型
				}

				Results();


					if(E>Emax) 
				{
				 Emax=E;
				 m_S_TD=TD;
				}
			 }
              
	          E=Emax;
			  m_S_E=E;
			  tt9.Format("%.9f",m_S_E);
			 m_S_E=atof(tt9);
             TD=m_S_TD;
			 tt9.Format("%.9f",m_S_TD);
			 m_S_TD=atof(tt9);
            UpdateData(FALSE);
          MessageBox("参数TD分析结束");

}

void Sensitivity::OnButtonSRMAX() 
{
	// TODO: Add your control notification handler code here
	CString tt9;
	         double Emax=E;
	       for(double j=m_S_SRMIN;j<=m_S_SRMAX;j=j+(m_S_SRMAX-m_S_SRMIN)/1000.0)
			 {
			      SRMAX=j;
	             SR0=0.002;
                  SBAR=0.05;

			   	Init(); //初始化 *SRZ=SR0;
             
				for(int i = 0; i <NSTEP; i++)
				{	
				NOWTIME = i;
				TOPmod();		//在每个时间上全流域应用模型
				}

				Results();


					if(E>Emax) 
				{
				 Emax=E;
				 m_S_SR=SRMAX;
				}
			 }
              
	          E=Emax;
			  m_S_E=E;
			  tt9.Format("%.9f",m_S_E);
			 m_S_E=atof(tt9);
             SRMAX=m_S_SR;
			  tt9.Format("%.9f",m_S_SR);
			 m_S_SR=atof(tt9);
            UpdateData(FALSE);
             MessageBox("参数SRMAX分析结束");
}

void Sensitivity::OnButtonchv() 
{
	// TODO: Add your control notification handler code here
	CString tt9;
		double Emax=E;
	       for(double j=m_S_CHVMIN;j<=m_S_CHVMAX;j=j+(m_S_CHVMAX-m_S_CHVMIN)/1000.0)
			 {
			      chv=j;
	             SR0=0.002;
                  SBAR=0.05;

			   	Init(); //初始化 *SRZ=SR0;
             
				for(int i = 0; i <NSTEP; i++)
				{	
				NOWTIME = i;
				TOPmod();		//在每个时间上全流域应用模型
				}

				Results();


					if(E>Emax) 
				{
				 Emax=E;
				 m_S_CHV=chv;
				}
			 }
              
	          E=Emax;
			  m_S_E=E;
             tt9.Format("%.9f",m_S_E);
			 m_S_E=atof(tt9);
             chv=m_S_CHV;
			  tt9.Format("%.9f",m_S_CHV);
			 m_S_CHV=atof(tt9);
            UpdateData(FALSE);
           MessageBox("参数CHV分析结束");
}

void Sensitivity::OnButtonOutputPara() 
{
	// TODO: Add your control notification handler code here
	 
	             SR0=0.002;
                  SBAR=0.05;

			   	Init(); //初始化 *SRZ=SR0;
             
				for(int i = 0; i <NSTEP; i++)
				{	
				NOWTIME = i;
				TOPmod();		//在每个时间上全流域应用模型
				}

				Results();
	
	FILE *fp;
	 fp= fopen("Parameter.txt","w");
	 fprintf(fp,"SZM	T0	TD	SRMAX	chv	Efficiency\n");
     fprintf(fp,"%f	%f	%f	%f	%f	%f\n",SZM,T0,TD,SRMAX,chv,E);
     fclose(fp);
	 MessageBox("结果已保存本程序所在目录下的Parameter.txt文件");
}
