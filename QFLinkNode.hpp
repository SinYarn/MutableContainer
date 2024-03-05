#pragma once
#include"QFMutableList.hpp"

// �ڵ���
template<typename T>
class QFMutableList;

template<typename E>
class QFLinkNode {
	// ��Ԫ��
	friend class QFMutableList<E>;
private:
	E ele;	// �洢��Ԫ��
	QFLinkNode<E>* previous; // ��һ���ڵ�ĵ�ַ
	QFLinkNode<E>* next;	//	��һ���ڵ�ĵ�ַ

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
