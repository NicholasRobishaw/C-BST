#include "BST_Utility.h"

// notes
// https://www.cs.usfca.edu/~galles/visualization/BST.html

/*
Name: clearTree
Process: recursively returns dynamically allocated data to the OS,
         uses post order traversal strategy
Function input/parameters: head pointer (StudentDataType *)
Function output/parameters: none
Function output/returned: empty tree (NULL)
Device input/---: none
Device output/---: none
Dependencies: free, clearTree (recursively)
*/
TreeNodeType *clearTree( TreeNodeType *wkgPtr )
  {
  // use post order
  // when arriving at a node
  // check if current is NULL
  if( wkgPtr != NULL )
    {
    // try recurse left
    clearTree( wkgPtr->leftChildPtr );
    
    //  try recurse right
    clearTree( wkgPtr->rightChildPtr );
    
    // free current
  	free( wkgPtr );
    }
  // return sucess 	
  return NULL;	
  }

/*
Name: compareRoomNumbers
Process: compares room numbers as follows:
         - if left room number is greater than the right room number, 
         returns value greater than zero (not necessarily 1)
         - if left room number is less than the right room number, 
         returns value less than zero (not necessarily -1)
         - if room numbers are equal but one is longer, longer one is greater
         - otherwise, returns zero
Function input/parameters: two room numbers (as strings)
                           to be compared (const char *)
Function output/parameters: none
Function output/returned: result as specified above (int)
Device input/---: none
Device output/---: none
Dependencies: isDigit
*/
int compareRoomNumbers( const char *roomNbrOne, const char *roomNbrTwo )
  {
  // variables	
  int sum, index = 0;	
  
  // test
  //printf("entered compareRoomNumbers, before while loop\n ");
  
  // add case for if one is NULL
  if( roomNbrOne == NULL)
    {
    return 0;// used to be 1
	}
  
  // test
  //printf( "roomNbrOne : %s, roomnbrTwo: %s\n", roomNbrOne, roomNbrTwo );
  
  // iterate through string of numbers
  while( roomNbrOne[ index ] != NULL_CHAR && roomNbrTwo[ index ] != NULL_CHAR )	
    {           
    // check if roomNbrOne and roomNbrTwo is a digit
    if( isDigit( roomNbrOne[ index ] ) && isDigit( roomNbrTwo[ index ] ) )
      {
      // sub roomNbrOne and roomNbrTwo  
      sum = roomNbrOne[ index ] - roomNbrTwo[ index ];
    
      // if sum is not zero
      if( sum != 0 )
        {
        //printf( "returned sum\n" );    
        // return sum
        return sum;    
        }  
      }
       
    // else iterate index and try next  
    index++;   
    }

  // if roomNbrOne is larger in length
  if( roomNbrOne[ index ] != NULL_CHAR && roomNbrTwo[index] == NULL_CHAR )
    {
    // return -1;
    return -1;
    }
	
  // other wise roomNbrTwo is larger in length
  else if( roomNbrOne[ index ] == NULL_CHAR && roomNbrTwo[index] != NULL_CHAR )
    {
    // return 1 
    return 1;
    }
    
  // return the sum
  return sum;
  }

/*
Name: copyTree
Process: recursively duplicates the provided tree
         using a pre order traversal strategy
Function input/parameters: working pointer for recursion (TreeNodeType *)
Function output/parameters: none
Function output/returned: pointer to duplicate tree (TreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: createTreeNodeFromNode
*/
TreeNodeType *copyTree( TreeNodeType *wkgPtr )
  {	 	
  // variables
  TreeNodeType *newTree = NULL;
  
  // check if the current is not NULL
  if( wkgPtr != NULL )
    {	   	
    // copy the current value into the new tree
    newTree = createTreeNodeFromNode( *wkgPtr );
  
    // try to copy left chiild
    newTree->leftChildPtr = copyTree( wkgPtr->leftChildPtr );
  
    // try to copy right child 
  	newTree->rightChildPtr = copyTree( wkgPtr->rightChildPtr );
    }
  	
  // return pointer
  return newTree;
  }

/*
Name: copyString
Process: copies source string to destination string
Function input/parameters: source string (const char *)
Function output/parameters: destination string (char *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void copyString( char *destStr, const char *srcStr )
  {
  // variables
  int index = 0;
  
  // copy string while not at NULL_CHAR
  while( srcStr[index] != NULL_CHAR )
    {
    // set the character from srcStr at the index to the dest at the index
    destStr[index] = srcStr[index];
    
    // increment index
    index++;
    
    // set the next destIndex to NULL_CHAR
    destStr[index] = NULL_CHAR;
    } 
  }

/*
Name: createTreeNodeFromData
Process: captures data from individual data items, 
         dynamically creates new node,
         copies data, sets child pointers to NULL,
         and returns pointer to new node         
Function input/parameters: room number, building room, 
                           class setup (const char *), and capacity (int)
Function output/parameters: none
Function output/returned: pointer to new node as specified (TreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: malloc, sizeof, copyString
*/
TreeNodeType *createTreeNodeFromData( const char *rmNumber, 
                   const char *buildingRm, const char *clsSetup, int capacity )
  {
  // variables
  // create the struct variables
  TreeNodeType *newNode;
  
  // allocate the memeory for the treeNode
  newNode = (TreeNodeType *)malloc( sizeof(TreeNodeType) );
  
  // set child pointers to NULL
  newNode->leftChildPtr = NULL;
  newNode->rightChildPtr = NULL;
  
  // copy data into new node
  copyString( newNode->buildingRoom, buildingRm );
  copyString( newNode->roomNumber, rmNumber );
  copyString( newNode->classSetup, clsSetup );
  newNode->roomCapacity = capacity;
  
  // return pointer to the newly created node
  return newNode;	
  }

/*
Name: createTreeNodeFromNode
Process: captures data from source node pointer, dynamically creates new node,
         copies data, sets child pointers to NULL, 
         and returns pointer to new node         
Function input/parameters: node to be copied (const TreeNodeType)
Function output/parameters: none
Function output/returned: pointer to new node as specified (TreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: variable options
*/
TreeNodeType *createTreeNodeFromNode( const TreeNodeType sourceNode )
  {	
  // create the new node
  TreeNodeType *newNode;   
  
  // allocate the memeory for the treeNode
  newNode = (TreeNodeType *)malloc( sizeof(TreeNodeType) ); 
      
  // create the new tree node with ( createTreeFromData )
  setTreeNodeData( newNode, sourceNode );
  
  // set the child pointer to NULL
  newNode->leftChildPtr = NULL;
  
  newNode->rightChildPtr = NULL;
  
  // return the new pointer node
  return newNode;
  }

/*
Name: displayInOrder
Process: recursively displays tree using in order traversal
Function input/parameters: working pointer for recursion (TreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: printf, displayInOrder (recursively)
*/
void displayInOrder( TreeNodeType *wkgPtr )
  {  
  // check if wkgPtr is not NULL
  if( wkgPtr != NULL )
    {    	
    // recurse left
    displayInOrder( wkgPtr->leftChildPtr );
    
    // print current
    printf( "%s: %s\n", wkgPtr->roomNumber,  wkgPtr->buildingRoom );
    
    // recurse right    
    displayInOrder( wkgPtr->rightChildPtr );
    }
  }

/*
Name: displayPostOrder
Process: recursively displays tree using post order traversal
Function input/parameters: working pointer for recursion (TreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: printf, displayPostOrder (recursively)
*/
void displayPostOrder( TreeNodeType *wkgPtr )
  {
  // post (left, right, current)
  
  // when you land on a node
  // check if not NULL
  if( wkgPtr != NULL )
    {
    // recurse left
    displayPostOrder( wkgPtr->leftChildPtr );
    
    // recurse right
    displayPostOrder( wkgPtr->rightChildPtr );
    
    // print current    
    printf( "%s: %s\n", wkgPtr->roomNumber,  wkgPtr->buildingRoom );
    }
  }

/*
Name: displayPreOrder
Process: recursively displays tree using pre order traversal
Function input/parameters: working pointer for recursion (TreeNodeType *)
Function output/parameters: none
Function output/returned: none
Device input/---: none
Device output/monitor: displayed as specified
Dependencies: printf, displayPreOrder (recursively)
*/
void displayPreOrder( TreeNodeType *wkgPtr )
  {
  // pre ( current, left, right)
  
  // when you land on a node
  // check if not NULL
  if( wkgPtr != NULL )
    {
    // print current    
    printf( "%s: %s\n", wkgPtr->roomNumber,  wkgPtr->buildingRoom );
    // recurse left
    displayPreOrder( wkgPtr->leftChildPtr );
    
    // recurse right
    displayPreOrder( wkgPtr->rightChildPtr );
    }   
    
  }

/*
Name: getStringLength
Process: returns length of c-style string using helper function
Function input/parameters: string (const char *)
Function output/parameters: none
Function output/returned: string length (int)
Device input/---: none
Device output/---: none
Dependencies: getStringLengthHelper
*/
int getStringLength( const char *str )
  {	
  // return the length ( call the helper function at 0) 	
  return getStringLengthHelper( str, 0 );
  }

/*
Name: getStringLengthHelper
Process: recursively iterates across string to find length
Function input/parameters: string to be tested (const char *),
                           index for recursion
Function output/parameters: none
Function output/returned: length of string (int)
Device input/---: none
Device output/---: none
Dependencies: getStringLengthHelper (recursively)
*/
int getStringLengthHelper( const char *str, int index )
  {    
  // check if index is not NULL CHAR
  if( str[index] != NULL_CHAR )
    {
    return getStringLengthHelper( str, index + 1 ) + 1;
    }  

  // return the current + index
  return 0;
  }

/*
Name: initializeBST
Process: sets BST root pointer to NULL, root pointer is returned by address
Function input/parameters: address of working pointer (TreeNodeType **)
Function output/parameters: address of updated working pointer 
                            (TreeNodeType **)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: none
*/
void initializeBST( TreeNodeType **bstPtr ) // keep in mind its a double
  {		
  // set the BST root ** to NULL	
  *bstPtr = NULL;
  }

/*
Name: insert
Process: recursively searches for available node in BST,
         creates new node and returns it to the calling function,
         if node is already in tree, data is overwritten,
         uses "look down" strategy for adding nodes to tree
Function input/parameters: working pointer for recursion (TreeNodeType *),
                           node to be inserted (const TreeNodeType)
Function output/parameters: none
Function output/returned: pointer to root node (TreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: compareRoomNumbers, setTreeNodeData, createTreeNodeFromNode,
              insert (recursively)
*/
TreeNodeType *insert( TreeNodeType *wkgPtr, const TreeNodeType inData )
  {
  // check if wkgPtr is NULL
  if( wkgPtr != NULL )
    {
    // variables
    int sum;          
    
    // calculate sum  
    sum = compareRoomNumbers( inData.roomNumber, wkgPtr->roomNumber );
  
    // check if search value is less than local data
    if( sum < 0 )
      {
      // check if left child does not exist
      if( wkgPtr->leftChildPtr == NULL )       
        {
        // assign the current node's left child
	    // to a new node with the given data
        wkgPtr->leftChildPtr = createTreeNodeFromNode( inData ); 
        }
      // otherwise, assume left child does exist
      else
	    {
        // call the function recursively to the left
        wkgPtr->leftChildPtr = insert( wkgPtr->leftChildPtr, inData );
	    }
   
      }

    // otherwise, check if searchVal is greater than local data
    else if( sum > 0 )
      {
      // check if right child does not exist
      if( wkgPtr->rightChildPtr == NULL)
        {
        // assign in Data to right child    
        wkgPtr->rightChildPtr = createTreeNodeFromNode( inData );
        }
        
      // otherwise, assume right child exists
      else
        {
        // recurse right
        wkgPtr->rightChildPtr = insert( wkgPtr->rightChildPtr, inData );    
        }    
	  }

    // otherwise, assume data searchVal is equal to local data
    else
      {
      setTreeNodeData( wkgPtr, inData );
      }
      
    }
    
  // otherwise assume at root
  else
    {
    wkgPtr = createTreeNodeFromNode( inData );
    }
        
  // return the root node pointer
  return wkgPtr; 
  }

/*
Name: isDigit
Process: checks for if digit character,
         one line of code
Function input/parameters: test character (char)
Function output/parameters: none
Function output/returned: result of test as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isDigit( char testVal )
  {
  // return true if digit otherwise return false	
  return testVal >= '0' && testVal <= '9';
  }

/*
Name: isEmpty
Process: tests root node for NULL, returns result,
         one line of code
Function input/parameters: pointer to root node (TreeNodeType *)
Function output/parameters: none
Function output/returned: result of test as specified (bool)
Device input/---: none
Device output/---: none
Dependencies: none
*/
bool isEmpty( TreeNodeType *rootPtr)
  {
  // check if pointer is NULL	

  return rootPtr == NULL;	
  }

/*
Name: removeFromMin
Process: recursively searches for min node,
         when found, node is unlinked from tree and returned,
         other linkage is managed
Function input/parameters: pointer to parent and child nodes (TreeNodeType *)
Function output/parameters: none
Function output/returned: pointer to removed node (TreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: removeFromMin (recursively)
*/
TreeNodeType *removeFromMin( TreeNodeType *parentPtr, TreeNodeType *childPtr )
  {       
  // search for min node
  // recurse left until hit NULL
  if( childPtr->leftChildPtr != NULL )
    {
    // try next level
    return removeFromMin( childPtr, childPtr->leftChildPtr );        
    }  

  // set the parents left the the childs right 
  parentPtr->leftChildPtr = childPtr->rightChildPtr;
  
  // return pointer to minNode
  return childPtr;  
  }

/*
Name: removeItem
Process: searches for item, 
         captures removed item, if available, from search pointer, 
         then removes item from tree using helper function and returns true,
         otherwise sets removed node pointer to NULL and returns false
Function input/parameters: address of pointer to root node (TreeNodeType *),
                           node to be removed with at least room number key
Function output/parameters: address of updated root node pointer 
                            (TreeNodeType **), 
                            pointer to removed item node (TreeNodeType *)
Function output/returned: Boolean result of operation (bool)
Device input/---: none
Device output/---: none
Dependencies: search, setTreeNodeData, removeItemHelper
*/
bool removeItem( TreeNodeType *removedNodePtr, 
                           TreeNodeType **rootPtr, const TreeNodeType outData )
  {	 	
  // variables
  TreeNodeType *tempNode = search( *rootPtr, outData );
  
  // if the item is avaliable
  if( tempNode != NULL )
    {	  	
    // capture it from search pointer
    setTreeNodeData( removedNodePtr, *tempNode );

    // remove item from tree
    *rootPtr = removeItemHelper( *rootPtr, *tempNode );// was wkgPtr
    
    // return true
    return true;
    }  
    
  removedNodePtr = NULL;
    
  // return failure  
  return false;
  }

/*
Name: removeItemHelper
Process: recursively searches for item, removes node,
         returns dynamic memory of removed node to OS,
         returns updated link to parent (at each recursive level),
         only one return at end of function
Function input/parameters: pointer to working node (TreeNodeType *),
                           node to be removed with at least state name key
                           (const TreeNodeType)
Function output/parameters: none
Function output/returned: link to recursive parent (TreeNodeType *)
Device input/---: none
Device output/---: none
Dependencies: compareRoomNumbers, setTreeNodeData, removeFromMin, free,
              removeItemHelper (recursively)
*/
TreeNodeType *removeItemHelper( TreeNodeType *wkgPtr, 
                                                   const TreeNodeType outData )
  {       
  // variables
  TreeNodeType *itemToDelete, *minNode;
  int sum = compareRoomNumbers( outData.roomNumber, wkgPtr->roomNumber );
  
  // check if less than current
  if( sum < 0 )
    {
    // try left
    wkgPtr->leftChildPtr = removeItemHelper( wkgPtr->leftChildPtr, outData );  
    }
  
  // check if greater than current
  else if( sum > 0 )
    {
    // try right
    wkgPtr->rightChildPtr = removeItemHelper( wkgPtr->rightChildPtr, outData );
    }      
    
    // for node with 1 child 
    // check for the current nodes lft child to be NULL
  else if( wkgPtr->leftChildPtr == NULL ) 
    {
    itemToDelete = wkgPtr;    
          
    // return right child ptr
    wkgPtr = itemToDelete->rightChildPtr;    
      
    // free removed item
    free( itemToDelete );
    }
    
  // for node with 1 child
  // check for the current nodes right child to be NULL
  else if( wkgPtr->rightChildPtr == NULL )  
    {   
    //
    itemToDelete = wkgPtr; 
      
    // return left child ptr
    wkgPtr = wkgPtr->leftChildPtr;
      
    // free removed item
    free( itemToDelete );
    }
    
  // removing node with 2 children
  // check that the right child has a left child
  else if( wkgPtr->rightChildPtr->leftChildPtr != NULL )
    {     
    // get the min of the right side of the tree
    minNode = removeFromMin( wkgPtr->rightChildPtr, wkgPtr->rightChildPtr->leftChildPtr );
      
    // copy data into the wkgPtr form minNode
    setTreeNodeData( wkgPtr, *minNode );
      
    // free the minNode
    free(minNode);
    }
      
  // if the right child does not have a left child
  else 
    {      
    // copy the right childs data into the current node
    setTreeNodeData( wkgPtr, *wkgPtr->rightChildPtr );
      
    // set tempPtr to the node that will be freed
    itemToDelete = wkgPtr->rightChildPtr;
      
    // link aroung the right child to remove the node
    wkgPtr->rightChildPtr = itemToDelete->rightChildPtr;
    
    // free memory of node
    free( itemToDelete ); 
    } 
   
  // return parent ptr  
  return wkgPtr;
  }

/*
Name: search
Process: recursively searches for item, if found, returns pointer to node,
         otherwise, returns NULL
Function input/parameters: pointer to working node (TreeNodeType *),
                           node to be found with at least state name key
                           (const TreeNodeType)
Function output/parameters: none
Function output/returned: link to found node, or NULL, as specified
Device input/---: none
Device output/---: none
Dependencies: compareRoomNumbers, search (recursively)
*/
TreeNodeType *search( TreeNodeType *wkgPtr, const TreeNodeType searchData )
  {
  // make sure not NULL
  if( wkgPtr != NULL )
    { 
    // variables 
    int sum; 
    
    // calculate sum
    sum = compareRoomNumbers( searchData.roomNumber, wkgPtr->roomNumber );
    
    // check for search val less than 0
    if( sum < 0 )
      {
      // try left
      return search( wkgPtr->leftChildPtr, searchData ); 	
	  }
  
    // check for val greater than 0
    else if( sum > 0 )
      {
      // try right
      return search( wkgPtr->rightChildPtr, searchData );         
      }
       
    // otherwise assume found item
    return wkgPtr;   
    }
 
  // return NULL
  return NULL;
  }

/*
Name: setTreeNodeData
Process: copies room data from source node to destination pointer
Function input/parameters: node to be copied (TreeNodeType)
Function output/parameters: destination pointer (TreeNodeType *)
Function output/returned: none
Device input/---: none
Device output/---: none
Dependencies: copyString
*/
void setTreeNodeData( TreeNodeType *destPtr, const TreeNodeType source )
  {     
  // copy the values into destPtr
  destPtr->roomCapacity = source.roomCapacity;
  copyString( destPtr->buildingRoom, source.buildingRoom ); 
  copyString( destPtr->classSetup, source.classSetup ); 
  copyString( destPtr->roomNumber, source.roomNumber );
  }
