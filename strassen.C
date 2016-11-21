#include "strassen.decl.h"
int THRESHOLD = 3;
#define VERBOSE 1

/*include in the discussion why choosing arrays vs vector
        array more primitive => takes only what it needs 
        vector get more memory

*/

class AddSubMsgArg : public CMessage_ValueMsg {
public:
    //std::vector<std::vector<int> > v;
    //int v(256,std::vector<int>(256));
    int size;
    CkFuture f;

    int **A;
    int **B;
    //int v[256][256];
    AddSubMsgArg(CkFuture f,int size){
        this->size = size;
        this->f = f;

        A = new int*[size];
        B = new int*[size];
        for (int i = 0; i < size; ++i){
            A[i] = new int[size];
            B[i] = new int[size];
        }
    }

 };

class StrassenSubMsgArg : public CMessage_ValueMsg {
public:
    //std::vector<std::vector<int> > v;
    //int v(256,std::vector<int>(256));
    int size;
    char partition;
    CkFuture f;

    int **A;
    int **B;
    int **C;
    int **D;

    //int v[256][256];
    StrassenSubMsgArg(CkFuture f,int size, char partition){
        this->size = size;
        this->f = f;
        this->partition = partition;

        A = new int*[size];
        B = new int*[size];
        C = new int*[size];
        if(partition == '6' || partition == '7' || partition == '1')
            D = new int*[size];

        for (int i = 0; i < size; ++i){
            A[i] = new int[size];
            B[i] = new int[size];
            C[i] = new int[size];
            /*initilize it only if needed(in 3 partitions out of 7)*/
            if(partition == '6' || partition == '7' || partition == '1')
                D[i] = new int[size];

        }
    }

 };

class StrassenMsgArg : public CMessage_ValueMsg {
public:
    //std::vector<std::vector<int> > v;
    //int v(256,std::vector<int>(256));
    int size;
    CkFuture f;

    int **A;
    int **B;

    //int v[256][256];
    StrassenMsgArg(CkFuture f,int size){
        this->size = size;
        this->f = f;

        A = new int*[size];
        B = new int*[size];
        for (int i = 0; i < size; ++i){
            A[i] = new int[size];
            B[i] = new int[size];
        }
    }

 };


class ValueMsg : public CMessage_ValueMsg {
public:
    //std::vector<std::vector<int> > v;
    //int v(256,std::vector<int>(256));
    int **v;
    //int v[256][256];
    ValueMsg(int size){
        v = new int*[size];
        for (int i = 0; i < size; ++i)
            v[i] = new int[size];
    }

    //i found a solution to allocate a non fixed sized without segment fault
    //ValueMsg(int size):v(size, std::vector<int>(size)){}
    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


class Main : public CBase_Main {
    public: 
        Main(CkMigrateMessage *m) {};
        Main(CkArgMsg * m) { 
            int size;
            if(m->argc > 1)size = atoi(m->argv[1]);
            else size = 8;
            if(m->argc > 2)THRESHOLD = atoi(m->argv[2]);

            thisProxy.run(size);
        }
    void run(int size_) {
        int size = size_;

        int A[size][size];
        int B[size][size];


        /*generate identity matrice of size input*/
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j){
                B[i][j] = 0;
                A[i][j] = 1;
            }
        /*generate identity matrice of one's of size input*/
        for (int i = 0; i < size; ++i)
            B[i][i] = 1;

        /*execution of parralelization*/
        double starttimer = CkWallTimer();
        CkFuture f = CkCreateFuture();
        /*create a message to send a param to strassen*/
        StrassenMsgArg *strassenMsgArg = new StrassenMsgArg(f,size);
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < size; ++i)
                 for (int j = 0; j < size; ++j)
                 {
                    strassenMsgArg->A[i][j] = A[i][j];
                    strassenMsgArg->B[i][j] = B[i][j];
                 }
        CProxy_strassen::ckNew(strassenMsgArg);
        //CProxy_strassen::ckNew(f,A,B,size);
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
        bool correctness = true;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if(m->v[i][j] != A[i][j]) correctness = false;
        if(correctness)
            CkPrintf("Correct: matrix size = %d, Threshold = %d, Exec time = %lf sec \n",  size, THRESHOLD,endtimer-starttimer);
        else
            CkPrintf("Incorrect: matrix size = %d, Threshold = %d, Exec time = %lf sec \n",  size, THRESHOLD,endtimer-starttimer);
               
            
        

        CkExit(); 
    }  
};

class addition :public CBase_addition{
    public:
    addition(CkMigrateMessage *m) {};
    addition(AddSubMsgArg* addSubMsgArg){
        thisProxy.run(addSubMsgArg);
    }
    void run(AddSubMsgArg *addSubMsgArg){

        ValueMsg *m = new ValueMsg(addSubMsgArg->size);

        for (int i = 0; i < addSubMsgArg->size; ++i)
        {
            for (int j = 0; j < addSubMsgArg->size; ++j)
            {
                 m->v[i][j] = addSubMsgArg->A[i][j] + addSubMsgArg->B[i][j];
            }
        }
        /*wrap the resulting substraction in a message of size and send it back to future*/

        CkSendToFuture(addSubMsgArg->f, m);
    }


};

class substraction :public CBase_substraction{
    public:
    substraction(CkMigrateMessage *m) {};
    substraction(AddSubMsgArg* addSubMsgArg){
        thisProxy.run(addSubMsgArg);
    }
    void run(AddSubMsgArg* addSubMsgArg){
        ValueMsg *m = new ValueMsg(addSubMsgArg->size);

        for (int i = 0; i < addSubMsgArg->size; ++i)
        {
            for (int j = 0; j < addSubMsgArg->size; ++j)
            {
                 m->v[i][j] = addSubMsgArg->A[i][j] - addSubMsgArg->B[i][j];
            }
        }
        /*wrap the resulting substraction in a message of size and send it back to future*/

        CkSendToFuture(addSubMsgArg->f, m);
    }
};

class strassenSub: public CBase_strassenSub{
public:
    strassenSub(CkMigrateMessage *m) {};
    //overload the function to take three matrices or four
    //how should I adapt the class to implement for substraction
    /*four additions*/
    strassenSub(StrassenSubMsgArg *strassenSubMsgArg){ thisProxy.run(strassenSubMsgArg); }


    void run(StrassenSubMsgArg *strassenSubMsgArg){
    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    if(strassenSubMsgArg->partition == '1'){
        //if(VERBOSE)CkPrintf("here stressen SUB run 1:\n");

        /*first partition M1 = (A11+A22)(B11+B22)*/
        CkFuture p1add1 = CkCreateFuture(); //A11+A22
        CkFuture p1add2 = CkCreateFuture(); //B11+B22
        //i could spawn all the additions needed here   
        //if(VERBOSE)CkPrintf("here stressen SUB run 2:\n");


        AddSubMsgArg *addSubMsgArg1 = new AddSubMsgArg(p1add1,strassenSubMsgArg->size);
        AddSubMsgArg *addSubMsgArg2 = new AddSubMsgArg(p1add2,strassenSubMsgArg->size);

        /*copy the values of the matrices in argmsgs*/
        for (int i = 0; i < strassenSubMsgArg->size; ++i)
            for (int j = 0; j < strassenSubMsgArg->size; ++j)
            {
                addSubMsgArg1->A[i][j] = strassenSubMsgArg->A[i][j];
                addSubMsgArg1->B[i][j] = strassenSubMsgArg->B[i][j];
                addSubMsgArg2->A[i][j] = strassenSubMsgArg->C[i][j];
                addSubMsgArg2->B[i][j] = strassenSubMsgArg->D[i][j];
            }

        CProxy_addition::ckNew(addSubMsgArg1);//param not matching yet just a pseudo code
        CProxy_addition::ckNew(addSubMsgArg2);//param not matching yet just a pseudo code
        //if(VERBOSE)CkPrintf("here stressen SUB run 3:\n");

        //ValueMsg *m1 = new ValueMsg(size);
        //ValueMsg *m2 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1add1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p1add2);



        CkFuture p1 = CkCreateFuture();
        //if(VERBOSE)CkPrintf("here stressen SUB run 5:\n");

        /*create a message to send a param to strassen*/
        StrassenMsgArg *strassenMsgArg = new StrassenMsgArg(p1,strassenSubMsgArg->size);
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < strassenSubMsgArg->size; ++i)
                 for (int j = 0; j < strassenSubMsgArg->size; ++j)
                 {
                    strassenMsgArg->A[i][j] = m1->v[i][j];
                    strassenMsgArg->B[i][j] = m2->v[i][j];
                 }
            //CProxy
        //CProxy_strassen::ckNew(p1,m1->v,m2->v,strassenSubMsgArg->size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        CProxy_strassen::ckNew(strassenMsgArg); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //if(VERBOSE)CkPrintf("here stressen SUB run 6:\n");

        //i could free m1 and m2 at this point
        delete m1;
        delete m2;
        //if(VERBOSE)CkPrintf("here stressen SUB run 7:\n");

        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p1);
        //if(VERBOSE)CkPrintf("here stressen SUB run 8:\n");

        CkSendToFuture(strassenSubMsgArg->f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    }    

    else if(strassenSubMsgArg->partition == '6' || strassenSubMsgArg->partition == '7'){
        /*partition M6 = (A21-A11)(B11+B12)*/
        /*OR partition M7 = (A12-A22)(B21+B22)*/
        CkFuture psub1 = CkCreateFuture(); 
        CkFuture padd2 = CkCreateFuture(); 

        AddSubMsgArg *addSubMsgArg1 = new AddSubMsgArg(psub1,strassenSubMsgArg->size);
        AddSubMsgArg *addSubMsgArg2 = new AddSubMsgArg(padd2,strassenSubMsgArg->size);

        /*copy the values of the matrices in argmsgs*/
        for (int i = 0; i < strassenSubMsgArg->size; ++i)
            for (int j = 0; j < strassenSubMsgArg->size; ++j)
            {
                addSubMsgArg1->A[i][j] = strassenSubMsgArg->A[i][j];
                addSubMsgArg1->B[i][j] = strassenSubMsgArg->B[i][j];
                addSubMsgArg2->A[i][j] = strassenSubMsgArg->C[i][j];
                addSubMsgArg2->B[i][j] = strassenSubMsgArg->D[i][j];
            }


        //i could spawn all the additions needed here   
        CProxy_substraction::ckNew(addSubMsgArg1);//param not matching yet just a pseudo code
        CProxy_addition::ckNew(addSubMsgArg2);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        //ValueMsg *m2 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        ValueMsg * m2 = (ValueMsg *) CkWaitFuture(padd2);
        CkFuture p = CkCreateFuture();
        /*create a message to send a param to strassen*/
        StrassenMsgArg *strassenMsgArg = new StrassenMsgArg(p,strassenSubMsgArg->size);
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < strassenSubMsgArg->size; ++i)
                 for (int j = 0; j < strassenSubMsgArg->size; ++j)
                 {
                    strassenMsgArg->A[i][j] = m1->v[i][j];
                    strassenMsgArg->B[i][j] = m2->v[i][j];
                 }
        //CProxy_strassen::ckNew(p, m1->v,m2->v, strassenSubMsgArg->size); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        CProxy_strassen::ckNew(strassenMsgArg); //to do (A11+A22)*(B11+B22) by giving m1->v and m2->v
        //i could free m1 and m2 at this point
        delete m1;
        delete m2;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        CkSendToFuture(strassenSubMsgArg->f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    }  


    /*THREE MATRICES ONLY*/

    //do the addition/substraction, and wait for for the result then call on it the bigger strassen chare
    //if needed a big multiplication
    //inside the bigger strassen chare it will decide whether to use the naive or strassen algo
    else if(strassenSubMsgArg->partition == '2' || strassenSubMsgArg->partition == '5'){
        /*partition M2 =(A21+A22)B11*/
        /*OR partition M5 =(A11+A12)B22*/
        CkFuture padd1 = CkCreateFuture(); 
        //i could spawn all the additions needed here   
        AddSubMsgArg *addSubMsgArg1 = new AddSubMsgArg(padd1,strassenSubMsgArg->size);
        /*copy the values of the matrices in argmsgs*/
        for (int i = 0; i < strassenSubMsgArg->size; ++i)
            for (int j = 0; j < strassenSubMsgArg->size; ++j)
            {
                addSubMsgArg1->A[i][j] = strassenSubMsgArg->A[i][j];
                addSubMsgArg1->B[i][j] = strassenSubMsgArg->B[i][j];
            }
        CProxy_addition::ckNew(addSubMsgArg1);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(padd1);
        CkFuture p = CkCreateFuture();
/*        int Y[size];
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                Y[i][j] = m1->v[i][j];
            }
        }*/
        /*create a message to send a param to strassen*/
        StrassenMsgArg *strassenMsgArg = new StrassenMsgArg(p,strassenSubMsgArg->size);
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < strassenSubMsgArg->size; ++i)
                 for (int j = 0; j < strassenSubMsgArg->size; ++j)
                 {
                    strassenMsgArg->A[i][j] = m1->v[i][j];
                    strassenMsgArg->B[i][j] = strassenSubMsgArg->C[i][j];
                 }
        //CProxy_strassen::ckNew(p,m1->v,C, strassenSubMsgArg->size); 
        CProxy_strassen::ckNew(strassenMsgArg); 
        //i could free m1 and m2 at this point
        delete m1;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        CkSendToFuture(strassenSubMsgArg->f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    } 
    else if(strassenSubMsgArg->partition == '3' || strassenSubMsgArg->partition == '4'){
        /*partition M3 = A11(B12-B22)*/
        /*OR partition M4 =A22(B21-B11)*/
        CkFuture psub1 = CkCreateFuture(); 
        //i could spawn all the additions needed here  
        AddSubMsgArg *addSubMsgArg1 = new AddSubMsgArg(psub1,strassenSubMsgArg->size); 
        /*copy the values of the matrices in argmsgs*/
        for (int i = 0; i < strassenSubMsgArg->size; ++i)
            for (int j = 0; j < strassenSubMsgArg->size; ++j)
            {
                addSubMsgArg1->A[i][j] = strassenSubMsgArg->B[i][j];
                addSubMsgArg1->B[i][j] = strassenSubMsgArg->C[i][j];
            }

        CProxy_substraction::ckNew(addSubMsgArg1);//param not matching yet just a pseudo code
        //ValueMsg *m1 = new ValueMsg(size);
        ValueMsg * m1 = (ValueMsg *) CkWaitFuture(psub1);
        CkFuture p = CkCreateFuture();
/*        int Y[size];
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                Y[i][j] = m1->v[i][j];
            }
        }*/
        /*create a message to send a param to strassen*/
        StrassenMsgArg *strassenMsgArg = new StrassenMsgArg(p,strassenSubMsgArg->size);
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < strassenSubMsgArg->size; ++i)
                 for (int j = 0; j < strassenSubMsgArg->size; ++j)
                 {
                    strassenMsgArg->A[i][j] = m1->v[i][j];
                    strassenMsgArg->B[i][j] = strassenSubMsgArg->A[i][j];
                 }
        //CProxy_strassen::ckNew(p,m1->v,C, strassenSubMsgArg->size); 
        CProxy_strassen::ckNew(strassenMsgArg); 
        //CProxy_strassen::ckNew(p,A,m1->v, strassenSubMsgArg->size); 
        //i could free m1 and m2 at this point
        delete m1;
        //ValueMsg *m3 = new ValueMsg(size);
        ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p);
        CkSendToFuture(strassenSubMsgArg->f, m3);
        //p1 = m3->v; //returned product of the two summation
        //i can free m3 at this point
        // thinking of using CkProbeFuture on (p1,p2,p3...) instead of wait to not block the next products
        //or should I use a block instead? UPDATES: I guess by now that I am using strassenSub It will be ok   
    } 


    }


};
class strassen : public CBase_strassen  {


    public:  
    strassen(CkMigrateMessage *m) {};
    strassen(StrassenMsgArg* strassenMsgArg){ thisProxy.run(strassenMsgArg); }


    void run(StrassenMsgArg* strassenMsgArg) {
            ValueMsg *m = new ValueMsg(strassenMsgArg->size);

            //if(VERBOSE)CkPrintf("here stressen run 1:\n");

/*            std::vector<int> inner (newSize);
            std::vector< std::vector<int> > 
            a11(newSize,inner), a12(newSize,inner), a21(newSize,inner), a22(newSize,inner),
            b11(newSize,inner), b12(newSize,inner), b21(newSize,inner), b22(newSize,inner),*/

        //if (n< THRESHOLD)
        /*naive matrix multiplication used under THRESHOLD*/
        if(strassenMsgArg->size < THRESHOLD){

             for (int i = 0; i < strassenMsgArg->size; i++) {
                for (int k = 0; k < strassenMsgArg->size; k++) {
                    m->v[i][k] = 0;
                    for (int j = 0; j < strassenMsgArg->size; j++) {
                        m->v[i][k] += strassenMsgArg->A[i][j] * strassenMsgArg->B[j][k];
                    }
                }
            }
            // if(VERBOSE)CkPrintf("computation done by ikjalgorithm\n");        


        }
        else {

            int newSize = strassenMsgArg->size/2;
            // int a11[newSize][newSize];
            // int a12[newSize][newSize];
            // int a21[newSize][newSize];
            // int a22[newSize][newSize];

            // int b11[newSize][newSize];
            // int b12[newSize][newSize];
            // int b21[newSize][newSize];
            // int b22[newSize][newSize];
            //if(VERBOSE)CkPrintf("here stressen run 4:\n");

        //dividing the matrices in 4 sub-matrices:
        //NO NEED TO DIVIDE NOW AS WE WILL PASS THEM DIRECTLY
        // for (int i = 0; i < newSize; i++) {
        //     for (int j = 0; j < newSize; j++) {
        //         a11[i][j] = strassenMsgArg->A[i][j];
        //         a12[i][j] = strassenMsgArg->A[i][j + newSize]; //*A[i][j+newSize] (NOPE]
        //         a21[i][j] = strassenMsgArg->A[i + newSize][j];
        //         a22[i][j] = strassenMsgArg->A[i + newSize][j + newSize];

        //         b11[i][j] = strassenMsgArg->B[i][j];
        //         b12[i][j] = strassenMsgArg->B[i][j + newSize];
        //         b21[i][j] = strassenMsgArg->B[i + newSize][j];
        //         b22[i][j] = strassenMsgArg->B[i + newSize][j + newSize];
        //     }
        // }
            //if(VERBOSE)CkPrintf("here stressen run 4-1:\n");

  
            //declaration of submatrices needed here
            
            // call for future (p1,p2....p7) with future then recolt the result

            //do the next computation with it
            /*four addition*/
            //the value of P1
            /*M1 = (A11+A22)(B11+B22)*/
            CkFuture p1Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg1 = new StrassenSubMsgArg(p1Future,newSize,'1');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg1->A[i][j] = strassenMsgArg->A[i][j]; //a11
                    strassenSubMsgArg1->B[i][j] = strassenMsgArg->A[i + newSize][j + newSize];//a22
                    strassenSubMsgArg1->C[i][j] = strassenMsgArg->B[i][j]; //b11
                    strassenSubMsgArg1->D[i][j] = strassenMsgArg->B[i + newSize][j + newSize];//b22

                 }

            //CProxy_strassenSub::ckNew(p1Future, a11, a22, b11, b22,newSize,'1');
            CProxy_strassenSub::ckNew(strassenSubMsgArg1);
            ValueMsg * m1 = (ValueMsg *) CkWaitFuture(p1Future);
            //if(VERBOSE)CkPrintf("here stressen run 5:\n");
            if(VERBOSE)CkPrintf("done with m1 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m1->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);


            /*three addition*/
            //the value of P2
            /*partition M2 =(A21+A22)B11*/
            CkFuture p2Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg2 = new StrassenSubMsgArg(p2Future,newSize,'2');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg2->A[i][j] = strassenMsgArg->A[i + newSize][j]; // a21
                    strassenSubMsgArg2->B[i][j] = strassenMsgArg->A[i + newSize][j + newSize];//a22
                    strassenSubMsgArg2->C[i][j] = strassenMsgArg->B[i][j]; //b11
                 }
            //CProxy_strassenSub::ckNew(p2Future, a21, a22, b11,newSize,'2');
            CProxy_strassenSub::ckNew(strassenSubMsgArg2);
            ValueMsg * m2 = (ValueMsg *) CkWaitFuture(p2Future);
            //if(VERBOSE)CkPrintf("here stressen run 6:\n of size %d\n",newSize);
            if(VERBOSE)CkPrintf("done with m2 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m2->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);





            //the value of P3
            /*partition M3 = A11(B12-B22)*/
            CkFuture p3Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg3 = new StrassenSubMsgArg(p3Future,newSize,'3');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg3->A[i][j] = strassenMsgArg->A[i][j]; //a11
                    strassenSubMsgArg3->B[i][j] = strassenMsgArg->B[i][j + newSize]; //b12
                    strassenSubMsgArg3->C[i][j] = strassenMsgArg->B[i + newSize][j + newSize]; //b22
                 }
            //CProxy_strassenSub::ckNew(p3Future, a11, b12, b22,newSize,'3');
            CProxy_strassenSub::ckNew(strassenSubMsgArg3);
            ValueMsg * m3 = (ValueMsg *) CkWaitFuture(p3Future);
            if(VERBOSE)CkPrintf("done with m3 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m3->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);

            //if(VERBOSE)CkPrintf("here stressen run 7:\n of size %d\n",newSize);



            //the value of P4
            /*OR partition M4 =A22(B21-B11)*/
            CkFuture p4Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg4 = new StrassenSubMsgArg(p4Future,newSize,'4');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg4->A[i][j] = strassenMsgArg->A[i + newSize][j + newSize]; // a22
                    strassenSubMsgArg4->B[i][j] = strassenMsgArg->B[i + newSize][j]; //b21
                    strassenSubMsgArg4->C[i][j] = strassenMsgArg->B[i][j]; //b11
                 }
            //CProxy_strassenSub::ckNew(p4Future, a22, b21, b11,newSize,'4');
            CProxy_strassenSub::ckNew(strassenSubMsgArg4);
            ValueMsg * m4 = (ValueMsg *) CkWaitFuture(p4Future);
            //if(VERBOSE)CkPrintf("here stressen run 8:\n of size %d\n",newSize);
            if(VERBOSE)CkPrintf("done with m4 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m4->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);



            //the value of P5
            /*OR partition M5 =(A11+A12)B22*/
            CkFuture p5Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg5 = new StrassenSubMsgArg(p5Future,newSize,'5');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg5->A[i][j] = strassenMsgArg->A[i][j]; //a11
                    strassenSubMsgArg5->B[i][j] = strassenMsgArg->A[i][j + newSize]; //a12
                    strassenSubMsgArg5->C[i][j] = strassenMsgArg->B[i + newSize][j + newSize]; //b22
                 }
            //CProxy_strassenSub::ckNew(p5Future, a11, a12, b22,newSize,'5');
            CProxy_strassenSub::ckNew(strassenSubMsgArg5);
            ValueMsg * m5 = (ValueMsg *) CkWaitFuture(p5Future);
            //if(VERBOSE)CkPrintf("here stressen run 9:\n");
            if(VERBOSE)CkPrintf("done with m5 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m5->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);


            //the value of P6
            /*partition M6 = (A21-A11)(B11+B12)*/
            CkFuture p6Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg6 = new StrassenSubMsgArg(p6Future,newSize,'6');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg6->A[i][j] = strassenMsgArg->A[i + newSize][j]; // a21
                    strassenSubMsgArg6->B[i][j] = strassenMsgArg->A[i][j]; //a11
                    strassenSubMsgArg6->C[i][j] = strassenMsgArg->B[i][j]; //b11
                    strassenSubMsgArg6->D[i][j] = strassenMsgArg->B[i][j + newSize]; //b12
                 }
            //CProxy_strassenSub::ckNew(p6Future, a21, a11, b11,b12,newSize,'6');
            CProxy_strassenSub::ckNew(strassenSubMsgArg6);
            ValueMsg * m6 = (ValueMsg *) CkWaitFuture(p6Future);
            //if(VERBOSE)CkPrintf("here stressen run 10:\n");
            if(VERBOSE)CkPrintf("done with m6 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m6->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);


            //the value of P7
            /*OR partition M7 = (A12-A22)(B21+B22)*/
            CkFuture p7Future = CkCreateFuture();
            /*create a message to send a param to strassenSub*/
            StrassenSubMsgArg *strassenSubMsgArg7 = new StrassenSubMsgArg(p7Future,newSize,'7');
            /*copy the sub matrices need for each op*/
             for (int i = 0; i < newSize; ++i)
                 for (int j = 0; j < newSize; ++j)
                 {
                    strassenSubMsgArg7->A[i][j] = strassenMsgArg->A[i][j + newSize]; //a12
                    strassenSubMsgArg7->B[i][j] = strassenMsgArg->A[i + newSize][j + newSize]; // a22
                    strassenSubMsgArg7->C[i][j] = strassenMsgArg->B[i + newSize][j]; //b21
                    strassenSubMsgArg7->D[i][j] = strassenMsgArg->B[i + newSize][j + newSize]; //b22
                 }
            //CProxy_strassenSub::ckNew(p7Future, a12, a22, b21,b22,newSize,'7');
            CProxy_strassenSub::ckNew(strassenSubMsgArg7);
            ValueMsg * m7 = (ValueMsg *) CkWaitFuture(p7Future);
            //if(VERBOSE)CkPrintf("here stressen run 11:\n");
            if(VERBOSE)CkPrintf("done with m7 of size %d\n",newSize);
            if(VERBOSE)CkPrintf("resulting matrix %d\n",newSize);
            if(VERBOSE){
                for (int i = 0; i < newSize; ++i){
                    for (int j = 0; j < newSize; ++j)
                        CkPrintf("%d ", m7->v[i][j]);
                CkPrintf("\n");

                }

            }
            if(VERBOSE)CkPrintf("------------------ \n",newSize);



            /*do we need another chare for the C1,C2,C3,C4 ?*/
            /*we should say why we didn't parralized the C1,C2,C3,C4
                    too much message passing
                    shared data
                    creation share expense vs just compute it
            */
            /*compute C11 = M1+M4-M5+M7*/

            //at this points we should wait for p1,p2,p3... to compute c11,c22,,c12,c21
            //combine it into a big C and return it in the form of a msgs

             // Grouping the results obtained in a single matrix:
            for (int i = 0; i < newSize; i++){
                for (int j = 0; j < newSize; j++) {
                    m->v[i][j] = m1->v[i][j] + m4->v[i][j] - m5->v[i][j] + m7->v[i][j];
                    m->v[i][j + newSize] = m3->v[i][j] + m5->v[i][j];
                    m->v[i + newSize][j] = m2->v[i][j] + m4->v[i][j];
                    m->v[i + newSize][j + newSize] = m1->v[i][j] - m2->v[i][j] + m3->v[i][j] + m6->v[i][j];
                     CkPrintf("%d", m1->v[i][j] + m4->v[i][j] - m5->v[i][j] + m7->v[i][j]);
                    CkPrintf("%d", m3->v[i][j] + m5->v[i][j]);
                    CkPrintf("%d", m2->v[i][j] + m4->v[i][j]);
                    CkPrintf("%d ", m1->v[i][j] - m2->v[i][j] + m3->v[i][j] + m6->v[i][j]);
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





/*            for (int i = 0; i < newSize ; i++) {
                for (int j = 0 ; j < newSize ; j++) {
                    m->v[i][j] = c11[i][j];
                    m->v[i].[j + newSize] = c12[i][j];
                    m->v[i + newSize][j] = c21[i][j];
                    m->v[i + newSize][j + newSize] = c22[i][j];
                }
            }*/
            //if(VERBOSE)CkPrintf("here stressen run 13:\n");

        if(VERBOSE)CkPrintf("The resulting matrix is :\n");

        for(int i=0; i<2*newSize;i++){
            for (int j = 0; j < 2*newSize; ++j)
            {
                /* code */
                if(VERBOSE)CkPrintf("%d ",m->v[i][j]);
            }
                if(VERBOSE)CkPrintf("\n");
        }

        }
            //if(VERBOSE)CkPrintf("here stressen run 14:\n");



        // for(int i=0; i<size;i++)
        //     for (int j = 0; j < size; ++j)
        //         m->v[i][j] = result[i][j];

        // //m->v = result;

        CkSendToFuture(strassenMsgArg->f, m);
            //if(VERBOSE)CkPrintf("here stressen run 15:\n");


          
    
    }  
};


#include "strassen.def.h"