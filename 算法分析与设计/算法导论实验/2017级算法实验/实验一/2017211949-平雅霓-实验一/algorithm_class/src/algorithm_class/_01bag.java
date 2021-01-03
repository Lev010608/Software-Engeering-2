package algorithm_class;
import java.util.ArrayList;

public class _01bag {
	static private int limited_weight=10;
	static ArrayList<ArrayList<Integer>> getSub(int args[])
	{
		ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<	Integer>>();
		ArrayList<Integer> subList = null;
		int max = 1 << args.length;  //����max��16��������Ϊ10000��

		for (int i = 0; i < max; i++)   //16���Ӽ�����ѭ�����
		{
			subList = new ArrayList<Integer>();   //����Ӽ�����
			int k = i;
			int index = 0;
			while (k > 0)  //k=0ʱ���Ӽ�Ϊ�ռ�
			{
				if ((k & 1) > 0)   //��k=14ʱ����ִ�� 
					subList.add(args[index]);
				k >>= 1;   //�жϴ�������������һλ�Ƿ�����Ӽ�����
				index++;
			}
			result.add(subList);
		}
		return result;
	}
	public static void main(String[] args) {
		int w1[]= {7,3,4,5};      //ÿ�����������
		int v1[]= {42,12,40,25};  //ÿ������ļ�ֵ
		int index[]= {1,2,3,4};   //����ı��
		int max_value=0;          //�����Ӽ����ܼ�ֵ���ļ�ֵ
		int proposal=0;           //��ֵ���ķ���������
		ArrayList<ArrayList<Integer>> list = null; //���������Ӽ�

		list = getSub(index);        //���ú������Ӽ�

		System.out.println("����\t"+"��ֵ"+"\t�Ƿ����\t\t"+"����");
		//���������Ӽ�����ÿ���Ӽ������������ܼ�ֵ����ѡ����ֵ���ķ���
		for (int i = 0; i < list.size(); i++)
		{
			int total_value=0;
			int total_weight=0;
			ArrayList<Integer> subList = list.get(i);          
			for(int j=0;j<subList.size();j++) {
				total_weight += w1[subList.get(j)-1];
				total_value += v1[subList.get(j)-1];
			}
			if(total_weight>limited_weight)     //�������������
				System.out.println(+total_weight+"\t"+total_value+"\t������\t\t"+subList.toString());
			else  		//���������δ����
			{
				System.out.println(total_weight+"\t"+total_value+"\t����\t\t"+subList.toString());
				//�Ƚ��ҳ��ܼ�ֵ���ķ���
				if(total_value>max_value) {
					max_value=total_value;
					proposal = i;
				}
			}

		}
		//��ӡ���
		System.out.print("\n��ѷ���Ϊ��");
		for(int i=0;i<list.get(proposal).size();i++) {
			System.out.print("��Ʒ"+(list.get(proposal).get(i))+"\t");
		}
		System.out.println("\n�ܼ�ֵΪ��"+max_value);
	}

}
