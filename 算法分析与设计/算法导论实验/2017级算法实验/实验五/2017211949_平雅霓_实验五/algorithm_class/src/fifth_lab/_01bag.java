package fifth_lab;

public class _01bag {
	public static int V[][];
	public static void main(String[] args) {	
		int limited_weight=10;
		int w[] = {0,2,2,6,5,4};  //ÿ�����������
		int v[] = {0,6,3,5,4,6};  //ÿ������ļ�ֵ
		int V[][]= new int[6][11];
		for(int i=1;i<w.length;i++)
			for(int j=1;j<=limited_weight;j++) {
				if(j<w[i])
					V[i][j]=V[i-1][j];
				else 
					V[i][j]=Math.max(V[i-1][j], V[i-1][j-w[i]]+v[i]);
			}
		//��ӡ���
		for(int i=0;i<w.length;i++) {
			for(int j=0;j<=limited_weight;j++) {
				System.out.print(V[i][j]+"\t");
			}
			System.out.print("\n");
		}
		System.out.print("����ֵΪ"+V[w.length-1][limited_weight]);
	}
}
