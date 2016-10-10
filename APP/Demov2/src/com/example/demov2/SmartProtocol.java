package com.example.demov2;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.List;

public class SmartProtocol {
	public static void sendMsg(final short msgtype, final String gateIp, Device device) {
		if(msgtype == 0x0004) {
			 //������ת��Ϊbyte ����
		} else if(msgtype == 0x0003) {
			//�õ�MainActivity�е�devicelist
			final List devicelist = MainActivity.devicelist;
			
			
			//===�������ֺ�ʱ�����������߳�����
			Thread t = new Thread() {
	            public void run() {
	                try {
	                    Socket socket = new Socket(gateIp, 6547);
	                    //char[] buffer = new char[200];
	                    
	                    ByteBuffer bf = ByteBuffer.allocate(2);
	                    //�����ô�˻���С�� ��put
	                    bf.order(ByteOrder.LITTLE_ENDIAN);
	                    bf.putShort(msgtype);
	                    
	                    
	                    byte[] buff = bf.array();
	                    //msgtype ��buff�еĴ洢˳��
	                    System.out.println("buf0 = " + buff[0] + "buff1 = " + buff[1]);
	                    System.out.println("msgtype�ĵ�λ" + (msgtype&0x00ff));
	                    System.out.println("����socket");
	                    
	                    OutputStream outputStream = socket.getOutputStream();
	    				outputStream.write(buff);				
	    	            //outputStream.write(ss.getBytes());	   		           
	    	            outputStream.flush();
	    	            
	    	            BufferedInputStream br = new BufferedInputStream(socket.getInputStream());
	    	            
	    	            byte[] bytes = new byte[277];
	    	            br.read(bytes);
	    	            	    	            
	    	            String s = new String(bytes, 6, 22);
	    	            System.out.println("�յ��ظ���" + s);
	    	            //����һ���豸����
	    	            Device device = new Device();
	    	            device.fillName(bytes);
	    	            device.fillId(bytes);
	    	            device.fillOnline(bytes);
	    	            
	    	            System.out.println("�豸�����ƣ�" + new String(device.name));
	    	            System.out.println("�豸��ID��" + new String(device.id));
	    	            System.out.println("�Ƿ����ߣ�" + device.online);//110 n  121 y  
	    	            
	    	            devicelist.add(device);
	    	            socket.close();
	    			} catch (IOException e) {
	    				// TODO Auto-generated catch block
	    				e.printStackTrace();
	    			}
	            }
			};
			
			t.start();
			
		}
	}
	
	
	//in_addr תip�ַ���
	public static String inAddrtoIP(int addr) {
		
		StringBuffer sb=new StringBuffer(""); 
		sb.append(String.valueOf(addr&0x000000FF)); 
		
		//sb.append(String.valueOf(addr>>>24));//ֱ������24λ 
		sb.append("."); 
		sb.append(String.valueOf((addr&0x0000FFFF)>>>8)); 
		
		//sb.append(String.valueOf((addr&0x00FFFFFF)>>>16)); //����8λ��0��Ȼ������16λ 
		sb.append("."); 
		sb.append(String.valueOf((addr&0x00FFFFFF)>>>16));
		
		//sb.append(String.valueOf((addr&0x0000FFFF)>>>8)); 
		sb.append("."); 
		sb.append(String.valueOf(addr>>>24));//ֱ������24λ 
		
		//sb.append(String.valueOf(addr&0x000000FF)); 
		return sb.toString(); 
				
	}
	
	public static int IPtoInaddr(String ip) {
		int in_addr;
		//ʹ�� \\. ������ .
		String[] as = ip.split("\\.");
		System.out.println("���鳤��:" + as.length);
		
		in_addr = Integer.parseInt(as[3])<<24 | Integer.parseInt(as[2])<<16 | Integer.parseInt(as[1])<<8 | Integer.parseInt(as[0]);
		
		return in_addr;	
	}
}