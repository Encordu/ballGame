int ifExceedMaxA(double Ax, double Ay)
{
	if (square(Ax) + square(Ay) > 100)
	{
		return 1;
	}
	return 0;
}
/// <summary>
/// ��ȡ���������õļ��ٶ�(ע��Ax^2+Ay^2&lt;=100)
/// </summary>
/// <param name="selfPlayer">���������������Ƶ�С������</param>
/// <param name="otherPlayer">��������������˿��Ƶ�С������</param>
/// <param name="returnAx">������ó��ĺ�����ٶ�</param>
/// <param name="returnAy">������ó���������ٶ�</param>
/// <param name="AIKind">ʹ�õ�AI����</param>
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
		printf("���󣬷���getAccleration��õļ��ٶȳ���Ԥ�����ֵ");
		getchar();
		*returnAx = 0;
		*returnAy = 0;
	}
}
