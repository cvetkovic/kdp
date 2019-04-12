const int M; // broj brojeva za generisanje
const int N; // broj procesa

const int EONAT = 20001; // EOS symbolic constant

channel comm[n](int val);

void process[0]()
{
	///////////////////////////////
	/////////// SENDING ///////////
	///////////////////////////////
	for (int i = 0; i < M; i++)
	{
		int generated = (int)(rand() / RAND_MAX * (20000 - 1) + 1);
		send comm[1](generated);
	}
	
	send comm[1](EONAT);
	
	///////////////////////////////
	/////////// RX / TX ///////////
	///////////////////////////////
	int v;
	
	receive comm[0](v);
	while (v != EONAT)
	{
		consume(v);
		
		send comm[1](v);
		receive comm[0](v);
	}
	send comm[1](EONAT);
}

void process[id=1..n-1]()
{
	const int myPrimeNumber = ...;
	int v;
	
	///////////////////////////////
	////////// RECEIVING //////////
	///////////////////////////////
	receive comm[id](v);
	while (v != EONAT)
	{
		if (v != myPrimeNumber)
			send comm[(id + 1) % N](v);
		
		receive comm[id](v);
	}
	send comm[(id + 1) % N](EONAT);
	///////////////////////////////
	/////////// RX / TX ///////////
	///////////////////////////////
	receive comm[id](v);
	while (v != EONAT)
	{
		consume(v);
		
		send comm[(id + 1) % N](v);
		receive comm[id](v);
	}
	send comm[(id + 1) % N](EONAT);
}