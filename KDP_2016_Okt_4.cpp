void person(int id)
{
	while (1)
	{
		int ticket;
		// waiting in row to apply for a car
		in("person_queue", ?ticket);
		out("person_queue", ticket + 1);
		in("my_turn", ticket);
		
		int cnt, car_no;
		
		// get car that has been waiting for the longest time
		in("p_cnt", ?cnt);
		out("p_cnt", cnt);
		in("queue", cnt, ?car_no);
		
		// require car
		out("request", car_no, id);
		// wait for car to become free
		in("car_free", car_no);
		// wait for permission to use car
		in("car_permission", id, car_no);
		
		mutualBump();
		
		// finish ride
		out("ride_finished", car_no);
		// leave the car
		out("car_exit", car_no);
		
		// signal that next who is waiting in the row can proceed further
		out("my_turn", ticket + 1);
	}
}

void car(int id)
{	
	while(1)
	{
		// set car free
		out("car_free", id);
		
		// broadcast that I'm free to ride
		in("cnt", ?tt);
		out("cnt", tt + 1);
		out("queue", tt, id);
		
		int driver;
		// wait for next request
		in("request", id, ?driver);
		// give permission to use car
		out("car_permission", driver, id);
		
		// wait for 
		in("ride_finished", id);
		in("car_exit", id);
	}
}

void init()
{
	out("person_queue", 0);
	out("my_turn", 0);
	out("cnt", 0);
	out("p_cnt", 0);
	
	for (int i = 0; i < n; i++)
		eval(person(i));
	for (int i = 0; i < n; i++)
		eval(car(i));
}