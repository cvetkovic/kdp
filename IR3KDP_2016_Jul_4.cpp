NORTH_CAR(i) ::
*[
    b:boolean; b = true;
	*[
		b-> Monitor!StartNorthCrossing();
			[ Monitor?AllowNorthCrossing() -> b = false;
			  []
			  Monitor!RemoveNorthQueue();
			]
	]
	CROSS;
	Monitor!FinishedNorthCrossing();
]

SOUTH_CAR ::
*[
    b:boolean; b = true;
	*[
		b-> Monitor!StartSouthCrossing();
			[ Monitor?AllowSouthCrossing() -> b = false;
			  []
			  Monitor!RemoveSouthQueue();
			]
	]
	CROSS;
	Monitor!FinishedSouthCrossing();
]

///////////////////////////////////////////////////

BRIDGE ::
	n_crossing, s_crossing, n_ahead, s_ahead : integer all initialize to 0;
	*[
		i:integer;
		
		true ->
		[
			s_crossing = 0; n_ahead < K; NORTH_CAR(i)?StartNorthCrossing() -> n_crossing++; 
																			  n_waiting--; 
																			  [s_waiting > 0 -> n_ahead++;]
																			  NORTH_CAR(i)!AllowNorthCrossing();
			[]
			NORTH_CAR(i)?FinishedNorthCrossing() -> n_crossing--; 
													[n_crossing = 0 -> s_ahead = 0]
			[]
			n_crossing = 0; s_ahead < K; SOUTH_CAR(i)?StartSouthCrossing() -> s_crossing++; 
																			  s_waiting--; 
																			  [n_waiting > 0 -> s_ahead++;]
																			  SOUTH_CAR(i)!AllowSouthCrossing();
			[]
			SOUTH_CAR(i)?FinishedSouthCrossing() -> s_crossing--; 
													[s_crossing = 0 -> n_ahead = 0]
			[]
			NORTH_CAR(i)?StartNorthCrossing() -> n_waiting++; 
			[]
			NORTH_CAR(i)?RemoveNorthQueue() -> n_waiting--;
			[]
			SOUTH_CAR(i)?StartSouthCrossing() -> s_waiting++; 
			[]
			SOUTH_CAR(i)?RemoveSouthQueue() -> s_waiting--;
		]
	]
	
///////////////////////////////////////////////////

[ bridge :: BRIDGE || n_car(1..50) : NORTH_CAR || s_car(1..50) : SOUTH_CAR ]