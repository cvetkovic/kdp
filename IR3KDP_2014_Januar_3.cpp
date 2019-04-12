const int n;
const int TIME;
const long SLEEP_TIME;

long currentTime();

void process()
{
	int niz[2 * n];
	int cnt = 0;
	
	bool uspelo = false;
	
	do
	{
		in("mutex");
		long startTime = currentTime();
		
		for (int i = 0; i < 2 * n; i++)
		{
			in("niz", i, ?niz[i]);
			
			if ((currentTime() - startTime) > TIME)
			{
				for (j = 0; j <= i; j++)
					out("niz", j, niz[j]);
				
				uspelo = false;
				out("mutex");
				sleep(rand() * SLEEP_TIME);
				break;
			}
			
			if (i == 2 * n - 1)
				uspelo = true;
		}
	} while (!uspelo);
	
	for (int i = 0; i < n; i++)
	{
		int t = niz[i];
		niz[2 * n - i - 1] = niz[i];
		niz[i] = t;
	}
	
	out("mutex");
}

void init()
{
	out("mutex");
	
	eval(process());
}