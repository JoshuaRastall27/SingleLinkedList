#pragma once
#include <string>

namespace Containers
{
	//singally linked list
	class Dictionary
	{
	public:
		using Key = std::string;
		using Item = std::string;

		Dictionary();//main constructer
		~Dictionary(); //deconstructor
		Dictionary(const Dictionary&); //copy constructor
		Dictionary(Dictionary&&) noexcept(true); //move constructor

		Dictionary& operator=(const Dictionary&); //copy operator
		Dictionary& operator=(Dictionary&&) noexcept(true); //move assignment operator
	

		bool insert(Key, Item);//insert an item
		Item* lookup(Key); //return pointer to searched item
		bool remove(Key); //remove item, 

		void CompleteDeepDelete(); //delete all nodes from the list - starts delete function at head


	private:
		/////private vars/////
		struct NODE;
		NODE* head; //starting node


		/////private functions/////

		//recursive worker functions
		static bool insertREC(Key, Item, NODE*); //key, item and target node pointer
		static Item* lookupREC(Key, NODE*);
		static bool removeREC(Key, NODE*, NODE*); //key and target node pointer

		static void deleteListFrom(NODE*); //DELETES starting from the input node. starts off the delete recursion from the input node
		static void deleteListREC(NODE*);



		//operation functions
		static NODE* deepCopy(NODE*);
	};


}
