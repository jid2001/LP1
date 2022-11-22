
import java.io.*;
import java.net.*;
import java.util.*;
public class Server {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		
		ServerSocket ss = new ServerSocket(4999);
		
		Socket s = ss.accept();
		System.out.println("Client is Connected");
		InputStreamReader ip = new InputStreamReader(s.getInputStream());
		BufferedReader br = new BufferedReader(ip);
		

		PrintWriter  pr = new PrintWriter(s.getOutputStream());
		Scanner sc = new Scanner(System.in);
		// String msg = sc.next();
		// pr.println(msg);
		
	
		   String fun;
	        int a, b, c;
	        while (true) {
	            fun = br.readLine();
	            
	            if( fun.compareTo("exit") == 0 ) {
	            	break;
	            }
	            if (fun != null) {
	                System.out.println("Operation : " + fun);
	            }
	            a = Integer.parseInt(br.readLine());
	            System.out.println("Parameter 1 : " + a);
	            b = Integer.parseInt(br.readLine());
	            System.out.println("Parameter 2 : " + b);

	            if (fun.compareTo("add") == 0) {
	                c = a + b;
	                // System.out.println("Addition = " + c);
	                pr.println("Addition = " + c);
					pr.flush();
	            }
	            if (fun.compareTo("sub") == 0) {
	                c = a - b;
	                // System.out.println("Substraction = " + c);
	                pr.println("Substraction = " + c);
					pr.flush();

	            }
	            if (fun.compareTo("mult") == 0) {
	                c = a * b;
	                // System.out.println("Multiplication = " + c);
	                pr.println("Multiplication = " + c);
					pr.flush();

	            }
	            if (fun.compareTo("div") == 0) {
	                c = a / b;
	                // System.out.println("Division = " + c);
	                pr.println("Division = " + c);
					pr.flush();

	            }
	            System.out.flush();
	            // pr.flush();

	}
	        ss.close();
	        s.close();
	        sc.close();
	}
}
