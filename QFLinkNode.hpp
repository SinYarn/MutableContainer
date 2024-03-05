#pragma once
#include"QFMutableList.hpp"

// 节点类
template<typename T>
class QFMutableList;

template<typename E>
class QFLinkNode {
	// 友元类
	friend class QFMutableList<E>;
private:
	E ele;	// 存储的元素
	QFLinkNode<E>* previous; // 上一个节点的地址
	QFLinkNode<E>* next;	//	下一个节点的地址

public:
	QFLinkNode(E ele);
};

template<typename E>
QFLinkNode<E>::QFLinkNode(E ele)
{
	this->ele = ele;
	previous = nullptr;
	next = nullptr;
}
