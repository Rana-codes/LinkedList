/* 
Name: HARSH RANA
Student Number: 100351582
Assignment, CPSC 2150 
LList::SEP and LList::NOT_DEFINED documented and provided by  Dr.Gladys Monagan
*/
#include "LList.h"
#include <string>
#include <iostream>
#include <cassert>
#include <climits>
#include <cmath>


// separates the elements when using the operator << 
const std::string LList::SEP = std::string(" ");

// Another constant defined for ease.
// Such a value has been chosen which is highly unlikely to be picked by the user
const short LList::NOT_DEFINED = SHRT_MIN;

/**
 * Creates an empty list using dynamic array
 * POSTCONDITION: an empty linked list is created
 */
LList::LList(){
    nodes = new Node[INITIAL_CAPACITY];
    for(int i = 0; i <INITIAL_CAPACITY-1; i++){
        nodes[i].item = SHRT_MIN; // this value is used as it is highly unlikely to be picked by the user
        nodes[i].link = i+1;
    }
    // last element declared manually to end the link with -1
    nodes[INITIAL_CAPACITY-1].item = SHRT_MIN;
    nodes[INITIAL_CAPACITY-1].link = -1;
    head = -1;
    free = 0;
    totalNodes = INITIAL_CAPACITY;
}

/**
 * Checks if the list is empty.
 * POSTCONDITION: Returns true if the list is empty or vice versa.
 */
bool LList::isEmpty() const{
    return head == -1;
}

/**
 * Copies the content of all the nodes from one array to another
 * PRECONDITION: appendedNodes.length() >= nodes.length()
 * POSTCONDITION: data stored in appendedNodes is lost and nodes, appended nodes become identical
 */
void LList::copyArray(Node* nodes, Node*& appendedNodes, int elementsToBeCopied){
    for(int i = 0; i < elementsToBeCopied; i++){
        appendedNodes[i].item = nodes[i].item;
        appendedNodes[i].link = nodes[i].link;
    }
}

//HELPER FOR APPEND ARRAY IF NEEDED, SPLICE
/**
 * Increases the size of the dynamic array used to store the list.
 * Makes sure all the items and links are kept. returns free memory to the heap
 * POSTCONDITION: The array storing the list is now double in length. 
 * NOTE: uses "copyArray"
 */
void LList::appendTheArray(){
    const int NEW_LENGTH = totalNodes*2;
    Node* appendedNodes = new Node[NEW_LENGTH];

    copyArray(nodes, appendedNodes, totalNodes-1); // -1 bcs last node is to be linked to others

    for(int i = totalNodes-1; i <NEW_LENGTH-1; i++){
        appendedNodes[i].item = SHRT_MIN;
        appendedNodes[i].link = i+1;
    }
    appendedNodes[NEW_LENGTH-1].item = SHRT_MIN;
    appendedNodes[NEW_LENGTH-1].link = -1;

    delete[] nodes;

    nodes = appendedNodes;
    totalNodes = NEW_LENGTH;
}

//HELPER FOR CONS, APPEND
/**
 * Checks if the array is to be appended. Appends it if necessary
 * POSTCONDITION: If only 1 free node is left, the array is appended.
 * NOTE: uses function"appendTheArray()""
 */
void LList::appendArrayIfNeeded(){
    if(nodes[free].link == -1){
        appendTheArray();
    }
}

/**
 * finds out the last node of the provided head.
 * POSTCONDITION: returnsthe index of the last node of the list.
 */
int LList::findTailNode(Node *nodes, int head){
    while(head != -1){
        if(nodes[head].link == -1){
            return head;
        }
        head = nodes[head].link;
    }
    return -1;
}

/**
 * inserts x at the beginning of the list
 * PRECONDITION: there is enough heap memory
 * POSTCONDITION:x is placed in the list as first element
 */
void LList::cons(short x){
    int indexOfNextFreeNode = nodes[free].link;

    nodes[free].item = x;
    nodes[free].link = head;
    head = free;
    free = indexOfNextFreeNode;

    appendArrayIfNeeded();
}

/**
 * Adds the provided element to the end of the linked list
 * PRECONDITION: there is enough heap memory
 * POSTCONDITION: x is placed as the last element
 */
void LList::append(short x){
    int indexOfNextFreeNode = nodes[free].link;

    nodes[free].item = x;
    nodes[free].link = -1;

    if(head == -1){
        head = free;
    }
    else{
        int tail = findTailNode(nodes, head);
        nodes[tail].link = free;
    }

    free = indexOfNextFreeNode;

    appendArrayIfNeeded();
}

//HELPER FOR LENGTH
/**
 * get the length of the list using the provided startingIndex in the array.
 */
int LList::findLength(Node* nodes, int startingIndex){
    int length = 0;
    while (startingIndex != -1){
        startingIndex = nodes[startingIndex].link;
        length ++;
    }

    return length;
}

/**
 * return the number of elements in the list
 * POSTCONDITION: An int value equivalent to the length of the list is returned.
 */
int LList::length() const{
    return findLength(nodes, head);
}

/**
 * determine if x is in the list
 * POSTCONDITION:  return true if x is found, false otherwise
 */
bool LList::search(short x) const{
    if(head == -1){
        return false;
    }
    int reference = head;
    while(reference != -1){
        if(nodes[reference].item == x){
            return true;
        }
        reference = nodes[reference].link;
    }
    return false;
}

/**
 * looks at the first element of list.
 * POSTCONDITION: returns the first value, NOT_DEFINED if the list is empty
 */
short LList::first() const{
    if(head == -1){
        return NOT_DEFINED;
    }
    return nodes[head].item;
}

/**
 * looks at the last element of list.
 * POSTCONDITION: returns the last value, NOT_DEFINED if the list is empty
 */
short LList::last() const{
    if(head == -1){
        return NOT_DEFINED;
    }
    return nodes[findTailNode(nodes, head)].item;
}

/**
 * remove all the occurrence of x in the list 
 * POSTCONDITION: returns true if any x is removed from the lise, else returns false.
 */
bool LList::removeAll(short x){
    if(head == -1){// if list is empty, no work is needed
        return false;
    }
    bool removed = false;
    int reference = head;
    while(reference != -1){

        if(nodes[head].item == x){// if its the first element
            head = nodes[reference].link;

            nodes[reference].item = SHRT_MIN;
            nodes[reference].link = free;
            free = reference;

            reference = head;
            removed = true;
        }
        else{// it can't be the 1st item
            if(nodes[nodes[reference].link].item == x){
                int indexToBeFreed = nodes[reference].link;
                nodes[reference].link = nodes[indexToBeFreed].link;

                nodes[indexToBeFreed].item = SHRT_MIN;
                nodes[indexToBeFreed].link = free;

                free = indexToBeFreed;
                removed = true;
                // did not move to the next link as values might be repeated.
                //for eg [ 6 5 5 ], if we move a 5 will be left.
            }
            else{
                reference = nodes[reference].link;
            }
        }
    }
    return removed; 
}

/**
 * empties the contents of a list into another list at a specified index
 * PRECONDITION: Sufficient heap memory is present
 * POSTCONDITION: all the elements of provided list are inserted into the existing
 * one at the given index.
 */
void LList::splice(LList& other, int idx){

    if(findLength(other.nodes, other.head) == 0){
        return;
    }
    
    if(idx >= findLength(nodes, head)){
        idx = findLength(nodes, head);
    }
        // WE KEEP TRACK OF ALL THE NECESSARY ITEMS
        // WE FIRST CREATE NEW NODES IN THE FREE NODES, THESE NODES HAVE ALL DATA FROM THE OTHER ARRAY
        int newFree = -1;
        int oldHead = head;
        int reference = other.head;
        int nxtFreeNode = free;
        while(reference != -1){
            if(nodes[nxtFreeNode].link == -1){
                appendTheArray();
            }
            nodes[nxtFreeNode].item = other.nodes[reference].item;
            newFree = nxtFreeNode;
            nxtFreeNode = nodes[nxtFreeNode].link;
            reference = other.nodes[reference].link;

            if(reference == -1){
                nodes[newFree].link = -1;
            }
        }
        // NOW WE HAVE THE 2ND LIST IN OUR ARRAY, WE JUST NEED TO LINK IT PROPERLY
        // LINKING IS DIFFERENT FOR DIFFERENT CASES
        if(idx == 0){ // BEFORE THE LIST
            head = free;
            free = nxtFreeNode;
            nodes[findTailNode(nodes, head)].link = oldHead;
        }
        else if( idx == findLength(nodes, head)){ // AT THE END
            nodes[findTailNode(nodes, head)].link = free;
            free = nxtFreeNode;
        }
        else{// SOMEWHERE IN MIDDLE
            int idxreference = head;
            for(int i = 0; i < idx-1; i++){
                idxreference = nodes[idxreference].link;
            }
            int brkpt = nodes[idxreference].link;
            nodes[idxreference].link = free;
            nodes[findTailNode(nodes, free)].link = brkpt;
            free = nxtFreeNode;
        }// NOW ALL I HAVE TO DO IS EMPTY THE OTHER LIST
        // THE ARRAY WAS NOT DELETED AS THIS LIST MIGHT STILL BE USED AGAIN
    for(int i = 0; i < other.totalNodes-1; i++){
        other.nodes[i].item = SHRT_MIN;
    }
    other.nodes[totalNodes-1].item = SHRT_MIN;
    other.nodes[totalNodes-1].link = -1;
    other.head = -1;
    other.free = 0;
}

/**
 * Divides the list into 2 parts
 * PRECONDITION: Sufficient heap memory is present
 * POSTCONDITION: if the number of elements n in this list is odd, 
 * this object keeps the first floor(n/2) elements and other list keeps the rest.
 */
LList LList::halve(){
    LList answer;

    int breakPoint = floor((findLength(nodes, head))/2.00);
    int currentIndex = head;

    
    if(head == -1){
        return answer;
    }
    //SPECIAL CASE
    else if(breakPoint < 1){ // when only 1 element
        answer.append(nodes[currentIndex].item);
        nodes[currentIndex].item = SHRT_MIN;
        head = -1;
        free = 0;

        return answer;
    }

    for(int i = 0; i < breakPoint-1; i++){// TRAVELLING TO THE POINT WHERE DIVISION OCCURS
        currentIndex = nodes[currentIndex].link;
    }
    // we are at the brk pt.
    int brkpt = currentIndex;
    currentIndex = nodes[currentIndex].link;
    int oldFree = free;

    while(currentIndex != -1){// APPENDING THE NEW LIST AND EMPTYING THE OLD ONE
        answer.append(nodes[currentIndex].item);
        nodes[currentIndex].item = SHRT_MIN;
        currentIndex = nodes[currentIndex].link;
    }

    // 2ND LIST IS GOOD AS IT WAS APPENDED, WE JUST NEED TO FIX LINKING OF THE EXISTING LIST
    free = nodes[brkpt].link;
    nodes[brkpt].link = -1;
    nodes[findTailNode(nodes, free)].link = oldFree; 
    
    return answer;
}

/**
 * operator to check if two lists are equal
 * POSTCONDITION: Returns true if both lists are identical, else vice versa
 */
bool operator == (const LList& lfSide, const LList& rtSide){
    if(LList::findLength(lfSide.nodes, lfSide.head) != LList::findLength(rtSide.nodes, rtSide.head)){
        return false;
    }
    int lfreference = lfSide.head;
    int rtreference = rtSide.head;
    while(lfreference != -1){
        if(lfSide.nodes[lfreference].item != rtSide.nodes[rtreference].item){
            return false;
        }
        lfreference = lfSide.nodes[lfreference].link;
        rtreference = rtSide.nodes[rtreference].link;
    }
    return true;

}

/**
 * operator to check if two lists are not equal
 * POSTCONDITION: Returns true if both lists are not identical, else vice versa
 */
bool operator != (const LList& lfSide, const LList& rtSide){
    return !(lfSide == rtSide);
}

//OUTPUT OPERATOR
/**
 *outputs elements of the list in a stream in the exact same order as they are present
 * eg [ 1 2 3 ]
 * POSTCONDITION: output in the order in which they are in the list
 */
std::ostream& operator << (std::ostream& out, const LList& list){
    out <<"["<< LList::SEP ;
    int refference = list.head;
    while(refference != -1){
        out << list.nodes[refference].item << LList::SEP;
        refference = list.nodes[refference].link;
    }
    out << "]";

    return out;
}

//COPY CONSTRUCTOR
/**
 * creates a copy of the provided list
 * PRECONDITION: Sufficient heap memory is present
 * POSTCONDITION: A copy of the list is created
 */
LList::LList(const LList& rhs){
    
    nodes = new Node[rhs.totalNodes];

    copyArray(rhs.nodes, nodes, rhs.totalNodes);
    head = rhs.head;
    free = rhs.free;
    totalNodes = rhs.totalNodes;

}

//ASSIGNMENT OPERATOR
/**
 * deletes old data and copies new data into the list.
 * PRECONDITION: Sufficient heap memory is present
 * POSTCONDITION: provided list is over-written with the contents of previous list
 */
LList& LList::operator = (const LList& rhs){
    if(head != -1){
        delete[] nodes;
        nodes = new Node[rhs.totalNodes];
    }

    copyArray(rhs.nodes, nodes, rhs.totalNodes);
    head = rhs.head;
    free = rhs.free;
    totalNodes = rhs.totalNodes;

    return *this;
}

//DESTRUCTOR
/**
 * Is called automatically when the program terminates to cleanup.
 * POSTCONDITION: Deletes a list.
 */
LList::~LList(){
    delete [] nodes;
    nodes = nullptr;
    head = -1;
    free = -1;
}

/**
 * Prints out all the elements required to understand the structure of the given linked list.
 */
void LList::dumpNodesArray(std::ostream& out) const{
    int n = findLength(nodes, head);

    out << "head = " << head << "\t" << "free = " << free << "\t";
    out << "n = " << n << "\t" <<"capacity = " << totalNodes << "\n\n";

    for(int i = 0; i < totalNodes; i++){
        out << "\t"<< i << "\t" ;
        if(nodes[i].item == SHRT_MIN){
            out << "***" << "\t" << nodes[i].link << "\n";
        }
        else{
            out << nodes[i].item << "\t" << nodes[i].link << "\n";
        }
    }

    out <<"\nList = " <<"["<< LList::SEP ;
    int refference = head;
    while(refference != -1){
        out << nodes[refference].item << LList::SEP;
        refference = nodes[refference].link;
    }
    out << "]\n";
}

