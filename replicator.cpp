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
	go(point a ){
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
	
	rotate(point centre, double angle ){
    angle *= M_PI / 180.0;
    double xM = x - centre.x;
    double yM = y - centre.y;
    x = xM * cos(angle) + yM * sin(angle) + centre.x;
    y = - xM * sin(angle) + yM * cos(angle) + centre.y;
	}
	
	translate(double tx,double ty ){
    x = x + tx;
    y = y + ty;
	}
	
	point jump(double jx,double jy ){
	point t(x,y) ;
    t.x = t.x + jx;
    t.y = t.y + jy;
	return t;
	}

} ;

point tete;
double z;
ofstream file;
double nw = 0.4;
double taux = 0.1;
double dia = 1.75;

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

void squarefill(){
	vector<point> poly ;
	poly.push_back(point(50,50));
	poly.push_back(point(50,60));
	poly.push_back(point(60,60));
	poly.push_back(point(60,50));
	double minx ;
	double maxx ;
	double miny ;
	double maxy ;
	double y = 50;
	vector<point> fill ;
	point p(50,50);
	double m = 0;
	fill.push_back(p);
	int tour = 0 ;
	while(y<=60){
		//point tmp;
		if(tour%2==1){
			point l =p.jump(0,nw);
			point m =l.jump(-10,0);
			fill.push_back(l);
			fill.push_back(m);
			p = m.jump(0,0);
			}
		else{
			point l =p.jump(0,nw);
			point m =l.jump(10,0);
			fill.push_back(l);
			fill.push_back(m);
			p = m.jump(0,0);
			}
		
		fill.push_back(p);
		tour = (tour +1)%2;
		y = y+nw;
	}
	
	polygnon(poly);
	polygnon(fill);
	
}

void squarefill2(){
	vector<point> poly ;
	poly.push_back(point(50,50));
	poly.push_back(point(50,60));
	poly.push_back(point(60,60));
	poly.push_back(point(60,50));
	double minx ;
	double maxx ;
	double miny ;
	double maxy ;
	double y = 50;
	vector<point> fill ;
	point p(50,50);
	double m = 0;
	fill.push_back(p);
	int tour = 0 ;
	while(y<=60){
		//point tmp;
		if(tour%2==1){
			point l =p.jump(0,0.2);
			point m =l.jump(-10,0);
			fill.push_back(l);
			fill.push_back(m);
			p = m.jump(0,0);
			}
		else{
			point l =p.jump(0,0.2);
			point m =l.jump(10,0);
			fill.push_back(l);
			fill.push_back(m);
			p = m.jump(0,0);
			}
		
		
		//fill.push_back(p);
		tour = (tour +1)%2;
		y = y+0.2;
	}
	
	for(int i = 0 ; i < fill.size(); i++){
		fill[i].rotate(point(50,50),90);
		fill[i].translate(0,10);
	}
	
	polygnon(poly);
	polygnon(fill);
	
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
	
	move(bord);
	
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




int main(){
srand (time(NULL));
	file.open("square.gcode");
	tete.x = 0;
	tete.y = 0;
	//header
	file<<"G21"<<endl;
	file<<"G90"<<endl;
	file<<"G28"<<endl;
	
	//move(point(50,50));
	//move(point(60,60));
	//line(point(50,50),point(60,60));
	
	// rand() % 10 + 1; rand(50,60)
	//vector<point> poly {point(50,50),point(50,60),point(60,60),point(60,50)};
	//{point(rand(50,60),rand(50,60)),point(rand(50,60),rand(50,60)),point(rand(50,60),rand(50,60)),point(rand(50,60),rand(50,60))};
	//for(int i = 0 ; i < 5 ; i++)
		//poly.push_back(point(rand(50,60),rand(50,60)));
		/*
	poly.push_back(point(50,50));
	poly.push_back(point(55,60));
	poly.push_back(point(60,50));
	poly.push_back(point(50,55));
	poly.push_back(point(60,55));
	poly.push_back(point(50,50));	
	*/
	vector<point> poly ;
	poly.push_back(point(50,50));
	poly.push_back(point(50,60));
	poly.push_back(point(60,60));
	poly.push_back(point(60,50));
	
	for(int i = 0; i < 4 ; i++){
		poly[i].rotate(point(50,50),0);
	}
	
	//poly
	//squarefill();
	int tmp = 0 ;
	//cercledelenfer(point(50.0,50.0),10.0);
	for(double i = 0 ; i < 50 ;i++){

		
		z = i*taux;
		//cercle(point(50.0,50.0),10.0);
		//cercle(point(50.0,50.0),10.0);
		//cercledelenfer(point(50.0,50.0),10.0);
		//polygnon(poly);
		if(tmp == 0){
		squarefill();
		}else{
			
		squarefill2();
		}
		tmp = (tmp +1)%2;
	}
	//code
	//line(point(50,50),point(60,60));
	//fin code
	
	
	file.close();
	return 0;
	
}
