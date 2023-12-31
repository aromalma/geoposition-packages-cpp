#include<iostream>
#include<math.h>
#include<array>
#include<vector>
#include<pybind11/stl.h>
#define PI 3.141592
//#define
#include <pybind11/pybind11.h>


namespace py =pybind11;
// using namespace std;

void split(std::string &, float *,float*);
float dmstodd(char *);
float distance(float a1,float b1,float a2,float b2){
    // return abs(a1-a2)+abs(b1-b2);
    float da,db,c;
    a1*=(PI/180);
    a2*=(PI/180);
    b1*=(PI/180);
    b2*=(PI/180);
    da=abs(a1-a2);
    db=abs(b1-b2);
    c =pow(sin(da/2),2)+cos(a1)*cos(a2) * pow(sin(db/2),2);
    // c=2*asin(sqrt(c))*6371;
    c=2*atan2(sqrt(c),sqrt(1-c))*3;

    // std::cout<<c;
    return c;

}
float calculateDistance(std::string &v1, std::string &v2){
    float a1,b1,a2,b2;
    split(v1,&a1,&b1);split(v2,&a2,&b2);
    return distance(a1,b1,a2,b2);
}
class query{
    public:
    std::vector<std::array<float, 2>> mas;
    query(const py::list & abc){
        ;
        for( auto &i:abc){
            std::array<float,2> a;
            std::string v =py::cast<std::string >(i);
            split(v,&a[0],&a[1]);
            this->mas.push_back(a);
        }
    }
    py::tuple nearest(std::string & a){
        float lt,ln,t;
        int ind=0,count=0;
        split(a,&lt,&ln);
        float min=10000;
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
        float d;
        std::vector<float> a((int)this->mas.size(),0);
        for (int i=0;i<(int)this->mas.size()-1;i++){
           d = distance(this->mas[i][0],this->mas[i][1],this->mas[i+1][0],this->mas[i+1][1]);
           a[i+1]=d+a[i];
        }
        return py::cast(a);
    }
};


// void mas(py::list & abc){
//     abc.append(2);
//     // std::cout<<abc[0];
//     for( auto &i:abc){
//         py::cast<int>(i);
//         }

// }



py::tuple geo_split(std::string & f){
    float lt,ln;
    split(f,&lt,&ln);
    return py::make_tuple(lt,ln);
}
float dmstodd(char *a){
    float t[3];
    int j=0,k=0;
    char temp[8];
    for(int i=0; a[i]!='\0'; i++,j++){
        if (a[i]!='.' || k>1){temp[j]=a[i];}
        else {
            temp[j]='\0';
            t[k]=atof(temp);
            k++;j=-1;
        }
    }
    temp[j]='\0';
    t[k]=atof(temp);
    return t[0]+t[1]/60+t[2]/3600;
}
void split(std::string & a,float *x,float * y){
    bool ew=false;
    int dms=0;
    *x=1.0;
    *y=1.0;
    char lt[16],ln[16];
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
//     float a1,b1,a2,b2;
//     std::string f1 ="12.345, -45.455";
//     std::string f2 ="N12.345E15.455";
//     split(f1,&a1,&b1);
//     split(f2,&a2,&b2);
//     std::cout<<a1<<" "<<b1<<" "<<distance(a1,b1,a2,b2);
    
//     return 0;

// }