#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>


// Fonction pour vérifier si le mot de passe satisfait à toutes les conditions
bool verifier_mot_de_passe(const char *mot_de_passe) {
    int longueur = strlen(mot_de_passe);
    bool a_majuscule = false;
    bool a_special = false;

    // Vérifier la longueur du mot de passe
    if (longueur < 8 || longueur > 20) {
        return false; // La longueur ne satisfait pas aux critères
    }

    // Vérifier la présence d'au moins une majuscule et un caractère spécial
    for (int i = 0; i < longueur; i++) {
        if (isupper(mot_de_passe[i])) {
            a_majuscule = true;
        } else if (ispunct(mot_de_passe[i])||isspace(mot_de_passe[i])) {
            a_special = true;
        }
    }
    
    return a_majuscule && a_special;
}

//Fonction pour verifier si une chaine est valide (nom, prenom,...)
bool valide(const char *chaine){
	int taille = strlen(chaine);
	for(int i=0; i<taille; i++){
		if(!isalpha(chaine[i])&&chaine[i]!= '-'){
			return false;
		}
	}
	return true;
}

//Fonction pour afficher un texte anime
void afficherTexteAnime(const char* texte) {
    int longueur = strlen(texte);
    for (int i = 0; i < longueur; i++) {
        printf("%c", texte[i]);
        fflush(stdout);  // Force l'affichage immédiat du caractère
        usleep(100000);  // Pause de 100 000 microsecondes (0.1 seconde)
    }
}


//Fonction permettant de sauvegarder les identifiants des utilisateurs
void sauvegarderIdentifiants(struct Administrateur *admins, int nbAdmins) {
    FILE *fichier = fopen("identifiants.txt", "w");
    //Gerer les erreurs d'ouverture de fichier
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    //Enregistrer les identifiants
    for (int i = 0; i < nbAdmins; i++) {
        fprintf(fichier, "%s %s\n", admins[i].nom_utilisateur, admins[i].mot_de_passe);
    }
    fclose(fichier);
}


//Fonction pour charger les identifiants des utilisateurs depuis un fichier
void lireIdentifiants(struct Administrateur *admins, int *nbAdmins) {
    FILE *fichier;
    //Creer le fichier s'il n'existe pas
    fichier = fopen("identifiants.txt", "a");
    fclose(fichier);
    fichier = fopen("identifiants.txt", "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    //initialiser le nombre d'administrateur
    *nbAdmins = 0;
    while (*nbAdmins < MAX_ADMINISTRATEURS && fscanf(fichier, "%99s %99s", admins[*nbAdmins].nom_utilisateur, admins[*nbAdmins].mot_de_passe) == 2) {
        (*nbAdmins)++;
    }
    fclose(fichier);
}

//Procedure pour saisir les identifiants
void saisirUtilisateur(struct Administrateur *admin) {
    printf("Nom d'utilisateur : ");
    scanf("%99s", admin->nom_utilisateur);
    printf("\nMot de passe : ");
    scanf("%99s", admin->mot_de_passe);
}


//Fonction pour gerer l'authentification d'un administrateur
int authentifier(struct Administrateur *admins, int nbAdmins, struct Administrateur *saisieAdmin) {
    for (int i = 0; i < nbAdmins; i++) {
        if (strcmp(saisieAdmin->nom_utilisateur, admins[i].nom_utilisateur) == 0 &&
            strcmp(saisieAdmin->mot_de_passe, admins[i].mot_de_passe) == 0) {
            return 1; // Authentification réussie
        }
    }
    return 0; // Échec de l'authentification
}


//Procedure pour ajouter un nouvel administrateur
void ajouterNouvelAdministrateur(struct Administrateur *admins, int *nbAdmins) {
    if (*nbAdmins < MAX_ADMINISTRATEURS) {
        do{
		    printf("Nom d'utilisateur : ");
		    scanf("%s",admins->nom_utilisateur);
		    if(!valide(admins->nom_utilisateur)){
			    printf(ROUGE"Nom invalide, veillez ressayer\n"RESET);
		    }
	    }while(!valide(admins->nom_utilisateur));
        printf("\n");
        do{
            printf("Mot de passe : ");
            scanf("%s", admins->mot_de_passe);
            if(!verifier_mot_de_passe(admins->mot_de_passe)){
                printf(ROUGE"Le mot de passe doit avoir entre 8 et 20 caracteres, avec au moins une majuscule et un caractere special\n"RESET);
            }
        }while(!verifier_mot_de_passe(admins->mot_de_passe));
        (*nbAdmins)++;
         
        FILE *fichier = fopen("identifiants.txt", "a");
        //Enregistrer les identifiants
        fprintf(fichier, "%s %s\n", admins->nom_utilisateur, admins->mot_de_passe);
        fclose(fichier);
        printf("Nouvel administrateur ajouté avec succès.\n");
    } else {
        printf("Le nombre maximal d'administrateurs a été atteint.\n");
    }
}


//Fonction pour verifier que l'utilisateur entre un entier
int saisirEntier() {
    int entier;
    int nombreDeCaracteresLus;
    while (1) {
        printf("\nVeillez entrer votre choix : ");
        nombreDeCaracteresLus = scanf("%d", &entier);
        // Vérification si l'entrée est un entier et si le nombre de caractères lus est correct
        if (nombreDeCaracteresLus == 1) {
            break;  // Sortir de la boucle si la saisie est un entier valide
        } else {
            printf("Entrée invalide. Veuillez entrer un entier.\n");
            // Nettoyer le tampon d'entrée
            while (getchar() != '\n');
        }
    }
    return entier;
}


// Fonction de recherche d'un élève par son matricule
int trouver_eleve_par_matricule(Classe *classe, const char *matricule) {
    for (int i = 0; i < classe->nombreEleves; i++) {
        if (strcmp(classe->eleves[i].matricule, matricule) == 0) {
            return i; // Retourne l'indice de l'élève dans le tableau
        }
    }
    return -1; // L'élève n'est pas trouvé
}

// Fonction d'initialisation d'une classe
void initialiser_classe(Classe *classe) {
    classe->nombreEleves = 0;
    classe->eleves = NULL;
}

// Fonction de chargement des élèves depuis un fichier
void charger_eleves(Classe *classe, const char *nomClasse) {
    FILE *fichier;
    char nomFichier[50];
    sprintf(nomFichier, "eleves_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        classe->eleves = (Eleve *)malloc(100 * sizeof(Eleve));  // Allocation dynamique
        if (classe->eleves == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
        while (fscanf(fichier, "%s %s %s %s %s %s",
                      classe->eleves[classe->nombreEleves].matricule,
                      classe->eleves[classe->nombreEleves].nom,
                      classe->eleves[classe->nombreEleves].prenom,
                      classe->eleves[classe->nombreEleves].sexe,
                      classe->eleves[classe->nombreEleves].nom_parent,
                      classe->eleves[classe->nombreEleves].contact_parent) == 6) {
            classe->nombreEleves++;
            if (classe->nombreEleves >= 100) {
                // Limiter le nombre d'élèves à 100
                break;
            }
        }
        fclose(fichier);
    }
}


// Fonction d'ajout d'un élève
void ajouter_eleve(Classe *classe, const char *nomClasse) {
    Eleve nouvelEleve;
    printf("Eleve %d\n", classe->nombreEleves + 1);
    char ch;
    /*
    Generer un matricule de 6 caracteres :
    2 caracteres pour l'annee
    1 caractere pour la classe
    Et 3 caracteres pour le numero
    */
    char matricule[7];
    if(strcmp(nomClasse, "6eme") == 0){
        ch = 'A';
    }
    else if(strcmp(nomClasse, "5eme") == 0) {
        ch = 'B';
    }
    else if(strcmp(nomClasse, "4eme") == 0) {
        ch = 'C';
    }
    else if(strcmp(nomClasse, "3eme") == 0) {
        ch = 'D';
    }
    else if(strcmp(nomClasse, "2nde") == 0) {
        ch = 'E';
    }
    else if(strcmp(nomClasse, "1ere") == 0) {
        ch = 'F';
    }
    else if(strcmp(nomClasse, "terminale") == 0) {
        ch = 'G';
    }
    int i=1;
    sprintf(matricule, "24%c%03d", ch, classe->nombreEleves+1);
    strcpy(nouvelEleve.matricule, matricule);
    //Verifier que le matricule est unique
    //Si oui, continuer, sinon generer un autre matricule
    int indice = trouver_eleve_par_matricule(classe, nouvelEleve.matricule);
    while(indice!=-1){
        sprintf(matricule, "24%c%03d", ch, classe->nombreEleves+i);
        strcpy(nouvelEleve.matricule, matricule);
        i++;
        indice = trouver_eleve_par_matricule(classe, nouvelEleve.matricule);
    }
    printf("Matricule: %s\n", nouvelEleve.matricule);
    do{
		printf("Nom: ");
		scanf("%s",nouvelEleve.nom);
		if(!valide(nouvelEleve.nom)){
			printf(ROUGE"Nom invalide, veillez ressayer\n"RESET);
		}
	}while(!valide(nouvelEleve.nom));
    do{
		printf("Prenom: ");
		scanf("%s",nouvelEleve.prenom);
		if(!valide(nouvelEleve.prenom)){
			printf(ROUGE"Prenom invalide, veillez ressayer\n"RESET);
		}
	}while(!valide(nouvelEleve.prenom));
    do{
        printf("Sexe(M/F): ");
        scanf("%s", nouvelEleve.sexe);
        if(strcmp(nouvelEleve.sexe,"M")!=0 && strcmp(nouvelEleve.sexe,"F")!=0){
            printf(ROUGE"Entree invalide!Reessayez\n"RESET);
        }
    } while(strcmp(nouvelEleve.sexe,"M")!=0 && strcmp(nouvelEleve.sexe,"F")!=0);
    do{
		printf("Nom parent: ");
		scanf("%s",nouvelEleve.nom_parent);
		if(!valide(nouvelEleve.nom_parent)){
			printf(ROUGE"Nom invalide, veillez ressayer\n"RESET);
		}
	}while(!valide(nouvelEleve.nom_parent));
    printf("Contact: ");
    scanf("%s", nouvelEleve.contact_parent);

    // Réallouer de la mémoire pour stocker les élèves
    classe->eleves = (Eleve *)realloc(classe->eleves, (classe->nombreEleves + 1) * sizeof(Eleve));
    classe->eleves[classe->nombreEleves] = nouvelEleve;
    classe->nombreEleves++;
    //Enregistrer les informations de l'eleve dans le fichier
    FILE *fichier;
    char nomFichier[50];
    sprintf(nomFichier, "eleves_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "a");
    if (fichier != NULL) {
        fprintf(fichier, "%s %s %s %s %s %s\n",
                nouvelEleve.matricule, nouvelEleve.nom,
                nouvelEleve.prenom, nouvelEleve.sexe,
                nouvelEleve.nom_parent, nouvelEleve.contact_parent);
        fclose(fichier);
    }
    printf("\n");
    afficherTexteAnime(VERT"L'élève a été ajouté à la classe avec succès.\n"RESET);
    usleep(1000000);
    system("clear");
}


// Fonction de modification d'un élève
void modifier_eleve(Classe *classe, const char *nomClasse, const char *matricule) {
    int indice = trouver_eleve_par_matricule(classe, matricule);    
    if (indice != -1) {
        Eleve *eleve = &(classe->eleves[indice]);
        autre:
        system("clear");
        printf("Quelle information voulez vous modifier?\n");
        printf("\n1- Nom\n");
        printf("\n2- Prenom\n");
        printf("\n3- Sexe\n");
        printf("\n4- Nom du parent\n");
        printf("\n5- Contact\n\n");
        int o = saisirEntier();
        switch (o){
            case 1:
                do{
                    system("clear");
		            printf("\nNom: ");
		            scanf("%s",eleve->nom);
		            if(!valide(eleve->nom)){
			            printf(ROUGE"Nom invalide, veillez ressayer\n"RESET);
		            }
	            }while(!valide(eleve->nom));
                break;
            case 2:
                do{
                    system("clear");
		            printf("Prénom: ");
		            scanf("%s",eleve->prenom);
		            if(!valide(eleve->prenom)){
			            printf(ROUGE"Nom invalide, veillez ressayer\n"RESET);
		            }
	            }while(!valide(eleve->prenom));
                break;
            case 3:
                do{
                    system("clear");
                    printf("Sexe(M/F): ");
                    scanf("%s", eleve->sexe);
                    if(strcmp(eleve->sexe,"M")!=0 && strcmp(eleve->sexe,"F")!=0){
                        printf(ROUGE"Entree invalide!Reessayez\n"RESET);
                    }
                } while(strcmp(eleve->sexe,"M")!=0 && strcmp(eleve->sexe,"F")!=0);
                break;
            case 4:
                do{
                    system("clear");
		            printf("Nom du parent: ");
		            scanf("%s",eleve->nom_parent);
		            if(!valide(eleve->nom_parent)){
			            printf(ROUGE"Nom invalide, veillez ressayer\n"RESET);
		            }
	            }while(!valide(eleve->nom_parent));
                break;
            case 5:
                system("clear");
                printf("Contact du parent: ");
                scanf("%s", eleve->contact_parent);
                break;
            default:
                printf(ROUGE"Choix invalide, ressayer\n"RESET);
                goto autre;
                break;
        }
        printf("\n\nVoulez-vous modifier une autre information?\n");
        printf("\n1- Oui\n");
        printf("\nAutre entier pour Non\n\n");
        int b = saisirEntier();
        if(b==1){
            goto autre;
        }

        //Enregistrer les mises a jour
        FILE *fichier;
        char nomFichier[50];
        sprintf(nomFichier, "eleves_%s.txt", nomClasse);
        fichier = fopen(nomFichier, "w");
        if (fichier != NULL) {
            for (int i = 0; i < classe->nombreEleves; i++) {
                fprintf(fichier, "%s %s %s %s %s %s\n",
                        classe->eleves[i].matricule, classe->eleves[i].nom,
                        classe->eleves[i].prenom, classe->eleves[i].sexe,
                        classe->eleves[i].nom_parent, classe->eleves[i].contact_parent);
            }
            fclose(fichier);
        }
        printf("\n");
        afficherTexteAnime(VERT"L'élève a été modifie avec succès.\n"RESET);
        usleep(1000000);
        system("clear");
    } else {
        system("clear");
        printf(ROUGE"Aucun élève trouvé avec le matricule fourni.\n"RESET);
        usleep(1000000);
    }
}


// Fonction de suppression d'un élève
void supprimer_eleve(Classe *classe, const char *nomClasse, const char *matricule, SoldeEleve *solde) {
    //Charger les soldes pour egalement supprimer les soldes dans le fichier
    charger_soldes(classe, nomClasse, solde);
    int indice = trouver_eleve_par_matricule(classe, matricule);
    if (indice != -1) {
        int i;
        for (i = indice; i < classe->nombreEleves - 1; i++) {
            classe->eleves[i] = classe->eleves[i + 1];
        }
        for (int i = indice; i < classe->nombreEleves - 1; i++) {
            solde[i] = solde[i + 1];
        }
        classe->nombreEleves--;
        FILE *fichier;
        char nomFichier[50];
        sprintf(nomFichier, "eleves_%s.txt", nomClasse);
        fichier = fopen(nomFichier, "w");
        if (fichier != NULL) {
            for (int i = 0; i < classe->nombreEleves; i++) {
                fprintf(fichier, "%s %s %s %s %s %s\n",
                        classe->eleves[i].matricule, classe->eleves[i].nom,
                        classe->eleves[i].prenom, classe->eleves[i].sexe,
                        classe->eleves[i].nom_parent, classe->eleves[i].contact_parent);
            }
            fclose(fichier);
        }
        enregistrer_soldes(classe, nomClasse,solde);
        printf("\n");
        afficherTexteAnime(VERT"L'élève a été supprime de la classe avec succès.\n"RESET);
        usleep(1000000);
        system("clear");
    } else {
        system("clear");
        printf(ROUGE"Aucun élève trouvé avec le matricule fourni.\n"RESET);
        usleep(1000000);
    }
}

//Afficher les infos d'un eleve en fonction du matricule fourni
void afficher_eleve(Classe *classe,  const char *matricule) {
    printf(VERT"\n----- Affichage de l'élève -----\n"RESET  );
    int indice = trouver_eleve_par_matricule(classe, matricule);
    if (indice != -1) {
        printf(BLEU"\n----- Élève %d -----\n"RESET, indice+1);
        printf("Matricule: %s\n", classe->eleves[indice].matricule);
        printf("Nom: %s\n", classe->eleves[indice].nom);
        printf("Prénom: %s\n", classe->eleves[indice].prenom);
        printf("Sexe: %s\n", classe->eleves[indice].sexe);
        printf("Nom parent: %s\n", classe->eleves[indice].nom_parent);
        printf("Contact parent: %s\n\n", classe->eleves[indice].contact_parent);
        
    }
    if (indice == -1) {
        system("clear");
        afficherTexteAnime(ROUGE"Aucun élève trouvé avec le matricule fourni.\n"RESET);
        usleep(1000000);
    }
}


//Afficher les informations des eleves d'une classe
void afficher_classe(Classe *classe, const char *nomClasse) {
    if (classe->nombreEleves == 0) {
        afficherTexteAnime(ROUGE"Aucun élève dans la classe.\n"RESET);
    }
    else {
        printf(VERT"\n----- Affichage de tous les élèves de la classe de %s-----\n"RESET, nomClasse);
        for (int i = 0; i < classe->nombreEleves; i++) {
            printf(BLEU"\n----- Élève %d -----\n"RESET, i + 1);
            printf("Matricule: %s\n", classe->eleves[i].matricule);
            printf("Nom: %s\n", classe->eleves[i].nom);
            printf("Prénom: %s\n", classe->eleves[i].prenom);
            printf("Sexe: %s\n", classe->eleves[i].sexe);
            printf("Nom parent: %s\n", classe->eleves[i].nom_parent);
            printf("Contact parent: %s\n", classe->eleves[i].contact_parent);
        }
    }
}


//Fonction pour definir les differents frais d'une classe
void definir_frais(Classe *classe, const char *nomClasse) {
    printf("Pour continuer vous devez d'abord definir les differents frais de la classe\n");
    printf("\nPour chaque frais, entrez le montant correspondant\n");
    // Demander à l'utilisateur de saisir les montants pour chaque type de frais
    printf("\nFrais de scolarité: ");
    scanf("%f", &(classe->frais.frais_scolarite));
    printf("\nFrais d'inscription: ");
    scanf("%f", &(classe->frais.frais_inscription));
    printf("\nFrais de cantine: ");
    scanf("%f", &(classe->frais.frais_cantine));
    printf("\nFrais de transport: ");
    scanf("%f", &(classe->frais.frais_transport));
    printf("\nFrais d'assurance: ");
    scanf("%f", &(classe->frais.frais_assurance));
    printf("\nFrais d'uniforme: ");
    scanf("%f", &(classe->frais.frais_uniforme));
//Sauvegarder dans un fichier
    FILE *fichier;
    char nomFichier[50];
    sprintf(nomFichier, "frais_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        fprintf(fichier, "%f %f %f %f %f %f\n",
                classe->frais.frais_scolarite, classe->frais.frais_inscription, 
                classe->frais.frais_cantine, classe->frais.frais_transport,
                classe->frais.frais_assurance, classe->frais.frais_uniforme);
        fclose(fichier);
    }
    printf("\n");
    afficherTexteAnime("Les frais de la classe de ");
    afficherTexteAnime(nomClasse); 
    afficherTexteAnime(" definis avec succès.\n");
    usleep(1000000);
    system("clear");
}


//Fonction de chargement des frais d'une classe depuis un fichier
void charger_frais(Classe *classe, const char *nomClasse){
    FILE *fichier;
    char nomFichier[50];
    sprintf(nomFichier, "frais_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        while (!feof(fichier)) {
            fscanf(fichier, "%f %f %f %f %f %f",
                   &classe->frais.frais_scolarite,
                   &classe->frais.frais_inscription,
                   &classe->frais.frais_cantine,
                   &classe->frais.frais_transport,
                   &classe->frais.frais_assurance,
                   &classe->frais.frais_uniforme);
        }
        fclose(fichier);
    }
}

//Fonction pour initialiser les soldes d'un eleve en fonction des frais predefinis
void initialiser_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde) {
    charger_frais(classe, nomClasse);
    solde[classe->nombreEleves].solde_scolarite = classe->frais.frais_scolarite;
    solde[classe->nombreEleves].solde_inscription = classe->frais.frais_inscription;
    solde[classe->nombreEleves].solde_cantine = classe->frais.frais_cantine;
    solde[classe->nombreEleves].solde_transport = classe->frais.frais_transport;
    solde[classe->nombreEleves].solde_assurance = classe->frais.frais_assurance;
    solde[classe->nombreEleves].solde_uniforme = classe->frais.frais_uniforme;
    FILE *fichier;
    char nomFichier[50];
    printf("%s", classe->eleves[classe->nombreEleves].matricule);
    sprintf(nomFichier, "soldes_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "a");
    if (fichier != NULL) {
        fprintf(fichier, "%.2f %.2f %.2f %.2f %.2f %.2f\n",
            solde[classe->nombreEleves].solde_scolarite,
            solde[classe->nombreEleves].solde_inscription,
            solde[classe->nombreEleves].solde_cantine,
            solde[classe->nombreEleves].solde_transport,
            solde[classe->nombreEleves].solde_assurance,
            solde[classe->nombreEleves].solde_uniforme);
        
        fclose(fichier);
    }
}

void definir_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde){
    charger_frais(classe, nomClasse);
    solde[classe->nombreEleves].solde_scolarite = classe->frais.frais_scolarite;
    solde[classe->nombreEleves].solde_inscription = classe->frais.frais_inscription;
    int ex;
    printf("\nDe quel frais cet eleve est-il excepte?\n");
    printf("\nFrais de cantine (1- oui/ Autre entier pour non): ");
    ex = saisirEntier();
    if(ex==1){    
        solde[classe->nombreEleves].solde_cantine = -1;
    }
    else{
        solde[classe->nombreEleves].solde_cantine = classe->frais.frais_cantine;
    }
    printf("\nFrais de transport (1- oui/ Autre entier pour non): ");
                                ex = saisirEntier();
                                if(ex==1){    
                                    solde[classe->nombreEleves].solde_transport = -1;
                                }
                                else{
                                    solde[classe->nombreEleves].solde_transport = classe->frais.frais_transport;
                                }
                                printf("\nFrais de assurance (1- oui/ Autre entier pour non): ");
                                ex = saisirEntier();
                                if(ex==1){    
                                    solde[classe->nombreEleves].solde_assurance = -1;
                                }
                                else{
                                    solde[classe->nombreEleves].solde_assurance = classe->frais.frais_assurance;
                                }
                                printf("\nFrais d'uniforme (1- oui/ Autre entier pour non): ");
                                ex = saisirEntier();
                                if(ex==1){    
                                    solde[classe->nombreEleves].solde_uniforme = -1;
                                }
                                else{
                                    solde[classe->nombreEleves].solde_uniforme = classe->frais.frais_uniforme;
                                }
                                FILE *fichier;
                                char nomFichier[50];
                                printf("%s", classe->eleves[classe->nombreEleves].matricule);
                                sprintf(nomFichier, "soldes_%s.txt", nomClasse);
                                fichier = fopen(nomFichier, "a");
                                if (fichier != NULL) {
                                    fprintf(fichier, "%.2f %.2f %.2f %.2f %.2f %.2f\n",
                                        solde[classe->nombreEleves].solde_scolarite,
                                        solde[classe->nombreEleves].solde_inscription,
                                        solde[classe->nombreEleves].solde_cantine,
                                        solde[classe->nombreEleves].solde_transport,
                                        solde[classe->nombreEleves].solde_assurance,
                                        solde[classe->nombreEleves].solde_uniforme);
                                }
                                fclose(fichier);
                            
}

//Enregistrer les soldes dans un fichier
void enregistrer_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde){
    FILE *fichier;
    char nomFichier[50];
    sprintf(nomFichier, "soldes_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        for(int i = 0; i< classe->nombreEleves;i++){
            fprintf(fichier, "%.2f %.2f %.2f %.2f %.2f %.2f\n",
                solde[i].solde_scolarite,
                solde[i].solde_inscription,
                solde[i].solde_cantine,
                solde[i].solde_transport,
                solde[i].solde_assurance,
                solde[i].solde_uniforme);
        }
        fclose(fichier);
    }
}


//Charger les soldes des eleves de la classe depuis un fichier
void charger_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde) {
    FILE *fichier;
    char nomFichier[50];
    sprintf(nomFichier, "soldes_%s.txt", nomClasse);
    fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        for (int i = 0; i < classe->nombreEleves; i++) {
            fscanf(fichier, "%f %f %f %f %f %f",
                   &solde[i].solde_scolarite,
                   &solde[i].solde_inscription,
                   &solde[i].solde_cantine,
                   &solde[i].solde_transport,
                   &solde[i].solde_assurance,
                   &solde[i].solde_uniforme);
        }
        fclose(fichier);
    }
}

//Fonction pour effectuer un paiement
int effectuer_paiement(Classe *classe, const char *nomClasse, SoldeEleve *solde, float *montant_du, float *montant_paye, const char *nomAdmin) {
    char matricule[20];
    charger_soldes(classe, nomClasse, solde);
    charger_frais(classe, nomClasse);
    float tranches_scolaite;
    printf("\nEntrez le matricule de l'élève pour le paiement : ");
    scanf("%s", matricule);
    int indice = trouver_eleve_par_matricule(classe, matricule);
    if (indice != -1) {
        montant_du[0] = solde[indice].solde_scolarite;
        montant_du[1] = solde[indice].solde_inscription;
        montant_du[2] = solde[indice].solde_cantine;
        montant_du[3] = solde[indice].solde_transport;
        montant_du[4] = solde[indice].solde_assurance;
        montant_du[5] = solde[indice].solde_uniforme;
        float montant_paiement;
        frais:
        system("clear");
        printf("Choisir le frais pour lequel vous voulez effectuer le paiement\n");
        printf("\n1- Frais de scolarite\n");
        printf("\n2- Frais d'inscription\n");
        printf("\n3- Frais de cantine\n");
        printf("\n4- Frais de transport\n");
        printf("\n5- Frais d'assurance\n");
        printf("\n6- Frais d'uniforme\n");
        int t;
        essaie:
        t = saisirEntier();
        if(t==1){
            if(solde[indice].solde_scolarite == 0){
                system("clear");
                printf("\n");
                afficherTexteAnime("L'eleve a fini de payer ce frais.\n");
                usleep(1000000);
            }
            // Mettez à jour les soldes de l'élève
            if(solde[indice].solde_scolarite!=0){
                system("clear");
                printf("\nEntrez le montant du paiement : ");
                scanf("%f", &montant_paiement);
                //if()
                if(montant_paiement<=solde[indice].solde_scolarite){
                    solde[indice].solde_scolarite -= montant_paiement;
                    montant_paye[0] = montant_paiement;
                }
                else{
                    printf("\nVous devez %.2f a cet eleve\n", (montant_paiement - solde[indice].solde_scolarite));
                    montant_paye[0] = solde[indice].solde_scolarite;
                    solde[indice].solde_scolarite = 0;
                }
            }
        }
        if(t==2){
            if(solde[indice].solde_inscription == 0){
                system("clear");
                printf("\n");
                afficherTexteAnime("L'eleve a fini de payer ce frais.\n");
                usleep(1000000);
            }
            // Mettez à jour les soldes de l'élève
            if(solde[indice].solde_inscription!=0){
                system("clear");
                printf("\nEntrez le montant du paiement : ");
                scanf("%f", &montant_paiement);
                if(montant_paiement<=solde[indice].solde_inscription){
                    solde[indice].solde_inscription -= montant_paiement;
                    montant_paye[1] = montant_paiement;
                }
                else{
                    printf("\nVous devez %.2f a cet eleve\n", (montant_paiement - solde[indice].solde_inscription));
                    montant_paye[1] = solde[indice].solde_inscription;
                    solde[indice].solde_inscription = 0;
                }
            }
        }

        if(t==3){
            if(solde[indice].solde_cantine == 0){
                system("clear");
                printf("\n");
                afficherTexteAnime("\nL'eleve a fini de payer ce frais.\n");
                usleep(1000000);
            }
            // Mettez à jour les soldes de l'élève
            if(solde[indice].solde_cantine>0){
                system("clear");
                printf("\nEntrez le montant du paiement : ");
                scanf("%f", &montant_paiement);
                if(montant_paiement<=solde[indice].solde_cantine){
                    solde[indice].solde_cantine -= montant_paiement;
                    montant_paye[2] = montant_paiement;
                }
                else{
                    printf("\nVous devez %.2f a cet eleve\n", (montant_paiement - solde[indice].solde_cantine));
                    montant_paye[2] = solde[indice].solde_cantine;
                    solde[indice].solde_cantine = 0;
                }
            }
            if(solde[indice].solde_cantine<0){
                printf("\nL'eleve a ete exempte de ce frais\n");
            }
        }

        if(t==4){
            if(solde[indice].solde_transport == 0){
                system("clear");
                printf("\n");
                afficherTexteAnime("L'eleve a fini de payer ce frais.\n");
                usleep(1000000);
            }
            // Mettez à jour les soldes de l'élève
            if(solde[indice].solde_transport>0){
                system("clear");
                printf("\nEntrez le montant du paiement : ");
                scanf("%f", &montant_paiement);
                if(montant_paiement<=solde[indice].solde_transport){
                    solde[indice].solde_transport -= montant_paiement;
                    montant_paye[3] = montant_paiement;
                }
                else{
                    printf("Vous devez %.2f a cet eleve\n", (montant_paiement - solde[indice].solde_transport));
                    montant_paye[3] = solde[indice].solde_transport;
                    solde[indice].solde_transport = 0;
                }
            }
            if(solde[indice].solde_transport<0){
                printf("\nL'eleve a ete exempte de ce frais\n");
            }
        }

        if(t==5){
            if(solde[indice].solde_assurance == 0){
                system("clear");
                printf("\n");
                afficherTexteAnime("L'eleve a fini de payer ce frais.\n");
                usleep(1000000);
            }
            // Mettez à jour les soldes de l'élève
            if(solde[indice].solde_assurance>0){
                system("clear");
                printf("\nEntrez le montant du paiement : ");
                scanf("%f", &montant_paiement);
                if(montant_paiement<=solde[indice].solde_assurance){
                    solde[indice].solde_assurance -= montant_paiement;
                    montant_paye[4] = montant_paiement;
                }
                else{
                    printf("\nVous devez %.2f a cet eleve\n", (montant_paiement - solde[indice].solde_assurance));
                    montant_paye[4] = solde[indice].solde_assurance;
                    solde[indice].solde_assurance = 0;
                }
            }
            if(solde[indice].solde_assurance<0){
                printf("\nL'eleve a ete exempte de ce frais\n");
            }
        }

        if(t==6){
            if(solde[indice].solde_uniforme == 0){
                system("clear");
                printf("\n");
                afficherTexteAnime("L'eleve a fini de payer ce frais.\n");
                usleep(1000000);
            }
            // Mettez à jour les soldes de l'élève
            if(solde[indice].solde_uniforme>0){
                system("clear");
                printf("\nEntrez le montant du paiement : ");
                scanf("%f", &montant_paiement);
                if(montant_paiement<=solde[indice].solde_uniforme){
                    solde[indice].solde_uniforme -= montant_paiement;
                    montant_paye[5] = montant_paiement;
                }
                else{
                    printf("\nVous devez %.2f a cet eleve\n", (montant_paiement - solde[indice].solde_uniforme));
                    montant_paye[5] = solde[indice].solde_uniforme;
                    solde[indice].solde_uniforme = 0;
                }
            }
            if(solde[indice].solde_uniforme<0){
                printf("\nL'eleve a ete exempte de ce frais\n");
            }
        }

        if(t!=1&&t!=2&&t!=3&&t!=4&&t!=5&&t!=6){
            afficherTexteAnime(ROUGE"\nChoix incorrecte, reessayer: "RESET);
            goto essaie;
        }

        printf("\n1- Effectuer un autre paiement\n");
        printf("\n0- Terminer le paiement\n");
        int y;
        y = saisirEntier();

        if(y==1){
            goto frais;
        }
        printf("\n");
        afficherTexteAnime("Paiement effectué avec succès.\n");
        enregistrer_soldes(classe, nomClasse, solde);
        generer_facture(classe, nomClasse, solde,montant_du, montant_paye, indice, nomAdmin);
       

    }
    
    else {
        system("clear");
        printf("\n");
        afficherTexteAnime(ROUGE"Aucun élève trouvé avec le matricule fourni.\n"RESET);
        usleep(1000000);
    }
     return indice;
}


//Afficher les soldes d'un eleve 
void afficher_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde) {
    char matricule[20];
    charger_soldes(classe, nomClasse, solde);
    printf("\nEntrez le matricule de l'élève pour afficher le solde : ");
    scanf("%s", matricule);

    int indice = trouver_eleve_par_matricule(classe, matricule);
    if (indice != -1) {
        printf(BLEU"----- Solde de l'élève -----\n"RESET);
        printf("\nMatricule : %s\n", matricule);
        printf("Nom: %s\n", classe->eleves[indice].nom);
        printf("Prenom: %s\n", classe->eleves[indice].prenom);
        printf("Classe: %s\n", nomClasse);
        printf("\nSolde de scolarité : %.2f\n", solde[indice].solde_scolarite);
        printf("\nSolde d'inscription: %.2f\n", solde[indice].solde_inscription);
        if(solde[indice].solde_cantine<0){
            printf("\nSolde de cantine: ---\n");
        }
        else{
            printf("\nSolde de cantine: %.2f\n", solde[indice].solde_cantine);
        }
        if(solde[indice].solde_transport<0){
            printf("\nSolde de transport: ---\n");
        }
        else{
            printf("\nSolde de transport: %.2f\n", solde[indice].solde_transport);
        }
        if(solde[indice].solde_assurance<0){
            printf("\nSolde de assurance: ---\n");
        }
        else{
            printf("\nSolde de assurance: %.2f\n", solde[indice].solde_assurance);
        }
        if(solde[indice].solde_uniforme<0){
            printf("\nSolde d'uniforme: ---\n");
        }
        else{
            printf("\nSolde de uniforme: %.2f\n", solde[indice].solde_uniforme);
        }
    } else {
        system("clear");
        afficherTexteAnime(ROUGE"Aucun élève trouvé avec le matricule fourni.\n"RESET);
        usleep(1000000);
    }
    
}

// Fonction de libération de la mémoire allouée pour les élèves
void liberer_memoire_eleves(Classe *classe) {
    free(classe->eleves);
    classe->eleves = NULL;
}


//Generer une facture sous forme d'un fichier texte
void generer_facture(Classe *classe, const char *nomClasse, SoldeEleve *solde, float *montant_du, float *montant_paye, int indice, const char *nomAdmin) {
    charger_soldes(classe, nomClasse, solde);
    if (indice != -1) {
        FILE *facture;
        char nomFichier[50];
        sprintf(nomFichier, "facture_%s_%s.txt", nomClasse, classe->eleves[indice].matricule);
        facture = fopen(nomFichier, "a");

        if (facture != NULL) {
            // Obtenir la date actuelle
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);

            fprintf(facture, "----- Facture -----\n");
            fprintf(facture, "Date : %02d/%02d/%d %02d:%02d\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
                    tm_info->tm_hour, tm_info->tm_min);
            fprintf(facture, "Matricule : %s\n", classe->eleves[indice].matricule);
            fprintf(facture, "Nom : %s\n", classe->eleves[indice].nom);
            fprintf(facture, "Prénom : %s\n", classe->eleves[indice].prenom);
            fprintf(facture, "sexe : %s\n", classe->eleves[indice].sexe);
            fprintf(facture, "Classe : %s\n", nomClasse);

            const char *categories[] = {"Scolarité", "Inscription", "Cantine", "Transport", "Assurance", "Uniforme"};

            fprintf(facture, "\n%20s | %10s | %10s | %10s\n", "Catégorie", "Montant du", "Montant payé", "Reste");
            fprintf(facture, "--------------------------------------------------------------------------\n");

            float reste[6] = {0,0,0,0,0,0};
            for (int i = 0; i < 6; i++) {
                switch (i) {
                    case 0: reste[i] = solde[indice].solde_scolarite; break;
                    case 1: reste[i] = solde[indice].solde_inscription; break;
                    case 2: reste[i] = solde[indice].solde_cantine; break;
                    case 3: reste[i] = solde[indice].solde_transport; break;
                    case 4: reste[i] = solde[indice].solde_assurance; break;
                    case 5: reste[i] = solde[indice].solde_uniforme; break;
                }
            }

            for (int i = 0; i < 6; i++) {
                if(montant_du[i]<0){
                    fprintf(facture, "%20s |     ---    |     ---    |     ----\n", categories[i]);
                }
                else{
                    fprintf(facture, "%20s | %10.2f | %10.2f | %10.2f\n", categories[i], montant_du[i], montant_paye[i], reste[i]);
                }
            }

            float total = 0;
            for (int i = 0; i < 6; i++) {
                switch (i) {
                    case 0: total += solde[indice].solde_scolarite; break;
                    case 1: total += solde[indice].solde_inscription; break;
                    case 2: 
                        if(solde[indice].solde_cantine>=0){
                            total += solde[indice].solde_cantine; 
                       
                        }
                         break;
                    case 3: 
                        if(solde[indice].solde_transport>=0){
                            total += solde[indice].solde_transport; 
                       
                        }
                         break;
                    case 4: 
                        if(solde[indice].solde_assurance>=0){
                            total += solde[indice].solde_assurance; 
                       
                        }
                         break;
                    case 5: 
                        if(solde[indice].solde_uniforme>=0){
                            total += solde[indice].solde_uniforme; 
                       
                        }
                         break;
                }
            }

            fprintf(facture, "--------------------------------------------------------------------------\n");
            fprintf(facture, "%20s | %10s | %10s | %10.2f\n", "Total", "", "", total);
            fprintf(facture,"\n\n                                            Administrateur: %s\n ", nomAdmin);

            fclose(facture);

        } else {
            printf(ROUGE"Erreur lors de la génération de la facture.\n"RESET);
        }
    }
}


//Afficher la facture qui a ete generer
void afficher_facture(Classe *classe, const char *nomClasse, SoldeEleve *solde, float *montant_du, float *montant_paye, int indice, const char *nomAdmin) {
    system("clear");
    charger_soldes(classe, nomClasse, solde);
    if (indice != -1) {
            // Obtenir la date actuelle
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);

            printf("----- Facture -----\n");
            printf("Date : %02d/%02d/%d %02d:%02d\n", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900,
                    tm_info->tm_hour, tm_info->tm_min);
            printf("Matricule : %s\n", classe->eleves[indice].matricule);
            printf("Nom : %s\n", classe->eleves[indice].nom);
            printf("Prénom : %s\n", classe->eleves[indice].prenom);
            printf("sexe : %s\n", classe->eleves[indice].sexe);
            printf("Classe : %s\n", nomClasse);

            const char *categories[] = {"Scolarité", "Inscription", "Cantine", "Transport", "Assurance", "Uniforme"};

            printf("\n%20s | %10s | %10s | %10s\n", "Catégorie", "Montant du", "Montant payé", "Reste");
            printf("--------------------------------------------------------------------------\n");

            float reste[6] = {0,0,0,0,0,0};
            for (int i = 0; i < 6; i++) {
                switch (i) {
                    case 0: reste[i] = solde[indice].solde_scolarite; break;
                    case 1: reste[i] = solde[indice].solde_inscription; break;
                    case 2: reste[i] = solde[indice].solde_cantine; break;
                    case 3: reste[i] = solde[indice].solde_transport; break;
                    case 4: reste[i] = solde[indice].solde_assurance; break;
                    case 5: reste[i] = solde[indice].solde_uniforme; break;
                }
            }

            for (int i = 0; i < 6; i++) {
                if(montant_du[i]<0){
                    printf("%20s |     ---    |     ---    |     ----\n",categories[i]);
                }
                else{
                    printf("%20s | %10.2f | %10.2f | %10.2f\n", categories[i], montant_du[i], montant_paye[i], reste[i]);
                }
            }

            float total = 0;
            for (int i = 0; i < 6; i++) {
                switch (i) {
                    case 0: total += solde[indice].solde_scolarite; break;
                    case 1: total += solde[indice].solde_inscription; break;
                    case 2: 
                        if(solde[indice].solde_cantine>=0){
                            total += solde[indice].solde_cantine; 
                       
                        }
                         break;
                    case 3: 
                        if(solde[indice].solde_transport>=0){
                            total += solde[indice].solde_transport; 
                       
                        }
                         break;
                    case 4: 
                        if(solde[indice].solde_assurance>=0){
                            total += solde[indice].solde_assurance; 
                       
                        }
                         break;
                    case 5: 
                        if(solde[indice].solde_uniforme>=0){
                            total += solde[indice].solde_uniforme; 
                       
                        }
                         break;
                }
            }

            printf("--------------------------------------------------------------------------\n");
            printf("%20s | %10s | %10s | %10.2f\n", "Total", "", "", total);
            printf("\n\n                                            Administrateur: %s\n ", nomAdmin);
    }
            
}


//Etablir les statistiques d'une classe sur le paiement des differents frais
void statistiques_classe(Classe *classe, const char *nomClasse, SoldeEleve *solde){
    charger_frais(classe, nomClasse);
    charger_soldes(classe, nomClasse, solde);
    printf(VERT"Statistiques de la classe de %s\n"RESET, nomClasse);
    printf("\nEffectif: %d eleves\n", classe->nombreEleves);
    printf(BLEU"\n----------Frais de scolarite----------\n"RESET);
    float scolarite = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        scolarite += solde[i].solde_scolarite;
    }
    printf("\nMontant paye: %.2f\n", ((classe->nombreEleves*classe->frais.frais_scolarite) - scolarite));
    printf("Reste a payer: %.2f\n", scolarite);
    printf("Taux de paiement: %.2f%%\n", (1 - (scolarite/(classe->nombreEleves*classe->frais.frais_scolarite)))*100);

    printf(BLEU"\n-----------Frais d'inscription----------\n"RESET);
    float inscription = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        inscription += solde[i].solde_inscription;
    }
    printf("\nMontant paye: %.2f\n", ((classe->nombreEleves*classe->frais.frais_inscription) - inscription));
    printf("Reste a payer: %.2f\n", inscription);
    printf("Taux de paiement: %.2f%%\n", (1 - (inscription/(classe->nombreEleves*classe->frais.frais_inscription)))*100);

    printf(BLEU"\n---------Frais de cantine----------\n"RESET);
    float cantine = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        if(solde[i].solde_cantine>=0){
            cantine += solde[i].solde_cantine;
        }
    }
    printf("\nMontant paye: %.2f\n", ((classe->nombreEleves*classe->frais.frais_cantine) - cantine));
    printf("Reste a payer: %.2f\n", cantine);
    printf("Taux de paiement: %.2f%%\n", (1 - (cantine/(classe->nombreEleves*classe->frais.frais_cantine)))*100);

    printf(BLEU"\n---------Frais de transport----------\n"RESET);
    float transport = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        if(solde[i].solde_transport>=0){
            transport += solde[i].solde_transport;
        }
    }
    printf("\nMontant paye: %.2f\n", ((classe->nombreEleves*classe->frais.frais_transport) - transport));
    printf("Reste a payer: %.2f\n", transport);
    printf("Taux de paiement: %.2f%%\n", (1 - (transport/(classe->nombreEleves*classe->frais.frais_transport)))*100);

    printf(BLEU"\n----------Frais d'assurance----------\n"RESET);
    float assurance = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        if(solde[i].solde_assurance>=0){
            assurance += solde[i].solde_assurance;
        }
    }
    printf("\nMontant paye: %.2f\n", ((classe->nombreEleves*classe->frais.frais_assurance) - assurance));
    printf("Reste a payer: %.2f\n", assurance);
    printf("Taux de paiement: %.2f%%\n", (1 - (assurance/(classe->nombreEleves*classe->frais.frais_assurance)))*100);

    printf(BLEU"\n----------Frais d'uniforme----------\n"RESET);
    float uniforme = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        if(solde[i].solde_uniforme>=0){
            uniforme += solde[i].solde_uniforme;
        }
    }
    printf("\nMontant paye: %.2f\n", ((classe->nombreEleves*classe->frais.frais_uniforme) - uniforme));
    printf("Reste a payer: %.2f\n", uniforme);
    printf("Taux de paiement: %.2f%%\n", (1 - (uniforme/(classe->nombreEleves*classe->frais.frais_uniforme)))*100);

    printf(BLEU"\n----------Total----------\n"RESET);
    float total_reste = 0;
    for(int i = 0; i < classe->nombreEleves; i++){
        total_reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            total_reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            total_reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            total_reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            total_reste+=solde[i].solde_uniforme;
        }
        
    }
    float taux, ini;
    ini = classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
    taux = (1 - (total_reste/ini))*100;
    printf("\nMontant paye: %.2f\n", (ini - total_reste));
    printf("Reste a payer: %.2f\n", total_reste);
    printf("Taux = %.2f%%\n", taux);
    //float total_paye;
}


//Etablir les statistiques de l'etablissement sur le paiement des differents frais
void statistiques_etablissement(Classe *classe){
    int effectif = 0;
    float reste = 0;
    float ini = 0;
    float scolarite = 0, inscription = 0, cantine = 0, transport = 0, assurance = 0, uniforme = 0;
    float frais_scolarite = 0, frais_inscription = 0, frais_cantine = 0, frais_transport = 0, frais_assurance = 0, frais_uniforme = 0;
    char nomClasse[20];
    for(int i=0; i<7; i++){
        SoldeEleve *solde = (SoldeEleve*)malloc(100 * sizeof(SoldeEleve));
        switch (i){
            case 1:
                strcpy(nomClasse, "6eme");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            case 2:
                strcpy(nomClasse, "5eme");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            case 3:
                strcpy(nomClasse, "4eme");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            case 4:
                strcpy(nomClasse, "3eme");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            case 5:
                strcpy(nomClasse, "2nde");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            case 6:
                strcpy(nomClasse, "1ere");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            case 7:
                strcpy(nomClasse,"terminale");
                initialiser_classe(classe);
                charger_eleves(classe, nomClasse);
                charger_frais(classe, nomClasse);
                charger_soldes(classe, nomClasse, solde);
                frais_scolarite += classe->nombreEleves*classe->frais.frais_scolarite;
                frais_inscription += classe->nombreEleves*classe->frais.frais_inscription;
                frais_cantine += classe->nombreEleves*classe->frais.frais_cantine;
                frais_transport += classe->nombreEleves*classe->frais.frais_transport;
                frais_assurance += classe->nombreEleves*classe->frais.frais_assurance;
                frais_uniforme += classe->nombreEleves*classe->frais.frais_uniforme;
                effectif += classe->nombreEleves;
                for(int i = 0; i < classe->nombreEleves; i++){
                    reste += solde[i].solde_scolarite + solde[i].solde_inscription;
        if(solde[i].solde_cantine>=0){
            reste+=solde[i].solde_cantine;
        }
        if(solde[i].solde_transport>=0){
            reste+=solde[i].solde_transport;
        }
        if(solde[i].solde_assurance>=0){
            reste+=solde[i].solde_assurance;
        }
        if(solde[i].solde_uniforme>=0){
            reste+=solde[i].solde_uniforme;
        }
                    scolarite += solde[i].solde_scolarite;
                    inscription += solde[i].solde_inscription;
                    if(solde[i].solde_cantine>=0){
                        cantine += solde[i].solde_cantine;
                    }
                    if(solde[i].solde_transport>=0){
                        transport += solde[i].solde_transport;
                    }
                    if(solde[i].solde_assurance>=0){
                        assurance += solde[i].solde_assurance;
                    }
                    if(solde[i].solde_uniforme>=0){
                        uniforme += solde[i].solde_uniforme;
                    }
                    
                }
                ini += classe->nombreEleves*(classe->frais.frais_scolarite + classe->frais.frais_inscription + classe->frais.frais_cantine + classe->frais.frais_transport + classe->frais.frais_assurance + classe->frais.frais_uniforme);
                free(solde);
                break;
            default:
                break;
        }
    }
      
    printf(VERT"Stattistiques de l'etablissement\n"RESET);
    printf("\nEffectif: %d eleves\n",effectif);
    printf(BLEU"\n----------Frais de scolarite----------\n"RESET);
    printf("\nMontant paye: %.2f\n", ((frais_scolarite) - scolarite));
    printf("Reste a payer: %.2f\n", scolarite);
    printf("Taux de paiement: %.2f%%\n", (1 - (scolarite/(frais_scolarite)))*100);

    printf(BLEU"\n-----------Frais d'inscription----------\n"RESET);
    printf("\nMontant paye: %.2f\n", (frais_inscription - inscription));
    printf("Reste a payer: %.2f\n", inscription);
    printf("Taux de paiement: %.2f%%\n", (1 - (inscription/frais_inscription))*100);

    printf(BLEU"\n---------Frais de cantine----------\n"RESET);
    printf("\nMontant paye: %.2f\n", (frais_cantine - cantine));
    printf("Reste a payer: %.2f\n", cantine);
    printf("Taux de paiement: %.2f%%\n", (1 - (cantine/frais_cantine))*100);

    printf(BLEU"\n---------Frais de transport----------\n"RESET);
    printf("\nMontant paye: %.2f\n", (frais_transport - transport));
    printf("Reste a payer: %.2f\n", transport);
    printf("Taux de paiement: %.2f%%\n", (1 - (transport/(frais_transport)))*100);

    printf(BLEU"\n----------Frais d'assurance----------\n"RESET);
    printf("\nMontant paye: %.2f\n", (frais_assurance - assurance));
    printf("Reste a payer: %.2f\n", assurance);
    printf("Taux de paiement: %.2f%%\n", (1 - (assurance/frais_assurance))*100);

    printf(BLEU"\n----------Frais d'uniforme----------\n"RESET);
    printf("\nMontant paye: %.2f\n", (frais_uniforme - uniforme));
    printf("Reste a payer: %.2f\n", uniforme);
    printf("Taux de paiement: %.2f%%\n", (1 - (uniforme/frais_uniforme))*100);

    printf(BLEU"\n----------Total----------\n"RESET);
    printf("\n\nMontant paye: %.2f\n", (ini - reste));
    printf("Reste: %.2f\n",reste);
    float taux = (1-(reste/ini))*100;
    printf("Taux de paiement: %.2f%%\n", taux);
}



//Identifier et afficher les eleves ayant finis de payer un frais
void fini_de_solder(Classe *classe, const char *nomClasse, SoldeEleve *solde){
        printf("Choisir le frais\n");
        printf("\n1- Frais de scolarite\n");
        printf("\n2- Frais d'inscription\n");
        printf("\n3- Frais de cantine\n");
        printf("\n4- Frais de transport\n");
        printf("\n5- Frais d'assurance\n");
        printf("\n6- Frais d'uniforme\n");
        int t;
        essaie:
        t = saisirEntier();
        system("clear");
        if(t==1){
            printf(BLEU"Liste des eleves de la classe de %s ayant fini de solder les frais de scolarite\n"RESET,nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_scolarite == 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                }
            }
        }
        if(t==2){
            printf(BLEU"Liste des eleves de la classe de %s ayant fini de solder les frais d'inscription\n"RESET,nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_inscription == 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                }
            }
        }

        if(t==3){
            printf(BLEU"Liste des eleves de la classe de %s ayant fini de solder les frais de cantine\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_cantine == 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                }
            }
        }

        if(t==4){
            printf(BLEU"Liste des eleves de la classe de %s ayant fini de solder les frais de transport\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_transport == 0){
                    printf("Matricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                }
            }
        }

        if(t==5){
            printf(BLEU"Liste des eleves de la classe de %s ayant fini de solder les frais d'assurance\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_assurance == 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                }
            }
        }

        if(t==6){
            printf(BLEU"Liste des eleves de la classe de %s ayant fini de solder les frais d'uniforme\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_uniforme == 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                }
            }
        }

        if(t!=1&&t!=2&&t!=3&&t!=4&&t!=5&&t!=6){
            printf(ROUGE"Choix incorrecte, reessayer: "RESET);
            goto essaie;
        }
}

//Identifier et afficher les eleves ayant finis de payer un frais ainsi que le reste a payer
void pas_fini_de_solder(Classe *classe, const char *nomClasse, SoldeEleve *solde){
        printf("Choisir le frais\n");
        printf("\n1- Frais de scolarite\n");
        printf("\n2- Frais d'inscription\n");
        printf("\n3- Frais de cantine\n");
        printf("\n4- Frais de transport\n");
        printf("\n5- Frais d'assurance\n");
        printf("\n6- Frais d'uniforme\n");
        int t;
        essaie:
        t = saisirEntier();
        system("clear");
        if(t==1){
            printf(BLEU"Liste des eleves de la classe de %s n'ayant pas fini de solder les frais de scolarite\n"RESET,nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_scolarite != 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                    printf(ROUGE"Reste: %.2f\n"RESET, solde[i].solde_scolarite);
                }
            }
        }
        if(t==2){
            printf(BLEU"Liste des eleves de la classe de %s n'ayant pas fini de solder les frais d'inscription\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_inscription != 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                    printf(ROUGE"Reste: %.2f\n"RESET, solde[i].solde_inscription);
                }
            }
        }

        if(t==3){
            printf(BLEU"Liste des eleves de la classe de %s n'ayant pas fini de solder les frais de cantine\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_cantine != 0){
                    printf("Matricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                    printf(ROUGE"Reste: %.2f\n"RESET, solde[i].solde_cantine);
                }
            }
        }

        if(t==4){
            printf(BLEU"Liste des eleves de la classe de %s n'ayant pas fini de solder les frais de transport\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_transport != 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                    printf(ROUGE"Reste: %.2f\n"RESET, solde[i].solde_transport);
                }
            }
        }

        if(t==5){
            printf(BLEU"Liste des eleves de la classe de %s n'ayant pas fini de solder les frais d'assurance\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_assurance != 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                    printf(ROUGE"Reste: %.2f\n"RESET, solde[i].solde_assurance);
                }
            }
        }

        if(t==6){
            printf(BLEU"Liste des eleves de la classe de %s n'ayant pas fini de solder les frais d'uniforme\n"RESET, nomClasse);
            for(int i=0; i<classe->nombreEleves;i++){
                if(solde[i].solde_uniforme != 0){
                    printf("\nMatricule: %s\n", classe->eleves[i].matricule);
                    printf("Nom: %s\n", classe->eleves[i].nom);
                    printf("Prénom: %s\n", classe->eleves[i].prenom);
                    printf(ROUGE"Reste: %.2f\n"RESET, solde[i].solde_uniforme);
                }
            }
        }

        if(t!=1&&t!=2&&t!=3&&t!=4&&t!=5&&t!=6){
            printf(ROUGE"Choix incorrecte, reessayer: "RESET);
            goto essaie;
        }
}
