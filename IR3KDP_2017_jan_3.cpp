struct PersonalRecord
{	
	char*ime;
	char* prezime;
	unsigned long jmbg;
	unsigned long datum;
}

bool validChecksum(unsigned long jmbg)
{
	/* 
	DDMMGGGRRBBBK = ABVGDĐEŽZIJKL
	L = 11 - (( 7*(A+E) + 6*(B+Ž) + 5*(V+Z) + 4*(G+I) + 3*(D+J) + 2*(Đ+K) ) % 11)
	*/
	return f(jmbg);
}

int brojSlicnihCifara(unsigned long izvor, unsigned long comp)
{
	int cnt = 0;
	
	// pretpostavljeno je da su brojevi iste duzine, a i da nisu petlja se zavrsava svakako
	while (izvor > 0 && comp > 0)
	{
		if (izvor % 10 == comp % 10)
			cnt++;
		
		izvor /= 10;
		comp /= 10;
	}
	
	return cnt;
}

PersonalRecord* pretraziPoJMBG(unsigned long jmbg)
{
	// tuple(ime, prezime, jmbg, datum)
	char *ime, *prezime;
	unsigned long datum;
	PersonalRecord* result = new PersonalRecord();
	
	if (rdp(?ime, ?prezime, jmbg, ?datum))
	{
		result->ime = ime;
		result->prezime = prezime;
		result->jmbg = jmbg;
		result->datum = datum;
		
		return result;
	}
	else
	{
		// nema poklapanja po jmbgu
		// provera kontrolne cifre
		if (validChecksum(unsigned long jmbg))
		{
			in("mutex");
			List<unsigned long> list;
			// dobijanje slicnih
			unsigned long t;
			
			bool b;
			do
			{			
				b = inp(ime, prezime, ?t, datum);
				if (b)
					list.add(t);
			} while (b && validChecksum(t));
			
			// potrebno je da je pronaden barem jedan
			unsigned long najslicniji = -1;
			bool izmenjeno = false;
			if (!validChecksum(t))
			{
				najslicniji = t;
				unsigned long slicnihCifara = brojSlicnihCifara(jmbg, najslicniji);
				
				while (inp(ime, prezime, ?t, datum))
				{
					if (!validChecksum(t))
					{
						lista.add(t);
						
						unsigned long x = brojSlicnihCifara(jmbg, t);
						
						if (x > slicnihCifara)
						{
							najslicniji = t;
							slicnihCifara = x;
						}
					}
				}
				
				// vracanje izmenjenog zapisa
				out(ime, prezime, jmbg, datum);
				izmenjeno = true;
			}
				
			// vracanje u prostor torki
			for (int i = 0; i < list.count(); i++)
			{
				unsigned long zaDodavanje = list.remove(i);
				if (najslicniji == -1 || zaDodavanje != najslicniji)
						out(ime, prezime, zaDodavanje, datum);
					
			}
			
			out("mutex");
			
			if (izmenjeno)
			{
				result->ime = ime;
				result->prezime = prezime;
				result->jmbg = jmbg;
				result->datum = datum;
				
				return result;
			}
			else
				return null;
		}
		else
		{
			// novi dokument
			return null;
		}
	}
}

void init()
{
	out("mutex");
}