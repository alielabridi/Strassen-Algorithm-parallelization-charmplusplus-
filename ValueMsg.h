#ifndef STRASSEN_VALUEMSG_H
#define STRASSEN_VALUEMSG_H

class ValueMsg : public CMessage_ValueMsg {
public:
    std::vector<std::vector<int> > v;
    //i found a solution to allocate a non fixed sized without segment fault
    ValueMsg(int size):v(size, std::vector<int>(size)){}
    ValueMsg(){}

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


class AddSubMsg : public CMessage_AddSubMsg  {
public:
    std::vector<std::vector<int> > A;
    std::vector<std::vector<int> > B;
    //i found a solution to allocate a non fixed sized without segment fault
    AddSubMsg(){}
    AddSubMsg(int size){
    	A = std::vector<std::vector<int>> (size,std::vector<int>(size));
    	B = std::vector<std::vector<int>> (size,std::vector<int>(size));
    }

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


class StrassenMsg : public CMessage_StrassenMsg  {
public:
    std::vector<std::vector<int> > A;
    std::vector<std::vector<int> > B;
    //i found a solution to allocate a non fixed sized without segment fault
    StrassenMsg(){}
    StrassenMsg(int size){
    	A = std::vector<std::vector<int>> (size,std::vector<int>(size));
    	B = std::vector<std::vector<int>> (size,std::vector<int>(size));
    }

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };


 class StrassenSubMsg : public CMessage_StrassenSubMsg  {
public:
    std::vector<std::vector<int> > A;
    std::vector<std::vector<int> > B;
    std::vector<std::vector<int> > C;
    std::vector<std::vector<int> > D;
    //i found a solution to allocate a non fixed sized without segment fault
    StrassenSubMsg(){}
    
    StrassenSubMsg(int size){
    	A = std::vector<std::vector<int>> (size,std::vector<int>(size));
    	B = std::vector<std::vector<int>> (size,std::vector<int>(size));
    	C = std::vector<std::vector<int>> (size,std::vector<int>(size));
    	D = std::vector<std::vector<int>> (size,std::vector<int>(size));
    }

    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };
#endif 