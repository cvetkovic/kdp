const int N = ...;

struct msg
{
	int min;
	int max;
}

MessageBox box[N];

void initiator()
{
	const int myval = ...;
	int min, max;
	
	Message m;
	m.min = myval;
	m.max = myval;
	// inicijalno slanje
	mbx_put(box[1], m);
	
	// prosledivanje rezultata
	mbx_get(box[0], m, INF, status);
	mbx_put(box[1], m);
}

void other_nodes(int i)
{
	const int myval = ...;
	int min, max;
	
	Message m;
	mbx_get(box[i], m, INF, status);
	if (myval < m.min)
		m.min = myval;
	else if (myval > m.max)
		m.max = myval;
	mbx_put(box[(i + 1) % n], m);
	
	// prosledivanje rezultata
	mbx_get(box[i], m, INF, status);
	if (i < n - 1)
		mbx_put(box[(i + 1) % n], m);
}