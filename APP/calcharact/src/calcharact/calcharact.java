package calcharact;

import java.util.Scanner;

public class calcharact {
	public static void main(String[] args) {
		//输入特征文件
		//提取出特征点信息P(x, y, d, t)
		System.out.println("Beigin");
		
		while(true) {
			Scanner in = new Scanner(System.in);
			
			System.out.println("输入：");
			
			String charc = in.nextLine();
			String charct = charc.replace(" ", "");
			System.out.println("处理1：" + charct);
			
			
			Integer charc1 = Integer.parseInt(charct, 16);
			Integer x =  charc1/8388608;
			Integer y =  charc1%8388608/16384;
			Integer t = charc1%2;
			System.out.println("X：" + x);
			System.out.println("Y：" + y);
			System.out.println("t：" + t);
		}

	}

}
