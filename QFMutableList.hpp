#include "QFLinkNode.hpp"

template<typename E>
class QFMutableList {
private:
	QFLinkNode<E>* frist;	// �����е��׽ڵ�
	QFLinkNode<E>* last;	// �����е�β�ڵ�
	int len;

public:
	QFMutableList();

	~QFMutableList();
};
