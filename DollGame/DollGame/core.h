/*�����ļ����洢��Ҫ����

*/

//����Ϊ(0,0)��,(width,0)��,(0,height)��,(width,height)��Χ�ɵĳ�����
#define CORE
void errorPrint(const char* massage)
{
	system("Cls");
	printf(massage);
	getchar();
}
struct sphere
{
	double x;//С�������
	double y;//С��������
	double r;//С��뾶
	double vx;//С��ĺ�����ٶ�
	double vy;//С���������ٶ�
	int hp;//С����;öȣ������߽�Ѫ��Ҳ�С�
};
struct _object//��ʾ���ʸ����С��
{
	sphere transform;
	void (*methodAfterScollision)(sphere*);
	//(*a)()�Ǻ���ָ�����ʽ��ָ��һ����sphere����������ֵΪvoid�ĺ���
};
struct List//����
{
	_object* thisObject;
	struct List* next;
};
typedef struct sphere sphere;
typedef struct _object _object;
typedef struct List list;
/// <summary>ƽ�������ƺ�û��ע�͵ı�Ҫ��</summary>
double square(double a)
{
	return a * a;
}
/// <summary>������ڣ���������ײ+2��������ײ+1������0�����·�����</summary>
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
/// <summary>��λ����ʵ�������ڵļ�Ⲣ�����ٶ������</summary>
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
/// ����Ƿ�Ӵ�������
/// </summary>
/// <param name="player">��ҿ��Ƶ�С��</param>
/// <param name="prop">����</param>
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
/// �ӵ����б������ٵ���
/// </summary>
/// <param name="PropList">�����б��ָ��</param>
/// <param name="neededDestoryProp">ָ����Ҫ���ٵĵ��ߵ�ָ��</param>
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
/// ����һ�����ߵ��б��У����صĵ��ߺʹ�������һ��
/// </summary>
/// <param name="list">�����б�</param>
/// <param name="prop">���ߵ�����</param>
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
/// ÿ֡���е��ƶ�����
/// </summary>
/// <param name="player">��ҿ��Ƶ�С��</param>
/// <param name="Ax">С��ĺ�����ٶ�</param>
/// <param name="Ay">С���������ٶ�</param>
void move(sphere* player, double Ax,double Ay)
{
	player->x += player->vx * 0.001 * deltaT;
	player->y += player->vy * 0.001 * deltaT;
	player->vx += Ax *0.001* deltaT;
	player->vy += Ay *0.001* deltaT;
}
/// <summary>
/// �����Ƿ�����������ײ�ĵ��ߣ����������ִ�к�������
/// </summary>
/// <param name="propList">�����б�</param>
/// <param name="playerA">���A</param>
/// <param name="playerB">���B</param>
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