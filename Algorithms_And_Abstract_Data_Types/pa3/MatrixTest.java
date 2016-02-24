/* 
Adel Danandeh
Assignment #3

MatrxTest.java is for testing Matrix

*/
public class MatrixTest {

public static void main(String[] args) {
		
		Matrix newMatrix = new Matrix(1000000);
		Matrix secondM =   new Matrix(1000000);
		
		newMatrix.changeEntry(1, 1, 10);
		newMatrix.changeEntry(1, 2, 20);
		newMatrix.changeEntry(2, 1, 20);
		newMatrix.changeEntry(2, 2, 20);
		newMatrix.changeEntry(2, 2, 20);
		newMatrix.changeEntry(2, 2, 0);
		newMatrix.changeEntry(9, 10, 51.1);
		
		secondM.changeEntry(1, 1, 10);
		secondM.changeEntry(1, 2, 10);
		secondM.changeEntry(2, 1, 10);
		secondM.changeEntry(2, 2, 10);
		
		System.out.println(newMatrix.copy());
		System.out.println(newMatrix.sub(secondM));
		System.out.println(newMatrix.mult(secondM));
		System.out.println(newMatrix.transpose());
		System.out.println(newMatrix.equals(newMatrix));
		System.out.println(newMatrix.add(secondM));
		System.out.println(newMatrix.sub(secondM));
		
	}
}	

