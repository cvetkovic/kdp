MEN :: 
*[	Monitor!menStart();
	FINISH_JOB;
	Monitor!menEnd();
]

WOMEN :: 
*[	Monitor!womenStart();
	FINISH_JOB;
	Monitor!womenEnd();
]

CHILD :: 
*[	Monitor!childStart();
	FINISH_JOB;
	Monitor!childEnd();
]

JANITOR :: 
*[	Monitor!janitorStart();
	FINISH_JOB;
	Monitor!janitorEnd();
]

MONITOR :: 
[
	numM, numW, numC, numJ, cnt : integer; nunM = 0; nunW = 0; nunC = 0; nunJ = 0; cnt = 0;
	*[
		cnt < N ->
					*[
						// MEN
						numW = 0; numJ = 0; MEN?menStart() -> numM++; cnt++;
						[]
						(numC == 0 || (numC != 0 && numM > 0); MEN?menEnd() -> numM--; cnt--;
						[]
						
						// WOMEN
						numM = 0; numJ = 0; WOMEN?womenStart() -> numW++; cnt++;
						[]
						(numC == 0 || (numC != 0 && numW > 0); WOMEN?womenEnd() -> numW--; cnt--;
						[]
						
						// CHILD
						(numM != 0 || numW != 0); numJ = 0; CHILD?childStart() -> numC++; cnt++;
						[]
						CHILD?childEnd() -> numC--; cnt--;
						[]
						
						// JANITOR
						cnt = 0; JANITOR?janitorStart() -> numJ++; cnt++;
						[]
						JANITOR?janitorEnd() -> numJ--; cnt--;
					]
		[]
		cnt >= N -> skip
	]
]