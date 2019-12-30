 /*
 *******************************************************************************
 *
 * Copyright (C) 2019 Momenta Incorporated - http://www.momenta.cn/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef __HAL_ARCH_H__
#define __HAL_ARCH_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * hal_arch_init() - openvx sys app need to init when start.
 * @desc: hal arch file handler
 * @return: Success return 0, failure return <0.
 * @note: This interface must be called before other hal interfaces are called
 */
int hal_arch_init(int* desc);


/**
 * hal_arch_deinit() - openvx sys app need to deinit when start.
 * @desc: hal arch file handler
 * @return: Success return 0, failure return <0.
 */
int hal_arch_deinit(int desc);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __HAL_ARCH_H__
