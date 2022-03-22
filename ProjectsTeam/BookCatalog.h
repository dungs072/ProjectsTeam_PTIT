#pragma once
#include<iostream>
#include <string>
#include "DoublyLinkedList.h"
using std::string;
using DataStructure::DoublyLinkedList;
using DataStructure::DoublyNode;


class Book
{
private:
	string MASACH;
	int trangthai = 0;
	string vitri;
public:
	Book() {};
	Book(string ms, int tt, string vt) {
		MASACH.assign(ms);
		trangthai = tt;
		vitri.assign(vt);
	};
	string getMASACH() {
		return MASACH;
	}
	void setMASACH(string newData) {
		MASACH = newData;
	}
	void setBook(string ms, int tt, string vt) {
		MASACH.assign(ms);
		trangthai = tt;
		vitri.assign(vt);
	};
};

class BookCatalog
{
private:
	DoublyLinkedList<Book> m_book;
public:
	typedef DoublyNode<Book> NodeBook;

	DoublyNode<Book>* CreateNodeBook(Book book) {
		NodeBook* node = new NodeBook;
		node->data = book;
		return node;
	}
	void setBook(string ms, int tt, string vt) {
		m_book.Clear();
		Book* newBook = new Book(ms, tt, vt);
		NodeBook* newNodeBook = new NodeBook(*newBook);
		m_book.AddFirst(newNodeBook);
	}
	BookCatalog(string ms, int tt, string vt);
	void InsertFirst_NodeBook(NodeBook*& First) {
		m_book.AddFirst(First);
	};
	void InsertAfter_NodeBook(NodeBook*& node, Book book) {
		m_book.AddAfter(node, book);
	};
	void InsertLast_NodeSach(NodeBook*& book) {
		m_book.AddLast(book);
	};
	bool containNodeBook(NodeBook* node) {
		return m_book.Contains(node);
	}
	NodeBook* getFirst() {
		return m_book.First();
	}
	NodeBook* getLast() {
		return m_book.Last();
	}
	NodeBook* GetNodeBook(NodeBook* First, int position) {
		NodeBook* node = First;
		for (int i = 0; node != nullptr; node = node->next) {
			if (i == position) break;
			++i;
		}
		return node;
	};
	NodeBook* GetNodeBook(NodeBook* First, string masach) {
		for (NodeBook* node = First; node != nullptr; node = node->next) {
			if (node->data.getMASACH() == masach) return node;
		}
		return nullptr;
	};
	void UpdateNodeBook(NodeBook*& node, Book& book) {
		if (node == nullptr) return;
		node->data = book;
	};
	Book* GetBook(NodeBook* First, string masach) {
		for (NodeBook* node = First; node != nullptr; node = node->next) {
			Book book = node->data;
			if (book.getMASACH() == masach) return &node->data;
		}
		return nullptr;
	};
	void reverseCatalog() {
		m_book.Reverse();
	}
};