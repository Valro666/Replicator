#include <stdlib.h>
#include <stdio.h>



int z = 0;
FILE* fichier = NULL;

void zigzag(int x, int y,int t);

void square(){
	int i = 0;
	char s[30];
	
	for(i=0; i < 25 ; i++){
		sprintf(s, "G0 X50 Y50 Z%.2lf\n", 0.2*i);
		//fputs("G0 X50 Y50 Z",fichier);
		fputs(s,fichier);
		//printf("%d\n",i);
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

void zigzag(int x, int y,int t){
	
	int sens = 0;//0 : h, 1: v
	
	//fputs("G0 X50 Y50 \n",fichier);
	fputs("G1 X50.2 Y50.2 F1200\n",fichier);
	
	int p = 0 ;
	char s[64];
	double pas = t/10;
	double e=0;
	double xx = 0;
	double yy = 0;
	for(p=x; p < x+t ;p++){
			e++;
			xx = p+0.2;
			yy = y-0.2;
			sprintf(s,"G1 X%.2f Y%.2f E%.2f F1200\n ",xx,yy,e);
			fputs(s,fichier);
						xx = p+0.2;
			yy = y+t-0.2;
			sprintf(s,"G1 X%.2f Y%.2f E%.2f F1200\n",xx,yy,e);
			fputs(s,fichier);
	}		
	
	fputs("G92 E0\n",fichier);
	
}


int main(){

	fichier = fopen("square.gcode", "w+");
	
	square();
	
	fclose(fichier);
	return 0;
}