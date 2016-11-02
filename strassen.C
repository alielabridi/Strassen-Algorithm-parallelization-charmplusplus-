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
/*            if(m->argc < 2) {
                //CmiAbort("./strassen N.");
                //cout << "test";
                CkExit();
            }
            int size = atoi(m->argv[1]);  */
            thisProxy.run();
        }
    void run() {
    std::vector<std::vector<int>> A{{1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    {1,1,1,1,1,1,1,1},
                                    }; 
    std::vector<std::vector<int>> B{{1,0,0,0,0,0,0,0},
                                    {0,1,0,0,0,0,0,0},
                                    {0,0,1,0,0,0,0,0},
                                    {0,0,0,1,0,0,0,0},
                                    {0,0,0,0,1,0,0,0},
                                    {0,0,0,0,0,1,0,0},
                                    {0,0,0,0,0,0,1,0},
                                    {0,0,0,0,0,0,0,1},
                                    };
        CkFuture f = CkCreateFuture();
        CProxy_strassen::ckNew(f,A,B,8);
        ValueMsg * m = (ValueMsg *) CkWaitFuture(f); 
        CkPrintf("The resulting matrix is :\n");

        for(int i=0; i<8;i++){
            for (int j = 0; j < 8; ++j)
            {
                /* code */
                CkPrintf("%d ",m->v[i][j]);
            }
                CkPrintf("\n");
        }
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
        /*first partition M1 = (A11+A22)(B11+B22)*/
        CkFuture p1add1 = CkCreateFuture(); //A11+A22
        CkFuture p1add2 = CkCreateFuture(); //B11+B22
        //i could spawn all the additions needed here   
        CProxy_addition::ckNew(p1add1,A,B,size);//param not matching yet just a pseudo code
        CProxy_addition::ckNew(p1add2,C,D,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        //ValueMsg *m2 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1add1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p1add2);
        CkFuture p1 = CkCreateFuture();
        CProxy_strassen::ckNew(p1,m1->v,m2->v,size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //i could free m1 and m2 at this point
        delete m1;
        delete m2;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);
        CkSendToFuture(f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    }    

    else if(partition == '6' || partition == '7'){
        /*partition M6 = (A21-A11)(B11+B12)*/
        /*OR partition M7 = (A12-A22)(B21+B22)*/
        CkFuture padd1 = CkCreateFuture(); 
        CkFuture psub2 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        CProxy_substraction::ckNew(padd1,A,B,size);//param not matching yet just a pseudo code
        CProxy_addition::ckNew(psub2,C,D,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        //ValueMsg *m2 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(padd1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(psub2);
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
        CProxy_addition::ckNew(psub1,B,C,size);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        CkFuture p = CkCreateFuture();
        CProxy_strassen::ckNew(p,m1->v,A, size); 
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
class strassen : public CBase_strassen  {
    //private:  int result, count, IamRoot;  CProxy_strassen parent;

    public:  
    strassen(CkMigrateMessage *m) {};
    strassen(CkFuture f,std::vector<std::vector<int>> A,std::vector<std::vector<int>> B,int size){ thisProxy.run(f,A,B,size); }


    void run(CkFuture f,std::vector<std::vector<int>> A,std::vector<std::vector<int>> B,int size) {

            int newSize = size/2;
            std::vector<int> inner (newSize);
            std::vector< std::vector<int> > 
            a11(newSize,inner), a12(newSize,inner), a21(newSize,inner), a22(newSize,inner),
            b11(newSize,inner), b12(newSize,inner), b21(newSize,inner), b22(newSize,inner),
            c11(newSize,inner), c12(newSize,inner), c21(newSize,inner), c22(newSize,inner),
            p1(newSize,inner), p2(newSize,inner), p3(newSize,inner), p4(newSize,inner), 
            p5(newSize,inner), p6(newSize,inner), p7(newSize,inner);


            std::vector<int> innerResult (size);
            std::vector< std::vector<int> > result(size,inner);

/*
        std::vector< std::vector<int> > ikjalgorithm(std::vector< std::vector<int> > A, 
                   std::vector< std::vector<int> > B,
                   int size) {

            for (int i = 0; i < size; i++) {
                for (int k = 0; k < size; k++) {
                    for (int j = 0; j < size; j++) {
                        C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
            return C;
        }*/


        //if (n< THRESHOLD)
        if(size < THRESHOLD){
             for (int i = 0; i < size; i++) {
                for (int k = 0; k < size; k++) {
                    for (int j = 0; j < size; j++) {
                        result[i][j] += A[i][k] * B[k][j];
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
  
            //declaration of submatrices needed here
            
            // call for future (p1,p2....p7) with future then recolt the result

            //do the next computation with it
            /*four addition*/
            //the value of P1
            /*M1 = (A11+A22)(B11+B22)*/
            CkFuture p1Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p1Future, a11, a22, b11, b22,newSize,'1');
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1Future);

            /*three addition*/
            //the value of P2
            /*partition M2 =(A21+A22)B11*/
            CkFuture p2Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p2Future, a21, a22, b11,newSize,'2');
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p2Future);


            //the value of P3
            /*partition M3 = A11(B12-B22)*/
            CkFuture p3Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p3Future, a11, b12, b22,newSize,'3');
            ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p3Future);

            //the value of P4
            /*OR partition M4 =A22(B21-B11)*/
            CkFuture p4Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p4Future, a22, b21, b11,newSize,'4');
            ValueMsg * m4 = (ValueMsg *) CkWaitFuture(p4Future);

            //the value of P5
            /*OR partition M5 =(A11+A12)B22*/
            CkFuture p5Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p5Future, a11, a12, b22,newSize,'5');
            ValueMsg * m5 = (ValueMsg *) CkWaitFuture(p5Future);

            //the value of P6
            /*partition M6 = (A21-A11)(B11+B12)*/
            CkFuture p6Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p6Future, a21, a11, b11,b12,newSize,'6');
            ValueMsg * m6 = (ValueMsg *) CkWaitFuture(p6Future);

            //the value of P7
            /*OR partition M7 = (A12-A22)(B21+B22)*/
            CkFuture p7Future = CkCreateFuture();
            CProxy_strassenSub::ckNew(p7Future, a12, a22, b21,b22,newSize,'7');
            ValueMsg * m7 = (ValueMsg *) CkWaitFuture(p7Future);



            /*do we need another chare for the C1,C2,C3,C4 ?*/
            /*compute C11 = M1+M4-M5+M7*/
            for (int i = 0; i < newSize; i++){
                for (int j = 0; j < newSize; j++) {
                    c11[i][j] = m1->v[i][j] + m4->v[i][j] - m5->v[i][j] + m7->v[i][j];
                    c12[i][j] = m3->v[i][j] + m5->v[i][j];
                    c21[i][j] = m2->v[i][j] + m4->v[i][j];
                    c22[i][j] = m1->v[i][j] - m2->v[i][j] + m3->v[i][j] + m6->v[i][j];
                } 
            }



            //at this points we should wait for p1,p2,p3... to compute c11,c22,,c12,c21
            //combine it into a big C and return it in the form of a msg

            //to not take into consideration just a chunk of code taken from fib

/*            CkFuture f2 = CkCreateFuture();
            CProxy_strassen::ckNew(size-1, f1);
            CProxy_strassen::ckNew(size-2, f2);
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(f1);
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(f2);
            result = m1->v[0][0] + m2->v[0][0];
            delete m1; 
            delete m2;*/

             // Grouping the results obtained in a single matrix:
            for (int i = 0; i < newSize ; i++) {
                for (int j = 0 ; j < newSize ; j++) {
                    result[i][j] = c11[i][j];
                    result[i][j + newSize] = c12[i][j];
                    result[i + newSize][j] = c21[i][j];
                    result[i + newSize][j + newSize] = c22[i][j];
                }
            }


        }
        ValueMsg *m = new ValueMsg(size);
        m->v = result;
        CkSendToFuture(f, m);
          
    
    }  
};


#include "strassen.def.h"