int numberOfChildren = 0, numberOfNann = 0, numberOfWaiting = 0;
int da = 0, dn = 0;
Semaphore e(1), a(0), n(0);

void adultStart(int num)
{
	wait(e);
	while (numberOfChildren + num > 3 * numberOfNann)
	{	da++; signal(e); wait(a);	}
	numberOfChildren += num;
	SIGNAL;
}

void adultEnd(int num)
{
	wait(e);
	numberOfChildren -= num;
	SIGNAL;
}

void nannStart()
{
	wait(e);
	numberOfNann++;	
	SIGNAL;
}

void nannEnd()
{
	wait(e);
	while (numberOfChildren > 3 * (numberOfNann - 1))
	{	dn++; signal(e); wait(d);	}
	SIGNAL;
}

#define SIGNAL 
if (da > 0)
{	da--; signal(a);	}
else if (dn > 0)
{	dn--; signal(d);	}
else
	signal(e);