Joc Snake Arduino - Cobuz Ionut-Alexandru

Elemente utilizate in crearea jocului
-matrice LED-uri 8x8
- driver Max7219
- Joystick
- display LCD

Cum functioneaza jocul

Startul si Sfarsitul :
-	Jocul incepe atunci cand este apasat butonul de pe Joystick
-	La inceput, pe ecran va aparea un mesaj de intampinare, si, ce sarpele mananca prima patratica va aparea scorul si gradul de dificultate la care s-a ajuns(viteza sarpelui)
-	Jocul se poate incheia in 2 situatii:
    - Sarpele acopera toate punctele de pe matrice, acesta fiind si finalul jocului, caz in care pe ecran se va mentiona ca jocul a fost castigat + scorul final
- Sarpele isi atinge coada, caz in care pe mesaj va aparea mesajul “Ai pierdut!” + scorul curent

Scorul si dificultatea:

-	Scorul creste progresiv, cu fiecare patratica pe care o mananca sarpele
-	Dificultatea progresiva este data de faptul ca viteza sarpelui creste cu fiecare patratica mancata( folosesc un delay care initial este 250ms si care scade cu 10 la fiecare patratica mancata)

Cum se joaca:

   Jocul incepe odata cu apasarea butonului de pe joystick.Sarpele are 4 directii de miscare (sus, jos, stanga, dreapta) si se misca cu ajutorul joystick-ului. Sarpele va executa singur ultima comanda, in caz ca joystick-ul nu mai primeste nicio comanda( de exemplu, daca ultima comanda a fost dreapta, atunci sarpele va merge singur dreapta pana cand va primi o noua comanda)
   La final, daca jocul este terminat ( fie ca este castigat sau pierdut), player-ul poate apasa din nou pe buton si jocul se va relua.
   
Implementare:

In implementare, avem o variabila in care retinem scorul, o variabila in care retinem viteza sarpelului( care se va modifica cu cat avansam in joc), un vector in care retinem sarpele(fiecare patratica din sarpe) si coordonatele patratelului care va fi “mancat”(coordonatele vor fi mereu random)

Vom avea functii pentru:
-	Mesaj de intampinare
-	Rularea jocului dupa apasarea butonului
-	Functie care generaza pozitia fructului pe matrice 
-	Functie in care verific daca sarpele mananca fructul (aici cresc scorul si viteza)
-	Functie care genereaza miscarea sarpelului si care trateaza toate cazurile deosebite( trecere prin perete , cazul in care joystick-ul nu primeste nicio comanda etc)
-	Functie care verifica daca sarpele moare(daca isi mananca coada)
-	Functie care reseteaza jocul
-	Mesajul final pentru castig/pierdere
-	Redimensionarea sarpelui dupa fiecare patratica mancata
