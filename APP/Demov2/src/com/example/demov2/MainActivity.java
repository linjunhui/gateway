package com.example.demov2;

import java.nio.ByteBuffer;
import java.nio.channels.GatheringByteChannel;
import java.util.ArrayList;
import java.util.List;

import com.zxing.activity.CaptureActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v4.widget.SwipeRefreshLayout.OnRefreshListener;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;

public class MainActivity extends Activity implements OnRefreshListener {
	
	public String gateID;
	public String gateIp;
	SwipeRefreshLayout deviceSw;
	ListView deviceList; 
	
	List<Device> devicelist = new ArrayList<Device>() ;
	
	Device device1;
	
	private Handler mHandler = new Handler() {
        public void handleMessage(android.os.Message msg)  
        {  
            switch (msg.what)  
            {  
            case 1:  
            	System.out.println("准备更新list");
            	devicelist.add(device1);
            	deviceList.setAdapter(new DeviceListAdapter(getBaseContext(), devicelist));
                break;  
  
            }  
        }; 
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		deviceSw = (SwipeRefreshLayout) findViewById(R.id.device_sw);
		deviceList = (ListView) findViewById(R.id.device_list);
		
		deviceSw.setOnRefreshListener(this);
		
		//========模拟====================
		device1 = new Device();
		
		
		device1.ip = "192.168.1.155";
		
		device1.name = "电扇";
		
		Attr attr1 = new Attr();
		attr1.attrName = "开关";
		attr1.datatype = 0x01;
		attr1.dataproperty = 0x02;//可读，可写
		attr1.data = 0x00;
		attr1.times = 1;
		
		device1.attrs[0] = attr1;
		device1.attrs[1] = attr1;
		
		devicelist.add(device1);
		//======设置listView的Adapter
		deviceList.setAdapter(new DeviceListAdapter(getBaseContext(), devicelist));
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	
	
	//================扫码获得网关的IP=======
	//扫描网关的ID,在元件清单中要添加扫描界面的Activity
	public void scanID(View v) {
		Intent intent = new Intent(MainActivity.this, CaptureActivity.class);
		
		startActivityForResult(intent, 0);
	}
	
	//扫描二维码获得结果后开始处理
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);

		if(resultCode == RESULT_OK) {
			
			gateID = data.getExtras().getString("result");
			System.out.println("ID:" + gateID);
			//connectServer conn = new connectServer();
			//gateIp = conn.connectserver(gateID);
			
			gateIp = ConnectServer.connectserver(gateID);

			System.out.println("返回IP:" + gateIp);
			
			//得到gate的IP后开始连接gate
//			homeProtocol hp = new homeProtocol();
//			int ip = 0;
//			ByteBuffer bf = null;
//			short msgtype = 0x0001;
//			ByteBuffer pdu = hp.assemData(msgtype, ip, bf);
//			hp.SendPDU(pdu, gateIp);
//			
//			homeProtocol hp = new homeProtocol(mHandler, devicelist);
//			int ip = 0xc0a80390;
//			short msgtype = 0x0001;
//			ByteBuffer pdu = hp.assemData(msgtype, ip, null);
//			hp.SendPDU(pdu, gateIp);
		}
	}
	
	//=============跳转到添加设备界面============
	public void addDevice(View v) {
		startActivity(new Intent(this, AddDeviceActivity.class));
	}
	
	//SwipeRefreshLayout.OnRefreshListener 接口中的方法   下拉时做什么
	@Override
	public void onRefresh() {
		// TODO Auto-generated method stub
		System.out.println("下拉了！！！！！");
		//停止刷新
		deviceSw.setRefreshing(false);
		//下拉时 向网关发消息请求设备列表
		
		Message swMsg = new Message();
		swMsg.what = 1;
		
		mHandler.sendMessage(swMsg);
		
		//网关的IP，消息内容 0x0003 请求设备列表
		//APP消息类型：1.请求设备列表  	2.控制设备
		//CCC.sendMsg(gateIP, 0x0003, NULL)
		/* 控制设备
		 * 拿到这个设备对象 或者说  信息，修改其中的属性
		 * CCC.sendMsg(gateIP, 0x0004, device)
		 * 
		 */
	}
	
	
}
