#include <fstream>
#include "strassen.decl.h"
#include "StrassenSub.h"
#include "AddSubMat.h"
#include "ValueMsg.h"

int THRESHOLD;
int VERBOSE;

class Main : public CBase_Main {
    public: 
        Main(CkMigrateMessage *m) {}
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

  if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j){
            B[i][j] = 0;
            A[i][j] = 1;

            }

        for (int i = 0; i < size; ++i)
            B[i][i] = 1;


        /*execution of parralelization*/
        double starttimer = CkWallTimer();
        CkFuture f = CkCreateFuture();

        StrassenMsg *strassenMsg = new StrassenMsg(size);
        for (int i = 0; i < size; ++i){
            strassenMsg->A[i] = A[i];
            strassenMsg->B[i] = B[i];
        }
        CProxy_strassen::ckNew(f,strassenMsg,size);

        ValueMsg * m = (ValueMsg *) CkWaitFuture(f); 
        double endtimer = CkWallTimer();

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
            CkPrintf("Strassen - Correct: matrix size = %d, Threshold = %d,# of proc = %d, Exec time = %lf sec \n",  size, THRESHOLD,CkNumPes(),endtimer-starttimer);
            myfile<<"Strassen - Correct: matrix size = " <<size<<", Threshold = "<< THRESHOLD<<",# of proc = "<<CkNumPes()<<" , Exec time = " << endtimer-starttimer << "\n";
        }
        else{
            CkPrintf("Strassen - Incorrect: matrix size = %d, Threshold = %d,# of proc = %d, Exec time = %lf sec \n",  size, THRESHOLD,CkNumPes(),endtimer-starttimer);
            myfile<<"Strassen - Incorrect: matrix size = " <<size<<", Threshold = "<< THRESHOLD<<",# of proc = "<<CkNumPes()<<" , Exec time = " << endtimer-starttimer << "\n";
        }
  myfile.close();
        delete m;

        CkExit(); 
    }  
};



class strassen : public CBase_strassen  {
    //private:  int result, count, IamRoot;  CProxy_strassen parent;

    public:  
    strassen(CkMigrateMessage *m) {}
    strassen(CkFuture f,StrassenMsg* Msg,int size){ thisProxy.run(f,Msg,size); }


    void run(CkFuture f,StrassenMsg* Msg,int size) {
            //if(VERBOSE)CkPrintf("here stressen run 1:\n");
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




            //if(VERBOSE)CkPrintf("here stressen run 3:\n");

        //if (n< THRESHOLD)
        if(size <= THRESHOLD){
             for (int i = 0; i < size; i++) {
                for (int k = 0; k < size; k++) {
                    m->v[i][k] = 0;
                    for (int j = 0; j < size; j++) {
                        m->v[i][k] += Msg->A[i][j] * Msg->B[j][k];
                    }
                }
            }
            // if(VERBOSE)CkPrintf("computation done by ikjalgorithm\n");        


        }
        else {
            //if(VERBOSE)CkPrintf("here stressen run 4:\n");

//dividing the matrices in 4 sub-matrices:
        for (int i = 0; i < newSize; i++) {
            for (int j = 0; j < newSize; j++) {
                a11[i][j] = Msg->A[i][j];
                a12[i][j] = Msg->A[i][j + newSize];
                a21[i][j] = Msg->A[i + newSize][j];
                a22[i][j] = Msg->A[i + newSize][j + newSize];

                b11[i][j] = Msg->B[i][j];
                b12[i][j] = Msg->B[i][j + newSize];
                b21[i][j] = Msg->B[i + newSize][j];
                b22[i][j] = Msg->B[i + newSize][j + newSize];
            }
        }
            //if(VERBOSE)CkPrintf("here stressen run 4-1:\n");

  
            //declaration of submatrices needed here
            
            // call for future (p1,p2....p7) with future then recolt the result

            //do the next computation with it
            /*four addition*/
            //the value of P1
            /*M1 = (A11+A22)(B11+B22)*/
            CkFuture p1Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg1 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg1->A[i] = a11[i];
                StrassenSubMsg1->B[i] = a22[i];
                StrassenSubMsg1->C[i] = b11[i];
                StrassenSubMsg1->D[i] = b22[i];
            }
        
            CProxy_strassenSub::ckNew(p1Future, StrassenSubMsg1,newSize,'1');
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1Future);
            //if(VERBOSE)CkPrintf("here stressen run 5:\n");
            if(VERBOSE)CkPrintf("done with m1 of size %d\n",newSize);


            /*three addition*/
            //the value of P2
            /*partition M2 =(A21+A22)B11*/
            CkFuture p2Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg2 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg2->A[i] = a21[i];
                StrassenSubMsg2->B[i] = a22[i];
                StrassenSubMsg2->C[i] = b11[i];
            }
            CProxy_strassenSub::ckNew(p2Future, StrassenSubMsg2,newSize,'2');
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p2Future);
            //if(VERBOSE)CkPrintf("here stressen run 6:\n of size %d\n",newSize);
            if(VERBOSE)CkPrintf("done with m2 of size %d\n",newSize);





            //the value of P3
            /*partition M3 = A11(B12-B22)*/
            CkFuture p3Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg3 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg3->A[i] = a11[i];
                StrassenSubMsg3->B[i] = b12[i];
                StrassenSubMsg3->C[i] = b22[i];
            }
            CProxy_strassenSub::ckNew(p3Future, StrassenSubMsg3,newSize,'3');
            ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p3Future);
            if(VERBOSE)CkPrintf("done with m3 of size %d\n",newSize);


            //if(VERBOSE)CkPrintf("here stressen run 7:\n of size %d\n",newSize);



            //the value of P4
            /*OR partition M4 =A22(B21-B11)*/
            CkFuture p4Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg4 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg4->A[i] = a22[i];
                StrassenSubMsg4->B[i] = b21[i];
                StrassenSubMsg4->C[i] = b11[i];
            }
            CProxy_strassenSub::ckNew(p4Future, StrassenSubMsg4,newSize,'4');
            ValueMsg * m4 = (ValueMsg *) CkWaitFuture(p4Future);
            //if(VERBOSE)CkPrintf("here stressen run 8:\n of size %d\n",newSize);
            if(VERBOSE)CkPrintf("done with m4 of size %d\n",newSize);



            //the value of P5
            /*OR partition M5 =(A11+A12)B22*/
            CkFuture p5Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg5 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg5->A[i] = a11[i];
                StrassenSubMsg5->B[i] = a12[i];
                StrassenSubMsg5->C[i] = b22[i];
            }
            CProxy_strassenSub::ckNew(p5Future, StrassenSubMsg5,newSize,'5');
            ValueMsg * m5 = (ValueMsg *) CkWaitFuture(p5Future);
            //if(VERBOSE)CkPrintf("here stressen run 9:\n");
            if(VERBOSE)CkPrintf("done with m5 of size %d\n",newSize);


            //the value of P6
            /*partition M6 = (A21-A11)(B11+B12)*/
            CkFuture p6Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg6 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg6->A[i] = a21[i];
                StrassenSubMsg6->B[i] = a11[i];
                StrassenSubMsg6->C[i] = b11[i];
                StrassenSubMsg6->D[i] = b12[i];
            }
        
            CProxy_strassenSub::ckNew(p6Future, StrassenSubMsg6,newSize,'6');
            ValueMsg * m6 = (ValueMsg *) CkWaitFuture(p6Future);
            //if(VERBOSE)CkPrintf("here stressen run 10:\n");
            if(VERBOSE)CkPrintf("done with m6 of size %d\n",newSize);


            //the value of P7
            /*OR partition M7 = (A12-A22)(B21+B22)*/
            CkFuture p7Future = CkCreateFuture();
            StrassenSubMsg* StrassenSubMsg7 = new StrassenSubMsg(newSize);
            for (int i = 0; i < newSize; ++i)
            {
                StrassenSubMsg7->A[i] = a12[i];
                StrassenSubMsg7->B[i] = a22[i];
                StrassenSubMsg7->C[i] = b12[i];
                StrassenSubMsg7->D[i] = b22[i];
            }
        
            CProxy_strassenSub::ckNew(p7Future,StrassenSubMsg7 ,newSize,'7');
            ValueMsg * m7 = (ValueMsg *) CkWaitFuture(p7Future);
            //if(VERBOSE)CkPrintf("here stressen run 11:\n");
            if(VERBOSE)CkPrintf("done with m7 of size %d\n",newSize);



            /*do we need another chare for the C1,C2,C3,C4 ?*/
            /*compute C11 = M1+M4-M5+M7*/
            for (int i = 0; i < newSize; i++){
                for (int j = 0; j < newSize; j++) {
                    m->v[i][j] = m1->v[i][j] + m4->v[i][j] - m5->v[i][j] + m7->v[i][j];
                    m->v[i][j + newSize] = m3->v[i][j] + m5->v[i][j];
                    m->v[i + newSize][j] = m2->v[i][j] + m4->v[i][j];
                    m->v[i + newSize][j + newSize] = m1->v[i][j] - m2->v[i][j] + m3->v[i][j] + m6->v[i][j];
                } 
            }
            //if(VERBOSE)CkPrintf("here stressen run 12:\n");
            delete m1;
            delete m2;
            delete m3;
            delete m4;
            delete m5;
            delete m6;
            delete m7;



            //at this points we should wait for p1,p2,p3... to compute c11,c22,,c12,c21
            //combine it into a big C and return it in the form of a msgs

            //if(VERBOSE)CkPrintf("here stressen run 13:\n");

        }
            //if(VERBOSE)CkPrintf("here stressen run 14:\n");




        //m->v = result;
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
            //if(VERBOSE)CkPrintf("here stressen run 15:\n");


          
    
    }  
};


#include "strassen.def.h"