#ifndef CONFIG_H
#define CONFIG_H

/*
    set to 1 for rows to be randomly chosen
    0 to choose rows in order
*/
#define RANDOMIZE_ROWS 1

/*
    set to 1 to use heur system

    will call decHeur or incHeur each time
    a doubly is covered oor uncovered
*/
#define USE_HEUR 1

#if USE_HEUR == 1
    #define HEUR_HEURISTIC(d) { hcol = heuristic((d));}
    #define HEUR_INIT(d, heur_max) { initHeurList((d), (heur_max)); printf("finished heur\n"); }
    #define HEUR_DEC(d, dcol, index, heur) { if((dcol) < (index)) { decHeur((d), (heur), 1); } }
    #define HEUR_INC(d, dcol, index, heur) { if((dcol) < (index)) { incHeur((d), (heur), 1); } }
    #define HEUR_FREE(d) { freeHeur((d)); }
#elif USE_HEUR == 0
    #define HEUR_HEURISTIC(d) { hcol = heuristic2((d)); }
    #define HEUR_INIT(d, heur_max)
    #define HEUR_DEC(d, dcol, index, heur)
    #define HEUR_INC(d, dcol, index, heur)
    #define HEUR_FREE(d)
#else
    #define HEUR_HEURISTIC(d) { error(); }
    #define HEUR_INIT(d, heur_max) { error(); }
    #define HEUR_DEC(d, dcol, index, heur) { error(); }
    #define HEUR_INC(d, dcol, index, heur) { error(); }
    #define HEUR_FREE(d) { error(); }
#endif

/*
    used for list memmory allocation
    starting capacity must be >= 1
    growth factor must be > 1
*/
#define STARTING_CAP 1
#define GROWTH_FACTOR 2

/*
    buffer size for printing
    no error checking for this
*/
#define BUFSIZE 100

#endif