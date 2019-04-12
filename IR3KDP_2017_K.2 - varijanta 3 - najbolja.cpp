void bringChildren(int num)
{
	wait(entry);
	wait(mutex);
	if (numChildren + num < 3 * numNann)
	{
		numWaitingC = n;
		signal(mutex);
		wait(toLeave);
		numWaitingC = 0;
	}
	numChildren += num;
	signal(mutex);
	signal(entry);
}

void takeChildren(int num)
{
	wait(mutex);
	numChildren -= num;
	if (numWaitingC > 0 && (numChildren + numWaitingC <= 3 * numNann))
		signal(toLeave);
	else if (numWaitingN > 0 && (numChildren <= 3 * (numNann - 1)))
		signal(toLeave);
	else
		signal(mutex);
}

void nannEnter()
{
	signal(mutex);
	numNann++;
	if (numWaitingC > 0 && ((numChildren + numWaitingC) <= 3 * numNann))
		signal(toLeave);
	else if (numWaitingN > 0 && numChildren <= 3 * (numNann - 1))
		signal(toLeave);
	else
		signal(mutex);
}

void nannLeave()
{
	wait(entry);
	wait(mutex);
	if (numChildren > 3 * (numNann - 1))
	{
		numWaitingN++;
		signal(mutex);
		wait(toLeave);
		numWaitingN--;
	}
	numNann--;
	signal(mutex);
	signal(entry);
}