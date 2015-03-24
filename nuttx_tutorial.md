On considère ici que l'utilisateur dispose d'une Debian 7 toute fraîche, sachant que celle-ci propose par défaut GCC pour x86-64 ainsi que python2.7.

Installation des outils

Il vous faut installer certains pré-requis:
Git

    sudo aptitude install git
    git config --global user.name "My Name" <-- à remplacer par votre nom
    git config --global user.email my.name@example.com <-- à remplacer par votre mail
    git config --global color.branch auto
    git config --global color.diff auto
    git config --global color.interactive auto
    git config --global color.status auto
    git config --global core.autocrlf false


ARM GCC

    télécharger https://launchpad.net/gcc-arm-embedded/4.9/4.9-2015-q1-update/+download/gcc-arm-none-eabi-4_9-2015q1-20150306-linux.tar.bz2
    extraire l'archive dans par example ~  (votre user home)
    ajouter ~/gcc-arm-none-eabi-4_9-2015q1/bin dans votre PATH, par exemple ajouter a la fin du ~/.bashrc la ligne [export PATH=$PATH:~/gcc-arm-none-eabi-4_9-2015q1/bin]


NuttX
La compilation de kconfig-frontends avec support de mconf (textuel) nécessite les paquets suivants

    sudo aptitutde install gperf libncurses5-dev flex bison automake autoconf


Récupération de NuttX depuis les sources (attention, version non supposée stable)

    git clone http://git.code.sf.net/p/nuttx/git ~/projects/nuttx-code


Compilation de kconfig spécifiquement pour NuttX (pour ne pas polluer une installation existante)

    cd ~/projects/nuttx-code/nx/misc/kconfig-frontends/
	mkdir ~/kconfig-nuttx
	ou 
	mkdir /home/[user]/kconfig-nuttx
	dans lequel [user] est votre nom de compte utilisateur

Si vous ne désirez que les versions texte+ncurses:

    ./configure --program-prefix=kconfig-nuttx- --prefix=/home/[user]/kconfig-nuttx --enable-frontends=nconf,mconf

sinon, à vous de voir ce qu'il manque en tapant:

    ./configure --program-prefix=kconfig-nuttx- --prefix=/home/[user]/kconfig-nuttx --enable-frontends=nconf,mconf,qconf,gconf


Build de kconfig

    make


Installation de kconfig

    make installcheck
	si OK alors
	make install

ou si pas administrateur sur la machine (par exemple en salle de TP IUT)

    make installcheck
	si OK alors
	make install
	puis
    ajout de kconfig dans votre PATH
    ajouter a la fin du ~/.bashrc la ligne [export PATH=$PATH:~/kconfig-nuttx/bin]


configuration de NuttX

    cd ~/projects/nuttx-code/tools
    ./configure.sh sam4s-xplained/nsh
	cd..
	APPSDIR=../apps kconfig-nuttx-mconf Kconfig
	
	pour chaque option, il y a une aide (appui sur h) qui est un peu cryptique par moment.
	
	
Téléversement sur la carte
- Segger JLink

- OpenOCD


Applications du projet terrarium (partie à complèter)

    git clone https://github.com/IUTInfoAix/terrarium_2015.git ~/projects/terrarium

    cd ~/projects/terrarium
    git checkout -b ma_partie_à_concevoir  <-- à remplacer par ce qui vous est identifié
    cd ma_partie_à_concevoir
    commencer à coder l'application qui vous est assignée :-D























