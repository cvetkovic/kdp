monitor Ambasada
{
	bool busy = false;
	long now = 0;
	long scheduler = 0;
	CV blocked;
	
	void tick()
	{
		now++;
		
		if (blocked.queue() && busy == false && minrank(cv) <= now)
			blocked.signal();
	}
	
	void applyForTicket()
	{
		long mypriority;
		
		if (blocked.queue())
		{
			mypriority = scheduler + 10
			scheduler += 10;
		}
		else
		{
			mypriority = now + 1; // +1 jer moze da se desi da se prvo dogodi tick pa onda pozove applyForTicket
			scheduler = now + 11;
		}
				
		blocked.wait(mypriority);
	}
	
	void workStart()
	{
		busy = true;
	}
	
	void workEnd()
	{
		busy = false;
		if (blocked.queue())
			cv.signal();
	}
}