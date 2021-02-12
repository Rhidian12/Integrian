#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: December 2020
// ====================================
#ifndef APP_BENCHMARK_LINKEDLIST_H
#define APP_BENCHMARK_LINKEDLIST_H

#include <algorithm>
#include <string>
namespace Engine
{
	template<typename Type>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList()
			: m_pStartNode{}
			, m_Size{}
		{
		}
		~DoublyLinkedList()
		{
			clear();
		}

		void push_back(const Type& data)
		{
			if (m_pStartNode == nullptr)
			{
				m_pStartNode = new Node{ data };
				m_pStartNode->pPreviousNode = m_pStartNode;
				m_pStartNode->pNextNode = m_pStartNode;
			}
			else
			{
				Node* pLastNode{ m_pStartNode->pPreviousNode }; // get last pointer
				pLastNode->pNextNode = new Node{ data }; // make new pointer at the following position
				pLastNode->pNextNode->pPreviousNode = pLastNode; // set new pointer its previous pointer to ex last pointer
				pLastNode->pNextNode->pNextNode = m_pStartNode; // set new pointer its next pointer to start
				m_pStartNode->pPreviousNode = pLastNode->pNextNode; // set start its previous pointer to new pointer
			}
			++m_Size;
		}
		void push_back(Type&& data)
		{
			if (m_pStartNode == nullptr)
			{
				m_pStartNode = new Node{ std::move(data) };
				m_pStartNode->pPreviousNode = m_pStartNode;
				m_pStartNode->pNextNode = m_pStartNode;
			}
			else
			{
				Node* pLastNode{ m_pStartNode->pPreviousNode }; // get last pointer
				pLastNode->pNextNode = new Node{ std::move(data) }; // make new pointer at the following position
				pLastNode->pNextNode->pPreviousNode = pLastNode; // set new pointer its previous pointer to ex last pointer
				pLastNode->pNextNode->pNextNode = m_pStartNode; // set new pointer its next pointer to start
				m_pStartNode->pPreviousNode = pLastNode->pNextNode; // set start its previous pointer to new pointer
			}
			++m_Size;
		}

		void push_front(const Type& data)
		{
			if (m_pStartNode == nullptr)
			{
				m_pStartNode = new Node{ data };
				m_pStartNode->pPreviousNode = m_pStartNode;
				m_pStartNode->pNextNode = m_pStartNode;
			}
			else
			{
				Node* pLastPointer{ m_pStartNode->pPreviousNode }; // get last pointer
				pLastPointer->pNextNode = new Node{ data }; // make new pointer at the following position
				pLastPointer->pNextNode->pNextNode = m_pStartNode; // set new pointer its next pointer to current start
				pLastPointer->pNextNode->pPreviousNode = pLastPointer; // set new pointer its previous pointer to last pointer
				m_pStartNode->pPreviousNode = pLastPointer->pNextNode; // set current start its previous pointer to new pointer
				m_pStartNode = pLastPointer->pNextNode; // set new pointer as new start node
			}
			++m_Size;
		}
		void push_front(Type&& data)
		{
			if (m_pStartNode == nullptr)
			{
				m_pStartNode = new Node{ std::move(data) };
				m_pStartNode->pPreviousNode = m_pStartNode;
				m_pStartNode->pNextNode = m_pStartNode;
			}
			else
			{
				Node* pLastPointer{ m_pStartNode->pPreviousNode }; // get last pointer
				pLastPointer->pNextNode = new Node{ std::move(data) }; // make new pointer at the following position
				pLastPointer->pNextNode->pNextNode = m_pStartNode; // set new pointer its next pointer to current start
				pLastPointer->pNextNode->pPreviousNode = pLastPointer; // set new pointer its previous pointer to last pointer
				m_pStartNode->pPreviousNode = pLastPointer->pNextNode; // set current start its previous pointer to new pointer
				m_pStartNode = pLastPointer->pNextNode; // set new pointer as new start node
			}
			++m_Size;
		}

		void insert(const int index, const Type& data)
		{
			int counter{};
			Node* pCurrentNode{ m_pStartNode }; // get start node
			while (counter != index) // check if we went through the entire thing
			{
				++counter;
				pCurrentNode = pCurrentNode->pNextNode;
			}

			// we have arrived at the index
			if (pCurrentNode == m_pStartNode) // check if we could do a push front
			{
				push_front(data);
				return;
			}
			if (pCurrentNode == m_pStartNode->pPreviousNode) // check if we could do a push back
			{
				push_back(data);
				return;
			}

			Node* pNewNode{ new Node{data} };
			Node* pPreviousNode{ pCurrentNode->pPreviousNode };

			pPreviousNode->pNextNode = pNewNode;
			pNewNode->pPreviousNode = pPreviousNode;
			pCurrentNode->pPreviousNode = pNewNode;
			pNewNode->pNextNode = pCurrentNode;
			++m_Size;
		}
		void insert(const int index, Type&& data)
		{
			int counter{};
			Node* pCurrentNode{ m_pStartNode }; // get start node
			while (counter != index) // check if we went through the entire thing
			{
				++counter;
				pCurrentNode = pCurrentNode->pNextNode;
			}

			// we have arrived at the index
			if (pCurrentNode == m_pStartNode) // check if we could do a push front
			{
				push_front(std::move(data));
				return;
			}
			if (pCurrentNode == m_pStartNode->pPreviousNode) // check if we could do a push back
			{
				push_back(std::move(data));
				return;
			}

			Node* pNewNode{ new Node{std::move(data)} };
			Node* pPreviousNode{ pCurrentNode->pPreviousNode };

			pPreviousNode->pNextNode = pNewNode;
			pNewNode->pPreviousNode = pPreviousNode;
			pCurrentNode->pPreviousNode = pNewNode;
			pNewNode->pNextNode = pCurrentNode;
			++m_Size;
		}

		void pop_back()
		{
			if (m_pStartNode == nullptr)
				return;
			if (m_pStartNode->pPreviousNode == m_pStartNode)
			{
				delete m_pStartNode;
				m_pStartNode = nullptr;
				return;
			}
			Node* pLastPointer{ m_pStartNode->pPreviousNode }; // get last pointer
			pLastPointer->pPreviousNode->pNextNode = m_pStartNode; // set last node its previous node its next pointer to start node
			m_pStartNode->pPreviousNode = pLastPointer->pPreviousNode; // set start node its previous node to node before last node

			delete pLastPointer;
			pLastPointer = nullptr; // delete last node
			--m_Size;
		}

		void pop_front()
		{
			if (m_pStartNode == nullptr)
				return;
			if (m_pStartNode->pPreviousNode == m_pStartNode)
			{
				delete m_pStartNode;
				m_pStartNode = nullptr;
			}
			Node* pLastPointer{ m_pStartNode->pPreviousNode }; // get last node
			pLastPointer->pNextNode = m_pStartNode->pNextNode; // set last node its next node to start its next node
			m_pStartNode->pNextNode->pPreviousNode = pLastPointer; // set start its next node its previous node to last node

			delete m_pStartNode;
			m_pStartNode = nullptr; // delete start node
			--m_Size;

			m_pStartNode = pLastPointer->pNextNode; // set last node its next node as start node
		}

		void remove(const Type& value)
		{
			Node* pCurrentNode{ m_pStartNode }; // get the start node
			while (pCurrentNode->pNextNode != m_pStartNode)
			{
				if (pCurrentNode->data == value)
				{
					pCurrentNode->pPreviousNode->pNextNode = pCurrentNode->pNextNode; // set current node its previous node its next node to current node its next node
					pCurrentNode->pNextNode->pPreviousNode = pCurrentNode->pPreviousNode; // set current node its next node its previous node to current node its previous node

					delete pCurrentNode;
					pCurrentNode = nullptr;
					--m_Size;

					pCurrentNode = m_pStartNode;
				}
				else
					pCurrentNode = pCurrentNode->pNextNode;
			}
			// we have checked everything except start node and last node
			if (m_pStartNode->data == value)
				pop_front();
			if (m_pStartNode->pPreviousNode->data == value)
				pop_back();
		}

		void clear()
		{
			while (m_pStartNode != nullptr)
			{
				pop_back();
			}
		}

		const std::string toString() const
		{
			if (m_pStartNode == nullptr)
				return {};
			std::string stringToBeReturned{};
			Node* pCurrentNode{ m_pStartNode };
			while (pCurrentNode->pNextNode != m_pStartNode)
			{
				stringToBeReturned += std::to_string(pCurrentNode->data) + ", ";
				pCurrentNode = pCurrentNode->pNextNode;
			}
			stringToBeReturned += std::to_string(pCurrentNode->data); // add final data
			return stringToBeReturned;
		}

		const int size() const
		{
			//if (m_pStartNode == nullptr)
			//	return 0;
			//int counter{ 1 }; // start at one since we're counting pCurrentNode
			//Node* pCurrentNode{ m_pStartNode }; // get start node
			//while (pCurrentNode->pNextNode != m_pStartNode) // check if we went through the entire thing
			//{
			//	pCurrentNode = pCurrentNode->pNextNode;
			//	++counter;
			//}
			//return counter;
			return m_Size;
		}

		Type front() const
		{
			if (m_pStartNode == nullptr)
				return Type{};
			return m_pStartNode->data;
		}

		Type back() const
		{
			if (m_pStartNode == nullptr)
				return Type{};
			return m_pStartNode->pPreviousNode->data;
		}

		// operator[]
		const Type& operator[](const size_t index) const
		{
			if (index > m_Size)
				throw OutOfBoundsException{}; // safety check
			else if (index == m_Size) // no use to check for start, since it will be the first thing found
				return m_pStartNode->pPreviousNode->data;
			else
			{
				Node* pCurrentNode{ m_pStartNode };
				int counter{};
				while (counter != index)
				{
					pCurrentNode = pCurrentNode->pNextNode;
					++counter;
				}
				return pCurrentNode->data;
			}
		}

	private:
		class OutOfBoundsException {};

		struct Node
		{
			Node(const Type& data)
				: data{ data }
				, pPreviousNode{ nullptr }
				, pNextNode{ nullptr }
			{
			}
			Node(const Node& other)
				: data{ other.data }
				, pPreviousNode{ other.pPreviousNode }
				, pNextNode{ other.pNextNode }
			{
			}

			Node* pPreviousNode;
			Node* pNextNode;
			Type data;
		};

		Node* m_pStartNode{};
		size_t m_Size{};
	};
}

#endif // !APP_BENCHMARK_LINKEDLIST_H