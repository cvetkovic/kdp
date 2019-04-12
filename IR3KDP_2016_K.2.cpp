struct Radnja
{
	int cntStajaci = 0;
	int cntSedeci = 0;
	int sedeci[10] = {0};
	int stajaci[10] = {0};
	int sedeciWriteTo = 0;
	int stajaciWriteTo = 0;
	
	int dodela = 0;
	int next = 0;
	
	int frizer[3] = {0};
	int plati[3] = {0};
}

Radnja frizeraj;

void ubaciURed(int i)
{
	if (cntSedeci != 10)
	{
		cntSedeci++;
		sedeci[sedeciWriteTo] = i;
		
		sedeciWriteTo = (sedeciWriteTo + 1) % n;
	}
	else if (cntStajaci != 10)
	{
		cntStajaci++;
		stajaci[stajaciWriteTo] = i;
		
		stajaciWriteTo = (stajaciWriteTo + 1) % n;
	}
}

int uzmiMusteriju()
{
	if (cntSedeci > 0)
	{
		int rez = cntSedeci[sedeciReadFrom];
		sedeciReadFrom = (sedeciReadFrom + 1) % n;
		cntSedeci--;
		
		// prebacivanje iz stajaceg u sedeci polozaj
		if (cntStajaci > 0)
		{
			cntSedeci++;
			sedeci[sedeciWriteTo] = stajaci[stajaciReadFrom];	
			sedeciWriteTo = (sedeciWriteTo + 1) % n;
			
			stajaciReadFrom = (stajaciReadFrom + 1) % n;		
			cntStajaci--;
		}
		
		return rez;
	}
}

bool customer()
{
	region frizeraj
	{
		if (cntStajaci == 10 && cntSedeci == 10)
			return false;
		
		int id = dodela++;
		ubaciURed(id);
		
		await(next == id);
		
		budiSisan();
		
		await(frizer[0] == id || frizer[1] == id || frizer[2] == id);
		
		budiNaplacen();
		
		await(plati[0] == id || plati[1] == id || plati[2] == id);
		
		idiKuci();
		
		return true;
	}
}

void getClient(int id)
{
	region frizeraj
	{
		await(cntSedeci != 0);
		
		next = uzmiMusteriju();
	}
	
	sisaj();
	
	region frizeraj	
	{
		frizer[id] = true;
	}
}

void billClient(int id)
{
	region frizeraj
	{
		plati[id] = true;
	}
}

void frizer()
{
	while (true)
	{
		getClient(id);
		...
		billClient(id);
	}
}