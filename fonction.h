#include <stdbool.h>
#ifndef FUNCTION_H
#define FUNCTION_H
#define MAX_ELEVES 500
#define MAX_ADMINISTRATEURS 5 

// Codes de couleur ANSI
#define RESET           "\033[0m"
#define NOIR            "\033[0;30m"
#define ROUGE           "\033[0;31m"
#define VERT            "\033[0;32m"
#define JAUNE           "\033[0;33m"
#define BLEU            "\033[0;34m"
#define MAGENTA         "\033[0;35m"
#define CYAN            "\033[0;36m"
#define BLANC           "\033[0;37m"

#define GRAS_NOIR       "\033[1;30m"
#define GRAS_ROUGE      "\033[1;31m"
#define GRAS_VERT       "\033[1;32m"
#define GRAS_JAUNE      "\033[1;33m"
#define GRAS_BLEU       "\033[1;34m"
#define GRAS_MAGENTA    "\033[1;35m"
#define GRAS_CYAN       "\033[1;36m"
#define GRAS_BLANC      "\033[1;37m"

#define FOND_NOIR       "\033[40m"
#define FOND_ROUGE      "\033[41m"
#define FOND_VERT       "\033[42m"
#define FOND_JAUNE      "\033[43m"
#define FOND_BLEU       "\033[44m"
#define FOND_MAGENTA    "\033[45m"
#define FOND_CYAN       "\033[46m"
#define FOND_BLANC      "\033[47m"


struct Administrateur {
    char nom_utilisateur[100];
    char mot_de_passe[100];
};

// Structure pour représenter un élève
typedef struct {
    char matricule[20];
    char nom[50];
    char prenom[50];
    char sexe[2];
    char nom_parent[50];
    char contact_parent[20];
} Eleve;

typedef struct {
    float frais_scolarite;
    float frais_inscription;
    float frais_cantine;
    float frais_transport;
    float frais_assurance;
    float frais_uniforme;
} Frais;

// Structure pour représenter une classe
typedef struct {
    Eleve *eleves;
    Frais frais;
    int nombreEleves;
} Classe;

typedef struct {
    char matricule[20];
    float solde_scolarite;
    float solde_inscription;
    float solde_cantine;
    float solde_transport;
    float solde_assurance;
    float solde_uniforme;
} SoldeEleve;
/*
struct Payment {
    char name[50];
    float amount;
}*/

struct Eleve {
    const char Matricule[7];
    char nom[50];
    float montantTotal;
    float montantPaye;
};

bool verifier_mot_de_passe(const char *mot_de_passe);
bool valide(const char *chaine);
void afficherTexteAnime(const char* texte);
int saisirEntier();
void sauvegarderIdentifiants(struct Administrateur *admins, int nbAdmins);
void lireIdentifiants(struct Administrateur *admins, int *nbAdmins);
void saisirUtilisateur(struct Administrateur *admin);
int authentifier(struct Administrateur *admins, int nbAdmins, struct Administrateur *saisieAdmin);
void ajouterNouvelAdministrateur(struct Administrateur *admins, int *nbAdmins);
int trouver_eleve_par_matricule(Classe *classe, const char *matricule);
void generer_matricule(Classe *classe, const char *nomClasse, Eleve eleve);
void initialiser_classe(Classe *classe);
void charger_eleves(Classe *classe, const char *nomClasse);
void ajouter_eleve(Classe *classe, const char *nomClasse);
void modifier_eleve(Classe *classe, const char *nomClasse, const char *matricule);
void supprimer_eleve(Classe *classe,const char *nomClasse, const char *matricule, SoldeEleve *solde);
void afficher_eleve(Classe *classe,  const char *matricule);
void afficher_classe(Classe *classe, const char *nomClasse);
void definir_frais(Classe *classe, const char *nomClasse);
void initialiser_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void charger_frais(Classe *classe, const char *nomClasse);
int effectuer_paiement(Classe *classe, const char *nomClasse, SoldeEleve *solde,float *montant_du,float *montant_paye, const char *nomAdmin);
void charger_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void afficher_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void liberer_memoire_eleves(Classe *classe);
void enregistrer_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void generer_facture(Classe *classe, const char *nomClasse, SoldeEleve *solde,float *montant_du,float *montant_paye, int indice, const char *nomAdmin);
void afficher_facture(Classe *classe, const char *nomClasse, SoldeEleve *solde, float *montant_du, float *montant_paye, int indice, const char *nomAdmin);
void statistiques_classe(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void afficher_statistiques_categorie(const char *categorie, float total_paye, float restant, float taux_paiement);
void afficher_statistiques_frais(const char *nom_frais, float total_frais, float total_paye);
void statistiques_etablissement(Classe *classe);
void fini_de_solder(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void pas_fini_de_solder(Classe *classe, const char *nomClasse, SoldeEleve *solde);
void definir_soldes(Classe *classe, const char *nomClasse, SoldeEleve *solde);


#endif
