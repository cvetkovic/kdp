[ c(i : 1..N) :: PROCESS || barrier :: BARRIER ]

BARRIER::
[
	count:integer; count = 0;
	
	*[
		count < N - 1; (i=1..N)PROCESS(i)?wait() -> count++;
		[]
		count = N; (i=1..N)PROCESS(i)?wait() -> i:integer; 
												i = 1;
												*[i <= N -> PROCESS(i)!proceed(); i++; ]
												count = 0;	
	]
]

PROCESS(i=1..N) ::
[
	*[  
		do_something();
		
		BARRIER!wait();
		BARRIER?proceed();
		
		do_something();
	]
]