# Snake-Cpp

## Italiano

Il gioco Snake in C++, con grafica tramite SFML e una classifica dei punteggi persistente su file. Progetto personale sviluppato nel 2021.

**Stack:** C++ · SFML 2.x (Graphics/Window/System)

### Descrizione

Implementazione del gioco Snake in C++ con la libreria SFML per la grafica 2D, su una griglia 20×20. Include un menu iniziale, la logica di movimento del serpente, la generazione casuale del cibo, il rilevamento delle collisioni (con i bordi e con il proprio corpo) e una classifica persistente: i punteggi vengono salvati su file e, a fine partita, vengono mostrati i primi tre in ordine decrescente.

### Struttura del progetto

```
Snake-Cpp/
├── src/
│   └── main.cpp           # Logica di gioco, rendering e gestione degli eventi
├── assets/
│   ├── fonts/
│   │   └── arial.ttf      # Font utilizzato per i testi
│   └── images/
│       ├── snake.png      # Spritesheet del serpente
│       ├── frutta.png     # Sprite del cibo
│       └── campo.png      # Sfondo del campo
├── data/
│   └── punteggio.txt      # Classifica dei punteggi (persistente, generata/aggiornata a runtime)
├── dist/                  # Eseguibile Windows precompilato "pronto all'uso" + DLL richieste
│   ├── Snake.exe
│   ├── *.dll
│   ├── image/             # Copia degli asset nel formato atteso dal binario precompilato
│   └── file/
├── Makefile
├── LICENSE
└── README.md
```

### Come si esegue

**Eseguibile Windows precompilato:** nella cartella `dist/` trovi `Snake.exe` già pronto, insieme alle DLL richieste e a una copia degli asset necessari. Basta lanciarlo direttamente da dentro `dist/` (il binario si aspetta le sottocartelle `image/` e `file/` accanto a sé, così come erano organizzate quando è stato compilato).

**Ricompilare da sorgente (consigliato, multipiattaforma):**
1. Installa SFML 2.x, ad esempio:
   - Debian/Ubuntu: `sudo apt install libsfml-dev`
   - Altri sistemi: vedi [sfml-dev.org](https://www.sfml-dev.org/download.php) o usa vcpkg
2. Dalla **root del progetto**:
   ```
   make
   ```
   Questo compila `src/main.cpp` e genera l'eseguibile in `build/Snake`.
3. Esegui **sempre dalla root del progetto**, così i percorsi relativi verso `assets/` e `data/` restano validi:
   ```
   make run
   ```
   oppure, equivalentemente:
   ```
   ./build/Snake
   ```

Il vecchio `Makefile.win` (generato da Dev-C++, con percorsi assoluti della macchina di sviluppo originale) è stato rimosso e sostituito da un `Makefile` cross-platform basato su `g++`, senza percorsi hardcoded.

### Funzionalità principali

- Movimento del serpente su una griglia 20×20, con crescita di una unità a ogni cibo mangiato
- Blocco delle inversioni di direzione a 180° (non è possibile invertire la marcia direttamente su sé stessi)
- Generazione casuale del cibo in una cella libera, verificando che non si sovrapponga al corpo del serpente
- Rilevamento delle collisioni con i bordi del campo o con il proprio corpo, che termina la partita
- Punteggio incrementale (+100 per ogni cibo mangiato)
- Classifica persistente: il punteggio di ogni partita viene salvato su file (`data/punteggio.txt`) e, a fine partita, vengono mostrati i tre punteggi più alti registrati
- Interfaccia grafica 2D con sprite, texture e font renderizzati tramite SFML

### Licenza

MIT

---

## English

The classic Snake game in C++, with graphics powered by SFML and a persistent file-based high score list. Personal project developed in 2021.

**Stack:** C++ · SFML 2.x (Graphics/Window/System)

### Description

C++ implementation of Snake using the SFML library for 2D graphics, on a 20×20 grid. It includes a start menu, the snake's movement logic, random food spawning, collision detection (with the walls and with the snake's own body), and a persistent leaderboard: scores are saved to a file and, at the end of each match, the top three are displayed in descending order.

### Project structure

```
Snake-Cpp/
├── src/
│   └── main.cpp           # Game logic, rendering and event handling
├── assets/
│   ├── fonts/
│   │   └── arial.ttf      # Font used for text rendering
│   └── images/
│       ├── snake.png      # Snake spritesheet
│       ├── frutta.png     # Food sprite
│       └── campo.png      # Field background
├── data/
│   └── punteggio.txt      # Persistent high score list (created/updated at runtime)
├── dist/                  # Precompiled Windows executable, ready to run, + required DLLs
│   ├── Snake.exe
│   ├── *.dll
│   ├── image/             # Copy of the assets in the layout expected by the precompiled binary
│   └── file/
├── Makefile
├── LICENSE
└── README.md
```

### How to run

**Precompiled Windows executable:** `dist/` contains a ready-to-run `Snake.exe`, together with the required DLLs and a copy of the needed assets. Just launch it directly from inside `dist/` (the binary expects the `image/` and `file/` subfolders next to it, matching how they were laid out when it was compiled).

**Rebuilding from source (recommended, cross-platform):**
1. Install SFML 2.x, e.g.:
   - Debian/Ubuntu: `sudo apt install libsfml-dev`
   - Other systems: see [sfml-dev.org](https://www.sfml-dev.org/download.php) or use vcpkg
2. From the **project root**:
   ```
   make
   ```
   This compiles `src/main.cpp` and produces the executable at `build/Snake`.
3. Always run it **from the project root**, so the relative paths to `assets/` and `data/` resolve correctly:
   ```
   make run
   ```
   or equivalently:
   ```
   ./build/Snake
   ```

The old `Makefile.win` (generated by Dev-C++, with absolute paths from the original development machine) has been removed and replaced with a cross-platform `Makefile` based on `g++`, with no hardcoded paths.

### Key features

- Snake movement on a 20×20 grid, growing by one segment for each food item eaten
- Blocked 180° direction reversal (the snake can't turn directly back onto itself)
- Random food spawning on a free cell, checked against the snake's body to avoid overlap
- Collision detection with the field's walls or the snake's own body, ending the match
- Incremental scoring (+100 for each food item eaten)
- Persistent leaderboard: each match's score is saved to a file (`data/punteggio.txt`) and, at the end of the match, the three highest recorded scores are shown
- 2D graphical interface with sprites, textures and fonts rendered via SFML

### License

MIT
