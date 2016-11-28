#ifndef STRASSEN_VALUEMSG_H
#define STRASSEN_VALUEMSG_H

class ValueMsg : public CMessage_ValueMsg {
public:
    int** v;
    //i found a solution to allocate a non fixed sized without segment fault
    ValueMsg(int size){
    	v = new int*[size];
    	for (int i = 0; i < size; ++i){
            v[i] = new int[size];
        }


    }
    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


class AddSubMsg : public CMessage_AddSubMsg  {
public:
    int** A;
    int** B;
    //i found a solution to allocate a non fixed sized without segment fault
    AddSubMsg(int size){
    	A = new int*[size];
    	B = new int*[size];
    	for (int i = 0; i < size; ++i){
            A[i] = new int[size];
            B[i] = new int[size];
        }
    }

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


class StrassenMsg : public CMessage_StrassenMsg  {
public:
    int** A;
    int** B;
    //i found a solution to allocate a non fixed sized without segment fault
    StrassenMsg(int size){
    	A = new int*[size];
    	B = new int*[size];
    	for (int i = 0; i < size; ++i){
            A[i] = new int[size];
            B[i] = new int[size];
        }
    }

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


 class StrassenSubMsg : public CMessage_StrassenSubMsg  {
public:
    int** A;
    int** B;
    int** C;
    int** D;
    //i found a solution to allocate a non fixed sized without segment fault
    
    StrassenSubMsg(int size){
    	A = new int*[size];
    	B = new int*[size];
    	C = new int*[size];
    	D = new int*[size];
    	for (int i = 0; i < size; ++i){
            A[i] = new int[size];
            B[i] = new int[size];
            C[i] = new int[size];
            D[i] = new int[size];
        }
    }

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };
#endif 