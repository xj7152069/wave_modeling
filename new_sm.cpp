
//声波方程正演模拟

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#define pi 3.1415926
using namespace std;

float **s1,**s2,**s3,**p2,**sx11,**sx12,**sx13,**sx21,\
**sx22,**sx23,**sx24,**sx31,**sx32,**sx33,**suface_data,*zbbx,**nspy;
char *str_movie,*str_forwave,*str_suface,*str_nspy,*str_id;

float zb(int k, float DT)
{
	float f;
    f=(pi)*(pi)*900*(k*DT-0.04)*\
exp((-pi*pi*900*(k*DT-0.04)*(DT*k-0.04)))\
*(3-2*pi*pi*900*(k*DT-0.04)*(DT*k-0.04));
	return f;
}

int main()
{
////////////////////////定义变量，并初始化////////////////////////
   float DX,DY,DT,xf,yf,t,x,z,dx,dy,ddx,ddy,\
snx1,sny1,snx2,sny2,t2,t5,xshd(25),source_id;
    int T,i,j,k,n,n1,i1,j1,t3,t4,N,D,m,X,Y,N1,source_model(3),\
out_movie(1),out_sufer(1),out_forwave(1),suface_PML(1);
    float xs2[5]={1.666667,-0.238095,0.039683,-0.004960,0.000317};
    float xs1[10]={-0.0007926,0.00991800,-0.0595200,0.238080,-0.833333,\
0.833333,-0.238080,0.0595200,-0.00991800,0.0007926};
    float f,u1(0),u2(0),u(0),ux(0),uy(0);
t=0.001,t2=300,x=0,z=40,yf=40,xf=400,\
X=801,Y=200,T=1500,DX=10,DY=10,DT=0.001;
///////////////////////输入参数///////////////////////////////////
    /*基本参数*/
    cout<<"input the width of model"<<endl;
    cin>>X;
    cout<<"input the deepth of model"<<endl;
    cin>>Y;
    cout<<"input the record time"<<endl;
    cin>>T;
    cout<<"input the gep of hor -->"<<endl;
    cin>>DX;
    cout<<"input the gep of vet |"<<endl;
    cin>>DY;
    cout<<"input the gep of time"<<endl;
    cin>>DT;

    /*震源模式及是否使用自由表面*/
    cout<<"input '1' to use surface_PML_boundary"<<endl;
    cin>>suface_PML;
    cout<<"chose the source model(1-4)"<<endl;
    cin>>source_model;
    cout<<"input the source_X location"<<endl;
    cin>>xf;
    cout<<"input the source_Y location"<<endl;
    cin>>yf;

    /*输出文件*/
    cout<<"input '1' to output movie"<<endl;
    cin>>out_movie;
    cout<<"input '1' to output suface data"<<endl;
    cin>>out_sufer;
    cout<<"input '1' to output forwave"<<endl;
    cin>>out_forwave;
    cout<<"input the time of output forwave"<<endl;
    cin>>t2;
    cout<<"input the depth of output suface"<<endl;
    cin>>z;
    cout<<"input the source id(should be >0)"<<endl;
    cin>>source_id;

    zbbx=new float[T]; 
    p2=new float*[Y];    
    for(j=0;j<Y;j++)  
    {  
        p2[j]=new float[X];  
    };
    suface_data=new float*[T];    
    nspy=new float*[T];   
    for(j=0;j<T;j++)  
    {  
        suface_data[j]=new float[X]; 
        nspy[j]=new float[X];  
    };
    str_movie=new char[99];  
    str_suface=new char[99];  
    str_nspy=new char[99];  
    str_forwave=new char[99];
    str_id=new char[9];  
    if(source_model==4)
    {strcpy(str_suface,"nspy_suface");
     strcpy(str_movie,"nspy_movie");
     strcpy(str_forwave,"nspy_forwave");
    }
    else
    {strcpy(str_suface,"suface");
     strcpy(str_movie,"movie");
     strcpy(str_forwave,"forwave");
    }
    strcpy(str_nspy,"suface");
    sprintf(str_id, "%f", source_id);
    if(source_id<10)
        str_id[1]='\0';
    else if(source_id>=10 && source_id<100)
        str_id[2]='\0';
    else if(source_id>=100 && source_id<1000)
        str_id[3]='\0';
    else if(source_id>=1000 && source_id<10000)
        str_id[4]='\0';
    strcat(str_movie,str_id);
    strcat(str_suface,str_id);
    strcat(str_forwave,str_id);
    strcat(str_nspy,str_id);
/////////////////////////////////////////////////////////////////  

    /*形成子波*/
     for(k=0;k<T;k++)
        {zbbx[k]=zb(k,DT);}

/*在逆时偏移情况下，读入地表记录*/
     ifstream infile;
    if(source_model==4)
    {infile.open(str_nspy,ios::binary);
     if(!infile) cout<<"error"<<endl;
      for(j=0;j<X;j++)
     {for(i=0;i<T;i++)
      {
      infile.read(( char *)&nspy[i][j],sizeof(nspy[i][j]));  
       }
      }
     infile.close();
    }

    //输入速度模型
      infile.open("model.dat",ios::binary);
      if(!infile) cout<<"error"<<endl;
      for(j=0;j<X;j++)
     {for(i=0;i<Y;i++)
      {
      infile.read(( char *)&p2[i][j],sizeof(p2[i][j]));  
       }
      }
     infile.close();

     float C3=3/2/(xshd)/DX*log(10000000)/(xshd)/DX/(xshd)/DX;
     t5=double(Y)/X;
    
 //////////////////用指针的形式定义动态数组////////////////////////// 
    s1=new float*[Y+20];  
    s2=new float*[Y+20];   
    s3=new float*[Y+20];  
    sx11=new float*[Y+20];    
    sx12=new float*[Y+20];     
    sx13=new float*[Y+20];     
    sx21=new float*[Y+20];     
    sx22=new float*[Y+20];     
    sx23=new float*[Y+20];     
    sx24=new float*[Y+20];     
    sx31=new float*[Y+20];     
    sx32=new float*[Y+20];     
    sx33=new float*[Y+20];     
    for(j=0;j<Y+20;j++)  
    {  
        s1[j]=new float[X+20];  
        s2[j]=new float[X+20]; 
        s3[j]=new float[X+20];  
        sx11[j]=new float[X+20];  
        sx12[j]=new float[X+20];  
        sx13[j]=new float[X+20];  
        sx21[j]=new float[X+20];  
        sx22[j]=new float[X+20];  
        sx23[j]=new float[X+20];  
        sx24[j]=new float[X+20];  
        sx31[j]=new float[X+20];  
        sx32[j]=new float[X+20];  
        sx33[j]=new float[X+20];  
    }

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

///////////////绘制速度模型的声波传播过程（主程序）////////////////////   

       ofstream outf_sufer;
       ofstream outf_forwave;
       ofstream outf_movie;
	    if(out_movie==1)
        {
        outf_movie.open(str_movie);}
        if(out_sufer==1)
        {
        outf_sufer.open(str_suface);}
        if(out_forwave==1)
        {
        outf_forwave.open(str_forwave);}
       
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
           if(source_model==1 && j==yf && i==xf+5 ) 
          {f=zbbx[k];}
           else if(source_model==2 && j==yf)
          {f=zbbx[k];}
           else if(source_model==3 && j>5 && p2[j-5][i-5]!=p2[j-6][i-5])
          {f=zbbx[k];}
           else if(source_model==4 && j==yf)
          {f=nspy[T-k-1][i-5];}
           else
           f=0;

           snx1=0.0;snx2=0.0;
           sny1=0.0;sny2=0.0;
           dx=0;ddx=0;dy=0;ddy=0;
        if(suface_PML==1)
          {if(i>=X-xshd+5 && j<=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)	
	           snx1=i-(X-xshd+5);
           if(i<=xshd+5 && j>=t5*i+5*(1-t5) && j<=-t5*i+Y+5+t5*5)		
	           snx2=xshd+5-i;
           if(j>=Y-xshd+5 && j>=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)		
	           sny1=j-(Y-xshd+5);
           if(j<=xshd+5 && j<=t5*i+5*(1-t5) && j<=-t5*i+Y+5+5*t5)		
	           sny2=xshd+5-j;		
          }  //角落处理问题
        else if(suface_PML==0)
          {if(i>=X-xshd+5 && j<=t5*i+5*(1-t5))	
	           snx1=i-(X-xshd+5);
           if(i<=xshd+5 && j<=-t5*i+Y+5+t5*5)		
	           snx2=xshd+5-i;
           if(j>=Y-xshd+5 && j>=t5*i+5*(1-t5) && j>=-t5*i+Y+5+5*t5)		
	           sny1=j-(Y-xshd+5);
           if(j<=xshd+5)		
	           sny2=0;		
          }

           if(sny1 !=0)
          {dy=p2[j-5][i-5]*C3*sny1*sny1*DY*DY;
	       ddy=p2[j-5][i-5]*C3*2*sny1*DY;	
           }
          if(sny2 !=0)
          {dy=p2[j-5][i-5]*C3*sny2*sny2*DY*DY;
	       ddy=p2[j-5][i-5]*C3*2*sny2*DY;	
           }
          if(snx1 !=0)
          {dx=p2[j-5][i-5]*C3*snx1*snx1*DX*DX;
	       ddx=p2[j-5][i-5]*C3*2*snx1*DX;	
           }
          if(snx2 !=0)
          {dx=p2[j-5][i-5]*C3*snx2*snx2*DX*DX;
	       ddx=p2[j-5][i-5]*C3*2*snx2*DX;	
           }
         if(i>=0.5*(X+5))
           t3=1;
         else
           t3=1;
         if(j>=0.5*(Y+5))
           t4=1;
         else
           t4=1;

        if(snx1!=0 || snx2!=0)
{sx11[j][i]=p2[j-5][i-5]*p2[j-5][i-5]\
*DT*DT*(u2-u*s2[j][i])*(1.0/(DX*DX))\
-dx*dx*DT*DT*sx12[j][i]+(2*sx12[j][i]\
-sx13[j][i])+DT*(2*dx*(sx13[j][i]-sx12[j][i]));

sx21[j][i]=(-p2[j-5][i-5]*p2[j-5][i-5]\
*ddx*(1.0/(DX))*(ux*t3)-dx*dx*dx*sx22[j][i]\
+3*dx*dx*(sx23[j][i]-sx22[j][i])/DT+3*dx*\
(2*sx23[j][i]-sx22[j][i]-sx24[j][i])/(DT*DT)\
+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])\
/(DT*DT*DT))*(DT*DT*DT);

sx31[j][i]=DT*DT*p2[j-5][i-5]*p2[j-5][i-5]\
*(1.0/(DX*DX))*(u1-u*s2[j][i])+2*sx32[j][i]\
-sx33[j][i];}
        else
{sx11[j][i]=p2[j-5][i-5]*p2[j-5][i-5]\
*DT*DT*(u1-u*s2[j][i])*(1.0/(DX*DX))\
-dy*dy*DT*DT*sx12[j][i]+(2*sx12[j][i]\
-sx13[j][i])+DT*(2*dy*(sx13[j][i]-sx12[j][i]));

sx21[j][i]=(-p2[j-5][i-5]*p2[j-5][i-5]\
*ddy*(1.0/(DX))*(uy*t4)-dy*dy*dy*sx22[j][i]\
+3*dy*dy*(sx23[j][i]-sx22[j][i])/DT\
+3*dy*(2*sx23[j][i]-sx22[j][i]-sx24[j][i])\
/(DT*DT)+(3*sx22[j][i]-3*sx23[j][i]+sx24[j][i])\
/(DT*DT*DT))*(DT*DT*DT);

sx31[j][i]=DT*DT*p2[j-5][i-5]*p2[j-5][i-5]\
*(1.0/(DX*DX))*(u2-u*s2[j][i])+2*sx32[j][i]\
-sx33[j][i];}   
              
     // if(snx1!=0 || snx2!=0 || sny1!=0 || sny2!=0)
        s3[j][i]=sx11[j][i]+sx21[j][i]+sx31[j][i]+f;

        if(j==z && out_sufer==1)
        {suface_data[k][i-5]=s3[j][i];}

        if(k==t2 && out_forwave==1)
        {outf_forwave.write((char*)&s3[j][i],sizeof(s3[j][i]));
         }
        if(out_movie==1)
        {outf_movie.write((char*)&s3[j][i],sizeof(s3[j][i]));}
      
         u1=0,u2=0,u=0,ux=0,uy=0;
        }
       }
          for(j1=0;j1<Y+20;j1++)
         {for(i1=0;i1<X+20;i1++)
         {s1[j1][i1]=s2[j1][i1];s2[j1][i1]=s3[j1][i1];
          sx13[j1][i1]=sx12[j1][i1],sx12[j1][i1]=sx11[j1][i1];
          sx33[j1][i1]=sx32[j1][i1],sx32[j1][i1]=sx31[j1][i1];
          sx24[j1][i1]=sx23[j1][i1],sx23[j1][i1]=sx22[j1][i1],\
          sx22[j1][i1]=sx21[j1][i1];
        }
          }
        if((k%100)==0)
          cout<<k<<endl;
       }
        if(out_sufer==1)
        {for(i=0;i<X;i++)
            {for(j=0;j<T;j++)
                {outf_sufer.write((char*)&suface_data[j][i],\
                 sizeof(suface_data[j][i]));
                }
            }
         }

	    if(out_movie==1)
        {
        outf_movie.close();}
        if(out_sufer==1)
        {
        outf_sufer.close();}
        if(out_forwave==1)
        {
        outf_forwave.close();}
   
 /////////////////////释放内存///////////////////////////////////////////  
    delete []zbbx;

    for(int i=0;i<T;i++)  
      {delete []suface_data[i];
       delete []nspy[i];
      }
    delete []suface_data;
    delete []nspy;

    for(int i=0;i<Y;i++)  
        delete []p2[i]; 
    delete []p2;

    for(int i=0;i<Y+20;i++)  
       {delete []s1[i];
        delete []s2[i];
        delete []s3[i];
        delete []sx11[i];
        delete []sx12[i];
        delete []sx13[i];
        delete []sx21[i];
        delete []sx22[i];
        delete []sx23[i];
        delete []sx24[i];
        delete []sx31[i];
        delete []sx32[i];
        delete []sx33[i];
       }//先单独释放第一维中每个数组的内存  
    delete []s1;
    delete []s2;
    delete []s3;
    delete []sx11;
    delete []sx12;
    delete []sx13;
    delete []sx21;
    delete []sx22;
    delete []sx23;
    delete []sx24;
    delete []sx31;
    delete []sx32;
    delete []sx33;

/////////////////////////////////////////////////////////////////////

cout<<endl<<"finished"<<endl;
return(0);
}

