/*
  Assignment #1
  Adel Danandeh
  
  Lex.java is the driver class. Input from a file gets sorted using 
  insertion method and then it gets printed to an output file.
  
*/

import java.io.*;

public class Lex {

	public static void main(String[] args) throws IOException {

		int lineCount = 0;
		String str[];
		FileReader filename = new FileReader(args[0]);
		List linklist = new List();

		try {
			BufferedReader bufferInput = new BufferedReader(filename);
			while (bufferInput.readLine() != null)
				lineCount++;

			bufferInput.close();
			filename.close();
		} catch (IOException e) {
			System.out.println("Error: " + e);
		}
		
		str = readIntoArray(args[0], lineCount);
		System.out.println();
		insertion(linklist, str, lineCount);
		System.out.println(linklist.toString());
		printToFile("Output.txt", linklist, str);

	}

	public static void printToFile(String filename, List linklist, String[] str) throws IOException {

		PrintWriter output = new PrintWriter(new FileWriter(filename));
		for (linklist.moveTo(0); linklist.getIndex() < linklist.length() && linklist.getIndex() != -1; linklist.moveNext())
			output.println(str[linklist.getElement()]);
		output.close();
	}

	public static String[] readIntoArray(String filename, int size)
			throws IOException {
		String[] str = new String[size];
		FileReader file = new FileReader(filename);
		BufferedReader bufferInput = new BufferedReader(file);
		for (int i = 0; i < size; i++) {
			str[i] = bufferInput.readLine();
		}

		bufferInput.close();
		file.close();
		return str;
	}

	public static void insertion(List linklist, String[] str, int size) {
		String key;
		int i;
		int index;
		int greater = 0;

		linklist.append(0);
		
		for (i = 1; i < size; i++) {
			key = str[i];
			linklist.moveTo(linklist.length() - 1);
			index = linklist.getElement();
			while ((greater = str[index].compareTo(key)) > 0
					&& linklist.getIndex() > 0) {
				linklist.movePrev();
				index = linklist.getElement();
			}
			if (greater <= 0)
				linklist.insertAfter(i);
			else
				linklist.prepend(i);
		}
	}
}
