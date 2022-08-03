//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_LOCKFREESTACK_H
#define HEIRLOOM_LOCKFREESTACK_H

#include <atomic>

namespace Heirloom
{
	template <class T> concept LockFreeStackType = std::destructible<T>;

	template <LockFreeStackType T>
	struct Node
	{
		Node* pNext;
		T Value;

		Node() = default;

		Node(T value, Node* nextNode)
				: pNext(nextNode),
				  Value(value)
		{
		}
	};

	struct SomeType
	{
		~SomeType() = delete;
	};

	template <LockFreeStackType T>
	class LockFreeStack
	{
	public:
		~LockFreeStack();
		void Push(T value);
		Node<T>* Pop();
		size_t Size() const;

	private:
		std::atomic<Node<T>*> m_pHead = nullptr;
	};

	template <LockFreeStackType T>
	LockFreeStack<T>::~LockFreeStack()
	{
		Node<T>* currentNode = m_pHead.load();
		size_t counter       = 0;

		while (currentNode != nullptr)
		{
			Node<T>* nextNode = currentNode->pNext;
			delete currentNode;
			currentNode = nextNode;
			++counter;
		}
	}

	template <LockFreeStackType T>
	void LockFreeStack<T>::Push(T value)
	{
		Node<T>* pNewNode = new Node<T>(value, nullptr);

		do
		{
			pNewNode->pNext = m_pHead.load();
		}
		while (!m_pHead.compare_exchange_weak(pNewNode->pNext, pNewNode));
	}

	template <LockFreeStackType T>
	Node<T>* LockFreeStack<T>::Pop()
	{
		Node<T>* pOldHead;

		do
		{
			pOldHead = m_pHead.load();
		}
		while (!m_pHead.compare_exchange_weak(pOldHead, pOldHead->pNext));

		return pOldHead;
	}

	template <LockFreeStackType T>
	size_t LockFreeStack<T>::Size() const
	{
		size_t size          = 0;
		Node<T>* currentNode = m_pHead;

		while (currentNode != nullptr && currentNode->pNext != nullptr)
		{
			++size;
			currentNode = currentNode->pNext;
		}

		if (m_pHead != nullptr)
		{
			++size;
		}

		return size;
	}
}

#endif //HEIRLOOM_LOCKFREESTACK_H
