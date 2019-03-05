#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include<bits/stdc++.h> 
using namespace std;
class point {
public :
	double x;
	double y;
	point(double a , double b) {
		x = a;
		y = b;
	};
	point() {
		x = 0.0;
		y = 0.0;
	};
	void go(point a ) {
		x = a.x;
		y = a.y;
	}

	double dist(point a ) {
		double xx = a.x - x;
		double yy = a.y - y;
		xx = xx * xx;
		yy = yy * yy;

		double res = xx + yy;
		res = sqrt(res);

		return res;
	}

	void rotate(point centre, double angle ) {
		angle *= M_PI / 180.0;
		double xM = x - centre.x;
		double yM = y - centre.y;
		x = xM * cos(angle) + yM * sin(angle) + centre.x;
		y = - xM * sin(angle) + yM * cos(angle) + centre.y;
	}

	void translate(double tx, double ty ) {
		x = x + tx;
		y = y + ty;
	}

	bool equals(point b) {
		if (b.x == x && b.y == y) {
			return true;
		}
		return false;
	}

	point jump(double jx, double jy ) {
		point t(x, y) ;
		t.x = t.x + jx;
		t.y = t.y + jy;
		return t;
	}

	point duplicate() {
		point t(x, y) ;
		return t;
	}

} ;

class shape {
public :
	vector<point> vertices;

	void inverse();

	void add(point a) {
		vertices.push_back(a);
	}

	void rotate(point centre, double angle ) {
		for (int i = 0 ; i < vertices.size(); i++) {
			vertices[i].rotate(centre, angle);
		}
	};

	void translate(double tx, double ty ) {
		for (int i = 0 ; i < vertices.size(); i++) {
			vertices[i].translate(tx, ty);
		}
	};

	shape duplicate() {
		shape s;
		for (int i = 0 ; i < vertices.size(); i++) {
			s.add(vertices[i].duplicate());
		}
	};

	void concat(shape s) {
		//shape s;
		for (int i = 0 ; i < s.vertices.size(); i++) {
			vertices.push_back(s.vertices[i]);
		}
	};

	void melt(point a) {
		shape s;
		for (int i = 0 ; i < vertices.size(); i++) {
			//    printf("molp");
			if (!vertices[0].equals(a)) {
				point a = vertices[0].duplicate();
				vertices.erase(vertices.begin(), vertices.begin() + 1);
				vertices.push_back(a);
			}
		}
		//  printf("mmpolohtcxd");
	};

	point minX() {
		point p = vertices[0];
		for (int i = 0 ; i < vertices.size(); i++) {
			if (vertices[i].x < p.x) {
				p = vertices[i];
			}
		}
		return p;
	}
	point maxX() {
		point p = vertices[0];
		for (int i = 0 ; i < vertices.size(); i++) {
			if (vertices[i].x > p.x) {
				p = vertices[i];
			}
		}
		return p;
	}
	point minY() {
		point p = vertices[0];
		for (int i = 0 ; i < vertices.size(); i++) {
			if (vertices[i].y < p.y) {
				p = vertices[i];
			}
		}
		return p;
	}
	point maxY() {
		point p = vertices[0];
		for (int i = 0 ; i < vertices.size(); i++) {
			if (vertices[i].y > p.y) {
				p = vertices[i];
			}
		}
		return p;
	}
	bool inside(point p) {
		int i = 0 ;

		point xmin = minX();
		point xmax = maxX();

		point p1 = vertices[0];
		point p2 = vertices[1];
		point p3 = vertices[2];
		int tr = 1 ;
		point init = vertices[1];

		int s1 = 0 ;
		int s2 = 1 ;
		int s3 = 2 ;

		while (tr > 0) {
			//cout << s1 << s2 << s3 << endl;
			double denominator = ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
			double a = ((p2.y - p3.y) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.y)) / denominator;
			double b = ((p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y)) / denominator;
			double c = 1 - a - b;

			if (a > 0)
				if (a < 1)
					if (b > 0)
						if (b < 1)
							if (c > 0)
								if (c < 1) return true; //*/

			s3 = (s3 + 1) % size() ;
			s2 = (s2 + 1) % size() ;
			p2 = vertices[s2];
			p3 = vertices[s3];

			if (s3 == 0) {
				tr = -1;
			}
		}
		return false;
	};
	bool insideBrainLess(point p) {

		vector<double> coef ;
		int i = 0 ;

		point xmin = minX();
		point xmax = maxX();

		point p1 = vertices[0];
		point p2 = vertices[1];
		point p3 = vertices[2];
		int tr = 1 ;
		point init = vertices[1];

		int s1 = 0 ;
		int s2 = 1 ;
		int s3 = 2 ;
		while (tr > 0) {
			double denominator = ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
			double a = ((p2.y - p3.y) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.y)) / denominator;
			double b = ((p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y)) / denominator;
			double c = 1 - a - b;

			if (a > 0)
				if (a < 1)
					if (b > 0)
						if (b < 1)
							if (c > 0)
								if (c < 1) return true; //*/

			s3 += 1;
			if (s3 > size() - 1) {
				s3 = 0;
				s2 += 1;
			}
			if (s2 > size() - 1) {
				s2 = 0;
				s1++;
			}

			p1 = vertices[s1];
			p2 = vertices[s2];
			p3 = vertices[s3];

			if (s1 == s2) {
				if (s1 == s3) {
					tr = -1;
				}
			}
		}

		return false;


	};

	void fusion(shape s) {
		point p = s.vertices[0];
		double d = vertices[0].dist(s.vertices[0]) ;
		for (int j = 0 ; j < s.vertices.size(); j++) {
			if (d > vertices[vertices.size()].dist(s.vertices[j])) {
				d = vertices[vertices.size()].dist(s.vertices[j]) ;
				p = s.vertices[j];
			}
		}
		s.melt(p);

		for (int j = 0 ; j < s.vertices.size(); j++) {
			vertices.push_back(s.vertices[j]);
		}
	};

	void dellast() {
		vertices.pop_back();
	};

	int size() {
		return vertices.size();
	};
};

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
	//file<<"G1 X"<<tete.x<<" Y"<<tete.y<<" Z"<<z<<" E1.0 F1200"<<endl;
	file << "G1 X" <<  tete.x << " Y" <<  tete.y << " Z" << z << " E" <<  extrud(a.dist(b)) << " F1200" << endl;
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

//G2 X Y I J E : XY centre IJ bord

shape cercledelenfer(point centre , double bord, double nb) {

	shape s ;
	//vector<point> poly ;


	double diametre = 2.0 * M_PI * (bord);

	double x = centre.x + bord;

	double to = 360 / nb;

	for (double i = 0.0; abs(i) < 360 ; i = i + to) {


		point p = centre.jump(0.0, 0.0);
		p.translate(bord, 0.0);
		p.rotate(centre, i);
		s.add(p);
		//	poly.push_back(p);

	}

	point p = centre.jump(0.0, 0.0);
	p.translate(bord, 0.0);
	p.rotate(centre, 360);

	if (!s.vertices[0].equals(s.vertices[s.size()]))
		s.add(s.vertices[0].duplicate());
	//s.add(p);
	//	poly.push_back(p);

	//polygnon(poly);

	//file<<"G92 E0.0"<<endl;

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

	double to = nn;
	if (sens == 1) {
		for (double i = bord ; i > 0 ; i = i - to) {
			shape tmp = cercledelenfer( centre ,  i,  nb);
			s.concat(tmp);
		}
	} else {
		for (double i = to ; i < bord ; i = i + to) {
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
		//	cout << i<<endl;
	}
}

void polygnon(shape s) {
	int i = 0;
	double tmp = 0;
	vector<point> poly = s.vertices;
	move(poly[0]);
	for (i = 1 ; i < poly.size(); i++) {
		tmp = (i - 1);
		line(poly[tmp], poly[i]);
		//	cout << i<<endl;
	}

	//file<<"G92 E0.0"<<endl;
}


void cube() {
	file.open("cube.gcode");
	tete.x = 0;
	tete.y = 0;
	//header
	header();

	shape s = square();
	shape f = squarefill();

	// printf("fghjkl");

	s.fusion(f);

	int tmp = 0 ;
	double taille = 10 / taux;
	for (double i = 0 ; i < taille ; i++) {

		z = i * taux;

		polygnon(s);
		s.rotate(point(50.0, 50.0), 90.0);
		s.translate(0.0, 10.0); //*/
		tmp = (tmp + 1) % 2;
	}
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
	double taille = 10 / taux;
	for (double i = 0 ; i < taille ; i++) {

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

shape fillShapeX(shape sh) {
	shape s ;

	point minX =  sh.minX();
	point maxX = sh.maxX();
	point maxY = sh.maxY();
	point minY = sh.minY();
	point first = point(100, 100);
	point last = point(100, 100);
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
			s.add(first);
			s.add(last);
		}
		tr ++;
	}
	return s;
}

void tricercle(double rayon = 20) {
	shape s = cercledelenfer(point(50, 50), rayon, rayon * 4);
	//shape s = formconv();
	shape ss = fillShapeX(s);
	//s.concat(ss);
	//shape melt = s.fusion(ss);
	polygnon(s);
	polygnon(ss);
	//polygnon(s);
	//polygnon(ss);
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

	// x*x + y*y = 1
	//x*x = 1 - y*y
	// x = sqrt(1-y*y)
	for (double i = 0 ; i <= taille ; i = i + taux) {

		//z = i*taux;
		z = i;
		//double r = ((taille - (taille - z))*rayon)/taille;
		double comp =  i;

		double r = sqrt((rayon * rayon) - (comp * comp));
		if (r > nw)
			tricercle(r);

		printf("%f %f \r", taille, z);
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

		//z = i*taux;
		z = i;
		//double r = ((taille - (taille - z))*rayon)/taille;
		double comp = taille - i;

		double r = (taille - comp) * rayon;
		r /= taille;
		if (rayon - r > nw)
			tricercle(rayon - r);

		printf("%f %f \r", taille, z);
	}
	endFunc();
}

void header() {

	file << "G21\nG90\nG28\nM140 S60\nM105\nM190 S60\nM104 S200\nM105\nM109 S200\nG92 E0\nG1 E10 F1200\nG92 E0\n" << endl;

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
		printf("creation d un cube dans cube.gcode\n");
		cube();
		printf("\nfin");
		return 1 ;
	case 2:
		printf("creation d un cylindre dans cylindre.gcode_n");
		cylindre();
		printf("\nfin");
		return 2 ;
		break;
	case 3:
		printf("creation d un cylindre dans hemi.gcode\n");
		hemiv();
		printf("\nfin");
		return 3 ;
		break;
	case 4:
		printf("creation d un cylindre dans pyramide.gcode\n");
		pyramide();
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
