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
#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include <cmath>
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
		return s;
	};

	void concat(shape s) {
		for (int i = 0 ; i < s.vertices.size(); i++) {
			vertices.push_back(s.vertices[i]);
		}
	};

	void melt(point a) {
		shape s;
		for (int i = 0 ; i < vertices.size(); i++) {
			if (!vertices[0].equals(a)) {
				point a = vertices[0].duplicate();
				vertices.erase(vertices.begin(), vertices.begin() + 1);
				vertices.push_back(a);
			}
		}
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