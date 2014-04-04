package com.example.openwrt;

import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.LinkedList;
import com.example.openwrt.R;
import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends Activity implements Button.OnClickListener {

	private Button btn01, btn02, btn03, btn04, btn05;
	private  PrintWriter out;
	private  Socket socket;
	private DataOutputStream dout;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		btn01 = (Button) findViewById(R.id.button1);
		btn02 = (Button) findViewById(R.id.button2);
		btn03 = (Button) findViewById(R.id.button3);
		btn04 = (Button) findViewById(R.id.button4);
		btn05 = (Button) findViewById(R.id.button5);
		btn01.setOnClickListener((OnClickListener) this);
		btn01.setTag(1);
		btn02.setOnClickListener((OnClickListener) this);
		btn02.setTag(2);
		btn03.setOnClickListener((OnClickListener) this);
		btn03.setTag(3);
		btn04.setOnClickListener((OnClickListener) this);
		btn04.setTag(4);
		btn05.setOnClickListener((OnClickListener) this);
		btn05.setTag(5);
		// new MySendCommondThread("hello888888888888").start();
		//Toast.makeText(getApplicationContext(), "fragment == null", Toast.LENGTH_SHORT).show();
	}
	
	
	public void onClick(View v) {
		int tag = (Integer) v.getTag();
		switch (tag) {
		case 1:
			new MySendCommondThread("open led").start();
			break;
		case 2:
			new MySendCommondThread("close led").start();
			break;
		case 3:
			new MySendCommondThread("close fan").start();
			break;
		case 4:
			new MySendCommondThread("fan 1").start();
			break;
		case 5:
			new MySendCommondThread("fan 2").start();
			break;
		default:
			break;
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	// TCP命令线程
	class MySendCommondThread extends Thread {
		private String commond;

		public MySendCommondThread(String commond) {
			this.commond = commond;
		}

		public void run() {
			// 实例化Socket
			try {
				socket = new Socket("121.49.97.195",3333);
				out = new PrintWriter(socket.getOutputStream());
				out.print(commond + '\0');
				out.flush();
				//dout = new DataOutputStream(socket.getOutputStream());
				//String str="fuck you";
				//dout.writeChars(str); 
				//dout.flush();
				out.close();
				socket.close();
			} catch (UnknownHostException e) {
			} catch (IOException e) {
				Log.d("ioerror", "");
			}
		}
	}
}
