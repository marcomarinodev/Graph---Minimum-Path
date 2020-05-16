#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_adj;
    int* adj;
} vertex;

// STACK VS QUEUE
// STACK: Si rimuove l'ultimo elemento inserito
// QUEUE: Si rimuove il più vecchio inseritoo
// in QUEUE si inserisce in fondo
// in STACK si inserisce in testa
// A scopo di implementare la visita in ampiezza
// devo definire la struttura coda e le sue procedure

// Poichè uso QUEUE nel numero giusto una sola volta
// Non ho bisogno di usare una lista linkata per rappresentare
// la QUEUE, per cui uso array statici.

typedef struct {
    int* values;
    int capacity;
    int back_index;
    int front_index;
} queue;

// Implementation
void queue_init(queue* q, int n) {
    q -> values = malloc(n * sizeof(int));
    q -> capacity = n;
    q -> back_index = 0;
    q -> front_index = 0;
}

void queue_pushBack(queue* q, int value) {
    // Mettiamo in back il nuovo elemento
    q -> values[q -> back_index] = value;

    // Avanziamo l'indice di back
    q -> back_index++;
}
int queue_popFront(queue* q) {
    // Ottengo il valore in front
    int picked_value  = q -> values[q -> front_index];

    // Sposto in avanti front
    q -> front_index++;

    return picked_value;
}
int queue_isEmpty(queue* q) {
    // Se i due indici coincidono allora vuol dire che  
    // la coda è vuota
    if (q -> front_index == q -> back_index) {
        return 1;
    }
    // Se ho qualcosa (se gli indici non corrispondono)
    // Ritorno che la QUEUE è non vuota
    return 0;
}

vertex* read_graph(int n) {
    vertex* E = malloc(n * sizeof(vertex));
    int n_adj;
    int current_adj_vertex;

    for (int i = 0; i < n; i++) {
        scanf("%d", &n_adj);
        E[i].n_adj = n_adj;
        E[i].adj = malloc(n_adj * sizeof(int));

        for (int j = 0; j < n_adj; j++) {
            scanf("%d", &current_adj_vertex);
            E[i].adj[j] = current_adj_vertex;
        }
    }

    return E;
}

// Breadth First Search
int min_path_len(vertex* E, int n, int start, int end) {
    int* colors = malloc(n * sizeof(int));
    int* distances = malloc(n * sizeof(int));
    queue q;
    int src, dest;
    int current_distance = 0;

    // Inizializzo i colori
    for (int i = 0; i < n; i++) colors[i] = 0;
    colors[start] = 1;

    // Inizializzo le distanze
    for (int i = 0; i < n; i++) distances[i] = 0;

    // Inizializzo la  coda
    queue_init(&q, n);
    queue_pushBack(&q, start);

    // loop fino a terminazione  della coda
    while (queue_isEmpty(&q) != 1) {
        src = queue_popFront(&q);

        for (int i = 0; i < E[src].n_adj; ++i) {
            dest = E[src].adj[i];

            if (src == end) {
                return 0;
            }

            // Caso in cui il colore del nodo destinazione è bianco
            if (colors[dest] == 0) {
                // Coloro di nero (Appena visitato)
                colors[dest] = 1;
                // Dico che la distanza dell'elemento corrente è quello del vertice di prima + 1
                distances[dest] = distances[src] + 1; 

                // Se ho trovato il nodo che cercavo
                // appena lo trovo esco
                // Se non lo trovo subito, può essere che sta più avanti
                if (dest == end) {
                    return distances[dest];
                } else {
                    queue_pushBack(&q, dest);
                }
            }
        }

    }

    // queue_deinit(&q);
    return -1;
}

int main () {
    int n; // Number of vertices
    int m; // Number of querys
    int query_vertex_start;
    int query_vertex_end;
    vertex* graph = NULL;

    scanf("%d", &n);

    graph = read_graph(n);

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &query_vertex_start, &query_vertex_end);

        printf("%d\n", min_path_len(graph, n, query_vertex_start, query_vertex_end));
    }


    return 0;
}
