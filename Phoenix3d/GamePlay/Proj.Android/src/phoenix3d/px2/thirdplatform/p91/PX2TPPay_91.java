package phoenix3d.px2.thirdplatform.p91;

import phoenix3d.px2.library.PX2Activity;
import phoenix3d.px2.thirdplatform.PX2TP;
import android.app.Activity;
import android.util.Log;
import android.widget.Toast;

import com.nd.commplatform.NdCallbackListener;
import com.nd.commplatform.NdCommplatform;
import com.nd.commplatform.NdErrorCode;
import com.nd.commplatform.NdMiscCallbackListener;
import com.nd.commplatform.entry.NdAppInfo;
import com.nd.commplatform.entry.NdBuyInfo;
import com.nd.commplatform.entry.NdLoginStatus;
import com.nd.commplatform.entry.NdPayResultInfo;

import phoenix3d.px2.thirdplatform.*;

public class PX2TPPay_91
{
	private static PX2TPPay_91 Instance = null;
	private NdBuyInfo mBuyInfo = null;
	
	public static PX2TPPay_91 Instance ()
	{
		if (null == Instance)
			Instance = new PX2TPPay_91();
		
		return Instance;
	}
	
	private PX2TPPay_91 ()
	{
	}	
	
	public void SynPay (final NdBuyInfo buyinfo)
	{
		mBuyInfo = buyinfo;
	
		if (!CheckBuyInfoValied())
			return;
		
		int error = NdCommplatform.getInstance().ndUniPay(mBuyInfo, PX2Activity.TheActivity,
				new NdMiscCallbackListener.OnPayProcessListener() 
				{
					public void finishPayProcess (int code)
					{
						String serial = mBuyInfo.getSerial();
						
						if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) 
						{
							PX2TPNatives.OnPaySuc(serial, true);
						} 
						else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_FAILURE)
						{
							PX2TPNatives.OnPayFailed(serial, true);
						}
						else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_CANCEL) 
						{
							PX2TPNatives.OnPayCancel(serial, true);
						}
					}
				}
				);
		
		if (0 != error)
		{
			Toast.makeText(PX2Activity.TheActivity, "���������Ʒ��Ϣ��ʽ����ȷ", Toast.LENGTH_SHORT).show();
			PX2TPNatives.OnPayError(mBuyInfo.getSerial(), error, true);
		}
	}
	
	public void ASynPay (final NdBuyInfo buyinfo) 
	{
		mBuyInfo = buyinfo;		
		
		if (!CheckBuyInfoValied())
			return;

		int error = NdCommplatform.getInstance().ndUniPayAsyn(mBuyInfo,
				PX2Activity.TheActivity,
				new NdMiscCallbackListener.OnPayProcessListener() 
				{
					String serial = mBuyInfo.getSerial();

					public void finishPayProcess(int code)
					{
						if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) 
						{ // ����ɹ�����ʱ������ҷ��ŵ���
							Log.w("phoenix3d.px2", "PaySuc!");
							PX2TPNatives.OnPaySuc(serial, false);
							Toast.makeText(PX2Activity.TheActivity, "����ɹ�����������������Ʒ", Toast.LENGTH_SHORT).show();
						} 
						else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_FAILURE)
						{ // ����ʧ��
							Log.w("phoenix3d.px2", "PayFailure!");
							PX2TPNatives.OnPayFailed(serial, false);
							Toast.makeText(PX2Activity.TheActivity, "����ʧ��", Toast.LENGTH_SHORT).show(); 
						}
						else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_CANCEL) 
						{ // ȡ������
							Log.w("phoenix3d.px2", "PayCancel!");
							PX2TPNatives.OnPayCancel(serial, false);
							Toast.makeText(PX2Activity.TheActivity, "ȡ������", Toast.LENGTH_SHORT).show();							
						} 
						else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_ASYN_SMS_SENT)
						{
							// ��ʱ�û��˺����㣬ͨ�����ų�ֵ��������ߣ����ڶ�����ʱ��Ҫ��һ�ȷ�϶��ţ�
							// ���Կ�������Ҫ���¹���Ķ����ţ��Ա����������ѯ����Ƿ���ɹ��Ա�����ҷ��ŵ���
							Log.w("phoenix3d.px2", "PayAsyn_SMS_Sent!");
							PX2TPNatives.OnPaySMSSent(serial, false);
							Toast.makeText(PX2Activity.TheActivity, "�������ύ����ֵ�����ѷ���", Toast.LENGTH_SHORT).show();
						} 
						else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_PAY_REQUEST_SUBMITTED)
						{
							// ��ʱ�û��˺����㣬ͨ����ֵ��������ߣ�����ʱ���޷�֪����Ҵ˴ι����Ƿ�ɹ���
							// ���Կ�������Ҫ���¹���Ķ����ţ��Ա����������ѯ����Ƿ���ɹ��Ա�����ҷ��ŵ���
							Log.w("phoenix3d.px2", "PayResuestSub!");
							PX2TPNatives.OnPayRequestSubmitted(serial, false);
							Toast.makeText(PX2Activity.TheActivity, "�������ύ", Toast.LENGTH_SHORT).show();
						}
						else
						{
							Toast.makeText(PX2Activity.TheActivity, "����ʧ��" + code, Toast.LENGTH_SHORT).show(); 
						}

					}
				});
		
		if (0 != error)
		{
			Toast.makeText(PX2Activity.TheActivity, "���������Ʒ��Ϣ��ʽ����ȷ", Toast.LENGTH_SHORT).show();
			PX2TPNatives.OnPayError(mBuyInfo.getSerial(), error, false);
		}
	}
	
	public void CheckResult ()
	{
		String serial = mBuyInfo.getSerial();
		
		if (serial == null || serial.trim().equals("".trim())) 
		{
			return;
		}
		
		NdCallbackListener<NdPayResultInfo> callback = new NdCallbackListener<NdPayResultInfo>()
		{
			@Override
			public void callback(int responseCode, NdPayResultInfo t)
			{
				if (responseCode == NdErrorCode.ND_COM_PLATFORM_SUCCESS)
				{ // ��ѯ�ɹ�
					if (t.isSuccess())
					{
						Toast.makeText(PX2Activity.TheActivity, "����֧���ɹ�,��Ʒ����Ϊ��" + t.getGoodsName(), Toast.LENGTH_SHORT).show();
					}
					else 
					{
						Toast.makeText(PX2Activity.TheActivity, "����֧��ʧ��", Toast.LENGTH_SHORT).show();
					}
				}
				else if (responseCode == NdErrorCode.ND_COM_PLATFORM_ERROR_UNEXIST_ORDER) 
				{ // �޴˶���
					Toast.makeText(PX2Activity.TheActivity, "�޴˶���", Toast.LENGTH_SHORT).show();
				} 
				else
				{
					Toast.makeText(PX2Activity.TheActivity, "��ѯʧ�ܣ������룺" + responseCode, Toast.LENGTH_SHORT).show();
				}
			}
		};		
		NdCommplatform.getInstance().ndSearchPayResultInfo(serial, PX2Activity.TheActivity, callback);
	}	
	
	public boolean CheckBuyInfoValied ()
	{
		if (null == mBuyInfo)
			return false;
		
		String serial = mBuyInfo.getSerial();
		double price = mBuyInfo.getProductPrice();
		int amount = mBuyInfo.getCount();
		
		if (null==serial || serial.trim().equals("".trim()))
		{
			Toast.makeText(PX2Activity.TheActivity, "�����Ų���Ϊ��", Toast.LENGTH_SHORT).show();
			return false;
		}
		
		if (price < 0.01)
		{
			Toast.makeText(PX2Activity.TheActivity, "��Ʒ���۲���С��0.01��91��", Toast.LENGTH_SHORT).show();
			return false;
		}
		
		if (amount < 1)
		{
			Toast.makeText(PX2Activity.TheActivity, "���������Ʒ��������С��1", Toast.LENGTH_SHORT).show();
			return false;
		}
		
		double allPrice = price * amount;
		if (allPrice > 1000000)
		{
			Toast.makeText(PX2Activity.TheActivity, "���ʽ��׶�ܴ���1000000��91��", Toast.LENGTH_SHORT).show();
			return false;
		}
		
		return true;
	}
}
