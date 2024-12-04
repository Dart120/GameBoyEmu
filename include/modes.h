
#ifndef MODES_H
#define MODES_H
enum MODES {
        H_BLANK = 0,
        V_BLANK = 1,
        OAM_SCAN = 2,
        DRAW = 3       
};

enum PF_MODES {
        GET_TILE = 0,
        GET_TILE_DATA_LOW = 1,
        GET_TILE_DATA_HIGH = 2,
      
        PUSH = 3
};
#endif