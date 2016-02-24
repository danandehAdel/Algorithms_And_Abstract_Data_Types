/* 
 Adel Danandeh
 Assignment #3

 List.java is implementation of a doubly link list structure which has certain methods defined in it. 

 */

public class List {

	private class Node {

		private Node forward;
		private Node backward;
		private Object data;

		Node() {

			forward = null;
			backward = null;
			this.data = null;
		}
	}

	private Node front;
	private Node back;
	private int length;
	private Node cursor;

	List() {

		front = null;
		back = null;
		cursor = null;
		this.length = 0;
	}

	// The function length does take any arguments
	// This function returns the length of the list
	public int length() {

		return length;
	}

	// The function getIndex does not take any arguments.
	// Returns the index of the cursor element in this list, or
	// returns -1 if the cursor element is undefined.
	public int getIndex() {
		int index = -1;
		Node temp;
		temp = cursor;

		while (temp != null) {

			temp = temp.backward;
			index++;
		}

		return index;
	}

	// The function front does not take any arguments.
	// Pre: length()>0
	Object front() {

		if (length() > 0) {
			return front.data;
		}

		return null;
	}

	// Function back does not take arguments
	// Pre: length()>0
	Object back() {

		if (length() > 0) {

			return back.data;
		}

		return null;
	}

	// The function getElement does not take any arguments.
	// Pre: length()>0, getIndex()>=0
	Object getElement() {

		if (length() > 0 && getIndex() >= 0)
			return cursor.data;

		return null;
	}

	// The function equals takes a list as an argument.
	// Returns true if this List and L are the same integer
	// sequence. The cursor is ignored in both lists.
	public boolean equals(Object x) {

		Node tempNode1 = front;
		Node tempNode2 = ((List) x).front;

		while (tempNode1 != null && tempNode2 != null) {

			if (tempNode1.data != tempNode2.data) {

				return false;
			}

			tempNode1 = tempNode1.forward;
			tempNode2 = tempNode2.forward;

		}

		return true;
	}

	// Function clear does not take any arguments.
	// Re-sets this List to the empty state.
	void clear() {

		length = 0;
		front = back = null;
		cursor = null;
	}

	// Function moveTo takes an integer as an argument.
	// If 0<=i<=length()-1, moves the cursor to the element
	// at index i, otherwise the cursor becomes undefined.
	void moveTo(int i) {

		int counter = 0;
		if (i >= 0 && i <= length() - 1) {
			cursor = front;
			while (counter != i) {
				cursor = cursor.forward;
				counter++;
			}
		} else
			cursor = null;
	}

	// Function movePrev does not take any arguments
	// If 0<getIndex()<=length()-1, moves the cursor one step toward the
	// front of the list. If getIndex()==0, cursor becomes undefined.
	// If getIndex()==-1, cursor remains undefined.
	void movePrev() {

		if (getIndex() > 0 && getIndex() <= length() - 1) {
			cursor = cursor.backward; // front of the list
		} else {
			cursor = null;
		}
	}

	// Function moveNext does not take any arguments
	// If 0<=getIndex()<length()-1, moves the cursor one step toward the
	// back of the list. If getIndex()==length()-1, cursor becomes
	// undefined. If index==-1, cursor remains undefined
	void moveNext() {

		if (0 <= getIndex() && getIndex() < length() - 1) {
			cursor = cursor.forward; // back of the list
		} else {
			cursor = null;
		}

	}

	// Function prepend takes an object as an argument
	// Inserts new element before front element in this List.
	void prepend(Object data) {

		Node newNode = new Node();

		if (length() == 0) {

			back = newNode;
		}

		else {

			front.backward = newNode;
			newNode.forward = front;
		}
		front = newNode;
		newNode.data = data;
		length++;
	}

	// Function append takes an object as an argument
	// Inserts new element after back element in this List.
	void append(Object data) {

		Node newNode = new Node();
		newNode.data = data;
		if (length() == 0)
			front = newNode;
		else {
			back.forward = newNode;
			newNode.backward = back;
		}
		back = newNode;
		length++;
	}

	// Function inserBefore takes an object data.
	// Inserts new element before cursor element in this
	// Pre: length()>0, getIndex()>=0
	void insertBefore(Object data) {

		if (getIndex() >= 0 && length() > 0) {

			Node newNode = new Node();
			newNode.data = data;

			if (getIndex() == 0) {

				cursor.backward = newNode;
				newNode.forward = cursor;
				front = newNode;
			}

			else {

				newNode.forward = cursor;
				newNode.backward = cursor.backward;
				cursor.backward.forward = newNode;
				cursor.backward = newNode;
			}
		}
		length++;
	}

	// Function insertAfter takes an object as argument.
	// Inserts new element after cursor element in this
	// Pre: length()>0, getIndex()>=0
	void insertAfter(Object data) {

		if (getIndex() >= 0 && length() > 0) {

			Node newNode = new Node();
			newNode.data = data;

			if (getIndex() == 0) {

				cursor.forward = newNode;
				newNode.backward = cursor;

			}

			else if (cursor.forward == null) {

				cursor.forward = newNode;
				newNode.backward = cursor;
			}

			else {

				newNode.backward = cursor;
				newNode.forward = cursor.forward;
				cursor.forward.backward = newNode;
				cursor.forward = newNode;

			}

		}

		length++;
	}

	// Function deleteFront does not take any arguments
	// Deletes the front element in this List. Pre: length()>0
	void deleteFront() {

		if (length() >= 0) {
			if (length() == 1) {
				front = null;
				back = null;
			} else {
				front = front.forward;
				front.backward.forward = null;
				front.backward = null;
			}
			length--;
		}
	}

	// Function deleteBack does not take any arguments.
	// Deletes the back element in this List. Pre: length()>0
	void deleteBack() {

		if (length() >= 0) {
			if (length() == 1) {
				front = null;
				back = null;
			} else {
				back = back.backward;
				back.forward.backward = null;
				back.forward = null;
			}
			length--;
		}
	}

	// Function delete does not take any arguments
	// Deletes cursor element in this List. Cursor is undefined after this
	// operation. Pre: length()>0, getIndex()>=0
	void delete() {
		if (length() > 0 && getIndex() >= 0) {
			if (getIndex() == 0) {
				if (length() > 1)
					cursor.forward.backward = null;
				else
					back = null;
				front = cursor.forward;
			} else if (getIndex() == length() - 1) {
				cursor.backward.forward = null;
				back = cursor.backward;
			} else {
				cursor.backward.forward = cursor.forward;
				cursor.forward.backward = cursor.backward;
			}
			cursor = null;
			length--;
		}
	}

	public String toString() {

		String str = " ";
		Node temp = front;

		for (int i = 0; i < length; i++) {

			str += temp.data.toString() + " ";
			temp = temp.forward;
		}

		return str;
	}
}
