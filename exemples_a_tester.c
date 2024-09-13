
// ls > infile | cat > test | " " | echo salam

// la premiere et la derniere commande doivent s'executer.
// puis message d'erreur du bash "bash:  : command not found"

//< infile > test cat > outfile -e

// seul les derniers redirections doivent etre executer Les autres redirections '<' on en tient pas compte.
// Pour les redirections '>' on open tout, on supprime le contenu de tout les outfile 
// sauf la derniere redir qu'on execute>.
// la commande qui s'execute ici c'est la [cat] [-e]