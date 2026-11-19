#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RIGHE 10
#define MAX_COL 55
#define DIM_STRINGA 56

/* Scarta i caratteri rimasti nel buffer fino a '\n' (o EOF).
   Restituisce 1 se ha scartato almeno un carattere diverso da '\n'. */
static int scarta_resto(void)
{
    int c, scartati = 0;
    while ((c = getchar()) != '\n' && c != EOF)
        scartati = 1;
    return scartati;
}

/* Legge una riga in buf (dimensione n). Rimuove '\n'.
   Restituisce -1 se EOF, 1 se la riga era troppo lunga (troncata), 0 altrimenti. */
static int leggi_riga(char *buf, int n)
{
    char *nl;
    if (fgets(buf, n, stdin) == NULL)
        return -1;
    nl = strchr(buf, '\n');
    if (nl != NULL) {
        *nl = '\0';
        return 0;
    }
    return scarta_resto();
}

/* Legge un intero da una riga. Restituisce 1 se valido, 0 se non valido, -1 se EOF. */
static int leggi_intero(int *valore)
{
    char buf[32];
    char *fine;
    long v;
    int r = leggi_riga(buf, sizeof(buf));

    if (r < 0)
        return -1;
    if (r > 0 || buf[0] == '\0')
        return 0;
    v = strtol(buf, &fine, 10);
    if (fine == buf)
        return 0;
    while (*fine == ' ' || *fine == '\t')
        fine++;
    if (*fine != '\0')
        return 0;
    if (v < -1000000L || v > 1000000L)
        return 0;
    *valore = (int)v;
    return 1;
}

/* Tiene solo le lettere a-z, A-Z, in minuscolo. */
static void ripulisci(char *s)
{
    size_t i, j = 0;
    for (i = 0; s[i] != '\0'; i++) {
        unsigned char c = (unsigned char)s[i];
        if (isalpha(c) && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
            s[j++] = (char)tolower(c);
    }
    s[j] = '\0';
}

/* Chiede il messaggio finche' non contiene almeno una lettera.
   Restituisce 0 se ok, -1 se EOF. */
static int chiedi_messaggio(char *stringa, int dim)
{
    for (;;) {
        int r;
        printf("Messaggio: ");
        r = leggi_riga(stringa, dim);
        if (r < 0)
            return -1;
        if (r > 0)
            printf("Attenzione: il messaggio e' stato troncato a %d caratteri.\n", dim - 1);
        ripulisci(stringa);
        printf("Testo ripulito: %s\n", stringa);
        if (stringa[0] != '\0')
            return 0;
        printf("Il messaggio non contiene lettere, riprova.\n");
    }
}

/* Chiede il numero di righe (2-10). Restituisce 0 se ok, -1 se EOF. */
static int chiedi_righe(int *righe)
{
    for (;;) {
        int r;
        printf("Numero di righe (2-%d): ", MAX_RIGHE);
        r = leggi_intero(righe);
        if (r < 0)
            return -1;
        if (r == 1 && *righe >= 2 && *righe <= MAX_RIGHE)
            return 0;
        printf("Valore non valido, riprova.\n");
    }
}

static void inizializza(char m[MAX_RIGHE][MAX_COL])
{
    int i, j;
    for (i = 0; i < MAX_RIGHE; i++)
        for (j = 0; j < MAX_COL; j++)
            m[i][j] = '.';
}

/* Scrive in m il carattere f(i) nelle posizioni dello zigzag.
   Se testo != NULL scrive le lettere, altrimenti '*'. */
static void disegna_zigzag(char m[MAX_RIGHE][MAX_COL], int righe, int lung, const char *testo)
{
    int riga = 0, dir = 1, col;
    for (col = 0; col < lung; col++) {
        m[riga][col] = (testo != NULL) ? testo[col] : '*';
        if (riga == 0)
            dir = 1;
        else if (riga == righe - 1)
            dir = -1;
        riga += dir;
    }
}

static void stampa_matrice(char m[MAX_RIGHE][MAX_COL], int righe, int lung)
{
    int i, j;
    for (i = 0; i < righe; i++) {
        for (j = 0; j < lung; j++) {
            if (j > 0)
                putchar(' ');
            putchar(m[i][j]);
        }
        putchar('\n');
    }
}

static void cifra(const char *testo, int righe)
{
    char m[MAX_RIGHE][MAX_COL];
    char cifrato[DIM_STRINGA];
    int lung = (int)strlen(testo);
    int i, j, k = 0;

    inizializza(m);
    disegna_zigzag(m, righe, lung, testo);
    stampa_matrice(m, righe, lung);

    for (i = 0; i < righe; i++)
        for (j = 0; j < lung; j++)
            if (m[i][j] != '.')
                cifrato[k++] = m[i][j];
    cifrato[k] = '\0';
    printf("Testo cifrato: %s\n", cifrato);
}

static void decifra(const char *cifrato, int righe)
{
    char m[MAX_RIGHE][MAX_COL];
    char chiaro[DIM_STRINGA];
    int lung = (int)strlen(cifrato);
    int i, j, k = 0, riga = 0, dir = 1;

    inizializza(m);
    disegna_zigzag(m, righe, lung, NULL);

    /* riempie le posizioni segnate riga per riga */
    for (i = 0; i < righe; i++)
        for (j = 0; j < lung; j++)
            if (m[i][j] == '*')
                m[i][j] = cifrato[k++];

    /* legge seguendo lo zigzag */
    for (j = 0; j < lung; j++) {
        chiaro[j] = m[riga][j];
        if (riga == 0)
            dir = 1;
        else if (riga == righe - 1)
            dir = -1;
        riga += dir;
    }
    chiaro[lung] = '\0';
    printf("Testo in chiaro: %s\n", chiaro);
}

int main(void)
{
    int scelta;

    for (;;) {
        int r;
        printf("1) Cifra\n2) Decifra\n0) Esci\nScelta: ");
        r = leggi_intero(&scelta);
        if (r < 0)
            break;
        if (r == 0 || scelta < 0 || scelta > 2) {
            printf("Scelta non valida, riprova.\n");
            continue;
        }
        if (scelta == 0) {
            printf("Arrivederci!\n");
            break;
        }

        {
            char stringa[DIM_STRINGA];
            int righe;

            if (chiedi_messaggio(stringa, sizeof(stringa)) < 0)
                break;
            if (chiedi_righe(&righe) < 0)
                break;
            if (scelta == 1)
                cifra(stringa, righe);
            else
                decifra(stringa, righe);
        }
    }
    return 0;
}