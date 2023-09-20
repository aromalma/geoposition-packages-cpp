#include<iostream>
#include<math.h>
#include<array>
#include<vector>
#define PI 3.141592
#include <pybind11/pybind11.h>
#include<pybind11/stl.h>
#include "utils.h"

namespace py =pybind11;
// using namespace std;


class query{
    public:
    std::vector<std::array<double, 2>> mas;
    query(const py::list & abc){
      
        for( auto &i:abc){
            std::array<double,2> a;
            std::string v =py::cast<std::string >(i);
            split(v,&a[0],&a[1]);
            this->mas.push_back(a);
        }
    }
    py::tuple nearest(std::string & a){
        double lt,ln,t;
        int ind=0,count=0;
        split(a,&lt,&ln);
        double min=10000;
        // for (int i=0;i<this->mas.size();i++){
        for(auto &i:this->mas){
            t=distance(i[0],i[1],lt,ln);
            // std::cout<<t<<" ";
            if (t<min){min=t;ind=count;}
            count++;
        }
        // std::cout<<(this->mas[0][0])<<" ";
        return py::make_tuple(ind,this->mas[ind][0],this->mas[ind][1]);
    }
    py::list cumil(){
        double d;
        std::vector<double> a((int)this->mas.size(),0);
        for (int i=0;i<(int)this->mas.size()-1;i++){
            d = distance(this->mas[i][0],this->mas[i][1],this->mas[i+1][0],this->mas[i+1][1]);
            a[i+1]=d+a[i];
        }
        return py::cast(a);
    }
};




py::tuple geo_split(std::string & f){
    double lt,ln;
    split(f,&lt,&ln);
    return py::make_tuple(lt,ln);
}


PYBIND11_MODULE(geo, m) {
    m.doc() = "geo package"; // optional module docstring

    m.def("geo_split", &geo_split, "convet string to tuple");
    m.def("calculateDistance",&calculateDistance,"distance in km");
    // m.def("mas",&mas);
    py::class_<query>(m,"query")
        .def(py::init<py::list>())
        .def("nearest",&query::nearest)
        .def("cumil",&query::cumil);
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
