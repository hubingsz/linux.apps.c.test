 /*
 *******************************************************************************
 *
 * Copyright (C) 2019 Momenta Incorporated - http://www.momenta.cn/
 * all rights reserved
 *
 *******************************************************************************
 */

/**
 * file: hal_version.h
 * description: This file provides an interface to get version information.
 */

#ifndef __HAL_VERSION_H__
#define __HAL_VERSION_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * typedef struct hal_version_t.
 * @sdk_major: SDK-based major version  number
 * @sdk_minor: SDK-based minor version  number
 * @hal_major:  hal major version  number
 * @hal_minor: hal minor version  number
 * @hal_tailor: hal tail version  number
 * @hal_rc: hal  release candidate version  number
 * description: The specific version number is implemented in the hal_version.c file
 */
typedef struct _hal_version_t
{
	unsigned char sdk_major;
	unsigned char sdk_minor;
	unsigned char hal_major;
	unsigned char hal_minor;
	unsigned char hal_endor;
	unsigned char hal_rc;
} hal_version_t;

/**
 * hal_get_version() - Get version information.
 * @desc: hal version file handler
 * @ver_info: hal version infomention
 * @return: success is 0, failure  < 0.
 */
int hal_get_version(hal_version_t *ver_info, int *desc);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_VERSION_H__

