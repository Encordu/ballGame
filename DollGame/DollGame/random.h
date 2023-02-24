#pragma once
/// <summary>
/// �������1(��)-1000(��)�ڵ�����
/// </summary>
/// <returns></returns>
int commonlyUsedRandom()
{
	//rand�������С��32768������
	int randNum;
	while (1)
	{
		randNum = rand() % 1024;
		if (randNum < 1000)
		{
			break;
		}
	}
	return randNum + 1;
}
/// <summary>
/// �������1(��)-MaxNum(��)�ڵ�����
/// </summary>
/// <param name="maxNum">������1000������</param>
/// <returns></returns>
int randWithMaxNum(int maxNum)
{
	int truncationArray[] = { 5,20,50,200,500,1000 };
	int index=0,randNum=0;
	for (int i = 0; i < 6; i++)
	{
		if (maxNum < truncationArray[i])
		{
			index = i;
			break;
		}
	}
	while (1)
	{
		randNum = commonlyUsedRandom() % truncationArray[index];
		if (randNum <maxNum)
		{
			break;
		}
	}
	return randNum + 1;
}
int randNumBetweenMinAndMax(int minNum, int maxNum)
{
	if (minNum == maxNum)
	{
		return minNum;
	}
	int randNum = randWithMaxNum(maxNum - minNum + 1);
	return randNum - 1 + minNum;
}
_object randomObject()
{
	int randNum = commonlyUsedRandom();
	int Tag =PstrengthenObj;
	if (randNum <= Tag)
	{
		return strengthenObj;
	}
	Tag += PquiescentObj;
	if (randNum <= Tag)
	{
		return quiescentObj;
	}
	Tag += PmadnessObj;
	if (randNum <= Tag)
	{
		return madnessObj;
	}
	Tag += PslowObj;
	if (randNum <= Tag)
	{
		return slowObj;
	}
	Tag += Pstop_Obj;
	if (randNum <= Tag)
	{
		return stop_Obj;
	}
	Tag += PslowObj;
	if (randNum <= Tag)
	{
		return slowObj;
	}
	Tag += PdeliverObj;
	if (randNum <= Tag)
	{
		return deliverObj;
	}
	Tag += PsmallATKObj;
	if (randNum <= Tag)
	{
		return smallATKObj;
	}
		return mediumATKObj;
}
_object randPositon(_object kind)
{
	_object returnObject = kind;
	returnObject.transform.x = randNumBetweenMinAndMax(returnObject.transform.r, (int)width - (int)returnObject.transform.r);
	returnObject.transform.y = randNumBetweenMinAndMax(returnObject.transform.r, (int)height - (int)returnObject.transform.r);
	return returnObject;
}