/* 
Name: HARSH RANA
Student Number: 100351582
Assignment #3, CPSC 2150 
Assigned by Dr.Gladys Monagan
LList::SEP and LList::NOT_DEFINED documented and provided by  Dr.Gladys Monagan
*/
#ifndef LLIST_H
#define LLIST_H
#include <string>
#include <iostream>

class  LList {
   public:
      // create an empty list
      LList();

      // return true if the list is empty, false otherwise
      bool isEmpty() const;

      // insert x at the beginning of the list
      // precondition: there is enough heap memory
      // postcondition: x is placed in the list as first element
      void cons(short x);

      // append x to the end of the list
      // precondition: there is enough heap memory
      // postcondition: x is placed as the last element
      void append(short x);

      // return the number of elements in the list
      int length() const;

      // determine if x is in the list
      // postcondition: return true if x is found, false otherwise
      bool search(short x) const;

      // return the first element of the list and 
      // return LList::NOT_DEFINED if the list is empty
      short first() const;

      // return the last element of the list and 
      // return LList::NOT_DEFINED if the list is empty
      short last() const;

      // value returned when the list is empty and first() or last() is called
      static const short NOT_DEFINED;

      // remove all the occurrence of x in the list 
      // postcondition: return true if at least one x was removed 
      // and return false if no occurrences of x were removed
      bool removeAll(short x);

      // transfer all the elements from the 'other' list into this list so that 
      // the elements of the other list are at index idx in the resulting list
      // which stays as this list (use of idx like in splice of Javascript)
      // -> when idx == 0, all the elements of the 'other' list will
      //    be placed before the 'original' elements of this list
      //    the first element of the 'other' list will be at index 0 as
      //    the first element of this list and the 'original' elements of this
      //    list will be appended to the last element of the 'other'
      // -> when idx >= length() 
      //    (i.e. if idx is greater than the length of this list),
      //    all the elements of the 'other' list are appended to this list
      // precondition: idx >= 0, length() >= 0, other.length() >= 0
      // postcondition: all the elements of the 'other' list are removed 
      // and placed into this list starting at index idx
      // 
      // As a result of calling splice, the lengths of both lists change so
      // that other.length() becomes 0 (all the elements are removed)
      // splice is a mutator method both for this object and for the 'other' object
      void splice(LList& other, int idx);

      // split the list into two halves: keep one half and return the other half
      // Example: if this list had [ 2 14 5 -1 37 ], this list keeps [ 2 14 ]
      // and the list returned has now as list [ 5 -1 37 ]
      // 
      // if the number of elements n in this list is odd, 
      // this object keeps the first floor(n/2) elements 
      // and the other object has the second half which is the list 
      // with the last floor(n/2) + 1 elements 
      LList halve();

      // return true if the lfSide is equal to the rtSide 
      // meaning that the elements of both lists are equal and in the same order
      friend bool operator == (const LList& lfSide, const LList& rtSide);

      // return true if the lfSide is not equal to the rtSide list, false otherwise
      friend bool operator != (const LList& lfSide, const LList& rtSide);
      
      // output in the order in which they are in the list 
      // from first to last in this format:
      //    -> the character '[' followed by the LList::SEP
      //    -> for each element: the element's value followed by the LList::SEP
      //    -> the character ']'
      // output has the form [SEPelement ... SEPelementSEP]
      // an empty list is output as [SEP]
      // Example: 3 elements would output "[ 41 36 999 ]" if the SEP is a blank
      friend std::ostream& operator << (std::ostream&, const LList&);

      // copy constructor
      // we assuming that there is enough heap memory to make a copy
      LList(const LList&);

      // overloaded assignment operator
      // we assuming that there is enough heap memory to make a copy
      LList& operator = (const LList&);

      // destructor
      ~LList();

      // string that separates the values of the list when outputting
      static const std::string SEP;

      #ifndef NDEBUG
      // dump the array (print the contents of the internal array) 
      // using the ostream passed which defaults to std::cout
      void dumpNodesArray(std::ostream& out = std::cout) const;
      #endif

   private:
      struct Node {
         short item;
         int link;
      };

      // the array of nodes has INITIAL_CAPACITY nodes
      static const int INITIAL_CAPACITY = 4;

      // dynamic array of nodes
      Node *nodes;

      // index of the first node in the linked list
      int head;

      // index of the first node of the "free nodes' list"
      int free;

      // simply to keep track of total nodes
      int totalNodes;

      // finds the length of the list formed by following links of provided head
      static int findLength(Node* nodes, int startingIndex);

      // checks if more free nodes are needed
      // appends if yes 
      void appendArrayIfNeeded();

      // appends the array
      void appendTheArray();

      // finds the last node for the provided head by following links
      static int findTailNode(Node *p, int starting);
      
      // copies the provided array into a second provided array. Only copies number of elements specified.
      // PRECONDITION: appendedNodes.length() >= nodes.length()
      static void copyArray(Node* nodes, Node*& appendedNodes, int elementsToBeCopied);


};
#endif
