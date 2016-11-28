#ifndef STRASSEN_ADDSUBMAT_H
#define STRASSEN_ADDSUBMAT_H
#include "ValueMsg.h"

class addition :public CBase_addition{
    public:
    addition(CkMigrateMessage *m) {};
    addition(CkFuture f,std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int size){
        thisProxy.run(f,A,B,size);
    }
    void run(CkFuture f,std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int size){
        //if(VERBOSE)CkPrintf("addition run 1:\n");
        /*wrap the resulting addition in a message of size and send it back to future*/

  //if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());


        ValueMsg *m = new ValueMsg(size);



        //if(VERBOSE)CkPrintf("addition run 1-1:\n");

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                m->v[i][j] = A[i][j] + B[i][j];
            }
        }
        //if(VERBOSE)CkPrintf("addition run 2:\n");



        //if(VERBOSE)CkPrintf("addition run 4:\n");

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
        //std::vector<std::vector<int>> C;

  //if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());

                   ValueMsg *m = new ValueMsg(size);


        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                m->v[i][j] = A[i][j] - B[i][j];
            }
        }
        /*wrap the resulting substraction in a message of size and send it back to future*/
        CkSendToFuture(f, m);
    }
};



#endif 