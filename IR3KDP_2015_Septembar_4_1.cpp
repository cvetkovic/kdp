/* https://github.com/hpc/cce-mpi-openmpi-1.6.4/blob/master/ompi/mca/coll/basic/coll_basic_barrier.c 

po uzoru na MPI biblioteku. 
if (rank > 0) je klijentski kod
else je serverski kod
*/

channel request(int id);
channel response[n]();

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
		
		receive in(id);
		
		////////////////////////////////
		queue.add(id);
		cnt++;
		
		if (cnt == N)
		{
			cnt == 0;
			
			for (int i = 0; i < N; i++)
				send response[queue.dequeue()]();
		}
	}
}

////////////////////////////////
//////////// CLIENT ////////////
////////////////////////////////
void wait_barrier(int id)
{
	send request(id);
	receive response[id];
}