/******************************************************************************

Copyright (c) [2018 - 2019] MOMENTA Incorporated. All rights reserved.

******************************************************************************/

/**
 * File: hal_camera.h
 *
 * Description: This file provides the interface functions of
 *              the HAL_CAMERA module and the associated structure variable types.
 */

#ifndef __HAL_CAMERA_H__
#define __HAL_CAMERA_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * include files
 */
#include <sys/time.h>
#include <stdbool.h>

/**
 * defines
 *
 * Description: The return status of the HAL CAMERA API.
 */
#define HAL_CAM_RESIZE_MAX_NUM  ((unsigned int)5)

#define HAL_CAM_MODE_OFFLINE    ((unsigned int)0)
#define HAL_CAM_MODE_ONLINE     ((unsigned int)1)

#define HAL_CAM_MODE_ASYNC      ((unsigned int)0)
#define HAL_CAM_MODE_SYNC       ((unsigned int)1)

#define HAL_FRAME_CONTINUES     ((unsigned int)0)
#define HAL_FRAME_LASTEST       ((unsigned int)1)

#define HAL_CAM_NO_RESIZE       ((unsigned int)0)
#define HAL_CAM_RESIZE          ((unsigned int)1)

#define HAL_CAM_TIMESTAMP_NO_ENCODE    ((unsigned int)0)
#define HAL_CAM_TIMESTAMP_ENCODE       (unsigned int)(1)

/**
 *enum _hal_cam_name - camera name.
 *
 * Select the name of the camera config.
 */
enum _hal_cam_name
{
	HAL_CAM_NAME_INVALID = 0,
	HAL_CAM_AR0820_UB953_UB960,
	HAL_CAM_IMX390_UB953_UB960,
};
/**
 *enum _hal_cam_format - Color format.
 *
 * Select the format of the color of the data frame output.
 */
enum _hal_cam_format
{
	HAL_CAM_FORMAT_INVALID = 0,
	HAL_CAM_YUYV422,
	HAL_CAM_UYVY422,
	HAL_CAM_YUV422P,
	HAL_CAM_YUV422I_YUYV,
	HAL_CAM_YUV422SP_UV,
	HAL_CAM_YUV422SP_VU,
	HAL_CAM_YUV420P,
	HAL_CAM_YUV420SP_UV,
	HAL_CAM_YUV420SP_VU,
	HAL_CAM_RGB24_888,
	HAL_CAM_BGR24_888,
	HAL_CAM_RGB32_888,
};

/**
 * Typedef struct hal_frame_resize_t.
 * @rsz_start_x: image scale start point x value
 * @rsz_start_y: image scale start point y value
 * @rsz_end_x: image scale end point x value
 * @rsz_end_y: image scale end point y value
 * @rsz_output_width: output image width after image scale
 * @rsz_output_height: output image height after image scale
 * @rsz_colorformat: output image colorformat after image scale
 * Description:config info for image scale.
 */
typedef struct _hal_frame_resize_t
{
	unsigned int rsz_start_x;
	unsigned int rsz_start_y;
	unsigned int rsz_end_x;
	unsigned int rsz_end_y;
	unsigned int rsz_output_width;
	unsigned int rsz_output_height;
	unsigned int rsz_colorformat;
}hal_frame_resize_t;

/**
 * Typedef struct hal_cam_frame_t.
 * @channel_id: camera channel index means this frame come from which camera
 * @group_id: camera group index means this frame come from which group
 * @exposure_time: camera exposure time
 * @silence_flag: True is mean no camera frame write to disk, False is or not
 * @hw_timestamp: hardware timestamp
 * @timestamp: system timestamp when get camera frame
 * @length: camera frame size = width*height*pixal.size; output only one frame when no resize
 * @buffer: camera frame buffer point at mem; output only one frame when no resize
 * @reserve: reserve
 * Description: camera frame info
 */
typedef struct _hal_cam_frame_t
{
	unsigned int channel_id;
	unsigned int group_id;
	unsigned int exposure_time;
	unsigned int silence_flag;
	unsigned long long hw_timestamp;
	struct timeval timestamp;
	unsigned int length[HAL_CAM_RESIZE_MAX_NUM];
	unsigned char *buffer[HAL_CAM_RESIZE_MAX_NUM];
	unsigned int reserve[4];
}hal_cam_frame_t;

/**
 * typedef hal_cam_callback_t - Define function pointer variable type.
 * @frame: struct hal_cam_frame_t pointer
 *
 * @return: void
 *
 * If the caller uses a custom callback to receive frame data,
 * You can customize a function of this function pointer type and register it in hal_camera_init().
 */
typedef void (*hal_cam_callback_t)(const hal_cam_frame_t* frame);

/**
 * Typedef struct hal_cam_cfg_t.
 * @cam_name: camera name
 * @channel_num: channel number means camera numbers
 * @group_num: group number means camera array numbers
 * @width: camera image width
 * @height: camera image height
 * @color_format: camera image color format
 * @color_length: camera image pixal size for example yuv420 rgb and so on
 * @frame_rate: camera output image frenquence
 * @cam_mode_flag: camera run mode is online or offline
 * @cam_sync_flag: camera sync mode is hardware sync or software sync
 * @frame_sync_flag: frame data sync mode is to output continuous frame or the newest frame
 * @resize_flag: resize flag is need to scale camera image,ture is need, false is or not
 * @resize_cfg: resize config is info for crop resize,such as start or end point
 * @ts_encode_flag: timestamp encode flag is true means write timestamp to evey frame use data block type
 * @cb_func: camera callback func point
 * @reserve: reserve size is 4*sizeof(unsigned int)
 * Description: camera config infomation when camera init use
 */
typedef struct _hal_cam_cfg_t
{
	unsigned int cam_name;
	unsigned int channel_num;
	unsigned int group_num;
	unsigned int width;
	unsigned int height;
	unsigned int color_format;
	float color_length;
	unsigned int frame_rate;
	unsigned int cam_mode_flag; // online or offline
	unsigned int cam_sync_flag;
	unsigned int frame_sync_flag; // continues or lastest
	unsigned int resize_flag;
	hal_frame_resize_t resize_cfg;
	unsigned int ts_encode_flag;
	hal_cam_callback_t cb_func;
	unsigned int reserve[4];
} hal_cam_cfg_t;

/**
 * Typedef struct hal_cam_state_t.
 * @power_state: camera power status
 * @ser_id: can be used to find serializer device still alive
 * @des_id: can be used to find deserializer device still alive
 * @sensor_id: can be used to find camera sensor device still alive
 * @frame_address_high: high mem address 64bit compatibility
 * @frame_address_low: low mem address 64bit compatibility
 * @cam_cfg: camera config info get real time not use config info
 * @reserve: reserve
 * Description: camera status info
 */
typedef struct _hal_cam_state_t
{
	unsigned int power_state;
	unsigned int serializer_id;
	unsigned int deserializer_id;
	unsigned int sensor_id;
	unsigned int frame_address_high;
	unsigned int frame_address_low;
	hal_cam_cfg_t cam_cfg;
	unsigned int reserve[4];
} hal_cam_state_t;

/**
 * hal_cam_init() - init camera device need.
 * @cfg: camera configuration info struct point
 * @desc: describe similar to the fd func in system call, it's just a file handler
 * @return: Success return 0, failure return <0.
 */
int hal_cam_init(const hal_cam_cfg_t* cfg, int* desc);

/**
 * hal_cam_deinit() - Close camera device need.
 * @desc: camera device file handler
 * @return: Success return 0, failure return <0.
 */
int hal_cam_deinit(int desc);

/**
 * hal_cam_start() - start or restart camera device single.
 * @desc: camera device file handler
 * @return: Success return 0, failure return <0.
 */
int hal_cam_start(int desc);

/**
 * hal_cam_stop() - stop or pause camera device single.
 * @desc: camera device file handler
 * @return: Success return 0, failure return <0.
 */
int hal_cam_stop(int desc);

/**
 * hal_cam_register_callback() - camera frame get use callback type get.
 * @desc: camera device file handler
 * @cb: camera callback func
 * @return: Success return 0, failure return <0.
 */
int hal_cam_register_callback(int desc, hal_cam_callback_t cb);

/**
 * hal_cam_read() - camera get frame data.
 * @desc: camera device file handler
 * @frame: all camera frame data info struct
 * @timeout: config camera get camera time while time over
 * @return: Success return 0, failure return <0.
 */
int hal_cam_read(int desc, hal_cam_frame_t* frame, int timeout);

/**
 * hal_cam_try_read() - camera try to get frame data.
 * @desc: camera device file handler
 * @frame: all camera frame data info struct
 * @return: Success return 0, failure return <0.
 */
int hal_cam_try_read(int desc, hal_cam_frame_t* frame);

/**
 * hal_cam_get_state() - camera get camera current status.
 * @desc: camera device file handler
 * @state: current camera status info
 * @return: Success return 0, failure return <0.
 */
int hal_cam_get_state(int desc, hal_cam_state_t* state);

/**
 * hal_cam_malloc() - camera malloc continuous mem, only use in camera run mode is offline.
 * @desc: camera device file handler
 * @data: malloc continuous phy address point for offline
 * @size: malloc size of mem for offline mode
 * @align: alignment of mem is or not
 * @return: Success return 0, failure return <0.
 */
int hal_cam_malloc(int desc, void **data, unsigned int size, unsigned int align);

/**
 * hal_cam_free() - camera free continuous mem, only use in camera run mode is offline.
 * @desc: camera device file handler
 * @data: free continuous phy address point for offline
 * @size: malloc size of mem for offline mode
 * @return: Success return 0, failure return <0.
 */
int hal_cam_free(int desc, void *data, unsigned int size);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_CAMERA_H__