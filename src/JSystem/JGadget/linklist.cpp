//
// Generated by dtk
// Translation Unit: linklist.cpp
//

#include "JSystem/JGadget/linklist.h"

namespace std {

template <class InputIterator, class Predicate>
inline InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last && !pred(*first))
		++first;
	return first;
}

} // namespace std

template <typename T>
class TPRIsEqual_pointer_ {
public:
    TPRIsEqual_pointer_<T>(const T* p) { this->p_ = p; }

    bool operator()(const T& rSrc) const {
        return &rSrc == this->p_;
    }

private:
    const T* p_;
};

/* 802BFC00-802BFC3C       .text __dt__Q27JGadget13TNodeLinkListFv */
JGadget::TNodeLinkList::~TNodeLinkList() {
}

/* 802BFC3C-802BFC84       .text erase__Q27JGadget13TNodeLinkListFQ37JGadget13TNodeLinkList8iterator */
JGadget::TNodeLinkList::iterator JGadget::TNodeLinkList::erase(iterator it) {
    iterator next = it;
    ++next;
    return erase(it, next);
}

/* 802BFC84-802BFCEC       .text erase__Q27JGadget13TNodeLinkListFQ37JGadget13TNodeLinkList8iteratorQ37JGadget13TNodeLinkList8iterator */
JGadget::TNodeLinkList::iterator JGadget::TNodeLinkList::erase(iterator a, iterator b) {
    TLinkListNode* cur = a.node;
    TLinkListNode* end = b.node;
    TLinkListNode* next;

    for (; cur != end; cur = next) {
        next = cur->mNext;
        Erase(cur);
    }

    return b;
}

/* 802BFCEC-802BFD8C       .text splice__Q27JGadget13TNodeLinkListFQ37JGadget13TNodeLinkList8iteratorRQ27JGadget13TNodeLinkListQ37JGadget13TNodeLinkList8iterator */
void JGadget::TNodeLinkList::splice(iterator it, TNodeLinkList& rSrc, iterator itSrc) {
    iterator itSrcNext = itSrc;
    ++itSrcNext;

    if ((it == itSrc) || (it == itSrcNext)) {
        return;
    } else {
        TLinkListNode* const node = &(*itSrc);
        rSrc.Erase(node);
        Insert(it, node);
    }
}

/* 802BFD8C-802BFDF4       .text Find__Q27JGadget13TNodeLinkListFPCQ27JGadget13TLinkListNode */
JGadget::TNodeLinkList::iterator JGadget::TNodeLinkList::Find(const TLinkListNode* node) {
    return std::find_if(begin(), end(), TPRIsEqual_pointer_<TLinkListNode>(node));
}

/* 802BFDF4-802BFE20       .text Insert__Q27JGadget13TNodeLinkListFQ37JGadget13TNodeLinkList8iteratorPQ27JGadget13TLinkListNode */
JGadget::TNodeLinkList::iterator JGadget::TNodeLinkList::Insert(iterator it, TLinkListNode* p) {
    TLinkListNode* pIt = it.node;
    TLinkListNode* pItPrev = pIt->mPrev;

    p->mNext = pIt;
    p->mPrev = pItPrev;
    pIt->mPrev = p;
    pItPrev->mNext = p;
    count++;
    return iterator(p);
}

/* 802BFE20-802BFE44       .text Erase__Q27JGadget13TNodeLinkListFPQ27JGadget13TLinkListNode */
JGadget::TNodeLinkList::iterator JGadget::TNodeLinkList::Erase(TLinkListNode* p) {
    TLinkListNode* pNext = p->mNext;
    TLinkListNode* pPrev = p->mPrev;
    pNext->mPrev = pPrev;
    pPrev->mNext = pNext;
    count--;
    return iterator(pNext);
}

/* 802BFE44-802BFF14       .text Remove__Q27JGadget13TNodeLinkListFPQ27JGadget13TLinkListNode */
void JGadget::TNodeLinkList::Remove(TLinkListNode* p) {
    remove_if(TPRIsEqual_pointer_<TLinkListNode>(p));
}

