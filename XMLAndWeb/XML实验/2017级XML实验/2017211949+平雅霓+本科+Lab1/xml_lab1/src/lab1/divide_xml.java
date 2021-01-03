package lab1;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.xml.parsers.*;
import org.w3c.dom.*;
import org.w3c.dom.Node;

public class divide_xml {

	static String displayText[] = new String[1500];
	static int numberLines = 0;
	static FileOutputStream outputStream_IBM = null;
	static FileOutputStream outputStream_ABC = null;

	public static void main(String[] args) {
		try {
			// ����һ��DocumentBuilderFactory
			DocumentBuilderFactory factory =
					DocumentBuilderFactory.newInstance();

			DocumentBuilder builder = null;
			try {
				//ʹ��DocumentBuilderFactory�õ�һ��DocumentBuilder����
				builder = factory.newDocumentBuilder();
			}
			catch (ParserConfigurationException e) {}

			Document document = null;

			//ʹ��DocumentBuilder�������xml�ļ����õ�һ��Document����
			document = builder.parse("src/lab1/ipo.xml");

			//��ͬ��Ŀ¼����ABC_COMP.xml�ļ�
			File file_ABC = new File("src/lab1/ABC_COMP.xml");
			file_ABC.createNewFile();
			outputStream_ABC = new FileOutputStream(file_ABC);

			//��ͬ��Ŀ¼����IBM_COMP.xml�ļ�
			File file_IBM = new File("src/lab1/IBM_COMP.xml");
			file_IBM.createNewFile();
			outputStream_IBM = new FileOutputStream(file_IBM);
			
			//��XML�ļ��ĵ�һ��������ļ���
			String data_ABC = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+"\n"
					+"<purchaseOrders>"+"\n"+"<ABC_COMP>"+"\n";
			String data_IBM = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"+"\n"
					+"<purchaseOrders>"+"\n"+"<IBM_COMP>"+"\n";
			outputStream_ABC.write(data_ABC.getBytes());
			outputStream_IBM.write(data_IBM.getBytes());

			//�ݹ����
			childLoop(document, "","");

			//��XML�ļ��Ľ�������������ļ���
			data_ABC ="</ABC_COMP>\n" + "</purchaseOrders>";
			data_IBM = "</IBM_COMP>\r\n" + "</purchaseOrders>";
			outputStream_ABC.write(data_ABC.getBytes());
			outputStream_IBM.write(data_IBM.getBytes());

			//�ر��ļ������
			outputStream_ABC.close();
			outputStream_IBM.close();
			
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}      	
		
		System.out.println("Done!");
	}
	
	
	//���ļ�������ݵĺ���
	public static void outputstream(String type,String data) throws IOException {
		
		//type�ж�����ABC_COMP�ļ��������IBM_COMP�ļ����
		if(type.equals("ABC")) {
			outputStream_ABC.write(data.getBytes());
			outputStream_ABC.write("\n".getBytes());
		}
		else if(type.equals("IBM")) {
			outputStream_IBM.write(data.getBytes());
			outputStream_IBM.write("\n".getBytes());
		}
	}

	//�ݹ�����ӽڵ�
	public static void childLoop(Node node, String indentation,String outputtype) throws IOException
	{
		if (node == null) {
			return;
		}

		int type = node.getNodeType();

		switch (type) {
		case Node.DOCUMENT_NODE: {
			NodeList rootList = (NodeList) node.getChildNodes(); 
			for(int i=0;i<rootList.getLength();i++)
				if(rootList.item(i).getNodeName()=="purchaseOrders") {
					//rootΪ<purchaseOrders>��Ԫ��
					Node root = rootList.item(i);
					//���<purchaseOrders>��������Ԫ��
					NodeList purchaseList = (NodeList) root.getChildNodes(); 
					//�ҳ�<purchaseOrders>������<purchaseOrder>��Ԫ��
					for(int j=0;j<purchaseList.getLength();j++) {
						if(purchaseList.item(j).getNodeName().equals("purchaseOrder")){ 
							//���purchaseOrder������
							Attr attr =(Attr)purchaseList.item(j).getAttributes().item(0);
							//��purchaseOrder������ֵΪABC�򴫵ݲ�����ABC�����ļ�д��ABC_COMP.xml�ļ�
							if(attr.getNodeValue().equals("ABC")) {
								outputStream_ABC.write(new String("<purchaseOrder>\n").getBytes());
								NodeList childList = (NodeList)purchaseList.item(j).getChildNodes(); 	
								for(int k=0;k<childList.getLength();k++)
									childLoop(childList.item(k), "    ","ABC");
								outputStream_ABC.write(new String("</purchaseOrder>\n").getBytes());
							}
							//��purchaseOrder������ֵΪIBM���򴫵ݲ�����IBM�����ļ�д��IBM_COMP.xml�ļ�
							else if(attr.getNodeValue().equals("IBM")) {
								outputStream_IBM.write(new String("<purchaseOrder>\n").getBytes());
								NodeList childList = (NodeList) purchaseList.item(j).getChildNodes(); 	
								for(int k=0;k<childList.getLength();k++)
									childLoop(childList.item(k), "    ","IBM");
								outputStream_IBM.write(new String("</purchaseOrder>\n").getBytes());
							}
						}
					}
				}
			break;
		}

		case Node.ELEMENT_NODE: {
			//�����Ԫ��
			displayText[numberLines] = indentation;
			displayText[numberLines] += "<";
			displayText[numberLines] += node.getNodeName();
			displayText[numberLines] += ">";
			//�����Ԫ�غ�����Ԫ�أ�����ʼ��ǩ���뵽�ļ��У���ռһ��
			//����������Ԫ�أ�����ʼ��ǩ�����ݡ���ֹ��ǩ��ͬһ�У�ֱ��������ֹ��ǩʱ��д���ļ�
			if(node.getChildNodes().getLength()!=1)
				outputstream(outputtype, displayText[numberLines]);
			
			int length = (node.getAttributes() != null) ?
					node.getAttributes().getLength() : 0;
					
					//�����������
					Attr attributes[] = new Attr[length];
					for (int loopIndex = 0; loopIndex < length; loopIndex++) {
						attributes[loopIndex] =
								(Attr)node.getAttributes().item(loopIndex);
					}
					
					//������ת��ΪԪ�����
					for (int loopIndex = 0; loopIndex < attributes.length;
							loopIndex++) {
						numberLines++;
						Attr attribute = attributes[loopIndex];
						displayText[numberLines] =  "    ";
						displayText[numberLines] += indentation;
						displayText[numberLines] += "<";
						displayText[numberLines] += attribute.getNodeName();
						displayText[numberLines] += ">";				
						displayText[numberLines] += attribute.getNodeValue();
						displayText[numberLines] += "</";
						displayText[numberLines] += attribute.getNodeName();
						displayText[numberLines] += ">";
						outputstream(outputtype, displayText[numberLines]);
					}
					
					//�����Ԫ��ӵ����Ԫ�أ�������+1����Ԫ��д���ļ�����һ��
					if(node.getChildNodes().getLength()!=1)
						numberLines++;
					NodeList childNodes = node.getChildNodes();
					if (childNodes != null) {
						length = childNodes.getLength();						
						indentation += "    ";
						for (int loopIndex = 0; loopIndex < length; loopIndex++ ) {
							childLoop(childNodes.item(loopIndex), indentation,outputtype);
						}
					}
					break;
		}

		case Node.TEXT_NODE: {
			String trimmedText = node.getNodeValue().trim();
			if(trimmedText.indexOf("\n") < 0 && trimmedText.length() > 0){
				displayText[numberLines] += trimmedText;
			}
			break;
		}


		case Node.CDATA_SECTION_NODE: {
			displayText[numberLines] = indentation;
			displayText[numberLines] += "<![CDATA[";
			displayText[numberLines] += node.getNodeValue();
			displayText[numberLines] += "]]>";
			outputstream(outputtype, displayText[numberLines]);
			numberLines++;
			break;
		}
		}

		if (type == Node.ELEMENT_NODE) {
			//�����Ԫ��û����Ԫ�أ�������Ԫ������ֹ��ǩ����д�뵽�ļ���
			if(node.getChildNodes().getLength()==1) {
				displayText[numberLines] += "</";
				displayText[numberLines] += node.getNodeName();
				displayText[numberLines] += ">";
				outputstream(outputtype, displayText[numberLines]);
				numberLines++;
				indentation += "    ";
			}
			//�����Ԫ������Ԫ�أ���ֹ��ǩ���ļ��ж�ռһ��
			else {
				displayText[numberLines] = indentation.substring(0,
						indentation.length() - 4);
				displayText[numberLines] += "</";
				displayText[numberLines] += node.getNodeName();
				displayText[numberLines] += ">";
				outputstream(outputtype, displayText[numberLines]);
				numberLines++;
				indentation += "    ";
			}		
		}
	}

}
