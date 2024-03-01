#include "QFLinkNode.hpp"

template<typename E>
class QFMutableList {
private:
	QFLinkNode<E>* frist;	// 链表中的首节点
	QFLinkNode<E>* last;	// 链表中的尾节点
	int len;

public:
	QFMutableList();

	~QFMutableList();
};
