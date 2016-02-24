/* 
Adel Danandeh
Assignment #3

Matrix.java is implementation a matrix which points to the doubly link list structure

*/

public class Matrix {

	int n; 		 // The size of the matrix.
	List[] rows; // The matrix.

	private class Entry {

		private int column;
		private double value;

		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}

		public boolean equals(Object x) {
			return ((column == ((Entry) x).column) && (value == ((Entry) x).value));
		}

		public String toString() {
			return ("(" + column + ", " + value + ")");
		}
	}

	// Matrix is a default constructor function which
	// makes a new n x n zero Matrix.
	// pre: n>=1
	Matrix(int n) {

		if (n < 1) {
			throw new RuntimeException("Error! Size of matrix should be 1 or greater.");
		}

		this.n = n;
		rows = new List[n + 1];
		for (int i = 1; i < n + 1; i++) {
			rows[i] = new List();
		}
	}

	// getSize function dose not take any arguments.
	// This function returns n, the number of rows and columns of this Matrix
	int getSize() {

		return n;
	}

	int getNNZ() {

		int num = 0;
		for (int i = 1; i < rows.length; i++) {
			rows[i].moveTo(0);
			while (rows[i].getIndex() != -1) {
				num++;
				rows[i].moveNext();
			}
		}
		return num;
	}

	// equals function takes an object as argument.
	// This function overrides Object's equals() method.
	// This function returns boolean (true/false) based on
	// the conditions inside the if statement.
	public boolean equals(Object x) {

		if (getSize() == ((Matrix) x).getSize()) {
		
			for (int i = 1; i <= getSize(); i++) {
				rows[i].moveTo(0);
				(((Matrix) x).rows[i]).moveTo(0);
				
				if(rows[i].length() != (((Matrix) x).rows[i]).length()){
					return false;
				}
					
				while (rows[i].getIndex() != -1 && ((((Matrix) x).rows[i]).getIndex()) != -1) {
				
					if ((((Entry) rows[i].getElement()).value != ((((Entry) (((Matrix) x).rows[i]).getElement()).value))) || 
							(((Entry) rows[i].getElement()).column != ((((Entry) (((Matrix) x).rows[i]).getElement()).column))) ){
							return false;
					}
					
					rows[i].moveNext();
					(((Matrix) x).rows[i]).moveNext();
				}
			}
		}
		return true;
	}

	// makeZero function does not take any arguments.
	// This function does not return anything.
	// This function sets this Matrix to the zero state
	void makeZero() {
		int i;

		for (i = 1; i < getSize() + 1; i++) {
			rows[i].clear();
		}
	}

	// copy function does not take any arguments.
	// returns a new Matrix having the same entries as this Matrix
	Matrix copy() {
		
		int i;
		Entry newEntry;
		Matrix newMatrix = new Matrix(getSize());

		for (i = 1; i <= getSize(); i++) {
			rows[i].moveTo(0);
			while(rows[i].getIndex() != -1){
				newEntry = new Entry(((Entry) rows[i].getElement()).column,((Entry) rows[i].getElement()).value);
				newMatrix.rows[i].append(newEntry);
				rows[i].moveNext();
			}
		}

		return newMatrix;
	}

	// Function changeEntry takes two integers, and
	// a double as an arguments.
	// changes ith row, jth column of this Matrix to x
	// This function does not return anything
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x){
		int k = rows[i].getIndex(); // preserve the cursor's position, so it could be place at it's original position once operation is done
		
		if(i >= 1 && i <= getSize() && j >= 1 && j <= getSize()){
				
			if(rows[i].length() == 0){
				if(x != 0)
					rows[i].prepend(new Entry(j, x));
			}
			else{
				rows[i].moveTo(rows[i].length()-1);
				while(rows[i].getIndex() != -1 && ((Entry)rows[i].getElement()).column > j)
					rows[i].movePrev();
				if(rows[i].getIndex() >= 0){
					if(x != 0)
						rows[i].insertAfter(new Entry(j, x));
					if(j == ((Entry)rows[i].getElement()).column)
						rows[i].delete();
				}	
				else{
					if(x != 0)
						rows[i].prepend(new Entry(j, x));	
				}
			 }
		}
		rows[i].moveTo(k); // setting back the cursor to where it was located initially
	}
	
	// Function scalarMult takes a double as an argument.
	// returns a new Matrix that is the scalar product of 
	// this Matrix with x
	Matrix scalarMult(double x) {

		Entry newEntry;
		Matrix newMatrix = new Matrix(getSize());
		int i;
		int j;

		for (i = 1; i <= getSize(); i++) {
			rows[i].moveTo(0);
			newEntry = ((Entry) rows[i].getElement());
			for (j = 1; j <= rows[i].length(); j++) {
				newMatrix.changeEntry(i, j, newEntry.value * x);
				rows[i].moveNext();
				newEntry = (Entry) (rows[i].getElement());
			}
		}

		return newMatrix;
	}
	
	// Function scalarMult takes a double as an argument.
	// returns a new Matrix that is the scalar product of 
	// this Matrix with x
	private static double dot(List P, List Q){
		
		double result = 0;
		double pVal, qVal = 0; 
		int pCols, qCols;
		P.moveTo(0);
		Q.moveTo(0);
		
		while(P.getIndex() != -1 && Q.getIndex() != -1){
			
			pVal = ((Entry)P.getElement()).value;
			qVal = ((Entry)Q.getElement()).value;
			pCols = ((Entry)P.getElement()).column;
			qCols = ((Entry)Q.getElement()).column;
				
			if(qCols < pCols){
				Q.moveNext();
			}
			else if(pCols < qCols){
				P.moveNext();
			}
			
			else{
				result += (pVal * qVal);
				P.moveNext();
				Q.moveNext();
			}
		}
		
		return result;
	}
	
	// Function transpose does not take any arguments
	// returns a new Matrix that is the transpose of this Matrix
	Matrix transpose(){
		
		int tempCols = 0;
		double tempValue = 0;
		Matrix newMatrix = new Matrix(getSize());
		
		 for (int i = 1; i <= getSize(); i++){
			 
	            this.rows[i].moveTo(0);
	            while(rows[i].getIndex() != -1){
	            	tempCols = ((Entry)(rows[i].getElement())).column;
	            	tempValue = ((Entry)(rows[i].getElement())).value;
	            	//newMatrix.changeEntry(tempCols, i , tempValue); 
	            	newMatrix.rows[tempCols].append(new Entry(i, tempValue));
	                rows[i].moveNext();
	            }
	     }
		 return newMatrix;
	}
	
	// Function mult takes a Matrix as an argument
	// pre: getSize() == M.getSize()
	// returns a new Matrix that is the product of this Matrix with M
	Matrix mult(Matrix M) {
		
		int i, j;
		double dotResult;
		Matrix transMatrix; 
		Matrix newMatrix = new Matrix(getSize());
		
		if (M.getSize() != getSize()) {
			throw new RuntimeException(
					"[Error]: Matrices do not have a same size.");
		}
		else{
			transMatrix = M.transpose();
			for (i = 1; i <= getSize(); i++) {
				if(rows[i].length() > 0){
				for (j = 1; j <= M.getSize(); j++) {
					if(transMatrix.rows[j].length() > 0){
						dotResult = dot(rows[i], transMatrix.rows[j]);
							if(dotResult != 0){
								newMatrix.changeEntry(i, j, dotResult);
							}
						}
					}
				}
			}
		}
		return newMatrix;
	}

	// Function add takes a Matrix
	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M){
		
		Matrix copyM;
		Matrix newMatrix = null;
		Entry firstData;
		Entry secondData;
		
		if (getSize() == M.getSize()) {

			newMatrix = new Matrix(getSize());
			copyM = M.copy();

			for (int i = 1; i <= getSize(); i++) { 
				if (rows[i].length() > 0 || copyM.rows[i].length() > 0) { // Making sure that lists are not empty

					rows[i].moveTo(0);						// setting the cursor of an existing matrix at the beginning of the list
					copyM.rows[i].moveTo(0);				// setting the cursor of copy of the matrix that gets passed in at the beginning of the list

					while (rows[i].getIndex() != -1 || copyM.rows[i].getIndex() != -1) {
						
						firstData = ((Entry) rows[i].getElement());					// getting elements of an existing matrix
						secondData = ((Entry) copyM.rows[i].getElement());			// getting elements of the copy matrix 
						
						if (firstData != null && secondData != null && firstData.column == secondData.column) { // This is where we add the values of two matrices
							newMatrix.changeEntry(i, firstData.column, firstData.value + secondData.value);
							rows[i].moveNext();
							copyM.rows[i].moveNext();
						}
						else if(firstData != null &&  (secondData == null || firstData.column < secondData.column)){
							newMatrix.changeEntry(i, firstData.column, firstData.value);
							rows[i].moveNext();
						}
						else if(secondData != null && (firstData == null || firstData.column > secondData.column)){
							newMatrix.changeEntry(i, secondData.column, secondData.value);
							copyM.rows[i].moveNext();
						}
					}
				}
			}
		}
		
		return newMatrix;
	}
	
	// Function sub takes a Matrix
	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M){
		
		Matrix copyM;
		Matrix newMatrix = null;
		Entry firstData;
		Entry secondData;
		
		if (getSize() == M.getSize()) {

			newMatrix = new Matrix(getSize());
			copyM = M.copy();

			for (int i = 1; i <= getSize(); i++) { 
				if (rows[i].length() > 0 || copyM.rows[i].length() > 0) { // Making sure that lists are not empty

					rows[i].moveTo(0);						// setting the cursor of an existing matrix at the beginning of the list
					copyM.rows[i].moveTo(0);				// setting the cursor of copy of the matrix that gets passed in at the beginning of the list

					while (rows[i].getIndex() != -1 || copyM.rows[i].getIndex() != -1) {
						
						firstData = ((Entry) rows[i].getElement());					// getting elements of an existing matrix
						secondData = ((Entry) copyM.rows[i].getElement());			// getting elements of the copy matrix 
						
						if (firstData != null && secondData != null && firstData.column == secondData.column) { // This is where we add the values of two matrices
							newMatrix.changeEntry(i, firstData.column, firstData.value - secondData.value);
							rows[i].moveNext();
							copyM.rows[i].moveNext();
						}
						else if(firstData != null &&  (secondData == null || firstData.column < secondData.column)){
							newMatrix.changeEntry(i, firstData.column, firstData.value);
							rows[i].moveNext();
						}
						else if(secondData != null && (firstData == null || firstData.column > secondData.column)){
							newMatrix.changeEntry(i, secondData.column, -secondData.value);
							copyM.rows[i].moveNext();
						}
					}
				}
			}
		}
		
		return newMatrix;
	}
	
	// Function toString does not take any arguments
	// overrides Object's toString() method
	// toString method returns a string
	public String toString() {
		
		String str = "";
		for (int i = 1; i < rows.length; i++) {
			if (rows[i].length() > 0) {

				str += i + ": ";
				rows[i].moveTo(0);
				while (rows[i].getIndex() != -1) {

					str += "(" + ((Entry) (rows[i].getElement())).column + ", ";
					str += ((Entry) (rows[i].getElement())).value + ") ";
					rows[i].moveNext();
				}

				str += "\n";
			}
		}
		return str;
	}
}
