#include "Fuzzy.h"

float Fuzzy(float P, float D,int symbol)
{
	/*������P����ֵ������*/
	float PFF[7] = { -500,-350,-200,0,200,350,500 };
	/*������D����ֵ������*/
	//float DFF[5] = { -50,-25,0,25,50 };
	float DFF[7] = { -50,-25,-10,0,10,25,50 };
	/*�����U����ֵ������(������������ѡ��ͬ�����ֵ)*/
	//	float UPFF[7] = { 0,20,40,60,70,80,90 };
	float UPFF[7] = { 20,40,50,60,70,80,90 };

	//float UDFF[7] = { 55,60,68,75,80,85,90 };
	float UDFF[7] = { 60,65,70,75,80,85,90 };

	int P_rule[7][7] = {


		//  -3  -2   -1   0   1   2   3 ec 
 
		//  -3  -2   -1   0   1   2   3 ec 
		////  e
		{ 5,  5,  4,  4,  4,  2,  2 }, //  -3
		{ 5,  4,  4,  4,  3,  2,  3 }, //  -2
		{ 4,  4,  4,  3,  2,  3,  3 }, //  -1
		{ 4,  4,  4,  4,  4,  4,  4 }, //  0
		{ 3,  3,  2,  3,  4,  4,  4 }, //  1
		{ 3,  2,  3,  4,  4,  4,  5 }, //  2
		{ 2,  2,  4,  4,  4,  5,  5 }  //   3

	};

	int D_rule[7][5] = {

		//// -2  -1   0   1   2 ec 
		////  e
		{ 6,  5,  3,  3,  2 }, //  -3
		{ 5,  4,  2,  2,  2 }, //  -2
		{ 4,  4,  2,  2,  2 }, //  -1
		{ 3,  2,  1,   2,  3 }, //   0
		{ 2,  2,  2,  3,  4 }, //   1
		{ 2,  2,  2,  4,  5 }, //   2
		{ 2,  3,  3,  5,  6 }  //   3


	};


	//


	float U = 0;  /*ƫ��,ƫ��΢���Լ����ֵ�ľ�ȷ��*/
	float PF[2] = { 0 }, DF[2] = { 0 }, UF[4] = { 0 };
	/*ƫ��,ƫ��΢���Լ����ֵ��������*/
	int Pn = 0, Dn = 0, Un[4] = { 0 };
	float t1 = 0, t2 = 0, t3 = 0, t4 = 0, temp1 = 0, temp2 = 0;
	/*�����ȵ�ȷ��*/
	/*����PD��ָ������ֵ�����Ч������*/
	if (P>PFF[0] && P<PFF[6])
	{
		if (P <= PFF[1])
		{
			Pn = -2;
			PF[0] = (PFF[1] - P) / (PFF[1] - PFF[0]);
		}
		else if (P <= PFF[2])
		{
			Pn = -1;
			PF[0] = (PFF[2] - P) / (PFF[2] - PFF[1]);
		}
		else if (P <= PFF[3])
		{
			Pn = 0;
			PF[0] = (PFF[3] - P) / (PFF[3] - PFF[2]);
		}
		else if (P <= PFF[4])
		{
			Pn = 1;
			PF[0] = (PFF[4] - P) / (PFF[4] - PFF[3]);
		}
		else if (P <= PFF[5])
		{
			Pn = 2;
			PF[0] = (PFF[5] - P) / (PFF[5] - PFF[4]);
		}
		else if (P <= PFF[6])
		{
			Pn = 3;
			PF[0] = (PFF[6] - P) / (PFF[6] - PFF[5]);
		}
	}

	else if (P <= PFF[0])
	{
		Pn = -2;
		PF[0] = 1;
	}
	else if (P >= PFF[6])
	{
		Pn = 3;
		PF[0] = 0;
	}

	PF[1] = 1 - PF[0];


	//�ж�D��������

	if (D>DFF[0] && D<DFF[6])
	{
		if (D <= DFF[1])
		{
			Dn = -2;
			DF[0] = (DFF[1] - D) / (DFF[1] - DFF[0]);
		}
		else if (D <= DFF[2])
		{
			Dn = -1;
			DF[0] = (DFF[2] - D) / (DFF[2] - DFF[1]);
		}
		else if (D <= DFF[3])
		{
			Dn = 0;
			DF[0] = (DFF[3] - D) / (DFF[3] - DFF[2]);
		}
		else if (D <= DFF[4])
		{
			Dn = 1;
			DF[0] = (DFF[4] - D) / (DFF[4] - DFF[3]);
		}
		else if (D <= DFF[5])
		{
			Dn = 2;
			DF[0] = (DFF[5] - D) / (DFF[5] - DFF[4]);
		}
		else if (D <= DFF[6])
		{
			Dn = 3;
			DF[0] = (DFF[6] - D) / (DFF[6] - DFF[5]);
		}
	}

	else if (D <= DFF[0])
	{
		Dn = -2;
		DF[0] = 1;
	}
	else if (D >= DFF[6])
	{
		Dn = 3;
		DF[0] = 0;
	}

	DF[1] = 1 - DF[0];

	/*ʹ����Χ�Ż���Ĺ����P_rule[7][7]*/
	/*���ֵʹ��13����������,����ֵ��UPFF[7]ָ��*/
	/*һ�㶼���ĸ�������Ч*/

	//���ڹ����ǽ������ŵ�
	if (symbol == 0)
	{
		Un[0] = P_rule[Pn - 1 + 3][Dn - 1 + 3];
		Un[1] = P_rule[Pn + 3][Dn - 1 + 3];
		Un[2] = P_rule[Pn - 1 + 3][Dn + 3];
		Un[3] = P_rule[Pn + 3][Dn + 3];
	}
	else
	{
		Un[0] = D_rule[Pn - 1 + 3][Dn - 1 + 3];
		Un[1] = D_rule[Pn + 3][Dn - 1 + 3];
		Un[2] = D_rule[Pn - 1 + 3][Dn + 3];
		Un[3] = D_rule[Pn + 3][Dn + 3];
	}




	//���Ӧ�õ�ֵģ������ö�Ӧ�������������
	if (PF[0] <= DF[0])    //��С ����U�������ȣ�
		UF[0] = PF[0];
	else
		UF[0] = DF[0];
	if (PF[1] <= DF[0])
		UF[1] = PF[1];
	else
		UF[1] = DF[0];
	if (PF[0] <= DF[1])
		UF[2] = PF[0];
	else
		UF[2] = DF[1];
	if (PF[1] <= DF[1])
		UF[3] = PF[1];
	else
		UF[3] = DF[1];


	/*ͬ���������������ֵ���*/
	if (Un[0] == Un[1])      //����ȵ�����ֵ�������Ƚ��д���
	{
		if (UF[0]>UF[1])
			UF[1] = 0;
		else
			UF[0] = 0;
	}
	if (Un[0] == Un[2])
	{
		if (UF[0]>UF[2])
			UF[2] = 0;
		else
			UF[0] = 0;
	}
	if (Un[0] == Un[3])
	{
		if (UF[0]>UF[3])
			UF[3] = 0;
		else
			UF[0] = 0;
	}
	if (Un[1] == Un[2])
	{
		if (UF[1]>UF[2])
			UF[2] = 0;
		else
			UF[1] = 0;
	}
	if (Un[1] == Un[3])
	{
		if (UF[1]>UF[3])
			UF[3] = 0;
		else
			UF[1] = 0;
	}
	if (Un[2] == Un[3])
	{
		if (UF[2]>UF[3])
			UF[3] = 0;
		else
			UF[2] = 0;
	}



	if (symbol == 0)
	{
		t1 = UF[0] * UPFF[Un[0]];
		t2 = UF[1] * UPFF[Un[1]];
		t3 = UF[2] * UPFF[Un[2]];
		t4 = UF[3] * UPFF[Un[3]];
	}
	else
	{
		t1 = UF[0] * UDFF[Un[0]];
		t2 = UF[1] * UDFF[Un[1]];
		t3 = UF[2] * UDFF[Un[2]];
		t4 = UF[3] * UDFF[Un[3]];
	}

	temp1 = t1 + t2 + t3 + t4;
	temp2 = UF[0] + UF[1] + UF[2] + UF[3];//ģ�������
	U = temp1 / temp2;
	return U;
}
