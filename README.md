WerCA
=====

Low cost smartwatch





This is a project for a low cost easy to build smartwatch, based on Atmel Atmega 328, PCD8544 display and nRf8001 Bluetooth low energy chip.

Here's an italian description of the project:

-Introduzione
=====
Con “Wearable Exploartion Technologies” si intende un progetto di ricerca e sviluppo riguardante tecnologie indossabili rivolte allo svago e alla produttività, con fine la realizzazione di un prototipo. Si intende quindi tralasciare il mondo delle tecnologie indossabili già esistente da tempo (si pensi al campo medico con i pacemaker), per rivolgersi a quello nascente della multimedialità e di internet, che, anche grazie allo sviluppo promosso dai grandi brand del mercato, sta acquistando sempre più importanza. I principali prodotti presenti sul mercato sono occhiali, integranti sistemi per l’acquisizione e la visualizzazione di dati (quali foto, video o messaggi e chiamate), e smartwatch, prodotti simili in dimensioni e forme ad orologi, in grado di connettersi al proprio smartphone visualizzando vari parametri quali chiamate perse, messaggi, musica in ascolto ed altre informazioni a seconda del prodotto.
Tra la prima tipologia di prodotti troviamo i Glass, prodotti da Google in collaborazione con Luxottica. Sicuramente più ampia è la seconda tipologia di prodotti, gli smartwatch. Troviamo affacciate sul mercato in questo campo varie aziende tra le quali Samsung, Sony, Pebble ed altre. Di seguito si procede ad un analisi dei più diffusi smartwatch.

-Analisi di mercato
=====
I’M WATCH:
Prezzo: da € 250
Dimensioni: 52,9 x 40,6 x 10 (in mm)
Display 1,54’’
Peso: g 95 (versione color)
Caratteristiche: 
Bluetooth tethering
Compatibile con: iOS 4.0 e successivi, Android 4 e successivi, Blackberry 10 (no SMS)
Memoria interna: 4 GB
Ram: 128 MB
Processore: IMX233
Funzioalità e descrizione:
i’m Watch interagisce con lo smartphone consentendo di visualizzare: email, sms, notifiche, social network, calendario, foto, contatti, meteo e tutte le applicazioni disponibili su i’market (store che raccoglie tutte le app per lo smartwatch);


SONY SMARTBAND SWR10:
Prezzo: € 90
Dimensioni: bracciale 
Display: no display
Peso: g 21
Caratteristiche: 
Impermeabile
3 LED
Tasti
Connessione/associazione NFC
Funzionalità e descrizione:
Permette di controllare le attività con avvisi di notifica e di controllare la musica da remoto. L’unità centrale è separabile dal cinturino, disponibile in vari colori; viene venduto con due cinturini (small e large).

SAMSUNG GEAR FIT:
Prezzo: € 180
Dimensioni: 57,4 x 23,4 x 11,95 
Display: 1.84" super AMOLED
Peso: g 21
Caratteristiche: 
Cardiofrequenzimetro
Accelerometro
Giroscopio
Funzionalità e caratteristiche:
Con Samsung Gear Fit ricevi subito notifiche di Email, SMS, chiamate in arrivo e app così sei sempre in contatto con il tuo mondo grazie al sensore di frequenza cardiaca integrato, Samsung Gear Fit ti supporta in tempo reale durante l'attività fisica e ti dà suggerimenti utili per raggiungere i tuoi obiettivi.

PEBBLE SMART WATCH:
Prezzo: € 150
Dimensioni: 97 x 76 x 66
Display: 1.26" e-ink
Peso: g 36
Caratteristiche: 
Accelerometro
Sensore ottico
Funzionalità e descrizione:
Puoi vedere le più importanti notifiche anche quando hai le mani occupate, potrai Music controllare la tua musica preferita mentre cammini, mentre corri o mentre guidi senza prendere lo smartphone in mano. Pebble può svegliarti in modo silenzioso con una leggera vibrazione al polso.
CST-01: THE WORLD'S THINNEST WATCH:
Prezzo: € 300
Spessore: 0,8 mm
Display: 1.26" e-ink
Peso: g 10
Caratteristiche: 
Sottilissimo
Batteria di lunghissima durata (45 giorni)
Funzionalità e descrizione:
Il braccialetto CST-01 viene prodotto laminando una serie di componenti flessibili al fine di creare un'unità con spessore di 0,8 mm e quest'ultima viene poi fissata fotochimicamente su una lastra sottilissima di acciaio inossidabile, andando a creare il prodotto finale. Ovviamente al momento si tratta di un semplice orologio e non certo di un device con capacità di e-Reader ma è un prodotto che potrebbe a breve schiudere nuove potenzialità per questo tipo di display.

-Hardware
=====
Analizzando la struttura delle due tipologie di prodotti, si denota una maggiore facilità e flessibilità nella realizzazione pratica di un prototipo con le nostre capacità produttive negli smartwatch.

L’idea di prototipo iniziale prevedeva un bracciale dalle dimensioni contenute con un LED RGB di segnalazione, che tramite un app su di uno smartphone connesso con la tecnologia Bluetooth 4.0 (aka BLE, Bluetooth Low Energy) trasferisse un comando per l’accensione del led con un determinata serie di colori prescelta dall’utente in caso di determinate notifiche sullo smartphone (chiamata persa, nuovo messaggio ecc.).
Durante la fase di sviluppo, è parsa evidente, però, l’impossibilità di proseguire per questa strada: i consumi del dispositivo sarebbero stati troppo elevati per essere gestiti da una batteria di ridotte dimensioni e l’autonomia ne avrebbe fortemente risentito.
Si è scelto quindi di sostituire al LED RGB un display LCD, dai consumi più contenuti.

La scelta del microprocessore, cuore dello smartwatch, è stata effettuata dopo un’analisi dei vari chip presenti sul mercato. Si è scelto un ATmega 320 data la sua compatibilità con l’ide di Arduino, che ne semplifica enormemente la programmazione e per la sua economicità. Dall’analisi si attende un arrivo di numerosi SoC (System on a Chip) tra la fine del secondo e l’inizio del terzo trimestre di quest’anno.

Come anticipato in precedenza, la visualizzazione dei dati avviene su di un display LCD. Si è scelto il display presente nei vecchi Nokia 5110 e 3310, pilotato dal controller Philips PCD8544, di facile reperibilità e dal basso costo.

La comunicazione tra lo smartwatch e lo smartphone è affidata al chip nRF8001, dal basso costo ed accompagnato da una vasta documentazione.

L'alimentazione non prevede un controllo della tensione, in quanto le tensioni massime e minime della batteria rientrano nei parametri operativi dei componenti. La ricarica della batteria è affidata ad un apposito modulo basato sul chip [nome chip].

Nota: nella realizzazione pratica si è optato per una verione di Arduino NANO modificata eliminando il regolatore di tensione AMS1117 5.0: dove prima era collegata l'uscita del regolatore è stato collegato il polo positivo della batteria da 3.7 volt. La pista che collegava il connettore USB al regolatore di tensione è stata collegata al caricatore della batteria. Le linee dati USB sono state lasciate inalterate: questo permette una riprogrammazione del dispositivo semplicemente collegandolo al computer tramite la porta USB e caricando il nuovo firmware, semplificando enormemente la procedura di aggiornamento ed evitando l'utilizzo di adattatori seriali esterni.

-Firmware
=====
Si consideri la dimensione del display (84 x 48) e del singolo carattere standard (5 x 7): considerando questi fattori, si ricava che il numero di notifiche massime visualizzabili è di quattro, con un aggiunta di una barra di stato sempre visibile in capo al display (altrezza di 11px).
Si sceglie di visualizzare le seguenti notifiche:
Chiamate perse
SMS
E-Mail
Altro.
Le icone occupano sempre la stessa posizione sullo schermo, quando visualizzate, per facilitare la lettura "a colpo d'occhio". Quando non sono presenti notifiche, l'orologio mostra data e ora a tutto schermo. L'ora e le notifiche vengono gestite ed aggiornate dall'app sullo smartphone. L'unico compito dell'Atmega è gestire il modoulo BLE e comunicare al display i dati ricevuti con la relativa grafica.

La comunicazione è simplex, da dispositivo a WerCA.

----- SPI div 16


