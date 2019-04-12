struct bridge
{
	int north_car;
	int south_car;
	double weight;
}

const double K = ...;
message_box mutex;
message<bridge> msg;

void north_car(double w)
{
	bool condition = false;
	
	do
	{
		get(mutex, msg, INF, status);
		if (msg.south_car == 0 && msg.weight + w <= K)
		{
			msg.north_car++;
			msg.weight += w;
			
			condition = true;
		}
		put(mutex, msg);
	} while (!condition);
	
	// CROSSING THE BRIDGE
	
	get(mutex, msg, INF, status);
	msg.north_car--;
	msg.weight -= w;
	put(mutex, msg);
}

void south_car(double w)
{
	// analogno sa north_car(...)
}