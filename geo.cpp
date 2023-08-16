#include<iostream>
#include<math.h>

#include <pybind11/pybind11.h>
// namespace py=pybind11::literals;
namespace py =pybind11;
using namespace std;
void spilt(std::string &, double *,double*);
py::tuple geo_split(std::string & f){
    double lt,ln;
    split(f,&lt,&ln);
    return py::make_tuple(lt,ln);
}
void split(std::string & a,double *x,double * y){
    bool ew=false;
    *x=1.0;
    *y=1.0;
    char lt[12],ln[12];
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
            if (ew){
                *pt1=i;pt1++;
            }
            else{
                *pt2=i;pt2++;
            }
        }
        
    }
    *pt1='\0';*pt2='\0';
    // cout<<atof(lt)<<"############# "<<ln;
    *x*=atof(lt);
    *y*=atof(ln);
}

double distance(double a1,double b1,double a2,double b2){
    return abs(a1-a2)+abs(b1-b2);
}

PYBIND11_MODULE(geo, m) {
    m.doc() = "geo package"; // optional module docstring

    m.def("geo_split", &geo_split, "convet string to tuple");
}

// int main(){
//     double a1,b1,a2,b2;
//     std::string f1 ="12.345, -45.455";
//     std::string f2 ="N12.345E15.455";
//     split(f1,&a1,&b1);
//     split(f2,&a2,&b2);
//     std::cout<<a1<<" "<<b1<<" "<<distance(a1,b1,a2,b2);
    
//     return 0;

// }