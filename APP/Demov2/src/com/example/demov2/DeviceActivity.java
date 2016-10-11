package com.example.demov2;


import java.util.ArrayList;
import java.util.List;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

public class DeviceActivity extends Activity{
	
	ListView attrlv;
	List<Attr> attrlist = new ArrayList<Attr>() ;
	final List<Device> devicelist = MainActivity.devicelist;
	int deviceposition; 
	
	
	Handler mHandler = new Handler() {
		
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			
			switch (msg.what) {
			case 0:
				System.out.println("收到消息");
				Device device = devicelist.get(deviceposition);
				//取出设备的属性一个个存到list
				attrlist.clear();
				for (int i = 0; i < 10; i++) {
					attrlist.add(device.attrs[i]);
				}
				attrlv.setAdapter(new AttrAdapter(getBaseContext(), attrlist));
				break;
			default:
				break;
			}
		};	
	};
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_device);
		
		Intent intent = this.getIntent();
		
//		Device device = (Device)intent.getSerializableExtra("device");
		
		deviceposition = intent.getIntExtra("position", 0);
		
		Device device = devicelist.get(deviceposition);
		
		System.out.println("position：：" + deviceposition);
		String title = new String(device.name);
		setTitle(title);

//====计算属性的个数==已经设置为10个了这里好像没必要
		int count = 0;
		for (Attr at : device.attrs) {
			if(at != null)
				count++;
		}
		
		//if( device.attrs[4]==null)
		
				System.out.println("count:" + count);
				System.out.println("attr1:" + device.attrs[0].data);
//		System.out.println(device.attrs[0].attrName);
				
		attrlv = (ListView)findViewById(R.id.attrlv);

//取出设备的属性一个个存到list
		for (int i = 0; i < count; i++) {
			attrlist.add(device.attrs[i]);
		}
		//attrlist.add(device.attrs[0]);
		
		
		attrlv.setAdapter(new AttrAdapter(getBaseContext(), attrlist));
	}

	
	public class AttrAdapter extends BaseAdapter {

		
	
		private LayoutInflater layoutInflater;
		private List<Attr> mAttrs; 
		private Context context; 
		
		public AttrAdapter(Context context, List<Attr> mAttrs) {
			// TODO Auto-generated constructor stub
			this.context = context;
			this.layoutInflater = LayoutInflater.from(context);
			this.mAttrs = mAttrs;
		}
		
		public final class Component {
			public TextView attrtv;
			public Button arrtvbt;
		}
		
		@Override
		public int getCount() {
			// TODO Auto-generated method stub
			return mAttrs.size();
		}

		@Override
		public Object getItem(int position) {
			// TODO Auto-generated method stub
			return mAttrs.get(position);
		}

		@Override
		public long getItemId(int position) {
			// TODO Auto-generated method stub
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			// TODO Auto-generated method stub
			Component component = null;
			final int pos = position;
			final View cv = convertView;
			if(component == null) {
				component = new Component();
				convertView = layoutInflater.inflate(R.layout.attrlist, null);
				component.attrtv = (TextView) convertView.findViewById(R.id.attrtv);
				component.arrtvbt = (Button) convertView.findViewById(R.id.attrvbt);
				
				convertView.setTag(component);
			} else {
				component = (Component) convertView.getTag();
			}
			
			
			String attrname = new String(mAttrs.get(position).attrName);
			System.out.println("attrname:" +  attrname);
			component.attrtv .setText(attrname);
			
			String attrv = null;
			
			if((attrname.substring(0, 2)).equals("开关")) {
				if(mAttrs.get(position).data == 0) 
					attrv = "关";
				else
					attrv = "开";
				
			System.out.println("开关状态:" + attrv);
			}
			
												
			
			component.arrtvbt.setText(attrv);
		
			
			//=======对按钮设置监听=========
			component.arrtvbt.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					// TODO Auto-generated method stub
					System.out.printf("参数按钮被点，第%d行\n", pos);

					String attrname = (new String(mAttrs.get(pos).attrName)).substring(0, 2);
					
					System.out.println("获得属性名：" + attrname);
					//改变当前状态显示
					if(attrname.substring(0, 2).equals("开关")) {
						System.out.println("状态改变:" + pos);
						if(devicelist.get(deviceposition).attrs[pos].data == 0 ){
							devicelist.get(deviceposition).attrs[pos].data = 1;
						} else {
							devicelist.get(deviceposition).attrs[pos].data = 0;
						}
						System.out.println("状态改变:");
						System.out.println("开关状态:");
					}
					
					Message msg = new Message();
					msg.what = 0;
					mHandler.sendMessage(msg);
					//调用方法 发送控制到网关 , 设备属性值已经修改，只需将设备对象发送到网关
					SmartProtocol.sendMsg((short) 0x0005, MainActivity.gateIp, devicelist.get(deviceposition));
				}
			});
			
			return convertView;
		}
		
	}
}
