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
import com.example.openwrt.ImageAdapter;
import android.os.Bundle;
import android.app.Activity;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.LightingColorFilter;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.Gallery;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends Activity implements Button.OnClickListener {

	private Button btn03, btn04, btn05;
	private ImageButton btn01, btn02;
	private PrintWriter out;
	private Socket socket;
	private DataOutputStream dout;
	/**
	 * 按下这个按钮进行的颜色过滤
	 */
	public final static float[] BT_SELECTED = new float[] { 2, 0, 0, 0, 2, 0,
			2, 0, 0, 2, 0, 0, 2, 0, 2, 0, 0, 0, 1, 0 };

	/**
	 * 按钮恢复原状的颜色过滤
	 */
	public final static float[] BT_NOT_SELECTED = new float[] { 1, 0, 0, 0, 0,
			0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };

	/**   
	   * 
	   */

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		// Gallery gallery = (Gallery) findViewById(R.id.gallery1);
		// gallery.setAdapter(new ImageAdapter(this)); //
		// gallery添加ImageAdapter图片资源
		// gallery.setOnItemClickListener(listener); // gallery设置点击图片资源的事件

		btn01 = (ImageButton) findViewById(R.id.button1);
		// btn01.getBackground().setAlpha(100);
		btn02 = (ImageButton) findViewById(R.id.button2);
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
		// Toast.makeText(getApplicationContext(), "fragment == null",
		// Toast.LENGTH_SHORT).show();
	}

	// AdapterView.OnItemClickListener listener = new
	// AdapterView.OnItemClickListener() {
	// @Override
	// public void onItemClick(AdapterView<?> parent, View view, int position,
	// long id) {
	// Toast.makeText(MainActivity.this, "图片 " + (position + 1),
	// Toast.LENGTH_SHORT).show();
	// }
	// };

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
		//	btn03.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_SELECTED ));   
			btn03.getBackground().setAlpha(255);	btn03.setBackgroundDrawable(btn03.getBackground());     
		//	btn04.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_NOT_SELECTED));  
			btn04.getBackground().setAlpha(150);	btn04.setBackgroundDrawable(btn04.getBackground());     
		//	btn05.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_NOT_SELECTED));   
			btn05.getBackground().setAlpha(150);	btn05.setBackgroundDrawable(btn05.getBackground());     
			break;
		case 4:
			new MySendCommondThread("fan 1").start();
			//btn03.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_NOT_SELECTED)); 
			btn03.getBackground().setAlpha(130);btn03.setBackgroundDrawable(btn03.getBackground());     
		//	btn04.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_SELECTED ));   
			btn04.getBackground().setAlpha(255);btn04.setBackgroundDrawable(btn04.getBackground());     
		//	btn05.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_NOT_SELECTED)); 
			btn05.getBackground().setAlpha(130);btn05.setBackgroundDrawable(btn05.getBackground());     
			break;
		case 5:
			new MySendCommondThread("fan 2").start();
		//	btn03.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_NOT_SELECTED));  
			btn03.getBackground().setAlpha(130);btn03.setBackgroundDrawable(btn03.getBackground());     
		//	btn04.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_NOT_SELECTED));  
			btn04.getBackground().setAlpha(130);btn04.setBackgroundDrawable(btn04.getBackground());      
		//	btn05.getBackground().setColorFilter(new ColorMatrixColorFilter(BT_SELECTED )); 
			btn05.getBackground().setAlpha(255);btn05.setBackgroundDrawable(btn05.getBackground());     
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
				socket = new Socket("192.168.10.1", 3333);
				out = new PrintWriter(socket.getOutputStream());
				out.print(commond + '\0');
				out.flush();
				// dout = new DataOutputStream(socket.getOutputStream());
				// String str="fuck you";
				// dout.writeChars(str);
				// dout.flush();
				out.close();
				socket.close();
			} catch (UnknownHostException e) {
			} catch (IOException e) {
				Log.d("ioerror", "");
			}
		}
	}
}
