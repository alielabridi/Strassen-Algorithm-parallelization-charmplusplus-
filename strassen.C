#include <fstream>
#include <vector>
#include "strassen.decl.h"
#include "StrassenSub.h"
#include "AddSubMat.h"
#include "ValueMsg.h"
#include "pup_stl.h"
#define VERBOSE2 0

int THRESHOLD;
int VERBOSE;

class Main : public CBase_Main {
    public: 
        Main(CkMigrateMessage *m) {};
        Main(CkArgMsg * m) { 
            int size;
            if(m->argc > 1)size = atoi(m->argv[1]);
            else size = 8;
            if(m->argc > 2)THRESHOLD = atoi(m->argv[2]);
            else THRESHOLD = 8;
            if(m->argc > 3)VERBOSE = atoi(m->argv[3]);
            else VERBOSE = 1;
            thisProxy.run(size);
        }
    void run(int size_) {
        int size = size_;

        std::vector<std::vector<int>> A(size,std::vector<int>(size));
        std::vector<std::vector<int>> B(size,std::vector<int>(size));

  if(VERBOSE)CkPrintf("Main call done by processor %d\n",CkMyPe());

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j){
            B[i][j] = 0;
            A[i][j] = 1;

            }

        for (int i = 0; i < size; ++i)
            B[i][i] = 1;


        /*execution of parralelization*/
        double starttimer = CkWallTimer();
        clock_t begin = clock();

        CkFuture f = CkCreateFuture();
        CProxy_strassen::ckNew(f,A,B,size);

        ValueMsg * m = (ValueMsg *) CkWaitFuture(f); 
        double endtimer = CkWallTimer();
        clock_t end = clock();

  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

        if(VERBOSE)CkPrintf("FINAL - The resulting matrix is :\n");

        for(int i=0; i<size;i++){
            for (int j = 0; j < size; ++j)
            {
                /* code */
                if(VERBOSE)CkPrintf("%d ",m->v[i][j]);
            }
                if(VERBOSE)CkPrintf("\n");
        }
       
        /*checking result if correct*/

        std::ofstream myfile;
  myfile.open ("results.txt",std::ofstream::app);

        bool correctness = true;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if(m->v[i][j] != A[i][j]) correctness = false;
        if(correctness && THRESHOLD == size){
            CkPrintf("Naive Serial - Correct: matrix size = %d, Exec time = %lf sec \n",  size,endtimer-starttimer);
            myfile<<"Naive Serial - Correct: matrix size = " <<size<<" , Exec time = " << endtimer-starttimer << "\n";
        
        }
        else if(!correctness && THRESHOLD == size){
            CkPrintf("Naive Serial - Incorrect: matrix size = %d, Exec time = %lf sec \n",  size,endtimer-starttimer);
            myfile<<"Naive Serial - Incorrect: matrix size = " <<size<<" , Exec time = " << endtimer-starttimer << "\n";
        
        }
        else if(correctness){
            CkPrintf("Charm++ - Correct: matrix size = %d, Threshold = %d,# of proc = %d, Exec time = %lf sec  \n",  size, THRESHOLD,CkNumPes(),endtimer-starttimer);
            myfile<<"Charm++ - Correct: matrix size = " <<size<<", Threshold = "<< THRESHOLD<<",# of proc = "<<CkNumPes()<<" , Exec time = " << endtimer-starttimer << "\n";
        }
        else{
            CkPrintf("Charm++ - Incorrect: matrix size = %d, Threshold = %d,# of proc = %d, Exec time = %lf sec \n",  size, THRESHOLD,CkNumPes(),endtimer-starttimer);
            myfile<<"Charm++ - Incorrect: matrix size = " <<size<<", Threshold = "<< THRESHOLD<<",# of proc = "<<CkNumPes()<<" , Exec time = " << endtimer-starttimer << "\n";
        }
  myfile.close();
        delete m;

        CkExit(); 
    }  
};



class strassen : public CBase_strassen  {
    public:  
    strassen(CkMigrateMessage *m) {};
    strassen(CkFuture f,const std::vector<std::vector<int>>& A,const std::vector<std::vector<int>>& B,int size){ thisProxy.run(f,A,B,size); }


    void run(CkFuture f,const std::vector<std::vector<int>>& A,const std::vector<std::vector<int>>& B,int size) {
        ValueMsg *m = new ValueMsg(size);

        int newSize = size/2;
        
        std::vector<std::vector<int>> a11(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> a12(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> a21(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> a22(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> b11(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> b12(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> b21(newSize,std::vector<int>(newSize));
        std::vector<std::vector<int>> b22(newSize,std::vector<int>(newSize));


        if(VERBOSE2)CkPrintf("Chare Strassen (size = %d) done by processor %d\n",size,CkMyPe());

        if(size <= THRESHOLD){
             for (int i = 0; i < size; i++) {
                for (int k = 0; k < size; k++) {
                    m->v[i][k] = 0;
                    for (int j = 0; j < size; j++) {
                        m->v[i][k] += A[i][j] * B[j][k];
                    }
                }
            }

        }
        else {

        //dividing the matrices in 4 sub-matrices:
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                a11[i][j] = A[i][j];
                a12[i][j] = A[i][j + newSize];
                a21[i][j] = A[i + newSize][j];
                a22[i][j] = A[i + newSize][j + newSize];

                b11[i][j] = B[i][j];
                b12[i][j] = B[i][j + newSize];
                b21[i][j] = B[i + newSize][j];
                b22[i][j] = B[i + newSize][j + newSize];
            }
        }
            
            // call for future (p1,p2....p7) with future then recolt the result

            //the value of P1
            /*M1 = (A11+A22)(B11+B22)*/
            CkFuture p1Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p1Future, a11, a22, b11, b22,newSize,'1');
            //the value of P2
            /*partition M2 =(A21+A22)B11*/
            CkFuture p2Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p2Future, a21, a22, b11,newSize,'2');

            //the value of P3
            /*partition M3 = A11(B12-B22)*/
            CkFuture p3Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p3Future, a11, b12, b22,newSize,'3');

            //the value of P4
            /*OR partition M4 =A22(B21-B11)*/
            CkFuture p4Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p4Future, a22, b21, b11,newSize,'4');

            //the value of P5
            /*OR partition M5 =(A11+A12)B22*/
            CkFuture p5Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p5Future, a11, a12, b22,newSize,'5');

            //the value of P6
            /*partition M6 = (A21-A11)(B11+B12)*/
            CkFuture p6Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p6Future,a21,a11,b11,b12,newSize,'6');

            //the value of P7
            /*OR partition M7 = (A12-A22)(B21+B22)*/
            CkFuture p7Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p7Future,a12,a22,b21,b22,newSize,'7');

            /*wait for all future to collect data*/
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1Future);
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p2Future);
            ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p3Future);
            ValueMsg * m4 = (ValueMsg *) CkWaitFuture(p4Future);
            ValueMsg * m5 = (ValueMsg *) CkWaitFuture(p5Future);
            ValueMsg * m6 = (ValueMsg *) CkWaitFuture(p6Future);
            ValueMsg * m7 = (ValueMsg *) CkWaitFuture(p7Future);

            /*compute C11 = M1+M4-M5+M7*/
            for (int i = 0; i < newSize; i++){
                for (int j = 0; j < newSize; j++) {
                    m->v[i][j] = m1->v[i][j] + m4->v[i][j] - m5->v[i][j] + m7->v[i][j];
                    m->v[i][j + newSize] = m3->v[i][j] + m5->v[i][j];
                    m->v[i + newSize][j] = m2->v[i][j] + m4->v[i][j];
                    m->v[i + newSize][j + newSize] = m1->v[i][j] - m2->v[i][j] + m3->v[i][j] + m6->v[i][j];
                } 
            }
            delete m1;
            delete m2;
            delete m3;
            delete m4;
            delete m5;
            delete m6;
            delete m7;


        }

        if(VERBOSE)CkPrintf("The resulting matrix is :\n");

        for(int i=0; i<size;i++){
            for (int j = 0; j < size; ++j)
            {
                /* code */
                if(VERBOSE)CkPrintf("%d ",m->v[i][j]);
            }
                if(VERBOSE)CkPrintf("\n");
        }
        CkSendToFuture(f, m);
    }  
};


#include "strassen.def.h"