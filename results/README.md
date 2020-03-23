# Les résultats

## Les CSV

Tous les csv produits lors des tests sont dans les dossiers [grid5000](./grid5000) et [local](./local). Le dossier _local_ correspond aux tests de ma machine personnelle.

## Les graphiques

De multiples graphiques donnant des informations plus condensées sont présents dans ce dossier. Ils ont été générés grâce à _LibreOffice_ depuis le fichier [results.ods](./results.ods) (Oui je devrais utiliser R, mais je n'ai pas eu le temps d'apprendre).

Il y a donc des graphiques montrant l'évolution en échelle forte, avec une taille fixe pour les données et en échelle faible où l'augmentation de la taille des données s'accompagne d'une augmentation du nombre de threads. Pour l'échelle faible, à chaque fois, le dernier point utilise le nombre maximum de threads (32 pour grid5000) et ce nombre est divisé par 2 entre chaque point.

Les graphiques ne représentent que des données générées sur grid5000.

## Quelques remarques

L'algorithme de multiplication de matrices étant le plus lourd en calcul, il est beaucoup plus long que les autres et a son propre graphique.

Pour l'échelle fort sur les vecteurs de taille 10 000, l'algorithme _auto\_add_ dépasse largement l'échelle du graphique. La réduction semble peu efficace pour des petites tailles avec beaucoup de coeurs. Pour une taille de 100 millions, le passage à l'échelle est bien plus présent.

Le placement des threads sur les coeurs de calcul n'a pas été fixé, pendant l'exécution, des threads peuvent très bien switcher de coeurs (par action de l'OS) et donc perdre des données de cache. La machine était également un système NUMA à 2 noeuds. Tout ceci a sûrement influencé les performances.

Les algorithmes sur les matrices de caractères montre bien que les parallélisations naïve d'un code avec OpenMP sont parfois inefficace. Sur l'échelle fort avec une taille de 12 800\*12 800, l'algorithme naïf n'est d'ailleurs pas représenté car trop lent.
