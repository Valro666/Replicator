#include <stdlib.h>
#include <stdio.h>



int z = 0;
FILE* fichier = NULL;

struct point{
	
	int x ;
	int y ;
	
};

void zigzag(int x, int y,int t);

void squaree(){
	int i = 0;
	char s[30];
	
	for(i=0; i < 25 ; i++){
		
		
		
		sprintf(s, "G0 X50 Y50 Z%.2lf\n", 0.2*i);
		//fputs("G0 X50 Y50 Z",fichier);
		fputs(s,fichier);
		//printf("%f\n",i);
		fputs("G1 X60.0 Y50.0 E1 F1200\n"
		"G1 X60.0 Y60.0 E2 F1200\n"
		"G1 X50.0 Y60.0 E3 F1200\n"
		"G1 X50.0 Y50.0 E4 F1200\nG92 E0\n",fichier);
		//fputs(";zig\n",fichier);
		zigzag(50,50,10);
		//fputs(";zag\n",fichier);
		//zigzig(50,50,10,25);
	}
}

void linel(double xo, double yo , double xf, double yf, double z){
	char s[256];
		sprintf(s, "G0 X%f Y%f Z%.2f F1200\n",xo,yo, z);//init
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xf,yf, z,1,1200);//
		fputs(s,fichier);
		fputs("G92 E0\n",fichier);

}

void squarefull(double xo, double yo , double w, double z){
	int i = 0;
	char s[256];
	double e = 0 ;
	
	//for(i=0; i < 25 ; i++){
		
		sprintf(s, "G0 X%f Y%f Z%.2f F1200\n",xo,yo, z);//init
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo+w,yo, z,1,1200);//
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo+w,yo+w, z,2,1200);//
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo,yo+w, z,3,1200);//
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo,yo, z,4,1200);//
		fputs(s,fichier);
		fputs("G92 E0\n",fichier);

	//}
}

void square(double xo, double yo , double w, double z){
	int i = 0;
	char s[256];
	double e = 0 ;
	
	//for(i=0; i < 25 ; i++){
	sprintf(s, "G0 X%f Y%f Z%.2f F1200\n",xo,yo, z);//init
	line(xo+w,yo,xo,yo,z);
	line(xo+w,yo+w,xo,yo,z);
	line(xo,yo+w,xo,yo,z);
	line(xo,yo,xo,yo,z);
		
		/*sprintf(s, "G0 X%f Y%f Z%.2f F1200\n",xo,yo, z);//init
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo+w,yo, z,1,1200);//
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo+w,yo+w, z,2,1200);//
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo,yo+w, z,3,1200);//
		fputs(s,fichier);
		sprintf(s, "G1 X%f Y%f Z%.2f E%d F%d\n",xo,yo, z,4,1200);//
		fputs(s,fichier);
		fputs("G92 E0\n",fichier);*/

	//}
}

void move(double x , double y , double z){
	char s[256];
		sprintf(s, "G0 X%f Y%f Z%.2f F1200\n",x,y,z);//init
		fputs(s,fichier);
}

void zigzag(int x, int y,int t){
	

	
}


int main(){

	fichier = fopen("square.gcode", "w+");
	double i = 0.2;
	struct point tete ;
	for(double i = 0 ; i < 10;i=i+0.2){
		square(50,50,10,i);
		//line(50,55,60,55,i);
		//line(55,50,55,60,i);
	}
	//square(50,50,10);
	
	fclose(fichier);
	return 0;
}