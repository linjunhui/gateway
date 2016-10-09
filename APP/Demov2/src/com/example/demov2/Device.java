package com.example.demov2;

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

//¿‡÷–¿‡
 class Attr {
	String attrName;
	byte datatype;
	byte dataproperty;
	int data;
	byte times;
}