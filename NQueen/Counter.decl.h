#ifndef _DECL_Counter_H_
#define _DECL_Counter_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
/* DECLS: message countMsg;
 */
class countMsg;
class CMessage_countMsg:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int);
    static void dealloc(void *p);
    CMessage_countMsg();
    static void *pack(countMsg *p);
    static countMsg* unpack(void* p);
    void *operator new(size_t, const int);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

/* DECLS: message DUMMY;
 */
class DUMMY;
class CMessage_DUMMY:public CkMessage{
  public:
    static int __idx;
    void* operator new(size_t, void*p) { return p; }
    void* operator new(size_t);
    void* operator new(size_t, int*, const int);
    void* operator new(size_t, int*);
#if CMK_MULTIPLE_DELETE
    void operator delete(void*p, void*){dealloc(p);}
    void operator delete(void*p){dealloc(p);}
    void operator delete(void*p, int*, const int){dealloc(p);}
    void operator delete(void*p, int*){dealloc(p);}
#endif
    void operator delete(void*p, size_t){dealloc(p);}
    static void* alloc(int,size_t, int*, int);
    static void dealloc(void *p);
    CMessage_DUMMY();
    static void *pack(DUMMY *p);
    static DUMMY* unpack(void* p);
    void *operator new(size_t, const int);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

/* DECLS: group counter: IrrGroup{
counter(DUMMY* impl_msg);
void sendCounts(DUMMY* impl_msg);
void childCount(countMsg* impl_msg);
};
 */
 class counter;
 class CkIndex_counter;
 class CProxy_counter;
 class CProxyElement_counter;
 class CProxySection_counter;
/* --------------- index object ------------------ */
class CkIndex_counter:public CkIndex_IrrGroup{
  public:
    typedef counter local_t;
    typedef CkIndex_counter index_t;
    typedef CProxy_counter proxy_t;
    typedef CProxyElement_counter element_t;
    typedef CProxySection_counter section_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: counter(DUMMY* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_counter_DUMMY();
    // Entry point index lookup
    
    inline static int idx_counter_DUMMY() {
      static int epidx = reg_counter_DUMMY();
      return epidx;
    }

    
    static int ckNew(DUMMY* impl_msg) { return idx_counter_DUMMY(); }
    
    static void _call_counter_DUMMY(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_counter_DUMMY(void* impl_msg, void* impl_obj);
    /* DECLS: void sendCounts(DUMMY* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_sendCounts_DUMMY();
    // Entry point index lookup
    
    inline static int idx_sendCounts_DUMMY() {
      static int epidx = reg_sendCounts_DUMMY();
      return epidx;
    }

    
    inline static int idx_sendCounts(void (counter::*)(DUMMY* impl_msg) ) {
      return idx_sendCounts_DUMMY();
    }


    
    static int sendCounts(DUMMY* impl_msg) { return idx_sendCounts_DUMMY(); }
    
    static void _call_sendCounts_DUMMY(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_sendCounts_DUMMY(void* impl_msg, void* impl_obj);
    /* DECLS: void childCount(countMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_childCount_countMsg();
    // Entry point index lookup
    
    inline static int idx_childCount_countMsg() {
      static int epidx = reg_childCount_countMsg();
      return epidx;
    }

    
    inline static int idx_childCount(void (counter::*)(countMsg* impl_msg) ) {
      return idx_childCount_countMsg();
    }


    
    static int childCount(countMsg* impl_msg) { return idx_childCount_countMsg(); }
    
    static void _call_childCount_countMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_childCount_countMsg(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxyElement_counter: public CProxyElement_IrrGroup{
  public:
    typedef counter local_t;
    typedef CkIndex_counter index_t;
    typedef CProxy_counter proxy_t;
    typedef CProxyElement_counter element_t;
    typedef CProxySection_counter section_t;

    CProxyElement_counter(void) {}
    CProxyElement_counter(const IrrGroup *g) : CProxyElement_IrrGroup(g){  }
    CProxyElement_counter(CkGroupID _gid,int _onPE,CK_DELCTOR_PARAM) : CProxyElement_IrrGroup(_gid,_onPE,CK_DELCTOR_ARGS){  }
    CProxyElement_counter(CkGroupID _gid,int _onPE) : CProxyElement_IrrGroup(_gid,_onPE){  }

    int ckIsDelegated(void) const
    { return CProxyElement_IrrGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxyElement_IrrGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxyElement_IrrGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxyElement_IrrGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxyElement_IrrGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxyElement_IrrGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxyElement_IrrGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_IrrGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxyElement_IrrGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxyElement_IrrGroup::ckSetReductionClient(cb); }
int ckGetGroupPe(void) const
{return CProxyElement_IrrGroup::ckGetGroupPe();}

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxyElement_IrrGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxyElement_IrrGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxyElement_IrrGroup::pup(p); }
    void ckSetGroupID(CkGroupID g) {
      CProxyElement_IrrGroup::ckSetGroupID(g);
    }
    counter* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static counter* ckLocalBranch(CkGroupID gID) {
      return (counter*)CkLocalBranch(gID);
    }
/* DECLS: counter(DUMMY* impl_msg);
 */
    

/* DECLS: void sendCounts(DUMMY* impl_msg);
 */
    
    void sendCounts(DUMMY* impl_msg);

/* DECLS: void childCount(countMsg* impl_msg);
 */
    
    void childCount(countMsg* impl_msg);

};
PUPmarshall(CProxyElement_counter)
/* ---------------- collective proxy -------------- */
class CProxy_counter: public CProxy_IrrGroup{
  public:
    typedef counter local_t;
    typedef CkIndex_counter index_t;
    typedef CProxy_counter proxy_t;
    typedef CProxyElement_counter element_t;
    typedef CProxySection_counter section_t;

    CProxy_counter(void) {}
    CProxy_counter(const IrrGroup *g) : CProxy_IrrGroup(g){  }
    CProxy_counter(CkGroupID _gid,CK_DELCTOR_PARAM) : CProxy_IrrGroup(_gid,CK_DELCTOR_ARGS){  }
    CProxy_counter(CkGroupID _gid) : CProxy_IrrGroup(_gid){  }
    CProxyElement_counter operator[](int onPE) const
      {return CProxyElement_counter(ckGetGroupID(),onPE,CK_DELCTOR_CALL);}

    int ckIsDelegated(void) const
    { return CProxy_IrrGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_IrrGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_IrrGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_IrrGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxy_IrrGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxy_IrrGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxy_IrrGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_IrrGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxy_IrrGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxy_IrrGroup::ckSetReductionClient(cb); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_IrrGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_IrrGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_IrrGroup::pup(p); }
    void ckSetGroupID(CkGroupID g) {
      CProxy_IrrGroup::ckSetGroupID(g);
    }
    counter* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static counter* ckLocalBranch(CkGroupID gID) {
      return (counter*)CkLocalBranch(gID);
    }
/* DECLS: counter(DUMMY* impl_msg);
 */
    
    static CkGroupID ckNew(DUMMY* impl_msg);
    CProxy_counter(DUMMY* impl_msg);

/* DECLS: void sendCounts(DUMMY* impl_msg);
 */
    
    void sendCounts(DUMMY* impl_msg);
    
    void sendCounts(DUMMY* impl_msg, int npes, int *pes);
    
    void sendCounts(DUMMY* impl_msg, CmiGroup &grp);

/* DECLS: void childCount(countMsg* impl_msg);
 */
    
    void childCount(countMsg* impl_msg);
    
    void childCount(countMsg* impl_msg, int npes, int *pes);
    
    void childCount(countMsg* impl_msg, CmiGroup &grp);

};
PUPmarshall(CProxy_counter)
/* ---------------- section proxy -------------- */
class CProxySection_counter: public CProxySection_IrrGroup{
  public:
    typedef counter local_t;
    typedef CkIndex_counter index_t;
    typedef CProxy_counter proxy_t;
    typedef CProxyElement_counter element_t;
    typedef CProxySection_counter section_t;

    CProxySection_counter(void) {}
    CProxySection_counter(const IrrGroup *g) : CProxySection_IrrGroup(g){  }
    CProxySection_counter(const CkGroupID &_gid,const int *_pelist,int _npes,CK_DELCTOR_PARAM) : CProxySection_IrrGroup(_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }
    CProxySection_counter(const CkGroupID &_gid,const int *_pelist,int _npes) : CProxySection_IrrGroup(_gid,_pelist,_npes){  }
    CProxySection_counter(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes) : CProxySection_IrrGroup(n,_gid,_pelist,_npes){  }
    CProxySection_counter(int n,const CkGroupID *_gid, int const * const *_pelist,const int *_npes,CK_DELCTOR_PARAM) : CProxySection_IrrGroup(n,_gid,_pelist,_npes,CK_DELCTOR_ARGS){  }

    int ckIsDelegated(void) const
    { return CProxySection_IrrGroup::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxySection_IrrGroup::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxySection_IrrGroup::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxySection_IrrGroup::ckDelegatedIdx(); }
inline void ckCheck(void) const {CProxySection_IrrGroup::ckCheck();}
CkChareID ckGetChareID(void) const
   {return CProxySection_IrrGroup::ckGetChareID();}
CkGroupID ckGetGroupID(void) const
   {return CProxySection_IrrGroup::ckGetGroupID();}
operator CkGroupID () const { return ckGetGroupID(); }

    inline void setReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_IrrGroup::setReductionClient(fn,param); }
    inline void ckSetReductionClient(CkReductionClientFn fn,void *param=NULL) const
    { CProxySection_IrrGroup::ckSetReductionClient(fn,param); }
    inline void ckSetReductionClient(CkCallback *cb) const
    { CProxySection_IrrGroup::ckSetReductionClient(cb); }
inline int ckGetNumSections() const
{ return CProxySection_IrrGroup::ckGetNumSections(); }
inline CkSectionInfo &ckGetSectionInfo()
{ return CProxySection_IrrGroup::ckGetSectionInfo(); }
inline CkSectionID *ckGetSectionIDs()
{ return CProxySection_IrrGroup::ckGetSectionIDs(); }
inline CkSectionID &ckGetSectionID()
{ return CProxySection_IrrGroup::ckGetSectionID(); }
inline CkSectionID &ckGetSectionID(int i)
{ return CProxySection_IrrGroup::ckGetSectionID(i); }
inline CkGroupID ckGetGroupIDn(int i) const
{ return CProxySection_IrrGroup::ckGetGroupIDn(i); }
inline int *ckGetElements() const
{ return CProxySection_IrrGroup::ckGetElements(); }
inline int *ckGetElements(int i) const
{ return CProxySection_IrrGroup::ckGetElements(i); }
inline int ckGetNumElements() const
{ return CProxySection_IrrGroup::ckGetNumElements(); } 
inline int ckGetNumElements(int i) const
{ return CProxySection_IrrGroup::ckGetNumElements(i); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxySection_IrrGroup::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxySection_IrrGroup::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxySection_IrrGroup::pup(p); }
    void ckSetGroupID(CkGroupID g) {
      CProxySection_IrrGroup::ckSetGroupID(g);
    }
    counter* ckLocalBranch(void) const {
      return ckLocalBranch(ckGetGroupID());
    }
    static counter* ckLocalBranch(CkGroupID gID) {
      return (counter*)CkLocalBranch(gID);
    }
/* DECLS: counter(DUMMY* impl_msg);
 */
    

/* DECLS: void sendCounts(DUMMY* impl_msg);
 */
    
    void sendCounts(DUMMY* impl_msg);

/* DECLS: void childCount(countMsg* impl_msg);
 */
    
    void childCount(countMsg* impl_msg);

};
PUPmarshall(CProxySection_counter)
#define counter_SDAG_CODE 
typedef CBaseT1<Group, CProxy_counter>CBase_counter;



/* ---------------- method closures -------------- */
class Closure_counter {
  public:



};

extern void _registerCounter(void);
#endif
