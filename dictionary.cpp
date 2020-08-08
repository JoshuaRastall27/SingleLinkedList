#include "dictionary.h"

using namespace Containers;

struct Dictionary::NODE
{

	//Constructor 
	NODE(std::string inputKey, std::string inputItem);

	Key key;
	Item item;

	NODE* nextNode;

};

Dictionary::Dictionary()
{
	head = nullptr;
}

Dictionary::~Dictionary()
{
	CompleteDeepDelete();
}

Dictionary::Dictionary(const Dictionary& original)
{
	this->head = deepCopy(original.head);
}

Dictionary::Dictionary(Dictionary&& original) noexcept(true)
{
	this->CompleteDeepDelete();
	this->head = original.head;
	original.head = nullptr;
}


Dictionary::NODE::NODE(std::string inputKey, std::string inputItem)
{
	this->key = inputKey;
	this->item = inputItem;
	nextNode = nullptr;
}


bool Dictionary::insert(Key input_key, Item input_item)
{
	//makes the inserted key present
	//attaches the input item to the key
	//make the key present
	//return true if the key was absent before the call
	//return false if the key existed before the call
	//go through the list checking each key, then add it at the end

	//if the head exists
	if (head != nullptr)
		return insertREC(input_key, input_item, head);
	else
	{
		head = new NODE(input_key, input_item);
		return true;
	}
}

bool Dictionary::insertREC(Key input_key, Item input_item, NODE* current_node_ptr)
{
	//if the current key is different to the input key and at the end of the linked list. The input key is absent from the list and a new node is created at the end
	if (current_node_ptr->key != input_key && current_node_ptr->nextNode != nullptr)
	{
		//move onto the next node in the list
		return insertREC(input_key, input_item, current_node_ptr->nextNode);
	}
	else if (current_node_ptr->key != input_key && current_node_ptr->nextNode == nullptr)
	{
		current_node_ptr->nextNode = new NODE(input_key, input_item); //Add node on the end of the list and set the pointer to it
		return true; //pull out of recursive stuff
	}
	//if the key already exists in the linked list and is present
	else
	{
		return false;
	}
}

Dictionary::Item* Containers::Dictionary::lookup(Key input_key)
{
	//return pointer to associated item of the input key
	//otherwise return nullptr
	//

	if (head != nullptr)
		return lookupREC(input_key, head);
	else
		return nullptr;
}

Dictionary::Item* Containers::Dictionary::lookupREC(Key input_key, NODE* current_node_ptr)
{
	//if keys do not match and there is another node
	if (current_node_ptr->key != input_key && current_node_ptr->nextNode != nullptr)
	{
		//go onto the next node
		return lookupREC(input_key, current_node_ptr->nextNode);
	}
	//if the key matches the current node and item needs to be sent up the recursive functions
	else if (current_node_ptr->key == input_key)
	{
		//item found, return
		return &current_node_ptr->item;
	}
	//cannot continue with the search anymore so just return nullptr as it is not found
	else
		return nullptr;


}

bool Dictionary::remove(Key input_key)
{
	//make the key absent
	//remove item and remove from the linked list?
	// return true if the key was present before being removed
	//otherwise just return false

	//go through the list until it reaches the key, needs to keep the previous node pointer on hand to 'knit' it together once removed

	if (head != nullptr)
	{
		//need to check if the head is what needs to be removed - if true then the head needs to be replaced

		if (head->key == input_key)
		{
			//swap the nodes so the next one along becomes the new head
			NODE* temp_node = head;

			if (head->nextNode != nullptr)
				head = head->nextNode;
			else
				head = nullptr;

			//delete the node
			delete temp_node;

			return true;
		}
		else
		{
			//start a node ahead as the head node needs to be handled manually
			return removeREC(input_key, head->nextNode, head);
		}

	}
	else
		return false;

}
bool Dictionary::removeREC(Key input_key, NODE* current_node_ptr, NODE* previous_node_ptr)
{
	//if keys do not match and there is another node
	if (current_node_ptr->key != input_key && current_node_ptr->nextNode != nullptr)
	{
		//go onto the next node
		return removeREC(input_key, current_node_ptr->nextNode, current_node_ptr);
	}
	else if (current_node_ptr->key == input_key)
	{
		//item found, delete the node, fix the gap and go back up the tree
		//safetly remove from the tree

		//be more efficient with stack allocation

		if (current_node_ptr->nextNode != nullptr)
		{
			//if gap needs to be fixed - try and prevent stack issues
			//fix the gap
			previous_node_ptr->nextNode = current_node_ptr->nextNode;
			//delete the node
		}
		//delete the node
		delete current_node_ptr;
		return true;
	}
	//cannot continue with the search anymore so just return nullptr
	else
		return false;
}

//automatically starts from the head
void Dictionary::CompleteDeepDelete()
{
	if (head != nullptr)
		deleteListFrom(head);
}

void Dictionary::deleteListFrom(NODE* starting_node)
{
	//deleting the dictionary does not remove the nodes, need to to remove nodes
	//go to the end of the list recursively and delete all at once
	//allocws more funtions like preserving the head
	if (starting_node != nullptr)
		deleteListREC(starting_node);

	return;
}

void Dictionary::deleteListREC(NODE* current_node)
{
	//check if is currently at the end of the linked list or not
	if (current_node->nextNode != nullptr)
		deleteListREC(current_node->nextNode); // go onto the next node if possible

	//will start when reached the end of the linked list
	delete current_node;

}


Dictionary::NODE* Dictionary::deepCopy(NODE* original_node)
{
	//copy node over
	//traverse
	//attached node

	NODE* CopiedNode = new NODE(original_node->key, original_node->item);

	//check if there's another node next in the line that needs to be copied
	if (original_node->nextNode != nullptr)
	{
		return CopiedNode->nextNode = deepCopy(original_node->nextNode); //repeat with the next node in the line
	}
	else//end of the line
	{
		return CopiedNode;
	}
}


////////////operator stuff////////////////
//deep copy assignment
Dictionary& Dictionary::operator=(const Dictionary& original)
{
	//clears the current linked list before copying stuff over into it
	this->CompleteDeepDelete();

	NODE* newHead = deepCopy(original.head);
	this->head = newHead;

	return *this;
}

//move operator
Dictionary& Dictionary::operator=(Dictionary&& original) noexcept(true)
{
	//move
	//1.delete and clear the destination pointer
	//2. deep copy over the target data
	//3. delete the old one

	//efficient pointer based move
	//1.shallow copy of original
	//2.set point of the original to null
	//

	this->CompleteDeepDelete();
	this->head = original.head;
	original.head = nullptr;
	return *this;
}