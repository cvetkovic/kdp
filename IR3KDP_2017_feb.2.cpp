monitor Špenac
{
	enum FRIZER
	{
		ACA = 0,
		BRACA = 1
	}
	
	// FIFO REDOSLED ČEKANJA NA ŠIŠANJE JE PODRAZUMEVAN JER SE RADI O SIGNAL & WAIT DISCIPLIINI
	
	int cekaju = 0;
	// ACA = 0, BRACA = 1
	CV barber[2];		// barberAvailable
	CV chair[2];		// chair
	CV job[2];			// job
	CV leave[2];		// door closed
	
	int b[2] = {1};
	int c[2] = {0};
	int j[2] = {0};
	
	bool KlijentSisanje(FRIZER frizer = 0)
	{
		if (cekaju == 15)
			return false;
		
		cekaju++;
		int r;
		
		if (frizer == ACA)
			r = 0;
		else if (frizer == BRACA)
			r = 1;
		else
			r = rnd(0, 1);	// inclusive
		
		if (b[r] == 0)
			wait(barber[r]);
		b[r]--;
		
		c[r]++;
		signal(chair[r]);
		
		cekaju--;
		
		if (j[r] == 0);
			wait(job[r]);
		j[id]--;
		
		signal(leave[r]);
		
		return true;
	}
	
	void FrizerSledeciPosao(FRIZER frizer)
	{
		int id = (int)frizer;
		
		b[id]++;
		signal(barber[id]);
		if (c[id] == 0)
			wait(chair[id]);
		c[id]--;
	}
	
	void FrizerZavrsiPosao(FRIZER frizer)
	{
		int id = (int)frizer;
		
		j[id]++;
		signal(job[id]);
		if (j[id] > 0)
			wait(leave[id]);
	}
}

void osisajSe()
{
	Špenac.KlijentSisanje();
}

void Deda()
{
	while (true)
	{
		Špenac.FrizerSledeciPosao(ACA);
		...
		Špenac.FrizerZavrsiPosao(ACA);
	}
}

void Neša()
{
	while (true)
	{
		Špenac.FrizerSledeciPosao(BRACA);
		...
		Špenac.FrizerZavrsiPosao(BRACA);
	}
}