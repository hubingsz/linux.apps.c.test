 /*
 *******************************************************************************
 *
 * Copyright (C) 2019 Momenta Incorporated - http://www.momenta.cn/
 * all rights reserved
 *
 *******************************************************************************
 */


/**
 * file: hal_perf.h
 * description: This file provides interface functions of the HAL performance module
 */

#ifndef __HAL_PERF_H__
#define __HAL_PERF_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define HAL_PERF_CORE_NAME_MAX   (10)

/**
 * enum hal_perf_process_id - Processor core type.
 * description: This enumeration member represents and configures the sequence number of the processor core.
 * deep learning accelerator : DLA : example :TDA2 EVE : TDA4 MMA : NXP AIRUNNER
 */
enum hal_perf_process_id
{
	// IPU 
	HAL_PERF_IPU_0 = 0,
	HAL_PERF_IPU_1,
	HAL_PERF_IPU_2,
	HAL_PERF_IPU_3,
	HAL_PERF_IPU_4,
	HAL_PERF_IPU_5,
	HAL_PERF_IPU_6,
	HAL_PERF_IPU_7,
	// CPU
	HAL_PERF_CPU_0,
	HAL_PERF_CPU_1,
	HAL_PERF_CPU_2,
	HAL_PERF_CPU_3,
	HAL_PERF_CPU_4,
	HAL_PERF_CPU_5,
	HAL_PERF_CPU_6,
	HAL_PERF_CPU_7,
	// DSP
	HAL_PERF_DSP_0,
	HAL_PERF_DSP_1,
	HAL_PERF_DSP_2,
	HAL_PERF_DSP_3,
	HAL_PERF_DSP_4,
	HAL_PERF_DSP_5,
	HAL_PERF_DSP_6,
	HAL_PERF_DSP_7,
	// DLA
	HAL_PERF_DLA_0,
	HAL_PERF_DLA_1,
	HAL_PERF_DLA_2,
	HAL_PERF_DLA_3,
	HAL_PERF_DLA_4,
	HAL_PERF_DLA_5,
	HAL_PERF_DLA_6,
	HAL_PERF_DLA_7,

	HAL_PERF_MAX,
	HAL_PERF_INVALID,
};

/**
 * typedef struct hal_perf_info_t.
 * @integer_val: the integer part of the percentage value
 * @fractional_val: the fractional part of the percentage value
 * @core_name: processor name
 * @core_use_flag: whether to use of the processor
 * description: define CPU usage structure
 */
typedef struct _hal_perf_info_t
{
	unsigned int integer_val;
	unsigned int fractional_val;
	char core_name[HAL_PERF_CORE_NAME_MAX];
	char core_use_flag;
}hal_perf_info_t;

/**
 * typedef struct hal_perf_all_info_t.
 * @perf: struct hal_perf_info_t array
 * description: define CPU usage structure array
 */
typedef struct _hal_perf_all_info_t
{
	hal_perf_info_t perf[HAL_PERF_MAX];
}hal_perf_all_info_t;

/**
 * typedef struct hal_perf_ddr_info_t.
 * @ddr_avg_bw_val: avg bytes read and write per second, in units of MB/s
 * @ddr_peek_bw_val: peak bytes read and write in a sampling period, in units of MB/s
 * @ddr_total_available_val: theoritical bw available to system, in units of MB/s
 * description: DDR Band Width information structure
 */
typedef struct _hal_perf_ddr_info_t
{
	unsigned int ddr_avg_bw_val;
	unsigned int ddr_peek_bw_val;
	unsigned int ddr_total_available_val;
}hal_perf_ddr_info_t;

/**
 * hal_perf_read() - get the usage of a processor.
 * @core_id: processor ID
 * @perf: CPU usage structure pointer
 * @return: success return 0, failure return <0.
 */
int hal_perf_read(int core_id, hal_perf_info_t *perf);

/**
 * hal_perf_read_all() - get the utilization of all processors in the system.
 * @perfall: all CPU usage structure pointer
 * @return: success return 0, failure return <0.
 */
int hal_perf_read_all(hal_perf_all_info_t *perfall);

/**
 * hal_perf_load_start() - Start to calculate the usage of all processors.
 * @return: None
 */
void hal_perf_read_start(void);

/**
 * hal_perf_load_stop_and_print() - end and print usage of all processors in the computing system.
 * @return: None
 * @return: success return 0, failure return <0.
 * description: after executing hal_system_perf_proc_load_start 0.5s, you can print the usage of all processors.
 */
int hal_perf_write_stop(hal_perf_all_info_t *perfall);

/**
 * hal_perf_ddr_read() - get peak and average of memory.
 * @hal_perf_ddr_info_t: memory info struct pointer
 * @return: success return 0, failure return <0.
 */
int hal_perf_ddr_read(hal_perf_ddr_info_t *ddr);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_PERF_H__

