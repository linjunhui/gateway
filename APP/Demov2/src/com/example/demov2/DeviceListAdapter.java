package com.example.demov2;

import java.util.List;
import java.util.zip.Inflater;

import android.R.layout;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class DeviceListAdapter extends BaseAdapter{
	
	private Context context;
	private LayoutInflater layoutInflater;
	private List<Device> mDevices; 
	
	public DeviceListAdapter(Context context, List<Device> mDevices) {
		// TODO Auto-generated constructor stub
		this.context = context;
		this.layoutInflater = LayoutInflater.from(context);
		this.mDevices = mDevices;
	}
	
	public final class Component {
		public TextView dntv;
		public TextView idtv;
		public TextView ontv;
	}
	
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return mDevices.size();
	}

	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		return mDevices.get(position);
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
		
		if(component == null) {
			component = new Component();
			convertView = layoutInflater.inflate(R.layout.deviceslist, null);
			component.dntv = (TextView) convertView.findViewById(R.id.dntv);
			component.idtv = (TextView) convertView.findViewById(R.id.idtv);
			component.ontv = (TextView) convertView.findViewById(R.id.ontv);
			
			convertView.setTag(component);
		} else {
			component = (Component) convertView.getTag();
		}
		
		
		//String devicename = String.valueOf(mDevices.get(position).name);
		String devicename = new String(mDevices.get(position).name);
		System.out.println("name1:" +  devicename);
		component.dntv.setText(devicename);
		
		
		//String ip = mDevices.get(position).ip;
		//String ip = SmartProtocol.inAddrtoIP(mDevices.get(position).ip);
		String id = new String(mDevices.get(position).id);
		component.idtv.setText(id);
		String online = null ;
		if(mDevices.get(position).online == 110)
			online = "����";
		if(mDevices.get(position).online == 121)
			online = "����";
		component.ontv.setText(online);
	
		
		return convertView;
	}

}

