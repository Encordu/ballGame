/*本头文件存储道具模板(类型为_object),模板的methodAfterScollision函数和基于前两种的函数
道具球可以复用，游戏逻辑上会有语句在运行中创建_object类型，更改transform后置于propOnMap这个链表中，实际的道具球都存在于propOnMap*/
#ifndef CORE
#include"core.h"
#endif // CORE
#ifndef DATE
#include"data.h"
#endif // !DATE

sphere basictransform = { 0,0,5,0,0,0 };//一个标准道具球大小，“它不动弹”   
sphere ATKtransform = { 0,0,5,0,0,1 };
/// <summary>
///作用是球球会变大。（半径+5）
/// </summary>
void addRadius(sphere* sphere)
{
	sphere->r += 5;
}
/// <summary>
/// 运动中的球强行停下来，它很不爽！
/// </summary>
void quiescent(sphere* sphere)
{
	sphere->vx = 0;
	sphere->vy = 0;
}
/// <summary>
/// 球球没法水平移动了
/// </summary>
void stop(sphere* sphere)
{
	sphere->vx = 0;
}
/// <summary>球球没法上下移动了</summary>
void stop_(sphere* sphere)
{
	sphere->vy = 0;
}
/// <summary>
/// 小球低HP狂化了
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
/// 传说中的减速球
/// </summary>
void slow(sphere* sphere)
{
	sphere->vx *=0.85;
	sphere->vy *=0.85;
}
/// <summary>
/// 归中球，“你想叫它传送门也行”
/// </summary>
void deliver(sphere* sphere)
{
	sphere->x = width / 2;
	sphere->y = height / 2;
}
/// <summary>
/// 小伤害球
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
//体积越大，伤害越高
_object strengthenObj = { basictransform,&addRadius };
_object quiescentObj = { basictransform,&quiescent /*函数的地址*/};
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
//感觉够了
//hp会怎么减少呢？
//是个好问题
//似乎是这样了
//没有思路，参数只有玩家的球，道具上能做的只有伤害球
//数值随便，游戏主体完之后才做数值
//是