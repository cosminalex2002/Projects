# Championship - client/server project
## Descriere:
Championship este o aplicatie proiectata pe modelul client/server care are la baza un sistem
concurent scris in limbajul de programare C/C++. 
## Tehnologii utilizate:
## 1.  Protocol
  In cadrul proiectului Championship comunicarea intre server si client se realizeaza prin intermediului protocolului Transmission Control Protocol (TCP). Transmission Control Protocol
este unul dintre protocoalele de baza ale suitei de protocoale Internet. TCP este unul dintre
cele doua componente originale ale suitei (celalalt fiind reprezentat de Protocolul Internet (IP)),
astfel incat intreaga suita este frecvent mentionata ca stiva TCP/IP.
## 2. Baza de date
  Pentru stocarea utilizatorilor si administratorilor am folosit o baza de date SQLite. De asemenea, scorurile partidelor jucate vor fi pastrare intr-o baza de date pentru a afla, la finalul campionatului, echipa\jucatorul castigatoare \castigator.
SQLite este o biblioteca C care implementeaza un motor de baze de date SQL incapsulat si
ofera posibilitatea de a-l introduce in diverse sisteme.


### Functionalitati:
✔ inregistrarea utilizatorilor(diferite tipuri de utilizatori: obisnuiti, administratori)  
✔ toate comenzile sunt restrictionate de sectiunea de logare  
✔ dupa logare utilizatorii vor putea primi informatii despre ultimele campionate inregistrate, avand posibilitatea de a se inscrie la ele
#### Principalele comenzi implementate:
* inregistrarea unui campionat
* specificarea jocului
* specificarea numarului de jucatori, diferite reguli sau structuri de campionat(single-elimination, double elimination), modul de extragere a partidelor(deciderea partidelor)
* inregistrarea unui utiliziator intr-un campionat
* istoric al scorurilor partidelor.

