/* 
Adel Danandeh
Assignment #3

Sparse.java opens an input file and writes out to an output file.

*/
import java.io.*;

public class Sparse {

	public static void main(String[] args) throws IOException {

		if(args.length == 2){
		int lineCount = 0;
		
		String[] str = new String[3];
		String str1;

		BufferedReader input;
		input = new BufferedReader(new FileReader(args[0]));
		PrintWriter output;
		
		str1 = input.readLine();
		str = str1.split(" ");
		
		Matrix newMatrix = new Matrix(Integer.parseInt(str[0]));
		Matrix newMatrix1 = new Matrix(Integer.parseInt(str[0]));
		
		str1 = input.readLine();
		while((str1 = input.readLine()).length() > 0){
			str = str1.split(" ");
			newMatrix.changeEntry(Integer.parseInt(str[0]), Integer.parseInt(str[1]), Double.parseDouble(str[2]));
		}
		
		while((str1 = input.readLine()) != null){
			str = str1.split(" ");
			newMatrix1.changeEntry(Integer.parseInt(str[0]), Integer.parseInt(str[1]), Double.parseDouble(str[2]));
		}
		
		input.close();
		output = new PrintWriter(new FileWriter(args[1]));
		
		output.println("A has " + newMatrix.getNNZ() + " non-zero entries: ");
		output.println(newMatrix);
		
		output.println("B has " + newMatrix1.getNNZ() + " non-zero entries: ");
		output.println(newMatrix1);
		
		output.println("(1.5)*A = ");
		output.println(newMatrix.scalarMult(1.5));
		
		output.println("A+B =");
		output.println(newMatrix.add(newMatrix1));
		
		output.println("A+A =");
		output.println(newMatrix.add(newMatrix));
		
		output.println("B-A =");
		output.println(newMatrix1.sub(newMatrix));
		
		output.println("Transpose(A) =");
		output.println(newMatrix.transpose());
		
		output.println("A*B =");
		output.println(newMatrix.mult(newMatrix1));
		
		output.println("B*B =");
		output.println(newMatrix1.mult(newMatrix1));
		
		output.close();
	}	
		else{
			System.out.println("Error!");
		}
	}
}


