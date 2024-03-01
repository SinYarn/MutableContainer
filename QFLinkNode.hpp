#pragma once

// �ڵ���
template<typename E>
class QFLinkNode {
private:
	E ele;	// �洢��Ԫ��
	QFLinkNode<E>* previous; // ��һ���ڵ�ĵ�ַ
	QFLinkNode<E>* next;	//	��һ���ڵ�ĵ�ַ

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
