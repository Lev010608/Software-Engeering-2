package xmljdbc;

import java.io.*;
import java.util.Properties;
import javax.xml.transform.OutputKeys;
import org.apache.xalan.lib.sql.ConnectionPoolManager;
import org.apache.xalan.lib.sql.DefaultConnectionPool;
import org.apache.xpath.XPathAPI;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.stream.StreamSource;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.dom.DOMSource;
import org.apache.xml.serializer.WriterToUTF8;


public class Sample1 {
  public Sample1() {
  }

  public static void main(String[] args) throws Exception{
    //��ʼ��һ�����ӳع�����
    ConnectionPoolManager cpMng=new ConnectionPoolManager();
    //����һ��Ĭ�ϵ����ӳ�
    DefaultConnectionPool cp = new DefaultConnectionPool();
    //�����ݿ��jdbc���������������ӳأ��˴���mysql��jdbc����
    cp.setDriver("org.gjt.mm.mysql.Driver");
    //�����ݿ��url�������ӳ�
    cp.setURL("jdbc:mysql://localhost/sppix");
    //�����ݿ�������û����������ӳ�
    cp.setUser("root");
    //�����ݿ�����������������ӳ�
    cp.setPassword("chenchen");
    //�������ӳ�
    cp.setMinConnections(10);
    //�������ӳصĿ���״̬
    cp.setPoolEnabled(true);
    //ע�����ӳص����ӳع�����
    cpMng.registerPool("sppixpool",cp);

    //��xml���߽���XSL�ļ�
    javax.xml.parsers.DocumentBuilderFactory dbf=javax.xml.parsers.DocumentBuilderFactory.newInstance();
    javax.xml.parsers.DocumentBuilder db=dbf.newDocumentBuilder();
    org.w3c.dom.Document doc=db.parse(Sample1.class.getResource("sample1.xsl").openStream());
    //ͨ��XPATH��XSL�ļ��е�·��Ϊ/stylesheet/param[@name="query"]�Ľڵ��ֵ�滻Ϊsql��ѯ���
    org.w3c.dom.Node node=XPathAPI.selectSingleNode(doc.getDocumentElement(),"/stylesheet/param[@name=\"query\"]");
    ((org.w3c.dom.Element)node).setAttribute("select","'select * from cat'");

    //����һ��transformer
    TransformerFactory tFactory = TransformerFactory.newInstance();

    DOMSource doms = new DOMSource (doc);


    Transformer transformer = tFactory.newTransformer();

    StringReader reader =
              new StringReader("<?xml version=\"1.0\"?> <doc/>");
    StringWriter writer=new StringWriter();
    //����޸ĺ��xsl��������StringWriter
    transformer.transform(doms,new StreamResult(writer));

    //����xsl�������������������ݿ��ѯ�����xml�ĵ�
    Transformer transformer1 = tFactory.newTransformer(
        new StreamSource(new StringReader(writer.toString())));
    //��ȡTransformser������������,�༴XSLT�����ȱʡ�������,����һ��
    //java.util.Properties����
    Properties properties = transformer1.getOutputProperties();

    //�����µ��������:����ַ�����ΪGB2312,��������֧�������ַ�,XSLT���������
    //��XML�ĵ���������������ַ�,����������ʾ,���������ν��"��������"��
    //������OutputKeys����ַ�������OutputKeys.ENCODING��
    properties.setProperty(OutputKeys.ENCODING,"UTF-8");
    properties.setProperty(OutputKeys.METHOD,"xml");

    //����XSLT�����������ԡ�
    transformer1.setOutputProperties(properties);


    transformer1.transform(new StreamSource(reader),
        new StreamResult(new FileOutputStream("result1.xml")));


  }

}
