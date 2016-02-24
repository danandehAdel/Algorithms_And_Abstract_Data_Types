/* 
Adel Danandeh
Assignment #3

ListTest.java is for testing List.

*/
public class ListTest {

	   public static void main(String[] args){
		     
		   	  List A = new List();
		      List B = new List();
		      
		      for(int i=1; i<=20; i++){
		         A.append(i);
		         B.prepend(i);
		      }
		      System.out.println(A);
		      System.out.println(B);
		      
		      A.moveTo(0);			// setting cursor of list A to the beginning of the list
		      B.moveTo(0);			// setting cursor of list B to the beginning of the list
		      
		      while(A.getIndex() >= 0){
		    	  System.out.print(A.getElement()+ " ");
		    	  A.moveNext();
		      }
		      
		      System.out.println();
		      
		      while(B.getIndex() >= 0){
		    	  System.out.print(B.getElement()+ " ");
		    	  B.moveNext();
		      }
		   
		      System.out.println(); 
		      System.out.println(A.equals(B));   // check to see if the lists are equal
		      A.deleteBack();
		      System.out.print(A);
		      System.out.println(); 
		      A.deleteFront();
		      System.out.print(A);
		      System.out.println();
		      A.moveTo(0);
		      B.insertAfter(2580);
		      A.insertBefore(200);
		      A.append(200);
		      A.prepend(500);
		      A.deleteBack();
		      A.deleteFront();
		      System.out.println(A.length());
		      A.clear();
	   }
}

