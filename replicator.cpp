#include <iostream>
#include <fstream>
#include <cmath>
#include <vector> 
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>  
using namespace std; 
ofstream file;
class point {
  public :
  	int x;
  	int y;
	point(int a , int b){
	x=a;
	y=b;
	};
	point(){
	x=0;
	y=0;
	};
	go(point a ){
	x=a.x;
	y=a.y;
	}

} ;

point tete;
double z;
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
	file<<"G1 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" E1.0 F1200"<<endl;
	file<<"G92 E0.0"<<endl;
}

void square(){
}

void polygnon(vector<point> poly){
	int i = 0;
	int tmp = 0;
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
	vector<point> poly ;//{point(rand(50,60),rand(50,60)),point(rand(50,60),rand(50,60)),point(rand(50,60),rand(50,60)),point(rand(50,60),rand(50,60))};
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
	poly.push_back(point(50,50));
	poly.push_back(point(50,60));
	poly.push_back(point(60,60));
	poly.push_back(point(60,50));
	
	//poly
	
	for(double i = 0 ; i < 50 ;i++){
		z = i*0.2;
		polygnon(poly);
	}
	//code
	//line(point(50,50),point(60,60));
	//fin code
	
	
	file.close();
	return 0;
	
}
