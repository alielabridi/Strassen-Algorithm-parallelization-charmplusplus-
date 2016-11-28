
#ifndef STRASSEN_STRASSENSUB_H
#define STRASSEN_STRASSENSUB_H
#include "ValueMsg.h"
#include <vector>
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
CkPrintf("SUB: Work done by processor %d\n",CkMyPe());

  //if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());
       
    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    if(partition == '1'){
        //if(VERBOSE)CkPrintf("here stressen SUB run 1:\n");
CkPrintf("SUB1: Work done by processor %d\n",CkMyPe());

        /*first partition M1 = (A11+A22)(B11+B22)*/
        CkFuture p1add1 = CkCreateFuture(); //A11+A22
        CkFuture p1add2 = CkCreateFuture(); //B11+B22
        //i could spawn all the additions needed here   
        //if(VERBOSE)CkPrintf("here stressen SUB run 2:\n");

        CProxy_addition::ckNew(p1add1,A,B,size);//param not matching yet just a pseudo code
        CProxy_addition::ckNew(p1add2,C,D,size);//param not matching yet just a pseudo code
        //if(VERBOSE)CkPrintf("here stressen SUB run 3:\n");

        //ValueMsg *m1 = new ValueMsg(size);
        //ValueMsg *m2 = new ValueMsg(size);
CkPrintf("SUB1 - END0: Work done by processor %d\n",CkMyPe());

        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1add1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p1add2);
CkPrintf("SUB1 - END0: Work done by processor %d\n",CkMyPe());

      /*  if(VERBOSE)CkPrintf("value of a11+a22:\n");

        for(int i=0; i<newSize;i++){
            for (int j = 0; j < newSize; ++j)
            {
                if(VERBOSE)CkPrintf("%d ",a11->v[i][j]);
            }
                if(VERBOSE)CkPrintf("\n");
        }*/
        //if(VERBOSE)CkPrintf("here stressen SUB run 4:\n");
CkPrintf("SUB1 - END0: Work done by processor %d\n",CkMyPe());

        CkFuture p1 = CkCreateFuture();
        //if(VERBOSE)CkPrintf("here stressen SUB run 5:\n");
CkPrintf("SUB1 - END0: Work done by processor %d\n",CkMyPe());

CkPrintf("SUB1 - END5: Work done by processor %d\n",CkMyPe());
CkPrintf("the result of m2 in partition %c\n",partition);
for (int i = 0; i < size; ++i)
{
 for (int j = 0; j < size; ++j)
 {
    CkPrintf("%d ",m2->v[i][j]);
 }
    CkPrintf("\n");

}
CkPrintf("the result of m1 in partition %c\n",partition);

for (int i = 0; i < size; ++i)
{
 for (int j = 0; j < size; ++j)
 {
    CkPrintf("%d ",m1->v[i][j]);
 }
    CkPrintf("\n");

}

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)

        {
            temp1[i][j] = m1->v[i][j];
            temp2[i][j] = m2->v[i][j];
        }
CkPrintf("SUB1 - END6: Work done by processor %d\n",CkMyPe());

        CProxy_strassen::ckNew(p1,temp1,temp2,size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //if(VERBOSE)CkPrintf("here stressen SUB run 6:\n");

        //i could free m1 and m2 at this point
        //if(VERBOSE)CkPrintf("here stressen SUB run 7:\n");

        //ValueMsg *m3 = new ValueMsg(size);
CkPrintf("SUB1 - END0: Work done by processor %d\n",CkMyPe());

        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);
        //if(VERBOSE)CkPrintf("here stressen SUB run 8:\n");
CkPrintf("SUB1 - END: Work done by processor %d\n",CkMyPe());

        CkSendToFuture(f, m3);
        delete m1;
        delete m2;

        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    }    

    else if(partition == '6' || partition == '7'){
CkPrintf("SUB6-7: Work done by processor %d\n",CkMyPe());

        /*partition M6 = (A21-A11)(B11+B12)*/
        /*OR partition M7 = (A12-A22)(B21+B22)*/
        CkFuture psub1 = CkCreateFuture(); 
        CkFuture padd2 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        CProxy_substraction::ckNew(psub1,A,B,size);//param not matching yet just a pseudo code
        CProxy_addition::ckNew(padd2,C,D,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        //ValueMsg *m2 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(padd2);
        CkFuture p = CkCreateFuture();
         for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)

        {
            temp1[i][j] = m1->v[i][j];
            temp2[i][j] = m2->v[i][j];
        }
        CProxy_strassen::ckNew(p,temp1,temp2, size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //i could free m1 and m2 at this point
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        delete m1;
        delete m2;
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
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

    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    if(partition == '2' || partition == '5'){
CkPrintf("SUB2-5: Work done by processor %d\n",CkMyPe());

        /*partition M2 =(A21+A22)B11*/
        /*OR partition M5 =(A11+A12)B22*/
        CkFuture padd1 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        CProxy_addition::ckNew(padd1,A,B,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(padd1);
        CkFuture p = CkCreateFuture();
         for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                temp1[i][j] = m1->v[i][j];

        CProxy_strassen::ckNew(p,temp1,C, size); 
        //i could free m1 and m2 at this point
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        delete m1;
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    } 
    else if(partition == '3' || partition == '4'){
CkPrintf("SUB3-4: Work done by processor %d\n",CkMyPe());

        /*partition M3 = A11(B12-B22)*/
        /*OR partition M4 =A22(B21-B11)*/
        CkFuture psub1 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        CProxy_substraction::ckNew(psub1,B,C,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        CkFuture p = CkCreateFuture();
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                temp1[i][j] = m1->v[i][j];

        CProxy_strassen::ckNew(p,A,temp1, size); 
        //i could free m1 and m2 at this point
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        delete m1;
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    } 


    }

};
#endif 
