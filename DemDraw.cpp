// DemDraw.cpp : implementation file
//

#include "stdafx.h"
#include "top8.h"
#include "DemDraw.h"
#include <math.h>
/*CString  m_msg;
unsigned short int color[1000][1000];
int ncol2,nrow2;
*/


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DemDraw dialog


extern float SZM,*Zbar,TL;
extern int NSTEP;

const int threshold=100;

CString  m_msg,ddd;
unsigned short int color[1000][1000],color1[1000][1000],colorlast[1000][1000][3];
int ncol2,nrow2;
int	yy=0,xx=0,bian=0;

short int **flowdir,**topindex;
int **larr;
double **dem,**dem1,**demtemp, **slop;
double nodata,csize;
int ncol,nrow;

double interval;
double TImean,TImin,TImax;
int MAX_DEPTH=50;//
int depth=0,depth2=0;//
double maximum=9998.0;//
static double Delta1[9]={0,0.001,0.00141,0.001,0.00141,0.001,0.00141,0.001,0.00141 }; 
static short int d1[9]={0,0, -1,  -1, -1, 0, 1, 1, 1};
static short int d2[9]={0,1, 1, 0, -1, -1, -1, 0, 1};
/*
int dd1[8],dd2[8];	//Offset pointers d1 and d2 			

int *d1 = dd1-1;
int *d2 = dd2-1;

void definedir()
{

d1[1]=0; d1[2]= -1; d1[3]= -1; d1[4]= -1; d1[5]=0; d1[6]=1; d1[7]=1; d1[8]=1;
d2[1]=1; d2[2]=1; d2[3]=0; d2[4]= -1; d2[5]= -1; d2[6]= -1; d2[7]=0; d2[8]=1;
}	
*/

DemDraw::DemDraw(CWnd* pParent /*=NULL*/)
	: CDialog(DemDraw::IDD, pParent)
{
	//{{AFX_DATA_INIT(DemDraw)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DemDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DemDraw)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DemDraw, CDialog)
	//{{AFX_MSG_MAP(DemDraw)
	ON_BN_CLICKED(IDC_Bopen, OnBopen)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_Color, OnSelchangeColor)
	ON_CBN_SELENDOK(IDC_Color, OnSelendokColor)
	ON_BN_CLICKED(IDC_BUTTON2, OnDEMfill)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonFlowdirection)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonArea)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonTopindex)
	ON_BN_CLICKED(IDC_BUTTON7, OnButtonWatertable)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonRivernet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DemDraw message handlers

void DemDraw::OnBopen() 
{
	ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	bian=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
		CString   StrFilter="文本文档(*.txt)|*.txt|所有文件(*.*)|*.*||";
	CFileDialog  Dlg(TRUE,NULL,NULL,NULL,StrFilter,this);	
	if (Dlg.DoModal()==IDOK)
	{
    m_msg=Dlg.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.
    UpdateData(FALSE);
	}
	   if(m_msg=="") return;
	 
	   
	   
	   	FILE *fp1;
  int i,j;
  //unsigned long total=0, total2;
 
 // double *arr1x, *arr1y, *arr1y2; 
 // double *arr2x, *arr2y, *arr2y2;  
  
   TImean=0;
 TImin=10000;
 TImax=0;
 
   char sss[120];

  fp1 = fopen(m_msg,"r");    ///////////////
  
       
       fscanf(fp1,"%s",sss);
       fscanf(fp1,"%d",&ncol);
	   fgets(sss,100,fp1);
       fscanf(fp1,"%s",sss);
       fscanf(fp1,"%d",&nrow);
	   fgets(sss,100,fp1);
       
	//   arr1x=new double[ncol*nrow+1];
        
	   for(i=1;i<=2;i++)
	   {
        fgets(sss,100,fp1);
	   }
        fscanf(fp1,"%s",sss);
       fscanf(fp1,"%lf",&csize);
	   fscanf(fp1,"%s",sss);
       fscanf(fp1,"%lf",&nodata);

      dem = new double *[ncol];
        dem[0]=new double[nrow*ncol];
		dem1 = new double *[ncol];
        dem1[0]=new double[nrow*ncol];

       for( i = 1; i < ncol; i++)
	   {
		   dem[i] = dem[i-1]+nrow;
		   dem1[i] = dem1[i-1]+nrow;
	   }

   

	    for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {
			   fscanf(fp1,"%lf",&dem[j][i]);
			   if(dem[j][i]!=nodata)
			   {
				  // total++;
				 //  arr1x[total]=temp;
                 //  TImean+=temp;
				   if(dem[j][i]<TImin) TImin=dem[j][i];
				  if(dem[j][i]>TImax) TImax=dem[j][i];

			   }

		   }
        //TImean/=(double)total;
		   interval=(TImax-TImin)/255;
       fclose(fp1);
	   ////////////////////////压缩dem数据,条件满足
	   nrow2=nrow;
	   ncol2=ncol;
	   int n=0,k=0,z=0; 
	    
         
 
if(ncol>770||nrow>577)
{     
	  if((ncol-770)>=(nrow-577)) 
		  n=ncol/770+1;
      else
		  n=nrow/577+1;	
	 
       for(int y=0;y<ncol/10*10;y+=n)
	   {   
		   int yyy=0;
	       for(int x=0;x<nrow/10*10;x+=n)
		   {
			   for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  dem1[yyy][xx]=dem1[yyy][xx]+dem[z][k];
					}
				
				}
        	dem1[yyy][xx]=dem1[yyy][xx]/(n*n);
	        yyy++;
			yy=yyy;	
			   }
    	xx++;
	   } 

	    for(i=0;i<xx;i++)
		   for(j=0;j<yy;j++)
		   {
              if(dem1[j][i]>0)
			  {
               color1[j][i]=(dem1[j][i]-TImin)/interval;
              }
           else 
			{
             color1[j][i]=255;
			}
           }
}
else
{

	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(dem[j][i]!=nodata)
			  {
               color[j][i]=(dem[j][i]-TImin)/interval;
              }
           else 
			{
             color[j][i]=255;
			}
           }
}
	   delete [] dem1[0];
     delete [] dem1;

/*////////////////////////////////////
	   double interval;
         interval=(TImax-TImin)/255;
    
	   
	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(dem[j][i]!=nodata)
			  {
               color[j][i]=(dem[j][i]-TImin)/interval;
              }
           else 
			{
             color[j][i]=255;
			}
           }
	  		   

	   

///////////////////////////////////////////////////////
int n,k,z; 
 
if(ncol2>770||nrow2>570)
{ 
	  if((ncol2-770)>=(nrow2-570)) 
		  n=ncol2/770+1;
      else
		  n=nrow2/570+1;	

       for(int y=0;y<nrow2;y+=n)
	   {   int yyy=0;
	       for(int x=0;x<ncol2;x+=n)
		   {
			   
	            for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  color1[xx][yy]=color1[xx][yy]+color[k][z];
					}
				}
        	color1[xx][yy]=color1[xx][yy]/(n*n);
	        yyy++;
			yy=yyy;
		   }
    	xx++;
	   } 
}
*/


   //MessageBox("数据读取完毕");
    DemDraw::OnOK();
}

void DemDraw::OnOK() 
{
	// TODO: Add extra validation here
	 CWnd* pp=GetDlgItem(IDC_dem); 
	  CDC* cc=pp->GetDC();  
	  //CBitmap *bitmap;
      pp->Invalidate();   
      pp->UpdateWindow();   
      cc->SelectStockObject(BLACK_BRUSH);
	  CDC MemDC;
	  CBitmap MemBitmap;
      MemDC.CreateCompatibleDC(NULL);
	  MemBitmap.CreateCompatibleBitmap(cc,770,577);
	  CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	  MemDC.FillSolidRect(0,0,770,577,RGB(255,255,255));
////////////////////////////////////  
int nx=0,ny=0;

cc->FillSolidRect(0,0,770,577,RGB(255,255,255));

///////////////////////////////////////
if(bian==0)
{
if(ncol2>770 || nrow2>577) 
{  
if(xx<577)   nx=(577-xx)/3;
if(yy<770)   ny=(770-yy)/2;
	 
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
	   {
	if(color1[y][x]!=255)
	MemDC.SetPixel(x,y,RGB(color1[y][x],color1[y][x],color1[y][x]));
		}
}

}
else
{
if(nrow2<577)   nx=(577-nrow2)/2;
if(ncol2<770)   ny=(770-nrow2)/2;
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
	      MemDC.SetPixel(y,x,RGB(color[y][x],color[y][x],color[y][x]));
	   }
}

}
}
else
{
if(ncol2>770 || nrow2>577) 
{  
if(xx<577)   nx=(577-xx)/3;
if(yy<770)   ny=(770-yy)/2;
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
	   {
	if(color1[y][x]!=255)
	MemDC.SetPixel(x,y,RGB(colorlast[y][x][1],colorlast[y][x][2],colorlast[y][x][3]));
	 }
}

}
else
{
if(nrow2<577)   nx=(577-nrow2)/2;
if(ncol2<770)   ny=(770-nrow2)/2;
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
	      MemDC.SetPixel(y,x,RGB(colorlast[y][x][1],colorlast[y][x][2],colorlast[y][x][3]));
	   }
}

}
}
   cc->BitBlt(ny,nx,770-ny,577-nx,&MemDC,0,0,SRCCOPY);
   MemBitmap.DeleteObject();
   MemDC.DeleteDC();
	//CDialog::OnOK();
}

void DemDraw::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
//	DemDraw::OnOK();
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL DemDraw::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("黑白图");
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("红色渐变");
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("绿色渐变");
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("蓝色渐变");
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("红色-绿色");
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("紫色->绿色");
	((CComboBox*)GetDlgItem(IDC_Color))->AddString("蓝色->黄色");
	((CComboBox*)GetDlgItem(IDC_Color))->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DemDraw::OnSelchangeColor() 
{
	// TODO: Add your control notification handler code here
	int index=((CComboBox*)GetDlgItem(IDC_Color))->GetCurSel();
switch(index)
{
case 0: bian=0;
	DemDraw::OnOK();
	break;
case 1:
	bian=1;
{
if(ncol2>770 || nrow2>577) 
{  
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
{
	if(color1[y][x]!=255)
	{
	colorlast[y][x][1]=color1[y][x];
	colorlast[y][x][2]=0;
	colorlast[y][x][3]=0;
	}
}
}
}
else
{
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
		 {
	colorlast[y][x][1]=color[y][x];
	colorlast[y][x][2]=0;
	colorlast[y][x][3]=0;
		 }
	   }
}
}
}
DemDraw::OnOK(); 
break;
case 2: 
	bian=2;
	if(ncol2>770 || nrow2>577) 
{  
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
{
	if(color1[y][x]!=255)
	{
	colorlast[y][x][1]=0;
	colorlast[y][x][2]=color1[y][x];
	colorlast[y][x][3]=0;
	}
}
}
}
else
{
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
		 {
	colorlast[y][x][1]=0;
	colorlast[y][x][2]=color[y][x];
	colorlast[y][x][3]=0;
		 }
	   }
}
}
DemDraw::OnOK();
break;
case 3: 
	bian=3;
	if(ncol2>770 || nrow2>577) 
{  
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
{
	if(color1[y][x]!=255)
	{
	colorlast[y][x][1]=0;
	colorlast[y][x][2]=0;
	colorlast[y][x][3]=color1[y][x];
	}
}
}
}
else
{
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
		 {
	colorlast[y][x][1]=0;
	colorlast[y][x][2]=0;
	colorlast[y][x][3]=color[y][x];
		 }
	   }
}
}
DemDraw::OnOK();
break;
case 4: 
	bian=4;
	if(ncol2>770 || nrow2>577) 
{  
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
{
	if(color1[y][x]!=255)
	{
	colorlast[y][x][1]=color1[y][x];
	colorlast[y][x][2]=255-color1[y][x];
	colorlast[y][x][3]=0;
	}
}
}
}
else
{
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
		 {
	colorlast[y][x][1]=color[y][x];
	colorlast[y][x][2]=255-color[y][x];
	colorlast[y][x][3]=0;
		 }
	   }
}
}
DemDraw::OnOK();
break;
case 5: 
	bian=5;
	if(ncol2>770 || nrow2>577) 
{  
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
{
	if(color1[y][x]!=255)
	{
	colorlast[y][x][1]=color1[y][x];
	colorlast[y][x][2]=255-color1[y][x];
	colorlast[y][x][3]=color1[y][x];
	}
}
}
}
else
{
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
		 {
	colorlast[y][x][1]=color[y][x];
	colorlast[y][x][2]=255-color[y][x];
	colorlast[y][x][3]=color[y][x];
		 }
	   }
}
}
DemDraw::OnOK();
break;
case 6: 
	bian=6;
	if(ncol2>770 || nrow2>577) 
{  
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
{
	if(color1[y][x]!=255)
	{
	colorlast[y][x][1]=255-color1[y][x];
	colorlast[y][x][2]=255-color1[y][x];
	colorlast[y][x][3]=color1[y][x];
	}
}
}
}
else
{
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
		 {
	colorlast[y][x][1]=255-color[y][x];
	colorlast[y][x][2]=255-color[y][x];
	colorlast[y][x][3]=color[y][x];
		 }
	   }
}
}

DemDraw::OnOK();
break;
}
}

void DemDraw::OnSelendokColor() 
{
	// TODO: Add your control notification handler code here
	//	DemDraw::OnOK();
}

void dry_upward_cell(int i,int j)
{  int k,in,jn;

	/* define directions */
	int    ny =nrow;
	int 	nx =ncol;
//definedir();
	depth++;
	if(depth<=MAX_DEPTH) 
	for(k=1; k<=8; k++)  
		{	
			

			in=i+d1[k];
	        jn=j+d2[k];
		    if((in>=0)&&(in<ny)&&(jn>=0)&&(jn<nx))
			if(demtemp[jn][in]==maximum)//这里有问题
			{     
				if(dem[jn][in]>=demtemp[j][i]+Delta1[k])       // 这里很容易出问题：Delta1[k]容易漏掉
				{	
					demtemp[jn][in]=dem[jn][in];
				   
					dry_upward_cell(in,jn);		
				}
			}
																	
		}
	
	
      depth--;


}



bool Next_Cell(int *R,int *C,int i,int *dR,int *dC,int *fR,int *fC)
{   int     ny=nrow;
	int 	 nx=ncol;
	*R=*R+dR[i];
	*C=*C+dC[i];
	if((*R<0)||(*C<0)||(*R>=ny)||(*C>=nx))
	{	*R=*R+fR[i];
	    *C=*C+fC[i];	
       if((*R<0)||(*C<0)||(*R>=ny)||(*C>=nx))
	   return false;
	}

	return true;
}

void DemDraw::OnDEMfill() 
{
	// TODO: Add your control notification handler code here

	

      demtemp = new double *[ncol];
        demtemp[0]=new double[nrow*ncol];

       for(int i = 1; i<ncol; i++)
        demtemp[i] = demtemp[i-1]+nrow;


//definedir();


    int    ny =nrow;
	int 	nx =ncol;
      int j;  
	
//  the following is the step 1
	for(i=0; i<ny; i++)
		for(j=0; j<nx; j++)
		
					demtemp[j][i]=dem[j][i];
			
	
/*


	//  the following is the step 2.1
    //count=0.0;
//	count2=0.0;

	for(i=0; i<ny; i++)
	{        
		    dry_upward_cell(i,0);	
			dry_upward_cell(i,nx-1);
		}
	
	for(j=1; j<nx-1; j++)
	{      
			dry_upward_cell(0,j);	
			dry_upward_cell(ny-1,j);
		}  

int R0[9],C0[9],dR[9],dC[9],fR[9],fC[9];

	R0[1]=0;R0[2]=ny-1;R0[3]=0;R0[4]=ny-1;R0[5]=0;R0[6]=ny-1;R0[7]=0;R0[8]=ny-1;
	C0[1]=0;C0[2]=nx-1;C0[3]=nx-1;C0[4]=0;C0[5]=nx-1;C0[6]=0;C0[7]=0;C0[8]=nx-1;
	dR[1]=0;dR[2]=0;dR[3]=1;dR[4]=-1;dR[5]=0;dR[6]=0;dR[7]=1;dR[8]=-1;
	dC[1]=1;dC[2]=-1;dC[3]=0;dC[4]=0;dC[5]=-1;dC[6]=1;dC[7]=0;dC[8]=0;
	fR[1]=1;fR[2]=-1;fR[3]=-ny;fR[4]=ny;fR[5]=1;fR[6]=-1;fR[7]=-ny;fR[8]=ny;
	fC[1]=-nx;fC[2]=nx;fC[3]=-1;fC[4]=1;fC[5]=nx;fC[6]=-nx;fC[7]=1;fC[8]=-1;

//  the following is the step 2.2
 
       bool something_done,flag;
        int *R,*C; 
       int scans,in,jn;
	    R=&i;
        C=&j;

   while(something_done&&1)
  {      
		 scans=1;
		while((scans<=8)&&something_done)
	   { 

          i=R0[scans];
		  j=C0[scans];
        
		 something_done=false;
          do
		  {     
				if(demtemp[j][i]>dem[j][i])
				{  
					
					for(int k=1; k<=8; k++)  
					{
						in=i+d1[k];
						jn=j+d2[k];
					
						 
						if(dem[j][i]>=demtemp[jn][in]+Delta1[k])
						{	demtemp[j][i]=dem[j][i];
							something_done=true;
						
							dry_upward_cell(i,j);   //这里容易出问题
							
							goto line22;
						}
						//	}

	
						if(demtemp[j][i]>demtemp[jn][in]+Delta1[k])  
						{	demtemp[j][i]=demtemp[jn][in]+Delta1[k];
							something_done=true;
							
						}
					}

				}

         
line22:      	flag=true;

			}while(Next_Cell(R,C,scans,dR,dC,fR,fC)==true);
			
	    // if(something_done==false)
		  // return 0;	// goto line28;
       scans++;
     
	  }
  }     //  if(something_done==true)   goto line4;



 //    delete [] dem[0];
  //     delete [] dem;

*/

	dem1 = new double *[ncol];
        dem1[0]=new double[nrow*ncol];

       for( i = 1; i<ncol; i++)
	   {
		   
		   dem1[i] = dem1[i-1]+nrow;
	   }


ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	bian=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
	
  
 
   
   
	   ////////////////////////压缩dem数据,条件满足
	   nrow2=nrow;
	   ncol2=ncol;
	   int n=0,k=0,z=0; 
	 
 
if(ncol>770||nrow>577)
{     
	  if((ncol-770)>=(nrow-577)) 
		  n=ncol/770+1;
      else
		  n=nrow/577+1;	
	 
       for(int y=0;y<ncol/10*10;y+=n)
	   {   
		   int yyy=0;
	       for(int x=0;x<nrow/10*10;x+=n)
		   {
			   for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  dem1[yyy][xx]=dem1[yyy][xx]+demtemp[z][k];
					}
				
				}
        	dem1[yyy][xx]=dem1[yyy][xx]/(n*n);
	        yyy++;
			yy=yyy;	
			   }
    	xx++;
	   } 

	    for(i=0;i<xx;i++)
		   for(j=0;j<yy;j++)
		   {
              if(dem1[j][i]>0)
			  {
               color1[j][i]=(dem1[j][i]-TImin)/interval;
              }
           else 
			{
             color1[j][i]=255;
			}
           }
}
else
{

	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(demtemp[j][i]!=nodata)
			  {
               color[j][i]=(demtemp[j][i]-TImin)/interval;
              }
           else 
			{
             color[j][i]=255;
			}
           }
}





/*
       delete [] demtemp[0];
       delete [] demtemp; */  
        delete [] dem1[0];
       delete [] dem1;
     


	     DemDraw::OnOK();
}

void DemDraw::OnButtonFlowdirection() 
{
	// TODO: Add your control notification handler code here

    int    ny =nrow;
	int 	 nx=ncol;
     int i,j;
        flowdir = new short int *[ncol];
        flowdir[0]=new short int[nrow*ncol];

       for( i = 1; i<ncol; i++)
        flowdir[i] = flowdir[i-1]+nrow;

     slop = new double *[ncol];
        slop[0]=new double[nrow*ncol];

       for( i = 1; i<ncol; i++)
        slop[i] = slop[i-1]+nrow;



double SlopeMax, SlopeTemp;
int direction_factor[9]={0,1,2,3,4,5,6,7,8};   //{0,1,128,64,32,16,8,4,2};

	
	for(i=1; i<ny-1; i++)
		for(j=1; j<nx-1; j++)
		{ 
			if(demtemp[j][i]!=nodata)
			{
					SlopeMax=0;
					int xu_flag=0;
				    for(int k=1; k<=8; k++)  
					{
						int in=i+d1[k];
					    int 	jn=j+d2[k];
					     
					  if(demtemp[jn][in]!=nodata)
						if((SlopeTemp=(demtemp[j][i]-demtemp[jn][in])/(1000*Delta1[k]*csize))>SlopeMax)
					   {   SlopeMax=SlopeTemp;
						   slop[j][i]=SlopeTemp;
                           flowdir[j][i]=direction_factor[k];
					   }
					 else
					 {
					 xu_flag=1;
					 }

					}
                   if((xu_flag==1)&&(SlopeMax==0)) 
				   {
					   slop[j][i]=-1;
					   flowdir[j][i]=-1;

				   }


			}
		   else
		   {
			   slop[j][i]=-1;
			   flowdir[j][i]=-1;
		   }
		}  
 
/// 下面是处理边界  

  for(i=0; i<ny; i++)
		{
          slop[0][i]=-1;
		  slop[nx-1][i]=-1;
		  flowdir[0][i]=-1;
		  flowdir[nx-1][i]=-1;
		}
for(j=0; j<nx; j++)
		{
          slop[j][0]=-1;
		  slop[j][ny-1]=-1;
		  flowdir[j][0]=-1;
		  flowdir[j][ny-1]=-1;
		}
 /////////////////////////////////////////////////////////////////////////////


    


	dem1 = new double *[ncol];
        dem1[0]=new double[nrow*ncol];

       for( i = 1; i<ncol; i++)
	   {
		   
		   dem1[i] = dem1[i-1]+nrow;
	   }


ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	bian=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
	
  
 
   
   
	   ////////////////////////压缩dem数据,条件满足
	   nrow2=nrow;
	   ncol2=ncol;
	   int n=0,k=0,z=0; 
	 
 
if(ncol>770||nrow>577)
{     
	  if((ncol-770)>=(nrow-577)) 
		  n=ncol/770+1;
      else
		  n=nrow/577+1;	
	 
       for(int y=0;y<ncol/10*10;y+=n)
	   {   
		   int yyy=0;
	       for(int x=0;x<nrow/10*10;x+=n)
		   {
			   for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  dem1[yyy][xx]=dem1[yyy][xx]+flowdir[z][k];
					}
				
				}
        	dem1[yyy][xx]=dem1[yyy][xx]/(n*n);
	        yyy++;
			yy=yyy;	
			   }
    	xx++;
	   } 

	    for(i=0;i<xx;i++)
		   for(j=0;j<yy;j++)
		   {
              if(dem1[j][i]>0)
			  {
               color1[j][i]=(dem1[j][i]-TImin)/interval;
              }
           else 
			{
             color1[j][i]=255;
			}
           }
}
else
{

	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(flowdir[j][i]!=-1)
			  {
               color[j][i]=(flowdir[j][i]-1)*255/7;//(flowdir[j][i]-1)*255/8;
              }
           else 
			{
             color[j][i]=255;
			}
           }
}





/*
       delete [] demtemp[0];
       delete [] demtemp; */  
        delete [] dem1[0];
       delete [] dem1;
     


	    DemDraw::OnOK();
////////////////////////////////////// 以下是输出流向文件
/*		FILE *fp;
	 fp= fopen("flowdir.txt","w");

fprintf(fp,"ncols %d\n",ncol);
fprintf(fp,"nrows %d\n",nrow);
fprintf(fp,"xllcenter	728172.117396\n");
fprintf(fp,"yllcenter	3685632.186265\n");
fprintf(fp,"cellsize %f\n",csize);
fprintf(fp,"nodata_value -1\n");
	 	
	    for(i=0; i<nrow; i++)
		{
		for(j=0; j<ncol; j++)
		{ 

	    fprintf(fp,"%d ",flowdir[j][i]);

		}
        fprintf(fp,"\n");
		}
     fclose(fp);

	 */
}


void darea(int i,int j)
  { 
     int     ny=nrow;
	 int 	nx =ncol;
    int in,jn,k,con=0;
      // con is a flag that signifies possible contaminatin of area
		//due to edge effects  
    if(i!=0 && i!=ny-1 && j!=0 && j!=nx-1 && flowdir[j][i] > -1)
                 //not on boundary  
    {
      if(larr[j][i]==0)  // not touched yet
      {
       larr[j][i]=1;
	//	if(useww == 1)fareaw.d[j][i]=fweight.d[j][i];                
        for(k=1; k<=8; k++)
        {  in=i+d1[k];
           jn=j+d2[k];
//test if neighbor drains towards cell excluding boundaryies 
           if(flowdir[jn][in]>0 && ( (flowdir[jn][in]-k)==4 || (flowdir[jn][in]-k)==-4))
             {
                darea(in,jn);
                if(larr[jn][in] < 0)con = -1;
                else larr[j][i]=larr[j][i]+larr[jn][in];
			    /*	                                                
			      if(useww == 1)
					{
					  if(fareaw.d[jn][in] <= ndv  || fareaw.d[j][i] <=ndv)
					  {  fareaw.d[j][i]=ndv;
					  }
					  else fareaw.d[j][i]=fareaw.d[j][i]+fareaw.d[jn][in];
					}
                 */
             }
           if(flowdir[jn][in] < 0)con = -1;
        }
       /*                                   
		if(con == -1 && ccheck == 1)
		{
			larr.d[j][i]=-1;
			if(useww == 1)fareaw.d[j][i]=ndv;         
		}
		*/
      }
    }
	else larr[j][i]=-1;


}



void DemDraw::OnButtonArea() 
{
	// TODO: Add your control notification handler code here
   int     ny=nrow;
	int 	 nx=ncol;
	int i,j;
//double smallest=0.001/csize;

     larr = new int *[ncol];
        larr[0]=new  int[nrow*ncol];

       for( i = 1; i<ncol; i++)
        larr[i] =larr[i-1]+nrow;




	
	for(i=0; i< ny; i++)
	{
		for(j=0; j< nx; j++)
        {
			if(i!=0 && i!=ny-1 && j!=0 && j!=nx-1 && flowdir[j][i] > -1)
				larr[j][i]=0;
			else
              larr[j][i]=-1;
        }
	}

	//call drainage area subroutine for each area 
		//work from middle outwards to avoid deep recursions
	
       for(i=1; i<ny-1; i++)                    
		for(j=1; j<nx-1; j++)
		{
		    darea(i,j);


		}
/*		for(i=ny/2; i<ny-1; i++)                    
		{  for(j=nx/2; j<nx-1; j++)
		    darea(i,j);



		for(j=nx/2-1; j>=1; j--)
			darea(i,j);
		}  
		for(i=ny/2-1; i>=1; i--)                    
		{  for(j=nx/2; j<nx-1; j++)
        darea(i,j);
		for(j=nx/2-1; j>=1; j--)
			darea(i,j);
		} 
*/

           
//上面是计算汇流面积 

/////////////////////////////////////////////////////////////////////////////
	
		// TImean=0;
 TImin=10000;
 TImax=0;
	double 	total;
		for(i=1; i<ny-1; i++)
		for(j=1; j<nx-1; j++)
		{  
           if(larr[j][i]!=-1)
			   {
				  //total++;
				   //arr1x[total]=temp;
                  // TImean+=larr[j][i];
				   if(larr[j][i]<TImin) TImin=larr[j][i];
				  if(larr[j][i]>TImax) TImax=larr[j][i];

			   }
		}

	      //TImean/=total;
		   interval=(TImax-TImin)/255;	
		
		
		
		
		
		
		
		dem1 = new double *[ncol];
        dem1[0]=new double[nrow*ncol];

       for( i = 1; i<ncol; i++)
	   {
		   
		   dem1[i] = dem1[i-1]+nrow;
	   }


ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	bian=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
	
  
 
   
   
	   ////////////////////////压缩dem数据,条件满足
	   nrow2=nrow;
	   ncol2=ncol;
	   int n=0,k=0,z=0; 
	 
 
if(ncol>770||nrow>577)
{     
	  if((ncol-770)>=(nrow-577)) 
		  n=ncol/770+1;
      else
		  n=nrow/577+1;	
	 
       for(int y=0;y<ncol/10*10;y+=n)
	   {   
		   int yyy=0;
	       for(int x=0;x<nrow/10*10;x+=n)
		   {
			   for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  dem1[yyy][xx]=dem1[yyy][xx]+larr[z][k];
					}
				
				}
        	dem1[yyy][xx]=dem1[yyy][xx]/(n*n);
	        yyy++;
			yy=yyy;	
			   }
    	xx++;
	   } 

	    for(i=0;i<xx;i++)
		   for(j=0;j<yy;j++)
		   {
              if(dem1[j][i]>0)
			  {
               color1[j][i]=(larr[j][i]-TImin)/interval;
              }
           else 
			{
             color1[j][i]=255;
			}
           }
}
else
{

	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(larr[j][i]!=-1)
			  {
               color[j][i]=(larr[j][i]-TImin)/interval;
              }
           else 
			{
             color[j][i]=255;
			}
           }
}





/*
       delete [] demtemp[0];
       delete [] demtemp; */  
        delete [] dem1[0];
       delete [] dem1;
     


	    DemDraw::OnOK();







	
}

void DemDraw::OnButtonTopindex() 
{
	// TODO: Add your control notification handler code here
    int     ny=nrow;
	int 	nx =ncol;
	int i,j;
	double smallest=0.001/csize;

        topindex = new short int *[ncol];
        topindex[0]=new short int[nrow*ncol];
         for( i = 1; i<ncol; i++)
        topindex[i] = topindex[i-1]+nrow;



for(i=0; i<ny; i++)
		for(j=0; j<nx; j++)
		{ 
			if(larr[j][i]!=-1)
			{
				if(slop[j][i]>smallest+0.00001)
                  topindex[j][i]= log(larr[j][i]*csize/slop[j][i]);
				else
					 topindex[j][i]= log(larr[j][i]*csize/(0.5/csize));   
			}
		   else 
			   topindex[j][i]=-1;          //  no data is -1 for topindex
		}  

     ////      ///////////////////////////////////////////////////////////////////////

	 TImin=10000;
 TImax=0;
	double 	total;
		for(i=1; i<ny-1; i++)
		for(j=1; j<nx-1; j++)
		{  
           if(topindex[j][i]!=-1)
			   {
				  //total++;
				   //arr1x[total]=temp;
                  // TImean+=topindex[j][i];
				   if(topindex[j][i]<TImin) TImin=topindex[j][i];
				  if(topindex[j][i]>TImax) TImax=topindex[j][i];

			   }
		}

	      //TImean/=total;
		   interval=(TImax-TImin)/255;	
		
		
		
		
		
		
		
		dem1 = new double *[ncol];
        dem1[0]=new double[nrow*ncol];

       for( i = 1; i<ncol; i++)
	   {
		   
		   dem1[i] = dem1[i-1]+nrow;
	   }


ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	bian=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
	
  
 
   
   
	   ////////////////////////压缩dem数据,条件满足
	   nrow2=nrow;
	   ncol2=ncol;
	   int n=0,k=0,z=0; 
	 
 
if(ncol>770||nrow>577)
{     
	  if((ncol-770)>=(nrow-577)) 
		  n=ncol/770+1;
      else
		  n=nrow/577+1;	
	 
       for(int y=0;y<ncol/10*10;y+=n)
	   {   
		   int yyy=0;
	       for(int x=0;x<nrow/10*10;x+=n)
		   {
			   for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  dem1[yyy][xx]=dem1[yyy][xx]+topindex[z][k];
					}
				
				}
        	dem1[yyy][xx]=dem1[yyy][xx]/(n*n);
	        yyy++;
			yy=yyy;	
			   }
    	xx++;
	   } 

	    for(i=0;i<xx;i++)
		   for(j=0;j<yy;j++)
		   {
              if(dem1[j][i]>0)
			  {
               color1[j][i]=(topindex[j][i]-TImin)/interval;
              }
           else 
			{
             color1[j][i]=255;
			}
           }
}
else
{

	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(topindex[j][i]!=-1)
			  {
               color[j][i]=(topindex[j][i]-TImin)/interval;
              }
           else 
			{
             color[j][i]=255;
			}
           }
}





/*
       delete [] demtemp[0];
       delete [] demtemp; */  
        delete [] dem1[0];
       delete [] dem1;
     


	    DemDraw::OnOK();
}

void DemDraw::OnButtonWatertable() 
{
	// TODO: Add your control notification handler code here

	ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
		CString   StrFilter="文本文档(*.txt)|*.txt|所有文件(*.*)|*.*||";
	CFileDialog  Dlg(TRUE,NULL,NULL,NULL,StrFilter,this);	
	if (Dlg.DoModal()==IDOK)
	{
    m_msg=Dlg.GetPathName();//传值代码可在此添加.说明:要获得文件名,可以用"dlg.GetFileName()"来实现.
    UpdateData(FALSE);
	}
	   if(m_msg=="") return;
	 
	   
	   
	   	FILE *fp1;
  int i,j,ncol,nrow;
  unsigned long total=0;
 float nodata,TImin=10000,TImax=0;
 // double *arr1x, *arr1y, *arr1y2; 
 // double *arr2x, *arr2y, *arr2y2;  
  
   
 
   char sss[120];

  fp1 = fopen(m_msg,"r");    ///////////////
  
       
       fscanf(fp1,"%s",sss);
       fscanf(fp1,"%d",&ncol);
	   fgets(sss,100,fp1);
       fscanf(fp1,"%s",sss);
       fscanf(fp1,"%d",&nrow);
	   fgets(sss,100,fp1);
       
	//   arr1x=new double[ncol*nrow+1];
        
	   for(i=1;i<=3;i++)
	   {
        fgets(sss,100,fp1);
	   }
        
	   fscanf(fp1,"%s",sss);
       fscanf(fp1,"%f",&nodata);
	  
       float **dem = new float *[ncol];
        dem[0]=new float[nrow*ncol];

       for( i = 1; i<ncol; i++)
        dem[i] = dem[i-1]+nrow;

   
         TImean=0;
	    for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {
			   fscanf(fp1,"%f",&dem[j][i]);
			   if(dem[j][i]!=nodata)
			   {
				   total++;
				 //  arr1x[total]=temp;
                 TImean+=dem[j][i];
				   if(dem[j][i]<TImin) TImin=dem[j][i];
				  if(dem[j][i]>TImax) TImax=dem[j][i];

			   }

		   }
        TImean/=(float)total;
       fclose(fp1);
	   

	  float interval;
         interval=(TImax-TImin)/255;

CWnd* pp=GetDlgItem(IDC_dem); 
	  CDC* cc=pp->GetDC();  
	  //CBitmap *bitmap;
      pp->Invalidate();   
      pp->UpdateWindow();   
      cc->SelectStockObject(BLACK_BRUSH);
	  CDC MemDC;
	  CBitmap MemBitmap;
      MemDC.CreateCompatibleDC(NULL);
	  MemBitmap.CreateCompatibleBitmap(cc,770,570);
	  CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	  MemDC.FillSolidRect(0,0,850,680,RGB(255,255,255));

 int NS;
for(int Ntemp=1;Ntemp<11;Ntemp++)
{
	  if(Ntemp==1) NS=181;
	  if(Ntemp==2) NS=208;
      if(Ntemp==3) NS=235;
	  if(Ntemp==4) NS=244;
      if(Ntemp==5) NS=253;
      if(Ntemp==6) NS=271;
	  if(Ntemp==7) NS=298;
	  if(Ntemp==8) NS=388;
	  if(Ntemp==9) NS=469;
	  if(Ntemp==10) NS=550;
	   
	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(dem[j][i]!=nodata)
			  {
               if(5*Zbar[NS]>SZM*(dem[j][i]-TL+5))
			   {
				 colorlast[j][i][1]=(dem[j][i]-TImin)/interval;
                 colorlast[j][i][2]=colorlast[j][i][1];
                 colorlast[j][i][3]=colorlast[j][i][1];

			   }
			   else
			   {   colorlast[j][i][1]=0;//(dem[j][i]-TImin)/interval;
				   colorlast[j][i][2]=255;//colorlast[j][i][1];
                  colorlast[j][i][3]=255;

			   }

              }
           else 
			{
             color[j][i]=255;
			}
           }
	  		   
	  
	   
	   nrow2=nrow;
	   ncol2=ncol;
///////////////////////////////////////////////////////
int n,k,z; 
 
if(ncol2>770||nrow2>577)
{ 
	  if((ncol2-770)>=(nrow2-577)) 
		  n=ncol2/770+1;
      else
		  n=nrow2/577+1;	

       for(int y=0;y<nrow2;y+=n)
	   {   int yyy=0;
	       for(int x=0;x<ncol2;x+=n)
		   {
			   
	            for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  color1[xx][yy]=color1[xx][yy]+color[k][z];
					}
				}
        	color1[xx][yy]=color1[xx][yy]/(n*n);
	        yyy++;
			yy=yyy;
		   }
    	xx++;
	   } 
}
   //MessageBox("数据读取完毕");


    


////////////////////////////////////  
int nx=0,ny=0;

cc->FillSolidRect(0,0,770,577,RGB(255,255,255));

///////////////////////////////////////


if(bian==0)
{
	if(ncol2>770 || nrow2>577) 
	{  
		if(xx<577)   nx=(577-xx)/2;
		if(yy<770)   ny=(770-yy)/2;
		for(int x=0;x<xx;x++)  
		{ 
			for(int y=0;y<yy;y++)
			{
        	if(color1[y][x]!=255)
			{
	          //if(Zbar[NS]<=SZM*(dem[j][i]-TImean))
	          MemDC.SetPixel(y,x,RGB(colorlast[y][x][1],colorlast[y][x][2],colorlast[y][x][3]));
			 // else 
			//	  MemDC.SetPixel(y,x,RGB(0,0,255));
			}
			}
		}

	}
  else
	{
	   if(nrow2<577)   nx=(577-nrow2)/2;
	   if(ncol2<770)   ny=(770-nrow2)/2;
	for(int x=0;x<nrow2;x++)  
	{ 
		for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
	      MemDC.SetPixel(y,x,RGB(colorlast[y][x][1],colorlast[y][x][2],colorlast[y][x][3]));
	   }
	}

	}
	}
else
{
if(ncol2>770 || nrow2>577) 
{  
if(xx<577)   nx=(577-xx)/2;
if(yy<770)   ny=(770-yy)/2;
for(int x=0;x<xx;x++)  
{ 
	for(int y=0;y<yy;y++)
	   {
	if(color1[y][x]!=255)
	MemDC.SetPixel(y,x,RGB(colorlast[y][x][1],colorlast[y][x][2],colorlast[y][x][3]));
	   }
}

}
else
{
if(nrow2<577)   nx=(577-nrow2)/2;
if(ncol2<770)   ny=(770-nrow2)/2;
for(int x=0;x<nrow2;x++)  
{ 
	for(int y=0;y<ncol2;y++)
	   {
		 if(color[y][x]!=255)
	      MemDC.SetPixel(y,x,RGB(colorlast[y][x][1],colorlast[y][x][2],colorlast[y][x][3]));//?????????
	   }
}

}
}
   cc->BitBlt(ny,nx,770-ny,577-nx,&MemDC,0,0,SRCCOPY);
   Sleep(600); 
}   
   MemBitmap.DeleteObject();
   MemDC.DeleteDC();


 delete [] dem[0];
       delete [] dem;

	
}

void DemDraw::OnButtonRivernet() 
{
	// TODO: Add your control notification handler code here
   // TImean=0;
 TImin=10000;
 TImax=0;
 int i,j;
 int  ny=nrow;
	int  nx=ncol;
	double 	total;
		for(i=1; i<ny-1; i++)
		for(j=1; j<nx-1; j++)
		{  
           if(larr[j][i]!=-1)
			   {
				  //total++;
				   //arr1x[total]=temp;
                  // TImean+=larr[j][i];
				   if(larr[j][i]<TImin) TImin=larr[j][i];
				  if(larr[j][i]>TImax) TImax=larr[j][i];

			   }
		}

	      //TImean/=total;
		   interval=(TImax-threshold)/255;	
		
		
		
		
		
		
		
		dem1 = new double *[ncol];
        dem1[0]=new double[nrow*ncol];

       for( i = 1; i<ncol; i++)
	   {
		   
		   dem1[i] = dem1[i-1]+nrow;
	   }


ncol2=0;
	nrow2=0;
	xx=0;
	yy=0;
	bian=0;
	for(int jjj=0;jjj<1000;jjj++)
	{for(int iii=0;iii<1000;iii++)
	{color[jjj][iii]=0;
	color1[jjj][iii]=0;
	}}
	// TODO: Add your control notification handler code here
	
  
 
   
   
	   ////////////////////////压缩dem数据,条件满足
	   nrow2=nrow;
	   ncol2=ncol;
	   int n=0,k=0,z=0; 
	 
 
if(ncol>770||nrow>577)
{     
	  if((ncol-770)>=(nrow-577)) 
		  n=ncol/770+1;
      else
		  n=nrow/577+1;	
	 
       for(int y=0;y<ncol/10*10;y+=n)
	   {   
		   int yyy=0;
	       for(int x=0;x<nrow/10*10;x+=n)
		   {
			   for(k=y;k<y+n;k++)
				{
                    for(z=x;z<x+n;z++)
					{
	                  dem1[yyy][xx]=dem1[yyy][xx]+larr[z][k];
					}
				
				}
        	dem1[yyy][xx]=dem1[yyy][xx]/(n*n);
	        yyy++;
			yy=yyy;	
			   }
    	xx++;
	   } 

	    for(i=0;i<xx;i++)
		   for(j=0;j<yy;j++)
		   {
              if(dem1[j][i]>0)
			  {
               color1[j][i]=(larr[j][i]-TImin)/interval;
              }
           else 
			{
             color1[j][i]=255;
			}
           }
}
else
{

	   for(i=0;i<nrow;i++)
		   for(j=0;j<ncol;j++)
		   {

              if(larr[j][i]<threshold)
			  color[j][i]=255;
			//  else if((larr[j][i]<2)&&(larr[j][i]
				 // color[j][i]=0;
              else 
               color[j][i]=(larr[j][i]-threshold)/interval;
              
		   }
}





/*
       delete [] demtemp[0];
       delete [] demtemp; */  
        delete [] dem1[0];
       delete [] dem1;
     


	    DemDraw::OnOK();


}
