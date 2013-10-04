
——————————————— Tutoriel :
1) Faite vos modifications, pull, etc …
2) Compilez (> make).
3) Lancer l’emmulateur (> make run)
4) Lancer GDB dans un autre terminal (> make gdb)
5) Enjoy…
6) Quitez l’emmulateur et GDB


Command pour compiler :
  Cela recompile tout .c et .s ayant ete ajouter/modifier.
  En cas de modification d’un .h, les .c dependents seront
  re-compiler automatiquement. Tout les fichiers generer
  sont alors dans ./build/ invisible dans “git status”.
  > make

Lancer l’emmulateur :
  Re-compile automatiquement au besoin avant de lancer
  l’emmulateur.
  > make run

Lancer le debugger :
  Pout lancer GDB Vous devez simplement veillez a avoir
  lancer  l’emmulateur (make run) dans un autre terminal
  avant.
  > make gdb

Command pour nettoyer :
  > make clean

Command pour tout recompiler :
  > make full



