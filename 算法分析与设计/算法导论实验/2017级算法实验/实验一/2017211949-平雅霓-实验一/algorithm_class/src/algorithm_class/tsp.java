package algorithm_class;
import java.util.ArrayList;

public class tsp {
	static double[][] cost_matrix= {
			{Double.POSITIVE_INFINITY,3,6,7},
			{12,Double.POSITIVE_INFINITY,2,8},
			{8,6,Double.POSITIVE_INFINITY,2},
			{3,7,6,Double.POSITIVE_INFINITY}};
	static char[] location= {'a','b','c','d'};
	static public double least_cost=Double.POSITIVE_INFINITY;
	static public int[] proposal= {0,0,0,0,0};
	static public void pringArray(int [] arr,int n){
		// ��ӡ����
		double cost=0;
		//��ӡÿ�ο�ѡ��·��
		System.out.print(location[arr[0]]+"->");
		for (int i = 1; i < arr.length; i++) {
			System.out.print(location[arr[i]]+"->");
		}
		System.out.print(location[arr[0]]);
		int j;
		for(j=0;j<3;j++) {
			cost+=cost_matrix[arr[j]][arr[j+1]];
		}
		cost+=cost_matrix[arr[j]][arr[0]];
		//�Ƚϣ���¼��С�Ĵ��۶�Ӧ��·��
		if(cost<least_cost) {
			least_cost=cost;
			proposal[0]=arr[0];
			proposal[1]=arr[1];
			proposal[2]=arr[2];
			proposal[3]=arr[3];
			proposal[4]=arr[0];
		}
		//��ӡÿ��·���Ĵ���
		System.out.print("\t"+cost+"\n");
	}
	static public void swap(int [] arr,int i,int j){
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	// ������arr����ȫ����
	static public void perum(int [] arr,int p){
		// �ݹ��������
		if(p == arr.length-1){
			//  ÿ�εݹ�����������������ӡ����
				pringArray( arr,arr.length);
		}
		// forѭ�������������е�Ԫ�غ͵�һ��Ԫ�ؽ��н�����Ȼ�����ȫ���С�
		for(int i =p ;i <= arr.length-1;i++){
			swap(arr,i,p);
			// ��ʣ�µ�Ԫ�ض���ȫ���С�
			perum(arr,p+1);
			// Ȼ���ٽ�����ȥ�����黹ԭ����֤��һ�β������ظ�������
			swap(arr,i,p);
		}
	}  
	public static void main(String[] args) {
		int index[]= {0,1,2,3};
		System.out.println("���п��ܵ�·��Ϊ��");
		perum(index,1);
		System.out.println("\n������Ϊ��");
		System.out.println(location[proposal[0]]+"->"+location[proposal[1]]+"->"
		+location[proposal[2]]+"->"+location[proposal[3]]+"->"+location[proposal[0]]);
		System.out.println("��С�ɱ�Ϊ��"+least_cost);
	}	
}
