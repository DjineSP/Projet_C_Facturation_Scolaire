#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>


int main() {
    system("clear");
    iden:
     struct Administrateur admins[MAX_ADMINISTRATEURS];
    int nbAdmins = 0;

    lireIdentifiants(admins, &nbAdmins);

    if (nbAdmins == 0) {
        system("clear");
        printf("\n\n\n");
        afficherTexteAnime(BLEU"Bienvenue !"RESET);
        printf("\n\n\n");
        afficherTexteAnime("Vous êtes la première personne à utiliser ce programme."   );
        printf("\n\n\n");
        afficherTexteAnime("Le programme permet de gerer un systeme de facturation scolaire. ");
        printf("\n\n");
        afficherTexteAnime("Veillez entrer vos identifiants pour continuer.");
        printf("\n\n");
        ajouterNouvelAdministrateur(admins, &nbAdmins);
        goto iden;
    }
    else {
        system("clear");
        struct Administrateur saisieAdmin;

        afficherTexteAnime(VERT"GESTION DES SYSTEMES DE FACTURATION SCOLAIRE"RESET);
        ressayer:
        printf("\n\n");
        afficherTexteAnime("Veillez entrer vos identifiants pour vous connecter a votre compte.");
        printf("\n\n");
        saisirUtilisateur(&saisieAdmin);

        if (authentifier(admins, nbAdmins, &saisieAdmin)) {
            system("clear");
            afficherTexteAnime(VERT"Authentification réussie."RESET);
            printf("\n\n");
            afficherTexteAnime("Bienvenue M/Mme: ");
            afficherTexteAnime(saisieAdmin.nom_utilisateur);
            usleep(1000000);
    menu:
    int choix;
    int p,q, r,s;
    char nomClasse[20];
    char matricule[20];

    do {
        system("clear");
        printf(FOND_BLEU "\n       Menu principal          \n" RESET);
        printf(JAUNE"\n1- Gestion des eleves\n"RESET);
        printf(VERT"\n2- Effectuer un paiement\n"RESET);
        printf(MAGENTA"\n3- Suivis des paiements\n"RESET);
        printf(CYAN"\n4- Voir les statistiques d'une classe\n"RESET);
        printf(BLANC"\n5- Voir les statistiques de l'etablissement\n"RESET);
        printf(BLEU"\n6- Ajouter un administrateurs\n"RESET);
        printf(ROUGE "\n7- Quitter\n\n" RESET);
        choix = saisirEntier();
        switch (choix) {
            case 1:
                system("clear");
                changer1:
                printf(FOND_BLEU"\n            GESTION DES ELEVES            \n"RESET);
                printf(VERT"\nVoici la liste des differentes classes de l'etablissement\n"RESET);
                printf("\n-->6eme\n-->5eme\n-->4eme\n-->3eme\n-->2nde\n-->1ere\n-->terminale\n");
                printf("\nEntrez le nom de la classe que vous souhaitez gerer\nNom de la classe: ");
                scanf("%s", nomClasse);
               
                while(strcmp(nomClasse, "6eme") != 0 && strcmp(nomClasse, "5eme") != 0 &&
                            strcmp(nomClasse, "4eme") != 0 && strcmp(nomClasse, "3eme") != 0 &&
                            strcmp(nomClasse, "2nde") != 0 && strcmp(nomClasse, "1ere") != 0 &&
                            strcmp(nomClasse, "terminale") != 0) 
                {
                    afficherTexteAnime(ROUGE"\nCette classe n'existe pas, veillez reessayer: "RESET);
                    scanf("%s", nomClasse);
                }
                                
                            
                FILE *fichier;
                char nomFichier[50];
                sprintf(nomFichier, "eleves_%s.txt", nomClasse);
                fichier = fopen(nomFichier, "a");
                fclose(fichier); 
                eleve:
                system("clear");
                do{
                    Classe maClasse;
                    SoldeEleve *solde;
                    initialiser_classe(&maClasse);
                    int reponse;
                    // Charger les élèves existants
                    charger_eleves(&maClasse, nomClasse);
                    printf(FOND_JAUNE"\n            GESTION DES ELEVES            \n"RESET);
                    printf(FOND_BLEU"    Menu   \n"RESET);
                    printf("\n1- Ajouter un eleve\n");
                    printf("\n2- Modifier un eleve\n");
                    printf("\n3- Supprimer un eleve\n");
                    printf("\n4- Afficher un eleve\n");
                    printf("\n5- Affcher la classe\n");
                    printf("\n6- Changer de classe\n");
                    printf("\n7- Retour au menu principal\n");
                    printf(ROUGE"\n8- Quitter\n\n"RESET);
                    p = saisirEntier();
                    switch (p){
                        case 1:

                            system("clear");
                            if (maClasse.nombreEleves == 0) {
                                definir_frais(&maClasse, nomClasse);
                            }
                            // Ajouter un nouvel élève
                            ajouter_eleve(&maClasse, nomClasse);
                            solde = (SoldeEleve*)malloc(999 * sizeof(SoldeEleve));
                            printf("\nY a t-il des frais facultatifs en particulier que l'eleve ne souhaite pas payer?\n");
                            printf("\n1- Oui\n");
                            printf("\nAutre entier pour non\n");
                            int w;
                            w = saisirEntier();
                            if(w==1){
                                definir_soldes(&maClasse, nomClasse, solde);
                            }
                            else{
                                initialiser_soldes(&maClasse, nomClasse, solde);
                            }
                            break;
                        case 2:
                            system("clear");
                            if (maClasse.nombreEleves == 0) {
                                afficherTexteAnime(ROUGE"Aucun élève dans la classe.\n"RESET);
                                usleep(1000000);
                                break;
                            }
                            // Demander à l'utilisateur le matricule de l'élève à modifier
                            printf("\n\nEntrez le matricule de l'élève à modifier: ");
                            scanf("%s", matricule);
                            modifier_eleve(&maClasse, nomClasse, matricule);
                            break;
                        case 3:
                            system("clear");
                            if (maClasse.nombreEleves == 0) {
                                afficherTexteAnime(ROUGE"Aucun élève dans la classe.\n"RESET);
                                usleep(1000000);
                                break;
                            }
                            // Demander à l'utilisateur le matricule de l'élève à supprimer
                            printf("Entrez le matricule de l'élève à supprimer: ");
                            scanf("%s", matricule);
                            solde = (SoldeEleve*)malloc(999 * sizeof(SoldeEleve));
                            supprimer_eleve(&maClasse, nomClasse, matricule, solde);
                            break;
                        case 4:
                            system("clear");
                            if (maClasse.nombreEleves == 0) {
                                afficherTexteAnime(ROUGE"Aucun élève dans la classe.\n"RESET);
                                usleep(1000000);
                                break;
                            }
                            // Demander à l'utilisateur le matricule de l'élève à afficher
                            printf("Entrez le matricule de l'élève à afficher: ");
                            scanf("%s", matricule);
                            afficher_eleve(&maClasse, matricule);
                            liberer_memoire_eleves(&maClasse);
                            printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Retour\n");
                            reponse = saisirEntier();
                            if(reponse==0){
                                goto eleve;
                            }
                            else{
                                goto menu;
                            }
                            break;
                        case 5:
                            system("clear");
                            if (maClasse.nombreEleves == 0) {
                                afficherTexteAnime(ROUGE"Aucun élève dans la classe.\n"RESET);
                                usleep(1000000);
                                break;
                            }
                            afficher_classe(&maClasse, nomClasse);
                            printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Retour\n");
                            reponse = saisirEntier();
                            if(reponse==0){
                                goto eleve;
                            }
                            else{
                                goto menu;
                            }
                            break;
                        case 6:
                            system("clear");
                            goto changer1;
                            break;
                        case 7:
                            system("clear");
                            goto menu;
                            break;
                        case 8:
                            system("clear");
                            return 0;
                            break;
                        default:
                            system("clear");
                            afficherTexteAnime(ROUGE"Veuillez entrer un chiffre valide.\n"RESET);
                            usleep(1000000);
                            // Nettoyer le tampon d'entrée
                            while (getchar() != '\n');
                            break;
                    }
                } while (p != 8);
                break;
               
            case 2:
                changer2:
                system("clear");
                printf(FOND_BLEU"\n            EFFECTUER UN PAIEMENT            \n"RESET);
                printf(VERT"\nVoici la liste des differentes classes de l'etablissement\n"RESET);
                printf("\n-->6eme\n-->5eme\n-->4eme\n-->3eme\n-->2nde\n-->1ere\n-->terminale\n");
                printf("\nEntrez le nom de la classe que vous souhaitez gerer\nNom de la classe: ");
                scanf("%s", nomClasse);
               
                while(strcmp(nomClasse, "6eme") != 0 && strcmp(nomClasse, "5eme") != 0 &&
                            strcmp(nomClasse, "4eme") != 0 && strcmp(nomClasse, "3eme") != 0 &&
                            strcmp(nomClasse, "2nde") != 0 && strcmp(nomClasse, "1ere") != 0 &&
                            strcmp(nomClasse, "terminale") != 0) 
                {
                    afficherTexteAnime(ROUGE"\nCette classe n'existe pas, veillez reessayer: "RESET);
                    scanf("%s", nomClasse);
                }
                Classe maClasse;
                
                initialiser_classe(&maClasse);
                // Charger les élèves existants
                charger_eleves(&maClasse, nomClasse);
                if (maClasse.nombreEleves == 0) {
                    system("clear");
                    afficherTexteAnime(ROUGE"Aucun élève dans la classe.\n"RESET);
                    printf("\n1- Changer de classe\n");
                    printf("Autre entier pour retourner au menu principal\n");
                    int e;
                    e = saisirEntier();
                    if(e==1){
                        goto changer2;
                    }
                    else{
                        goto menu;
                    }
                    
                }
                SoldeEleve *solde = (SoldeEleve*)malloc(100 * sizeof(SoldeEleve));
                system("clear");
                float montant_du[6];
                float montant_paye[6] = {0,0,0,0,0,0};
                int index = effectuer_paiement(&maClasse, nomClasse, solde, montant_du, montant_paye, saisieAdmin.nom_utilisateur);
                if(index!=-1){
                    system("clear");
                    printf("\nUne facture a ete genere\n");
                    printf("\nVoulez vous l'afficher? (O/n)");
                    char ch;
                    int o=0;
                    do{
                        scanf("%c",&ch);
                        if(ch == 'O' || ch == 'o'){
                            o=1;
                            afficher_facture(&maClasse, nomClasse, solde, montant_du, montant_paye, index, saisieAdmin.nom_utilisateur);
                            printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Quitter\n");
                            int reponse = saisirEntier();
                            if(reponse==0){
                                return 0;
                            }
                            else{
                                goto menu;
                            }
                            
                        }
                        if(ch == 'N' || ch == 'n'){
                            o=1;
                            goto menu;
                            break;
                        }
                        
                    }while(ch!='o' || ch != 'O' || ch !='N' || ch!='n');
                }
                break;
            case 3:
                changer3:
                system("clear");
                printf(FOND_BLEU"\n            SUIVI DES PAIEMENTS            \n"RESET);
                printf(VERT"\nVoici la liste des differentes classes de l'etablissement\n"RESET);
                printf("\n-->6eme\n-->5eme\n-->4eme\n-->3eme\n-->2nde\n-->1ere\n-->terminale\n");
                printf("\nEntrez le nom de la classe que vous souhaitez gerer\nNom de la classe: ");
                scanf("%s", nomClasse);
               
                while(strcmp(nomClasse, "6eme") != 0 && strcmp(nomClasse, "5eme") != 0 &&
                            strcmp(nomClasse, "4eme") != 0 && strcmp(nomClasse, "3eme") != 0 &&
                            strcmp(nomClasse, "2nde") != 0 && strcmp(nomClasse, "1ere") != 0 &&
                            strcmp(nomClasse, "terminale") != 0) 
                {
                    afficherTexteAnime(ROUGE"\nCette classe n'existe pas, veillez reessayer: "RESET);
                    scanf("%s", nomClasse);
                }
                //lasse maClasse;
                
                initialiser_classe(&maClasse);
                // Charger les élèves existants
                charger_eleves(&maClasse, nomClasse);
                if (maClasse.nombreEleves == 0) {
                    system("clear");
                    printf(ROUGE"Aucun élève dans la classe de %s.\n"RESET,nomClasse);
                    printf("1- Changer de classe\n");
                    printf("Autre entier pour retourner au menu principal\n");
                    int e;
                    e = saisirEntier();
                    if(e==1){
                        goto changer3;
                    }
                    else{
                        goto menu;
                    }
                    
                }
                solde = (SoldeEleve*)malloc(100 * sizeof(SoldeEleve));
                charger_soldes(&maClasse, nomClasse, solde);
                do{
                    paiement:
                    int reponse;
                system("clear");
                printf(FOND_BLEU"\n            SUIVI DES PAIEMENTS            \n"RESET);
                printf("\n1- Afficher les soldes d'un eleve\n");
                printf("\n2- Afficher les eleves n'ayant pas fini de solder un frais\n");
                printf("\n3- Afficher les eleves ayant fini de solder un frais\n");
                printf("\n4- Retour au menu principal\n");
                printf(ROUGE"\n5- Sortir\n"RESET);
                s = saisirEntier();
                switch (s){
                    case 1:
                        system("clear");
                        afficher_soldes(&maClasse, nomClasse, solde);
                        printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Retour\n");
                        reponse = saisirEntier();
                        if(reponse==0){
                            goto paiement;
                        }
                        else{
                            goto menu;
                        }
                        break;
                    case 2:
                        pas_fini_de_solder(&maClasse,nomClasse, solde);
                        printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Retour\n");
                        reponse = saisirEntier();
                        if(reponse==0){
                            goto paiement;
                        }
                        else{
                            goto menu;
                        }
                        break;
                    case 3:
                        fini_de_solder(&maClasse,nomClasse, solde);
                        printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Retour\n");
                        reponse = saisirEntier();
                        if(reponse==0){
                            goto paiement;
                        }
                        else{
                            goto menu;
                        }
                    case 4:
                        goto menu;
                        break;
                    case 6:
                        return 0;
                        break;
                    default:
                        system("clear");
                        printf(ROUGE"Veuillez entrer un chiffre valide.\n"RESET);
                        usleep(1000000);
                        // Nettoyer le tampon d'entrée
                        while (getchar() != '\n');
                        break;
                }
                }while(s!=6);
                break;
            case 4:
                changer4:
                system("clear");
                printf(FOND_BLEU"\n            VOIR LES STATISTIQUES D'UNE CLASSE            \n"RESET);
                printf(VERT"\nVoici la liste des differentes classes de l'etablissement\n"RESET);
                printf("\n-->6eme\n-->5eme\n-->4eme\n-->3eme\n-->2nde\n-->1ere\n-->terminale\n");
                printf("\nEntrez le nom de la classe que vous souhaitez gerer\nNom de la classe: ");
                scanf("%s", nomClasse);
               
                while(strcmp(nomClasse, "6eme") != 0 && strcmp(nomClasse, "5eme") != 0 &&
                            strcmp(nomClasse, "4eme") != 0 && strcmp(nomClasse, "3eme") != 0 &&
                            strcmp(nomClasse, "2nde") != 0 && strcmp(nomClasse, "1ere") != 0 &&
                            strcmp(nomClasse, "terminale") != 0) 
                {
                    afficherTexteAnime(ROUGE"\nCette classe n'existe pas, veillez reessayer: "RESET);
                    scanf("%s", nomClasse);
                }
                //Classe maClasse;
                
                initialiser_classe(&maClasse);
                // Charger les élèves existants
                charger_eleves(&maClasse, nomClasse);
                if (maClasse.nombreEleves == 0) {
                    system("clear");
                    printf("Aucun élève dans la classe de %s.\n",nomClasse);
                    printf("1- Changer de classe\n");
                    printf("Autre entier pour retourner au menu principal\n");
                    int e;
                    e = saisirEntier();
                    if(e==1){
                        goto changer4;
                    }
                    else{
                        goto menu;
                    }
                    
                }
                solde = (SoldeEleve*)malloc(100 * sizeof(SoldeEleve));
                system("clear");
                statistiques_classe(&maClasse,nomClasse,solde);
                printf("\n\nEntrer un entier different de 0 pour retourner au menu principal");
                printf(ROUGE"\n0- Quitter\n"RESET);
                int reponse = saisirEntier();
                if(reponse==0){
                    return 0;
                }
                else{
                    goto menu;
                }
                break;
            case 5:
                system("clear");
                statistiques_etablissement(&maClasse);
                printf("\n\nEntrer un entier different de 0 pour retourner au menu principal\n0- Quitter\n");
                reponse = saisirEntier();
                if(reponse==0){
                    return 0;
                }
                else{
                    goto menu;
                }
                break;
            case 6:
                system("clear");
                ajouterNouvelAdministrateur(admins, &nbAdmins);
                printf("Nouvel Administrateur ajoute avec succes.\n");
                usleep(1000000);
                break;
            case 7:
                return 0;
                break;
            default:
                system("clear");
                afficherTexteAnime(ROUGE"Veuillez entrer un chiffre valide."RESET);
                usleep(1000000);
                // Nettoyer le tampon d'entrée
                while (getchar() != '\n');
                break;
        }

     } while (choix != 7);
    
        } else {
            system("clear");
            printf("\n\n\n");
            afficherTexteAnime(ROUGE"Échec de l'authentification.\n"RESET);
            afficherTexteAnime("\nVeuillez vérifier vos identifiants.");
            printf("\n");
            usleep(1000000);
            goto ressayer;
        }
    }

    
    return 0;
}
