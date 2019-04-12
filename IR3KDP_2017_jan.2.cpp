const int K = ...;
int passengersAtStation = 0;
int busPassengerCount = 0;
bool canCheckIn = true;
bool busAtStation = false;
bool finishedTrip = false;
bool aboard = false;
bool travelling = false;

void passenger()
{
	region transport
	{
		await(canCheckIn);
		passengersAtStation++;
		
		await(busAtStation);
		
		if (busPassengerCount < K)
		{	
			busPassengerCount++;
			passengersAtStation--;
		}
		if (busPassengerCount == K || passengersAtStation == 0)
		{
			aboard = true;
		}
		
		await(travelling);
		
		travel();
		
		await(finishedTrip);
	}
}

void bus()
{
	region transport
	{
		canCheckIn = false;
		finishedTrip = false;
		busAtStation = true;
		
		await(aboard || passengersAtStation == 0);
		
		busAtStation = false;

		travelling = true;
		
		travel();
		
		finishedTrip = true;
		canCheckIn = true;
		travelling = false;
	}
}