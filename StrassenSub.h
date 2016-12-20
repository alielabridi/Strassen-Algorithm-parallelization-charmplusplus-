
#ifndef STRASSEN_STRASSENSUB_H
#define STRASSEN_STRASSENSUB_H
#include "ValueMsg.h"
#include <vector>
#define VERBOSE2 0
class strassenSub: public CBase_strassenSub{
public:
    strassenSub(CkMigrateMessage *m) {};
    //overload the function to take three matrices or four
    //how should I adapt the class to implement for substraction
    /*four additions*/
    strassenSub(CkFuture f,const std::vector<std::vector<int>>& A,
                 const std::vector<std::vector<int>>& B, const std::vector<std::vector<int>>& C, const std::vector<std::vector<int>>& D,
                  int size, char partition){ thisProxy.run(f,A,B,C,D,size,partition); }


    void run(CkFuture f,const std::vector<std::vector<int>>& A,
                 const std::vector<std::vector<int>>& B, const std::vector<std::vector<int>>& C, const std::vector<std::vector<int>>& D,
                  int size, char partition){
        std::vector<std::vector<int>> temp1(size,std::vector<int>(size));
        std::vector<std::vector<int>> temp2(size,std::vector<int>(size));
    if(VERBOSE2)CkPrintf("Chare StrassenSub (size = %d, partition = %c) done by processor %d\n",size,partition,CkMyPe());
   
    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    if(partition == '1'){


        /*first partition M1 = (A11+A22)(B11+B22)*/
        CkFuture p1add1 = CkCreateFuture(); //A11+A22
        CkFuture p1add2 = CkCreateFuture(); //B11+B22

        CProxy_addition::ckNew(p1add1,A,B,size);
        CProxy_addition::ckNew(p1add2,C,D,size);

        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1add1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p1add2);

        CkFuture p1 = CkCreateFuture();

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)

        {
            temp1[i][j] = m1->v[i][j];
            temp2[i][j] = m2->v[i][j];
        }

        CProxy_strassen::ckNew(p1,temp1,temp2,size); 

        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);

        CkSendToFuture(f, m3);
        delete m1;
        delete m2;
    }    

    else if(partition == '6' || partition == '7'){
        /*partition M6 = (A21-A11)(B11+B12)*/
        /*OR partition M7 = (A12-A22)(B21+B22)*/
        CkFuture psub1 = CkCreateFuture(); 
        CkFuture padd2 = CkCreateFuture(); 

        CProxy_substraction::ckNew(psub1,A,B,size);
        CProxy_addition::ckNew(padd2,C,D,size);

        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(padd2);
        CkFuture p = CkCreateFuture();
         for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)

        {
            temp1[i][j] = m1->v[i][j];
            temp2[i][j] = m2->v[i][j];
        }
        CProxy_strassen::ckNew(p,temp1,temp2, size);

        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        delete m1;
        delete m2;
        CkSendToFuture(f, m3);
        
    }  


    }


     /*three addition*/
    strassenSub(CkFuture f,const std::vector<std::vector<int>>& A,
             const std::vector<std::vector<int>>& B, const std::vector<std::vector<int>>& C,
              int size, char partition){ thisProxy.run(f,A,B,C,size,partition); }


    void run(CkFuture f,const std::vector<std::vector<int>>& A,
                 const std::vector<std::vector<int>>& B, const std::vector<std::vector<int>>& C,
                  int size,char partition){
        std::vector<std::vector<int>> temp1(size,std::vector<int>(size));
    if(VERBOSE2)CkPrintf("Chare StrassenSub (size = %d, partition = %c) done by processor %d\n",size,partition,CkMyPe());

    if(partition == '2' || partition == '5'){

        /*partition M2 =(A21+A22)B11*/
        /*OR partition M5 =(A11+A12)B22*/
        CkFuture padd1 = CkCreateFuture(); 

        CProxy_addition::ckNew(padd1,A,B,size);

        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(padd1);
        CkFuture p = CkCreateFuture();
         for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                temp1[i][j] = m1->v[i][j];

        CProxy_strassen::ckNew(p,temp1,C, size); 

        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        delete m1;
        CkSendToFuture(f, m3);
        
    } 
    else if(partition == '3' || partition == '4'){

        /*partition M3 = A11(B12-B22)*/
        /*OR partition M4 =A22(B21-B11)*/
        CkFuture psub1 = CkCreateFuture(); 

        CProxy_substraction::ckNew(psub1,B,C,size);

        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        CkFuture p = CkCreateFuture();
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                temp1[i][j] = m1->v[i][j];

        CProxy_strassen::ckNew(p,A,temp1, size); 

        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        delete m1;
        CkSendToFuture(f, m3);
        
    } 


    }

};
#endif 
