// Šta je raspodeljeni binarni semafor?

To je takav skup binarnih semafora (binarni je semafor onaj čija semaforska promenljiva uzima vrednost samo nula 
ili jedan) tako da samo jedan od njih može da ima vrednost jedan u nekom trenutku.

// Zašto su uvedeni?

Da bi se omogućila uslovna sinhronizacija.

// Da li se tim rešenjem smanjuje broj ukupno potrebnih semafora?

Ne, povećava se broj semafora semafora, ali se povećava i konkuretnost.

// Primer sa dva semafora koji čine raspodeljeni binarni semafor

Producer - consumer problem

Semaphore empty(1), full(0);

void produce()
{
	wait(empty);
	...
	signal(full);
}

void consume()
{
	wait(full);
	...
	signal(empty);
}