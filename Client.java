

import java.io.*;
import java.net.*;
import java.util.*;
public class Client {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		Socket s = new Socket("localhost", 4999);
		
		PrintWriter pr = new PrintWriter(s.getOutputStream(),true);
		Scanner sc = new Scanner(System.in);
		
		// String str = sc.nextLine();
		
		// pr.println(str);
		
		
		InputStreamReader ip = new InputStreamReader(s.getInputStream());
		BufferedReader br = new BufferedReader(ip);
		String  rmsg, smsg, temp;
		
		System.out.println("Client is ready  ");
		
		while(true) {
			System.out.println("\n Enter operation to perform(add,sub,mult,div,exit).........!");
			
			temp = sc.nextLine();
			if(temp.compareTo("exit") == 0) {
				pr.println(temp);
				pr.flush();
				break;
				
			}
			pr.println(temp);
			pr.flush();
			System.out.println("Enter op1 :");
			smsg = sc.nextLine();
			pr.println(smsg);
			pr.flush();
			System.out.println("Enter op2 :");
			smsg = sc.nextLine();
			pr.println(smsg);
			pr.flush();
			
			rmsg = br.readLine();
			
			pr.flush();

			if(rmsg != null) {
				System.out.println(rmsg);
			}
			
			
		}
		
		sc.close();
		s.close();
		
		

	}

}
