/*核心文件：存储重要方法

*/

//场景为(0,0)点,(width,0)点,(0,height)点,(width,height)点围成的长方形
#define CORE
void errorPrint(const char* massage)
{
	system("Cls");
	printf(massage);
	getchar();
}
struct sphere
{
	double x;//小球横坐标
	double y;//小球纵坐标
	double r;//小球半径
	double vx;//小球的横向分速度
	double vy;//小球的纵向分速度
	int hp;//小球的耐久度，“或者叫血量也行”
};
struct _object//表示性质各异的小球
{
	sphere transform;
	void (*methodAfterScollision)(sphere*);
	//(*a)()是函数指针的形式，指向一个有sphere参数，返回值为void的函数
};
struct List//链表
{
	_object* thisObject;
	struct List* next;
};
typedef struct sphere sphere;
typedef struct _object _object;
typedef struct List list;
/// <summary>平方，“似乎没有注释的必要”</summary>
double square(double a)
{
	return a * a;
}
/// <summary>检测碰壁，横向发生碰撞+2，纵向碰撞+1，返回0则无事发生。</summary>
int scollisionKind(sphere iru)
{
	int returnValur = 0;
	if (iru.x - iru.r <= 0 && iru.vx < 0)
	{
		returnValur += 2;
	}
	if (iru.x + iru.r >= width && iru.vx > 0)
	{
		returnValur += 2;
	}
	if (iru.y - iru.r <= 0 && iru.vy < 0)
	{
		returnValur++;
	}
	if (iru.y + iru.r >= height && iru.vy > 0)
	{
		returnValur++;
	}
	return returnValur;
}
/// <summary>用位运算实现了碰壁的检测并更新速度情况。</summary>
void methodAfterScollision(struct  sphere* iru, int scollisionKind)
{
	if ((scollisionKind & 2) == 2)
	{
		iru->vx *= -1;
	}
	if ((scollisionKind & 1) == 1)
	{
		iru->vy *= -1;
	}
}
/// <summary>
/// 检测是否接触到道具
/// </summary>
/// <param name="player">玩家控制的小球</param>
/// <param name="prop">道具</param>
/// <returns></returns>
int ifScollisionObject(sphere *player, _object *prop)
{
	double squareDistance = square(player->x - prop->transform.x) + square(player->y - prop->transform.y);
	if (squareDistance > square(player->r + prop->transform.r))
	{
		return 0;
	}
	return 1;
}
/// <summary>
/// 从道具列表里销毁道具
/// </summary>
/// <param name="PropList">道具列表的指针</param>
/// <param name="neededDestoryProp">指向需要销毁的道具的指针</param>
void destroyObject(list *PropList, _object* neededDestoryProp)
{
	if (PropList->thisObject = neededDestoryProp)
	{
		if (PropList->next == 0)
		{
			free(PropList->thisObject);
			return;
		}
		else
		{
			PropList->thisObject = PropList->next->thisObject;
			PropList->next = PropList->next->next;
			return;
		}
	}
	destroyObject(PropList->next, neededDestoryProp);
}
/// <summary>
/// 加载一个道具到列表中，加载的道具和传入数据一致
/// </summary>
/// <param name="list">道具列表</param>
/// <param name="prop">道具的属性</param>
void listAdd(list* proplist, _object prop)
{ 
	if (proplist->next == 0)
	{
		_object* neededAddprop = (_object*)calloc(1, sizeof(_object));
		proplist->thisObject = neededAddprop;
		proplist->next = (list*)calloc(1, sizeof(list));
	}
	else
	{
		listAdd(proplist->next, prop);
	}
}
/// <summary>
/// 每帧进行的移动操作
/// </summary>
/// <param name="player">玩家控制的小球</param>
/// <param name="Ax">小球的横向加速度</param>
/// <param name="Ay">小球的竖向加速度</param>
void move(sphere* player, double Ax,double Ay)
{
	player->x += player->vx * 0.001 * deltaT;
	player->y += player->vy * 0.001 * deltaT;
	player->vx += Ax *0.001* deltaT;
	player->vy += Ay *0.001* deltaT;
}
/// <summary>
/// 查找是否有与两球碰撞的道具，并根据情况执行后续操作
/// </summary>
/// <param name="propList">道具列表</param>
/// <param name="playerA">玩家A</param>
/// <param name="playerB">玩家B</param>
void listTest(list* propList, sphere* playerA, sphere* playerB)
{
	if (propList->thisObject == 0)
	{
		return;
	}
	int scolli = 0;
	if(ifScollisionObject(playerA,propList->thisObject))
	{
		propList->thisObject->methodAfterScollision(playerA);
		scolli++;
	}
	if (ifScollisionObject(playerB, propList->thisObject))
	{
		propList->thisObject->methodAfterScollision(playerB);
		scolli++;
	}
	if (scolli != 0)
	{
		destroyObject(propList, propList->thisObject);
	}
	if (propList->next != 0)
	{
		listTest(propList->next, playerA, playerB);
	}
}
void moveATKprop(list* propList)
{
	if (propList->thisObject == 0)
	{
		return;
	}
	if (propList->thisObject->transform.hp == 1)
	{
		move(&(propList->thisObject->transform), 0, 0);
	}
	if (propList->next == 0)
	{
		return;
	}
	moveATKprop(propList->next);
}
int usingXToGetXPattern(double x)
{
	return (int)(x * (numOfPatternX-1) / width);
}
int usingYToGetYPattern(double y)
{
	return (int)(y * (numOfPatternY-1) / height);
}