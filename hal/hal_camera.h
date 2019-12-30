 /*
 *******************************************************************************
 *
 * Copyright (C) 2019 Momenta Incorporated - http://www.momenta.cn/
 * all rights reserved
 *
 *******************************************************************************
 */

/**
 * hal_camera.h
 * description: hal camera head file with hal API.
 */

#ifndef __HAL_CAMERA_H__
#define __HAL_CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <sys/time.h>
#include <stdbool.h>

/**
 * macros
 * description: the Macro definition of Camera.
 */
#define HAL_CAMERA_MODE_OFFLINE    ((unsigned int)0)
#define HAL_CAMERA_MODE_ONLINE     ((unsigned int)1)

#define HAL_CAMERA_MODE_ASYNC      ((unsigned int)0)
#define HAL_CAMERA_MODE_SYNC       ((unsigned int)1)

#define HAL_FRAME_CONTINUES        ((unsigned int)0)
#define HAL_FRAME_LASTEST          ((unsigned int)1)

#define HAL_CAMERA_TIMESTAMP_NO_ENCODE    ((unsigned int)0)
#define HAL_CAMERA_TIMESTAMP_ENCODE       (unsigned int)(1)

/**
 * enum _hal_camera_name - camera name.
 * select the name of the camera config.
 */
enum hal_camera_name
{
	HAL_CAMERA_NAME_INVALID = 0,
	HAL_CAMERA_AR0820_UB953_UB960,
	HAL_CAMERA_IMX390_UB953_UB960,
};

/**
 * enum _hal_camera_format - Color format.
 * select the format of the color of the data frame output.
 */
enum hal_camera_format
{
	HAL_CAMERA_FORMAT_INVALID = 0,
	HAL_CAMERA_YUYV422,
	HAL_CAMERA_UYVY422,
	HAL_CAMERA_YUV422P,
	HAL_CAMERA_YUV422I_YUYV,
	HAL_CAMERA_YUV422SP_UV,
	HAL_CAMERA_YUV422SP_VU,
	HAL_CAMERA_YUV420P,
	HAL_CAMERA_YUV420SP_UV,
	HAL_CAMERA_YUV420SP_VU,
	HAL_CAMERA_RGB24_888,
	HAL_CAMERA_BGR24_888,
	HAL_CAMERA_RGB32_888,
};

/**
 * typedef struct hal_camera_frame_t.
 * @channel_id: camera channel index means this frame come from which camera
 * @group_id: camera group index means this frame come from which group
 * @exposure_time: camera exposure time
 * @silence_flag: True is mean no camera frame write to disk, False is or not
 * @hw_timestamp: hardware timestamp
 * @timestamp: system timestamp when get camera frame
 * @length: camera frame size = width*height*pixal.size
 * @buffer: camera frame buffer point at mem
 * @reserve: reserve
 * description: camera frame info
 */
typedef struct _hal_camera_frame_t
{
	unsigned int channel_id;
	unsigned int group_id;
	unsigned int exposure_time;
	unsigned int silence_flag;
	unsigned long long hw_timestamp;
	struct timeval timestamp;
	unsigned int length;
	unsigned char *buffer;
	unsigned int reserve[4];
}hal_camera_frame_t;

/**
 * typedef hal_camera_callback_t - Define function pointer variable type.
 * @frame: struct hal_camera_frame_t pointer
 * @return: void
 * description: If the caller uses a custom callback to receive frame data,
 * You can customize a function of this function pointer type and register it in hal_camera_init().
 */
typedef void (*hal_camera_callback_t)(const hal_camera_frame_t* frame);

/**
 * typedef struct hal_camera_cfg_t.
 * @camera_name: camera name
 * @channel_num: channel number means camera numbers
 * @group_num: group number means camera array numbers
 * @width: camera image width
 * @height: camera image height
 * @color_format: camera image color format
 * @color_length: camera image pixal size for example yuv420 rgb and so on
 * @frame_rate: camera output image frenquence
 * @camera_mode_flag: camera run mode is online or offline
 * @camera_sync_flag: camera sync mode is hardware sync or software sync
 * @frame_sync_flag: frame data sync mode is to output continuous frame or the newest frame
 * @ts_encode_flag: timestamp encode flag is true means write timestamp to evey frame use data block type
 * @cb_func: camera callback func point
 * @reserve: reserve size is 4*sizeof(unsigned int)
 * description: camera config infomation when camera init use
 */
typedef struct _hal_camera_cfg_t
{
	unsigned int camera_name;
	unsigned int channel_num;
	unsigned int group_num;
	unsigned int width;
	unsigned int height;
	unsigned int color_format;
	float color_length;
	unsigned int frame_rate;
	unsigned int camera_mode_flag; // online or offline
	unsigned int camera_sync_flag;
	unsigned int frame_sync_flag; // continues or lastest
	unsigned int ts_encode_flag;
	hal_camera_callback_t cb_func;
	unsigned int reserve[4];
} hal_camera_cfg_t;

/**
 * typedef struct hal_camera_state_t.
 * @power_state: camera power status
 * @ser_id: can be used to find serializer device still alive
 * @des_id: can be used to find deserializer device still alive
 * @sensor_id: can be used to find camera sensor device still alive
 * @frame_address_high: high mem address 64bit compatibility
 * @frame_address_low: low mem address 64bit compatibility
 * @camera_cfg: camera config info get real time not use config info
 * @reserve: reserve
 * description: camera status info
 */
typedef struct _hal_camera_state_t
{
	unsigned int power_state;
	unsigned int serializer_id;
	unsigned int deserializer_id;
	unsigned int sensor_id;
	unsigned int frame_address_high;
	unsigned int frame_address_low;
	hal_camera_cfg_t camera_cfg;
	unsigned int reserve[4];
} hal_camera_state_t;

/**
 * hal_camera_init() - init camera device need.
 * @cfg: camera configuration info struct point
 * @desc: describe similar to the fd func in system call, it's just a file handler
 * @return: Success return 0, failure return <0.
 */
int hal_camera_init(const hal_camera_cfg_t* cfg, int* desc);

/**
 * hal_camera_deinit() - Close camera device need.
 * @desc: camera device file handler
 * @return: Success return 0, failure return <0.
 */
int hal_camera_deinit(int desc);

/**
 * hal_camera_start() - start or restart camera device single.
 * @desc: camera device file handler
 * @return: Success return 0, failure return <0.
 */
int hal_camera_start(int desc);

/**
 * hal_camera_stop() - stop or pause camera device single.
 * @desc: camera device file handler
 * @return: Success return 0, failure return <0.
 */
int hal_camera_stop(int desc);

/**
 * hal_camera_register_callback() - camera frame get use callback type get.
 * @desc: camera device file handler
 * @cb: camera callback func
 * @return: Success return 0, failure return <0.
 */
int hal_camera_register_callback(int desc, hal_camera_callback_t cb);

/**
 * hal_camera_read() - camera get frame data.
 * @desc: camera device file handler
 * @frame: all camera frame data info struct
 * @timeout: config camera get camera time while time over
 * @return: Success return 0, failure return <0.
 */
int hal_camera_read(int desc, hal_camera_frame_t* frame, int timeout);

/**
 * hal_camera_try_read() - camera try to get frame data.
 * @desc: camera device file handler
 * @frame: all camera frame data info struct
 * @return: Success return 0, failure return <0.
 */
int hal_camera_try_read(int desc, hal_camera_frame_t* frame);

/**
 * hal_camera_get_state() - camera get camera current status.
 * @desc: camera device file handler
 * @state: current camera status info
 * @return: Success return 0, failure return <0.
 */
int hal_camera_get_state(int desc, hal_camera_state_t* state);

/**
 * hal_camera_malloc() - camera malloc continuous mem, only use in camera run mode is offline.
 * @desc: camera device file handler
 * @data: malloc continuous phy address point for offline
 * @size: malloc size of mem for offline mode
 * @align: alignment of mem is or not
 * @return: Success return 0, failure return <0.
 */
int hal_camera_malloc(int desc, void **data, unsigned int size, unsigned int align);

/**
 * hal_camera_free() - camera free continuous mem, only use in camera run mode is offline.
 * @desc: camera device file handler
 * @data: free continuous phy address point for offline
 * @size: malloc size of mem for offline mode
 * @return: Success return 0, failure return <0.
 */
int hal_camera_free(int desc, void *data, unsigned int size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_CAMERA_H__
