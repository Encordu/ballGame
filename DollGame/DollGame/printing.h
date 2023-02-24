//一个用于显示画面，并提供修改函数的库
#define PRINTING
void printPattern(char map[numOfPatternY][numOfPatternX])//输出map中的所有元素。
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
//对map做一些修改，使其printPattern后出现球形
void addCirularToMap(char map[numOfPatternY][numOfPatternX], sphere irular)//以小球的信息，将小球显示在map中。
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
//Line函数的独有函数，检测纵坐标是否合法。
int isSafeY(int y)
{
	if (y >= 0 && y <= width)
	{
		return 1;
	}
	return 0;
}
void Line(char map[numOfPatternY][numOfPatternX],int x1,int y1,int x2,int y2)//未知内容      
{
	if (isSafeX(x1) + isSafeX(x2) + isSafeY(y1) + isSafeY(y2) != 4)
	{
		errorPrint("Line函数中数据超过限定值");
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
//Line函数的独有函数，检测横坐标是否合法。

char getTag(_object);
//在地图中标记道具球
void addTagWithObject(char map[numOfPatternY][numOfPatternX], _object kind)
{
	char Tag = getTag(kind);
	if (Tag == 0)
	{
		errorPrint("出现未定义的道具球");
	}
	int y = usingYToGetYPattern(kind.transform.y);
	int x = usingXToGetXPattern(kind.transform.x);
	if (y < numOfPatternY && y >= 0 && x < numOfPatternX && x >= 0)
	{
		map[y][x] = Tag;
		return;
	}
	errorPrint("标记超出边界外。");
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
	errorPrint("标记超出边界外。");
}
void drawBoundaries(char map[numOfPatternY][numOfPatternX])
{
	Line(map, 0, 0, width, 0);
	Line(map, 0, 0, 0, height);
	Line(map, 0, height, width, height);
	Line(map, width, 0, width, height);
}
void incipientMap(char map[numOfPatternY][numOfPatternX])//清空map，“一切元素，终将归于空格”
{
	for (int i = 0; i < numOfPatternY; i++)
	{
		for (int j = 0; j < numOfPatternX; j++)
		{
			map[i][j] = ' ';
		}
	}
}
