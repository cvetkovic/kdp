// cobegin
co [i = 0 to n]
	a[i] = f(i);
	
// C-Linda	
for (int i = 0; i < n; i++)
	eval("process", f(i));

/* Cobegin i eval jesu načini na koji se uvodi konkurentnost u prošireni Pascal, odnosno C-Linda biblioteku, respektivno. One proizvode ekvivalentno dejtsvo u jeziku na kome su realizovane.

Cobegin/coend iskazi se realizuju kao pravljenje niti najčešće, ali mogu da budu i procesi. U Linda se konkurentnost realizuje pravljenjem novog procesa na nivou operativnog sistema i to dodavanjem torke putem eval funkcije gde parametri mogu da budu konstante ili same funkcije od kojih se samo prave novi procesi. 
Ovakva torka je aktivna i po njoj ne može da se pretražuje dok se svi novokreirani procesi ne završe, tj. vrate povratnu vrednost i tada značenje eval komande postaje kao out sa istim parametrima. Prevođenje C-Linda funkcija vrši Linda kompajler koji dodaje potreban kod za realizovanje svega navedenoga.

Jedna od razlika jeste i da je cobegin blokirajuća i da se iskazi ispod coend izvršavaju tek nakon što se završe svi procesi stvoreni u telu cobegin, dok je eval naredba neblokirajuća i program nastavlja sekvencijalno izvršavanje.
*/