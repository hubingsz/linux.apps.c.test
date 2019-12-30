 /*
 *******************************************************************************
 *
 * Copyright (C) 2019 Momenta Incorporated - http://www.momenta.cn/
 * all rights reserved
 *
 *******************************************************************************
 */


/**
 * file: hal_pref.h
 * description: This file provides interface functions of the HAL performance module
 */

#ifndef __HAL_PREF_H__
#define __HAL_PREF_H__

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
 * @flag: whether to use of the processor
 * description: define CPU usage structure
 */
typedef struct _hal_perf_info_t
{
	unsigned int integer_val;
	unsigned int fractional_val;
	char core_name[HAL_PERF_CORE_NAME_MAX];
	char flag;
}hal_perf_info_t;

/**
 * typedef struct hal_perf_all_info_t.
 * @perf: Struct hal_perf_info_t array
 * description: Define CPU usage structure array
 */
typedef struct _hal_perf_all_info_t
{
	hal_perf_info_t perf[HAL_PERF_MAX];
}hal_perf_all_info_t;

/**
 * hal_system_get_perf() - Get the usage of a processor.
 * @core_id: Processor ID
 * @perf: CPU usage structure pointer
 * @return: Success return 0, failure return <0.
 */
int hal_perf_get(int core_id, hal_perf_info_t *perf);

/**
 * hal_system_get_perf_all() - Get the utilization of all processors in the system.
 * @perfall: All CPU usage structure pointer
 * @return: Success return 0, failure return <0.
 */
int hal_perf_get_all(hal_perf_all_info_t *perfall);

/**
 * hal_system_print_perf_all() - Printf the utilization of all processors in the system.
 * @perfall: All CPU usage structure pointer
 * @return: None
 */
void hal_perf_print_all(hal_perf_all_info_t *perfall);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //__HAL_PREF_H__

