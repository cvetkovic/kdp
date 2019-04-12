/*void cook()
{
	wait(cook);
	servings = M;
	signal(mutex);
}

void savage()
{
	wait(mutex);
	servings--;
	if (servings == 0)
		signal(cook);
	else
		signal(mutex);
}*/

[ savage :: SAVAGE(i:1..N) || food :: FOOD || cook :: COOK ]

FOOD::
[
	ammount:integer; ammount = 0;
	*[
		ammount > 0; (i:1..N)SAVAGE(i)?getFood() -> ammount--; 
													FOOD!gotFood();
		[]
		ammount = 0; (i:1..N)SAVAGE(i)?getFood() -> COOK!cook(); 
													COOK?cookingFinished(); 
													ammount = M;
													ammount--; 
													FOOD!gotFood();
	]
]

(i=1..N) SAVAGE(i)::
*[
	FOOD!getFood();
	FOOD?gotFood();
	
	eat();
]

COOK::
*[
	FOOD?cook();
	cook();
	FOOD!cookingFinished();
]