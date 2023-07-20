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

int8_t table_pos[8][8] = {1,1,1,1,1,1,1,1,
                          1,1,1,1,1,1,1,1,
                          0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,
                          2,2,2,2,2,2,2,2,
                          2,2,2,2,2,2,2,2};

//================================== DATATYPES ==========================

typedef struct{
    char* name;
    uint8_t piece_atual_pos_x;
    uint8_t piece_atual_pos_y;
    bool piece_life;
    uint8_t player;
}PIECE_INFO;

typedef struct{
    PIECE_INFO pawn_status;
    int8_t pawn_possible_next_pos[3][2];
}PAWN;

typedef struct{
    PIECE_INFO horse_status;
    int8_t horse_possible_next_pos[8][2];
}HORSE;

typedef struct{
    PIECE_INFO king_status;
    int8_t king_possible_next_pos[8][2];
}KING;

typedef struct{
    PIECE_INFO tower_status;
    int8_t** tower_possible_next_pos;
}TOWER;

typedef struct{
    PIECE_INFO bisjop_status;
    int8_t** bishop_possible_next_pos;
}BISHOP;

typedef struct{
    PIECE_INFO queen_status;
    int8_t** queen_possible_next_pos;
}QUEEN;

//==================================== FUNCTIONS ===================================

int8_t** pawn_next_pos_calc(PIECE_INFO pawn_status){
    int8_t** pawn_next_pos = (int8_t**)calloc(4, sizeof(int8_t*));
    int8_t x1, y1, pos_counter = 1;
    int8_t pos_adds[3][2] = {0,1,1,1,-1,1};

    x1 = pawn_status.piece_atual_pos_x + pos_adds[0][0];
    y1 = pawn_status.piece_atual_pos_y + pos_adds[0][1];

    if(y1 <= TABLE_HEIGHT){
        if(table_pos[x1][y1] != pawn_status.player){
            pawn_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            pawn_next_pos[pos_counter][0] = x1;
            pawn_next_pos[pos_counter][1] = y1;
            pos_counter++;
        }
    }

    x1 = pawn_status.piece_atual_pos_x + pos_adds[1][0];
    y1 = pawn_status.piece_atual_pos_y + pos_adds[1][1];

    if((x1 > 0 && x1 < TABLE_WIDTH) && (y1 > 0 && y1 < TABLE_HEIGHT)){
        if(table_pos[x1][y1] != pawn_status.player && table_pos[x1][y1] != 0){
            pawn_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            pawn_next_pos[pos_counter][0] = x1;
            pawn_next_pos[pos_counter][1] = y1;
            pos_counter++;
        }
    }

    x1 = pawn_status.piece_atual_pos_x + pos_adds[2][0];
    y1 = pawn_status.piece_atual_pos_y + pos_adds[2][1];

    if((x1 > 0 && x1 < TABLE_WIDTH) && (y1 > 0 && y1 < TABLE_HEIGHT)){
        if(table_pos[x1][y1] != pawn_status.player && table_pos[x1][y1] != 0){
            pawn_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            pawn_next_pos[pos_counter][0] = x1;
            pawn_next_pos[pos_counter][1] = y1;
            pos_counter++;
        }
    }
    pawn_next_pos[0] = (int8_t*)calloc(2, sizeof(int8_t));
    pawn_next_pos[0][0] = pos_counter-1;
    pawn_next_pos[0][1] = 0;

    return pawn_next_pos;
}

int8_t** horse_next_pos_calc(PIECE_INFO horse_status){
    int8_t** horse_next_pos = (int8_t**)calloc(9, sizeof(int8_t*));
    int8_t x1, y1, pos_counter = 1;
    int8_t pos_adds[8][2] = {1,3,1,-3,-1,3,-1,-3,3,1,3,-1,-3,1,-3,-1};

    for(uint8_t i = 0; i < 8; i++){

        x1 = horse_status.piece_atual_pos_x + pos_adds[i][0];
        y1 = horse_status.piece_atual_pos_y + pos_adds[i][1];

        if((x1 > 0 && x1 < TABLE_WIDTH) && (y1 > 0 && y1 < TABLE_HEIGHT)){
            if(table_pos[x1][y1] != horse_status.player){
                horse_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
                horse_next_pos[pos_counter][0] = x1;
                horse_next_pos[pos_counter][1] = y1;
                pos_counter++;
            }
        }
    }
    horse_next_pos[0] = (int8_t*)calloc(2, sizeof(int8_t));
    horse_next_pos[0][0] = pos_counter - 1;
    horse_next_pos[0][1] = 0;

    return horse_next_pos;
}

int8_t** king_next_pos_calc(PIECE_INFO king_status){
    int8_t** king_next_pos = (int8_t**)calloc(8, sizeof(int8_t*));
    int8_t x1, y1, pos_counter = 1;

    y1 = king_status.piece_atual_pos_y + 1;
    if(y1 <= TABLE_HEIGHT && table_pos[king_status.piece_atual_pos_x][y1] == 0){
        king_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        king_next_pos[pos_counter][0] = king_status.piece_atual_pos_x;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    x1 = king_status.piece_atual_pos_x + 1;
    if(x1 <= TABLE_WIDTH && table_pos[x1][king_status.piece_atual_pos_y] == 0){
        king_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = king_status.piece_atual_pos_y;
        pos_counter++;
    }
    if(table_pos[x1][y1] == 0){
        king_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    y1 = king_status.piece_atual_pos_y - 1;
    if(y1 > 0 && table_pos[king_status.piece_atual_pos_x][y1] == 0){
        king_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        king_next_pos[pos_counter][0] = king_status.piece_atual_pos_x;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    x1 = king_status.piece_atual_pos_x - 1;
    if(x1 > 0 && table_pos[x1][king_status.piece_atual_pos_y] == 0){
        king_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = king_status.piece_atual_pos_y;
        pos_counter++;
    }
    if(table_pos[x1][y1] == 0){
        king_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    
}

int8_t** tower_next_pos_calc(PIECE_INFO tower_status){

    int8_t** tower_next_pos = (int8_t**)calloc(14, sizeof(int8_t*));
    int8_t x1, y1, pos_counter = 1;

    for(uint8_t i = tower_status.piece_atual_pos_x + 1; i <= TABLE_WIDTH; i++){
        if(table_pos[i][tower_status.piece_atual_pos_y] == tower_status.player) break;
        if(table_pos[i][tower_status.piece_atual_pos_y] != tower_status.player && table_pos[i][tower_status.piece_atual_pos_y] != 0){
            tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            tower_next_pos[pos_counter][0] = i;
            tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        tower_next_pos[pos_counter][0] = i;
        tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
        pos_counter++;
    }
    for(uint8_t i = tower_status.piece_atual_pos_x - 1; i > 0; i--){
        if(table_pos[i][tower_status.piece_atual_pos_y] == tower_status.player) break;
        if(table_pos[i][tower_status.piece_atual_pos_y] != tower_status.player && table_pos[i][tower_status.piece_atual_pos_y] != 0){
            tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            tower_next_pos[pos_counter][0] = i;
            tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        tower_next_pos[pos_counter][0] = i;
        tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
        pos_counter++;
    }
    for(uint8_t i = tower_status.piece_atual_pos_y + 1; i <= TABLE_HEIGHT; i++){
        if(table_pos[tower_status.piece_atual_pos_x][i] == tower_status.player) break;
        if(table_pos[tower_status.piece_atual_pos_x][i] != tower_status.player && table_pos[tower_status.piece_atual_pos_x][i] != 0){
            tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
            tower_next_pos[pos_counter][1] = i;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
        tower_next_pos[pos_counter][1] = i;
        pos_counter++;
    }
    for(uint8_t i = tower_status.piece_atual_pos_y - 1; i > 0; i--){
        if(table_pos[tower_status.piece_atual_pos_x][i] == tower_status.player) break;
        if(table_pos[tower_status.piece_atual_pos_x][i] != tower_status.player && table_pos[tower_status.piece_atual_pos_x][i] != 0){
            tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
            tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
            tower_next_pos[pos_counter][1] = i;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (int8_t*)calloc(2, sizeof(int8_t));
        tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
        tower_next_pos[pos_counter][1] = i;
        pos_counter++;
    }

    tower_next_pos[0] = (int8_t*)calloc(2, sizeof(int8_t));
    tower_next_pos[0][0] = pos_counter - 1;
    tower_next_pos[0][1] = 0;

    return tower_next_pos;
}

int8_t** bishop_next_pos_calc(PIECE_INFO bishop_status){
    int8_t** bishop_next_pos = (int8_t**)calloc(26, sizeof(int8_t*));
    int8_t x1, y1, pos_counter = 1;
    bool break_flag = 0;

    for(uint8_t i = bishop_status.piece_atual_pos_x + 1; i <= TABLE_WIDTH; i++){
        for(uint8_t j = bishop_status.piece_atual_pos_y + 1; j <= TABLE_HEIGHT; j++){
            if(table_pos[i][j] == bishop_status.player){
                break_flag = 1;
                break;
            }
        }
        if(break_flag) break;
    }
}