#pragma once

// 节点类
template<typename E>
class QFLinkNode {
private:
	E ele;	// 存储的元素
	QFLinkNode<E>* previous; // 上一个节点的地址
	QFLinkNode<E>* next;	//	下一个节点的地址

public:
	QFLinkNode(E ele);
	~QFLinkNode() override;
};

template<typename E>
QFLinkNode<E>::QFLinkNode(E ele)
{
	this->ele = ele;
	previous = nullptr;
	next = nullptr;
}

template<typename E>
inline QFLinkNode<E>::~QFLinkNode()
{
}
