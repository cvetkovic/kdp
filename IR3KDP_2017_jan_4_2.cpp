/*  II varijanta - prevodenje semaforskog koda na MPI
	
	wait(mutex_north);
	if (carSouth != 0)
		wait(south);
	else if (weight + w > K)
	{ wait(weight); q.add(w); }
	carNorth++;
	weight += w;
	signal(mutex_north);
	
	// CROSS THE BRIDGE
	
	wait(mutex_north);
	carNorth--;
	weight -= w;
	if (queue.first() <= w)
		signal(weight);
	else if (carSouth == 0 && !south.empty())
		signal(south);
	else
		signal(mutex_north);
*/

struct bridge
{
	int giveId = 0;
	int call = 0;
	int north_car;
	int south_car;
	double weight;
	queue<double> waiting;
}

const double K = ...;
message_box mutex_north, mutex_south, shared;
message<int> blank;
message<bridge> msg;
message<queue<int>> queue;

void north_car(double w)
{
	get(mutex_north, blank, INF, status);
	///
	get(shared, msg, INF, status);
	int ID = msg.giveId++;
	
	if (msg.south_car != 0)
	{
		put(shared, msg);
		
		put(sleep1, ID);
		do
		{
			get(confirm1, int confirm, INF, status);
		} while (confirm != ID);
		get(shared, msg, INF, status);
		
		msg.north_car++;
		msg.weight += w;
		
		put(shared, msg);
		put(mutex_north, blank);
	}
	else if (weight + w > K)
	{
		msg.queue.add(w);
		put(shared, msg);
		
		put(sleep1_2, ID);
		do
		{
			get(confirm1_2, int confirm, INF, status);
		} while (confirm != ID);
		get(shared, msg, INF, status);
		
		msg.north_car++;
		msg.weight += w;
		
		put(shared, msg);
		put(mutex_north, blank);
	}
	else
	{
		msg.north_car++;
		msg.weight += w;
		put(shared, msg);
		put(mutex_north, blank);
	}
	
	/////////////////////////
	// CROSSING THE BRIDGE //
	/////////////////////////
	
	get(mutex_north, blank, INF, status);
	///
	get(shared, msg, INF, status);
	msg.north_car--;
	msg.weight -= w;
	if (msg.queue.first() <= w)	
	{
		msg.queue.dequeue();
		get(sleep2_2, int t, INF, status);
		put(confirm2_2, t);
	}
	else if (msg.south_car == 0 && )
	{
		put(shared);
		get(sleep2, int t, INF, status);
		put(confirm2, t);
		// no mutex_north, upper 'if' will release it because of giving exclusive and fair access
	}
	else
	{
		put(shared, msg);
		put(mutex_north, blank);
	}
}

void south_car(double w)
{
	// analogno sa north_car(...)
}