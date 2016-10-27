#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <sys/time.h>
#include <cmath>

using namespace std;

double f(double inDbl,int extraWork)
{
   double wrkDbl;
              /* add extra work */
   for(int w=0; w<extraWork; w++)
   {
      wrkDbl = pow(inDbl,2.0);
      wrkDbl = sqrt(inDbl);
   } /* end of for loop */

   return pow(inDbl,2.0);
}

int main(int argc, char *argv[])
{
          /*  if arguments 1 or 2 or 3 are null, print out an error message and end the program */
   if(argv[1] == NULL
   || argv[2] == NULL
   || argv[3] == NULL)
   {
      cout << "One or more required arguments are null.   Three arguments are required" << endl;
      cout << "Proper arguments are arg1 is a,  arg2 is b, arg3 is #of points" << endl;
      cout << "arg4 is optional and specifies the intensity.   Defaults to 0 - zero" << endl;
      exit(0);
   }
   /* cout << "arg1 " << argv[1] << " arg2 " << argv[2] << " arg3 " << argv[3] << " arg4 " << argv[4] << endl; */

   stringstream arg1;      /* convert char to int (a - lower bound) */
   arg1 << argv[1];
   double dblA;
   arg1 >> dblA;
   int intA;
   arg1 >> intA;

   stringstream arg2;  /* convert  to int (b - upper bound) */
   arg2 << argv[2];
   double dblB;
   arg2 >> dblB;
   int intB;
   arg2 >> intB;

   stringstream arg3;  /* convert to (numPts number of points) */
   arg3 << argv[3];
   int numPts;
   arg3 >> numPts;

         /* now set intensity */
   int intensity = 0;

   if (argv[4] == NULL)    /* default if none specified is 0 */
   {
      intensity = 0;
   }
   else
   {
      stringstream arg4;  /* convert to (intensity) */
      arg4 << argv[4];
      arg4 >> intensity;
   }

   double mySum = 0.0;

                /* get the starting time */
   /*time_t startTime,endTime;*/
   timeval curTime;
   gettimeofday(&curTime, NULL);
   double startTime = curTime.tv_sec + (curTime.tv_usec / 1000000.0);
   double f1 = 0.0;

   /* cout << "Starting our loop"  << " a=" << dblA << " b=" << dblB << " numPts=" << numPts
        << " intensity=" << intensity << endl;   */
   f1 = (dblB - dblA) / numPts;

          /* loop thru the number of points and call the function using the formula provided */
   for(int i=0; i<numPts; i++)
   {
      mySum = mySum + (f(dblA + ((i + .5) * ((dblB - dblA) / numPts)),intensity) * ((dblB - dblA) / numPts));
   } /* end of for loop */

             /* get the end time */
   /*time(&endTime);
   double elapse = difftime(endTime,startTime);*/
   gettimeofday(&curTime, NULL);
   double endTime = curTime.tv_sec + (curTime.tv_usec / 1000000.0);
   double elapse = endTime - startTime;

   /* cout << "End: " << endTime << " Start: " << startTime << endl; */


              /* first write to console */
   cout << "a=" << dblA << " b=" << dblB << " #of points=" << numPts
     << " intensity=" << intensity
     << " result=" << mySum
     << " and it took "
     << elapse << " seconds" << endl;

              /* write same thing to output text file */
   freopen("output.txt","a",stdout);    /* redirect output to output.txt - append to existing file */

   cout << "a=" << dblA << " b=" << dblB << " #of points=" << numPts
     << " intensity=" << intensity
     << " result=" << mySum
     << " and it took "
     << elapse << " seconds" << endl;

             /* now build a comma delimited .csv file */
   freopen("output.csv","a",stdout);    /* redirect output to output.csv - append to existing file */

   cout << numPts << "," << intensity << "," << elapse << endl;


   /*******   end of mainline *****/

} /* end of main */

