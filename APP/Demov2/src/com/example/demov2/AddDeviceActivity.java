package com.example.demov2;

import com.hiflying.smartlink.OnSmartLinkListener;
import com.hiflying.smartlink.SmartLinkedModule;
import com.hiflying.smartlink.v3.SnifferSmartLinker;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnDismissListener;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class AddDeviceActivity extends Activity implements OnSmartLinkListener {
	private static final String TAG = "AddDeviceActivity";
	
	protected EditText ssidEditText;
	protected EditText passEditText;
	protected Button startButton;
	
	
	//����һ����̽��
	protected SnifferSmartLinker mSnifferSmartLinker;
	private boolean mIsConncting = false;
	protected Handler mViewHandler = new Handler();
	protected ProgressDialog mWaitingDialog;
	private BroadcastReceiver mWifiChangedReceiver;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		
		//����һ����̽��
		mSnifferSmartLinker = SnifferSmartLinker.getInstence();
		
		
		mWaitingDialog = new ProgressDialog(this);
		mWaitingDialog.setMessage(getString(R.string.hiflying_smartlinker_waiting));
		mWaitingDialog.setButton(ProgressDialog.BUTTON_NEGATIVE, getString(android.R.string.cancel), new DialogInterface.OnClickListener() {
			
			@Override
			public void onClick(DialogInterface dialog, int which) {
			}
		});
		mWaitingDialog.setOnDismissListener(new OnDismissListener() {
			
			@Override
			public void onDismiss(DialogInterface dialog) {

				mSnifferSmartLinker.setOnSmartLinkListener(null);
				mSnifferSmartLinker.stop();
				mIsConncting = false;
			}
		});
		
		
		
		setContentView(R.layout.add_device);
		
		ssidEditText = (EditText) findViewById(R.id.editText_hiflying_smartlinker_ssid);
		passEditText = (EditText) findViewById(R.id.editText_hiflying_smartlinker_password);
		startButton = (Button) findViewById(R.id.button_hiflying_smartlinker_start);
		ssidEditText.setText(getSSid());
	
		
		//�Կ�ʼ��ť���ü��� 
		//�Կ�ʼ��ť���ü���
		startButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				
				//�����ǰ�ֻ�WiFi��������
				if(!mIsConncting){

				
					try {
						//��̽����������
						mSnifferSmartLinker.setOnSmartLinkListener(AddDeviceActivity.this);
						//ssid������  ȥ�����ҿո�
						mSnifferSmartLinker.start(getApplicationContext(), passEditText.getText().toString().trim(), 
								ssidEditText.getText().toString().trim());
						mIsConncting = true;
						//������
						mWaitingDialog.show();
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
		
		
		
		
		
		//����һ���㲥���գ���������Ϊwifi��������Ĺ㲥��������״���ı��ʱ��������ʾ���
		mWifiChangedReceiver = new BroadcastReceiver() {
			
			@Override
			//
			public void onReceive(Context context, Intent intent) {
				//����һ�����ӹ�����
				ConnectivityManager connectivityManager = (ConnectivityManager)getSystemService(Context.CONNECTIVITY_SERVICE);
				//��ȡ������Ϣ
				NetworkInfo networkInfo = connectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
				
				//��ǰ������������ ����ssid �ؼ�
				if (networkInfo != null && networkInfo.isConnected()) {
					ssidEditText.setText(getSSid());
					passEditText.requestFocus();
					startButton.setEnabled(true);
				}else {
					ssidEditText.setText(getString(R.string.hiflying_smartlinker_no_wifi_connectivity));
					ssidEditText.requestFocus();
					startButton.setEnabled(false);
					if (mWaitingDialog.isShowing()) {
						mWaitingDialog.dismiss();
					}
				}
			}
		};
		
		//ע��㲥�������� ���ù��� ������������������ص�Intent
		registerReceiver(mWifiChangedReceiver, new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION));

}
	
//===========��ȡ��ǰ���ӵ�SSID==========	
	private String getSSid(){

		WifiManager wm = (WifiManager) getSystemService(WIFI_SERVICE);
		if(wm != null){
			WifiInfo wi = wm.getConnectionInfo();
			if(wi != null){
				String ssid = wi.getSSID();
				if(ssid.length()>2 && ssid.startsWith("\"") && ssid.endsWith("\"")){
					return ssid.substring(1,ssid.length()-1);
				}else{
					return ssid;
				}
			}
		}

		return "";
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		mSnifferSmartLinker.setOnSmartLinkListener(null);
		try {
			unregisterReceiver(mWifiChangedReceiver);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}


	@Override
	public void onLinked(final SmartLinkedModule module) {
		// TODO Auto-generated method stub
		
		Log.w(TAG, "onLinked");
		mViewHandler.post(new Runnable() {

			@Override
			public void run() {
				//�����Ϻ󵯿���ʾģ����Ϣ
				Toast.makeText(getApplicationContext(), getString(R.string.hiflying_smartlinker_new_module_found, module.getMac(), module.getModuleIP()), 
						Toast.LENGTH_SHORT).show();
			}
		});
	}


	@Override
	public void onCompleted() {
		
		Log.w(TAG, "onCompleted");
		mViewHandler.post(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Toast.makeText(getApplicationContext(), getString(R.string.hiflying_smartlinker_completed), 
						Toast.LENGTH_SHORT).show();
				mWaitingDialog.dismiss();
				mIsConncting = false;
			}
		});
	}


	@Override
	public void onTimeOut() {
		
		Log.w(TAG, "onTimeOut");
		mViewHandler.post(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Toast.makeText(getApplicationContext(), getString(R.string.hiflying_smartlinker_timeout), 
						Toast.LENGTH_SHORT).show();
				mWaitingDialog.dismiss();
				mIsConncting = false;
			}
		});
	}	
}