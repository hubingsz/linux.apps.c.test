 /*
 *******************************************************************************
 *
 * Copyright (C) 2019 Momenta Incorporated - http://www.momenta.cn/
 * all rights reserved
 *
 *******************************************************************************
 */

/**
 * file: hal_common.h
 * description: hal common head file with hal API.
 */

#ifndef __HAL_COMMON_H__
#define __HAL_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*
 * Common macro definitions
 */
#define HAL_STATUS_OK               (0)
#define HAL_STATUS_EFAIL            (-1)
#define HAL_STATUS_ETIMEOUT         (-2)
#define HAL_STATUS_EALLOC           (-3)
#define HAL_STATUS_EBUSY            (-4)
#define HAL_STATUS_EINVALID_PARAMS  (-5)
#define HAL_STATUS_UNKNOWN          (-6)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_COMMON_H__

