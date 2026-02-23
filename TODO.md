								ERREUR REPERTORIER

6 / certaine built-in semblent se lancer deux fois, notamment echo et pwd, a voir si il y en a pas plus
								ERREUR CORRIGER
copier coller les lignes repertorier qu'on a corriger ici et la supprimer des repertorier

1/	./minishell | < > << >>          -> avec seulement 1 op apres l'executable = segfault

2/	./minishell test | < > << >>     -> en finnissant par 1 op = segfault

3/	minishel>						 -> sans rien juste entrer, avec une ligne vide = segfault

4/	exit quitte quand meme si il y'a a trop d'arg alors qu'il ne devrais pas

5/	double check if (!str) dans exite peut etre que le deuxieme devrais etre if (!str[i]) ??

7/	env | sort | grep -v SHLVL | grep -v ^_ <-- Probleme pipeline, sort non realiser, grep SHLVL aussi pas realiser, grep ^_ pas realiser non plus


