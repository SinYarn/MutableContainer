#pragma once

#include "QFLinkNode.hpp"
#include "QFMutableContainer.h"
#include <iostream>
#include <sstream>

using namespace std;

template<typename E>
class QFMutableList : public QFMutableContainer<E>{
private:
	QFLinkNode<E>* frist;	// 链表中的首节点
	QFLinkNode<E>* last;	// 链表中的尾节点
	int len;

	QFLinkNode<E>* getNode(int index);		// 通过下标获取节点

public:
	QFMutableList();

    void add(E ele) override;

	// 下标，增加一个元素
	void add(int index, E ele) override;

	// 按照下标删除元素
    E remove(int index) override;

	// 按照元素删除
	bool removeElement(E ele) override;

	// 清空容器
	void clear() override;

	// 通过下标修改元素
	E set(int index, E ele) override;

	// 通过下标获取元素
	E get(int index) override;

	// 排序
	void sort() override;

	// 查找元素的下标
	int index(E ele) override;

	// 将容器的元素拼接为字符串
	string str() override;

	// 元素数量

	int length() override;

	~QFMutableList() override;
};

template<typename E>
QFLinkNode<E>* QFMutableList<E>::getNode(int index)
{
	QFLinkNode<E>* p = frist;

	// 遍历index次， 查找第index个节点
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

// 插在链表尾部
template<typename E>
void QFMutableList<E>::add(E ele)
{
	// 创建一个新的节点对象
	QFLinkNode<E>* node = new QFLinkNode<E>(ele);

	// 添加到尾节点后面
	if (len == 0) {
		//  如果链表为空，则新节点即为头节点又为尾节点
		this->frist = node;
		this->last = node;
	}
	else {
		// 链表有元素的 更新last指针
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
		// 添加位置为0号
		node->next = frist;
		frist->previous = node;
		frist = node;
		len++;
	}else if (index == len) {
		// 添加位置为最后
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

		// 删除堆上的空间
		delete frist;

		// 指针置为空
		frist = nullptr;
		last = nullptr;
	}
	else {
		if (index == 0) {
			// 删除首节点
			tmp = frist->ele;
			frist = frist->next;
			delete frist->previous;
			frist->previous = nullptr;
		}
		else if (index == len - 1) {
			// 删除尾节点
			tmp = last->ele;
			last = last->previous;
			delete last->next;
			last->next = nullptr;
		}
		else {
			// 删除中间节点
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
		// 释放每一个节点的空间
		QFLinkNode<E>* p1 = frist;
		QFLinkNode<E>* p2 = frist->next;

		// 遍历链表依次删除， p2为null时删除
		while (p2 != nullptr) {
			delete p1;
			p1 = p2;
			p2 = p2->next;
		}
		delete p1;

		// 使首节点 尾节点指针 置为空 ，链表为空时， 头 尾 节点 指向为nullptr
		frist = nullptr;
		last = nullptr;
		len = 0;
	}
}

template<typename E>
inline E QFMutableList<E>::set(int index, E ele)
{
	// 通过下标获取节点 
	QFLinkNode<E>* node = getNode(index);
	
	// 备份原来的数据
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
	// 交换元素， 不要交换节点
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


