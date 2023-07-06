#
#	Algorithms.py 
#
#   Version 1.1
#	February 2021
#
#	Subroutines for Data Structures and Algorithms
#	Copyright@ Yuan-Hsiang Chang, Ph.D.
#	Department of Information & Computer Engineering
#	Chung Yuan Christian University
#
# 	-----------------------------------------------------------------------------------------
#   Instructions
#   -----------------------------------------------------------------------------------------
#   1. All subroutines were either implemented or collected from the given references.
#   2. The subroutines were originally tested using Python 3.7.
#	3. All subroutines may contain bugs, therefore still subject to further revision.
#   4. If you have any suggestions or would like to make contributions, please let me know.
#
#   -----------------------------------------------------------------------------------------
#   References
#   -----------------------------------------------------------------------------------------
#   Introduction to Algorithms, 3rd Edition(Cormen)
#   Fundamentals of Data Structures in C++(Horowitz)
#   名題精選百則使用C語言(冼鏡光)
#	Data Structure and Algorithmic Thinking with Python(Karumanchi)
#   資料結構使用C++(蔡明志)
#   資料結構使用Python(蔡明志)
#

#####################################################################################
#
#	Fundamental Algorithms
#	
#####################################################################################
#
#	Subsets (Combinations)
#   List the subsets of A using a n-bit counter.
#	There are 2**n possible subsets.
#	
def Subsets( A ):
	n = len( A )
	for i in range( 0, 2**n ):
		count = format( i, 'b' ).zfill( n )
		
		print( "{", end = " " )
		for j in range( 0, n ):
			if ( count[n - j -1] != '0' ):
				print( A[j], end = " " )
		print( "}" )
			

#
#	k-Subsets (k-Combinations)
#   List the k-subsets of A.
#	There are C(n,k) possible k-subsets.
#
#	Reference: 名題精選百則使用C語言 (冼鏡光)
#
def k_Subsets( A, k ):
	n = len( A )
	S = [0] * n

	for i in range( k ):
		S[i] = i + 1

	print( "{", end = " " )
	print( A[S[0] - 1], end = " " )
	for j in range( 1, k ):
		print( A[S[j] - 1], end = " " )
	print( "}" )	

	position = k - 1
	while ( 1 ):
		if ( S[k - 1] == n ):
			position -= 1
		else:
			position = k - 1
		S[position] += 1
		for i in range( position + 1, k ):
			S[i] = S[i - 1] + 1

		print( "{", A[S[0] - 1], end = " " )
		for j in range( 1, k ):
			print( A[S[j] - 1 ], end = " " )
		print( "}" )

		if ( S[0] >= n - k + 1 ):
			break


#
#	Permutations
#	List the permutations of A in lexical order.
#	There are n! permutations.
#			
def Permutations( A ):
	n = len( A )
	_Permutations( A, 0, n )


def _Permutations( A, i, n ):
	if i < n:
		for j in range( i, n ):
			temp = A[j]
			for k in range( j, i, -1 ):
				A[k] = A[k - 1]
			A[i] = temp
			
			_Permutations( A, i + 1, n )
			
			for k in range( i, j ):
				A[k] = A[k + 1]
			A[j] = temp
	else:
		for j in range( 0, n ):
			print( A[j], end = " " )
		print()	
	

#
#	Factorials
#	Compute the Factorials n!
#
def Factorial( n ):
	if n <= 1:
		return 1
	else:
		return n * Factorial( n - 1 )

		
def Factorial_Iter( n ):
	if n <= 1:
		return 1
	else:
		ans = 1
		for i in range( 2, n + 1 ):
			ans *= i
		return ans

		
#
#	Fibonacci Numbers
#	Compute the nth Fibonacci Numbers
#	F(n) = F(n-1) + F(n-2)
#
def Fib( n ):
	if n == 0:
		return 0
	elif n == 1:
		return 1
	else:
		return Fib( n - 1 ) + Fib( n - 2 )


def Fib_Iter( n ):
	if n == 0:
		return 0
	elif n == 1:
		return 1
	else:
		f0 = 1
		f1 = 1
		for i in range( 2, n + 1 ):
			temp = f0 + f1		
			f0 = f1
			f1 = temp
		return temp

		
#
#	Catalan Numbers
#	Compute the nth Catalan Numbers.
#
def Catalan( n ):
	if n == 0:
		return 1
	else:
		c = 0
		for k in range( 0, n ):
			c += ( Catalan( k ) * Catalan( n - 1 - k ) )
	return c


def Catalan_Iter( n ):
	if n == 0 or n == 1:
		return 1
	else:
		c = []
		for i in range( 0, n + 1 ):
			c.append( 0 )
		
		c[0] = c[1] = 1
		for i in range( 2, n + 1 ):
			c[i] = 0
			for k in range( 0, i ):
				c[i] += c[k] * c[i - 1 - k]
		return c[n]
	
	
#
#  	Binomial Coefficients
# 	Compute the Binomial Coefficients C(n,k)
#
def Cnk( n, k ):
	if k == 0 or n == k:
		return 1
	else:
		return Cnk( n - 1, k ) + Cnk( n - 1, k - 1 )

		
#
#  Pascal Triangle
#
def Pascal_Triangle( n ):
	for n1 in range( 1, n ):
		for k in range( 0, n1 + 1 ):
			print( format( Cnk( n1, k ), "4d" ), end = "" )
		print( )


#####################################################################################
#
#	Recursive Algorithms (Divide & Conquer)
#	
#####################################################################################			
#
#	Tower of Hanoi
#	Solving the Tower of Hanoi problem.
#
#	Input:  a = 'A', b = 'B', c = 'C', n: number of disks
#	Output: Procedures of moving the disks
#
def Hanoi_Tower( a, b, c, n ):
	if n == 1:
		print( "Move disk from", a, "to", c )
	else:
		Hanoi_Tower( a, c, b, n - 1 )	
		Hanoi_Tower( a, b, c, 1 )
		Hanoi_Tower( b, a, c, n - 1 )


#
#	Maximum-Subarray Problem
#	Find the maximum-subarray.
#
def Find_Maximum_Subarray( A ):
	n = len( A )
	low, high, sum = _Find_Maximum_Subarray( A, 0, n - 1 )
	
	print( "Maximum-Subarray Problem:" )
	print( "Low =", low, "High =", high, "Sum =", sum )


def _Find_Maximum_Subarray( A, low, high ):
	if high == low:
		return low, high, A[low]
	else:
		mid = ( low + high ) // 2 
		
		left_low, left_high, left_sum    = _Find_Maximum_Subarray( A, low, mid )
		right_low, right_high, right_sum = _Find_Maximum_Subarray( A, mid + 1, high )		
		cross_low, cross_high, cross_sum = _Find_Max_Crossing_Subarray( A, low, mid, high )
		
		if ( left_sum > right_sum and left_sum >= cross_sum ):
			return left_low, left_high, left_sum
		elif ( right_sum >= left_sum and right_sum >= cross_sum ):
			return right_low, right_high, right_sum
		else:
			return cross_low, cross_high, cross_sum


def _Find_Max_Crossing_Subarray( A, low, mid, high ):
	left_sum = -3000000
	sum = 0
	for i in range( mid, low - 1, -1 ):
		sum += A[i]
		if sum > left_sum:
			left_sum = sum		
			max_left = i
		
	right_sum = -3000000
	sum = 0
	for j in range( mid + 1, high + 1 ):
		sum += A[j]
		if sum > right_sum:
			right_sum = sum	
			max_right = j
	
	cross_low  = max_left
	cross_high = max_right
	cross_sum  = left_sum + right_sum
	
	return cross_low, cross_high, cross_sum


#####################################################################################
#
#	Data Structures
#	
#####################################################################################
#
#	Singly Linked List
#
#	Operations:
#	  Seach      (Search for a key)
#	  Insert     (Insert to the head of Linked List)
#	  Delete     (Delete from the head of Linked List)
#	  InsertTail (Insert to the tail of Linked List)
#	  DeleteTail (Delete from the tail of Linked List)
#	  Display    (Display the Linked List)
#
class SLLNode:

	def __init__( self ):
		self.key  = None
		self.next = None


class SinglyLinkedList:

	def __init__( self, head = None ):
		self.head = SLLNode()
		self.next = None
		self.length = 0

	def Search( self, key ):
		current = self.head.next
		while ( current ):
			if ( current.key == key ):
				return True
			else:
				current = current.next
		return False

	def Insert( self, key ):
		newNode = SLLNode()
		newNode.key = key
		newNode.next = self.head.next
		self.head.next = newNode
		self.length += 1

	def Delete( self ):
		if ( self.length == 0 ):
			print( "No keys in singly linked list" )	
		else:
			current = self.head.next
			self.head.next = current.next
			self.length -= 1	

	def InsertTail( self, key ):
		newNode = SLLNode()
		newNode.key = key
		newNode.next = None

		if ( self.head.next == None ):
			self.head.next = newNode
		else:
			current = self.head.next
			while ( current.next ):
				current = current.next
			current.next = 	newNode		

		self.length += 1	

	def DeleteTail( self ):
		if ( self.length == 0 ):
			print( "No keys in singly linked list." )
		else:
			prev = self.head
			current = self.head.next
			while ( current.next ):
				prev = current
				current = current.next
			prev.next = None
			self.length -= 1

	def Display( self ):
		if ( self.length == 0 ):
			print( "No keys in singly linked list." )
		else:
			print( "Singly Linked List:" )
			current = self.head.next
			while( current ):
				print( current.key, end = " " )
				current = current.next
			print( )	


#
#	Doubly Linked List
#
#	Operations:
#	  Seach      (Search for a key)
#	  Insert     (Insert to the head of Linked List)
#	  Delete     (Delete from the head of Linked List)
#	  InsertTail (Insert to the tail of Linked List)
#	  DeleteTail (Delete from the tail of Linked List)
#	  Display    (Display the Linked List)
#
class DLLNode:

	def __init__( self ):
		self.key   = None
		self.left  = None
		self.right = None


class DoublyLinkedList:

	def __init__( self, head = None ):
		self.head = DLLNode()
		self.head.left = self.head
		self.head.right = self.head
		self.length = 0

	def Search( self, key ):
		current = self.head.right
		while ( current != self.head ):
			if ( current.key == key ):
				return True
			else:
				current = current.right
		return False

	def Insert( self, key ):
		ptr = DLLNode()
		ptr.key = key

		current = self.head.right
		current.left = ptr

		ptr.left = self.head
		ptr.right = current
		self.head.right = ptr

		self.length += 1

	def Delete( self ):
		if ( self.length == 0 ):
			print( "No keys in doubly linked list." )
		else:
			current = self.head.right
			self.head.right = current.right
			current.right.left = current.left
			self.length -= 1			

	def InsertTail( self, key ):
		ptr = DLLNode()
		ptr.key = key

		prev = self.head
		current = self.head.right
		while ( current != self.head ):
			prev = current
			current = current.right
		current.left = ptr

		ptr.left = prev
		ptr.right = current
		prev.right = ptr

		self.length += 1		

	def DeleteTail( self ):
		if ( self.length == 0 ):
			print( "No keys in doubly linked list." )
		else:
			prev = self.head.right
			current = self.head.right
			while ( current != self.head ):
				prev = current
				current = current.right
			prev.left.right = self.head
			self.length -= 1			

	def Display( self ):
		if ( self.length == 0 ):
			print( "No keys in doubly linked list." )	
		else:
			print( "Doubly Linked List:" )
			current = self.head.right
			while ( current != self.head ):
				print( current.key, end = " " )
				current = current.right
			print()


#
#	Stack
#
#	Operations:
#	  isEmpty (Check if the stack is empty)
#	  Push    (Push to the stack)
#	  Pop     (Pop from the stack)
#	  Display (Display the stack)
#
class Stack:
	
	def __init__( self ):
		self.S = []

	def isEmpty( self ):
		return ( self.S == [] )

	def Push( self, key ):
		self.S.append( key )

	def Pop( self ):
		if ( self.isEmpty() ):
			print( "Underflow" )
			return None
		else:
			return self.S.pop()

	def Display( self ):
		print( "Stack:", end = "" )
		print( self.S )	


#
#	Queue
#
#	Operations:
#	  isEmpty (Check if the Queue is empty)
#	  Enqueue (Enqueue to the Queue)
#	  Dequeue (Dequeue from the Queue)
#	  Display (Display the Queue)
#
class Queue:
	
	def __init__( self ):
		self.Q = []

	def isEmpty( self ):
		return ( self.Q == [] )

	def Enqueue( self, key ):
		self.Q.append( key )

	def Dequeue( self ):
		if ( self.isEmpty() ):
			print( "Underflow" )
			return None
		else:
			return self.Q.pop( 0 )

	def Display( self ):
		print( "Queue:", end = "" )
		print( self.Q )


#
#	Binary Search Tree
#
#	Operations:
#	  Insert    (Insert to the binary search tree)
#	  Delete    (Delete from the binary search tree)
#	  Preorder  (Preorder traversal)
#	  Inorder   (Inorder traversal)
#	  Postorder (Postorder traversal)
#
class BSTNode:

	def __init__( self ):
		self.key   = None
		self.left  = None
		self.right = None


class BinarySearchTree:

	def __init__( self ):
		self.root = None
		self.n = 0

	def Insert( self, key ):
		ptr = BSTNode()
		ptr.key = key
		ptr.left = None
		ptr.right = None

		if ( self.root == None ):
			self.root = ptr
		else:
			parent = None
			current = self.root
			while ( current != None ):
				parent = current
				if ( key < current.key ):
					current = current.left
				else:
					current = current.right
			if ( key < parent.key ):
				parent.left = ptr
			else:
				parent.right = ptr
		self.n += 1

	def Delete( self, key ):
		parent = None
		current = self.root	
		while ( current != None ):			
			if ( key == current.key ):
				break
			parent = current
			if ( key < current.key ):
				current = current.left
			else:
				current = current.right

		if ( current == None ):
			print( "Deleted node is not found." )
		else:
			if ( current.left == None and current.right == None ):  # Leaf node
				if ( current == self.root ):
					self.root = None
				else:
					if ( current.key < parent.key ):
						parent.left = None
					else:
						parent.right = None
			elif ( current.left != None and current.right == None ):  # Left subtree is not empty
				if ( current == self.root ):
					self.root = current.left
				else:
					if ( current.key < parent.key ):
						parent.left = current.left
					else:
						parent.right = current.left
			elif ( current.left == None and current.right != None ):  # Right subtree is not empty
				if ( current == self.root ):
					self.root = current.right
				else:
					if ( current.key < parent.key ):
						parent.left = current.right
					else:
						parent.right = current.right
			else:                                        # Both left & right subtrees are not empty
				prev = current
				ptr = current.right
				while ( ptr.left != None ):
					prev = ptr
					ptr = ptr.left

				if ( ptr.key < prev.key ):
					prev.left = ptr.right
				else:
					prev.right = ptr.right

				current.key = ptr.key

			self.n -= 1				

	def Preorder( self ):
		if ( self.root == None ):
			print( "No keys in the binary search tree." )
		else:
			print( "Binary Search Tree (Preoder):" )
			self._Preorder( self.root )
			print()

	def _Preorder( self, ptr ):
		if ( ptr != None ):
			print( ptr.key, end = " " )
			self._Preorder( ptr.left )	
			self._Preorder( ptr.right )

	def Inorder( self ):
		if ( self.root == None ):
			print( "No keys in the binary search tree." )
		else:
			print( "Binary Search Tree (Inorder):" )
			self._Inorder( self.root )
			print()

	def _Inorder( self, ptr ):
		if ( ptr != None ):
			self._Inorder( ptr.left )
			print( ptr.key, end = " " )
			self._Inorder( ptr.right )
	
	def Postorder( self ):
		if ( self.root == None ):
			print( "No keys in the binary search tree." )
		else:
			print( "Binary Search Tree (Postorder):" )
			self._Postorder( self.root )
			print()

	def _Postorder( self, ptr ):
		if ( ptr != None ):
			self._Postorder( ptr.left )
			self._Postorder( ptr.right )
			print( ptr.key, end = " " )


#
#	Minimum Priority Queue
#
#	Operations:
#	  Insert      (Insert to the priority queue)
#	  Minimum     (Minimum of priority queue)
#	  Extract_Min (Extract minimum from the priority queue)
#	  Display     (Display the priority queue)
#
class MinPriorityQueue:

	def __init__( self ):
		self.Q = []
		self.heap_size = 0

	def Insert( self, key ):
		if ( self.heap_size == 0 ):
			self.Q.append( key )
			self.heap_size += 1		
		else:
			self.Q.append( key )
			i = self.heap_size
			j = ( i - 1 ) // 2
			while ( i != 0 ):
				if ( self.Q[i] < self.Q[j] ):
					self.Q[i], self.Q[j] = self.Q[j], self.Q[i]
					i = j
					j = ( i - 1 ) // 2
				else:
					break	
			self.heap_size += 1
	
	def Minimum( self ):
		return self.Q[0]

	def Extract_Min( self ):
		if ( self.heap_size == 0 ):
			print( "Underflow" )
			return None
		else:
			min = self.Q[0]
			self.Q[0] = self.Q[self.heap_size - 1]
			self.heap_size -= 1

			self.Min_Heapify( self.Q, 0, self.heap_size )
			self.Q.pop()			
			return min

	def Min_Heapify( self, A, i, heap_size ):
		l = 2 * i + 1
		r = 2 * i + 2
		if ( l < heap_size and A[l] < A[i] ):
			smallest = l
		else:
			smallest = i
		if ( r < heap_size and A[r] < A[smallest] ):
			smallest = r

		if ( smallest != i ):
			A[i], A[smallest] = A[smallest], A[i]
			self.Min_Heapify( A, smallest, heap_size )
			
	def Display( self ):
		if ( self.heap_size == 0 ):
			print( "No keys in minimum priority queue." )
		else:
			print( "Minimum Priority Queue:", end = "" )
			print( self.Q )


#
#	Maximum Priority Queue
#
#	Operations:
#	  Insert      (Insert to the priority queue)
#	  Maximum     (Maximum of priority queue)
#	  Extract_Max (Extract Maximum from the priority queue)
#	  Display     (Display the priority queue)
#
class MaxPriorityQueue:

	def __init__( self ):
		self.Q = []
		self.heap_size = 0

	def Insert( self, key ):
		if ( self.heap_size == 0 ):
			self.Q.append( key )
			self.heap_size += 1		
		else:
			self.Q.append( key )
			i = self.heap_size
			j = ( i - 1 ) // 2
			while ( i != 0 ):
				if ( self.Q[i] > self.Q[j] ):
					self.Q[i], self.Q[j] = self.Q[j], self.Q[i]
					i = j
					j = ( i - 1 ) // 2
				else:
					break	
			self.heap_size += 1
	
	def Maximum( self ):
		return self.Q[0]

	def Extract_Max( self ):
		if ( self.heap_size == 0 ):
			print( "Underflow" )
			return None
		else:
			max = self.Q[0]
			self.Q[0] = self.Q[self.heap_size - 1]
			self.heap_size -= 1

			self.Max_Heapify( self.Q, 0, self.heap_size )
			self.Q.pop()
			return max

	def Max_Heapify( self, A, i, heap_size ):
		l = 2 * i + 1
		r = 2 * i + 2
		if ( l < heap_size and A[l] > A[i] ):
			largest = l
		else:
			largest = i
		if ( r < heap_size and A[r] > A[largest] ):
			largest = r

		if ( largest != i ):
			A[i], A[largest] = A[largest], A[i]
			self.Max_Heapify( A, largest, heap_size )
			
	def Display( self ):
		if ( self.heap_size == 0 ):
			print( "No keys in maximum priority queue" )
		else:
			print( "Maximum Priority Queue:", end = "" )
			print( self.Q )


#
#	Fibonacci Heap
#
#	Operations:
#	  Insert      (Insert to the Fibonacci Heap)
#	  Extract_Min (Extract Minimum from the Fibonacci Heap)
#	  Merge       (Merge two Fibonacci Heaps)
#
class FibonacciHeap:

	# internal node class
	class Node:
		def __init__( self, key, value ):
			self.key = key
			self.value = value
			self.parent = self.child = self.left = self.right = None
			self.degree = 0
			self.mark = False

	# function to iterate through a doubly linked list
	def iterate( self, head ):
		node = stop = head
		flag = False
		while True:
			if node == stop and flag is True:
				break
			elif node == stop:
				flag = True
			yield node
			node = node.right

	# pointer to the head and minimum node in the root list
	root_list, min_node = None, None

	# maintain total node count in full fibonacci heap
	total_nodes = 0

	# return min node in O(1) time
	def find_min( self ):
		return self.min_node

	# extract (delete) the min node from the heap in O(log n) time
	def extract_min( self ):
		z = self.min_node
		if z is not None:
			if z.child is not None:
				# attach child nodes to root list
				children = [x for x in self.iterate(z.child)]
				for i in range( 0, len(children) ):
					self.merge_with_root_list(children[i])
					children[i].parent = None
			self.remove_from_root_list(z)
			# set new min node in heap
			if z == z.right:
				self.min_node = self.root_list = None
			else:
				self.min_node = z.right
				self.consolidate()
			self.total_nodes -= 1
		return z

	# insert new node into the unordered root list in O(1) time
	# returns the node so that it can be used for decrease_key later
	def insert( self, key, value=None ):
		n = self.Node(key, value)
		n.left = n.right = n
		self.merge_with_root_list(n)
		if self.min_node is None or n.key < self.min_node.key:
			self.min_node = n
		self.total_nodes += 1
		return n

	# modify the key of some node in the heap in O(1) time
	def decrease_key( self, x, k ):
		if k > x.key:
			return None
		x.key = k
		y = x.parent
		if y is not None and x.key < y.key:
			self.cut(x, y)
			self.cascading_cut(y)
		if x.key < self.min_node.key:
			self.min_node = x

	# merge two fibonacci heaps in O(1) time by concatenating the root lists
	# the root of the new root list becomes equal to the first list and the second
	# list is simply appended to the end (then the proper min node is determined)
	def merge( self, h2 ):
		H = FibonacciHeap()
		H.root_list, H.min_node = self.root_list, self.min_node
		# fix pointers when merging the two heaps
		last = h2.root_list.left
		h2.root_list.left = H.root_list.left
		H.root_list.left.right = h2.root_list
		H.root_list.left = last
		H.root_list.left.right = H.root_list
		# update min node if needed
		if h2.min_node.key < H.min_node.key:
			H.min_node = h2.min_node
		# update total nodes
		H.total_nodes = self.total_nodes + h2.total_nodes
		return H

	# if a child node becomes smaller than its parent node we
	# cut this child node off and bring it up to the root list
	def cut( self, x, y ):
		self.remove_from_child_list(y, x)
		y.degree -= 1
		self.merge_with_root_list(x)
		x.parent = None
		x.mark = False

	# cascading cut of parent node to obtain good time bounds
	def cascading_cut( self, y ):
		z = y.parent
		if z is not None:
			if y.mark is False:
				 y.mark = True
			else:
				self.cut(y, z)
				self.cascading_cut(z)

	# combine root nodes of equal degree to consolidate the heap
	# by creating a list of unordered binomial trees
	def consolidate( self ):
		A = [None] * self.total_nodes
		nodes = [w for w in self.iterate(self.root_list)]
		for w in range(0, len(nodes)):
			x = nodes[w]
			d = x.degree
			while A[d] != None:
				y = A[d]
				if x.key > y.key:
					temp = x
					x, y = y, temp
				self.heap_link(y, x)
				A[d] = None
				d += 1
			A[d] = x
        
		# find new min node - no need to reconstruct new root list below
		# because root list was iteratively changing as we were moving
		# nodes around in the above loop
		for i in range( 0, len(A) ):
			if A[i] is not None:
				if A[i].key < self.min_node.key:
					self.min_node = A[i]

	# actual linking of one node to another in the root list
	# while also updating the child linked list
	def heap_link( self, y, x ):
		self.remove_from_root_list(y)
		y.left = y.right = y
		self.merge_with_child_list(x, y)
		x.degree += 1
		y.parent = x
		y.mark = False

	# merge a node with the doubly linked root list
	def merge_with_root_list( self, node ):
		if self.root_list is None:
			self.root_list = node
		else:
			node.right = self.root_list.right
			node.left = self.root_list
			self.root_list.right.left = node
			self.root_list.right = node

	# merge a node with the doubly linked child list of a root node
	def merge_with_child_list( self, parent, node ):
		if parent.child is None:
			parent.child = node
		else:
			node.right = parent.child.right
			node.left = parent.child
			parent.child.right.left = node
			parent.child.right = node

	# remove a node from the doubly linked root list
	def remove_from_root_list( self, node ):
		if node == self.root_list:
			self.root_list = node.right
		node.left.right = node.right
		node.right.left = node.left

	# remove a node from the doubly linked child list
	def remove_from_child_list( self, parent, node ):
		if parent.child == parent.child.right:
			parent.child = None
		elif parent.child == node:
			parent.child = node.right
			node.right.parent = parent
		node.left.right = node.right
		node.right.left = node.left


#
#	Disadjoint Set
#
#	Operations:
#	  Find    (Find the representative of a key)
#	  Union   (Union of two keys)
#	  Display (Display the disjoint sets)
#
class DisjointSets:

	def __init__( self, n ):
		self.set = [0 for i in range( n + 1 )]
		self.set_size = n

	def Find( self, key ):
		if ( self.set[key] == 0 ):
			return key
		else:
			return self.Find( self.set[key] )	

	def Union( self, a, b ):
		if ( self.Find( a ) == self.Find( b ) ):
			if ( a < b ):
				self.set[b] = a
			else:
				self.set[a] = b
		else:
			if ( self.Find( a ) < self.Find( b ) ):		
				self.set[b] = a
			else:
				self.set[a] = b	

	def Display( self ):
		print( "Disjoint Sets:" )
		for i in range( 1, self.set_size + 1 ):
			if ( self.set[i] == 0 ):
				print( "{", end = "" )
				print( i, end = "" )
				for j in range( i + 1, self.set_size + 1 ):
					if ( self.Find( j ) == i ):
						print( ",", end = "" )
						print( j, end = "" )
				print( "}", end = "" )
		print()


#
#	Hash Table
#
#	Method = 1  Linear Probing
#	       = 2  Quadratic Probing
#	       = 3  Double Hashing
#
#	Operations:
#	  Search  (Search for a key)
#	  Insert  (Insert to the hash table)
#	  Display (Display the hash table)
#
class HashTable:

	def __init__( self, n ):
		self.table = [ None ] * n
		self.table_size = n	
		self.method = 1

	def setMethod( self, method ):
		self.method = method

	def hash_function( self, key, i ):
		h1 = key % self.table_size

		# Linear Probing	
		if ( self.method == 1 ):		
			j = ( h1 + i ) % self.table_size

		# Quadratic Probing	
		elif ( self.method == 2 ):
			j = ( h1 + i * i ) % self.table_size

		# Double Hashing	
		else:
			h2 = 1 + key % ( self.table_size - 1 )
			j = ( h1 + i * h2 ) % self.table_size
		
		return j

	def Search( self, key ):
		flag = True
		i = 0
		while( flag ):
			j = self.hash_function( key, i )

			if ( self.table[j] == key ):
				return j
			else:
				if ( self.table[j] == None ):
					return None
				else:
					i += 1
					if ( i == self.table_size ):
						return None	

	def Insert( self, key ):
		flag = True
		i = 0
		while ( flag ):
			j = self.hash_function( key, i )

			if ( self.table[j] == None ):
				self.table[j] = key
				flag = False
			else:
				i += 1
				if ( i == self.table_size ):
					print( "Hash Table Overflow" )
					flag = False

	def Display( self ):
		print( "Hash Table:" )
		for i in range( self.table_size ):
			print( i, self.table[i] )


#####################################################################################
#
#	Sorting Algorithms
#	
#####################################################################################	
#
#	Bubble Sort
#
def BubbleSort( A ):
	n = len( A )
	for i in range( 0, n - 1 ):
		for j in range( i + 1, n ):
			if A[i] > A[j]:
				A[i], A[j] = A[j], A[i]


#
#	Selection Sort
#
def SelectionSort( A ):
	n = len( A )
	for i in range( 0, n ):
		j = i
		for k in range( i + 1, n ):
			if A[k] < A[j]:
				j = k
		A[i], A[j] = A[j], A[i]
	

#
#	Insertion Sort
#
def InsertionSort( A ):
	n = len( A )
	for j in range( 1, n ):
		key = A[j]
		i = j - 1
		while i >= 0 and A[i] > key:
			A[i + 1] = A[i]
			i -= 1
		A[i + 1] = key

		
#
#	Shell Sort
#
def ShellSort( A ):
	n = len( A )
	inc = n // 2
	while inc > 0:
		for i in range( inc, n ):
			j = i
			temp = A[i]
			while j >= inc and A[j - inc] > temp:
				A[j] = A[j - inc]
				j = j - inc
			A[j] = temp
		inc = int( inc / 2 )


#
#	Merge Sort
#
def MergeSort( A ):
	n = len( A )
	_MergeSort( A, 0, n - 1 )


def _MergeSort( A, p, r ):
	if p < r:
		q = ( p + r ) // 2
		_MergeSort( A, p, q )
		_MergeSort( A, q + 1, r )
		Merge( A, p, q, r )


def Merge( A, p, q, r ):
	n1 = q - p + 1
	n2 = r - q
	
	L = []
	R = []
	for i in range( n1 ):
		L.append( A[p + i] )
		
	for j in range( n2 ):
		R.append( A[q + j + 1] )
		
	i = j = 0
	for k in range( p, r + 1 ):
		if i < n1 and j < n2:
			if L[i] <= R[j]:
				A[k] = L[i]
				i += 1
			else:
				A[k] = R[j]
				j += 1
		elif i < n1 and j >= n2:
			A[k] = L[i]
			i += 1
		else:
			A[k] = R[j]
			j += 1


#
#	Heap Sort
#
def HeapSort( A ):
	n = len( A )
	Build_Max_Heap( A, n )
	heap_size = n
	for i in range( n - 1, -1, -1 ):
		A[0], A[i] = A[i], A[0]
		heap_size -= 1
		Max_Heapify( A, 0, heap_size)


def Build_Max_Heap( A, n ):
	heap_size = n
	for i in range( int(n / 2 - 1), -1, -1 ):
		Max_Heapify( A, i, heap_size )


def Max_Heapify( A, i, heap_size ):
	l = 2 * i + 1
	r = 2 * i + 2
	if l < heap_size and A[l] > A[i]:
		largest = l
	else:
		largest = i
	
	if r < heap_size and A[r] > A[largest]:
		largest = r
	
	if largest != i:
		A[i], A[largest] = A[largest], A[i]
		Max_Heapify( A, largest, heap_size )


#
#	Quick Sort
#
def QuickSort( A ):
	n = len( A )
	_QuickSort( A, 0, n - 1 )


def _QuickSort( A, p, r ):
	if p < r:
		q = Partition( A, p, r )
		_QuickSort( A, p, q - 1 )
		_QuickSort( A, q + 1, r )


def Partition( A, p, r ):
	x = A[r]
	i = p - 1
	for j in range( p, r ):
		if A[j] <= x:
			i += 1
			A[i], A[j] = A[j], A[i]
	A[i + 1], A[r] = A[r], A[i + 1]
	return i + 1


#
#	Counting Sort
#	Input array:  A[0..n-1] 
#	Output Array: B[0..n-1]
#	All keys must be in the range of 0 to k
#  
def CountingSort( A, B, k ):
	n = len( A )
	C = [0] * ( k + 1 )

	for j in range( n ):
		C[A[j]] += 1

	for i in range( 1, k + 1 ):
		C[i] += C[i-1]

	for j in range( n - 1, -1, -1 ):
		B[C[A[j]] - 1] = A[j]
		C[A[j]] -= 1


#
#	Bucket Sort
#  
def BucketSort( A ):
	n = len( A )
	maximum = max( A )
	size = maximum / n

	buckets = [ [ ] for _ in range( n ) ]
	for i in range( n ):
		j = int( A[i] / size )
		if j != n:
			buckets[j].append( A[i] )
		else:
			buckets[n - 1].append( A[i] )

	for i in range( n ):
		InsertionSort( buckets[i] )

	result = []
	for i in range( n ):
		result = result + buckets[i]

	return result


#####################################################################################
#
#	Dynamic Programming
#	
#####################################################################################
#
#	Rod Cutting
#	Given a rod of length n inches and a table of prices pi, determine the maximum 
#	revenue obtainable by cutting up the rod and selling pieces.
#
#	Reference: Introduction to Algorithms, 3rd Edition
#
def Rod_Cutting( p ):
	n = len( p ) - 1
	
	r = [ 0 for i in range( 0, n + 1 ) ]
	s = [ 0 for i in range( 0, n + 1 ) ]
	
	for j in range( 1, n + 1 ):
		q = -3000000
		for i in range( 1, j + 1 ):
			if q < p[i] + r[j - i]:
				q = p[i] + r[j - i]
				s[j] = i
		r[j] = q
	
	print( "Rod-Cutting Problem" )
	print( "" )
	
	for i in range( 0, n + 1 ):
		print( format( i, '4d' ), end = "" )
	print("")
	
	print( "----------------------------------------------------------" )
	
	for i in range( 0, n + 1 ):
		print( format( r[i], '4d' ), end = "" )
	print("")
	
	for i in range( 0, n + 1 ):
		print( format( s[i], '4d' ), end = "" )
	print( "" )
	

#
#	Matrix Chain Multiplication
#	Given a sequence of A1, A2,..., An of n matrices, find the optimal parenthesization.
#	The matrix Ai has the dimensions p[i - 1] x p[i].
#
#	Reference: Introduction to Algorithms, 3rd Edition
#
def Matrix_Chain_Multiplication( p ):
	n = len( p ) - 1

	m = [ [ 0 for j in range( 0, n + 1 ) ] for i in range( 0, n + 1 ) ]
	s = [ [ 0 for j in range( 0, n + 1 ) ] for i in range( 0, n + 1 ) ]	

	for l in range( 2, n + 1 ):
		for i in range( 1, n - l + 2 ):
			j = i + l - 1
			m[i][j] = 3000000
			for k in range( i, j ):
				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]
				if q < m[i][j]:
					m[i][j] = q
					s[i][j] = k
					
	print( "The m table" )				
	for i in range( 1, n + 1 ):
		for j in range( i + 1, n + 1 ):
			print( format( m[i][j], '6d' ), end = "" )
		print("")

	print("")
	print( "The s table" )			
	for i in range( 1, n + 1 ):
		for j in range( i + 1, n + 1 ):
			print( format( s[i][j], '2d' ), end = "" )
		print("")
	
	print( "Optimal Parenthesization" )	
	Print_Optimal_Parens( s, 1, n )
	print()


def Print_Optimal_Parens( s, i, j ):
	if i == j:
		print( "A" + str( i ), end = "" )
	else:
		print( "(", end = "" )
		Print_Optimal_Parens( s, i, s[i][j] )
		Print_Optimal_Parens( s, s[i][j] + 1, j )
		print( ")", end = "" )
	

#
#	Longest Common Subsequence (LCS)
#	Given two strings X & Y, find the LCS.
#
#	Reference: Introduction to Algorithms, 3rd Edition
#
def LCS( X, Y ):

	UPPERLEFT = 1
	UP 		  = 2
	LEFT 	  = 3

	m = len( X )
	n = len( Y )

	c = [ [ 0 for j in range( 0, n + 1 ) ] for i in range( 0, m + 1 ) ]
	b = [ [ 0 for j in range( 0, n + 1 ) ] for i in range( 0, m + 1 ) ]
	
	for i in range( 1, m + 1 ):
		c[i][0] = 0
	
	for j in range( 1, n + 1 ):
		c[0][j] = 0
	
	for i in range( 1, m + 1 ):
		for j in range( 1, n + 1 ):
			if X[i - 1] == Y[j - 1]:
				c[i][j] = c[i - 1][j - 1] + 1
				b[i][j] = UPPERLEFT
			else:
				if c[i - 1][j] >= c[i][j - 1]:
					c[i][j] = c[i - 1][j]
					b[i][j] = UP
				else:
					c[i][j] = c[i][j - 1]
					b[i][j] = LEFT
	
	i = m
	j = n
	result = ""
	while i != 0 and j != 0:  
		if b[i][j] == UPPERLEFT:
			result = str( X[i - 1] ) + result
			i -= 1
			j -= 1
		elif b[i][j] == UP:
			i -= 1
		else:
			j -= 1

	return result
	
	
#
#	Optimal Binary Search Tree
#	Find the optimal search tree (BST) given the probabilities of n keys (nodes)
#	such that the number of nodes visited is minimized.
#
#	p[i]: probability of key i
#	q[i]: probability of dummy key i
#
#	Reference: Introduction to Algorithms, 3rd Edition
#
def Optimal_BST( p, q ):
	n = len( p ) - 1

	e    = [ [ 0 for j in range( 0, n + 2 ) ] for i in range( 0, n + 2 ) ]
	w    = [ [ 0 for j in range( 0, n + 2 ) ] for i in range( 0, n + 2 ) ]
	root = [ [ 0 for j in range( 0, n + 2 ) ] for i in range( 0, n + 2 ) ]

	for i in range( 1, n + 2 ):
		e[i][i - 1] = q[i - 1]
		w[i][i - 1] = q[i - 1]
		
	for l in range( 1, n + 1 ):
		for i in range( 1, n - l + 2 ):
			j = i + l - 1
			e[i][j] = 1000000000000
			w[i][j] = w[i][j - 1] + p[j] + q[j]
			
			for r in range( i, j + 1 ):
				t = e[i][r - 1] + e[r + 1][j] + w[i][j]
				if t < e[i][j]:
					e[i][j] = t
					root[i][j] = r
	
	print( "The e table" )
	for i in range( 1, n + 2 ):
		for j in range( i - 1, n + 1 ):
			print( format( e[i][j], '6.2f' ), end = "" )
		print("")
	
	print("")
	print( "The w table" )
	for i in range( 1, n + 2 ):
		for j in range( i - 1, n + 1 ):
			print( format( w[i][j], '6.2f' ), end = "" )
		print("")
		
	print("")
	print( "The root table" )
	for i in range( 1, n + 1 ):
		for j in range( i, n + 1 ):
			print( format( root[i][j], '3d' ), end = "" )
		print("")	


#
#	Edit-Distance
#	Given two strings X & Y, find the edit distance, i.e.,
#	the number of editing required to change from X to Y.
#	Possible editing: Insert/Delete/Substitute
#
#	Reference: Introduction to Algorithms, 3rd Edition
#
def Edit_Distance( X, Y ):

	INSERT_COST     = 1
	DELETE_COST     = 1
	SUBSTITUTE_COST = 1

	EDIT_NOCHANGE   = 0
	EDIT_INSERT     = 1
	EDIT_DELETE     = 2
	EDIT_SUBSTITUTE = 3
	
	m = len( X )
	n = len( Y )

	d = [ [ 0 for j in range( 0, n + 1 ) ] for i in range( 0, m + 1 ) ]
	e = [ [ 0 for j in range( 0, n + 1 ) ] for i in range( 0, m + 1 ) ]
								
	for i in range( 0, m + 1 ):
		d[i][0] = i
	
	for j in range( 1, n + 1 ):
		d[0][j] = j
	
	for i in range( 1, m + 1 ):
		for j in range( 1, n + 1 ):
			if X[i - 1] == Y[j - 1]:
				cost = 0
			else:
				cost = SUBSTITUTE_COST
			
			d[i][j] = d[i][j - 1] + INSERT_COST
			e[i][j] = EDIT_INSERT
			
			if d[i][j] >= d[i - 1][j] + DELETE_COST:
				d[i][j] = d[i - 1][j] + 1
				e[i][j] = EDIT_DELETE
			
			if d[i][j] >= d[i - 1][j - 1] + cost:
				d[i][j] = d[i - 1][j - 1] + cost
				if cost == 0:
					e[i][j] = EDIT_NOCHANGE
				else:
					e[i][j] = EDIT_SUBSTITUTE
				
	edit_distance = d[m][n]
	
	print( "The d table" )
	for i in range( 0, m + 1 ):
		for j in range( 0, n + 1 ):
			print( format( d[i][j], '4d' ), end = "" )
		print("")
	
	return edit_distance


#####################################################################################
#
#	Greedy Algorithms
#	
#####################################################################################
#
#	Making Change
#	Given a set of base value base[0],..base[k-1] (coin change values) and input number n
#	find the minimum number of base values to make change for n.
#
#	Reference: 名題精選百則使用C語言 (冼鏡光)
#
def Making_Change( base, k, n ):
	money = [0] * ( n + 1 )

	money[0] = 0
	money[1] = 1
	for i in range( 2, n + 1 ):
		minimum = n
		for j in range( k ):
			if ( i >= base[j] ):
				minimum = min( money[ i - base[j] ] + 1, minimum )
		money[i] = minimum

	return minimum


#
#	0-1 Knapsack
#	A theif robbing a store find n items, where the i-th item worths value[i] dollars and 
#	weight[i] pounds, i = 0..n-1, he can only carry at most W pounds (knapsack). Find the 
#	maximum load. This routine implements the Dynamic Programming (DP) algorithm for solving 
#	the problem.
#
#	Reference: 名題精選百則使用C語言 (冼鏡光)
#
def DP_0_1_Knapsack( value, weight, n, W ):

	c = [ [ 0 for w in range( W + 1 ) ] for i in range( n + 1 ) ]
	
	for w in range( W + 1 ):
		c[0][w] = 0

	for i in range( n + 1 ):
		c[i][0] = 0
		for w in range( 1, W + 1 ):
			if ( weight[i - 1] <= w ):
				if ( value[i - 1] + c[i - 1][w - weight[i - 1]] > c[i - 1][w] ):
					c[i][w] = value[i - 1] + c[i - 1][w - weight[i - 1]]
				else:
					c[i][w] = c[i - 1][w]
			else:
				c[i][w] = c[i - 1][w]
	
	return c[n][W]	


#####################################################################################
#
#	Graph Algorithms
#
#####################################################################################
#
#	Graph (Adjacency Matrix Representation)
#	By default, vertices are numbered as 1..n
#
#	Operations:
#	  Display            (Display the Adjacency Matrix)
#	  BFS                (Breadth-First Seach)
#	  DFS                (Depth-First Search1)
#	  Topological_Sort   (Topological Sort)		
#	  Prim               (Prim's Algorithm for Minimum Spanning Tree)
#	  Bellman_Ford       (Bellman-Ford Algorithm for Single-Source Shortest Paths)
#	  Dijkstra           (Dijkstra's Algorithm for Single-Source Shortest Paths)
#	  Floyd_warshall     (Floyd-Warshall Algorithm for All-Pairs Shortest Paths)
#	  Transitive_Closure (Transitive Closure)
#
#	Reference: Introduction to Algorithms, 3rd Edition
#
INFINITY = 1e30
WHITE = 1
GRAY = 2
BLACK = 3

class AdjacencyMatrix:

	def __init__ ( self, n_vertices ):
		self.n_vertices = n_vertices
		self.n_edges = 0
		self.A = [ [ 0 for j in range( n_vertices + 1 )] for i in range( n_vertices + 1 ) ]

		self.color = [ 0 for i in range( n_vertices + 1 ) ]
		self.d     = [ 0 for i in range( n_vertices + 1 ) ]
		self.pi    = [ 0 for i in range( n_vertices + 1 ) ]
		self.f     = [ 0 for i in range( n_vertices + 1 ) ]

		self.time = 0
		self.TS_list = []

	def SetEdge( self, start_vertex, end_vertex ):
		if ( start_vertex >= 1 and start_vertex <= self.n_vertices and 
			 end_vertex >= 1 and end_vertex <= self.n_vertices ):
			if ( self.A[start_vertex][end_vertex] == 0 ):
				self.A[start_vertex][end_vertex] = self.A[end_vertex][start_vertex] = 1
				self.n_edges += 1

	def SetEdgeWeight( self, start_vertex, end_vertex, weight ):
		if ( start_vertex >= 1 and start_vertex <= self.n_vertices and 
			 end_vertex >= 1 and end_vertex <= self.n_vertices ):
			if ( self.A[start_vertex][end_vertex] == 0 ):
				self.A[start_vertex][end_vertex] = self.A[end_vertex][start_vertex] = weight
				self.n_edges += 1

	def SetDirectedEdge( self, start_vertex, end_vertex ):
		if ( start_vertex >= 1 and start_vertex <= self.n_vertices and 
			 end_vertex >= 1 and end_vertex <= self.n_vertices ):
			if ( self.A[start_vertex][end_vertex] == 0 ):
				self.A[start_vertex][end_vertex] = 1
				self.n_edges += 1

	def SetDirectedEdgeWeight( self, start_vertex, end_vertex, weight ):
		if ( start_vertex >= 1 and start_vertex <= self.n_vertices and 
			 end_vertex >= 1 and end_vertex <= self.n_vertices ):
			if ( self.A[start_vertex][end_vertex] == 0 ):
				self.A[start_vertex][end_vertex] = weight
				self.n_edges += 1

	def Display( self ):
		print( "Graph (Adjacency Matrix Representation)" )
		print( "Number of Vertices =", self.n_vertices )
		print( "Number of Edges =", self.n_edges )
		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				print( self.A[i][j], end = " " )
			print()	


	def BFS( self, source ):
		for u in range( 1, self.n_vertices + 1 ):
			if ( u != source ):
				self.color[u] = WHITE
				self.d[u] = INFINITY
		
		self.color[source] = GRAY
		self.d[source] = 0
		self.pi[source] = 0

		print( "BFS Sequence:" )
		Q = Queue()
		Q.Enqueue( source )

		while ( Q.isEmpty() == False ):
			u = Q.Dequeue()
			print( u, end = " " )
			for v in range( 1, self.n_vertices + 1 ):
				if ( self.A[u][v] != 0 ):
					if ( self.color[v] == WHITE ):
						self.color[v] = GRAY
						self.d[v] = self.d[u] + self.A[u][v]
						self.pi[v] = u
						Q.Enqueue( v )
			self.color[u] = BLACK
		print()	


	def DFS( self, source ):
		for u in range( 1, self.n_vertices + 1 ):
			self.color[u] = WHITE	
			self.d[u] = INFINITY
			self.pi[u] = 0
			self.f[u] = 0

		print( "DFS Sequence:" )
		self.time = 0
		self._DFS( source )
		print() 

	def _DFS( self, u ):
		print( u, end = " " )
		self.color[u] = GRAY
		self.time += 1
		self.d[u] = self.time
		for v in range( 1, self.n_vertices + 1 ):
			if ( self.A[u][v] != 0 ):
				if ( self.color[v] == WHITE ):
					self.pi[v] = u
					self._DFS( v )
		self.color[u] = BLACK
		self.time += 1
		self.f[u] = self.time


	def Topological_Sort( self, source ):
		for u in range( 1, self.n_vertices + 1 ):
			self.color[u] = WHITE
			self.d[u] = INFINITY
			self.pi[u] = 0
			self.f[u] = 0

		self.time = 0
		self._Topological_Sort( source )	
		
		print( "Topological Sort:" )
		for i in range( 0, len( self.TS_list ) ):
			print( self.TS_list[i], end = " " )
		print()
		
	def _Topological_Sort( self, u ):
		self.color[u] = GRAY
		self.time += 1
		self.d[u] = self.time
		
		for v in range( 1, self.n_vertices + 1 ):
			if ( self.A[u][v] != 0 ):
				if ( self.color[v] == WHITE ):
					self.pi[v] = u
					self._Topological_Sort( v )	

		self.color[u] = BLACK
		self.time += 1
		self.f[u] = self.time
		self.TS_list.insert( 0, u )


	def Prim( self, source ):
		
		parent = [ 0 for i in range( self.n_vertices + 1 ) ]
		key = [ INFINITY for i in range( self.n_vertices + 1 ) ]
		set = [ False for i in range( self.n_vertices + 1 ) ]

		MST = [ [ 0 for j in range( self.n_vertices + 1 ) ] for i in range( self.n_vertices + 1 ) ]

		key[source]	= 0
		parent[source] = 0
		set[source] = False

		print( "Prim's Algorithm (MST Sequence)" )
		for i in range( 1, self.n_vertices + 1 ):
			min = INFINITY
			min_idx = 0
			for j in range( 1, self.n_vertices + 1 ):
				if ( set[j] == False and key[j] < min ):
					min = key[j]
					min_idx = j

			set[min_idx] = True
			print( min_idx, end = " " )

			for j in range( 1, self.n_vertices + 1 ):
				if ( self.A[min_idx][j] != 0 and set[j] == False and self.A[min_idx][j] < key[j] ):
					parent[j] = min_idx
					key[j] = self.A[min_idx][j]
		print()

		min_cost = 0
		for i in range( 1, self.n_vertices + 1 ):
			j = parent[i]
			if ( j != 0 ):
				MST[i][j] = MST[j][i] = 1
				min_cost += self.A[i][j]

		print( "Minimum Spanning Tree:" )
		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				print( MST[i][j], end = " " )
			print()

		print( "Minimun Cost =", min_cost )


	def Bellman_Ford( self, source ):

		# Initialization
		for i in range( 1, self.n_vertices + 1 ):
			self.d[i] = INFINITY
		self.d[source] = 0
		self.pi[source] = 0

		edge_start = [ 0 ] * self.n_edges
		edge_end   = [ 0 ] * self.n_edges

		k = 0
		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				if ( self.A[i][j] != 0 ):
					edge_start[k] = i
					edge_end[k] = j
					k += 1

		# Relax			
		for i in range( 1, self.n_vertices ):
			for j in range( 0, self.n_edges ):
				u = edge_start[j]
				v = edge_end[j]

				if ( self.d[v] > self.d[u] + self.A[u][v] ):
					self.d[v] = self.d[u] + self.A[u][v]
					self.pi[v] = u	

		print( "Bellman-Ford Algorithm:" )
		for i in range( 1, self.n_vertices + 1 ):
			print( "Vertex", i, "Distance to souce =", self.d[i], "Parent =", self.pi[i] )


	def Dijkstra( self, source ):

		# Initialization
		for i in range( 1, self.n_vertices + 1 ):
			self.d[i] = INFINITY
		self.d[source] = 0
		self.pi[source] = 0

		set = [True] * ( self.n_vertices + 1 )

		n = self.n_vertices
		while ( n != 0 ):
			# Extract Minimum
			u = 0
			min = INFINITY
			for i in range( 1, self.n_vertices + 1 ):
				if ( set[i] and self.d[i] < min ):
					u = i
					min = self.d[i]
			set[u] = False
			n -= 1

			# Relax
			for v in range( 1, self.n_vertices + 1 ):
				if ( self.A[u][v] != 0 ):
					if ( self.d[v] > self.d[u] + self.A[u][v] ):
						self.d[v] = self.d[u] + self.A[u][v]
						self.pi[v] = u

		print( "Dijkstra Algorithm:" )
		for i in range( 1, self.n_vertices + 1 ):
			print( "Vertex", i, "Distance to souce =", self.d[i], "Parent =", self.pi[i] )


	def Floyd_Warshall( self ):

		D  = [ [ 0 for j in range( self.n_vertices + 1 ) ] for i in range( self.n_vertices + 1 ) ]
		D1 = [ [ 0 for j in range( self.n_vertices + 1 ) ] for i in range( self.n_vertices + 1 ) ]

		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				if ( i == j ):
					D[i][j] = 0
				else:
					if ( self.A[i][j] != 0 ):
						D[i][j] = self.A[i][j]
					else:
						D[i][j] = INFINITY

		for k in range( 1, self.n_vertices + 1 ):	
			for i in range( 1, self.n_vertices + 1 ):
				for j in range( 1, self.n_vertices + 1 ):
					D1[i][j] = min( D[i][j], D[i][k] + D[k][j] )

			for i in range( 1, self.n_vertices + 1 ):
				for j in range( 1, self.n_vertices + 1 ):
					D[i][j] = D1[i][j]

		print( "Floyd-Warshall Algorithm:" )
		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				print( D[i][j], end = " " )
			print()


	def Transitive_Closure( self ):

		T  = [ [ 0 for j in range( self.n_vertices + 1 ) ] for i in range( self.n_vertices + 1 ) ]
		T1 = [ [ 0 for j in range( self.n_vertices + 1 ) ] for i in range( self.n_vertices + 1 ) ]

		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				if ( i == j or self.A[i][j] != 0 ):
					T[i][j] = 1
				else:
					T[i][j] = 0

		for k in range( 1, self.n_vertices + 1 ):	
			for i in range( 1, self.n_vertices + 1 ):
				for j in range( 1, self.n_vertices + 1 ):
					if ( T[i][j] == 1 or ( T[i][k] == 1 and T[k][j] == 1 ) ):
						T1[i][j] = 1

			for i in range( 1, self.n_vertices + 1 ):
				for j in range( 1, self.n_vertices + 1 ):
					T[i][j] = T1[i][j]

		print( "Transitive Closure:" )
		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				print( T[i][j], end = " " )
			print()


#####################################################################################
#
#	Flow Network
#
#####################################################################################
#
#	This subroutine implements the algorithm for solving the flow network problem.
#	The algorithm is based on the Ford-Fulkerson method, in which the BFS is used 
#	for the augmenting path (i.e., Edmonds-Karp algorithm).
#
#	By default, vertices are numbered as 1..n (source = 1, sink = n)
#
#	Operations:
#	  SetEdge  (Set directed edge)
#	  Display  (Display the flow network)
#	  BFS      (BFS to determine if the augmenting path exists) 
#	  MaxFlow  (Find the maximum flow)
#
#	Reference: Introduction to Algorithms, 3rd Edition (Cormen)
#
class FlowNetwork:

	def __init__ ( self, n_vertices ):
		
		# Initialization (By default: source vertex = 1, sink vertex = n)
		self.n_vertices = n_vertices
		self.n_edges = 0
		self.source = 1			 
		self.sink = n_vertices	 

		# Capacity & Flow
		self.cap  = [ [ 0 for i in range( n_vertices + 1 )] for j in range( n_vertices + 1 ) ]
		self.flow = [ [ 0 for i in range( n_vertices + 1 )] for j in range( n_vertices + 1 ) ]
	
		# For the BFS
		self.color = [ 0 for i in range( n_vertices + 1 ) ]
		self.pi     = [ 0 for i in range( n_vertices + 1 ) ]

	def SetEdge( self, start_vertex, end_vertex, capacity ):
		if ( start_vertex >= 1 and start_vertex <= self.n_vertices and 
			 end_vertex >= 1 and end_vertex <= self.n_vertices ):
				self.cap[start_vertex][end_vertex] = capacity
				self.n_edges += 1

	def Display( self ):
		print( "Flow Network" )
		print( "Number of Vertices =", self.n_vertices )
		print( "Number of Edges =", self.n_edges )
		for i in range( 1, self.n_vertices + 1 ):
			for j in range( 1, self.n_vertices + 1 ):
				print( self.cap[i][j], end = " " )
			print()

	def BFS( self ):		
		for u in range( 1, self.n_vertices + 1 ):
			if ( u != self.source ):
				self.color[u] = WHITE
				self.pi[self.source] = 0

		self.color[self.source] = GRAY
		self.pi[self.source] = 0

		Q = Queue()
		Q.Enqueue( self.source )

		while ( Q.isEmpty() == False ):
			u = Q.Dequeue()
			for v in range( 1, self.n_vertices + 1 ):
				if ( self.color[v] == WHITE and self.cap[u][v] - self.flow[u][v] > 0 ):
					self.color[v] = GRAY
					self.pi[v] = u
					Q.Enqueue( v )
			self.color[u] = BLACK

		if ( self.color[self.sink] == BLACK ):  # If the sink is reachable, then the augmenting path exists!
			return True
		else:
			return False

	def MaxFlow( self ):
		max_flow = 0

		while ( self.BFS() ):  # Determine if the augmenting path exists

			increment = 10000000
			u = self.sink
			while( self.pi[u] >= self.source ):
				if ( increment > self.cap[self.pi[u]][u] - self.flow[self.pi[u]][u] ):
					increment = self.cap[self.pi[u]][u] - self.flow[self.pi[u]][u]
				u = self.pi[u]

			u = self.sink
			while ( self.pi[u] >= self.source ):  # Update the flow
				self.flow[self.pi[u]][u] += increment
				self.flow[u][self.pi[u]] -= increment
				u = self.pi[u]

			max_flow += increment
			if ( increment == 0 ): break	

		return max_flow


#####################################################################################
#
#	String Algorithms
#	
#####################################################################################
#
#	infix to postfix conversion
#
#	Input:  One legal infix expression, which contains no blanks on one line of input.
#	Output: The given infix expression and the equivalent postfix expression.
#
#	Assumptions:
#	1. The input string is a legal infix expression, which can contain parentheses.
#	2. Only the following operators +, -, *, /, ^ are allowed.
#	3. Every character that is not an operator or a parenthesis is a legal operand.
#	4. The class Stack for a stack of characters is available.
#
LOW     = 1
MIDDLE  = 2
HIGH    = 3
HIGHEST = 4

def priority_op( op ):
	if ( op == '^' ):
		return HIGHEST
	elif ( op == '*' or op == '/' ):
		return HIGH
	elif ( op == '+' or op == '-' ):
		return MIDDLE	
	else:
		return LOW

def infix_to_postfix( in_str ):
	k = len( in_str )
	S = Stack()
	out_str = ""

	for i in range( k ):
		ch = in_str[i]

		if ( ch in '+-*/^' ):
			done = False
			while ( ( S.isEmpty() == False ) and ( done == False ) ):
				top = S.Pop()
				if ( ( top != '(' ) and ( priority_op( top ) >= priority_op( ch ) ) ):
					out_str += top
				else:
					S.Push( top )
					done = True
			S.Push( ch )

		elif ( ch == '(' ):  
			S.Push( ch )

		elif ( ch == ')' ):  
			top = S.Pop()
			while ( top != '(' ):
				out_str += top
				top = S.Pop()

		else:  # Operands
			out_str += ch

	while( S.isEmpty() == False ):
		out_str = out_str + S.Pop()

	return ( out_str )


#
#	Naive String Matching
#	(Brute-Forch Approach)
#
#	Input: Text[0..n-1] & Pattern[0..m-1] (Strinngs)
#	Ouput: Valid shifts of matched string
#
def Naive_String_Matching( text, pattern ):
	n = len( text )
	m = len( pattern )

	found = False
	for s in range( 0, n - m + 1 ):
		flag = True
		for i in range( m ):
			if ( pattern[i] != text[s + i] ):
				flag = False
				break

		if ( flag ):
			print( "Pattern occurs with shift", s )
			found = True

	if ( not found ):
		print( "Pattern not found!" )

	return found


#
#	Knuth-Morris Pratt (KMP) String Matching
#
#	Input: Text[0..n-1] & Pattern[0..m-1] (Strinngs)
#	Ouput: Valid shifts of matched string
#
def KMP_String_Matching( text, pattern ):
	n = len( text )
	m = len( pattern )
	pi = [0] * m

	found = False

	# Compute Prefix Function
	pi[0] = 0
	k = 0
	for q in range( 1, m ):
		while ( k > 0 and pattern[k] != pattern[q] ):
			k = pi[k - 1]
		if ( pattern[k] == pattern[q] ):
			k += 1
		pi[q] = k

	# Matching
	q = 0
	for i in range( n ):
		while( q > 0 and pattern[q] != text[i] ):
			q = pi[q - 1]
		if ( pattern[q] == text[i] ):
			q += 1
		if ( q == m ):
			print( "Pattern occurs with shift", i - m + 1 )
			q = pi[q - 1]
			found = True

	if ( not found ):
		print( "Pattern not found!" )


#
#	Boyer-Moore (BM) String Matching
#
#	Input: Text[0..n-1] & Pattern[0..m-1] (Strinngs)
#	Ouput: Valid shifts of matched string
#
#	Reference: Introduction to the Design & Analysis of Algorithms (Levitin)
#
def BM_String_Matching( text, pattern ):
	n = len( text )
	m = len( pattern )

	# ASCII Codes
	table = [0] * 256

	found = False

	# Generate shift table
	for i in range( 256 ):
		table[i] = m

	for j in range( m - 1 ):
		table[ ord( pattern[j] ) ] = m - 1 - j

	# Matching
	i = m - 1
	while ( i <= n - 1 ):
		k = 0
		while ( k <= m - 1 and pattern[m - 1 - k] == text[i - k] ):
			k += 1

		if ( k == m ):
			print( "Pattern occurs with shift", i - m + 1 )
			i += 1
			found = True
		else:
			i += table[ ord ( text[i] ) ]

	if ( not found ):
		print( "Pattern not found!" )