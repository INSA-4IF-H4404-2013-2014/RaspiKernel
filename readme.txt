Système de compilation V3

1) Régler les options
  > cp makeOptions.gitlocal.sample makeOptions.gitlocal
  > vim makeOptions.gitlocal

	Options importantes :
		- MODE (remote ou local)
			Permet de choisir de compiler sur sa machine, ou à distance.
			Par défaut si vous ne touchez à rien, le mode remote est activé.
			Notez que si vous voulez le mode local, il faudra installer le compilateur arm
			sur votre machine, puis régler les options BUILD_PREFIX et GDB_CMD.

		- REMOTE_USERNAME :
			Nom d'utilisateur Linux du départ'. À configurer pour une utilisation remote.
			CF tout en bas section annexes pour se faire une clef SSH.

		- SDCARD :
			Utilisée pour le déploiement automatique.
			Cette variable doit être réglée au chemin d'accès absolu vers la carte SD.
			Pour le trouver, insérez une fois la carte SD dans votre ordinateur,
			puis localisez le chemin de la partition contenant kernel.img à sa racine.
			Attention, cette carte SD possède deux partitions.


2) Fonctionnement
	make est appelable depuis le dossier racine du projet ou depuis chacune des applications.
	Les commandes suivantes changent leur comportement automatiquement selon que vous êtes en
	mode remote ou local.

	* Si vous êtes en mode local, rien de spécial dans le comportement à signaler.
	* Si vous êtes en mode remote, vos fichiers sont automatiquement envoyés avec "make send"
		avant que la compilation distante ne démarre si vous utilisez les commandes
		make ou make all.

	Imaginons que vous avez réglé makeOptions.gitlocal.sample sur MODE=local.
	Si vous voulez ponctuellement faire un seul make en mode remote, plutôt que de changer
	la configuration, vous pouvez lancer les commandes en rajoutant "MODE=remote" à la fin.
	Exemple :
		> make clean MODE=remote
		lancera le "make clean" à distance.


3) Commandes disponibles

	- Depuis le dossier racine
		> make
			Lance la compilation de toutes les apps. Seuls sont compilés les modules
			ayant été modifiés depuis la dernière fois (+ gestion des dépendances).
			Si vous êtes en mode remote, vos fichiers sont d'abord envoyés sur le serveur.

		> make clean
			Nettoie tous les dossiers build/ de toutes les apps.

		> make all
			Nettoie tous les dossiers build/ et recompile toutes les apps.
			Si vous êtes en mode remote, vos fichiers sont d'abord envoyés sur le serveur.

		> make send [ seulement en mode remote ! ]
			Envoie seulement les fichiers ayant changés sur le serveur indiqué dans les réglages.
			Normalement, vous ne devriez pas avoir besoin d'appeler "make send" puisqu'elle est
			appelée automatiquement (lors de make, make all).

	- Depuis un dossier d'application
		> make
			Lance la compilation de l'app courante. Seuls sont compilés les modules
			ayant été modifiés depuis la dernière fois (+ gestion des dépendances).
			Si vous êtes en mode remote, vos fichiers sont d'abord envoyés sur le serveur avec
			"make send".

		> make clean
			Nettoie le dossier build/ de l'app courante.

		> make all
			Nettoie le dossier build/ et recompile l'app courante.
			Si vous êtes en mode remote, vos fichiers sont d'abord envoyés sur le serveur.

		> make deploy
			Compile si besoin (make) puis déploie le kernel.img fraichement compilé
			automatiquement dans la carte SD indiquée dans la variable SDCARD.
			Cette commande appelle aussi juste après "make umount", qui démonte
			la carte SD (vous pouvez la retirer tout de suite et l'insérer dans le RaspPi)!

		> make sdcopy
			Permet de ne lancer que la copie du kernel.img dans la carte SD, sans rien compiler.

		> make umount
			Permet de ne lancer que le démontage de la carte SD.

		> make send [ seulement en mode remote ! ]
			Envoie seulement les fichiers ayant changés sur le serveur indiqué dans les réglages.
			Notez que même en appelant "make send" depuis un dossier d'application, les autres
			applications sont quand même envoyées sur le serveur.
			Normalement, vous ne devriez pas avoir besoin d'appeler "make send" puisqu'elle est
			appelée automatiquement (lors de make, make all).

		> make run
			Ne marche qu'en mode local (pour pouvoir voir gdb).
			Compile si besoin, lance l'é


4) Annexes :
	Utilisation d'une clef SSH pour le mode remote :
		Pour que ce mode soit utilisable, il est conseillé de vous faire
		une clef SSH. Sinon votre mot de passe pourra vous être demandé jusqu'à deux fois par
		commande (exemple "make" pour le rsync initial puis la compilation distante avec ssh).
		- Vérifiez si vous avez déjà une clef SSH.
			> ls ~/.ssh/id_rsa.pub
			Si vous en avez, vous pouvez sauter l'étape suivante.

		- Créez-vous une clef SSH si vous n'en avez pas :
			> ssh-key-gen -t rsa
			On vous demande une clef de verrouillage, vous pouvez en mettre une ou laisser vide.

		- Envoyez votre clef SSH sur le serveur distant :
			> ssh-copy-id -i ~/.ssh/id_rsa.pub votrepseudo@iftpserv2.insa-lyon.fr
			Entrez votre mot de passe de session Linux pour la dernière fois.
			La clef se copie sur la machine distante dans ~/.ssh/authorized_keys
			Les prochaines connexions n'auront plus besoin de mot de passe !
