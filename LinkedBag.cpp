//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <iostream>
#include <stdlib.h>
template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
	itemCount = aBag.itemCount;
  Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

  if (origChainPtr == nullptr)
      headPtr = nullptr;  // Original bag is empty
  else{
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer

      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while

      newChainPtr->setNext(nullptr);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty



//***********************************************//
//Part 1: If headPtr is a pointer variable that
//points to the first node of a linked chain of at
//least two nodes, write C++ statements that delete
//the second node and return it to the system.
//***********************************************//
template<class ItemType>
void LinkedBag<ItemType>::deleteSecondNode()
{
	if (headPtr!=nullptr) {
			Node<ItemType> *newNode = new Node<ItemType>();
	    Node<ItemType> *deleteNode = new Node<ItemType>();

	    newNode = headPtr;
			//this newNode is being set to headPtr
	    if (headPtr->getNext() != nullptr) //the next node is note null
	    {
	       deleteNode = headPtr->getNext(); //the node that needs deleting is the second node
	       newNode->setNext(deleteNode->getNext());
	       delete deleteNode; //delete the note,which is the second node
	       deleteNode = nullptr; //reassign value as deleteNode
	       itemCount --; //lost an item
	    }
	 }
}	//end deleteSecondNode

//***********************************************//
//Part 2: Revise the public method add in the class
//LinkedBag so that the new node is inserted at the
//end of the linked chain.
//***********************************************//
template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{

	Node<ItemType>* entry_ptr = new Node<ItemType>(newEntry); // dynamically allocate memory for the new entry
	Node<ItemType>* temp_ptr = headPtr; // points to what head ptr points to

	while (temp_ptr != nullptr) { //while the pointer is not null keep going down the chain
		temp_ptr = temp_ptr->getNext();
	}

	temp_ptr->setNext(entry_ptr); // set the next node to the node that we want
	return ((temp_ptr->getItem()) == newEntry); // if it worked return true
}  // end add

//***********************************************//
//Part 3A: Suppose that the class LinkedBag did not
//have the data member itemCount. Revise the method
//getCurrentSize so that it counts the number of
//nodes in the linked chain
//                A. Iteratively
//***********************************************//
template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	Node<ItemType> *thisNode = new Node<ItemType>(); //create node
  	thisNode = headPtr; //set node equal to headPtr
    int iter_count = 0; //create counter
    if (thisNode != nullptr){ //if this node is not null
      iter_count ++; 					//count up
      while(thisNode->getNext() != nullptr){ //while not null
        thisNode = thisNode->getNext();      //the node is equal to the next one
        iter_count++;												 //count up
      }
      return iter_count;

		}else{
      return iter_count;
   }
}  // end getCurrentSize


//***********************************************//
//Part 3B: Suppose that the class LinkedBag did not
//have the data member itemCount. Revise the method
//getCurrentSize so that it counts the number of
//nodes in the linked chain
//                B. Recursively
//***********************************************//
template<class ItemType>
int LinkedBag<ItemType>::getCurrentSizeRecursive()
{
	//This identifies the base case
  if (headPtr == nullptr){
		return 0;
  }else{
    headPtr = headPtr->getNext();
		//This allows the function to be Recursive
		//by calling itself
    return 1 + getCurrentSizeRecursive();
   }

} // end getCurrentSizeRecursive

//***********************************************//
//Part 4: Add a constructor to the class LinkedBag
//that creates a bag from a given array of entries.
//***********************************************//
template<class ItemType>
LinkedBag<ItemType>::LinkedBag(ItemType entryArr[], int count)
{
	Node<ItemType> *first_temp = new Node<ItemType>;
  first_temp->setItem(entryArr[0]);
	first_temp->setNext(nullptr);
	headPtr = first_temp;
	itemCount = count;
	for (int i = 1; i < count; i++)
	{
		Node<ItemType> *second_temp = new Node<ItemType>;
	  first_temp->setNext(second_temp);
	  second_temp->setItem(entryArr[i]);
	  second_temp->setNext(nullptr);
	  first_temp=second_temp;

	 }
}//end this cunstructor

//***********************************************//
//Part 5: Specify and define a method for LinkedBag
//that removes a random entry from the bag.
//***********************************************//
template<class ItemType>
ItemType LinkedBag<ItemType>::removeRandom()
{
	ItemType random_remove_bag;
  srand(time(NULL));
	int rand_num = rand() % itemCount +1;
	Node<ItemType> *freshNode = new Node<ItemType>();
	Node<ItemType> *deletingNode = new Node<ItemType>();
	Node<ItemType> *first_node = new Node<ItemType>();
	freshNode = headPtr;
	first_node=headPtr;
	if (rand_num == 0 || rand_num == 1){
	  random_remove_bag = first_node->getItem();
	  deletingNode = first_node;
	  headPtr = headPtr->getNext();
	  delete deletingNode;
	  deletingNode = nullptr;
	  return random_remove_bag;
	}else if(rand_num == itemCount){
	  for (int i = 0; i < rand_num; i++){
	  	if (i==0){}
			else{
	      first_node = first_node->getNext();
	      if (i == itemCount - 1){
	        break;
	      }
				if (i > 1 || (i != itemCount - 1)){
	        freshNode= freshNode->getNext();
	      }
	    }
	  }
	  random_remove_bag = first_node->getItem();
	  deletingNode = first_node;
	  freshNode->setNext(nullptr);
	  delete deletingNode;
	  deletingNode = nullptr;
	  itemCount --;
	  return random_remove_bag;
	}
	for (int i = 0; i < rand_num; i++){
		if (i==0){}
			else {
	    	first_node = first_node->getNext();
	      if (i > 1 && i != itemCount - 1){
	      	freshNode = freshNode->getNext();
	      }
	    }
	}
	random_remove_bag = first_node->getItem();
	deletingNode = first_node;
	freshNode->setNext(deletingNode->getNext());
	delete deletingNode;
	deletingNode = nullptr;
	itemCount --;
	return random_remove_bag;
} //end removeRandom

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
   Node<ItemType>* curPtr = headPtr;
   int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
   {
		bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
      counter++;
   }  // end while

   return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
   Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
   if (canRemoveItem)
   {
      // Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());

      // Delete first node
      Node<ItemType>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;

      itemCount--;
   } // end if

	return canRemoveItem;
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
   Node<ItemType>* nodeToDeletePtr = headPtr;
   while (headPtr != nullptr)
   {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(nullptr);
      delete nodeToDeletePtr;

      nodeToDeletePtr = headPtr;
   }  // end while
   // headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
   int counter = 0;
   Node<ItemType>* curPtr = headPtr;
   while ((curPtr != nullptr) && (counter < itemCount))
   {
      if (anEntry == curPtr->getItem())
      {
         frequency++;
      } // end if

      counter++;
      curPtr = curPtr->getNext();
   } // end while

	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains

/* ALTERNATE 1
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   return getFrequencyOf(anEntry) > 0;
}
*/
/* ALTERNATE 2
template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;
   int i = 0;
   while (!found && (curPtr != nullptr) && (i < itemCount))
   {
      if (anEntry == curPtr-<getItem())
      {
         found = true;
      }
      else
      {
         i++;
         curPtr = curPtr->getNext();
      }  // end if
   }  // end while

   return found;
}  // end contains
*/

// private
// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
   bool found = false;
   Node<ItemType>* curPtr = headPtr;

   while (!found && (curPtr != nullptr))
   {
      if (anEntry == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
   } // end while

   return curPtr;
} // end getPointerTo
