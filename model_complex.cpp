
//输出地下速度模型

#include <iostream>
#include <stdio.h>
#include <fstream>
#include<iomanip>
#include<cmath>
using namespace std;
float p[801][200];
int main()
{while(1)
{ofstream outf;
outf.open("complex.txt");
double pi=3.1415926;
int i,j,k,n,i1,j1;
   
for(i=0;i<801;i++)
  {for(j=0;j<200;j++)
    {  	
       p[i][j]=3000;
        if (j>80+20*sin(2*pi*i/800))
            p[i][j]=3500;
        
        if (j>130+10*sin(2*pi*i/800))
            p[i][j]=4000;
        
        if (j>160)
            p[i][j]=4500;
        

     }
   }
     

 for(j=0;j<801;j++)
   {for(i=0;i<200;i++)
      {
         outf<<p[j][i]<<" ";
       }
         outf<<endl;
    }

outf.close(); 
cout<<"finished"<<endl;
cin>>n;
if(n!=68768776)
break;
}
return (0);
}
