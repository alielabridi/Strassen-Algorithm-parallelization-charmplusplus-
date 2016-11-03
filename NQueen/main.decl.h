#ifndef _DECL_main_H_
#define _DECL_main_H_
#include "charm++.h"
#include "envelope.h"
#include <memory>
#include "sdag.h"
#include "Counter.decl.h"

/* DECLS: readonly int numQueens;
 */

/* DECLS: readonly int grainsize;
 */

/* DECLS: readonly CkGroupID counterGroup;
 */

/* DECLS: readonly int mask;
 */

/* DECLS: message QueenState;
 */
class QueenState;
class CMessage_QueenState:public CkMessage{
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
    CMessage_QueenState();
    static void *pack(QueenState *p);
    static QueenState* unpack(void* p);
    void *operator new(size_t, const int);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

/* DECLS: message DUMMYMSG;
 */
class DUMMYMSG;
class CMessage_DUMMYMSG:public CkMessage{
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
    CMessage_DUMMYMSG();
    static void *pack(DUMMYMSG *p);
    static DUMMYMSG* unpack(void* p);
    void *operator new(size_t, const int);
#if CMK_MULTIPLE_DELETE
    void operator delete(void *p, const int){dealloc(p);}
#endif
    static void __register(const char *s, size_t size, CkPackFnPtr pack, CkUnpackFnPtr unpack) {
      __idx = CkRegisterMsg(s, pack, unpack, dealloc, size);
    }
};

/* DECLS: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
threaded void Quiescence1(DUMMYMSG* impl_msg);
};
 */
 class Main;
 class CkIndex_Main;
 class CProxy_Main;
/* --------------- index object ------------------ */
class CkIndex_Main:public CkIndex_Chare{
  public:
    typedef Main local_t;
    typedef CkIndex_Main index_t;
    typedef CProxy_Main proxy_t;
    typedef CProxy_Main element_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: Main(CkArgMsg* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Main_CkArgMsg();
    // Entry point index lookup
    
    inline static int idx_Main_CkArgMsg() {
      static int epidx = reg_Main_CkArgMsg();
      return epidx;
    }

    
    static int ckNew(CkArgMsg* impl_msg) { return idx_Main_CkArgMsg(); }
    
    static void _call_Main_CkArgMsg(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Main_CkArgMsg(void* impl_msg, void* impl_obj);
    /* DECLS: threaded void Quiescence1(DUMMYMSG* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_Quiescence1_DUMMYMSG();
    // Entry point index lookup
    
    inline static int idx_Quiescence1_DUMMYMSG() {
      static int epidx = reg_Quiescence1_DUMMYMSG();
      return epidx;
    }

    
    inline static int idx_Quiescence1(void (Main::*)(DUMMYMSG* impl_msg) ) {
      return idx_Quiescence1_DUMMYMSG();
    }


    
    static int Quiescence1(DUMMYMSG* impl_msg) { return idx_Quiescence1_DUMMYMSG(); }
    
    static void _call_Quiescence1_DUMMYMSG(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_Quiescence1_DUMMYMSG(void* impl_msg, void* impl_obj);
    
    static void _callthr_Quiescence1_DUMMYMSG(CkThrCallArg *);
};
/* --------------- element proxy ------------------ */
class CProxy_Main:public CProxy_Chare{
  public:
    typedef Main local_t;
    typedef CkIndex_Main index_t;
    typedef CProxy_Main proxy_t;
    typedef CProxy_Main element_t;

    CProxy_Main(void) {};
    CProxy_Main(CkChareID __cid) : CProxy_Chare(__cid){  }
    CProxy_Main(const Chare *c) : CProxy_Chare(c){  }

    int ckIsDelegated(void) const
    { return CProxy_Chare::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_Chare::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_Chare::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_Chare::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_Chare::ckCheck(); }
    const CkChareID &ckGetChareID(void) const
    { return CProxy_Chare::ckGetChareID(); }
    operator const CkChareID &(void) const
    { return ckGetChareID(); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_Chare::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_Chare::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_Chare::pup(p); }

    void ckSetChareID(const CkChareID &c)
    {      CProxy_Chare::ckSetChareID(c); }
    Main *ckLocal(void) const
    { return (Main *)CkLocalChare(&ckGetChareID()); }
/* DECLS: Main(CkArgMsg* impl_msg);
 */
    static CkChareID ckNew(CkArgMsg* impl_msg, int onPE=CK_PE_ANY);
    static void ckNew(CkArgMsg* impl_msg, CkChareID* pcid, int onPE=CK_PE_ANY);
    CProxy_Main(CkArgMsg* impl_msg, int onPE=CK_PE_ANY);

/* DECLS: threaded void Quiescence1(DUMMYMSG* impl_msg);
 */
    
    void Quiescence1(DUMMYMSG* impl_msg);

};
PUPmarshall(CProxy_Main)
#define Main_SDAG_CODE 
typedef CBaseT1<Chare, CProxy_Main>CBase_Main;

/* DECLS: chare NQueen: Chare{
NQueen(QueenState* impl_msg);
};
 */
 class NQueen;
 class CkIndex_NQueen;
 class CProxy_NQueen;
/* --------------- index object ------------------ */
class CkIndex_NQueen:public CkIndex_Chare{
  public:
    typedef NQueen local_t;
    typedef CkIndex_NQueen index_t;
    typedef CProxy_NQueen proxy_t;
    typedef CProxy_NQueen element_t;

    static int __idx;
    static void __register(const char *s, size_t size);
    /* DECLS: NQueen(QueenState* impl_msg);
     */
    // Entry point registration at startup
    
    static int reg_NQueen_QueenState();
    // Entry point index lookup
    
    inline static int idx_NQueen_QueenState() {
      static int epidx = reg_NQueen_QueenState();
      return epidx;
    }

    
    static int ckNew(QueenState* impl_msg) { return idx_NQueen_QueenState(); }
    
    static void _call_NQueen_QueenState(void* impl_msg, void* impl_obj);
    
    static void _call_sdag_NQueen_QueenState(void* impl_msg, void* impl_obj);
};
/* --------------- element proxy ------------------ */
class CProxy_NQueen:public CProxy_Chare{
  public:
    typedef NQueen local_t;
    typedef CkIndex_NQueen index_t;
    typedef CProxy_NQueen proxy_t;
    typedef CProxy_NQueen element_t;

    CProxy_NQueen(void) {};
    CProxy_NQueen(CkChareID __cid) : CProxy_Chare(__cid){  }
    CProxy_NQueen(const Chare *c) : CProxy_Chare(c){  }

    int ckIsDelegated(void) const
    { return CProxy_Chare::ckIsDelegated(); }
    inline CkDelegateMgr *ckDelegatedTo(void) const
    { return CProxy_Chare::ckDelegatedTo(); }
    inline CkDelegateData *ckDelegatedPtr(void) const
    { return CProxy_Chare::ckDelegatedPtr(); }
    CkGroupID ckDelegatedIdx(void) const
    { return CProxy_Chare::ckDelegatedIdx(); }

    inline void ckCheck(void) const
    { CProxy_Chare::ckCheck(); }
    const CkChareID &ckGetChareID(void) const
    { return CProxy_Chare::ckGetChareID(); }
    operator const CkChareID &(void) const
    { return ckGetChareID(); }

    void ckDelegate(CkDelegateMgr *dTo,CkDelegateData *dPtr=NULL)
    {       CProxy_Chare::ckDelegate(dTo,dPtr); }
    void ckUndelegate(void)
    {       CProxy_Chare::ckUndelegate(); }
    void pup(PUP::er &p)
    {       CProxy_Chare::pup(p); }

    void ckSetChareID(const CkChareID &c)
    {      CProxy_Chare::ckSetChareID(c); }
    NQueen *ckLocal(void) const
    { return (NQueen *)CkLocalChare(&ckGetChareID()); }
/* DECLS: NQueen(QueenState* impl_msg);
 */
    static CkChareID ckNew(QueenState* impl_msg, int onPE=CK_PE_ANY);
    static void ckNew(QueenState* impl_msg, CkChareID* pcid, int onPE=CK_PE_ANY);
    CProxy_NQueen(QueenState* impl_msg, int onPE=CK_PE_ANY);

};
PUPmarshall(CProxy_NQueen)
#define NQueen_SDAG_CODE 
typedef CBaseT1<Chare, CProxy_NQueen>CBase_NQueen;








/* ---------------- method closures -------------- */
class Closure_Main {
  public:


};

/* ---------------- method closures -------------- */
class Closure_NQueen {
  public:

};

extern void _registermain(void);
extern "C" void CkRegisterMainModule(void);
#endif
