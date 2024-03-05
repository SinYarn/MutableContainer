#pragma once

#include "QFLinkNode.hpp"
#include "QFMutableContainer.h"
#include <iostream>
#include <sstream>

using namespace std;

template<typename E>
class QFMutableList : public QFMutableContainer<E>{
private:
	QFLinkNode<E>* frist;	// �����е��׽ڵ�
	QFLinkNode<E>* last;	// �����е�β�ڵ�
	int len;

	QFLinkNode<E>* getNode(int index);		// ͨ���±��ȡ�ڵ�

public:
	QFMutableList();

    void add(E ele) override;

	// �±꣬����һ��Ԫ��
	void add(int index, E ele) override;

	// �����±�ɾ��Ԫ��
    E remove(int index) override;

	// ����Ԫ��ɾ��
	bool removeElement(E ele) override;

	// �������
	void clear() override;

	// ͨ���±��޸�Ԫ��
	E set(int index, E ele) override;

	// ͨ���±��ȡԪ��
	E get(int index) override;

	// ����
	void sort() override;

	// ����Ԫ�ص��±�
	int index(E ele) override;

	// ��������Ԫ��ƴ��Ϊ�ַ���
	string str() override;

	// Ԫ������

	int length() override;

	~QFMutableList() override;
};

template<typename E>
QFLinkNode<E>* QFMutableList<E>::getNode(int index)
{
	QFLinkNode<E>* p = frist;

	// ����index�Σ� ���ҵ�index���ڵ�
	for (int i = 0; i < index; i++)
	{
		p = p->next;
	}
	return p;
}

template<typename E>
inline QFMutableList<E>::QFMutableList()
{
	frist = nullptr;
	last = nullptr;
	len = 0;
}

template<typename E>
inline QFMutableList<E>::~QFMutableList()
{
	clear();
}

// ��������β��
template<typename E>
void QFMutableList<E>::add(E ele)
{
	// ����һ���µĽڵ����
	QFLinkNode<E>* node = new QFLinkNode<E>(ele);

	// ��ӵ�β�ڵ����
	if (len == 0) {
		//  �������Ϊ�գ����½ڵ㼴Ϊͷ�ڵ���Ϊβ�ڵ�
		this->frist = node;
		this->last = node;
	}
	else {
		// ������Ԫ�ص� ����lastָ��
		this->last->next = node;
		node->previous = this->last;
		this->last = node;
	}
	len++;
}

template<typename E>
void QFMutableList<E>::add(int index, E ele)
{
	QFLinkNode<E>* node = new QFLinkNode<E>(ele);
	if (index > len) {
		
	}


	if (index == 0) {
		// ���λ��Ϊ0��
		node->next = frist;
		frist->previous = node;
		frist = node;
		len++;
	}else if (index == len) {
		// ���λ��Ϊ���
		last->next = node;
		node->previous = node;
		last = node;
		len++;
	}
	else {
		QFLinkNode<E>* target = getNode(index);
		target->previous->next = node;
		node->previous = target->previous;
		node->next = target;
		target->previous = node;
		len++;
	}
	
}

template<typename E>
E QFMutableList<E>::remove(int index)
{
	E tmp;
	if (len == 1) {
		tmp = frist->ele;

		// ɾ�����ϵĿռ�
		delete frist;

		// ָ����Ϊ��
		frist = nullptr;
		last = nullptr;
	}
	else {
		if (index == 0) {
			// ɾ���׽ڵ�
			tmp = frist->ele;
			frist = frist->next;
			delete frist->previous;
			frist->previous = nullptr;
		}
		else if (index == len - 1) {
			// ɾ��β�ڵ�
			tmp = last->ele;
			last = last->previous;
			delete last->next;
			last->next = nullptr;
		}
		else {
			// ɾ���м�ڵ�
			QFLinkNode<E>* node = getNode(index);
			tmp = node->ele;

			node->previous->next = node->next;
			node->next->previous = node->previous;
			delete node;
		}

	}
	len--;
	return tmp;
}

template<typename E>
inline bool QFMutableList<E>::removeElement(E ele)
{
	// 
	int index = this->index(ele);

	if (index == -1) {
		return false;
	}
	remove(index);
	return true;
}

template<typename E>
inline void QFMutableList<E>::clear()
{
	if (frist != nullptr) {
		// �ͷ�ÿһ���ڵ�Ŀռ�
		QFLinkNode<E>* p1 = frist;
		QFLinkNode<E>* p2 = frist->next;

		// ������������ɾ���� p2Ϊnullʱɾ��
		while (p2 != nullptr) {
			delete p1;
			p1 = p2;
			p2 = p2->next;
		}
		delete p1;

		// ʹ�׽ڵ� β�ڵ�ָ�� ��Ϊ�� ������Ϊ��ʱ�� ͷ β �ڵ� ָ��Ϊnullptr
		frist = nullptr;
		last = nullptr;
		len = 0;
	}
}

template<typename E>
inline E QFMutableList<E>::set(int index, E ele)
{
	// ͨ���±��ȡ�ڵ� 
	QFLinkNode<E>* node = getNode(index);
	
	// ����ԭ��������
	E tmp = node->ele;

	// 
	node->ele = ele;

	return tmp;
}

template<typename E>
E QFMutableList<E>::get(int index)
{
	QFLinkNode<E>* node = getNode(index);


	return node->ele;
}

template<typename E>
inline void QFMutableList<E>::sort()
{
	// ����Ԫ�أ� ��Ҫ�����ڵ�
	for (int i = 0; i < len - 1; i++) {
		QFLinkNode<E>* node = frist;
		for (int j = 0; j < len - 1 - i; j++) {
			if (node->ele > node->next->ele) {
				E tmp = node->ele;
				node->ele = node->next->ele;
				node->next->ele = tmp;
			}
			node = node->next;
		}
	}
}

template<typename E>
int QFMutableList<E>::index(E ele)
{
	QFLinkNode<E>* node = frist;
	for (int i = 0; i < len; i++) {
		if (node->ele == ele) {
			return i;
		}
		node = node->next;
	}
	return -1;
}

template<typename E>
inline string QFMutableList<E>::str()
{
	if (len == 0) {
		return "[]";
	}
	ostringstream oss;

	oss << "[";
	QFLinkNode<E>* node = frist;

	for (int i = 0; i < len - 1; i++)
	{
		oss << node->ele << ", ";
		node = node->next;

	}

	oss << node->ele << "]";

	return oss.str();
}

template<typename E>
inline int QFMutableList<E>::length()
{

	return len;
}


