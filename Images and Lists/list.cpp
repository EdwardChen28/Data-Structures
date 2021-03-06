/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
   //clear();  /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{	
	ListNode * temp;
	while(head->next!=NULL){
		temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
	head=NULL;
		
	
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
	if(head==NULL) {
		head = new ListNode(ndata);
		tail = head;
	}
	else{
	ListNode * temp = new ListNode(ndata);
	temp->next=head;
	head->prev = temp;
	head = temp;
	temp=NULL;
	}
	length++;
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
	if(head == NULL ||tail == NULL){
		tail = new ListNode(ndata);
		head=tail;
	}
	else{
		tail->next = new ListNode(ndata);
		tail->next->prev = tail;
		tail = tail->next;
	}
	length++;
	
	
    /// @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
	//ListNode* s = head->next;
	//ListNode* e = tail->prev;
	
    reverse(head,tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
	if(startPoint == endPoint)
		return;

	ListNode * startPointPrev = startPoint->prev;
	ListNode *endPointNext = endPoint->next;
		
	ListNode * temp, * curr;
	curr = startPoint;

	while( curr != endPoint){
		temp = curr->next;
		curr->next = curr->prev;
		curr->prev = temp;
		curr = temp;		
	}

	curr->next = curr->prev;
	if(endPointNext !=NULL) {
		endPointNext-> prev = startPoint;
	}	
	startPoint->next =endPointNext;

	if(startPointPrev != NULL) {
		startPointPrev->next = curr;
	}
	curr->prev = startPointPrev;
	
	endPoint = startPoint;
	startPoint = curr;
	
    /// @todo Graded in MP3.1
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
 
template <class T>
void List<T>::reverseNth( int n )
{	
	if(n == length){
		reverse(head,tail);
		return;
	}
	
	int count = 1;
	ListNode * startpoint, *endpoint;
	startpoint = head;
	endpoint = head;
	
	while( count < length ){
	
		if( count % n != 0){
			endpoint= endpoint -> next;
			count++;
		}
		else{
		reverse(startpoint, endpoint);
		if(count == n) head = startpoint;
		startpoint = endpoint->next;
		endpoint = endpoint->next;
		count++;
		}
		
	}
	reverse(startpoint, endpoint);	
	tail = endpoint;
	
	
	
    /// @todo Graded in MP3.1
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{        
	if ( length < 3) return; 
	ListNode *curr = head;
	ListNode *ptemp = NULL;
	ListNode *ntemp = NULL;                          
	while(curr->next != tail && curr->next!=NULL){
		curr = curr->next;
		ptemp = curr->prev;
		ntemp = curr->next;	
		tail->next = curr;
		curr->prev = tail;
		curr->next = NULL;
		ptemp->next=ntemp;
		ntemp->prev = ptemp;	
		tail = tail->next;
		curr=ntemp;		
	}
	
    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{	
	ListNode *secondHead = start;
	while(splitPoint != 0){
		secondHead = secondHead->next;
		splitPoint--;
	}
	//tail = secondHead->prev;
	secondHead->prev->next = NULL;
	secondHead->prev = NULL;
	
	//tail = secondHead->prev;
	//tail->next = NULL;
	//secondHead->prev = NULL;
    /// @todo Graded in MP3.2
    return secondHead; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
	
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{	
	
	ListNode * result = forwardMerge( first, second);
	result->prev = NULL;
	first = result;
	second= result->next;
	while(second->next!= NULL){
		second->prev = first;
		first = second;
		second = second->next;
	}
		second->prev = first;
		first = NULL;
		second = NULL;
		return result;
		
}

template <class T>
typename List<T>::ListNode * List<T>::forwardMerge(ListNode* first, ListNode * second)
{
	ListNode * result = NULL;
	if(first == NULL) {
		second->prev = result;
		
		return second;
	}	
	else if( second == NULL) {
		first->prev = result;
		return first;
	}
		
	if(first->data < second->data){
		result = first;
		result->next = forwardMerge(first->next, second);
		result->next->prev = result;
	}
	else{
		result = second;
		result->next=forwardMerge(first , second->next);
		result->next->prev = result;
	}
	
	return result;
}


/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
	if(chainLength <=1)
	return start;
	//ListNode* firstHalf = start;
	ListNode * secondHalf = split( start, chainLength/2);
	start= mergesort(start , chainLength/2);
	secondHalf = mergesort(secondHalf, chainLength - (chainLength/2));
	return merge(start, secondHalf);
	
	
    /// @todo Graded in MP3.2
    // change me!
}
