package webservice.client;
import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import buptsse.StringOperation;

public class ServerInvoke {

	public static void main(String[] args) {
		try {
			// ����web service˵�����ַ
			URL url = new URL("http://localhost:8080/WebServiceProject/StringOperationPort?WSDL");
			
			// ָ�������ռ䣬��������ƣ����ö�λ���Ǹ�����
			QName serviceName = new QName("http://buptsse/", "StringOperationService");
			Service service = Service.create(url, serviceName);
			
			// ��ȡ�ӿڵ�ʵ��
			StringOperation stringOperation = service.getPort(new QName("http://buptsse/", "StringOperationPort"), 
					StringOperation.class);
			
			// ���ýӿ�
			String addString = stringOperation.AddString("XML", "Web");
			Boolean isEqual = stringOperation.CompareString("Hello", "Hello");
			
			// ������
			System.out.println("�ַ�����ӵĽ��Ϊ��" + addString);
			System.out.println("�ַ����ȽϵĽ��Ϊ��" + isEqual);
			
		}catch(Exception e) {
			System.out.println(e);
		}
	}
}
