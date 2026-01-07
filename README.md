ESERCIZIO 4 - Il Registro delle Renne di Babbo Natale
Gestisci le renne di Babbo Natale usando struct, pipe e allocazione dinamica.
Struct da usare:    [FOTO]
Il processo figlio (elfo responsabile delle renne) genera un numero casuale di renne tra 5 e 12
Per ogni renna genera:
nome nel formato "Renna_1", "Renna_2", ecc.
velocità casuale tra 50 e 100 km/h
resistenza casuale tra 1 e 10
L'elfo invia le renne una alla volta al padre tramite pipe
Quando ha finito, invia una renna sentinella con velocita = -1
Il padre (Babbo Natale) riceve le renne e le salva in un array allocato dinamicamente con malloc/realloc
Alla fine stampa tutte le renne ricevute e seleziona quella con velocità più alta dicendo: "Renna_X guiderà la slitta con velocità Y km/h!"
Libera correttamente la memoria con free()
