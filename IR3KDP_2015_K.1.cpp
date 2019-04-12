enum USER_TYPE { DISABLED = 1, FAMILY = 2, OTHER = 3 }

monitor BankQueue
{
	cv queue;
	bool busy = false;
	
public:
	void RequestTicket(USER_TYPE type)
	{
		// podrazumevano FIFO po prioritetima
		if (!queue.empty() || busy)
			queue.wait(PRIORITY);
		
		busy = true;
	}
	
	void ReleaseTicket()
	{
		busy = false;
		if (!queue.empty())
			queue.signal();
	}
}

monitor MoneyOperations
{
	double saldo = 0;
	
public:
	bool Deposit(double ammount, int accountNumber, int user)
	{
		bool result = false;
		if (ammount >= 0)
		{
			if (canAccess(user, accountNumber))
			{
				money[accountNumber] += ammount;
				result = true;
			}
		}
		
		return result;
	}
	
	bool Get(double ammount, int accountNumber, int user)
	{
		bool result = false;
		if (ammount >= 0)
		{
			if (canAccess(user, accountNumber))
			{
				if (saldo >= ammount)
				{
					money[accountNumber] -= ammount;
					result = true;
				}
			}
		}
		
		return result;
	}
	
	double State(int accountNumber)
	{
		double result = false;
		
		if (canAccess(user, accountNumber))
		{
			result = saldo;
		}
		
		return result;
	}
}

void ClientExample(USER_TYPE t)
{
	BankQueue.RequestTicket(t);
	MoneyOperations.Deposit();	
	BankQueue.ReleaseTicket();
}

// svaki salter treba da ima svoj monitor BankQueue jer jedan korisnik ceka da bude prozvan na tom salteru
// i nema veze sa ostalima