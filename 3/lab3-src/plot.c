
#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}






void createPlot( char * funcFile, double minX, double maxX) {
	//test minX maxX------------------correct
	//	printf("This is minX: %f\n",minX);
	//	printf("This is maxX: %f\n",maxX);
	//
	int i = 0;
  	int nvals = MAXCOLS;
  	double yy[MAXCOLS];
  	double xx[MAXCOLS];
  	clearPlot();
  // Evaluate function and store in vector yy
  	for(i ; i<MAXCOLS;i++){
		double x = minX + (maxX - minX)*i/MAXCOLS;


		//printf("This is i: %d\n",i);
		//printf("This is x: %f\n",x);
		//test funcFile
		//printf("This is funcFile: %s\n",funcFile);
		//


		double y = rpn_eval(funcFile,x);
		xx[i] = x;
		//printf("This is x in xx[%d]: %f\n",i,xx[i]);
		
		yy[i] = y;
	}


	/*TEST CALCULATION IS CORRECT OR NOT!
	int test = 0;
	for (test;test<MAXCOLS - 1;test++){
		printf("This is x in xx[%d]: %f\n",test,xx[test]);
		printf("This is y in yy[%d]: %f\n",test,yy[test]);
	}
	*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////				Get value of x and y is correct




  //Compute maximum and minimum y in vector yy
  	double minY = yy[0];
	double maxY = yy[0];
  	int j = 0;
	int storeX = 0;
	for(j ; j<i;j++){
		if(yy[j] < minY){
			minY = yy[j];
		}
		if(yy[j] > maxY){
			maxY = yy[j];
		}
		if(yy[j] == 0){
			 storeX = j;
		}
	}
	
	//printf("This is minY: %f\n",minY);
	//printf("This is maxY: %f\n",maxY);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////			minY maxY correct

				/*
  //Plot y axis
	int axisY = 0;
	for(axisY;axisY<MAXROWS;axisY++){
		plotXY(40,axisY,'|');
	}
	
  //Plot x axis
	int axisX = 0;
	for(axisX;axisX<MAXCOLS;axisX++){
		plotXY(axisX,20,'_');
	}


				*/

	//plot x-axis and y-axis
	i = 0;
	//y-axis
	for(i ; i < MAXROWS;i++){
		if(plot[i][40] != '*'){
			plotXY(40,i,'|');
		}
	}

	//x-axis
	i = 0;
        for(i; i< MAXCOLS; i++){
	     int x = i;
	     int y = (int)((0 - minY) * MAXROWS/(maxY - minY));
	     if(y > MAXROWS){
	     	y = MAXROWS;
	     }
	     if(plot[y][x] != '*'){
	     		plotXY(x,MAXROWS - 1 - y,'_');
        	}
	}
	
  // Plot function. Use scaling.
  // minX is plotted at column 0 and maxX is plotted ar MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1
  	i = 0;
  	for(i; i< MAXCOLS; i++){
		int x = i;
		int y = (int)((yy[i]-minY) * MAXROWS/(maxY - minY));
	//	if(y > MAXROWS){
	//		y = MAXROWS;
	//	}
		plotXY(x,MAXROWS - 1 - y,'*');
	}



  printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  // Getnt arguments
  char * funcName = argv[1];
  double xmin = 0;
  double xmax = 0;

	sscanf(argv[2],"%lf",&xmin);
	sscanf(argv[3],"%lf",&xmax);

	//test xmin xmax------------------correct
		//printf("This is xmin: %f\n", xmin);
		//printf("This is xmax: %f\n",xmax);
	//

  	createPlot(funcName, xmin, xmax);
}
