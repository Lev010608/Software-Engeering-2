package algorithm_class;


/*����ƥ������*/
public class marriage_match {
	public static void main(String[] args) {
		String[][] data = {{"Xavier","Yancey","Zeus"},{"Amy","Bertha","Clare"}};
		int men_pre[][]= {{0,1,2},{1,0,2},{0,1,2}};  //��λ����ϲ����Ů������
		int women_pre[][]= {{1,0,2},{0,1,2},{0,1,2}};  //��λŮ��ϲ������������
		int current_girlfriend[]= {-1,-1,-1};  //������ǰ�Ƿ���Ů����
		int current_boyfriend[]= {-1,-1,-1};   //Ů����ǰ�Ƿ���������
		int manIndex[]= {0,0,0};  //��¼�������ܾ���Ӧ��ѡ���Ů����

		boolean manSingle=false;  //��������������
		int i,j,m,w;
		
		//�����Ե�����һֱѭ��
		while(!manSingle) {
			manSingle=true;
			for(i=0;i<3;i++){
				if(current_girlfriend[i]!=-1) // �������i�Ѿ�����Ů����
					continue;
				manSingle=false;
				j=manIndex[i]++; // ����i���ڸ�ѡ��ϲ�������еĵ�j��Ů��
				w=men_pre[i][j];    //��j��Ů���ǵ�w��
				m= current_boyfriend[w];    //Ů��w���ڵ�������m
				if(m==-1 || women_pre[w][i]<women_pre[w][m]){ // ���Ů��wû�������ѻ��߸�ϲ������i
					current_boyfriend[w]=i;
					current_girlfriend[i]=w;
					if(m!=-1)  //���Ů��Ҫ���������ѣ���ǰ���ѵ�ǰ��Ů������Ϊ-1
						current_girlfriend[m]=-1;
				}
			}
		}
		for(i=0;i<3;i++) {
			System.out.println(data[0][i]+"����"+data[1][current_girlfriend[i]]);
		}
	}
}
