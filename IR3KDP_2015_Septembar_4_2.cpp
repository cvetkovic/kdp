/* https://github.com/hpc/cce-mpi-openmpi-1.6.4/blob/master/ompi/mca/coll/basic/coll_basic_barrier.c 

po uzoru na MPI biblioteku. 
if (rank > 0) je klijentski kod
else je serverski kod
*/
const int N = ...;

struct Parameter
{
	int id;
}

MessageBox barrier;
MessageBox user[N];

////////////////////////////////
//////////// SERVER ////////////
////////////////////////////////
void server()
{
	List<int> queue;
	int cnt = 0;
	const int N;
	
	while (1)
	{
		int id;
		
		Message<Parameter> p;
		mbx_receive(barrier, p, INF, status);
				
		//////////////////////////////////////////
		queue.add(p.id);
		cnt++;
		
		if (cnt == N)
		{
			cnt == 0;
			
			for (int i = 0; i < N; i++)
				mbx_put(user[queue.dequeue()], p);
		}
	}
}

////////////////////////////////
//////////// CLIENT ////////////
////////////////////////////////
void wait_barrier(int id)
{
	Message<Parameter> p;
	p.id = id;
	mbx_put(barrier, p);
	mbx_receive(user[id], p, INF, status);
}