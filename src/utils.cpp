#include <iostream>
#include "utils.h"
#define PI 3.141592
#include<math.h>
#include<array>
#include<vector>
// #include <pybind11/pybind11.h>
// #include<pybind11/stl.h>
// namespace py =pybind11;


double distance(double a1,double b1,double a2,double b2){
    // return abs(a1-a2)+abs(b1-b2);
    double da,db,c;
    a1*=(PI/180);
    a2*=(PI/180);
    b1*=(PI/180);
    b2*=(PI/180);
    da=a1-a2;
    db=b1-b2;
    c =pow(sin(da/2),2)+cos(a1)*cos(a2) * pow(sin(db/2),2);
    c=2*atan2(sqrt(c),sqrt(1-c))*6371;
    // std::cout<<c;
    return c;

}

double calculateDistance(std::string &v1, std::string &v2){
    double a1,b1,a2,b2;
    split(v1,&a1,&b1);split(v2,&a2,&b2);
    return distance(a1,b1,a2,b2);
}

double dmstodd(char *a){
    double t[3],sign=1.0;
    int j=0,k=0,i=0;
    char temp[8];
    if (a[0]=='-'){sign=-1.0;i=1;}
    for(; a[i]!='\0'; i++,j++){
        if (a[i]!='.' || k>1){temp[j]=a[i];}
        else {
            temp[j]='\0';
            t[k]=atof(temp);
            k++;j=-1;
        }
    }
    temp[j]='\0';
    t[k]=atof(temp);
    return (t[0]+t[1]/60+t[2]/3600)*sign;
}
void split(std::string & a,double *x,double * y){
    bool ew=false;
    int dms=0;
    *x=1.0;
    *y=1.0;
    char lt[32],ln[32];
    char *pt1=ln;
    char *pt2=lt;
    for(char &i: a){
        if (i=='N' || i=='n'){}
        else if (i=='S' || i=='s'){*x=-1.0;}
        else if (i=='E' || i=='e'){ew=true;}
        else if (i=='W' || i=='w'){*y=-1.0;ew=true;}
        else if (i==','){ew=true;}
        else if (i==' '){}
        else{
            if (i=='.'){dms++;}
            if (ew){
                *pt1=i;pt1++;
            }
            else{
                *pt2=i;pt2++;
            }
        }
        
    }
    *pt1='\0';*pt2='\0';
    if (dms <3){
        *x*=atof(lt);
        *y*=atof(ln);
    }
    else{
        *x*=dmstodd(lt);
        *y*=dmstodd(ln);
    }
    *x=round(*x * 1000000)/1000000;
    *y=round(*y * 1000000)/1000000;
}