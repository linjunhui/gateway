package com.cqupt.demov1;

import java.io.Serializable;

public class Device implements Serializable {
	String ip;
	String name;
	String id;
	char locked;
	String gateID;
	Attr[] attrs = new Attr[20];
	
	public void SerializableDevice() { 
	}	

}

