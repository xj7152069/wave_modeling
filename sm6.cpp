
//声波方程正演模拟

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>

using namespace std;
float **s1,**s2,**s3,**s4,**sx11,**sx12,**sx13,**sx21,**sx22,**sx23,**sx24,**sx31,**sx32,**sx33;
float p2[2000][2000];
int main()
{   

////////////////////////定义变量，并初始化////////////////////////
   float mod(0), xsxs,DX,DY,DT,a91,a1,a2,a3,a4,a5,a6,a7,a8,a9,xf,yf,t,x,z,dx,dy,ddx,ddy,snx1,sny1,snx2,sny2,t2,t5;
    int T,i,j,k,n,n1,i1,j1,t3,t4,N,D,m,X,Y,N1,Xzuo,Xyou;
    float xs2[5]={1.666667,-0.238095,0.039683,-0.004960,0.000317};
    float xs1[10]={-0.0007926,0.00991800,-0.0595200,0.238080,-0.833333,0.833333,-0.238080,0.0595200,-0.00991800,0.0007926};
    float f,u0(0),u1(0),u2(0),u3(0),u4(0),u5(0),u(0),ux(0),uy(0);
    
    a91=0,a9=-9;t=0.001,t2=0,x=0,z=0,yf=40,xf=200,X=300,Y=250,T=1500,DX=10,DY=10,DT=0.001,a1=-9,a2=-9,a3=-9,a4=-9,a5=-9,a6=1,a7=-9,a8=-9;
/////////////////////////////////////////////////////////////////
          
     for(i=0;i<X;i++)
       {for(j=0;j<Y;j++)
         {p2[j][i]=3000;}}      
          
/////////////////功能选择////////////////////////////////////////
     cout<<"input the 'xsxs', [3.0,7.0] is ok"<<endl;
     cin>>xsxs;
  while(a1!=0)
 {  cout<<endl;cout<<endl;
    cout<<"************************************************"<<endl;
    cout<<"you can input the number to choose the following function"<<endl;
    cout<<"1--mulity secsmic modeling"<<endl;
    cout<<"2--change the defaults parameters and input the underground model from your file"<<endl;
    cout<<"3--output the seismic record of horizontal profile(x-t)"<<endl;
    cout<<"4--output the seismic record of vertical profile(y-t)"<<endl;
    cout<<"5--output a wave front"<<endl;
    cout<<"6--change the seismic focus model"<<endl;
    cout<<"7--output the seismic movie(the file may be large)"<<endl;
    cout<<"8--model surface focus"<<endl;
    cout<<"0--quit the function chose and output the data"<<endl;
    cout<<"************************************************"<<endl;
    cin>>a1;
     if(a1==1)
    {a8=1;
     cout<<"please input the separation distance of seismic focus(D)"<<endl;
     cin>>D;
     cout<<"please input the number of seismic focus(N)"<<endl;
     cin>>N;
     cout<<"please input the (N1)"<<endl;
     cin>>N1;
     cout<<"please input the (Xzuo)"<<endl;
     cin>>Xzuo;
     cout<<"please input the (Xyou)"<<endl;
     cin>>Xyou;        //Xzuo&&Xyou should >=0,else output all surface data
     cout<<"input '1' to output movie";
     cin>>a7;
     }

    //改变参数值
     if(a1==2)
    {
     cout<<"please inpout the range X, but the X can't over 1980"<<endl;
     cin>>X;
     while(X>1980)
    {cout<<"the X has over the range, please input again"<<endl;
     cin>>X;}
     cout<<"please inpout the range Y, but the Y can't over 1980"<<endl;
     cin>>Y;
     while(Y>1980)
    {cout<<"the Y has over the range, please input again"<<endl;
     cin>>Y;}
     cout<<"please inpout the T, but the T can't over 10000"<<endl;
     cin>>T;
     while(T>10000)
    {cout<<"the T has over the range, please input again"<<endl;
     cin>>T;}
     cout<<"please inpout the DX&DY:";
     cin>>DX;
     DY=DX;
     cout<<"please inpout the DT:";
     cin>>DT;
     cout<<"OK"<<endl;
     xf=0.5*(X);
     
    //输入速度模型
     ifstream infile;
     infile.open("model.dat",ios::binary);
     if(!infile) cout<<"error"<<endl;
      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&p2[i][j],sizeof(p2[i][j]));  
      if(i>150)
         p2[i][j]=5000.0;
       }
      }
     infile.close();
     mod=1;

     cout<<"the input of model has finished"<<endl;
     cout<<"your underground model will be saved as dat2"<<endl;
     a2=1; xf=0.5*(X);
     cout<<"input a number to continue:";
     cin>>n1;
    }
    if(a1==3)
    {cout<<"please input the z"<<endl;
     cin>>z;
     while(z>Y || z<0)
    {cout<<"the z has over the range, please input again"<<endl;
     cin>>z;}
     a3=1;
     cout<<"the data will be saved as dat3"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==4)
    {cout<<"please input the x"<<endl;
     cin>>x;
     while(x>X || x<0)
    {cout<<"the x has over the range, please input again"<<endl;
     cin>>x;}
     a4=1;
     cout<<"the data will be saved as dat4"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==5)
    {cout<<"please input the t"<<endl;
     cin>>t2;a5=1;
     cout<<"the data will be saved as dat5"<<endl;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==6)
    { cout<<"1--change the site of single seismic focus"<<endl;
      cout<<"2--the surface is filled with seismic focus"<<endl;
      cin>>a6;
      if(a6==1)
      {cout<<"please input the site of seismic focus(xf)"<<endl;
       cin>>xf;
       cout<<"please input the site of seismic focus(yf)"<<endl;
       cin>>yf;}
       cout<<"OK"<<endl;
       cout<<"input a number to continue:";
       cin>>n1;}
     if(a1==7)
    {cout<<"your movie data will be saved as dat1"<<endl;
     a7=1;
     cout<<"input a number to continue:";
     cin>>n1;}
     if(a1==8)
     {a9=1;
     cout<<"do you want to use the vector seismic focus?(input '1' to use)"<<endl;
     cin>>a91;
     cout<<"input a number to continue:";
     cin>>n1;}
    if(a1==0)
    {cout<<"the simulation has begin, please wait a moment"<<endl;}
     }
     
     float C3=xsxs/2/(30)/DX*log(1000)/(30)/DX/(30)/DX;
     t5=double(Y)/X;
 /////////////////////////////////////////////////////////////////////    
     
     
     
 //////////////////用指针的形式定义动态数组//////////////////////////    
    s1=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        s1[j]=new float[X+20];  
    };
    
    s4=new float*[T];    
    for(j=0;j<T;j++)  
    {  
        s4[j]=new float[X+20];  
    };

    s2=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s2[j]=new float[X+20];  
    };
    
    s3=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s3[j]=new float[X+20];  
    };
    
    sx11=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx11[j]=new float[X+20];  
    };
    
    sx12=new float*[Y+20];    
    for(j=0;j<Y+20;j++)  
    {  
        sx12[j]=new float[X+20];  
    };
    
    sx13=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx13[j]=new float[X+20];  
    };
    
    sx21=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx21[j]=new float[X+20];  
    };
    
    sx22=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx22[j]=new float[X+20];  
    };
    
    sx23=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx23[j]=new float[X+20];  
    };
    
    sx24=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx24[j]=new float[X+20];  
    };
    
    sx31=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx31[j]=new float[X+20];  
    };
    
     
    sx32=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx32[j]=new float[X+20];  
    };
    
    sx33=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        sx33[j]=new float[X+20];  
    };
    
     for(j=0;j<Y+20;j++)
      {
      for(i=0;i<X+20;i++)
       {
       s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
     sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
     sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;sx24[j][i]=0.0;
     sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
     }
     }
///////////////////////////////////////////////////////////////

     
 ////////////多炮并行计算//////////////////////////////////
          if(a8==1)
          {
       ofstream outf3;
       ofstream outf2;
       ofstream outf;
char *str1,*str2,*str3;
double wj;
     outf2.open("model.dat");
       for(m=0;m<=N;m++)
       {

     for(j=0;j<Y+20;j++)
      {
      for(i=0;i<X+20;i++)
       {
       s1[j][i]=0.0;s2[j][i]=0.0;s3[j][i]=0.0;
     sx11[j][i]=0.0;sx12[j][i]=0.0;sx13[j][i]=0.0;
     sx21[j][i]=0.0;sx22[j][i]=0.0;sx23[j][i]=0.0;sx24[j][i]=0.0;
     sx31[j][i]=0.0;sx32[j][i]=0.0;sx33[j][i]=0.0;
     }
     }

    str1=new char[20];  
    str2=new char[10];  
    str3=new char[20]; 
 
if(mod==0)
{strcpy(str1,"zdb");
strcpy(str3,"zdmovie");}

if(mod==1)
{strcpy(str1,"surface");
strcpy(str3,"movie");}
wj=N1+m*D;
sprintf(str2, "%f", wj);
str2[4]='\0';
strcat(str1,str2);
strcat(str3,str2);
  
   if(a7==1)
    { outf.open(str3);}
     outf3.open(str1);

        for(k=0;k<T;k++)
       { 
        for(i=5;i<X+5;i++)
       {for(j=5;j<Y+5;j++)
        {
           for(n=0;n<5;n++)
           {  
           u=u+2*xs2[n];
           u1=u1+xs2[n]*(s2[j-n-1][i]+s2[j+n+1][i]);
           u2=u2+xs2[n]*(s2[j][i-n-1]+s2[j][i+n+1]);
           }
           for(n=0;n<10;n++)
           {if(n<5)
            {ux=ux+s2[j][i+n-5]*xs1[n];
             uy=uy+s2[j+n-5][i]*xs1[n];}
            else
            {ux=ux+s2[j][i+n-4]*xs1[n];
             uy=uy+s2[j+n-4][i]*xs1[n];}
           }

           if(j==40 && i==N1+m*D)
{f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));
/*f=exp((-3.1415*3.1415*900*(k*DT-0.04)*(k*DT-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(k*DT-0.04));*/ }
           else {f=0;}

           u3=(p2[j-5][i-5]*p2[j-5][i-5]*(DT/DX)*(DT/DX));
           s3[j][i]=(u1+u2-2*u*s2[j][i])*u3+2*s2[j][i]-s1[j][i]+f;
           snx1=0.0;snx2=0.0;
           sny1=0.0;sny2=0.0;
           dx=0;ddx=0;dy=0;ddy=0;
           if(i>=X-26 && j<=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)	   //角落处理	
	   snx1=i-(X-26);
           if(i<=34 && j>=t5*i+5*(1-t5) && j<=-t5*i+Y+5+t5*5)		
	   snx2=34-i;
           if(j>=Y-26 && j>t5*i+5*(1-t5) && j>-t5*i+Y+5+5*t5)		
	   sny1=j-(Y-26);
           if(j<=34 && j<t5*i+5*(1-t5) && j<-t5*i+Y+5+5*t5)		
	   sny2=34-j;		
           if(sny1 !=0)
          {dy=p2[j][i]*C3*sny1*sny1*DY*DY;
	   ddy=p2[j][i]*C3*2*sny1*DY;	
           }
          if(sny2 !=0)
          {dy=p2[j][i]*C3*sny2*sny2*DY*DY;
	   ddy=p2[j][i]*C3*2*sny2*DY;	
           }
          if(snx1 !=0)
          {dx=p2[j][i]*C3*snx1*snx1*DX*DX;
	   ddx=p2[j][i]*C3*2*snx1*DX;	
           }
          if(snx2 !=0)
          {dx=p2[j][i]*C3*snx2*snx2*DX*DX;
	   ddx=p2[j][i]*C3*2*snx2*DX;	
           }
         if(i>=0.5*(X+5))
           t3=1;
         else
           t3=-1;
         if(j>=40)
           t4=1;
         else
           t4=-1;
if(snx1!=0 || snx2!=0)
{sx11[j][i]=p2[j-5][i-5]*p2[j-5][i-5]*DT*DT*(u2-u*s2[j][i])*(1.0/(DX*DX))-dx*dx*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dx*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j-5][i-5]*p2[j-5][i-5]*ddx*(1.0/(DX))*(ux*t3)-dx*dx*dx*sx22[j][i]+3*dx*dx*(sx23[j][i]-sx22[j][i])/DT+3*dx*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j-5][i-5]*p2[j-5][i-5]*(1.0/(DX*DX))*(u1-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}
else    
{sx11[j][i]=p2[j-5][i-5]*p2[j-5][i-5]*DT*DT*(u1-u*s2[j][i])*(1.0/(DX*DX))-dy*dy*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dy*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j-5][i-5]*p2[j-5][i-5]*ddy*(1.0/(DX))*(uy*t4)-dy*dy*dy*sx22[j][i]+3*dy*dy*(sx23[j][i]-sx22[j][i])/DT+3*dy*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j-5][i-5]*p2[j-5][i-5]*(1.0/(DX*DX))*(u2-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}     
              
     // if(snx1!=0 || snx2!=0 || sny1!=0 || sny2!=0)
        s3[j][i]=sx11[j][i]+sx21[j][i]+sx31[j][i]+f;

       if(Xzuo>=0 && Xyou>=0)
        {if(j==40 && i>=(N1+m*D)-Xzuo && i<=(N1+m*D)+Xyou)
        {outf3.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
         }
        else
        {if(j==40)
        {outf3.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
         }

        if(k==1 && a2==1 && m==0)
        {outf2.write((char*)&p2[j-5][i-5],sizeof(p2[j-5][i-5]));
         }

       if(a7==1)
        {outf.write((char*)&s3[j][i],sizeof(s3[j][i]));}
      
         u1=0,u2=0,u3=0,u4=0,u=0,ux=0,uy=0;
        }
       }
          for(j1=0;j1<Y+20;j1++)
         {for(i1=0;i1<X+20;i1++)
         {s1[j1][i1]=s2[j1][i1];s2[j1][i1]=s3[j1][i1];
          sx13[j1][i1]=sx12[j1][i1],sx12[j1][i1]=sx11[j1][i1];
          sx33[j1][i1]=sx32[j1][i1],sx32[j1][i1]=sx31[j1][i1];
          sx24[j1][i1]=sx23[j1][i1],sx23[j1][i1]=sx22[j1][i1],sx22[j1][i1]=sx21[j1][i1];
        }
          }
         // cout<<k<<endl;
       }

    delete []str1;
    delete []str2;
    delete []str3;
outf3.close();

if(a7==1)
{outf.close();}
      cout<<m<<endl;
      }   
outf2.close();
}
/////////////////////////////////////////////////////////////////    
   
   
   
   
///////////////绘制速度模型的声波传播过程（主程序）////////////////////   
          if(a8!=1)
{
       ofstream outf3;
       ofstream outf4;
       ofstream outf2;
       ofstream outf5;
       ofstream outf;
	if(a7==1)
        {
        outf.open("dat1");}
        if(a2==1)
        {
        outf2.open("dat2");}
        if(a5==1)
        {
        outf5.open("dat5");}
        if(a3==1)
        {
        outf3.open("dat3");}
        if(a4==1)
        {
        outf4.open("dat4");}
   
       
        for(k=1;k<T;k++)
       { 
        for(i=5;i<X+5;i++)
       {for(j=5;j<Y+5;j++)
        {
           for(n=0;n<5;n++)
           {  
           u=u+2*xs2[n];
           u1=u1+xs2[n]*(s2[j-n-1][i]+s2[j+n+1][i]);
           u2=u2+xs2[n]*(s2[j][i-n-1]+s2[j][i+n+1]);
           }
           for(n=0;n<10;n++)
           {if(n<5)
            {ux=ux+s2[j][i+n-5]*xs1[n];
             uy=uy+s2[j+n-5][i]*xs1[n];}
            else
            {ux=ux+s2[j][i+n-4]*xs1[n];
             uy=uy+s2[j+n-4][i]*xs1[n];}
           }
           if(j==40 && a6==2 && i>=40 && i<=X-30) 
          {f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
           else if(j==yf && i==xf && a6==1)
{f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
           else {f=0;}

if(a9==1 && j<Y-4)
{f=0;
 if(((p2[j-5][i-5]-p2[j-4][i-5])!=0 || (p2[j-5][i-5]-p2[j-5][i-4])!=0) && i>40 && i<X-30 && a91==1)
  {f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
  else if((p2[j-5][i-5]-p2[j-4][i-5])!=0 && i>40 && i<X-30)
{f=(3.1415926)*(3.1415926)*900*(k*DT-0.04)*exp((-3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04)))*(3-2*3.1415*3.1415*900*(k*DT-0.04)*(DT*k-0.04));}
   }

           u3=(p2[j-5][i-5]*p2[j-5][i-5]*(DT/DX)*(DT/DX));
           s3[j][i]=(u1+u2-2*u*s2[j][i])*u3+2*s2[j][i]-s1[j][i]+f;
           snx1=0.0;snx2=0.0;
           sny1=0.0;sny2=0.0;
           dx=0;ddx=0;dy=0;ddy=0;
           if(i>=X-26 && j<=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)	   //角落处理	
	   snx1=i-(X-26);
           if(i<=34 && j>=t5*i+5*(1-t5) && j<=-t5*i+Y+5+t5*5)		
	   snx2=34-i;
           if(j>=Y-26 && j>t5*i+5*(1-t5) && j>-t5*i+Y+5+5*t5)		
	   sny1=j-(Y-26);
           if(j<=34 && j<t5*i+5*(1-t5) && j<-t5*i+Y+5+5*t5)		
	   sny2=34-j;		
           if(sny1 !=0)
          {dy=p2[j][i]*C3*sny1*sny1*DY*DY;
	   ddy=p2[j][i]*C3*2*sny1*DY;	
           }
          if(sny2 !=0)
          {dy=p2[j][i]*C3*sny2*sny2*DY*DY;
	   ddy=p2[j][i]*C3*2*sny2*DY;	
           }
          if(snx1 !=0)
          {dx=p2[j][i]*C3*snx1*snx1*DX*DX;
	   ddx=p2[j][i]*C3*2*snx1*DX;	
           }
          if(snx2 !=0)
          {dx=p2[j][i]*C3*snx2*snx2*DX*DX;
	   ddx=p2[j][i]*C3*2*snx2*DX;	
           }
         if(i>=0.5*(X+5))
           t3=1;
         else
           t3=-1;
         if(j>=40)
           t4=1;
         else
           t4=-1;
if(snx1!=0 || snx2!=0)
{sx11[j][i]=p2[j-5][i-5]*p2[j-5][i-5]*DT*DT*(u2-u*s2[j][i])*(1.0/(DX*DX))-dx*dx*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dx*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j-5][i-5]*p2[j-5][i-5]*ddx*(1.0/(DX))*(ux*t3)-dx*dx*dx*sx22[j][i]+3*dx*dx*(sx23[j][i]-sx22[j][i])/DT+3*dx*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j-5][i-5]*p2[j-5][i-5]*(1.0/(DX*DX))*(u1-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}
else    
{sx11[j][i]=p2[j-5][i-5]*p2[j-5][i-5]*DT*DT*(u1-u*s2[j][i])*(1.0/(DX*DX))-dy*dy*DT*DT*sx12[j][i]+(2*sx12[j][i]-sx13[j][i])+DT*(2*dy*(sx13[j][i]-sx12[j][i]));
sx21[j][i]=(-p2[j-5][i-5]*p2[j-5][i-5]*ddy*(1.0/(DX))*(uy*t4)-dy*dy*dy*sx22[j][i]+3*dy*dy*(sx23[j][i]-sx22[j][i])/DT+3*dy*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])/(DT*DT*DT))*(DT*DT*DT);
sx31[j][i]=DT*DT*p2[j-5][i-5]*p2[j-5][i-5]*(1.0/(DX*DX))*(u2-u*s2[j][i])+2*sx32[j][i]-sx33[j][i];}     
              
     // if(snx1!=0 || snx2!=0 || sny1!=0 || sny2!=0)
        s3[j][i]=sx11[j][i]+sx21[j][i]+sx31[j][i]+f;

        if(i==x && a4==1)
        {outf4.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(j==z && a3==1)
        {outf3.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(k==t2 && a5==1)
        {outf5.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(k==1 && a2==1)
        {outf2.write((char*)&p2[j-5][i-5],sizeof(p2[j-5][i-5]));
         }
        if(a7==1)
        {outf.write((char*)&s3[j][i],sizeof(s3[j][i]));}
      
         u1=0,u2=0,u3=0,u4=0,u=0,ux=0,uy=0;
        }
       }
          for(j1=0;j1<Y+20;j1++)
         {for(i1=0;i1<X+20;i1++)
         {s1[j1][i1]=s2[j1][i1];s2[j1][i1]=s3[j1][i1];
          sx13[j1][i1]=sx12[j1][i1],sx12[j1][i1]=sx11[j1][i1];
          sx33[j1][i1]=sx32[j1][i1],sx32[j1][i1]=sx31[j1][i1];
          sx24[j1][i1]=sx23[j1][i1],sx23[j1][i1]=sx22[j1][i1],sx22[j1][i1]=sx21[j1][i1];
        }
          }
          cout<<k<<endl;
       }
if(a2==1)
outf2.close(); 
if(a7==1)
outf.close(); 
if(a5==1)
outf5.close(); 
if(a3==1)
outf3.close(); 
if(a4==1)
outf4.close(); 
  }
  ///////////////////////////////////////////////////////////////////// 
   
   
   
 /////////////////////释放内存///////////////////////////////////////////  

    for(int i=0;i<Y+20;i++)  
        delete []s1[i];//先单独释放第一维中每个数组的内存  
    delete []s1;

    for(int i=0;i<T;i++)  
        delete []s4[i];//先单独释放第一维中每个数组的内存  
    delete []s4;

    for(int i=0;i<Y+20;i++)  
        delete []s2[i];//先单独释放第一维中每个数组的内存  
    delete []s2;
    
    for(int i=0;i<Y+20;i++)  
        delete []s3[i];//先单独释放第一维中每个数组的内存  
    delete []s3;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx11[i];//先单独释放第一维中每个数组的内存  
    delete []sx11;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx12[i];//先单独释放第一维中每个数组的内存  
    delete []sx12;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx13[i];//先单独释放第一维中每个数组的内存  
    delete []sx13;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx21[i];//先单独释放第一维中每个数组的内存  
    delete []sx21;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx22[i];//先单独释放第一维中每个数组的内存  
    delete []sx22;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx23[i];//先单独释放第一维中每个数组的内存  
    delete []sx23;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx24[i];//先单独释放第一维中每个数组的内存  
    delete []sx24;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx31[i];//先单独释放第一维中每个数组的内存  
    delete []sx31;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx32[i];//先单独释放第一维中每个数组的内存  
    delete []sx32;
    
    for(int i=0;i<Y+20;i++)  
        delete []sx33[i];//先单独释放第一维中每个数组的内存  
    delete []sx33;

/////////////////////////////////////////////////////////////////////
   
   

cout<<endl<<"finished"<<endl;

return(0);
}
