Semaphore rw(N);
Semaphore mutex(1);

void Writer()
{
	wait(mutex);
	
	for (int i = 0; i < N; i++)
		wait(rw);
	write();
	for (int i = 0; i < N; i++)
		signal(rw);
	
	signal(mutex);
}

void Reader()
{
	wait(rw);
	read();
	signal(rw);
}