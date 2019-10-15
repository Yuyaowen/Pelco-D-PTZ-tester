#ifndef PROTOCOL_H
#define PROTOCOL_H

#define TURBO_SPEED   0xff
#define MAX_SPEED     0x3f
#define MIN_SPEED     0x00

/* Start cmd1 */
#define AUTO_SCAN     0x90
#define MANUAL_SCAN   0x80
#define CAM_ON        0x88
#define CAM_OFF       0x80
#define IRIS_CLOSE    0x04
#define IRIS_OPEN     0x02
#define FOCUS_NEAR    0x01
/* End cmd1 */

/* Start cmd2 */
#define UP            0x08
#define DOWN          0x10
#define LEFT          0x04
#define RIGHT         0x02
#define ZOOM_TELE     0x20
#define ZOOM_WIDE     0x40
#define FOCUS_FAR     0x80

#define SET_PRESET    0x03
#define DEL_PRESET    0x05
#define CALL_PRESET   0x07
/* End cmd2 */

struct __attribute__((packed)) pelco_d {
    unsigned char sync;
    unsigned char cam_addr;
    unsigned char cmd1;
    unsigned char cmd2;
    unsigned char dat1; // Pan speed
    unsigned char dat2; // Tilt speed
    unsigned char check_sum;
};

#define PELCO_D_LEN sizeof(struct pelco_d)

extern void free_pack(struct pelco_d *pack);
extern struct pelco_d *protocol_stop(unsigned char cam_addr);
extern struct pelco_d *protocol_up(unsigned char cam_addr, unsigned char speed);
extern struct pelco_d *protocol_down(unsigned char cam_addr, unsigned char speed);
extern struct pelco_d *protocol_left(unsigned char cam_addr, unsigned char speed);
extern struct pelco_d *protocol_right(unsigned char cam_addr, unsigned char speed);
extern struct pelco_d *protocol_left_top(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed);
extern struct pelco_d *protocol_right_top(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed);
extern struct pelco_d *protocol_left_bottom(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed);
extern struct pelco_d *protocol_right_bottom(unsigned char cam_addr, unsigned char pan_speed, unsigned char tilt_speed);

extern struct pelco_d *set_preset(unsigned char cam_addr, unsigned char num);
extern struct pelco_d *call_preset(unsigned char cam_addr, unsigned char num);
extern struct pelco_d *del_preset(unsigned char cam_addr, unsigned char num);

#endif // PROTOCOL_H
