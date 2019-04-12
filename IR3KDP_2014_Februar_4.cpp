/* -------------------------------------
   -------------- globalno -------------
   ------------------------------------- */
enum OPERACIJA
{
	UPLATA,
	ISPLATA,
	PROVERA_STANJA
}

union Rezultat
{
	bool v1;
	double v2;
}

const int N; // max broj klijenata

channel request(int id, OPERACIJA op, Rezultat p);
channel response[N](Rezultat r);

/* -------------------------------------
   -------------- server ---------------
   ------------------------------------- */
process Server()
{
	while (1)
	{
		int id;
		OPERACIJA op;
		double iznos;
		receive request(id, op, iznos);
		
		Rezultat r;
		
		if (op == UPLATA)
		{
			r.v1 = Account.Uplati(iznos);
		}
		else if (op == ISPLATA)
		{
			r.v1 = Account.Isplati(id, iznos);
		}
		else if (op == PROVERA_STANJA)
		{
			r.v2 = Account.Stanje(id);
		}
		
		send response[id](r);
	}
}

class Account
{
	double saldo;
	
	bool pristup(int id);
	
	double Stanje(int id)
	{
		if (pristup[id])
			return saldo;
	}
	
	bool Uplati(double iznos)
	{
		if (iznos > 0)
		{
			saldo += iznos;
			return true;
		}
		else
			return false;
	}
	
	bool Isplati(int id, double iznos)
	{
		if (iznos > 0)
		{
			if (pristup[id])
			{
				if (saldo - iznos >= 0)
				{
					saldo -= iznos;
					return true;
				}
				else
					return false;
			}
		}
		else
			return false;
	}
}

/* -------------------------------------
   -------------- klijent --------------
   ------------------------------------- */
bool uplati(int korisnik, double iznos)
{
	Rezultat r;
	
	send request(korisnik, OPERACIJA.UPLATA, iznos);
	receive response[korisnik](r);
	
	return r.v1;
}

bool isplati(int korisnik, double iznos)
{
	Rezultat r;
	
	send request(korisnik, OPERACIJA.ISPLATA, iznos);
	receive response[korisnik](r);
	
	return r.v1;
}

double proveriStanje(int korisnik)
{
	Rezultat r;
	
	send request(korisnik, OPERACIJA.PROVERA_STANJA, 0);
	receive response[korisnik](r);
	
	return r.v2;
}