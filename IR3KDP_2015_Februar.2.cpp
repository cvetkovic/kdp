int count[3] = {0}; 	// in roundabout
int blocked[3] = {0};	// in blocked state
Semaphore sem[3];		// blocking queue

// PRETPOSTAVLJA SE FIFO SEMAFOR

int next(int i)
{
	return (i + 1) % 3;
}

void enter(int segment)
{
	wait(mutex);
	if (blocked[segment] != 0 || count[segment] != 0)
	{
		blocked[segment]++;
		signal(mutex);
		sem[segment].wait();
		// biće pozvan u mutex-u neke druge procedure
		// START
		blocked[segment]--;
		count[next(segment)]++;
		// END
	}
	else
	{
		count[next(segment)]++;
		signal(mutex);
	}
}

void moveFrom(int segment)
{
	wait(mutex);
	count[next(segment)]++;
	count[segment]--;
	while (blocked[segment] != 0 && count[segment] == 0)
		sem[segment].signal();
	signal(mutex);
}

void leave(int segment)
{
	wait(mutex);
	count[segment]--;
	while (blocked[segment] != 0 && count[segment] == 0)
		sem[segment].signal();
	signal(mutex);
}