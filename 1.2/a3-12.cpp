#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <sys/time.h>
#include <cmath>

using namespace  std;

/* define global variables - visible to all functions */

double globalSum;
double globalA;
double globalB;
int globalIntens;
int globalNumPts;
int globalNextPt;
int globalGran;
int globalThreadSum [16];
string globalMutLev;

pthread_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16;  // define the threads
pthread_mutex_t sumLock;            // define the lock for globalSum
pthread_mutex_t nextPtLock;         // define the lock for globalNextPt

/*  declare some functions that will follow main */
double  f(double,int);              // the function that started this whole mess
void    startThreads(int);          // routine to start the right number of threads
void    joinThreads(int);           // routine that will join (wait on) the threads
double  innerLoop(int, int);        // innerLoop routine
void*   loopSched();                // routine to schedule the work within a thread
bool    Done();                     // routine to see if the work is done
int     getNext(int, int);          // get next range of points to process




/**********   mainline  **********/

int main(int argc, char *argv[])
{
          /*  if arguments 1 or 2 or 3 are null, print out an error message and end the program */
    if(argv[1] == NULL
    || argv[2] == NULL
    || argv[3] == NULL
    || argv[4] == NULL
    || argv[5] == NULL
    || argv[6] == NULL
    || argv[7] == NULL)
    {
      cout << "One or more required arguments are null.   Seven arguments are required" << endl;
      cout << "Proper arguments are arg1 is a,  arg2 is b, arg3 is #of points" << endl;
      cout << "arg4 is intensity.  arg5 is #threads  arg6 is Granularity  arg7 is which mutex" << endl;
      cout << "mutex  can be inner, local, or thread" << endl;
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
    stringstream arg4;  /* convert to (intensity) */
    arg4 << argv[4];
    arg4 >> intensity;

               /* now set #threads */
    int prmThreads = 0;
    stringstream arg5;
    arg5 << argv[5];
    arg5 >> prmThreads;

                /* now set granularity */
    int prmGran = 0;
    stringstream arg6;
    arg6 << argv[6];
    arg6 >> prmGran;

                  /* now set mutex level */
    string prmMutex;
    stringstream arg7;
    arg7 << argv[7];
    arg7 >> prmMutex;

             /*  if arguments 1 or 2 or 3 are null, print out an error message and end the program */
    if(prmMutex != "inner"
    && prmMutex != "local"
    && prmMutex != "thread")
    {
      cout << "Invalid value for arg7 - 'which mutex'. input was " << prmMutex << endl;
      cout << "Valid values for which mutex are:  inner  local  thread" << endl;
      exit(0);
    }

    cout << "a " << dblA << "  b " << dblB << " numPts " << numPts << " intensity " << intensity
       << " prmThreads " << prmThreads << " prmGran " << prmGran << " prmMutex " << prmMutex << endl;



         /*  set global variable and other intiializations */

    double mySum = 0.0;
    globalSum = 0.0;

    globalA = dblA;
    globalB = dblB;
    globalIntens = intensity;
    globalNextPt = 0;
    globalGran = prmGran;
    globalMutLev = prmMutex;
    globalNumPts = numPts;


    /* define the locks */
    pthread_mutex_init(&sumLock, NULL);
    pthread_mutex_init(&nextPtLock, NULL);



                /* get the starting time */
    /*time_t startTime,endTime;*/
    timeval curTime;
    gettimeofday(&curTime, NULL);
    double startTime = curTime.tv_sec + (curTime.tv_usec / 1000000.0);
    double f1 = 0.0;

    /* cout << "Starting our loop"  << " a=" << dblA << " b=" << dblB << " numPts=" << numPts
        << " intensity=" << intensity << endl;   */
    /* f1 = (dblB - dblA) / numPts; */


            /* start threads based on prmThreads */
    startThreads(prmThreads);

            /* wait on the started threads */
    joinThreads(prmThreads);


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
     << " #threads=" << prmThreads
     << " granularity=" << prmGran
     << " Mutex level=" << globalMutLev
     << " result=" << globalSum
     << " and it took "
     << elapse << " seconds" << endl;

              /* write same thing to output text file */
    freopen("output12q4.txt","a",stdout);    /* redirect output to output.txt - append to existing file */

    cout << "a=" << dblA << " b=" << dblB << " #of points=" << numPts
     << " intensity=" << intensity
     << " #threads=" << prmThreads
     << " granularity=" << prmGran
     << " Mutex level=" << globalMutLev
     << " result=" << globalSum
     << " and it took "
     << elapse << " seconds" << endl;

             /* now build a comma delimited .csv file */
    freopen("output12q4.csv","a",stdout);    /* redirect output to output.csv - append to existing file */

    cout << numPts
    << "," << intensity
    << "," << prmThreads
    << "," << prmGran
    << "," << globalMutLev
    << "," << elapse << endl;


    /*******   end of mainline *****/



    /*
    pthread_self();  to get id of thread
    */

} /* end of main */




/***********************   our function **************/
/*    input is a double & an int for extra work      */
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

}   /* end of function f */


/**** getnext function ********/
/*    checks/updates globalNextPtr sets the next processing range for a thread */
/*    returns 0 if success,   returns 1 if done                                */
int getNext(int *next,int *end)
{
    pthread_mutex_lock(&nextPtLock);
    if (globalNextPt >= globalNumPts)
    {               /* done */
        pthread_mutex_unlock(&nextPtLock);
        return 1;
    }

    *next = globalNextPt;
    globalNextPt = globalNextPt + globalGran;
    if (globalNextPt >= globalNumPts)
    {
        *end = globalNumPts;
    } else
    {
        *end = *next + globalGran;
    }

    pthread_mutex_unlock(&nextPtLock);

    return 0;

}   /* end of getNext function */




/**** done function ********/
/*    checks to see if more work.   returns true if work is done     */
bool Done()
{
    pthread_mutex_lock(&nextPtLock);
    if (globalNextPt < globalNumPts)
    {               /* not done */
        pthread_mutex_unlock(&nextPtLock);
        return false;
    } else
    {               /* done */
        pthread_mutex_unlock(&nextPtLock);
        return true;
    }
}   /* end of Done function */



  /*************  function to schedule the work within a thread *********/
void* loopSched(void* data)
{
    int last_rc = 0;
    double threadSum = 0;

    /* if there is more to do, get the next range to be processed */
    while (!Done())
    {
        int begin, end;
        last_rc = getNext(&begin,&end);
        if (last_rc > 0)   /* if rc>0 then nothing else to process */
            break;
         threadSum = threadSum + innerLoop(begin,end);
    }   /* end of while */

    if (globalMutLev == "thread")       /* if measuring at thread level - lock and add to globalSum */
    {
        pthread_mutex_lock(&sumLock);
        globalSum = globalSum + threadSum;
        pthread_mutex_unlock(&sumLock);
    }

    return NULL;

}  /* end of loopSched */


  /*************  function to loop through a range of points & calculate the sum *********/  /*BTC*/
double innerLoop(int inBegin,int inEnd)
{
    double retValue = 0;
    double localSum = 0;

       /* loop thru the number of points and call the function using the formula provided */
    for(int i=inBegin; i<inEnd; i++)
    {
        retValue = (f(globalA + ((i + .5) * ((globalB - globalA) / globalNumPts)),globalIntens) * ((globalB - globalA) / globalNumPts));

        localSum = localSum + retValue;    /*  accumulate for 'local' level - before return from this routine */

        if (globalMutLev == "inner")       /* if measuring at inner level - lock and add to globalSum */
        {
            pthread_mutex_lock(&sumLock);
            globalSum = globalSum + retValue;
            pthread_mutex_unlock(&sumLock);
        }
    } /* end of for loop */

    if (globalMutLev == "local")       /* if measuring at inner level - lock and add to globalSum */
    {
        pthread_mutex_lock(&sumLock);
        globalSum = globalSum + localSum;
        pthread_mutex_unlock(&sumLock);
    }

    return localSum;    /* return for loopSched to accumulate */

}  /* end of innerLoop */



      /*************  routine that starts the threads *********/
void startThreads(int numThreads)
{

    pthread_create(&t1,NULL,loopSched,NULL);

    if (numThreads >= 2)
    {
        pthread_create(&t2,NULL,loopSched,NULL);
    }

    if (numThreads >= 3)
    {
        pthread_create(&t3,NULL,loopSched,NULL);
    }

    if (numThreads >= 4)
    {
        pthread_create(&t4,NULL,loopSched,NULL);
    }

    if (numThreads >= 5)
    {
        pthread_create(&t5,NULL,loopSched,NULL);
    }

    if (numThreads >= 6)
    {
        pthread_create(&t6,NULL,loopSched,NULL);
    }

    if (numThreads >= 7)
    {
        pthread_create(&t7,NULL,loopSched,NULL);
    }

    if (numThreads >= 8)
    {
        pthread_create(&t8,NULL,loopSched,NULL);
    }

    if (numThreads >= 9)
    {
        pthread_create(&t9,NULL,loopSched,NULL);
    }

    if (numThreads >= 10)
    {
        pthread_create(&t10,NULL,loopSched,NULL);
    }

    if (numThreads >= 11)
    {
        pthread_create(&t11,NULL,loopSched,NULL);
    }

    if (numThreads >= 12)
    {
        pthread_create(&t12,NULL,loopSched,NULL);
    }

    if (numThreads >= 13)
    {
        pthread_create(&t13,NULL,loopSched,NULL);
    }

    if (numThreads >= 14)
    {
        pthread_create(&t14,NULL,loopSched,NULL);
    }

    if (numThreads >= 15)
    {
        pthread_create(&t15,NULL,loopSched,NULL);
    }

    if (numThreads >= 16)
    {
        pthread_create(&t16,NULL,loopSched,NULL);
    }


}  /* end of startThreads */



      /*************  routine that starts the threads *********/
void joinThreads(int numThreads)
{

    pthread_join(t1,NULL);

    if (numThreads >= 2)
    {
        pthread_join(t2,NULL);
    }

    if (numThreads >= 3)
    {
        pthread_join(t3,NULL);
    }

    if (numThreads >= 4)
    {
        pthread_join(t4,NULL);
    }

    if (numThreads >= 5)
    {
        pthread_join(t5,NULL);
    }

    if (numThreads >= 6)
    {
        pthread_join(t6,NULL);
    }

    if (numThreads >= 7)
    {
        pthread_join(t7,NULL);
    }

    if (numThreads >= 8)
    {
        pthread_join(t8,NULL);
    }

    if (numThreads >= 9)
    {
        pthread_join(t9,NULL);
    }

    if (numThreads >= 10)
    {
        pthread_join(t10,NULL);
    }

    if (numThreads >= 11)
    {
        pthread_join(t11,NULL);
    }

    if (numThreads >= 12)
    {
        pthread_join(t12,NULL);
    }

    if (numThreads >= 13)
    {
        pthread_join(t13,NULL);
    }

    if (numThreads >= 14)
    {
        pthread_join(t14,NULL);
    }

    if (numThreads >= 15)
    {
        pthread_join(t15,NULL);
    }

    if (numThreads >= 16)
    {
        pthread_join(t16,NULL);
    }

}  /* end of joinThreads */
