void bringChildren(int num)
{
	while (true)
	{
		wait(mutex);
		if (numOfChildren + num <= 3 * numOfNann)
		{
			numOfChildren += num;
			signal(mutex);
			return;
		}
		else
		{
			numOfAdultWaiting++;
			signal(mutex);
			wait(adultLeaveChildren);
		}
	}
}

void takeChildren(int num)
{
	wait(mutex);
	numOfChildren -= num;
	
	if (numOfAdultWaiting > 0)
	{
		signal(mutex);
		signal(adultLeaveChildren);
	}
	else
	{
		int out = numOfNann - (numOfChildren + 2) / 3;
		if (out > numOfWaiting)
			out = numOfWaiting;
		for (int i = 0; i < out; i++)
		{
			signal(go);
			wait(confirm);
		}
		
		signal(mutex);
	}
}

void comeToWork()
{
	wait(mutex);
	numOfNann++;
	if (numOfAdultWaiting > 0)
	{
		signal(mutex);
		signal(adultLeaveChildren);
	}
	else if (numOfWaiting > 0)
	{
		signal(go);
		wait(confirm);
		signal(mutex);
	}
}

void goHome()
{
	wait(mutex);
	if ((numOfChildren <= 3 * (numOfNann - 1)) && numOfAdultWaiting == 0)
	{
		numOfNann--;
		signal(mutex);
	}
	else
	{
		numOfWaiting++;
		signal(mutex);
		
		wait(go);
		numOfWaiting--;
		numOfNann--;
		signal(confirm);
	}
	
}