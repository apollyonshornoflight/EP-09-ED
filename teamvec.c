#include "teamvec.h"
#include <stdlib.h>

struct teamvec {
    Team **teams;
    int size;
    int capacity;
};

TeamVec *tv_create(void) {
    TeamVec *tv = malloc(sizeof(TeamVec));
    if (tv == NULL)
        return NULL;

    tv->size = 0;
    tv->capacity = 4;
    tv->teams = malloc(tv->capacity * sizeof(Team *));
    if (tv->teams == NULL) {
        free(tv);
        return NULL;
    }
    return tv;
}

void tv_insert(TeamVec *tv, Team *t) {
    if (tv->size == tv->capacity) {
        int new_capacity = tv->capacity * 2;
        Team **new_teams = realloc(tv->teams, new_capacity * sizeof(Team *));
        if (new_teams == NULL)
            return;
        tv->teams = new_teams;
        tv->capacity = new_capacity;
    }
    tv->teams[tv->size] = t;
    tv->size++;
}

int tv_size(TeamVec *tv) {
    return tv->size;
}

Team *tv_get(TeamVec *tv, int i) {
    return tv->teams[i];
}

void tv_free(TeamVec *tv) {
    for (int i = 0; i < tv->size; i++)
        team_free(tv->teams[i]);
    free(tv->teams);
    free(tv);
}