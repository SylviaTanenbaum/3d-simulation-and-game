package phoenix3d.px2.thirdplatform;

import java.util.UUID;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import phoenix3d.px2.gameplay.PX2GamePlayActivity;
import phoenix3d.px2.thirdplatform.PX2TPNatives;

public abstract class PX2TP 
{
	public static PX2TP Instance = null;

	public static String PaySource;
	public static String PayHostName;
	public static String Source;
		
	public static Activity TheTPActivity;
	private static String mSerial;
	
	public PX2TP (Activity activity)
	{
		TheTPActivity = activity;
	}
	
	public abstract void InitGame ();
	
	// �ͷ�ƽ̨sdk
	public abstract void Term ();
	
	// �Ӻ�̨�л���ǰ̨
	public abstract void OnResume ();
	
	// back�����Ƴ�
	public abstract void OnExist ();
	public abstract void OnLogoutExist ();
	
	// �ο͵�¼
	public abstract void GuestLogin ();
	
	// ��¼
	public abstract void Login ();
	public abstract boolean IsLogin ();
	
	// �ǳ�
	public abstract void Logout();
	
	// ����			
	public abstract void SynPay (
			String productID,
			String productName,
			float productPrice,
			float productOrginalPrice,
			int count,
			String payDescription);
	
	public abstract void ASynPay (
			String productID,
			String productName,
			float productPrice,
			float productOrginalPrice,
			int count,
			String payDescription);
	
	String GetSerial ()
	{
		return mSerial;
	}
	
	public String MakeSerial() 
	{//���ɶ����� 
		UUID guid = UUID.randomUUID(); 
		String text = guid.toString(); 
		text = text.replace("-", "".trim()); 
		
		mSerial = text;
		
		return mSerial;
	}
}
