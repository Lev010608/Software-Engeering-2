package fifth_lab;

public class subSequence {
	public static int count=0;
	public static void main(String[] args) {
		String S_[] = {"��Yahoo��Ʊ","��eBay��Ʊ","��Yahoo��Ʊ","��Oracle��Ʊ"};
		String S[] = {"��Yahoo��Ʊ","��Oracle��Ʊ"};	
		int j=0;

		for(int i=0;i<S.length;i++)
			for(;j<S_.length;) {
				if(S[i].equals(S[j])) {
					count++;
					break;
				}				
				j++;
			}
		if(count==S.length)
			System.out.println("S'��S��������");
		else {
			System.out.println("S'����S��������");
		}
	}
}
