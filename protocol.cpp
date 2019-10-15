#include <stdlib.h>
#include "protocol.h"

static unsigned char check_sum(unsigned char *pak)
{
    int i;
    unsigned char sum = 0;

    for (i = 0; i < 5; i++) {
        sum += pak[i];
    }

    pak[i] = sum;

    return sum;
}

static struct pelco_d *pack_cmd(unsigned char cam_addr, unsigned char cmd1, unsigned char cmd2, unsigned char dat1, unsigned char dat2)
{
    struct pelco_d *package;

    package = (struct pelco_d *)malloc(sizeof(struct pelco_d));
    if (package == NULL)
        return NULL;

    package->sync = 0xff;
    package->cam_addr = cam_addr;
    package->cmd1 = cmd1;
    package->cmd2 = cmd2;
    package->dat1 = dat1;
    package->dat2 = dat2;
    check_sum((unsigned char *)package + 1);

    return package;
}

void free_pack(struct pelco_d *pack)
{
    if (pack != NULL) {
        free(pack);
        pack = NULL;
    }
}

struct pelco_d *protocol_stop(unsigned char cam_addr)
{
    return pack_cmd(cam_addr, 0, 0, 0, 0);
}

struct pelco_d *protocol_up(unsigned char cam_addr, unsigned char speed)
{
    return pack_cmd(cam_addr, 0, UP, 0, speed);
}

struct pelco_d *protocol_down(unsigned char cam_addr, unsigned char speed)
{
    return pack_cmd(cam_addr, 0, DOWN, 0, speed);
}

struct pelco_d *protocol_left(unsigned char cam_addr, unsigned char speed)
{
    return pack_cmd(cam_addr, 0, LEFT, speed, 0);
}

struct pelco_d *protocol_right(unsigned char cam_addr, unsigned char speed)
{
    return pack_cmd(cam_addr, 0, RIGHT, speed, 0);
}

struct pelco_d *protocol_left_top(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed)
{
    return pack_cmd(cam_addr, 0, UP | LEFT, pan_speed, tilt_speed);
}

struct pelco_d *protocol_right_top(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed)
{
    return pack_cmd(cam_addr, 0, UP | RIGHT, pan_speed, tilt_speed);
}

struct pelco_d *protocol_left_bottom(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed)
{
    return pack_cmd(cam_addr, 0, DOWN | LEFT, pan_speed, tilt_speed);
}

struct pelco_d *protocol_right_bottom(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed)
{
    return pack_cmd(cam_addr, 0, DOWN | RIGHT, pan_speed, tilt_speed);
}

struct pelco_d *set_preset(unsigned char cam_addr, unsigned char num)
{
    return pack_cmd(cam_addr, 0, SET_PRESET, 0, num);
}

struct pelco_d *call_preset(unsigned char cam_addr, unsigned char num)
{
    return pack_cmd(cam_addr, 0, CALL_PRESET, 0, num);
}

struct pelco_d *del_preset(unsigned char cam_addr, unsigned char num)
{
    return pack_cmd(cam_addr, 0, DEL_PRESET, 0, num);
}
