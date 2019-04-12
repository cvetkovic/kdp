monitor Upis
{
	struct Zahtev
	{
		int broj;
		Zahtev* sledeci;
		
		Zahtev(int b, Zahtev* z) : broj(b), sledeci(z) {}
	}
	
	bool zauzeto = false;
	
	int dodelaIndeksa = 1;
	Zahtev* glava = 0;
	
	int Upisi()
	{
		if (glava == 0)
			return dodelaIndeksa++;
		else
		{
			Zahtev* z = glava;
			glava = glava->sledeci;
			
			int i = z->broj;
			delete z;
			
			return i;
		}
	}
	
	int Ispisi(int indeks)
	{
		Zahtev *p = 0, *q = glava;
		
		while (q != nullptr && q->broj < indeks)
		{
			p = q;
			q = q->sledeci;
		}
		
		if (p == 0)
		{
			glava = new Zahtev(indeks);
		}
		else
		{
			Zahtev* z = new Zahtev(indeks);
			
			p->sledeci = z;
			z>sledeci = q;
		}
	}
}