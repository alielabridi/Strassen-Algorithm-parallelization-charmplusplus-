
#ifndef STRASSEN_VALUEMSG_H
#define STRASSEN_VALUEMSG_H

class ValueMsg : public CMessage_ValueMsg {
public:
    std::vector<std::vector<int> > v;
    //i found a solution to allocate a non fixed sized without segment fault
    ValueMsg(int size):v(size, std::vector<int>(size)){}
    //for the time being i am going to stick to array as vectors produce segment fault
    //int v[4][4];
 };

#endif 