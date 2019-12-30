/******************************************************************************

Copyright (c) [2018 - 2019] MOMENTA Incorporated. All rights reserved.

******************************************************************************/

/**
 * File: hal_version.h
 *
 * Description: This file provides an interface to get version information.
 *              
 */

#ifndef __HAL_VERSION_H__
#define __HAL_VERSION_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * hal_version - hal version module data struct.
 * @sdk_major: SDK-based major version  number
 * @sdk_minor: SDK-based minor version  number
 * @hal_major:  hal major version  number
 * @hal_minor: hal minor version  number
 * @hal_tailor: hal tail version  number
 * @hal_rc: hal  release candidate version  number
 * @note: The specific version number is implemented in the hal_version.c file
 */
typedef struct hal_version
{
	char sdk_major;
	char sdk_minor;
	char hal_major;
	char hal_minor;
	char hal_endor;
	char hal_rc;
} hal_version_t;

/**
 * hal_get_version() - Get version information.
 * @desc: hal version file handler
 * @ver_info: hal version infomention
 * @return: success is 0, failure  < 0.
 */
int hal_get_version(int *desc, hal_version_t *ver_info);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_VERSION_H__

