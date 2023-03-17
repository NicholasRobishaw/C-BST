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
  // variables
  
  // check if index is not NULL CHAR
  if( str[index] != NULL_CHAR )
    {
    // index += next recurse
    return getStringLengthHelper( str, index+1 );
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
  // variables    
  TreeNodeType *tempInData = NULL; 
  setTreeNodeData( tempInData, inData );
  int sum;
      
  // check if data is avaliable
  if( !isEmpty( tempInData ) )
    { 
    // calc sum
    sum = compareRoomNumbers( wkgPtr->roomNumber, inData.roomNumber ); 
    
    // look down        
      
    // check if the inData is less than the current
    if( sum > 0 )
      {   	
      // try left child    
      wkgPtr->leftChildPtr = insert( wkgPtr->leftChildPtr, inData );     // redo we are supposed to change data at this node not make another
      }
  
    // try right
    else if( sum < 0 )
      {
      // try right child
      wkgPtr->rightChildPtr = insert( wkgPtr->rightChildPtr, inData );  // redo we are supposed to change data at this node not make another
      }
  
    // if data is the same
    else if( sum == 0 )
      {	    	
      // other wise  
      // create the new node
      wkgPtr = createTreeNodeFromNode( inData ); 
      
      // set the tree node data
      setTreeNodeData( wkgPtr, inData ); 
      // overwrite it
      }  
        
    //return wkgPtr; 
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
  //test
  printf( "entered remove from min\n" );    
   
  printf( "data being passed in\n parentPte: %s, childPtr: %s\n", parentPtr->roomNumber, childPtr->roomNumber ); 
      
  // variables
  TreeNodeType *minNode = parentPtr;
  
  // search for min node
  // recurse left until hit NULL
  if( childPtr != NULL )
    {
    // try next level
    minNode = removeFromMin( childPtr, childPtr->leftChildPtr );        
    
    }
    
  printf( " Min node to return : %s\n", minNode->roomNumber );  
    
  // if at end return null up  
  return minNode;  
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
  TreeNodeType *tempNode = search( *rootPtr, outData ), *wkgPtr = *rootPtr;
  
  // test
  printf( "finished search\n" );
  printf( "returned node roomNumber: %s\n", tempNode->roomNumber );  
  
  // if the item is avaliable
  if( tempNode != NULL )
    {
    // test
	printf( "temp item is avaliable\n" );	
    	
    // capture it from search pointer
    setTreeNodeData( removedNodePtr, *tempNode );

    // test
    printf( "removed node pt\n" );

    // remove item from tree
    *rootPtr = removeItemHelper( wkgPtr, *tempNode );// was wkgPtr
    
    // test
    printf(  "set the rootPtr\n" );
    
    // return true
    return true;
    }
    
  // test
  //printf( " return false\n" );  
    
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
  // once at the shoppign list set the temp to the current node
  // set wkgPtr to next
  // free the temp
  // fall through other checks
  // return wkgPtr back
      
  // test
  printf( "entered remove item helper\n" );    
      
  // variables
  TreeNodeType *itemToDelete, *temp;
  int sum = compareRoomNumbers( wkgPtr->roomNumber, outData.roomNumber );
  
  // test
  printf( "before check\n" );
  
  // check if at nodes 
  if( sum == 0 )
    {
    // test
    printf( "check passed\n" );    
        
    // set the temp to node to delete
    itemToDelete = wkgPtr; // here might be the probelm since you would delete all you just changed 
     
    printf( "item to Delete: %s\n", itemToDelete->roomNumber );
    
    // for no children
    if( wkgPtr->leftChildPtr == NULL && wkgPtr->rightChildPtr == NULL )
      {
      printf( "no children\n" );    
          
      free(itemToDelete);    
      return NULL;    
      }
    
    // for node with 1 child 
    // check for the current nodes lft child to be NULL
    if( wkgPtr->leftChildPtr == NULL || wkgPtr->rightChildPtr == NULL )
      {
      // test
      printf( " leftchild is NULL\n" );    
      printf( " returning right childs data: %s\n", wkgPtr->rightChildPtr->roomNumber );
       
      if( wkgPtr->rightChildPtr == NULL )
        {
        setTreeNodeData( wkgPtr, *wkgPtr->leftChildPtr );    
        } 
      
      else
        {
        // return right childs reference    
        setTreeNodeData( wkgPtr, *wkgPtr->rightChildPtr );   
        }    
     
      free( itemToDelete ); 
     
      }
      
    
    // removing node with 2 children
    // check that the right child has a left child
    if( wkgPtr->rightChildPtr->leftChildPtr != NULL )
      {
      // test
      printf( " wkgPtr->rightChildPtr->leftChildPtr != NULL\n" );  
          
      // call remove from min, transfer the data from the removed node to the current node
      wkgPtr = removeFromMin( wkgPtr, wkgPtr );
      
      
      // set children
      wkgPtr->leftChildPtr = itemToDelete->leftChildPtr;
      //wkgPtr->rightChildPtr = itemToDelete->rightChildPtr;
      
      wkgPtr->rightChildPtr = itemToDelete->rightChildPtr;
      
      printf( "wkgPtr = %s, wkgPtr->left = %s,wkgPtr->right = %s \n", wkgPtr->roomNumber, wkgPtr->leftChildPtr->roomNumber, wkgPtr->rightChildPtr->roomNumber );
      printf( "ItemToDelete = %s, ItemToDelete->left = %s, itemToDelete->right = %s\n", itemToDelete->roomNumber, itemToDelete->leftChildPtr->roomNumber, itemToDelete->rightChildPtr->roomNumber );
      
      //wkgPtr->rightChildPtr = removeItemHelper( wkgPtr, *itemToDelete );// aregument 1 was wkgPtr->right
      
      printf( "wkgPtr set to value from removeFromMin\n " );
      }
      
    // if the right child does not have a left child
    if( wkgPtr->rightChildPtr->leftChildPtr == NULL )
      {
      // test
      printf( " wkgPtr->rightChildPtr->leftChildPtr == NULL\n" );      
          
      // copy the left childs data into the current node
      //setTreeNodeData( wkgPtr, *wkgPtr->leftChildPtr );
      wkgPtr = wkgPtr->leftChildPtr;
      
      // test to show new node
      printf( " overwritten with %s\n", wkgPtr->roomNumber );
      
      temp = wkgPtr->rightChildPtr;
      
      printf( "temp is holding %s\n", temp->roomNumber );
      
      // relink right side of list
      wkgPtr->rightChildPtr = itemToDelete->rightChildPtr;
      
      wkgPtr->leftChildPtr->rightChildPtr = temp;
      
      // call again for left child
      //wkgPtr->leftChildPtr = removeItemHelper( wkgPtr->leftChildPtr, *wkgPtr->leftChildPtr );
      //wkgPtr->
      } 
    
    
    printf( "after tests in remove helper, freeing node\n" );  
    // free the deleted node
    //free( itemToDelete );  
         
    }
  
  else
    {
    // try left    
    if( sum > 0 )
      {
       wkgPtr->leftChildPtr = removeItemHelper( wkgPtr->leftChildPtr, outData );
      }
   
    if( sum < 0 )
      {
      // try right
      wkgPtr->rightChildPtr = removeItemHelper( wkgPtr->rightChildPtr, outData );  
      }
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
  //variables
  int sum = compareRoomNumbers( wkgPtr->roomNumber , searchData.roomNumber );
  
  //testing
  printf( "sum = %s - %s\n", wkgPtr->roomNumber , searchData.roomNumber );
  printf( "sum in search: %d\n", sum );
  
  // make sure not NULL
  if( wkgPtr != NULL )
    {  
    // check for search val less than 0
    if( sum < 0 )
      {
      // try right
      wkgPtr = search( wkgPtr->rightChildPtr, searchData ); 	
	  }
  
    // check for val greater than 0
    if( sum > 0 )
      {
      // try left
      wkgPtr = search( wkgPtr->leftChildPtr, searchData );         
      }
  
    /*
    // check if item is found
    if( sum == 0 )
      {
      // testing
      printf( "Item Found\n" );   
             
      // return the node pointer
      return wkgPtr;
      }    
    */ 
      
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
