#ifndef STRASSEN_ADDSUBMAT_H
#define STRASSEN_ADDSUBMAT_H
#include "ValueMsg.h"

class addition :public CBase_addition{
    public:
    addition(CkMigrateMessage *m) {};
    addition(CkFuture f,const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int size){
        thisProxy.run(f,A,B,size);
    }
    void run(CkFuture f,const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int size){
        /*wrap the resulting addition in a message of size and send it back to future*/
        ValueMsg *m = new ValueMsg(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                m->v[i][j] = A[i][j] + B[i][j];
        CkSendToFuture(f, m);
    }
};

class substraction :public CBase_substraction{
    public:
    substraction(CkMigrateMessage *m) {};
    substraction(CkFuture f,const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int size){
        thisProxy.run(f,A,B,size);
    }
    void run(CkFuture f,const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int size){
    //CkPrintf("substraction: Work done by processor %d\n",CkMyPe());
        /*wrap the resulting addition in a message of size and send it back to future*/
        ValueMsg *m = new ValueMsg(size);
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                m->v[i][j] = A[i][j] - B[i][j];
        CkSendToFuture(f, m);
    }
};



#endif 