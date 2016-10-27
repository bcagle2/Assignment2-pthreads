#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <sys/time.h>
#include <cmath>

using namespace std;

/* Global variables */
int matA[3][3] = {          //defined as 3x3 but only using the
   {0,0,0},                 //range starting from [1][1] to match
   {0,4,9},                 //the formula
   {0,12,33}};

int matB[3][3] = {
   {0,0,0},
   {0,7,1},
   {0,17,5}};

int wrkM[8];
int wrkN[8];
int wrkP[8];
int wrkT[4];
int intensity;
int intensityFactor;


/* Function declarations */
int myMult(int,int);           // my multiply function
int myAdd(int,int);
int mySub(int,int);
void moreWork();

int main(int argc, char *argv[])
{
          /*  if argument 1 is null, print out an error message and end the program */
    if(argv[1] == NULL)
    {
      cout << "The argument is null. One argument is required" << endl;
      cout << "arg1 is intensity." <<endl;
      exit(0);
    }

         /* now set intensity */
    stringstream arg1;  /* convert to (intensity) */
    arg1 << argv[1];
    arg1 >> intensity;

    intensityFactor = 5;

            /* get the starting time */
    /*time_t startTime,endTime;*/
    timeval curTime;
    gettimeofday(&curTime, NULL);
    double startTime = curTime.tv_sec + (curTime.tv_usec / 1000000.0);
    double f1 = 0.0;

    wrkM[1] = myAdd(matA[1][1],0);
    wrkM[2] = myAdd(matA[1][2],0);
    wrkM[3] = myAdd(matA[2][1],matA[2][2]);
    wrkM[4] = mySub(wrkM[3],matA[1][1]);
    wrkM[5] = mySub(matA[1][1],matA[2][1]);
    wrkM[6] = mySub(matA[1][2],wrkM[4]);
    wrkM[7] = myAdd(matA[2][2],0);

    wrkN[1] = myAdd(matB[1][1],0);
    wrkN[2] = myAdd(matB[2][1],0);
    wrkN[3] = mySub(matB[1][2],matB[1][1]);
    wrkN[4] = mySub(matB[2][2],wrkN[3]);
    wrkN[5] = mySub(matB[2][2],matB[1][2]);
    wrkN[6] = myAdd(matB[2][2],0);
    wrkN[7] = mySub(matB[2][1],wrkN[4]);


    for(int i=1; i<8; i++)
    {
        wrkP[i] = myMult(wrkM[i],wrkN[i]);
    }

    wrkT[1] = myAdd(wrkP[1],wrkP[4]);
    wrkT[2] = myAdd(wrkT[1],wrkP[5]);
    wrkT[3] = myAdd(wrkT[1],wrkP[3]);


                 /* get the end time */
    /*time(&endTime);
    double elapse = difftime(endTime,startTime);*/
    gettimeofday(&curTime, NULL);
    double endTime = curTime.tv_sec + (curTime.tv_usec / 1000000.0);
    double elapse = endTime - startTime;


                  /* first write to console */
    cout << " intensity=" << intensity
     << " and it took " << elapse << " seconds" << endl;

              /* write same thing to output text file */
    freopen("output21.txt","a",stdout);    /* redirect output to output.txt - append to existing file */

    cout << " intensity=" << intensity
     << " and it took " << elapse << " seconds" << endl;

             /* now build a comma delimited .csv file */
    freopen("output21.csv","a",stdout);    /* redirect output to output.csv - append to existing file */

    cout << intensity << "," << elapse << endl;


}

void moreWork()
{

    double wrkDbl;

              /* add extra work */
    for(int w=0; w<intensity; w++)
    {
      wrkDbl = pow(intensityFactor,2.0);
      wrkDbl = sqrt(intensityFactor);
    } /* end of for loop */

}   /* end of function f */

int myMult(int mult1,int mult2)
{
    for(int i=0; i<intensityFactor; i++)
    {
        moreWork();
    }

    return mult1 * mult2;
}

int myAdd(int add1,int add2)
{
    moreWork();

    return add1 + add2;
}

int mySub(int sub1,int sub2)
{
    moreWork();

    return sub1 - sub2;
}
