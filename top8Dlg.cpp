// top8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "top8.h"
#include "top8Dlg.h"
#include "Input.h"
#include "Sensitivity.h"
#include "Optimizing.h"
#include "math.h"
#include "Huatu.h"
#include "DemDraw.h"
//#include "TOPMODEL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int sum,cutp=0,cutinput=0,cutr=0;
int NoWIClass,NoDisIncreament,NR;
int  DT,INFEX,NOWTIME,NSTEP;
float *WI,*PE,*R,RINT,DF,*EX,*SRZ,SR0,Sumae,
	*SUZ,*SD,SBAR,*Zbar,SZQ,*Qsur,*Qbot,Q0,TL,UZ,
	M,XK0,HF,DTH,*Distance,
	areaOfCatch,*AC,SUMAC,*AR,SUMAR,*CA,*ACH;
double lowDis;
double highDis;
double tempF1,tempF2,tempF3,tempF4;

 float SZM,T0,TD,chv,SRMAX,E;
 float *Q,*QOBS;

//extern CString m_msg1,m_msg2,m_msg3,m_msg4;
CString m_msg11,m_msg22,m_msg33,m_msg44;



void TOPmod();
void Input1();
void Init();
void Results();

//
////////////////////////////////////////////////////////////////////////////

//extern double  m_m11, m_m22,m_m33, m_m44, m_m55;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTop8Dlg dialog

CTop8Dlg::CTop8Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTop8Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTop8Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTop8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTop8Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTop8Dlg, CDialog)
	//{{AFX_MSG_MAP(CTop8Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Input, OnInput)
	ON_BN_CLICKED(IDC_Parameter, OnParameter)
	ON_BN_CLICKED(IDC_Optimizing, OnOptimizing)
	ON_BN_CLICKED(IDC_Draw, OnDraw)
	ON_BN_CLICKED(IDC_DemDraw, OnDemDraw)
	ON_BN_CLICKED(IDC_BUTTONwatertable, OnBUTTONwatertable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTop8Dlg message handlers

BOOL CTop8Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTop8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTop8Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTop8Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTop8Dlg::OnInput() 
{// TODO: Add your control notification handler code here
  Input dlg;
  dlg.DoModal();
}

void CTop8Dlg::OnParameter() 
{
	// TODO: Add your control notification handler code here
	Sensitivity dlgSensi;
	dlgSensi.DoModal();
}

void CTop8Dlg::OnOK() 
{
	// TODO: Add extra validation here
   /// MessageBox(m_msg4);
	//CDialog::OnOK();
	      if(cutinput==0)
               return;	
	//Input1();
      
///////////////////////////////////////		
	SR0=0.002;
    SBAR=0.05;
/*	
   SZM=0.164496;
    TD=3.58;
    T0=-3;
    SRMAX=0.02914;
	chv=2848;

    	
	SZM=m_m11; 
    T0=m_m22;
    SRMAX=m_m33;
    chv=m_m44;
    TD=m_m55;*/
      ////////////////////////////////	
	Init(); //初始化
       

			for(int i = 0; i < NSTEP; i++)
		{	
			NOWTIME = i;
			TOPmod();		//在每个时间上全流域应用模型
			}

		Results();
 //////////////



	FILE *fpmain;
	fpmain= fopen(m_msg44,"w");

    for(i=0;i<NSTEP;i++)
    fprintf(fpmain,"%f	%f	%f	%f\n",R[i],QOBS[i],Q[i],Zbar[i]);

    fclose(fpmain);
	MessageBox("结果已保存到:  " + m_msg44);
	cutr=1;
	return ;
}


void CTop8Dlg::OnOptimizing() 
{
	// TODO: Add your control notification handler code here
	 Optimizing dlg;
     dlg.DoModal();
}

void TOPmod()
{
	int irof,i,Ihour,In,Ihrof;	//irof,Ihour,Ihrof的意义到现在还不明确
	float Rex,Cumf,ACmax,Sump,Sumq,SumQb,SumQuz,SumEX,
		Qof,Quz,Qb,Qout,EP,P,Acm,Ea,Sae,Of,ACF;
	irof=0;
	Cumf = ACmax = Sump =  Sumq = 0.0;
	Sumae = 0;
	SumQuz = SumQb =  SumEX = 0;
	Qof = 0;
	Quz = 0;
//	if(NOWTIME = 85)AfxMessageBox("!");

	for(i = 0; i < NoWIClass; i++)		//开始每个类
	{
		Rex = 0;
		
		EP = PE[NOWTIME];
		P = R[NOWTIME] ;
		Sump += P;
	/*	
		if(INFEX ==1 && P>0)//计算每个时间步长内的超渗产流情况
		{
		RINT = P/DT;
		ExpinF(irof,i,RINT,DF,Cumf);//超渗产流所使用的是GREEN-AMPT模型
		Rex = P-DF;				//超渗产出水流
		P = P-Rex;				//P是地表控制的渗透作用剩下的雨水
		if(irof == 1)
			Ihrof += 1;
		else 
			Rex=0;
		irof=0;
		Cumf=0;
		}				//超渗产流计算完毕

*/
		Acm=0.0;
		                //在每个wetindex上循环
		UZ = 0;
        EX[i] = 0; //EX是该处饱和渗出水量
		
	
		SRZ[i] -= P;						
		//SRZ是当前点的root zone deficit
/*		if(P>0)
		{
			printf("P:%f\n",P);
			printf("SRZ[%d]:%f\n",i,SRZ[i]);
			getchar();
		}*/
		if(SRZ[i] < 0 )
		{
		SUZ[i] -= SRZ[i];
							//SUZ是当前点的不饱和带的储水量
							//unsaturated zone storage
		SRZ[i] = 0;	//总是ROOT ZONE先饱和
		}
		SD[i] = SBAR + SZM*(TL-WI[i]);
											//SD是当前点的排水赤字
		                                   //"local drainage deficit"
		                                   //WI 是当前湿润指数
										   //TL 是平均湿润指数，
										   //全流域平均得到
										   //这是TOPMODEL的主要方程
		if(SD[i] < 0) 
			SD[i] = 0; 	//SD不小于0
		if(SUZ[i] > SD[i])
		{
		EX[i] = SUZ[i] - SD[i];
								//蓄满产流
		SUZ[i] = SD[i];	
								//产流后不饱和层的含水量与SD相等
								//此即意味着SD是不饱和层的含水量下限
		}
		//从以上代码可知，模型分两层，一个是root zone，一个是unstaturated zone
		//root zone 在unstaturated zone 之上，前者的水总是要先渗向后者
		//当unstaturated zone饱和后（即大于SD时）则向地下水层渗透
		if(SD[i] > 0)				//SD大于0说明地下水没有
		{									//漫出
		UZ = SUZ[i] / (SD[i] * TD*  DT);
								//TD是滞时，DT是时间步长
		if(UZ > SUZ[i])
			UZ = SUZ[i];
		SUZ[i] -= UZ;
		if(SUZ[i] < 0.0000001)
			SUZ[i] = 0;
		Quz += UZ * AC[i] ;											
		}
					//QUZ最后参与了SBAR（流域平均缺水度）的计算
					//是从不饱和层排向地下水的水量
		Ea=0;
		if(EP>0)							//从这里开始计算root zone的蒸散发
		{
		Ea = EP * ( 1 - SRZ[i] / SRMAX);
									//SRMAX是root zone的最大持水量
		if(Ea > SRMAX - SRZ[i])
			Ea = SRMAX - SRZ[i];
						//Ea表示root zone的蒸散发
						//它的上限是该层有的水与最大储水量之差
		SRZ[i] += Ea;		//蒸散发失水算入根系层赤字
		}
		Sumae  += Ea * AC[i] ;
		Sae += Ea;							//Sae之前没有定义，不明确含义
		//饱和面上的产流
	
		Ihour=0;
		Of = 0;
		if(i > 0 && EX[i] > 0)		//统计该点作为饱和面的时间；
		{							//并且把饱和面产流算入Qof中
		Ihour += 1;					//原模型计算时考虑了各个ln（a/tanb）
		Of = AC[i] * ( EX[i] + EX[i - 1])/2;
		Acm += AC[i];
		SumEX += EX[i] / sum;
		}
		else 
			if(i > 0 && EX[ i - 1] > 0)
		{
			ACF = AC[i] * EX[i-1]/(EX[i-1] - EX[i]);
			Of = ACF * EX[i - 1] / 2;
			Acm += ACF;
		}
/*		if(Of != 0)
		{
			printf("Of:%f\n",Of);
			getchar();
		}*/
		Qof += Of;					//全饱和区出流
		CA[NOWTIME] = Acm;
		if(Acm > ACmax)ACmax = Acm;
		
	}//在所有类别上循环结束         ////////////////////////////////....
		
		
		Qb = SZQ *(float) exp( - SBAR / SZM ) ;
		
		SBAR = SBAR - Quz + Qb ;
        Zbar[NOWTIME] = SBAR;

		Qout = Qb + Qof;
		Sumq = Sumq + Qout;
		for(i = 0;i <NR; i++)
		{
		In = i + NOWTIME ;//把汇流时间转化为第n个时间步长		
		if(In < NSTEP)
			Q[In] += Qout * AR[i] ;	
//		    Qsur[In] += Qof * AR[i] ;
//			Qbot[In] += Qb * AR[i] ;
		    
		}
//		    Qsur[NOWTIME] = Qof ;
//			Qbot[NOWTIME] = Qb ;
//			Q[NOWTIME] = Qout ;
}

////////////////////////////////////////////////////////////////////
/////////////////  	Input		SubFunction	///////////////////////
///////////////////////////////////////////////////////////////////
//该函数读入了所有文件数据，并且开辟了所有数组
void Input1()
{
//	printf("TopInput\n");
	FILE *fp;
	char temp[50];
	int i,j;

	
	float tarea;
	fp = fopen(m_msg11,"r");//calib.txt
	if(!fp)
		printf("calib error");

    fscanf(fp,"%d %d",&NSTEP,&DT);
	
	
	Q = new float [NSTEP];
    Qsur = new float [NSTEP];
	Qbot = new float [NSTEP];
    Zbar = new float [NSTEP];

	R = new float [NSTEP];
	PE = new float [NSTEP];
	QOBS = new float [NSTEP];
	CA = new float [NSTEP];
	for(i = 0;i < NSTEP ;i ++)
	{
		fscanf(fp,"%f %f %f",&R[i],&PE[i],&QOBS[i] );//读降水 蒸散发 流量	
	}
	fclose(fp);
	fp=fopen(m_msg22,"r");
	if(!fp)
		printf("wet error");
		
	 fscanf(fp,"%d %f",&NoWIClass,&areaOfCatch);
	
		WI = new float [NoWIClass];	
		AC = new float [NoWIClass];
		for(i = 0; i < NoWIClass; i++)
			{
			fscanf(fp,"%f %f",&AC[i] ,&WI[i]);
			
			}
		fclose(fp);	
									//读WI完毕
		SUZ = new float [NoWIClass];
		SRZ = new float [NoWIClass];
		EX = new float [NoWIClass];
		SD = new float [NoWIClass];
	
		tarea = 0;
		for(i = 0; i < NoWIClass; i++)
			tarea += AC[i];			//总流域面积
		TL = 0;
		AC[0] = AC[0] / tarea;
		SUMAC = AC[0];
		for(i = 1; i < NoWIClass; i++)
		{
			AC[i] = AC[i] / tarea;
			SUMAC = SUMAC + AC[i];
			TL = TL + AC[i] * (WI[i] + WI[i - 1] / 2);
		}
			//算得平均地形指数
			//AC已经为百分比


		Q0=QOBS[0];
/*
		fp = fopen("params.txt","r");	//读参数
		if(!fp)
		printf("para error");
		
		fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f",&SZM,&T0 ,&TD,&SRMAX,&Q0,&SR0,&INFEX,&XK0, &HF ,&DTH,&chv);
	
		fclose(fp);
*/
	   fp = fopen(m_msg33,"r");//读等流时线
		if(!fp)
		printf("Distance error");
		
		fscanf(fp,"%d",&NoDisIncreament);
		
		Distance = new float[NoDisIncreament];		
		ACH = new float[NoDisIncreament];
		for(i = 0; i < NoDisIncreament; i++)
		{
		fscanf(fp,"%f %f",&ACH[i],&Distance[i]);
		
		}
		fclose(fp);//读结束

 
}
///////////////////////////////////////////////////////////////////
/////////////////  	Init		SubFunction	///////////////////////
///////////////////////////////////////////////////////////////////
void Init()
{
//		printf("TopInit\n");
		//Q的初始化。跟原模型不同，没有子流域。没有集中汇流。
		//在第一个TD之内一定会有水流到出水点，所以Q不再初始化。	
		//考虑到Q0需要用于确定SBAR，保留Q0，以观后效
		float TODT,SUM;
		float chvdt,A1,A2,*TCH;
		int i,j;
		TODT = T0 + (float)log(DT) ;
		SZQ =(float) exp(TODT - TL)  ;
		for(i = 0; i < NSTEP; i++)       //Q初始化
		{
					Q[i] = 0;
					Qsur[i] = 0;
					Qbot[i] = 0;
		}
		for(i = 0; i < NoWIClass; i++)
			
			{
				SUZ[i] = 0;
				SRZ[i] = SR0;
			}	
			SBAR = -SZM * log( Q0 / SZQ) ;

////////////////////////////////////////////////////////////////		
		chvdt = chv * DT;
		
		TCH = new float [NoDisIncreament];
		for(i = 0; i < NoDisIncreament; i++)
			TCH[i] = Distance[i] / chvdt;
		NR = int(TCH[NoDisIncreament - 1]);
		if(NR < TCH[NoDisIncreament - 1])
			NR = NR + 1;					//计算循环次数
		AR = new float [NR+1];
		//AR[0] = 0;
		for(i = 0;i <NR; i++)				//开始转化距离/面积为
											//时滞直方图
		{   if(i+1>TCH[NoDisIncreament - 1])
		        AR[i]=1;
		    else
			  for( j = 1; j < NoDisIncreament; j++ )
				if(i <= TCH[j])
				{
				AR[i] = ACH[j-1] + 
				( ACH[j] - ACH[j-1] )*
				( i+1 - TCH[j-1] ) / (TCH[j] - TCH [j - 1]);
				break;
				}
		}									
										//AR是比某时间小的区域的
										//累积百分比
									
		A1 = AR[0] ;
		SUMAR = AR [0];
		AR[0] *= areaOfCatch;
		for( i = 1; i <= NR; i++)
		{
			A2 = AR [i];
			AR[i] = A2 - A1;
			A1 = A2;
			SUMAR += AR[i];
//			AR[i] *= areaOfCatch;
		}								//算每个小时汇流面积
////////////////////////////////////////////////////////////////////
			SUM = 0;
		for( i = 0; i < NR; i++)
		{
			SUM += AR[i];
			Q[i] += Q0 * (1 - SUM); 
            Qbot[i] = Q[i];
			//第i时间汇到出水点的，是此面积之上的面积的汇水
		}

}

////////////////////////////////////////////////////////////////////
/////////////////  	Results		SubFunction	///////////////////////
///////////////////////////////////////////////////////////////////
void Results()
{
//	printf("TopRslt\n");
	double SumQ,SsQ,QBAR,VARQ,VARE;
	tempF1 = tempF2 = tempF3 = tempF4 = SumQ = SsQ = 0;
	int i,nLowDis,nHighDis;
//	FILE *fp;
	for(i = 0;i < NSTEP;i++)
	{
	SumQ += QOBS[i]; 
	SsQ += QOBS[i]*QOBS[i];
	tempF1 += (Q[i] - QOBS[i])*(Q[i] - QOBS[i]);
	tempF2 += fabs(Q[i] - QOBS[i]);	
	}
	
	QBAR = SumQ / NSTEP;	//平均流量
	VARQ = (SsQ / NSTEP - QBAR*QBAR);
	VARE = tempF1 / NSTEP;
	E = 1 - VARE / VARQ ;	//nash系数 
/*	

	fp = fopen("Total.txt","w"); 
	if(!fp)
		printf("Total error");
//	fprintf(fp,"Objective function values\n");
//	fprintf(fp,"F1:%f\nF2:%f\nMean Obs Q:%f\nNash Index:%f\n",
//		tempF1,tempF2,QBAR,E);
	for(i=0;i<NSTEP;i++)
	fprintf(fp,"%10.7f	%10.7f	%10.7f	%10.7f	%10.7f	%10.7f\n",
		R[i],QOBS[i],Q[i],Qsur[i],Qbot[i],Zbar[i]);
	fclose(fp);
	
	
////////////////////////////四个目标函数//////////////////////////
	tempF1 = tempF2 = tempF3 = tempF4 = 0;
	nLowDis = nHighDis = 0;
	for(i = 0;i < NSTEP; i++)
	{
		
		tempF1 += fabs( Q[i] - QOBS[i]);
		tempF2 += (Q[i] - QOBS[i])*(Q[i] - QOBS[i]);
		if(QOBS[i] <= lowDis) 
		{
			nLowDis++;
			tempF3 += (Q[i] - QOBS[i]) * (Q[i] - QOBS[i]);
		}
		if(QOBS[i] >= highDis)
		{
			nHighDis++;
			tempF4 += (Q[i] - QOBS[i]) * (Q[i] - QOBS[i]);
		}
		if(tempF1 < 0 || tempF2 < 0 || tempF3 < 0 || tempF4 < 0)
		{
	//		printf("F<0");
	//		getchar();
			tempF1 = tempF2 = tempF3 = tempF4 = 10000;
		}
	}
	tempF3 = sqrt(tempF3) / nLowDis;
	tempF4 = sqrt(tempF4) / nHighDis;
////////////目标函数计算完毕//////////////////////////////////////
	fp=fopen("Q.txt","w");				//记录最后得到的流量
	if(!fp)printf("Q error\n");
	for(i=0;i<NSTEP;i++)
	fprintf(fp,"%f\n",Q[i]);
	fclose(fp);
*/
}

void CTop8Dlg::OnDraw() 
{
	// TODO: Add your control notification handler code here
	Huatu dlg;
	dlg.DoModal();
}

void CTop8Dlg::OnDemDraw() 
{
	// TODO: Add your control notification handler code here
	DemDraw dlg;
	dlg.DoModal();
}

void CTop8Dlg::OnBUTTONwatertable() 
{
	// TODO: Add your control notification handler code here
	DemDraw dlg;
	dlg.DoModal();
}
