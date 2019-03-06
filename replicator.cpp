#include <iostream>
#include <fstream>
#include <cmath>
#include "poly.h"
using namespace std;

point tete;
double z;  //hauteur tete
ofstream file;
double nw = 0.4; //diametre sortie
double taux = 0.2;  // layer
double dia = 1.75;  //
double nn = 0.5; //

void polygnon(vector<point> poly);
void polygnon(shape s);
void endFunc();
void header();
shape fillShapeX(shape sh);
shape fillShapeY(shape sh);
double extrud(double dist) {
	double vt = nw * taux * dist;
	double p = M_PI * (dia * dia) / 4.0;
	return vt / p;
}

void polygnon(vector<point> poly);
double rand(double a, double b) {
	return (rand() / (double) RAND_MAX * (b - a)) + a;
}

void move(point a) {
	tete.go(a);
	file << "G0 X" <<  tete.x << " Y" <<  tete.y << " Z" <<  z << " F3000" << endl;
}

void line(point a , point b) {
	move(a);
	tete.go(b);
	double d = a.dist(b);
	double ex = extrud(d);
	file << "G1 X" <<  tete.x << " Y" <<  tete.y << " Z" << z << " E" <<  ex << " F1200" << endl;
	file << "G92 E0.0" << endl;
}

shape squarefill() {

	shape fill ;
	double m = 0;
	int tour = 0 ;
	double pour = 5;
	point p(50, 50);
	double y = 50;
	p.translate(0.0, nn);

	fill.add(p.duplicate());
	while (y < 60 - nn) {

		point t = p.duplicate();
		if (tour % 2 == 1) {
			t = p.duplicate();
			t.translate(-(10.0 - nn - nn), 0.0);
		}
		else {
			t = p.duplicate();
			t.translate(10.0 - nn - nn, 0.0);
		}
		fill.add(t);
		p = t.duplicate();
		p.translate(0.0, nn);
		fill.add(p.duplicate());
		tour = (tour + 1) % 2;
		y = y + nn;
	}
	fill.translate(nn, 0.0);
	return fill;
}

shape square() {
	shape poly ;
	poly.add(point(50, 50));
	poly.add(point(50, 60));
	poly.add(point(60, 60));
	poly.add(point(60, 50));
	poly.add(point(50, 50));
	return poly;
}

shape cercledelenfer(point centre , double bord, double nb) {

	shape s ;
	double diametre = 2.0 * M_PI * (bord);
	double x = centre.x + bord;
	double to = 360 / nb;

	for (double i = 0.0; abs(i) < 360 ; i = i + to) {
		point p = centre.jump(0.0, 0.0);
		p.translate(bord, 0.0);
		p.rotate(centre, i);
		s.add(p);
	}

	point p = centre.jump(0.0, 0.0);
	p.translate(bord, 0.0);
	p.rotate(centre, 360);

	if (!s.vertices[0].equals(s.vertices[s.size()]))
		s.add(s.vertices[0].duplicate());
	return s;
}
shape formconv() {
	shape s ;
	s.add(point(50, 50));
	s.add(point(50, 70));
	s.add(point(80, 100));
	s.add(point(100, 100));
	s.add(point(100, 80));
	s.add(point(50, 50));
	return s;
}

void affshape(shape sh) {
	for(int i = 0 ; i < sh.size()-1; i++){
		printf("%f,%f -> %f,%f\n",sh.vertices[i].x,sh.vertices[i].y,sh.vertices[i+1].x,sh.vertices[i+1].y);
	}
}

shape cercledelenferfill(point centre , double bord, double nb) {
	shape s ;
	double to = nn;
	for (double i = bord ; i > 0 ; i = i - to) {
		shape tmp = cercledelenfer( centre ,  i,  nb);
		s.concat(tmp);
	}
	return s;
}

shape cercledelenferfill(point centre , double bord, double nb, double sens) {
	shape s ;
	double to = nw;
	if (sens == 1) {
		for (double i = bord ; i > 0 ; i = i - to) {
			shape tmp = cercledelenfer( centre ,  i,  nb);
			s.concat(tmp);
		}
	} else {
		for (double i = to ; i <= bord ; i = i + to) {
			shape tmp = cercledelenfer( centre ,  i,  nb);
			s.concat(tmp);
		}
	}
	return s;
}

void polygnon(vector<point> poly) {
	int i = 0;
	double tmp = 0;
	move(poly[0]);
	for (i = 0 ; i < poly.size(); i++) {
		tmp = (i + 1) % poly.size();
		line(poly[i], poly[tmp]);
	}
}

void polygnonOld(shape s) {
	int i = 0;
	double tmp = 0;
	vector<point> poly = s.vertices;
	move(poly[2]);
	for (i = 2 ; i < poly.size(); i++) {
		tmp = (i - 1);
		line(poly[tmp], poly[i]);
	}
}

void polygnon(shape s) {
	int i = 0;
	double tmp = 0;
	vector<point> poly = s.vertices;
	move(s.vertices[0]);
	for (i = 0 ; i < poly.size()-1; i++) {
		line(s.vertices[i],s.vertices[i+1]);
	}
}


void cube() {
	file.open("cube.gcode");
	tete.x = 0;
	tete.y = 0;
	//header
	header();
	shape s = square();
	shape f = squarefill();
	s.fusion(f);
	int tmp = 0 ;
	double taille = 10 / taux;
	for (double i = 1 ; i < taille ; i++) {
		z = i * taux;
		polygnon(s);
		s.rotate(point(50.0, 50.0), 90.0);
		s.translate(0.0, 10.0); //*/
		tmp = (tmp + 1) % 2;
	}
	endFunc();
	file.close();
}

void cube2() {
	file.open("cubeV2.gcode");
	tete.x = 0;
	tete.y = 0;
	//header
	header();

	shape s = square();
	shape sx = fillShapeX(s);
	shape sy = fillShapeY(s);

	int cloche = -1;
	int tmp = 0 ;
	double taille = 10 ;

	for (double i = taux ; i < taille ; i = i + taux) {
		z=i;
		polygnon(s);
		if(cloche == -1){
			polygnon(sx);
			cloche = -1 * cloche; 
		}else{
			polygnon(sy);
			cloche = -1 * cloche;
		}
		tmp = (tmp + 1) % 2;
	}
	endFunc();
	file.close();
}

void cylindreold() {
	file.open("cylindre.gcode");
	header();
	tete.x = 0;
	tete.y = 0;
	//header
	double discret = 30 ;
	shape vint = cercledelenferfill(point(50, 50), 4, discret, 0);
	shape vext = cercledelenferfill(point(50, 50), 4, discret, 1);

	int tmp = 0 ;
	double taille = 10 / taux;
	for (double i = 1 ; i < taille ; i++) {
		z = i * taux;
		if (tmp == 0) {
			polygnon(vint);
		} else {
			polygnon(vext);
		}
		tmp = (tmp + 1) % 2;
	}
	endFunc();
	file.close();
}
void cylindre() {
	file.open("cylindre.gcode");
	header();
	tete.x = 0;
	tete.y = 0;
	//header

	double discret = 30 ;
	shape vint = cercledelenferfill(point(50, 50), 4, discret, 0);
	shape vext = cercledelenferfill(point(50, 50), 4, discret, 1);

	int tmp = 0 ;
	double taille = 8;
	for (double i = taux ; i < taille ; i = i + taux) {
		z = i;
		if (tmp == 0) {
			polygnon(vint);
		} else {
			polygnon(vext);
		}
		tmp = (tmp + 1) % 2;
	}
	endFunc();
	file.close();
}

shape fillShapeX(shape sh) {
	shape s ;

	point minX =  sh.minX();
	point maxX = sh.maxX();
	point maxY = sh.maxY();
	point minY = sh.minY();
	point first = point(0, 0);
	point last = point(0, 0);
	int tr = 0 ;

	for (double y = minY.y; y < maxY.y; y = y + nw  ) {
		bool start = true;
		if ((tr % 2) == 0) {
			for (double x = minX.x - 1; x < maxX.x + 1; x = x + 0.01  ) {
				if (start) {
					if (sh.inside(point(x, y))) {
						first = point(x + nw, y);
						start = false;
					}
				}
				if (sh.inside(point(x, y))) {
					last = point(x - nw, y);
				}
			}
		} else {
			for (double x = maxX.x + 1; x > minX.x - 1; x = x - 0.01  ) {
				if (start) {
					if (sh.inside(point(x, y))) {
						first = point(x - nw, y);
						start = false;
					}
				}
				if (sh.inside(point(x, y))) {
					last = point(x + nw, y);
				}
			}
		}
		if (!first.equals(last)) {
			if(first.y == last.y){
				s.add(first);
				s.add(last);
			}
		}
		tr ++;
	}
	return s;
}

shape fillShapeY(shape sh) {
	shape s ;

	point minX =  sh.minX();
	point maxX = sh.maxX();
	point maxY = sh.maxY();
	point minY = sh.minY();
	point first = point(0, 0);
	point last = point(0, 0);
	int tr = 0 ;

	for (double x = minX.x+nw; x < maxX.x-nw; x = x + nw  ) {
		bool start = true;
		if ((tr % 2) == 0) {
			for (double y = minY.y-1; y < maxY.y+1; y = y + 0.01  ) {	
				if (start) {
					if (sh.inside(point(x, y))) {
						first = point(x , y+nw);
						start = false;
					}
				}
				if (sh.inside(point(x, y))) {
					last = point(x , y-nw);
				}
			}
		} else {
			for (double y = maxY.y+1 ; y > minY.y-1 ; y = y - 0.01  ) {
				if (start) {
					if (sh.inside(point(x, y))) {
						first = point(x , y-nw);
						start = false;
					}
				}
				if (sh.inside(point(x, y))) {
					last = point(x , y+nw);
				}
			}
		}
		if (!first.equals(last)) {

			if(first.x == last.x){
				s.add(first);
				s.add(last);
			}
		}
		tr ++;
	}
	return s;
}

void tricercle(double rayon = 20) {
	shape ext = cercledelenfer(point(50, 50), rayon, rayon * 4);
	shape int1 = cercledelenfer(point(50, 50), rayon-nw, rayon * 4);
	shape int2 = cercledelenfer(point(50, 50), rayon-nw-nw, rayon * 4);
	shape ss = fillShapeX(int2);
	polygnon(ext);
	polygnon(int1);
	polygnon(int2);
	polygnon(ss);
}

void grille(shape s,double a,double b) {
	for(double x = 0 ; x < 10; x = x + 2*nw){
	}
}

void hemiv() {

	file.open("hemi.gcode");
	header();
	tete.x = 0;
	tete.y = 0;
	//header
	file << "G21" << endl;
	file << "G90" << endl;
	file << "G28" << endl;
	//head();
	double rayon = 20;
	double taille = 20;

	for (double i = taux ; i <= taille ; i = i + taux) {
		z = i;
		double comp =  i;
		double r = sqrt((rayon * rayon) - (comp * comp));
		if (r > nw)
			tricercle(r);
	}
	endFunc();
}

void puzzle() {

	file.open("hemi.gcode");
	header();
	tete.x = 0;
	tete.y = 0;
	//header
	shape s = square();
	file << "G21" << endl;
	file << "G90" << endl;
	file << "G28" << endl;
	//head();
	double rayon = 20;
	double taille = 20;

	for (double i = taux ; i <= taille ; i = i + taux) {
		z = i;
		double comp =  i;
		grille(s,0,0);
		double r = sqrt((rayon * rayon) - (comp * comp));
		if (r > nw)
			tricercle(r);
	}
	endFunc();
}

void pyramide() {

	file.open("pyramide.gcode");
	header();
	tete.x = 0;
	tete.y = 0;
	//header
	file << "G21" << endl;
	file << "G90" << endl;
	file << "G28" << endl;
	//head();
	double rayon = 20;
	double taille = 20;
	for (double i = 0 ; i < taille ; i = i + taux) {
		z = i;
		double comp = taille - i;
		double r = (taille - comp) * rayon;
		r /= taille;
		if (rayon - r > nw)
			tricercle(rayon - r);
	}
	endFunc();
}

void header() {
	move(point(-10, 75));
	move(point(75, 75));
}

void endFunc() {
	z = z + 15;
	move(tete);
	move(point(0, 0));
}



int main(int argc, char *argv[]) {

	switch (atoi(argv[1])) {

	case 1:
		printf("creation d une forme dans cube.gcode\n");
		cube();
		printf("\nfin");
		return 1 ;
	case 2:
		printf("creation d une forme dans cylindre.gcode\n");
		cylindre();
		printf("\nfin");
		return 2 ;
		break;
	case 3:
		printf("creation d une forme dans hemi.gcode\n");
		hemiv();
		printf("\nfin");
		return 3 ;
		break;
	case 4:
		printf("creation d une forme dans pyramide.gcode\n");
		pyramide();
		printf("\nfin");
		return 4 ;
		break;
	case 5:
		printf("creation d une forme dans cubeV2.gcode\n");
		cube2();
		printf("\nfin");
		return 4 ;
		break;
	case 6:
		printf("creation d une forme dans puzzle.gcode\n");
		puzzle();
		printf("\nfin");
		return 4 ;
		break;
	default :
		printf("cette operation n existe pas\n");
		return 0;
		break;

	}


	srand (time(NULL));
	return 0 ;

}
