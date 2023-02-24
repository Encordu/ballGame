int ifExceedMaxA(double Ax, double Ay)
{
	if (square(Ax) + square(Ay) > 100)
	{
		return 1;
	}
	return 0;
}
/// <summary>
/// 获取经计算所得的加速度(注意Ax^2+Ay^2&lt;=100)
/// </summary>
/// <param name="selfPlayer">传入计算中自身控制的小球数据</param>
/// <param name="otherPlayer">传入计算中其他人控制的小球数据</param>
/// <param name="returnAx">经计算得出的横向加速度</param>
/// <param name="returnAy">经计算得出的竖向加速度</param>
/// <param name="AIKind">使用的AI种类</param>
void getAcceleration(sphere selfPlayer, sphere otherPlayer, double* returnAx, double* returnAy, int AIKind)
{
	switch (AIKind)
	{
		case 1:
			bestMethod(selfPlayer,otherPlayer,returnAx,returnAy);
		default:
			;
	}
	if (ifExceedMaxA(*returnAx, *returnAy))
	{
		system("Cls");
		printf("错误，方法getAccleration获得的加速度超过预定最大值");
		getchar();
		*returnAx = 0;
		*returnAy = 0;
	}
}
