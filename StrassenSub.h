
#ifndef STRASSEN_STRASSENSUB_H
#define STRASSEN_STRASSENSUB_H
#include "ValueMsg.h"

class strassenSub: public CBase_strassenSub{
public:
    strassenSub(CkMigrateMessage *m) {};
    //overload the function to take three matrices or four
    //how should I adapt the class to implement for substraction
    /*four additions*/
    strassenSub(CkFuture f,std::vector<std::vector<int>> A,
                 std::vector<std::vector<int>> B, std::vector<std::vector<int>> C, std::vector<std::vector<int>> D,
                  int size, char partition){ thisProxy.run(f,A,B,C,D,size,partition); }


    void run(CkFuture f,std::vector<std::vector<int>> A,
                 std::vector<std::vector<int>> B, std::vector<std::vector<int>> C, std::vector<std::vector<int>> D,
                  int size, char partition){
    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    if(partition == '1'){
        //if(VERBOSE)CkPrintf("here stressen SUB run 1:\n");

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
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1add1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p1add2);

      /*  if(VERBOSE)CkPrintf("value of a11+a22:\n");

        for(int i=0; i<newSize;i++){
            for (int j = 0; j < newSize; ++j)
            {
                if(VERBOSE)CkPrintf("%d ",a11->v[i][j]);
            }
                if(VERBOSE)CkPrintf("\n");
        }*/
        //if(VERBOSE)CkPrintf("here stressen SUB run 4:\n");

        CkFuture p1 = CkCreateFuture();
        //if(VERBOSE)CkPrintf("here stressen SUB run 5:\n");

        CProxy_strassen::ckNew(p1,m1->v,m2->v,size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //if(VERBOSE)CkPrintf("here stressen SUB run 6:\n");

        //i could free m1 and m2 at this point
        //if(VERBOSE)CkPrintf("here stressen SUB run 7:\n");

        //ValueMsg *m3 = new ValueMsg(size);
        delete m1;
        delete m2;
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);
        //if(VERBOSE)CkPrintf("here stressen SUB run 8:\n");

        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    }    

    else if(partition == '6' || partition == '7'){
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
        CProxy_strassen::ckNew(p,m1->v,m2->v, size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //i could free m1 and m2 at this point
        delete m1;
        delete m2;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    }  


    }


     /*three addition*/
    strassenSub(CkFuture f,std::vector<std::vector<int>> A,
             std::vector<std::vector<int>> B, std::vector<std::vector<int>> C,
              int size, char partition){ thisProxy.run(f,A,B,C,size,partition); }


    void run(CkFuture f,std::vector<std::vector<int>> A,
                 std::vector<std::vector<int>> B, std::vector<std::vector<int>> C,
                  int size,char partition){

    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    if(partition == '2' || partition == '5'){
        /*partition M2 =(A21+A22)B11*/
        /*OR partition M5 =(A11+A12)B22*/
        CkFuture padd1 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        CProxy_addition::ckNew(padd1,A,B,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(padd1);
        CkFuture p = CkCreateFuture();

        CProxy_strassen::ckNew(p,m1->v,C, size); 
        //i could free m1 and m2 at this point
        delete m1;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    } 
    else if(partition == '3' || partition == '4'){
        /*partition M3 = A11(B12-B22)*/
        /*OR partition M4 =A22(B21-B11)*/
        CkFuture psub1 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        CProxy_substraction::ckNew(psub1,B,C,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        CkFuture p = CkCreateFuture();
        CProxy_strassen::ckNew(p,A,m1->v, size); 
        //i could free m1 and m2 at this point
        delete m1;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    } 


    }

};
#endif 
