//һ��������ʾ���棬���ṩ�޸ĺ����Ŀ�
#define PRINTING
void printPattern(char map[numOfPatternY][numOfPatternX])//���map�е�����Ԫ�ء�
{
	for (int i = numOfPatternY-1; i >=0; i--)
	{
		for (int j =0; j < numOfPatternX; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}
//��map��һЩ�޸ģ�ʹ��printPattern���������
void addCirularToMap(char map[numOfPatternY][numOfPatternX], sphere irular)//��С�����Ϣ����С����ʾ��map�С�
{
	double lengthOfEveryBlockX = width / numOfPatternX;
	double lengthOfEveryBlockY = height / numOfPatternY;
	for (int i = 0; i < numOfPatternY; i++)
	{
		for (int j = 0; j < numOfPatternX; j++)
		{
			double usingX = (j + 0.5) * lengthOfEveryBlockX;
			double usingY = (i + 0.5) * lengthOfEveryBlockY;
			if (square(usingX - irular.x) + square(usingY - irular.y) <= square(irular.r))
			{
				map[i][j] = '*';
			}
		}
	}
}
int isSafeX(int x)
{
	if (x >= 0 && x <= width)
	{
		return 1;
	}
	return 0;
}
//Line�����Ķ��к���������������Ƿ�Ϸ���
int isSafeY(int y)
{
	if (y >= 0 && y <= width)
	{
		return 1;
	}
	return 0;
}
void Line(char map[numOfPatternY][numOfPatternX],int x1,int y1,int x2,int y2)//δ֪����      
{
	if (isSafeX(x1) + isSafeX(x2) + isSafeY(y1) + isSafeY(y2) != 4)
	{
		errorPrint("Line���������ݳ����޶�ֵ");
	}
	if (x1 == x2)
	{
		int numX = usingXToGetXPattern(x1);
		if (y2 > y1)
		{
			for (int i = y1; i < y2; i++)
			{
				int numY = usingYToGetYPattern(i);
				map[numY][numX] = '*';
			}
		}
		else
		{
			for (int i = y2; i < y1; i++)
			{
				int numY = usingYToGetYPattern(i);
				map[numY][numX] = '*';
			}
		}
		return;
	}
	if (x1 > x2)
	{
		for(int i = x2;  i<=x1; i++)
		{
			int UsedX = usingXToGetXPattern(i);
			int UsedY = usingYToGetYPattern(y2 + (i - x2) *(y1 - y2)/(x1-x2));
			map[UsedY][UsedX] = '*';
		}
	}
	else
	{
		Line(map, x2, y2, x1, y1);
	}
}
//Line�����Ķ��к��������������Ƿ�Ϸ���

char getTag(_object);
//�ڵ�ͼ�б�ǵ�����
void addTagWithObject(char map[numOfPatternY][numOfPatternX], _object kind)
{
	char Tag = getTag(kind);
	if (Tag == 0)
	{
		errorPrint("����δ����ĵ�����");
	}
	int y = usingYToGetYPattern(kind.transform.y);
	int x = usingXToGetXPattern(kind.transform.x);
	if (y < numOfPatternY && y >= 0 && x < numOfPatternX && x >= 0)
	{
		map[y][x] = Tag;
		return;
	}
	errorPrint("��ǳ����߽��⡣");
}
void addTag(char map[numOfPatternY][numOfPatternX], char Tag,sphere player)
{
	int y = usingYToGetYPattern(player.y);
	int x = usingXToGetXPattern(player.x);
	if (y < numOfPatternY && y >= 0 && x < numOfPatternX && x >= 0)
	{
		map[y][x] = Tag;
		return;
	}
	errorPrint("��ǳ����߽��⡣");
}
void drawBoundaries(char map[numOfPatternY][numOfPatternX])
{
	Line(map, 0, 0, width, 0);
	Line(map, 0, 0, 0, height);
	Line(map, 0, height, width, height);
	Line(map, width, 0, width, height);
}
void incipientMap(char map[numOfPatternY][numOfPatternX])//���map����һ��Ԫ�أ��ս����ڿո�
{
	for (int i = 0; i < numOfPatternY; i++)
	{
		for (int j = 0; j < numOfPatternX; j++)
		{
			map[i][j] = ' ';
		}
	}
}
