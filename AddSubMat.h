#ifndef STRASSEN_ADDSUBMAT_H
#define STRASSEN_ADDSUBMAT_H
#include "ValueMsg.h"

class addition :public CBase_addition{
    public:
    addition(CkMigrateMessage *m) {}
    addition(CkFuture f,AddSubMsg* Msg, int size){
        thisProxy.run(f,Msg,size);
    }
    void run(CkFuture f,AddSubMsg* Msg, int size){
        /*wrap the resulting addition in a message of size and send it back to future*/

  //if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());

        ValueMsg *m = new ValueMsg(size);

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                m->v[i][j] = Msg->A[i][j] + Msg->A[i][j];
            }
        }

        CkSendToFuture(f, m);
    }


};

class substraction :public CBase_substraction{
    public:
    substraction(CkMigrateMessage *m) {}
    substraction(CkFuture f,AddSubMsg* Msg, int size){
        thisProxy.run(f,Msg,size);
    }
    void run(CkFuture f,AddSubMsg* Msg, int size){
        //std::vector<std::vector<int>> C;

  //if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());

                   ValueMsg *m = new ValueMsg(size);


        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                m->v[i][j] = Msg->A[i][j] - Msg->A[i][j];
            }
        }
        /*wrap the resulting substraction in a message of size and send it back to future*/
        CkSendToFuture(f, m);
    }
};



#endif 