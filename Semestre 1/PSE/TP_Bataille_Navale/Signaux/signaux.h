

// Correspondance entre nom personnalisé et nom "officiel" pour les signaux employés.

// Indique à l'amiral le souhait de jouer (avec initialisation si nécessaire)
#define SIG_JEU SIGUSR1

// Demande au navire de s'inscrire dans le fichier
#define SIG_INFOS SIGUSR2

// Indique au navire qu'il a fini sont tour et doit réduire sont énérgie d'énergie
#define SIG_NRJ SIGABRT

// Indique au navire qu'il est pris pour cible
#define SIG_BCL SIGCHLD

// Indique au navire qu'il est le gagnant
#define SIG_WINNER SIGINT

// Indique au navire qu'il a été coulé
#define SIG_COULE SIGTRAP

