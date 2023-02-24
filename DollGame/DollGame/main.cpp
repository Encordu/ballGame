#include"induct.h"
list propOnMap;
char map[numOfPatternY][numOfPatternX];
int time = 0;
int main()
{
	//隐藏控制台光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);

	sphere playerA = { 10,10,5,0,0,maxHP };
	sphere playerB = { width,height,5,0,0,maxHP };

	while (0)
	{
		//每帧开始，计数器自增
		time++;
		//先检测碰撞
		methodAfterScollision(&playerA, scollisionKind(playerA));
		methodAfterScollision(&playerB, scollisionKind(playerB));
		//检测与道具的碰撞情况
		listTest(&propOnMap, &playerA, &playerB);
		//移动
		double Ax=0, Ay=0;
		getAcceleration(playerA, playerB, &Ax, &Ay, 1);
		double ax=0, ay=0;
		getAcceleration(playerB, playerA, &ax, &ay, 2);
		move(&playerA,Ax,Ay);
		move(&playerB,ax,ay);
		moveATKprop(&propOnMap);
		//绘制图像
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

//玩法在群里讨论？
//可以。玩法出来了就可以找人做数值策划了。
//有一种好正常的感觉是怎么回事
