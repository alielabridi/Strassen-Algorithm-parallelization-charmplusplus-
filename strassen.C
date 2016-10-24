#include "strassen.decl.h"
#define THRESHOLD 3

class ValueMsg : public CMessage_ValueMsg {
public:
    std::vector<std::vector<int> > v;
    //i found a solution to allocate a non fixed sized without segment fault
    ValueMsg(int size):v(size, std::vector<int>(size)){}
    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };
class Main : public CBase_Main {
    public: 
        Main(CkMigrateMessage *m) {};
        Main(CkArgMsg * m) { 
            if(m->argc < 2) {
                //CmiAbort("./strassen N.");
                //cout << "test";
                CkExit();
            }
            int size = atoi(m->argv[1]);  
            thisProxy.run(size);
        }
    void run(int size) { 
        CkFuture f = CkCreateFuture();
        CProxy_strassen::ckNew(size, f);
        ValueMsg * m = (ValueMsg *) CkWaitFuture(f); 
        CkPrintf("The number is : %d\n", m->v[0][0]);
        CkExit(); delete m;
    }  
};

class addition :public CBase_addition{
    public:
    addition(CkMigrateMessage *m) {};
    addition(CkFuture f,std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int size){
        thisProxy.run(f,A,B,size);
    }
    void run(CkFuture f,std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int size){
        std::vector<std::vector<int>> C;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        /*wrap the resulting addition in a message of size and send it back to future*/
        ValueMsg *m = new ValueMsg(size);
        m->v = C;
        CkSendToFuture(f, m);
    }


};

class substraction :public CBase_substraction{
    public:
    substraction(CkMigrateMessage *m) {};
    substraction(CkFuture f,std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int size){
        thisProxy.run(f,A,B,size);
    }
    void run(CkFuture f,std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int size){
        std::vector<std::vector<int>> C;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                C[i][j] = A[i][j] - B[i][j];
            }
        }
        /*wrap the resulting substraction in a message of size and send it back to future*/
        ValueMsg *m = new ValueMsg(size);
        m->v = C;
        CkSendToFuture(f, m);
    }
};

class strassen : public CBase_strassen  {
    private:  int result, count, IamRoot;  CProxy_strassen parent;

    public:  
    strassen(CkMigrateMessage *m) {};
    strassen(int size, CkFuture f){ thisProxy.run(size, f); }
/*    int seqFib(int size){
        if ((size == 1) || (size == 0)) {
                return size;
            }
        return seqFib(size - 1) + seqFib(size - 2);
    }*/
/*
    void ikjalgorithm(vector< vector<int> > A, 
                                   vector< vector<int> > B,
                                   vector< vector<int> > &C, int size) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                for (int j = 0; j < n; j++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }*/
    void run(int size, CkFuture f) {

        //if (n< THRESHOLD)
        if(size < THRESHOLD);
            //result = ikjalgorithm(size);
        else {  
            //declaration of submatrices needed here
            int newSize = size/2;
            std::vector<int> inner (newSize);
            std::vector< std::vector<int> > 
            a11(newSize,inner), a12(newSize,inner), a21(newSize,inner), a22(newSize,inner),
            b11(newSize,inner), b12(newSize,inner), b21(newSize,inner), b22(newSize,inner),
            c11(newSize,inner), c12(newSize,inner), c21(newSize,inner), c22(newSize,inner),
            p1(newSize,inner), p2(newSize,inner), p3(newSize,inner), p4(newSize,inner), 
            p5(newSize,inner), p6(newSize,inner), p7(newSize,inner),
            


            CkFuture p1add1 = CkCreateFuture(); //A11+A22
            CkFuture p1add2 = CkCreateFuture(); //B11+B22
            //i could spawn all the additions needed here   
            CProxy_addition::ckNew(size-1, f1);//param not matching yet just a pseudo code
            CProxy_addition::ckNew(size-1, f1);//param not matching yet just a pseudo code
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1add1);
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p1add2);
            CkFuture p1 = CkCreateFuture();
            CProxy_strassen::ckNew(size-1, f1); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
            //i could free m1 and m2 at this point
            ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);
            p1 = m3->v; //returned product of the two summation
            //i can free m3 at this point
            // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
            //or should I use a block instead?





            CkFuture f2 = CkCreateFuture();
            CProxy_strassen::ckNew(size-1, f1);
            CProxy_strassen::ckNew(size-2, f2);
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(f1);
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(f2);
            result = m1->v[0][0] + m2->v[0][0];
            delete m1; 
            delete m2;
        }
        ValueMsg *m = new ValueMsg(1000);
        m->v[0][0] = result;
        CkSendToFuture(f, m);
          
    
    }  
};


#include "strassen.def.h"