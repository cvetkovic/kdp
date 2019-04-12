process voda_licitacije()
{
	double pocetna_cena = 1000; // RSD
	
	out("licitacija", pocetna_cena);
	out("ponuda", 0, 0, pocetna_cena, 0); // id prva nula; br ponude druga nula; vreme treca nula
	
	int id, brojPonude;
	double cena;
	long vreme;
	
	int readFrom = 0;
	bool zavrseno = false;
	int pobednik;
	
	while (inp("ponuda", ?id, readFrom, ?cena, ?vreme) || !zavrseno)
	{
		rdp("system_time", ?time);
		if (time >= vreme + 15) // 15 sekundi rok da se da ponuda
			zavrseno = true;
		
		if (!zavrseno)
		{
			if (cena > pocetna_cena)
			{
				pocetna_cena = cena;
				
				in("licitacija", pocetna_cena);
				out("licitacija", pocetna_cena);
				
				out("prihvati_ponudu", id, true);
				pobednik = id;
			}
			else
			{
				out("prihvati_ponudu", id, false);
			}
		}
		else
			out("prihvati_ponudu", id, false);
	}
	
	in("licitacija", pocetna_cena);
	for (int i = 0; i < BR_UCESNIKA; i++)
		out("pobednik", pobednik, pocetna_cena);
}

process ucesnik_u_licitaciji(int id)
{
	while (1)
	{
		double cena;
		int pobednik;
		
		if (!inp("pobednik", ?pobednik, ?cena))
		{
			rdp("licitacija", ?cena);
			double nova_cena = 0;
			
			if ((nova_cena = ZelimDaLicitiramDalje(cena)) != 0)
			{
				int noPonude;
				
				in("indexW", ?noPonude);
				out("indexW", noPonude + 1);
				noPonude++;
				
				out("ponuda", id, noPonude, nova_cena, time);
				
				bool b;
				in("prihvati_ponudu", id, ?b);
				
				if (b)
					// OBAVESTI PRIHVACENO
				else
					// OBAVESTI NEPRIHVACENO
			}
		}
		else
		{
			// OBAVESTI DA JE POBEDNIK 'pobednik' za 'cena' RSD
			break;
		}
	}
}

void tick()
{
	while (1)
	{
		long t;
		
		in("system_time", ?t);
		out("system_time", t + 1); // s
		sleep(1000); // ms
	}
}

void init()
{
	out("system_time", 0);
	
	eval(tick());
	eval(voda_licitacije());
	
	for (int i = 0; i < n; i++)
		eval(ucesnik_u_licitaciji(i));
}