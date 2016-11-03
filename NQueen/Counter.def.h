

/* ---------------- method closures -------------- */
#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */


/* DEFS: message countMsg;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_countMsg::operator new(size_t s){
  return countMsg::alloc(__idx, s, 0, 0);
}
void *CMessage_countMsg::operator new(size_t s, int* sz){
  return countMsg::alloc(__idx, s, sz, 0);
}
void *CMessage_countMsg::operator new(size_t s, int* sz,const int pb){
  return countMsg::alloc(__idx, s, sz, pb);
}
void *CMessage_countMsg::operator new(size_t s, const int p) {
  return countMsg::alloc(__idx, s, 0, p);
}
void* CMessage_countMsg::alloc(int msgnum, size_t sz, int *sizes, int pb) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb);
}
CMessage_countMsg::CMessage_countMsg() {
countMsg *newmsg = (countMsg *)this;
}
void CMessage_countMsg::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_countMsg::pack(countMsg *msg) {
  return (void *) msg;
}
countMsg* CMessage_countMsg::unpack(void* buf) {
  countMsg *msg = (countMsg *) buf;
  return msg;
}
int CMessage_countMsg::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: message DUMMY;
 */
#ifndef CK_TEMPLATES_ONLY
void *CMessage_DUMMY::operator new(size_t s){
  return DUMMY::alloc(__idx, s, 0, 0);
}
void *CMessage_DUMMY::operator new(size_t s, int* sz){
  return DUMMY::alloc(__idx, s, sz, 0);
}
void *CMessage_DUMMY::operator new(size_t s, int* sz,const int pb){
  return DUMMY::alloc(__idx, s, sz, pb);
}
void *CMessage_DUMMY::operator new(size_t s, const int p) {
  return DUMMY::alloc(__idx, s, 0, p);
}
void* CMessage_DUMMY::alloc(int msgnum, size_t sz, int *sizes, int pb) {
  CkpvAccess(_offsets)[0] = ALIGN_DEFAULT(sz);
  return CkAllocMsg(msgnum, CkpvAccess(_offsets)[0], pb);
}
CMessage_DUMMY::CMessage_DUMMY() {
DUMMY *newmsg = (DUMMY *)this;
}
void CMessage_DUMMY::dealloc(void *p) {
  CkFreeMsg(p);
}
void* CMessage_DUMMY::pack(DUMMY *msg) {
  return (void *) msg;
}
DUMMY* CMessage_DUMMY::unpack(void* buf) {
  DUMMY *msg = (DUMMY *) buf;
  return msg;
}
int CMessage_DUMMY::__idx=0;
#endif /* CK_TEMPLATES_ONLY */

/* DEFS: group counter: IrrGroup{
counter(DUMMY* impl_msg);
void sendCounts(DUMMY* impl_msg);
void childCount(countMsg* impl_msg);
};
 */
#ifndef CK_TEMPLATES_ONLY
 int CkIndex_counter::__idx=0;
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
/* DEFS: counter(DUMMY* impl_msg);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendCounts(DUMMY* impl_msg);
 */

void CProxyElement_counter::sendCounts(DUMMY* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkGroupMsgPrep(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->GroupSend(ckDelegatedPtr(),CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else CkSendMsgBranch(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void childCount(countMsg* impl_msg);
 */

void CProxyElement_counter::childCount(countMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkGroupMsgPrep(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->GroupSend(ckDelegatedPtr(),CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID());
  } else CkSendMsgBranch(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupPe(), ckGetGroupID(),0);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: counter(DUMMY* impl_msg);
 */

CkGroupID CProxy_counter::ckNew(DUMMY* impl_msg)
{
  UsrToEnv(impl_msg)->setMsgtype(BocInitMsg);
  return CkCreateGroup(CkIndex_counter::__idx, CkIndex_counter::idx_counter_DUMMY(), impl_msg);
}

  CProxy_counter::CProxy_counter(DUMMY* impl_msg)
{
  UsrToEnv(impl_msg)->setMsgtype(BocInitMsg);
  ckSetGroupID(CkCreateGroup(CkIndex_counter::__idx, CkIndex_counter::idx_counter_DUMMY(), impl_msg));
}

// Entry point registration function

int CkIndex_counter::reg_counter_DUMMY() {
  int epidx = CkRegisterEp("counter(DUMMY* impl_msg)",
      _call_counter_DUMMY, CMessage_DUMMY::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)DUMMY::ckDebugPup);
  return epidx;
}


void CkIndex_counter::_call_counter_DUMMY(void* impl_msg, void* impl_obj_void)
{
  counter* impl_obj = static_cast<counter *>(impl_obj_void);
  new (impl_obj) counter((DUMMY*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendCounts(DUMMY* impl_msg);
 */

void CProxy_counter::sendCounts(DUMMY* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkGroupMsgPrep(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->GroupBroadcast(ckDelegatedPtr(),CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgBranch(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID(),0);
}

void CProxy_counter::sendCounts(DUMMY* impl_msg, int npes, int *pes) {
  CkSendMsgBranchMulti(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID(), npes, pes,0);
}

void CProxy_counter::sendCounts(DUMMY* impl_msg, CmiGroup &grp) {
  CkSendMsgBranchGroup(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID(), grp,0);
}

// Entry point registration function

int CkIndex_counter::reg_sendCounts_DUMMY() {
  int epidx = CkRegisterEp("sendCounts(DUMMY* impl_msg)",
      _call_sendCounts_DUMMY, CMessage_DUMMY::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)DUMMY::ckDebugPup);
  return epidx;
}


void CkIndex_counter::_call_sendCounts_DUMMY(void* impl_msg, void* impl_obj_void)
{
  counter* impl_obj = static_cast<counter *>(impl_obj_void);
  impl_obj->sendCounts((DUMMY*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void childCount(countMsg* impl_msg);
 */

void CProxy_counter::childCount(countMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkGroupMsgPrep(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->GroupBroadcast(ckDelegatedPtr(),CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID());
  } else CkBroadcastMsgBranch(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID(),0);
}

void CProxy_counter::childCount(countMsg* impl_msg, int npes, int *pes) {
  CkSendMsgBranchMulti(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID(), npes, pes,0);
}

void CProxy_counter::childCount(countMsg* impl_msg, CmiGroup &grp) {
  CkSendMsgBranchGroup(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID(), grp,0);
}

// Entry point registration function

int CkIndex_counter::reg_childCount_countMsg() {
  int epidx = CkRegisterEp("childCount(countMsg* impl_msg)",
      _call_childCount_countMsg, CMessage_countMsg::__idx, __idx, 0);
  CkRegisterMessagePupFn(epidx, (CkMessagePupFn)countMsg::ckDebugPup);
  return epidx;
}


void CkIndex_counter::_call_childCount_countMsg(void* impl_msg, void* impl_obj_void)
{
  counter* impl_obj = static_cast<counter *>(impl_obj_void);
  impl_obj->childCount((countMsg*)impl_msg);
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: counter(DUMMY* impl_msg);
 */
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void sendCounts(DUMMY* impl_msg);
 */

void CProxySection_counter::sendCounts(DUMMY* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkGroupMsgPrep(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->GroupSectionSend(ckDelegatedPtr(),CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp = (ckGetNumSections()>1) ? CkCopyMsg((void **) &impl_msg) : impl_msg;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgBranchMulti(CkIndex_counter::idx_sendCounts_DUMMY(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
/* DEFS: void childCount(countMsg* impl_msg);
 */

void CProxySection_counter::childCount(countMsg* impl_msg)
{
  ckCheck();
  if (ckIsDelegated()) {
     CkGroupMsgPrep(CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetGroupID());
     ckDelegatedTo()->GroupSectionSend(ckDelegatedPtr(),CkIndex_counter::idx_childCount_countMsg(), impl_msg, ckGetNumSections(), ckGetSectionIDs());
  } else {
    void *impl_msg_tmp = (ckGetNumSections()>1) ? CkCopyMsg((void **) &impl_msg) : impl_msg;
    for (int i=0; i<ckGetNumSections(); ++i) {
       impl_msg_tmp= (i<ckGetNumSections()-1) ? CkCopyMsg((void **) &impl_msg):impl_msg;
       CkSendMsgBranchMulti(CkIndex_counter::idx_childCount_countMsg(), impl_msg_tmp, ckGetGroupIDn(i), ckGetNumElements(i), ckGetElements(i),0);
    }
  }
}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
void CkIndex_counter::__register(const char *s, size_t size) {
  __idx = CkRegisterChare(s, size, TypeGroup);
  CkRegisterBase(__idx, CkIndex_IrrGroup::__idx);
   CkRegisterGroupIrr(__idx,counter::isIrreducible());
  // REG: counter(DUMMY* impl_msg);
  idx_counter_DUMMY();

  // REG: void sendCounts(DUMMY* impl_msg);
  idx_sendCounts_DUMMY();

  // REG: void childCount(countMsg* impl_msg);
  idx_childCount_countMsg();

}
#endif /* CK_TEMPLATES_ONLY */

#ifndef CK_TEMPLATES_ONLY
void _registerCounter(void)
{
  static int _done = 0; if(_done) return; _done = 1;
/* REG: message countMsg;
*/
CMessage_countMsg::__register("countMsg", sizeof(countMsg),(CkPackFnPtr) countMsg::pack,(CkUnpackFnPtr) countMsg::unpack);

/* REG: message DUMMY;
*/
CMessage_DUMMY::__register("DUMMY", sizeof(DUMMY),(CkPackFnPtr) DUMMY::pack,(CkUnpackFnPtr) DUMMY::unpack);

/* REG: group counter: IrrGroup{
counter(DUMMY* impl_msg);
void sendCounts(DUMMY* impl_msg);
void childCount(countMsg* impl_msg);
};
*/
  CkIndex_counter::__register("counter", sizeof(counter));

}
#endif /* CK_TEMPLATES_ONLY */
#ifndef CK_TEMPLATES_ONLY
template <>
void CBase_counter::virtual_pup(PUP::er &p) {
    recursive_pup<counter >(dynamic_cast<counter* >(this), p);
}
#endif /* CK_TEMPLATES_ONLY */
