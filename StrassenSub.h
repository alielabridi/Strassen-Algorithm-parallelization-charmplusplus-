
#ifndef STRASSEN_STRASSENSUB_H
#define STRASSEN_STRASSENSUB_H
#include "ValueMsg.h"

class strassenSub: public CBase_strassenSub{
public:
    strassenSub(CkMigrateMessage *m) {}
    //overload the function to take three matrices or four
    //how should I adapt the class to implement for substraction
    /*four additions*/

     /*three addition*/
    strassenSub(CkFuture f,StrassenSubMsg* Msg,
              int size, char partition){ thisProxy.run(f,Msg,size,partition); }


    void run(CkFuture f,StrassenSubMsg* Msg,
                  int size,char partition){

        //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
        //if needed a big multiplication
        //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
        if(partition == '2' || partition == '5'){
            /*partition M2 =(A21+A22)B11*/
            /*OR partition M5 =(A11+A12)B22*/
            CkFuture padd1 = CkCreateFuture(); 
            AddSubMsg* addSubMsg = new AddSubMsg(size);
            for (int i = 0; i < size; ++i)
            {
                addSubMsg->A[i] = Msg->A[i];
                addSubMsg->B[i] = Msg->B[i];
            }
            //i could spawn all the additions needed here   
            CProxy_addition::ckNew(padd1,addSubMsg,size);//param not matching yet just a pseudo code
            //ValueMsg *m1 = new ValueMsg(size);
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(padd1);
            CkFuture p = CkCreateFuture();
            StrassenMsg* strassenMsg = new StrassenMsg(size);
            for (int i = 0; i < size; ++i)
            {
            strassenMsg->A[i] = m1->v[i];
            strassenMsg->B[i] = Msg->C[i];
            }
            CProxy_strassen::ckNew(p,strassenMsg,size);
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
            /*partition M3 = A11(B12-B22)*/
            /*OR partition M4 =A22(B21-B11)*/
            CkFuture psub1 = CkCreateFuture(); 
            //i could spawn all the additions needed here
            AddSubMsg* addSubMsg = new AddSubMsg(size);
            for (int i = 0; i < size; ++i)
            {
                addSubMsg->A[i] = Msg->B[i];
                addSubMsg->B[i] = Msg->C[i];
            }
            CProxy_substraction::ckNew(psub1,addSubMsg,size);//param not matching yet just a pseudo code
            //ValueMsg *m1 = new ValueMsg(size);
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
            CkFuture p = CkCreateFuture();
            StrassenMsg* strassenMsg = new StrassenMsg(size);
            for (int i = 0; i < size; ++i)
            {
            strassenMsg->A[i] = Msg->A[i];
            strassenMsg->B[i] = m1->v[i];
            }
            CProxy_strassen::ckNew(p,strassenMsg, size); 
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


      //if(VERBOSE)CkPrintf("Work done by processor %d\n",CkMyPe());
           
        //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
        //if needed a big multiplication
        //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
        else if(partition == '1'){
            //if(VERBOSE)CkPrintf("here stressen SUB run 1:\n");

            /*first partition M1 = (A11+A22)(B11+B22)*/
            CkFuture p1add1 = CkCreateFuture(); //A11+A22
            CkFuture p1add2 = CkCreateFuture(); //B11+B22
            //i could spawn all the additions needed here   
            //if(VERBOSE)CkPrintf("here stressen SUB run 2:\n");
            AddSubMsg* addSubMsg1 = new AddSubMsg(size);
            AddSubMsg* addSubMsg2 = new AddSubMsg(size);
            for (int i = 0; i < size; ++i)
            {
                addSubMsg1->A[i] = Msg->A[i];
                addSubMsg1->B[i] = Msg->B[i];
                addSubMsg2->A[i] = Msg->C[i];
                addSubMsg2->B[i] = Msg->D[i];
            }
            CProxy_addition::ckNew(p1add1,addSubMsg1,size);//param not matching yet just a pseudo code
            CProxy_addition::ckNew(p1add2,addSubMsg2,size);//param not matching yet just a pseudo code
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

            StrassenMsg* strassenMsg = new StrassenMsg(size);
            for (int i = 0; i < size; ++i)
            {
            strassenMsg->A[i] = m1->v[i];
            strassenMsg->B[i] = m2->v[i];
            }
            CProxy_strassen::ckNew(p1,strassenMsg,size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
            //if(VERBOSE)CkPrintf("here stressen SUB run 6:\n");

            //i could free m1 and m2 at this point
            //if(VERBOSE)CkPrintf("here stressen SUB run 7:\n");

            //ValueMsg *m3 = new ValueMsg(size);
            ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);
            delete m1;
            delete m2;
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
            AddSubMsg* addSubMsg1 = new AddSubMsg(size);
            AddSubMsg* addSubMsg2 = new AddSubMsg(size);
            for (int i = 0; i < size; ++i)
            {
                addSubMsg1->A[i] = Msg->A[i];
                addSubMsg1->B[i] = Msg->B[i];
                addSubMsg2->A[i] = Msg->C[i];
                addSubMsg2->B[i] = Msg->D[i];
            }
            CProxy_substraction::ckNew(psub1,addSubMsg1,size);//param not matching yet just a pseudo code
            CProxy_addition::ckNew(padd2,addSubMsg2,size);//param not matching yet just a pseudo code
            //ValueMsg *m1 = new ValueMsg(size);
            //ValueMsg *m2 = new ValueMsg(size);
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(padd2);
            CkFuture p = CkCreateFuture();
            StrassenMsg* strassenMsg = new StrassenMsg(size);
            for (int i = 0; i < size; ++i)
            {
            strassenMsg->A[i] = m1->v[i];
            strassenMsg->B[i] = m2->v[i];
            }
            CProxy_strassen::ckNew(p,strassenMsg,size);//to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
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
};
#endif 
