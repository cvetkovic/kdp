[ c :: COORDINATOR || p(i=1..N) :: PROCESS(i) ]]

COORDINATOR::
[
	free:integer; free = MAX_SPACE;
	*[
		QUEUE!hasSpace() -> b:boolean;
						    QUEUE?b;
							[b == true -> [PROCESS[i]?request(ammount) -> QUEUE::enqueue(i, ammount)]];
		[]
		PROCESS[i]?release(ammount) -> free += ammount;
		[]
		free > 0  ->   QUEUE?hasRequests(free);
					   b:boolean; 
					   QUEUE?b;
					   [b = true -> id, ammount:boolean;
									QUEUE?dequeue(id, ammount);
								    free -= ammount;
								    PROCESS[id]!confirm();
					   ]
		[]
	
	]
]

PROCESS(i)::
[
	ammount:integer; ammount = ...;
	
	COORDINATOR!request(ammount);
	COORDINATOR?confirm();
	...
	COORDINATOR!release(ammount);
]

QUEUE ::
	front, rear, cnt : integer; front = 0; rear = 0; cnt = 0;
	buffer1 : integer[N];
	buffer2 : integer[N];
	
	*[
		cnt != N; QUEUE?enqueue(t, u) -> i:integer; 
										 i = cnt;
										 [i >= 0 && u > buffer2[i] -> buffer2[i + 1] = buffer2[i];
																	  buffer1[i + 1] = buffer1[i];
										 ];
										 buffer1[i + 1] = t;
										 buffer2[i + 1] = u;
										 cnt++;
		[]
		COORDINATOR?hasRequests(free) -> b:boolean; 
									     b = false; 
									     [buffer2[front] <= free -> b = true];
									     COORDINATOR!b;
		[]
		cnt != 0; QUEUE?dequeue() -> COORDINATOR!next(buffer1[0], buffer1[0]);
		[]
		COORDINATOR?hasSpace() -> [cnt != N -> COORDINATOR!true;
								   cnt == N -> COORDINATOR!false;]
	]