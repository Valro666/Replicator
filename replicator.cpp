#include <iostream>
#include <fstream>
#include <cmath>
#include <vector> 
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>  
using namespace std; 
class point {
  public :
  	double x;
  	double y;
	point(double a , double b){
	x=a;
	y=b;
	};
	point(){
	x=0.0;
	y=0.0;
	};
	void go(point a ){
	x=a.x;
	y=a.y;
	}
	
	double dist(point a ){
	//x=a.x;
	//y=a.y;
	double xx = a.x-x;
	double yy = a.y-y;
	xx = xx*xx;
	yy =yy*yy;
	
	double res = xx+yy;
	res = sqrt(res);
	
	return res;
	}
	
	void rotate(point centre, double angle ){
    angle *= M_PI / 180.0;
    double xM = x - centre.x;
    double yM = y - centre.y;
    x = xM * cos(angle) + yM * sin(angle) + centre.x;
    y = - xM * sin(angle) + yM * cos(angle) + centre.y;
	}
	
	void translate(double tx,double ty ){
    x = x + tx;
    y = y + ty;
	}
	
    bool equals(point b){
    if(b.x==x){
        if(b.y==y){
            return true;
        } 
    } 
    return true;
	}
	
	point jump(double jx,double jy ){
	point t(x,y) ;
    t.x = t.x + jx;
    t.y = t.y + jy;
	return t;
	}
	
    point duplicate(){
	point t(x,y) ;
	return t;
	}

} ;

class shape {
	public : 
	vector<point> vertices;
	
	void inverse();
    
	void add(point a){
		vertices.push_back(a);
	}
	
	void rotate(point centre, double angle ){
        for(int i = 0 ;i < vertices.size();i++){
            vertices[i].rotate(centre,angle);
        }
    };
    
    void translate(double tx,double ty ){
        for(int i = 0 ;i < vertices.size();i++){
            vertices[i].translate(tx,ty);
        }
    };
    
    shape duplicate(){
        shape s;
        for(int i = 0 ;i < vertices.size();i++){
            s.add(vertices[i].duplicate());
        }
    };
    
    void melt(point a){
        shape s;
        for(int i = 0 ;i < vertices.size();i++){
        //    printf("molp");
            if(!vertices[0].equals(a)){
                point a = vertices[0].duplicate();
                vertices.erase(vertices.begin(),vertices.begin()+1);
                vertices.push_back(a);
            }
        }
      //  printf("mmpolohtcxd");
    };
    
    void fusion(shape s){
        
        
        
        point p =s.vertices[0];
        double d = vertices[0].dist(s.vertices[0]) ;
        //for(int i = 0 ;i < vertices.size();i++){
                    for(int j = 0 ;j < s.vertices.size();j++){
    //                    printf("azerty");
                        if(d>vertices[vertices.size()].dist(s.vertices[j])){
                            d = vertices[vertices.size()].dist(s.vertices[j]) ;
                            p = s.vertices[j];
                        }
                }
  //              printf("nji");
        s.melt(p);
//        printf("fghjklm");
        
                    for(int j = 0 ;j < s.vertices.size();j++){
                        //printf("azertyyyyyyyyyyyyy");
                        vertices.push_back(s.vertices[j]);
                        //printf("azeeeeeeeeeeeeeeeee");
                        }     
        //}
    };
    
    void dellast(){
        vertices.pop_back();
    };
    
    int size(){
        return vertices.size();
    };
};

point tete;
double z;
ofstream file;
double nw = 0.4;
double taux = 0.1;
double dia = 1.75;
void polygnon(vector<point> poly);
void polygnon(shape s);

double extrud(double dist){
	
	double vt = nw * taux * dist;
	double p = M_PI*(dia*dia)/4.0;
	
	return vt/p;
}

void polygnon(vector<point> poly);
double rand(double a, double b){
	return (rand()/(double) RAND_MAX*(b-a))+a;
}

void move(point a){
	tete.go(a);
	file<<"G0 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" F3000"<<endl;
}

void line(point a , point b){
	move(a);
	tete.go(b);
	//file<<"G1 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" E1.0 F1200"<<endl;
	file<<"G1 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" E"<< extrud(a.dist(b))<<" F1200"<<endl;
	file<<"G92 E0.0"<<endl;
}

shape squarefill(){
	double minx ;
	double maxx ;
	double miny ;
	double maxy ;
	//double y = 50;
	shape fill ;

	
	double m = 0;
	//fill.add(p);
	int tour = 0 ;
    
    double pour = 5;
    double bid = 0.2;
    //double nn = extrud(bid)*M_PI*bid*bid*0.25;
    double nn = 0.5;
    point p(50,50);
    //p.translate(0.0,0.2);
    double y = 50;
    p.translate(0.0,nn);
    fill.add(p.duplicate());
	while(y<60-nn){

        point t = p.duplicate();
		if(tour%2==1){
            t = p.duplicate();
            t.translate(-(10.0-nn-nn),0.0);
            //p = m.jump(0,0);
			}
		else{
            t = p.duplicate();
            t.translate(10.0-nn-nn,0.0);
			//p = m.jump(0,0);
			}
        fill.add(t);
        p = t.duplicate();
		//fill.add(p);
        p.translate(0.0,nn);
        fill.add(p.duplicate());
		tour = (tour +1)%2;
		y = y+nn;
	}
	
	//fill.dellast();
	fill.translate(nn,0.0);
	return fill;
	//polygnon(poly);
	//polygnon(fill);
	
}

shape square(){
	shape poly ;
	poly.add(point(50,50));
	poly.add(point(50,60));
	poly.add(point(60,60));
	poly.add(point(60,50));
    poly.add(point(50,50));
    return poly;
}

//G2 X Y I J E : XY centre IJ bord

void cercledelenfer(point centre , double bord){
	move(centre);
	
	vector<point> poly ;
	//poly.push_back(centre);
	//tete.go(b);
	//file<<"G1 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" E1.0 F1200"<<endl;
	//file<<"G1 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" E"<< extrud(a.dist(b))<<" F1200"<<endl;
	
	//file<<"G2 X"<<tete.x<<" Y"<<tete.y<<" I"<<bord<<" J"<<0.0<<" Z"<<z<<" E"<< extrud(2*M_PI*(bord))<<" F1200"<<endl;
	
	//file << "G2 X90.6 Y13.8 I5 J10 E22.4" << endl;
	
	//move(bord);
	
	double diametre = 2.0*M_PI*(bord);
	
	double x = centre.x+bord;
	
	//move(bord);
	
	for(double i = 0.0; i < 360 ; i = i+0.1){
		point p = centre.jump(0.0,0.0);
		p.translate(bord,0.0);
		p.rotate(centre,i);
		poly.push_back(p);
		
	}
	
	polygnon(poly);
	
	file<<"G92 E0.0"<<endl;
}

void polygnon(vector<point> poly){
	int i = 0;
	double tmp = 0;
	move(poly[0]);
	for(i = 0 ; i < poly.size(); i++){
		tmp = (i+1)%poly.size();
		line(poly[i],poly[tmp]);
	//	cout << i<<endl;
	}
}

void polygnon(shape s){
	int i = 0;
	double tmp = 0;
	vector<point> poly = s.vertices;
	move(poly[0]);
	for(i = 1 ; i < poly.size(); i++){
		tmp = (i-1);
		line(poly[tmp],poly[i]);
	//	cout << i<<endl;
	}
}




int main(){
srand (time(NULL));
	file.open("square.gcode");
	tete.x = 0;
	tete.y = 0;
	//header
	file<<"G21"<<endl;
	file<<"G90"<<endl;
	file<<"G28"<<endl;
	
    shape s = square();
    shape f = squarefill();
    
   // printf("fghjkl");
    
    s.fusion(f);

	int tmp = 0 ;
	for(double i = 0 ; i < 50 ;i++){

		
		z = i*taux;

        polygnon(s);
		/*if(tmp == 0){
		//squarefill();
            //polygnon(f);
		}else{
			//polygnon(f);
		//squarefill2();
		}*/
        
        
        
		//polygnon(f);
        s.rotate(point(50.0,50.0),90.0);
        s.translate(0.0,10.0);//*/
		tmp = (tmp +1)%2;
	}
	//code

	
	
	file.close();
	return 0;
	
}
