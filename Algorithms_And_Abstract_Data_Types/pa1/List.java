/* 
  Adel Danandeh
  Assignment #1
  ID# 1436677
  Due Date: 10/13/14
  
  List.java is implementation of a doubly link list structure which has certain methods defined in it. 
  
*/

public class List {

	public class Node {

		Node forward;
		Node backward;
		int data;

		Node() {

			forward = null;
			backward = null;
			this.data = 0;
		}
	}

	private Node front;
	private Node back;
	private int length;
	Node cursor;

	List() {

		front = null;
		back = null;
		cursor = null;
		this.length = 0;
	}

	int length() {

		return length;
	}

	int getIndex() {
		int index = -1;
		Node temp;
		temp = cursor;

		while (temp != null) {

			temp = temp.backward;
			index++;
		}

		return index;
	}

	boolean equals(List l) {

		Node tempNode1 = front;
		Node tempNode2 = l.front;

		while (tempNode1 != null && tempNode2 != null) {

			if (tempNode1.data != tempNode2.data) {

				return false;
			}

			tempNode1 = tempNode1.forward;
			tempNode2 = tempNode2.forward;
			
		}

		return true;
	}

	int front() {

		if (length() > 0) {
			return front.data;
		}

		return -1;
	}

	int back() {

		if (length() > 0) {

			return back.data;
		}

		return -1;
	}

	int getElement() {

		if (length() > 0 && getIndex() >= 0)
			return cursor.data;

		return -1;
	}

	void clear() {

		length = 0;
		front = back = null;
	}

	void moveTo(int i) {

		int j = 0;
		cursor = front;

		if (length() > 0) {
			while (i > j) {

				cursor = cursor.forward;
				j++;
			}
		} else

			cursor = null;
	}

	void movePrev() {

		if (getIndex() <= length() - 1) {
			cursor = cursor.backward;
		}

		else if (getIndex() == 0) {

			cursor = null;
		}

	}

	void moveNext() {

		if (getIndex() < length() - 1) {

			cursor = cursor.forward;
		}

		else if (getIndex() == length() - 1) {
			cursor = null;
		}

	}

	void prepend(int data) {

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

	void append(int data) {

		Node newNode = new Node();

		if (length() == 0) {

			front = newNode;
		}

		else {

			back.forward = newNode;
			newNode.backward = back;

		}

		back = newNode;
		newNode.data = data;
		length++;
	}

	void insertBefore(int data) {

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

	void insertAfter(int data) {

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

	void deleteFront() {

		if (length() > 0) {

			if (front.forward == null) {

				front = null;
				back = null;
			}

			else {

				front = front.forward;
				front.forward.backward.forward = null;
				front.forward.backward = null;

			}

		}
	}

	void deleteBack() {

		if (length() > 0) {

			if (back.backward == null) {

				back = null;
				front = null;
			}

			else {

				back = back.backward;
				back.backward.forward = null;
				back.backward = null;
			}
		}

	}

	void delete() {

		if (getIndex() >= 0 && length() > 0) {

			if (length == 1) {

				cursor.forward = null;
				cursor.backward = null;
			}

			else if (getIndex() == 0) {

				cursor.forward.backward = null;
				cursor.forward = null;
				front = cursor.forward;

			}

			else if (getIndex() == length - 1) {

				cursor.backward.forward = null;
				cursor.forward = null;
			}
		}
	}

	List copy() {

		List newList = new List();
		Node temp = front;
		
		for (int i = 0; i < length ; i++) {
			
			newList.append(temp.data);
			temp = temp.forward;
		}

		return newList;
	}

	public String toString() {

		String str = " ";
		Node temp = front;

		for (int i = 0; i < length; i++) {

			str += temp.data + " ";
			temp = temp.forward;

		}

		return str;
	}
}
