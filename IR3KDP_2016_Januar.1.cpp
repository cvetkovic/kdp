/*
Tie braker algoritam spada u weakly fair algoritme
i on je fer samo u specijalnom slučaju kada učestvuju
samo dva procesa jer tera da čeka onog koji je zadnji
došao, tj. pušta onog prvodošlog.

U opštem slučaju se garantuje da samo onaj koji je 
zadnji ušao u svaku iteraciju algoritma biva zakašnjen, 
dok redosled između prvog i svakog osim zadnjeg u toj 
iteraciji zavisi isključivo od raspoređivača operativnog
sistema i može da se dogodi da onaj koji je u prvoj iteraciji
bio predzadnji bude onaj ko će prvi da uđe u kritičnu sekciju.
Moguća je i varijanta da se to ne dogodi, pa da se ispoštuje
redosled pristizanja procesa od prve iteracije pa sve do
ulaska u kritičnu sekciju.

U svakom slučaju, garantuje se ulazak u kritičnu sekciju
u nekom trenutku svakome procesu.
*/