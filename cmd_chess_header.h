/*
    cmd chess header

*/

//==================================== HEADERS ==========================
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

//================================= PRE-DEFS ============================

#define TABLE_WIDTH 8
#define TABLE_HEIGHT 8

//================================== DATATYPES ==========================

typedef struct{
    char* name;
    uint8_t piece_atual_pos_x;
    uint8_t piece_atual_pos_y;
    bool piece_life;
    bool player;
}piece;

typedef struct{
    piece pawn;
    int8_t pawn_possible_next_pos[3][2];
}PAWN;

typedef struct{
    piece horse;

    int8_t horse_possible_next_pos[8][2];
}HORSE;

typedef struct{
    piece tower;

    int8_t** tower_next_pos;
}TOWER;

//==================================== FUNCTIONS ===================================

int8_t** pawn_next_pos_calc(piece pawn){
    int8_t** pawn_next_pos = (int8_t**)calloc(3, sizeof(int8_t*));
    for(uint8_t i = 0; i < 3; i++){
        pawn_next_pos[i] = (int8_t*)calloc(2, sizeof(int8_t));
    }

    pawn_next_pos = {pawn.piece_atual_pos_x, pawn.piece_atual_pos_y + 1,
                     pawn.piece_atual_pos_x + 1, pawn.piece_atual_pos_y + 1,
                     pawn.piece_atual_pos_x - 1, pawn.piece_atual_pos_y + 1};
}

int8_t** horse_next_pos_calc(piece horse){
    int8_t** horse_next_pos = (int8_t**)calloc(8, sizeof(int8_t*));
    for(uint8_t i = 0; i < 8; i++){
        horse_next_pos[i] = (int8_t*)calloc(2, sizeof(int8_t));
    }
    
    horse_next_pos = {horse.piece_atual_pos_x + 1,horse.piece_atual_pos_y + 3,
                      horse.piece_atual_pos_x + 1,horse.piece_atual_pos_y - 3,
                      horse.piece_atual_pos_x - 1,horse.piece_atual_pos_y + 3,
                      horse.piece_atual_pos_x - 1,horse.piece_atual_pos_y - 3,
                      horse.piece_atual_pos_x + 3,horse.piece_atual_pos_y + 1,
                      horse.piece_atual_pos_x + 3,horse.piece_atual_pos_y - 1,
                      horse.piece_atual_pos_x - 3,horse.piece_atual_pos_y + 1,
                      horse.piece_atual_pos_x - 3,horse.piece_atual_pos_y - 1};
}

int8_t** tower_next_pos_calc(piece tower){
    int8_t** tower_possible_next_pos = (int8_t**)calloc(2, sizeof(int8_t*));
    tower_possible_next_pos[0] = (int8_t*)calloc(2, sizeof(int8_t));
    tower_possible_next_pos[1] = (int8_t*)calloc(2, sizeof(int8_t));
    uint8_t k = 1;

    //left track
    for(uint8_t i = tower.piece_atual_pos_x + 1; i < TABLE_WIDTH; i++){
        tower_possible_next_pos[k][0] = i;
        tower_possible_next_pos[k][1] = tower.piece_atual_pos_y;
        tower_possible_next_pos = (int8_t**)realloc(tower_possible_next_pos, (k+2)*sizeof(int8_t**));
        tower_possible_next_pos[k+1] = (int8_t*)calloc(2, sizeof(int8_t));
        k++;
    }
    //right track
    for(uint8_t i = tower.piece_atual_pos_x - 1; i > 0; i--){
        tower_possible_next_pos[k][0] = i;
        tower_possible_next_pos[k][1] = tower.piece_atual_pos_y;
        tower_possible_next_pos = (int8_t**)realloc(tower_possible_next_pos, (k+2)*sizeof(int8_t**));
        tower_possible_next_pos[k+1] = (int8_t*)calloc(2, sizeof(int8_t));
        k++;
    }
    //up track
    for(uint8_t i = tower.piece_atual_pos_y + 1; i < TABLE_HEIGHT; i++){
        tower_possible_next_pos[k][0] = tower.piece_atual_pos_x;
        tower_possible_next_pos[k][1] = i;
        tower_possible_next_pos = (int8_t**)realloc(tower_possible_next_pos, (k+2)*sizeof(int8_t**));
        tower_possible_next_pos[k+1] = (int8_t*)calloc(2, sizeof(int8_t));
        k++;
    }
    //down track
    for(uint8_t i = tower.piece_atual_pos_y - 1; i > 0; i--){
        tower_possible_next_pos[k][0] = tower.piece_atual_pos_x;
        tower_possible_next_pos[k][1] = i;
        tower_possible_next_pos = (int8_t**)realloc(tower_possible_next_pos, (k+2)*sizeof(int8_t**));
        tower_possible_next_pos[k+1] = (int8_t*)calloc(2, sizeof(int8_t));
        k++;
    }

    tower_possible_next_pos[0][0] = (int8_t)k;
    tower_possible_next_pos[0][0] = 0;

    return tower_possible_next_pos;
}
