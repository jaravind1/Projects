package serverPackage;

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.*;

public class Server extends IntegrityCheck{

	public static void main(String[] args) throws Exception {
		

		
		
		//will save the respective error codes in this variable and use it to notify the client. 
		int errorCode;
		
		//Opening the data socket and using a port number.
		DatagramSocket dsc = new DatagramSocket (9991);
		
		//Using buf as a buffer to save the incoming bytes. 
		byte [] buf = new byte[8000];
		
		//response Message that will be sent to the client.
		String responseMessage="";
		
		//Creating an object for the ServerResponseMessage object that returns final message that needs to be sent to the client.
		ServersResponseMessage srm = new ServersResponseMessage(); // the class that has methods that will return the response message.
		
		
		
		
		
		
		
		//Infinite loop so that the server runs continuously. 
		while(true){
			
			//creating the object for a data packet that is to be received.
			DatagramPacket dpc = new DatagramPacket (buf, buf.length);
			
			//receiving the data packet.
			dsc.receive(dpc);
			
			//notifying any user monitoring the server that a packet has been received.
			System.out.println("Message received from client");
			
			//to convert the received bits into string.
			String receivedMessage = new String(dpc.getData(), 0, dpc.getLength());
			//notifying the user, the received message in String.
			System.out.println(receivedMessage);
			
			/*dividing the received message into different parts
			 * separatedMessage[0] is the header.
			 * separatedMessage[1] is the file name.
			 * separatedMessage[2] is the integrity check value received from Client.
			*/
			String [] separatedMessage = receivedMessage.split("\r\n");
			
					
			
			//Integrity check on the this (server) side by combining the header and the file name that was received.
			int lastPosition= receivedMessage.lastIndexOf("\r\n"); //last position of "\r\n".
			String sep = receivedMessage.substring(0,lastPosition);
			int secondLastPosition = sep.lastIndexOf("\r\n");
			sep = sep.substring(0,secondLastPosition+2);
			String receivedChecksum = receivedMessage.substring(secondLastPosition+2, lastPosition);
			
			
			//String serverIntegrityCheck = ic.IC(separatedMessage[0]+"\r\n"+separatedMessage[1]+"\r\n");
			String serverIntegrityCheck = Integritycheck(sep);
			
			//assigning error code if integrity check fails.
			if (!serverIntegrityCheck.equals(receivedChecksum)){
				errorCode = 1;
				responseMessage = srm.responseMessage(errorCode);
				
			}
			
			
			else if (!separatedMessage[1].matches("^[A-Za-z][A-Za-z0-9_]*[.][a-zA-Z0-9]*") || separatedMessage.length!=3 || !separatedMessage[0].matches("^(ENTS/).*(Request)")){
				errorCode = 2;
				responseMessage = srm.responseMessage(errorCode);
			}
			
			else if (!separatedMessage[0].contains("1.0")){
				errorCode=4;				
				responseMessage = srm.responseMessage(errorCode);
			}			
			
			else{
				errorCode = 0;
			}
			
			
			//opening the requested file after checking that there is no error in the format of the message received.
			//change and specify the path of the folder that contains the files as required.				
			String folderPath = "C:\\Users\\Sreeram\\Desktop\\640 PROJECT\\";
			int inErrorCode; //new error code variable. This also gives confirmation that the internal loop was executed.
			
			if (errorCode ==0){
				String filePath = folderPath+separatedMessage[1] ; 
				
				String bufferText = "";
				String textInFile = "";
				
				try{
					
					BufferedReader br = new BufferedReader(new FileReader (filePath));
					
					while (((bufferText= br.readLine())!=null)){
						textInFile += bufferText + "\n";
						
					}
					inErrorCode = 0;
					responseMessage = srm.responseMessage(inErrorCode, textInFile);
					
				}
				
				
				catch (IOException e){
				inErrorCode = 3; //assigning error code of 3 in case the file is not present.
				responseMessage = srm.responseMessage(inErrorCode);					
				}				
				
			}
			
			System.out.println(responseMessage);
			
			//converting the response message into bytes.
			byte [] responseBytes = responseMessage.getBytes();
			
			for (int i =0; i<responseBytes.length; i++){
				System.out.print(responseBytes[i]+",");
			}
			
			DatagramPacket dpcResponse = new DatagramPacket (responseBytes, responseBytes.length, dpc.getAddress(), dpc.getPort());
			dsc.send(dpcResponse);
			
			System.out.println("sent!");			
			
		}



	}

}
