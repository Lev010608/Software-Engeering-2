package buptsse.client1;

public class WebServiceClient {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		StringOperationService service = new StringOperationService();
		StringOperationDelegate delegate = service.getStringOperationPort();
		
		// �ַ������
		System.out.print("\"XML&\" + \"&Web\" = ");
		System.out.println(delegate.addString("XML&", "&Web"));
		
		// �ַ����Ƚ�
		System.out.print("\"Hello\" == \"Hello\" = ");
		System.out.println(delegate.compareString("Hello", "Hello"));
	}
}
