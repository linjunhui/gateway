package com.cqupt.demov1;


import java.io.Serializable;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

import com.zxing.activity.CaptureActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

public class MainActivity extends Activity {
	
	String gateID;
	String gateIp = "92.168.1.110";
	private ListView deviceslv;
	private TextView devicecttv;
	List<Device> devicelist = new ArrayList<Device>() ;
	private TextView gatetv;
	
	Handler mHandler = new Handler() {
		
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			
			switch (msg.what) {
			case 0:
				gatetv.setText("���أ�" + gateIp + "������" );
				break;
			case 1:
				deviceslv.setAdapter(new DeviceListAdapter(getBaseContext(), devicelist));
				devicecttv.setText("�ѽ����豸��" + devicelist.size());
				break;
			default:
				break;
			}
		}
	};	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		//�ؼ�
		deviceslv = (ListView) findViewById(R.id.deviceslv);
		gatetv = (TextView) findViewById(R.id.gatetv);
		devicecttv = (TextView)findViewById(R.id.devicecttv);
		

		
		
//		homeProtocol hp = new homeProtocol();
//		String ip = hp.inAddrtoIP(0xc0a80390);
//		ByteBuffer hh = ByteBuffer.allocate(4);
//		int x = 0x22;
//		hh.putInt(x);
//		
//		
//		
//		short msgtype = 0x1001;
//		ByteBuffer bf = hp.assemData(msgtype, 0xc0a80390, hh);
//		hp.SendPDU(bf, "192.168.1.214");
//		System.out.println("ת�����ip��" + ip);
		
		Device device1 = new Device();
		
	
		device1.ip = "192.168.1.155";
		
		device1.name = "����";
		
		Attr attr1 = new Attr();
		attr1.attrName = "����";
		attr1.datatype = 0x01;
		attr1.dataproperty = 0x02;//�ɶ�����д
		attr1.data = 0x00;
		attr1.times = 1;
		
		device1.attrs[0] = attr1;
		device1.attrs[1] = attr1;
	
		
		deviceslv.setAdapter(new DeviceListAdapter(getBaseContext(), devicelist));
		
		devicelist.add(device1);
		devicelist.add(device1);
		
		deviceslv.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
				// TODO Auto-generated method stub
				System.out.println("ѡ��position:" + position);
				TextView text = (TextView)view.findViewById(R.id.dntv);
				String str = (String) text.getText();
				System.out.println("ѡ�е�ssid:" + str);
				//��ת����device����
				
				Intent intent = new Intent();
				Bundle bundle = new Bundle();
			
				bundle.putSerializable("device", devicelist.get(position));
				
				intent.putExtras(bundle);
				
				intent.setClass(getBaseContext(), DeviceActivity.class);
				
				startActivity(intent);
				

				
			}
			
		});
	}

	//ɨ�����ص�ID,��Ԫ���嵥��Ҫ����ɨ������Activity
	public void scanID(View v) {
		Intent intent = new Intent(MainActivity.this, CaptureActivity.class);
		
		startActivityForResult(intent, 0);
	}
	
	//ɨ���ά���ý����ʼ����
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);

		if(resultCode == RESULT_OK) {
			
			gateID = data.getExtras().getString("result");
			System.out.println("ID:" + gateID);
			connectServer conn = new connectServer();
			gateIp = conn.connectserver(gateID);

			System.out.println("����IP:" + gateIp);
			
			//�õ�gate��IP��ʼ����gate
//			homeProtocol hp = new homeProtocol();
//			int ip = 0;
//			ByteBuffer bf = null;
//			short msgtype = 0x0001;
//			ByteBuffer pdu = hp.assemData(msgtype, ip, bf);
//			hp.SendPDU(pdu, gateIp);
			
			homeProtocol hp = new homeProtocol(mHandler, devicelist);
			int ip = 0xc0a80390;
			short msgtype = 0x0001;
			ByteBuffer pdu = hp.assemData(msgtype, ip, null);
			hp.SendPDU(pdu, gateIp);
		}
	}
	
	
	//���������豸�б�
	public void refreshDevice(View v) {
		devicelist.clear();
		
		homeProtocol hp = new homeProtocol(mHandler, devicelist);
		int ip = 0xc0a80390;
		short msgtype = 0x0003;
		ByteBuffer pdu = hp.assemData(msgtype, ip, null);
		hp.SendPDU(pdu, gateIp);
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
}