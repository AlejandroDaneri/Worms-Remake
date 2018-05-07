#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define MAX_BUF_LEN 1024

#define MOVING_OBJECT 0
#define DEAD_OBJECT 1
#define ACTION 2

#define WORM_TYPE 0
#define WEAPON_TYPE 1


#define START_TURN 0
#define END_TURN 1
#define MOVE_ACTION 2
#define CHANGE_WEAPON_ACTION 3
#define SHOOT_WEAPON 4
#define SHOOT_SELF_DIRECTED 5

#define MOVE_RIGHT 0
#define MOVE_LEFT 1
#define JUMP 2
#define ROLLBACK 3

#endif
