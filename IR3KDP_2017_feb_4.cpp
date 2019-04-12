bool reserveSpace(int id, int ammount)
{
	rd("number_of_servers", ?servers);
	
	for (int i = 0; i < servers; i++)
		out("request", i, id, ammount);
	
	bool tableOfTaken[number_of_servers] = { 0 };
	bool satisfied = false;
	int checked = 0;
	
	while (satisfied || checked == number_of_servers)
	{
		int server, amm;
		
		in("reservation", ?server, id, ?amm);
		ammount -= amm;
		tableOfTaken[server] = true;
		
		checked++;
		
		if (ammount == 0)
			satisfied = true;
	}
	
	if(checked == number_of_servers && ammount != 0)
	{
		// not enought space
		return false;
	}
	else
	{
		for (int i = 0; i < number_of_servers; i++)
		{
			if (tableOfTaken[i])
				out("confirm", i, id, true);
			else
			{
				in("reservation", i, id, ?amm);
				out("confirm", i, id, false);
			}
		}
	}
}

// 1..N
void server(int id)
{
	int t;
	int ammount = MAX_SPACE;
	
	in("number_of_servers", ?t);
	out("number_of_servers", t + 1);
	
	int reservationTable[N] = {0};
	
	while (1)
	{
		int user, requested_ammount;
		bool status;		
		
		if (inp("confirm", id, ?user, ?status))
		{
			if (!status)
			{
				ammount += reservationTable[user];
				reservationTable[user] = 0;
			}
		}
		// blokiranje ili neblokiranje da bi se čistile confirm torke i brisale neuspešne rezervacije
		else if(inp("request", id, ?user, ?ammount))
		{
			if (requested_ammount > ammount)
			{
				out("reservation", id, user, ammount);
				reservationTable[user] += ammount;
				ammount = 0;
			}
			else
			{
				out("reservation" id, user, requested_ammount);
				reservationTable[user] += requested_ammount;
				ammount -= requested_ammount;
			}
		}
	}
}

void init()
{
	out("number_of_servers", 0);
	
	for (int i = 0; i < N; i++)
		eval(server(i));
}