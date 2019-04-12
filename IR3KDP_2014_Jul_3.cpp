("data", BR_LETA, FROM, TO, TIME_DEP, DATE_DEP, TIME_ARR, DATE_ARR, CLASS, NUM);
("flight_state", BR_LETA, SEAT, STANJE);
("cnt", BR_LETA, PLANE_CAPACITY, PASSENGER_NUMBER);

// dat princip realizacije koji je potrebno da se dodatno sredi da bi radio na C/C++

enum State
{
	AVAILABLE,
	RESERVED,
	SOLD
}

struct FlightData
{
	int flightNo;
	
	string from;
	string to;
	
	int time_dep;
	int date_dep;
	int time_arr;
	int date_arr;
	
	int classNo;
	int seatNo;
	
	State state;
	
	int planeCapacity = -1;
}

void CreateFlight(FlightData fd)
{	
	in("mutex");
	for (int i = 0; i < fd.planeCapacity; i++)
	{
		out("data", 
			fd.flightNo,
			fd.from,
			fd.to,
			fd.time_dep,
			fd.date_dep,
			fd.time_arr,
			fd.date_arr,
			fd.classNo,
			fd.seatNo);
			
		out("cnt", fd.flightNo, fd.planeCapacity, 0);
	}
	out("mutex");
}

void MakeReservation(int flight, int seat, int holder)
{
	FlightData fd;
	
	in("mutex");
	if (rdp("data", flight, ?fd.FROM, ?fd.TO, ?fd.TIME_DEP, ?fd.DATE_DEP, ?fd.TIME_ARR, ?fd.DATE_ARR, ?fd.CLASS, seat))
	{
		int t;
		
		if (!rdp("ticket", flight, seatNo, State.RESERVED, ?t) && !rdp("ticket", flight, seatNo, State.SOLD, ?t))
		{
			rd("cnt", flight, ?cap, ?t))
				
			if (cap - t > 0) // ima mesta
				out("ticket", flight, seatNo, State.RESERVED, holder);
		}
	}
	out("mutex");
}

void BuyTicket(int flight, int seat, int holder = -1)
{
	FlightData fd;
	
	in("mutex");
	if (rdp("data", flight, ?fd.FROM, ?fd.TO, ?fd.TIME_DEP, ?fd.DATE_DEP, ?fd.TIME_ARR, ?fd.DATE_ARR, ?fd.CLASS, seat))
	{
		State s;
		int h;
		
		if (!inp("ticket", flight, seat, ?h, ?t) || (s == State.RESERVED && h == holder))
		{
			out("ticket", flight, seat, h, State.SOLD);
			
			in("cnt", flight, ?x, ?t);
			out("cnt", flight, x, t + 1);
		}
	}
	out("mutex");
}

void ConnectFlight()
{
	while (1)
	{
		in("mutex");
		
		List<FlightData, bool> f;
		FlightData tmp;
		
		while (inp("data", ?fd.BR_LETA, ?fd.FROM, ?fd.TO, ?fd.TIME_DEP, ?fd.DATE_DEP, ?fd.TIME_ARR, ?fd.DATE_ARR, ?fd.CLASS, ?fd.SEAT))
			f.addIfNotContainsFlightNumber(tmp); // imace duplikate za broj sedista
		
		for(Tuple<FlightData, bool> let : f)
		{
			for (int i = 0; i < f.count(); i++)
			{
				for (int j = 0; j < f.count(); j++)
				{
					int potrebno_mesta;
					int f1, f2, max, max1, max2;
					rd("cnt", f.BR_LETA, ?max, ?potrebno_mesta);
					rd("cnt", f.get(i).BR_LETA, ?max1, ?f1);
					rd("cnt", f.get(j).BR_LETA, ?max2, ?f2);
					
					if (!f.get(i).getBoolean() && // i se ne brise
						!f.get(j).getBoolean() && // j se ne brise
						f1 + potrebno_mesta <= max1 && 
						f2 + potrebno_mesta <= max2 &&
						f.get(i).FROM == let.FROM && 
						f.get(j).TO == let.TO &&
						f.get(i).DATE_DEP == let.DATE_DEP &&
						abs(f.get(i).TIME_DEP - let.TIME_DEP) <= 3 &&
						f.get(i).DATE_ARR == let.DATE_ARR)
					{
						f.remove(let);
						in("cnt", f.BR_LETA, ?PLANE_CAPACITY, ?PASSENGER_NUMBER);
						
						let.setBoolean(true); // pretpostavlja se da ide po referenci azuziranje u f
						
						int seat;
						Stanje st;
						while(inp("flight_state", f.BR_LETA, ?seat, ?st))
						{
							out("flight_state", f.get(i).BR_LETA, seat, st);
							out("flight_state", f.get(j).BR_LETA, seat, st);
							
							in("cnt", f.get(i).BR_LETA, ?PLANE_CAPACITY, ?t);
							in("cnt", f.get(i).BR_LETA, ?PLANE_CAPACITY, t + 1);
							in("cnt", f.get(j).BR_LETA, ?PLANE_CAPACITY, ?t);
							in("cnt", f.get(j).BR_LETA, ?PLANE_CAPACITY, t + 1);
						}
						
					}
				}
			}
		}
		
		for(Tuple<FlightData, bool> fd : f)
		{
			if (let.getBool())
			{
				in("cnt", fd.getFlightData.BR_LETA, ?t, ?t2);
				
				for (int i = 0; i < t; i++)
					out("data", fd.BR_LETA, fd.FROM, fd.TO, fd.TIME_DEP, fd.DATE_DEP, fd.TIME_ARR, fd.DATE_ARR, fd.CLASS, i))
			}
		}
		
		out("mutex");
	}
}

void Initialize()
{
	out("mutex");
	
	eval(CreateFlight(...));
	eval(MakeReservation(...));
	eval(BuyTicket(...));
	eval(ConnectFlight());
}