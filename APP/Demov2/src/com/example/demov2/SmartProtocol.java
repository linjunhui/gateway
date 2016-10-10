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
			 //将对象转化为byte 数组
		} else if(msgtype == 0x0003) {
			//拿到MainActivity中的devicelist
			final List<Device> devicelist = MainActivity.devicelist;
			
			
			//===网络这种耗时操作放在子线程中做
			Thread t = new Thread() {
	            public void run() {
	                try {
	                    Socket socket = new Socket(gateIp, 6547);
	                    //char[] buffer = new char[200];
	                    
	                    ByteBuffer bf = ByteBuffer.allocate(2);
	                    //先设置大端还是小端 再put
	                    bf.order(ByteOrder.LITTLE_ENDIAN);
	                    bf.putShort(msgtype);
	                    
	                    
	                    byte[] buff = bf.array();
	                    //msgtype 在buff中的存储顺序
	                    System.out.println("buf0 = " + buff[0] + "buff1 = " + buff[1]);
	                    System.out.println("msgtype的低位" + (msgtype&0x00ff));
	                    System.out.println("建立socket");
	                    
	                    OutputStream outputStream = socket.getOutputStream();
	    				outputStream.write(buff);				
	    	            //outputStream.write(ss.getBytes());	   		           
	    	            outputStream.flush();
	    	            
	    	            BufferedInputStream br = new BufferedInputStream(socket.getInputStream());
	    	            

	    	            byte[] bytes = new byte[277];
	    	          
	    	           //int i;
	    	          while(br.read(bytes) > 0) {
	    	        	  	
	    	        	    //int i =  br.read(bytes);
		    	            //System.out.println("读取到字节数：" + i);	    	            
		    	            String s = new String(bytes, 6, 22);
		    	            System.out.println("收到回复：" + s);
		    	            //创建一个设备对象
		    	            Device device = new Device();
		    	            device.fillName(bytes);
		    	            device.fillId(bytes);
		    	            device.fillOnline(bytes);
		    	            
		    	            System.out.println("设备的名称：" + new String(device.name));
		    	            System.out.println("设备的ID：" + new String(device.id));
		    	            System.out.println("是否在线：" + device.online);//110 n  121 y  
		    	            
		    	            devicelist.add(device);
		    	    
	    	         }
	    	         //  System.out.println("读取到字节数：" + i);
	    	           System.out.println("设备列表更新完成");
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
	
	
	//in_addr 转ip字符串
	public static String inAddrtoIP(int addr) {
		
		StringBuffer sb=new StringBuffer(""); 
		sb.append(String.valueOf(addr&0x000000FF)); 
		
		//sb.append(String.valueOf(addr>>>24));//直接右移24位 
		sb.append("."); 
		sb.append(String.valueOf((addr&0x0000FFFF)>>>8)); 
		
		//sb.append(String.valueOf((addr&0x00FFFFFF)>>>16)); //将高8位置0，然后右移16位 
		sb.append("."); 
		sb.append(String.valueOf((addr&0x00FFFFFF)>>>16));
		
		//sb.append(String.valueOf((addr&0x0000FFFF)>>>8)); 
		sb.append("."); 
		sb.append(String.valueOf(addr>>>24));//直接右移24位 
		
		//sb.append(String.valueOf(addr&0x000000FF)); 
		return sb.toString(); 
				
	}
	
	public static int IPtoInaddr(String ip) {
		int in_addr;
		//使用 \\. 而不是 .
		String[] as = ip.split("\\.");
		System.out.println("数组长度:" + as.length);
		
		in_addr = Integer.parseInt(as[3])<<24 | Integer.parseInt(as[2])<<16 | Integer.parseInt(as[1])<<8 | Integer.parseInt(as[0]);
		
		return in_addr;	
	}
}
