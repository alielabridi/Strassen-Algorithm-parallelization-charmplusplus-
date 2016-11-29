
#ifndef STRASSEN_VALUEMSG_H
#define STRASSEN_VALUEMSG_H
#include "pup_stl.h"


class ValueMsg : public CMessage_ValueMsg {
public:

    /*std::vector<std::vector<int> > v;
*/
	int size;
    int **v;


    //i found a solution to allocate a non fixed sized without segment fault
    ValueMsg(int size){
    	this->size = size;
    	v = new int*[size];
    	for (int i = 0; i < size; ++i)
            v[i] = new int[size];
    }



    //for the time being i am going to stick to array as vectors produce segment fault
	static ValueMsg* unpack(void *buf)
	{
	  // CkPrintf("M::unpack called\n");
	  char *bufChar = (char *) buf;
	  int size;
	  memcpy(&size,bufChar,sizeof(int));


	  ValueMsg* pmsg = (ValueMsg*)CkAllocBuffer(buf, sizeof(ValueMsg));




		pmsg = new ((void*)pmsg) ValueMsg(size); 
		for (int i = 0; i < size; ++i)
			memcpy(&(pmsg->v[i][0]),bufChar+sizeof(int)+i*sizeof(int)*size, sizeof(int)*size);
/*testing display*/
/*		int* bufInt = (int *) buf;
		for (int i = 0; i < size*size + 1; ++i)
			CkPrintf("the element %d in buffer(unpack) : %d\n", i,*(bufInt+i));
	    //CkExit(); 
		CkPrintf("the result of unpacking \n");

		for (int i = 0; i < size; ++i)
		{
			 for (int j = 0; j < size; ++j)
			    CkPrintf("%d|",pmsg->v[i][j]);
			CkPrintf("\n");
		}*/

		CkFreeMsg(buf);

	  return pmsg;
	}



	static void* pack(ValueMsg* inmsg)
	{
	  // CkPrintf("M::pack called\n");
	  	int size = inmsg->size;
		int totalsize = sizeof(int) + (size* sizeof(int) * size);
		char* buf = (char*) CkAllocBuffer(inmsg,totalsize);

		
		memcpy(buf,&(size),sizeof(int));

		for (int i = 0; i < size; ++i)
			memcpy(buf+sizeof(int)+i*sizeof(int)*size, &(inmsg->v[i][0]), sizeof(int)*size);


		/*testing display*/
		/*for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				CkPrintf("%d|",inmsg->v[i][j]);
			}
			CkPrintf("\n");
		}

		int* bufInt = (int *) buf;
		for (int i = 0; i < size*size + 1; ++i)
			CkPrintf("the element %d in buffer(pack) : %d\n", i,*(bufInt+i));
		*/

		delete inmsg;
		return (void*) buf;
	}
 };
 // allocate memory for varmessage so charm can keep track of memory


#endif 