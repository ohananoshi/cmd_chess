/*
    cmd chess header

*/

//==================================== HEADERS ==========================
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//================================= PRE-DEFS ============================

#define TABLE_WIDTH 8
#define TABLE_HEIGHT 8

uint8_t table_pos[8][8] = {1,1,1,1,1,1,1,1,
                          1,1,1,1,1,1,1,1,
                          0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,
                          0,0,0,0,0,0,0,0,
                          2,2,2,2,2,2,2,2,
                          2,2,2,2,2,2,2,2};

//================================== DATATYPES ==========================

typedef struct{
    char name[10];
    uint8_t piece_atual_pos_x;
    uint8_t piece_atual_pos_y;
    uint8_t player;
    bool piece_life;
}PIECE_INFO;

typedef struct{
    PIECE_INFO pawn_status;
    uint8_t** pawn_possible_next_pos;
}PAWN;

typedef struct{
    PIECE_INFO horse_status;
    uint8_t** horse_possible_next_pos;
}HORSE;

typedef struct{
    PIECE_INFO king_status;
    uint8_t** king_possible_next_pos;
}KING;

typedef struct{
    PIECE_INFO tower_status;
    uint8_t** tower_possible_next_pos;
}TOWER;

typedef struct{
    PIECE_INFO bishop_status;
    uint8_t** bishop_possible_next_pos;
}BISHOP;

typedef struct{
    PIECE_INFO queen_status;
    uint8_t** queen_possible_next_pos;
}QUEEN;

typedef struct{
    PAWN player_pawn[8];
    HORSE player_horse[2];
    BISHOP player_bishop[2];
    TOWER player_tower[2];
    KING player_king;
    QUEEN player_queen;

    uint8_t player;
}PLAYER;
//==================================== FUNCTIONS ===================================

uint8_t** pawn_next_pos_calc(PIECE_INFO pawn_status){
    uint8_t** pawn_next_pos = (uint8_t**)calloc(4, sizeof(uint8_t*));
    uint8_t x1, y1, pos_counter = 1;
    uint8_t pos_adds[3][2] = {0,1,1,1,-1,1};

    x1 = pawn_status.piece_atual_pos_x + pos_adds[0][0];
    y1 = pawn_status.piece_atual_pos_y + pos_adds[0][1];

    if(y1 <= TABLE_HEIGHT){
        if(table_pos[x1][y1] != pawn_status.player){
            pawn_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            pawn_next_pos[pos_counter][0] = x1;
            pawn_next_pos[pos_counter][1] = y1;
            pos_counter++;
        }
    }

    x1 = pawn_status.piece_atual_pos_x + pos_adds[1][0];
    y1 = pawn_status.piece_atual_pos_y + pos_adds[1][1];

    if((x1 > 0 && x1 < TABLE_WIDTH) && (y1 > 0 && y1 < TABLE_HEIGHT)){
        if(table_pos[x1][y1] != pawn_status.player && table_pos[x1][y1] != 0){
            pawn_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            pawn_next_pos[pos_counter][0] = x1;
            pawn_next_pos[pos_counter][1] = y1;
            pos_counter++;
        }
    }

    x1 = pawn_status.piece_atual_pos_x + pos_adds[2][0];
    y1 = pawn_status.piece_atual_pos_y + pos_adds[2][1];

    if((x1 > 0 && x1 < TABLE_WIDTH) && (y1 > 0 && y1 < TABLE_HEIGHT)){
        if(table_pos[x1][y1] != pawn_status.player && table_pos[x1][y1] != 0){
            pawn_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            pawn_next_pos[pos_counter][0] = x1;
            pawn_next_pos[pos_counter][1] = y1;
            pos_counter++;
        }
    }
    pawn_next_pos[0] = (uint8_t*)calloc(2, sizeof(uint8_t));
    pawn_next_pos[0][0] = pos_counter-1;
    pawn_next_pos[0][1] = 0;

    return pawn_next_pos;
}

uint8_t** horse_next_pos_calc(PIECE_INFO horse_status){
    uint8_t** horse_next_pos = (uint8_t**)calloc(9, sizeof(uint8_t*));
    uint8_t x1, y1, pos_counter = 1;
    uint8_t pos_adds[8][2] = {1,3,1,-3,-1,3,-1,-3,3,1,3,-1,-3,1,-3,-1};

    for(uint8_t i = 0; i < 8; i++){

        x1 = horse_status.piece_atual_pos_x + pos_adds[i][0];
        y1 = horse_status.piece_atual_pos_y + pos_adds[i][1];

        if((x1 > 0 && x1 < TABLE_WIDTH) && (y1 > 0 && y1 < TABLE_HEIGHT)){
            if(table_pos[x1][y1] != horse_status.player){
                horse_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
                horse_next_pos[pos_counter][0] = x1;
                horse_next_pos[pos_counter][1] = y1;
                pos_counter++;
            }
        }
    }
    horse_next_pos[0] = (uint8_t*)calloc(2, sizeof(uint8_t));
    horse_next_pos[0][0] = pos_counter - 1;
    horse_next_pos[0][1] = 0;

    return horse_next_pos;
}

uint8_t** king_next_pos_calc(PIECE_INFO king_status){
    uint8_t** king_next_pos = (uint8_t**)calloc(8, sizeof(uint8_t*));
    uint8_t x1, y1, pos_counter = 1;

    y1 = king_status.piece_atual_pos_y + 1;
    if(y1 <= TABLE_HEIGHT && table_pos[king_status.piece_atual_pos_x][y1] == 0){
        king_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        king_next_pos[pos_counter][0] = king_status.piece_atual_pos_x;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    x1 = king_status.piece_atual_pos_x + 1;
    if(x1 <= TABLE_WIDTH && table_pos[x1][king_status.piece_atual_pos_y] == 0){
        king_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = king_status.piece_atual_pos_y;
        pos_counter++;
    }
    if(table_pos[x1][y1] == 0){
        king_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    y1 = king_status.piece_atual_pos_y - 1;
    if(y1 > 0 && table_pos[king_status.piece_atual_pos_x][y1] == 0){
        king_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        king_next_pos[pos_counter][0] = king_status.piece_atual_pos_x;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    x1 = king_status.piece_atual_pos_x - 1;
    if(x1 > 0 && table_pos[x1][king_status.piece_atual_pos_y] == 0){
        king_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = king_status.piece_atual_pos_y;
        pos_counter++;
    }
    if(table_pos[x1][y1] == 0){
        king_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        king_next_pos[pos_counter][0] = x1;
        king_next_pos[pos_counter][1] = y1;
        pos_counter++;
    }
    
}

uint8_t** tower_next_pos_calc(PIECE_INFO tower_status){

    uint8_t** tower_next_pos = (uint8_t**)calloc(14, sizeof(uint8_t*));
    uint8_t x1, y1, pos_counter = 1;

    for(uint8_t i = tower_status.piece_atual_pos_x + 1; i <= TABLE_WIDTH; i++){
        if(table_pos[i][tower_status.piece_atual_pos_y] == tower_status.player) break;
        if(table_pos[i][tower_status.piece_atual_pos_y] != tower_status.player && table_pos[i][tower_status.piece_atual_pos_y] != 0){
            tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            tower_next_pos[pos_counter][0] = i;
            tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        tower_next_pos[pos_counter][0] = i;
        tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
        pos_counter++;
    }
    for(uint8_t i = tower_status.piece_atual_pos_x - 1; i > 0; i--){
        if(table_pos[i][tower_status.piece_atual_pos_y] == tower_status.player) break;
        if(table_pos[i][tower_status.piece_atual_pos_y] != tower_status.player && table_pos[i][tower_status.piece_atual_pos_y] != 0){
            tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            tower_next_pos[pos_counter][0] = i;
            tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        tower_next_pos[pos_counter][0] = i;
        tower_next_pos[pos_counter][1] = tower_status.piece_atual_pos_y;
        pos_counter++;
    }
    for(uint8_t i = tower_status.piece_atual_pos_y + 1; i <= TABLE_HEIGHT; i++){
        if(table_pos[tower_status.piece_atual_pos_x][i] == tower_status.player) break;
        if(table_pos[tower_status.piece_atual_pos_x][i] != tower_status.player && table_pos[tower_status.piece_atual_pos_x][i] != 0){
            tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
            tower_next_pos[pos_counter][1] = i;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
        tower_next_pos[pos_counter][1] = i;
        pos_counter++;
    }
    for(uint8_t i = tower_status.piece_atual_pos_y - 1; i > 0; i--){
        if(table_pos[tower_status.piece_atual_pos_x][i] == tower_status.player) break;
        if(table_pos[tower_status.piece_atual_pos_x][i] != tower_status.player && table_pos[tower_status.piece_atual_pos_x][i] != 0){
            tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
            tower_next_pos[pos_counter][1] = i;
            pos_counter++;
            break;
        }
        tower_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        tower_next_pos[pos_counter][0] = tower_status.piece_atual_pos_x;
        tower_next_pos[pos_counter][1] = i;
        pos_counter++;
    }

    tower_next_pos[0] = (uint8_t*)calloc(2, sizeof(uint8_t));
    tower_next_pos[0][0] = pos_counter - 1;
    tower_next_pos[0][1] = 0;

    return tower_next_pos;
}

uint8_t** bishop_next_pos_calc(PIECE_INFO bishop_status){
    uint8_t** bishop_next_pos = (uint8_t**)calloc(26, sizeof(uint8_t*));
    uint8_t x1, y1, pos_counter = 1;

    for(uint8_t i = bishop_status.piece_atual_pos_x + 1, j = bishop_status.piece_atual_pos_y + 1; i <= TABLE_WIDTH && j <= TABLE_HEIGHT; i++, j++){
        if(table_pos[i][j] == bishop_status.player) break;
        if(table_pos[i][j] != bishop_status.player && table_pos[i][j] != 0){
            bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            bishop_next_pos[pos_counter][0] = i;
            bishop_next_pos[pos_counter][1] = j;
            pos_counter++;
            break;
        }
        bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        bishop_next_pos[pos_counter][0] = i;
        bishop_next_pos[pos_counter][1] = j;
        pos_counter++;
    }
    for(uint8_t i = bishop_status.piece_atual_pos_x + 1, j = bishop_status.piece_atual_pos_y - 1; i <= TABLE_WIDTH && j > 0; i++, j--){
        if(table_pos[i][j] == bishop_status.player) break;
        if(table_pos[i][j] != bishop_status.player && table_pos[i][j] != 0){
            bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            bishop_next_pos[pos_counter][0] = i;
            bishop_next_pos[pos_counter][1] = j;
            pos_counter++;
            break;
        }
        bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        bishop_next_pos[pos_counter][0] = i;
        bishop_next_pos[pos_counter][1] = j;
        pos_counter++;
    }
    for(uint8_t i = bishop_status.piece_atual_pos_x - 1, j = bishop_status.piece_atual_pos_y + 1; i > 0 && j <= TABLE_HEIGHT; i--, j++){
        if(table_pos[i][j] == bishop_status.player) break;
        if(table_pos[i][j] != bishop_status.player && table_pos[i][j] != 0){
            bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            bishop_next_pos[pos_counter][0] = i;
            bishop_next_pos[pos_counter][1] = j;
            pos_counter++;
            break;
        }
        bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        bishop_next_pos[pos_counter][0] = i;
        bishop_next_pos[pos_counter][1] = j;
        pos_counter++;
    }
    for(uint8_t i = bishop_status.piece_atual_pos_x - 1, j = bishop_status.piece_atual_pos_y - 1; i > 0 && j > 0; i--, j--){
        if(table_pos[i][j] == bishop_status.player) break;
        if(table_pos[i][j] != bishop_status.player && table_pos[i][j] != 0){
            bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
            bishop_next_pos[pos_counter][0] = i;
            bishop_next_pos[pos_counter][1] = j;
            pos_counter++;
            break;
        }
        bishop_next_pos[pos_counter] = (uint8_t*)calloc(2, sizeof(uint8_t));
        bishop_next_pos[pos_counter][0] = i;
        bishop_next_pos[pos_counter][1] = j;
        pos_counter++;
    }

    bishop_next_pos[0] = (uint8_t*)calloc(2, sizeof(uint8_t));
    bishop_next_pos[0][0] = pos_counter;
    bishop_next_pos[0][1] = 0;

    return bishop_next_pos;
}

uint8_t** queen_next_pos_calc(PIECE_INFO queen_status){
    uint8_t** temp_diagonal = bishop_next_pos_calc(queen_status);
    uint8_t** temp_lines = tower_next_pos_calc(queen_status);

    uint8_t** queen_next_pos = (uint8_t**)calloc(temp_diagonal[0][0] + temp_lines[0][0], sizeof(uint8_t*));

    for(uint8_t i = 1; i <= temp_diagonal[0][0]; i++){
        queen_next_pos[i] = (uint8_t*)calloc(2, sizeof(uint8_t));
        queen_next_pos[i][0] = temp_diagonal[i][0];
        queen_next_pos[i][1] = temp_diagonal[i][1];
    }
    for(uint8_t i = temp_diagonal[0][0] + 1; i <= (temp_lines[0][0] + temp_diagonal[0][0]); i++){
        queen_next_pos[i] = (uint8_t*)calloc(2, sizeof(uint8_t));
        queen_next_pos[i][0] = temp_diagonal[i][0];
        queen_next_pos[i][1] = temp_diagonal[i][1];
    }

    return queen_next_pos;
}

void piece_init(PIECE_INFO* piece, uint8_t player, char* piece_name, uint8_t piece_start_pos_x, uint8_t piece_start_pos_y){
    sprintf(piece->name, "%s%d", piece_name, player);
    piece->player = player;
    piece->piece_life = 1;
    piece->piece_atual_pos_x = piece_start_pos_x;
    piece->piece_atual_pos_y = piece_start_pos_y;
}

void player_init(PLAYER* player, uint8_t player_number){
    player->player = player_number;
    
    if(player_number == 1){
        //pawns init
        for(uint8_t i = 1; i <= 8; i++){
            piece_init(&(player->player_pawn[i-1].pawn_status), player->player, "PAWN", i, 7);
        }
        //towers init
        piece_init(&(player->player_tower[0].tower_status), player->player, "TOWER", 1, 8);
        piece_init(&(player->player_tower[1].tower_status), player->player, "TOWER", 8, 8);
        //bishop init
        piece_init(&(player->player_bishop[0].bishop_status), player->player, "BISHOP", 3, 8);
        piece_init(&(player->player_bishop[1].bishop_status), player->player, "BISHOP", 6, 8);
        //horse init
        piece_init(&(player->player_horse[0].horse_status), player->player, "HORSE", 2, 8);
        piece_init(&(player->player_horse[1].horse_status), player->player, "HORSE", 7, 8);
        //king init
        piece_init(&(player->player_king.king_status), player->player, "KING", 5, 8);
        //queen init
        piece_init(&(player->player_queen.queen_status), player->player, "QUEEN", 6, 8);
    }else{
        //pawns init
        for(uint8_t i = 1; i <= 8; i++){
            piece_init(&(player->player_pawn[i-1].pawn_status), player->player, "PAWN", i, 2);
        }
        //towers init
        piece_init(&(player->player_tower[0].tower_status), player->player, "TOWER", 1, 1);
        piece_init(&(player->player_tower[1].tower_status), player->player, "TOWER", 8, 1);
        //bishop init
        piece_init(&(player->player_bishop[0].bishop_status), player->player, "BISHOP", 3, 1);
        piece_init(&(player->player_bishop[1].bishop_status), player->player, "BISHOP", 6, 1);
        //horse init
        piece_init(&(player->player_horse[0].horse_status), player->player, "HORSE", 2, 1);
        piece_init(&(player->player_horse[1].horse_status), player->player, "HORSE", 7, 1);
        //king init
        piece_init(&(player->player_king.king_status), player->player, "KING", 6, 1);
        //queen init
        piece_init(&(player->player_queen.queen_status), player->player, "QUEEN", 5, 1);
    } 
}

