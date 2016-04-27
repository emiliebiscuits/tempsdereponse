# tempsdereponse
Utilisez la commande "make" du Makefile pour générer un exécutable.
Pour lancer une démonstration rapide, tapez "make demo".
NOTE : "make demo" génère automatiquement l’exécutable si celui-ci n'existe pas.

Pour lancer les tests du script python : python TP_tests.py
NOTE : Vous devez avoir Python installé, et avoir généré l'exécutable du programme.

Pour lancer un test personnalisé, tapez :
./TP_reel <nombre de tests> <attente> <dt> <sortie>
<attente> : passive (0) ou active (1)
<dt> : en microseconde
<sortie> : standard (0) ou fichier (1)

Si la sortie est défini en fichier, les outputs seront ajoutés au fichier "out_file.txt"
NOTE : Si celui-ci n'existe pas, il sera automatiquement généré.
