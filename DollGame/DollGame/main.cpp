#include"induct.h"
list propOnMap;
char map[numOfPatternY][numOfPatternX];
int time = 0;
int main()
{
	//���ؿ���̨���
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);

	sphere playerA = { 10,10,5,0,0,maxHP };
	sphere playerB = { width,height,5,0,0,maxHP };

	while (0)
	{
		//ÿ֡��ʼ������������
		time++;
		//�ȼ����ײ
		methodAfterScollision(&playerA, scollisionKind(playerA));
		methodAfterScollision(&playerB, scollisionKind(playerB));
		//�������ߵ���ײ���
		listTest(&propOnMap, &playerA, &playerB);
		//�ƶ�
		double Ax=0, Ay=0;
		getAcceleration(playerA, playerB, &Ax, &Ay, 1);
		double ax=0, ay=0;
		getAcceleration(playerB, playerA, &ax, &ay, 2);
		move(&playerA,Ax,Ay);
		move(&playerB,ax,ay);
		moveATKprop(&propOnMap);
		//����ͼ��
		Sleep(deltaT);
		system("Cls");
		incipientMap(map);
		drawBoundaries(map);
		addCirularToMap(map, playerA);
		addCirularToMap(map, playerB);
		printPattern(map);
		if (playerA.x >= 100)
		{
			system("Cls");
			printf("%d %lf", time, playerA.vx);
			return 0;
		}
	}
}

//�淨��Ⱥ�����ۣ�
//���ԡ��淨�����˾Ϳ�����������ֵ�߻��ˡ�
//��һ�ֺ������ĸо�����ô����
