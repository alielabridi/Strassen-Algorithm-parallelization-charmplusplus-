






/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */


/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */



/* DEFS: readonly int numQueens;
 */
extern int numQueens;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_numQueens(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|numQueens;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly int grainsize;
 */
extern int grainsize;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_grainsize(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|grainsize;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly CkGroupID counterGroup;
 */
extern CkGroupID counterGroup;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_counterGroup(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|counterGroup;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: readonly int mask;
 */
extern int mask;
#ifndef CK_TEMPLATES_ONLY
extern "C" void __xlater_roPup_mask(void *_impl_pup_er) {
  PUP::er &_impl_p=*(PUP::er *)_impl_pup_er;
  _impl_p|mask;
}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message QueenState;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_QueenState::operator new(size_t s){
  return QueenState::alloc(__idx, s, 0, 0);
}
void *CMessage_QueenState::operator new(size_t s, int* sz){
  return QueenState::alloc(__idx, s, sz, 0);
}
void *CMessage_QueenState::operator new(size_t s, int* sz,const int pb){
  return QueenState::alloc(__idx, s, sz, pb);
}
void *CMessage_QueenState::operator new(size_t s, const int p) {
  return QueenState::alloc(__idx, s, 0, p);
}
void* CMessage_QueenState::alloc(int msgnum, size_t sz, int *sizes, int pb) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb);
}
CMessage_QueenState::CMessage_QueenState() {
QueenState *newmsg = (QueenState *)this;
}
void CMessage_QueenState::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_QueenState::pack(QueenState *msg) {
  return (void *) msg;
}
QueenState* CMessage_QueenState::unpack(void* buf) {
  QueenState *msg = (QueenState *) buf;
  return msg;
}
int CMessage_QueenState::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message DUMMYMSG;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_DUMMYMSG::operator new(size_t s){
  return DUMMYMSG::alloc(__idx, s, 0, 0);
}
void *CMessage_DUMMYMSG::operator new(size_t s, int* sz){
  return DUMMYMSG::alloc(__idx, s, sz, 0);
}
void *CMessage_DUMMYMSG::operator new(size_t s, int* sz,const int pb){
  return DUMMYMSG::alloc(__idx, s, sz, pb);
}
void *CMessage_DUMMYMSG::operator new(size_t s, const int p) {
  return DUMMYMSG::alloc(__idx, s, 0, p);
}
void* CMessage_DUMMYMSG::alloc(int msgnum, size_t sz, int *sizes, int pb) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb);
}
CMessage_DUMMYMSG::CMessage_DUMMYMSG() {
DUMMYMSG *newmsg = (DUMMYMSG *)this;
}
void CMessage_DUMMYMSG::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_DUMMYMSG::pack(DUMMYMSG *msg) {
  return (void *) msg;
}
DUMMYMSG* CMessage_DUMMYMSG::unpack(void* buf) {
  DUMMYMSG *msg = (DUMMYMSG *) buf;
  return msg;
}
int CMessage_DUMMYMSG::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
threaded void Quiescence1(DUMMYMSG* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_Main::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: Main(CkArgMsg* impl_msg);
 */

CkChareID CProxy_Main::ckNew(CkArgMsg* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, &impl_ret, impl_onPE);
  return impl_ret;
}

void CProxy_Main::ckNew(CkArgMsg* impl_msg, CkChareID* pcid, int impl_onPE)
{
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, pcid, impl_onPE);
}

  CProxy_Main::CProxy_Main(CkArgMsg* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_Main::__idx, CkIndex_Main::idx_Main_CkArgMsg(), impl_msg, &impl_ret, impl_onPE);
  ckSetChareID(impl_ret);
}

// Entry point registration function

int CkIndex_Main::reg_Main_CkArgMsg() {
  int epidx = CkRegisterEp("Main(CkArgMsg* impl_msg)",
      _call_Main_CkArgMsg, CMessage_CkArgMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)CkArgMsg::ckDebugPup);
  return epidx;
}


void CkIndex_Main::_call_Main_CkArgMsg(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  new (impl_obj) Main((CkArgMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: threaded void Quiescence1(DUMMYMSG* impl_msg);
 */

void CProxy_Main::Quiescence1(DUMMYMSG* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
    int destPE=CkChareMsgPrep(CkIndex_Main::idx_Quiescence1_DUMMYMSG(), impl_msg, &ckGetChareID());
    if (destPE!=-1) ckDelegatedTo()->ChareSend(ckDelegatedPtr(),CkIndex_Main::idx_Quiescence1_DUMMYMSG(), impl_msg, &ckGetChareID(),destPE);
  }
  else CkSendMsg(CkIndex_Main::idx_Quiescence1_DUMMYMSG(), impl_msg, &ckGetChareID(),0);
}

// Entry point registration function

int CkIndex_Main::reg_Quiescence1_DUMMYMSG() {
  int epidx = CkRegisterEp("Quiescence1(DUMMYMSG* impl_msg)",
      _call_Quiescence1_DUMMYMSG, CMessage_DUMMYMSG::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)DUMMYMSG::ckDebugPup);
  return epidx;
}


void CkIndex_Main::_call_Quiescence1_DUMMYMSG(void* impl_msg, void* impl_obj_void)
{
  Main* impl_obj = static_cast<Main *>(impl_obj_void);
  CthThread tid = CthCreate((CthVoidFn)_callthr_Quiescence1_DUMMYMSG, new CkThrCallArg(impl_msg,impl_obj), 0);
  ((Chare *)impl_obj)->CkAddThreadListeners(tid,impl_msg);
  CthResume(tid);
}

void CkIndex_Main::_callthr_Quiescence1_DUMMYMSG(CkThrCallArg *impl_arg)
{
  void *impl_msg = impl_arg->msg;
  Main *impl_obj = (Main *) impl_arg->obj;
  delete impl_arg;
  impl_obj->Quiescence1((DUMMYMSG*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_Main::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeMainChare);
  CkRegisterBase(__idx, CkIndex_Chare::__idx);
  // REG: Main(CkArgMsg* impl_msg);
  idx_Main_CkArgMsg();
  CkRegisterMainChare(__idx, idx_Main_CkArgMsg());

  // REG: threaded void Quiescence1(DUMMYMSG* impl_msg);
  idx_Quiescence1_DUMMYMSG();

}
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: chare NQueen: Chare{
NQueen(QueenState* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_NQueen::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: NQueen(QueenState* impl_msg);
 */

CkChareID CProxy_NQueen::ckNew(QueenState* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_NQueen::__idx, CkIndex_NQueen::idx_NQueen_QueenState(), impl_msg, &impl_ret, impl_onPE);
  return impl_ret;
}

void CProxy_NQueen::ckNew(QueenState* impl_msg, CkChareID* pcid, int impl_onPE)
{
  CkCreateChare(CkIndex_NQueen::__idx, CkIndex_NQueen::idx_NQueen_QueenState(), impl_msg, pcid, impl_onPE);
}

  CProxy_NQueen::CProxy_NQueen(QueenState* impl_msg, int impl_onPE)
{
  CkChareID impl_ret;
  CkCreateChare(CkIndex_NQueen::__idx, CkIndex_NQueen::idx_NQueen_QueenState(), impl_msg, &impl_ret, impl_onPE);
  ckSetChareID(impl_ret);
}

// Entry point registration function

int CkIndex_NQueen::reg_NQueen_QueenState() {
  int epidx = CkRegisterEp("NQueen(QueenState* impl_msg)",
      _call_NQueen_QueenState, CMessage_QueenState::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)QueenState::ckDebugPup);
  return epidx;
}


void CkIndex_NQueen::_call_NQueen_QueenState(void* impl_msg, void* impl_obj_void)
{
  NQueen* impl_obj = static_cast<NQueen *>(impl_obj_void);
  new (impl_obj) NQueen((QueenState*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_NQueen::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeChare);
  CkRegisterBase(__idx, CkIndex_Chare::__idx);
  // REG: NQueen(QueenState* impl_msg);
  idx_NQueen_QueenState();

}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void _registermain(void)
{
  static int _done = 0; if(_done) return; _done = 1;
  _registerCounter();

  CkRegisterReadonly("numQueens","int",sizeof(numQueens),(void *) &numQueens,__xlater_roPup_numQueens);

  CkRegisterReadonly("grainsize","int",sizeof(grainsize),(void *) &grainsize,__xlater_roPup_grainsize);

  CkRegisterReadonly("counterGroup","CkGroupID",sizeof(counterGroup),(void *) &counterGroup,__xlater_roPup_counterGroup);

  CkRegisterReadonly("mask","int",sizeof(mask),(void *) &mask,__xlater_roPup_mask);

/* REG: message QueenState;
*/
CMessage_QueenState::__register("QueenState", sizeof(QueenState),(CkPackFnPtr) QueenState::pack,(CkUnpackFnPtr) QueenState::unpack);

/* REG: message DUMMYMSG;
*/
CMessage_DUMMYMSG::__register("DUMMYMSG", sizeof(DUMMYMSG),(CkPackFnPtr) DUMMYMSG::pack,(CkUnpackFnPtr) DUMMYMSG::unpack);

/* REG: mainchare Main: Chare{
Main(CkArgMsg* impl_msg);
threaded void Quiescence1(DUMMYMSG* impl_msg);
};
*/
  CkIndex_Main::__register("Main", sizeof(Main));

/* REG: chare NQueen: Chare{
NQueen(QueenState* impl_msg);
};
*/
  CkIndex_NQueen::__register("NQueen", sizeof(NQueen));

}
extern "C" void CkRegisterMainModule(void) {
  _registermain();
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_Main::virtual_pup(PUP::er &p) {
    recursive_pup<Main >(dynamic_cast<Main* >(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_NQueen::virtual_pup(PUP::er &p) {
    recursive_pup<NQueen >(dynamic_cast<NQueen* >(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
