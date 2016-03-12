package clientPackage;

import java.io.IOException;
import java.io.InterruptedIOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;


public class Client extends IntegrityCheck{
	
public static void ErrorCheck(char k, String content)//Method for checking the Error codes and giving appropriate response statements.

    {
		User_Response_To_Resend_Message=0;//Initializing the value of the variable	
	switch(k)
	{
	case '0':
			System.out.println(content);//No error. So print the content of the Message.
			break;
	case '1':
		int s=1;
		while(s==1)
		{
			System.out.println("Do you want to resend the message ?(Y/N)");//Integrity check failure. So ask the user to Resend the message.
			Scanner input1 = new Scanner(System.in);
			String l=input1.next();
			while(l.equalsIgnoreCase("y")||l.equalsIgnoreCase("n"))
			{
			if(l.equalsIgnoreCase("y"))
			{
				User_Response_To_Resend_Message=1;//User asking to Resend message since Integrity check failed.
				s=0;
			    break;
			}
			else
			{
				User_Response_To_Resend_Message=0;//User doesn't want the message to be resent.
				s=0;
				break;
				
			}
			
			}
			if(!(l.equalsIgnoreCase("y")|l.equalsIgnoreCase("n"))){
			System.out.println("Invalid entry. Enter (y/n)");//If the user enters anything other than y/n
			
			s=1;
			}
		}
		break;
	case '2':
		System.out.println("Error: Malformed Request. The syntax of the request message is not correct.");
	    break;
	case '3':
		System.out.println("Error: Non-existent File. The file with the requested name does not exist.");
			break;
	case '4':
		System.out.println("Error: Wrong protocol Version. The version number in the request is different from 1.0.");
	    break;
    default:
		System.out.println("Invalid Error code");
		break;

	    	
	}
}
	
public static String User_Request()
{
	String filename = null;//variable to store the filename the user requests
	String choice;//variable which stores the user choice
	int choice_int=9;//integer variable which stores the same
	boolean x=false;
	
	do
	{
	System.out.println("Enter the file to be received from the server: ");
	System.out.println("1 . directors_message.txt");
	System.out.println("2 . program_overview.txt");
	System.out.println("3 . scholarly_paper.txt");
	System.out.println("Please select an option #:");
	Scanner input = new Scanner(System.in);//Opening a port to receive input from user
		choice = input.nextLine();//User gives an input value which can be anything. So storing in a string variable.
		//input.close();//Closing the input port
		if(choice.length()==1)
		{
			choice_int=(int)(choice.charAt(0)-48);
		}
		else
		{
			choice_int=9;//if user input has more than 1 character then assign a default value for user choice
		}

	switch(choice_int)
	{
	case 1:
		{
		filename="directors_message.txt";
		x=false;
		break;
		}
	case 2:
		{
		filename="program_overview.txt";
		x=false;
		break;
		}
	case 3:
		{
		filename="scholarly_paper.txt";
		x=false;
		break;
		}
	default:
		{
		System.out.println("Please Enter a valid option (1,2 or 3)");
		x=true;
		break;
		}
	}
	
	}while(x);
	return filename;
}
public static String Packet_Send_Receive(byte[] reqbin) throws IOException//Method which receives the packet from server and returns a string response message
{  
	final int RX_MESSAGE_SIZE = 3072;//The size limit of the received message.
	final int SERVER_PORT_NUM = 9991; // should be the same port as the one the server is listening on!
	int TIMEOUT_VALUE_MS = 1000;//The timout value to wait for the message from the Server.
	InetAddress serverIp = InetAddress.getByName("192.168.1.7");//Getting the IP address of the local machine. Specify/Change the ip address of the server here.
	DatagramPacket sentPacket = new DatagramPacket(reqbin, reqbin.length, serverIp, SERVER_PORT_NUM);//Opening a datagram packet for sending the message.
	DatagramSocket clientSocket = new DatagramSocket();//Opening A Datagram socket for sending the message.
	clientSocket.send(sentPacket);//Sends the request to server
	System.out.print("\nMessage sent to the server.");
	byte[] Resbin = new byte[RX_MESSAGE_SIZE];
	DatagramPacket receivedPacket = new DatagramPacket(Resbin, RX_MESSAGE_SIZE);//The received packet will be stored in Resbin in binary format.
	
	while(TIMEOUT_VALUE_MS<=8000)
	{
		clientSocket.setSoTimeout(TIMEOUT_VALUE_MS);
	try
	{
		System.out.print("\n Waiting for the server's response...");
		clientSocket.receive(receivedPacket);
		if(receivedPacket.getLength()>0)
			break;
		}
	
	catch(InterruptedIOException e)// timeout - timer expired before receiving the response from the server.
	{
		
	if(TIMEOUT_VALUE_MS==8000)//When timer value reaches 8 seconds, the server fails to respond. So exit the program
	{
		System.out.print("\n Client socket timeout! Exception object e : " + e);//Print the timer exception
		System.exit(0);//Exit the program when the last timer expires
	}
		
	}
	TIMEOUT_VALUE_MS=TIMEOUT_VALUE_MS*2;
	
	}
	
	System.out.println("\nMessage successfully received from the server");
	String ResMsg = new String(receivedPacket.getData(), 0, receivedPacket.getLength());
	clientSocket.close();
	return ResMsg;

}

public static boolean R=false;
public static int User_Response_To_Resend_Message=0;//Stores the user response to resend message.

public static void main(String[] args) throws Exception 
    {
		
		
	int res=1;
	while(res==1)
	
	{
	String ResMsg;//Forr storing the received message
	String file_name = 	User_Request();//Reciving the filename from the user
	String icc=Integritycheck("ENTS/1.0 Request"+"\r\n"+file_name+"\r\n");//Performing integrity check on the input from the user.
	String Req_msg;//The message requested from the server.
	Req_msg = "ENTS/1.0 Request"+"\r\n"+file_name+"\r\n"+icc+"\r\n";//Putting the request message in the correct format.
	byte[] Reqbin = Req_msg.getBytes();//Converting the request message to binary format to be sent to server.
	R=false;
	while(!R)
	{
		
	ResMsg=Packet_Send_Receive(Reqbin);
	String [] separatedMessage = new String [5];
	String response_code;//Error code in the response message.
    String content;//The content of the response message.
	String integrity_check;//The integrity check value received.
	String IC ;
	separatedMessage = ResMsg.split("\r\n");//Splitting the response code

	response_code=separatedMessage[1];//The response error code received.
	char[] c=response_code.toCharArray();
	int lastPosition= ResMsg.lastIndexOf("\r\n"); //last position of "\r\n".
	String ResMsg_withoutIC = ResMsg.substring(0,lastPosition);
	int secondLastPosition = ResMsg_withoutIC.lastIndexOf("\r\n");
	ResMsg_withoutIC = ResMsg_withoutIC.substring(0,secondLastPosition+2);//The received message without the Integrity check field
	integrity_check = ResMsg.substring(secondLastPosition+2, lastPosition);//To extract the Integrity check value from the received message
	
	if(c[0]=='0'&&c.length==1)//If the response message has no errors go to this loop since the content field is present
	{
		content=separatedMessage[3];//The received message content
	}
	
	else		//If the response message has error code other than 0 go to this loop since the content field is not present
	{
		content=null;	
	}
	IC = Integritycheck(ResMsg_withoutIC);//Performing the integrity check on the received message
	//Closing the client socket.
	if(!IC.equals(integrity_check))
	{
		R=false;
		continue;//If integrity check fails Resend message
	}
	
	//Converting the response code to character array so that it can be used in switch statement.
	ErrorCheck(c[0],content);//c[0] contains the error code which can be sent to the Errorcheck method which compares the value of the error code.
	
	if(User_Response_To_Resend_Message==1)
	{
		continue;//If user responds to resend then continue sending the message, else exit loop. This operation occurs in the ErrorCheck method when errorcode 1 occurs
	}
	
	else
	{
	R=true;
    break;//Exit the loop. Stop resending the message
	}
	
	}
	}//Continue this loop till the application is terminated
	
	
}
}



