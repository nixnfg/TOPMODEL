// Optimizing.cpp : implementation file
//

#include "stdafx.h"
#include "top8.h"
//#include "top8Dlg.h"
#include "Optimizing.h"
//#include "TOPMODEL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern CString m_msg1,m_msg2,m_msg3,m_msg4;
//extern double  m_m11, m_m22,m_m33, m_m44, m_m55;
extern float SZM,TD,T0,chv,SR0,E,SBAR,SRMAX;
extern int NSTEP,NOWTIME,cutp;
extern void TOPmod();

extern void Init();
extern void Results();
/////////////////////////////////////////////////////////////////////////////
// Optimizing dialog


Optimizing::Optimizing(CWnd* pParent /*=NULL*/)
	: CDialog(Optimizing::IDD, pParent)
{
	//{{AFX_DATA_INIT(Optimizing)
	m_random = 100;
	m_OPI_CHV = 0.0;
	m_OPI_SRmax = 0.0;
	m_OPI_SZM = 0.0;
	m_OPI_TO = 0.0;
	m_OPI_TD = 0.0;
	m_OPI_Efficiency = 0.0;
	//}}AFX_DATA_INIT
}


void Optimizing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Optimizing)
	DDX_Text(pDX, IDC_Erandom, m_random);
	DDX_Text(pDX, IDC_OPI_CHV, m_OPI_CHV);
	DDX_Text(pDX, IDC_OPI_SRmax, m_OPI_SRmax);
	DDX_Text(pDX, IDC_OPI_SZM, m_OPI_SZM);
	DDX_Text(pDX, IDC_OPI_T0, m_OPI_TO);
	DDX_Text(pDX, IDC_OPI_TD, m_OPI_TD);
	DDX_Text(pDX, IDC_E_Efficiency, m_OPI_Efficiency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Optimizing, CDialog)
	//{{AFX_MSG_MAP(Optimizing)
	ON_EN_CHANGE(IDC_Erandom, OnChange_random)
	ON_BN_CLICKED(IDC_BUTTON2, On_Optimizing)
	ON_EN_CHANGE(IDC_E_Efficiency, OnChangeEEfficiency)
	ON_EN_CHANGE(IDC_OPI_SZM, OnChangeOpiSzm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Optimizing message handlers

void Optimizing::OnChange_random() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
   UpdateData();

	
}

void Optimizing::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

void Optimizing::On_Optimizing() 
{
	// TODO: Add your control notification handler code here
	//CTop8Dlg  dlg0;
	cutp=0;
    CString  tt;
	double Emax=-10;
	double SZMopti,TDopti,chvopti,T0opti,SRMAXopti;
//	int NOWTIME;

    srand( (unsigned)time( NULL ) );
	for(int m=0; m<m_random; m++)  
	{

			SZM=(0.05-0.01)*double(rand())/32767+0.01;
             TD=(50-2)*double(rand())/32767+2;
             T0=(5-1)*double(rand())/32767+1;
             SRMAX=(0.05-0.01)*double(rand())/32767+0.01;
			 chv=(3600-1700)*double(rand())/32767+1700;
 
                 // double SRZinit=0.002;
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
				 SZMopti=SZM;
				 TDopti=TD;
				 T0opti=T0;
				 SRMAXopti=SRMAX;
				 chvopti=chv;
				}
	}
             SZM=SZMopti;
             TD=TDopti;
             T0= T0opti;
             SRMAX=SRMAXopti;
			 chv= chvopti;
             E=Emax;
			
//////////////////////////////////////////////////			 
			 tt.Format("%.9f",Emax);
			 m_OPI_Efficiency=atof(tt);			 
			 tt.Format("%.9f",SZM);
			 m_OPI_SZM=atof(tt);
			 tt.Format("%.9f",T0);
			 m_OPI_TO=atof(tt);
			 tt.Format("%.9f",TD);
			 m_OPI_TD=atof(tt);
			 tt.Format("%.9f",chv);
			 m_OPI_CHV=atof(tt);
			 tt.Format("%.9f",SRMAX);
			 m_OPI_SRmax=atof(tt);
//	  m_OPI_Efficiency=Emax;
//    m_OPI_SZM=SZM; 
//    m_OPI_TO=T0;
//    m_OPI_SRmax=SRMAX;
//    m_OPI_CHV=chv;
//    m_OPI_TD=TD;

    UpdateData(FALSE);
    MessageBox("本次优化参数结束!");	
    cutp=1;
}

void Optimizing::OnChangeEEfficiency() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
     
	
}

void Optimizing::OnChangeOpiSzm() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
