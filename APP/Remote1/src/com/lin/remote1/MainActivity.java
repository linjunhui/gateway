package com.lin.remote1;

import java.io.BufferedReader;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import com.zxing.activity.CaptureActivity;

import android.R.string;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewDebug.CapturedViewProperty;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	EditText gateIDtv = null;
	static TextView gateIptv = null;
	String mac = "";
	String gateID = "";
	String gateIp = "";
	
	
	   static Handler handler = new Handler() {
	        public void handleMessage(android.os.Message msg) {
	            switch (msg.what) {
	                case 1:
	                	gateIptv.setText((String) msg.obj);
	                    break;

	            }

	        }
	    };
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		gateIDtv = (EditText) findViewById(R.id.gateIDtv);
		gateIptv = (TextView) findViewById(R.id.gateiptv);
	}

	
	public void scanClick(View v) {
		Intent intent = new Intent(MainActivity.this, CaptureActivity.class);
		
		startActivityForResult(intent, 0);
	}

	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		if(resultCode == RESULT_OK) {
			
			mac = data.getExtras().getString("result");
			gateID = mac.replace(":", "");
			
			gateIDtv.setText(gateID);
		}
		
	}
	
	public void connectClick(View v) {
		gateID = gateIDtv.getText().toString();
		if(gateID.length() == 12) {
			
			Intent intent = new Intent();
			Bundle bundle = new Bundle();
			bundle.putString("mac", mac);
			intent.putExtras(bundle);
			//连接服务器获取GateIP
			connectServer();
			//intent.setClass(this, DeviceConnected.class);
			
			//startActivity(intent);
			
		} else {
			
			Toast.makeText(this, "不是正确的gateID", Toast.LENGTH_LONG).show();
		}
	}
	
    public void connectServer() {
        Thread t = new Thread() {
            public void run() {
                try {
                    Socket socket = new Socket("119.29.34.51", 6666);

                   // rSocket = new WeakReference<Socket>(socket);

                    System.out.println("1111");
                    OutputStream outputStream = socket.getOutputStream();
                    outputStream.write(("M" + gateID).getBytes());
                    System.out.println("M" + gateID);
                    outputStream.flush();
                   // recMsg();
                    socket.shutdownOutput();
                    System.out.println("222");
                    BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                    System.out.println("3333");
                  
                    String line = null;
                    while ((line = br.readLine()) != null) {
                        System.out.println("line:" + line);
                        if (line.length()>6 && line.length() < 16) {
                            gateIp = line;
                            System.out.println("ip2:" + gateIp);
                            
                            Message msg = new Message();
                            msg.what = 1;
                            msg.obj = gateIp;
                            
                            handler.sendMessage(msg);
                        } else  {
                            System.out.println("这不是一个ip地址");
                        }
                    }
                    
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        };
        t.start();
    }
    
    public void connectServer(View v) {
    	Thread t = new Thread() {
    		public void run() {
    			try {
					Socket socket = new Socket(gateIp, 6547);
					
                    OutputStream outputStream = socket.getOutputStream();
                    outputStream.write(("I AM MOBILE!").getBytes());
                    outputStream.flush();
                    socket.close();
                    //跳转到下个界面
                   
				} catch (UnknownHostException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
    		}
    	};
    	t.start();
    }
}
