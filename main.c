#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT 1024
#define MAX_NAME 50

void loadText(const char *filename, const char *key, char *output) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur : Impossible de charger le fichier %s\n", filename);
        exit(1);
    }

    char line[MAX_TEXT];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, key, strlen(key)) == 0) {
            strcpy(output, line + strlen(key) + 1); // Skip key and delimiter
            output[strcspn(output, "\n")] = 0;   // Remove newline
            fclose(file);
            return;
        }
    }

    printf("Erreur : Texte pour '%s' introuvable dans %s\n", key, filename);
    fclose(file);
    exit(1);
}

void personalizeText(char *text, const char *name) {
    char buffer[MAX_TEXT];
    char *placeholder = strstr(text, "{nom}");
    if (placeholder) {
        size_t prefixLen = placeholder - text;
        snprintf(buffer, sizeof(buffer), "%.*s%s%s", (int)prefixLen, text, name, placeholder + 5); // Skip "{nom}"
        strcpy(text, buffer);
    }
}

void choixAventure(const char *langFile, const char *name) {
    char text[MAX_TEXT];
    char choix;

    // Message de bienvenue personnalisé
    loadText(langFile, "BIENVENUE", text);
    personalizeText(text, name);
    printf("%s\n", text);

    // Introduction
    loadText(langFile, "INTRO", text);
    printf("%s\n", text);

    // Premier choix
    loadText(langFile, "CHOIX1", text);
    printf("%s\n", text);
    printf("a) ");
    loadText(langFile, "CHOIX1A", text);
    printf("%s\n", text);
    printf("b) ");
    loadText(langFile, "CHOIX1B", text);
    printf("%s\n", text);
    printf("C) ");
    loadText(langFile, "CHOIX1C", text);
    printf("%s\n", text);

    printf("\nVotre choix : ");
    scanf(" %c", &choix);

    if (choix == 'a') {
        loadText(langFile, "RESULTAT1A", text);
        printf("%s\n", text);
    } 
    else if (choix == 'b') {
        loadText(langFile, "RESULTAT1B", text);
        printf("%s\n", text);
    } 
    else if (choix == 'c') {
        loadText(langFile, "RESULTAT1C", text);
        printf("%s\n", text);
    } 
    else {
        printf("Choix invalide. Fin de l'aventure.\n");
    }
}

int main() {
    char lang[10];
    char langFile[50];
    char name[MAX_NAME];

    printf("Choisissez une langue (fr/en) : ");
    scanf("%s", lang);

    if (strcmp(lang, "fr") == 0) {
        strcpy(langFile, "textes_fr.txt");
    } else if (strcmp(lang, "en") == 0) {
        strcpy(langFile, "textes_en.txt");
    } else {
        printf("Langue non supportée.\n");
        return 1;
    }

    // Saisie du nom du joueur
    char text[MAX_TEXT];
    loadText(langFile, "SAISIE_NOM", text);
    printf("%s\n", text);
    getchar(); // Clear the newline left by the previous input
    fgets(name, MAX_NAME, stdin); // Read the name, including spaces
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    choixAventure(langFile, name);

    return 0;
}
