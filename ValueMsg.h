
#ifndef STRASSEN_VALUEMSG_H
#define STRASSEN_VALUEMSG_H
#include "pup_stl.h"


class ValueMsg : public CMessage_ValueMsg {
public:
	int size;
	int capacity;
    std::vector<std::vector<int> > v;

/*	int size;
    int **v;*/


    //i found a solution to allocate a non fixed sized without segment fault
    ValueMsg(int size){
    	this->size = size;
    	v = std::vector<std::vector<int>> (size,std::vector<int>(size));
    	capacity = v.capacity();

    	/*v = new int*[size];
    	for (int i = 0; i < size; ++i)
            v[i] = new int[size];*/
    }
/*    ValueMsg(int size, int** p){
    	this->size = size;
    	v = p;
    }
*/


    //for the time being i am going to stick to array as vectors produce segment fault
	static ValueMsg* unpack(void *buf)
	{
	  CkPrintf("M::unpack called\n");
	  char *m = (char *) buf;
	  int size;
	  int capacity;
	  memcpy(&size,m,sizeof(int));
	  memcpy(&capacity,m,sizeof(int));
	  m = m + 2*sizeof(int);

	  int sizeVec = (size)*( sizeof(v) + sizeof(int) * capacity );
	  ValueMsg* pmsg = (ValueMsg*)CkAllocBuffer(buf, sizeVec + 2*sizeof(int));


		CkPrintf("size of ValMsg= %d and others %d is \n",sizeof(ValueMsg),sizeVec+sizeof(int));

/*		CkPrintf("the value of m (size:%d) is \n",size);
int ** iter = (int **)m;
	    for (int i = 0; i < size; ++i)
{
 for (int j = 0; j < size; ++j)
 {
    CkPrintf("%d ",iter[i][j]);
 }
    CkPrintf("\n");

}*/
		pmsg = new ((void*)pmsg) ValueMsg(size);
		for (int i = 0; i < size; ++i)
		 {
		 	pmsg->v[i];
	  		memcpy(&pmsg->v[i],m,sizeVec/size);
	  		m = m + sizeVec/size;

		 } 
		  CkFreeMsg(buf);
		CkPrintf("the result of unpacking \n");

for (int i = 0; i < size; ++i)
{
 for (int j = 0; j < size; ++j)
 {
    CkPrintf("%d ",pmsg->v[i][j]);
 }
    CkPrintf("\n");

}
	  return pmsg;
	}




	static void* pack(ValueMsg* inmsg)
	{
	  CkPrintf("M::pack called\n");

	  	int totalsize = sizeof(int) + sizeof(int) + (inmsg->size)*( sizeof(inmsg->v) + sizeof(int) * (inmsg->v).capacity() );
		//int totalsize = sizeof(int) + (inmsg->size*inmsg->size*sizeof(int)) ;
		char* buf = (char*) CkAllocBuffer(inmsg,totalsize);
		memcpy(buf,&(inmsg->size),sizeof(int));
		memcpy(buf,&(inmsg->capacity),sizeof(int));
		buf = buf + 2*sizeof(int);
		for (int i = 0; i < inmsg->size; ++i)
		{
			memcpy(buf, &inmsg->v[i], sizeof(inmsg->v) + sizeof(int) * inmsg->v.capacity() );
		}
		CkPrintf("the size of the vector = %d",sizeof(inmsg->v));
		buf = buf - 2*sizeof(int);

		/*testing*/
/*		int ** iter = (int **)(buf+sizeof(int));
		CkPrintf("the value of m (size:%d) BEFORE PACKING is \n",inmsg->size);
	    for (int i = 0; i < size; ++i)
		{
			 for (int j = 0; j < size; ++j)
			 {
				CkPrintf("%d ",iter[i][j]);
			 }
			CkPrintf("\n");
		}*/

		return (void*) buf;
	}
    //int v[4][4];
 };
 // allocate memory for varmessage so charm can keep track of memory





/*static void* alloc(int msgnum, size_t size, int* array, int priobits)
{
  int totalsize, first_start, second_start;
  // array is passed in when the message is allocated using new (see below).
  // size is the amount of space needed for the part of the message known
  // about at compile time.  Depending on their values, sometimes a segfault
  // will occur if memory addressing is not on 8-byte boundary, so altered
  // with ALIGN8
  first_start = ALIGN8(size);  // 8-byte align with this macro
  second_start = ALIGN8(first_start + array[0]*sizeof(int));
  totalsize = second_start + array[1]*sizeof(double);
  VarsizeMessage* newMsg = 
    (VarsizeMessage*) CkAllocMsg(msgnum, totalsize, priobits);
  // make firstArray point to end of newMsg in memory
  newMsg->firstArray = (int*) ((char*)newMsg + first_start);
  // make secondArray point to after end of firstArray in memory
  newMsg->secondArray = (double*) ((char*)newMsg + second_start);

  return (void*) newMsg;
}*/

/*// returns pointer to memory containing packed message

static void* pack(VarsizeMessage* in)
{
  // set firstArray an offset from the start of in
  in->firstArray = (int*) ((char*)in->firstArray - (char*)in);
  // set secondArray to the appropriate offset
  in->secondArray = (double*) ((char*)in->secondArray - (char*)in);
  return in;
}

// returns new message from raw memory

static VarsizeMessage* VarsizeMessage::unpack(void* inbuf)
{
  VarsizeMessage* me = (VarsizeMessage*)inbuf;
  // return first array to absolute address in memory
  me->firstArray = (int*) ((size_t)me->firstArray + (char*)me);
  // likewise for secondArray
  me->secondArray = (double*) ((size_t)me->secondArray + (char*)me);
  return me;
}


*/
#endif 