enum PRIORITET
{
	VISOK = 0,
	SREDNJI = 1,
	NISKI = 2
}

Queue<int> qa, qb, qc;
Semaphore a[n], b[n], c[n];

// ID je lekar koji poziva
void zahtevajSanitet(PRIORITET p)
{
	wait(e);
	
	if (k == 0)
	{
		if (p == VISOK)
		{
			qa.enqueue(id));
			signal(e);
			wait(a[ID]);
		}
		else if (p == SREDNJI)
		{
			qb.enqueue(id);
			signal(e);
			wait(b[ID]);
		}
		else
		{
			qc.enqueue(id);
			signal(e);
			wait(c[ID]);
		}
	}
	
	k--;
	signal(e);
}

void oslobodiSanitet()
{
	wait(e);
	k++;
	
	if (!qa.empty())
	{
		int t = qa.dequeue();
		signal(a[t]);
	}
	else if (!qb.empty()
	{
		int t = qb.dequeue();
		signal(b[t]);
	}
	else if (!qc.empty())
	{
		int t = qc.dequeue();
		signal(c[t]);
	}
	else
		signal(e);
}