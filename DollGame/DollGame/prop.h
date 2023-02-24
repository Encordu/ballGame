/*��ͷ�ļ��洢����ģ��(����Ϊ_object),ģ���methodAfterScollision�����ͻ���ǰ���ֵĺ���
��������Ը��ã���Ϸ�߼��ϻ�������������д���_object���ͣ�����transform������propOnMap��������У�ʵ�ʵĵ����򶼴�����propOnMap*/
#ifndef CORE
#include"core.h"
#endif // CORE
#ifndef DATE
#include"data.h"
#endif // !DATE

sphere basictransform = { 0,0,5,0,0,0 };//һ����׼�������С��������������   
sphere ATKtransform = { 0,0,5,0,0,1 };
/// <summary>
///������������󡣣��뾶+5��
/// </summary>
void addRadius(sphere* sphere)
{
	sphere->r += 5;
}
/// <summary>
/// �˶��е���ǿ��ͣ���������ܲ�ˬ��
/// </summary>
void quiescent(sphere* sphere)
{
	sphere->vx = 0;
	sphere->vy = 0;
}
/// <summary>
/// ����û��ˮƽ�ƶ���
/// </summary>
void stop(sphere* sphere)
{
	sphere->vx = 0;
}
/// <summary>����û�������ƶ���</summary>
void stop_(sphere* sphere)
{
	sphere->vy = 0;
}
/// <summary>
/// С���HP����
/// </summary>
/// <param name="sphere"></param>
void madness(sphere* sphere)
{
	if (sphere->hp * 6 < maxHP)
	{
		sphere->vx *= 1.5;
		sphere->vy *= 1.5;
		return;
	}
	if (sphere->hp * 2 < maxHP)
	{
		sphere->vx *= 1.2;
		sphere->vy *= 1.2;
	}
}
/// <summary>
/// ��˵�еļ�����
/// </summary>
void slow(sphere* sphere)
{
	sphere->vx *=0.85;
	sphere->vy *=0.85;
}
/// <summary>
/// �����򣬡��������������Ҳ�С�
/// </summary>
void deliver(sphere* sphere)
{
	sphere->x = width / 2;
	sphere->y = height / 2;
}
/// <summary>
/// С�˺���
/// </summary>
void smallATK(sphere* sphere)
{
	sphere->hp -= 2;
}
void mediumATK(sphere* sphere)
{
	sphere->hp -= 4;
}
void bigATK(sphere* sphere)
{
	sphere->hp -= 8;
}
//���Խ���˺�Խ��
_object strengthenObj = { basictransform,&addRadius };
_object quiescentObj = { basictransform,&quiescent /*�����ĵ�ַ*/};
_object madnessObj = { basictransform,&madness};
_object stopObj = { basictransform,&stop};
_object stop_Obj = { basictransform,&stop_};
_object slowObj = { basictransform,&slow};
_object deliverObj = { basictransform,&deliver };
_object smallATKObj = { ATKtransform,&smallATK };
_object mediumATKObj = { ATKtransform,&mediumATK };
_object bigATKObj = { ATKtransform,&bigATK };
void addATKsphereToLIst(list* list, sphere player)
{
	double Xadd=0,Yadd=0, player_V=0;
	player_V = sqrt(square(player.vx) + square(player.vy));
	Xadd = player.vx / player_V;
	if (player.r < limitR1)
	{
		_object neededAddProp = smallATKObj;
	}

}
char getTag(_object prop)
{
	if (prop.methodAfterScollision == &addRadius)
	{
		return 'R';
	}
	if (prop.methodAfterScollision == &quiescent)
	{
		return ' ';
	}
	if (prop.methodAfterScollision == &madness)
	{
		return 'M';
	}
	if (prop.methodAfterScollision == &stop)
	{
		return '|';
	}
	if (prop.methodAfterScollision == &stop_)
	{
		return '-';
	}
	if (prop.methodAfterScollision == &slow)
	{
		return '~';
	}
	if (prop.methodAfterScollision == &deliver)
	{
		return ':';
	}
	if (prop.methodAfterScollision == &smallATK || prop.methodAfterScollision == &mediumATK || prop.methodAfterScollision == &bigATK)
	{
		return'!';
	}
	return 0;
}
//�о�����
//hp����ô�����أ�
//�Ǹ�������
//�ƺ���������
//û��˼·������ֻ����ҵ��򣬵�����������ֻ���˺���
//��ֵ��㣬��Ϸ������֮�������ֵ
//��