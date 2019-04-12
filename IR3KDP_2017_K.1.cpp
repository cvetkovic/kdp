/*
Kod ovakvih monitora razlikuju se tri reda za cekanje
1. entry queue - služi za obezbeđivanje međusobnog isključenja - mutex semafor
2. CV queue - poseban red za svaku od uslovnih promenljivih za obezveđivanje uslovne sinhronizacije - cv semafor
3. urgent queue - red čekanja onih nad kojima je izvršen signal & urgent wait - pq semafor
*/

// Svaka monitorska procedura je sledeceg oblika
wait(mutex);

// kod procedure

if (pq.count > 0)
	signal(pq);
else
	signal(mutex);

// Wait na uslvnoj promenljivoj
cv.count++;
if (pq.count > 0)
	signal(pq);
else
	signal(mutex);
wait(cv);
cv.count--;

// Signal and Urgent Wait na uslovnoj promenljivoj
if (cv.count > 0)
{
	pq.count++;
	signal(cv);
	wait(pq);
	pq.count--;
}

/* Signal operacija na semaforu na kome niko ne čeka omogućava da proces koji pozove wait u takvom stanju
prođe dalje jer će da ima 1 žeton, dok kod monitora u slučaju praznog reda za čekanje na uslovnoj promeljivoj
taj proces neće da ima žeton i biće blokiran. */