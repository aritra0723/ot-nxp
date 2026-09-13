/*
 * Copyright 2026 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MCXW71_MBEDTLS_PSA_CONFIG_H
#define MCXW71_MBEDTLS_PSA_CONFIG_H

/*
 * PSA crypto configuration for MCXW71 (K32W1).
 *
 * This file is required because third_party/mbedtls/configs/ot-nxp-mbedtls-config.h
 * defines MBEDTLS_PSA_CRYPTO_CONFIG unconditionally, which makes mbedtls include
 * MBEDTLS_PSA_CRYPTO_CONFIG_FILE (set per platform in third_party/common_sdk and
 * third_party/mbedtls CMakeLists).
 *
 * Unlike MCXW72, MCXW71 has no ELE S2xx subsystem and third_party/mcxw71_sdk/prj.conf
 * enables no psa_crypto_driver backend, so no MBEDTLS_PSA_ACCEL_* flags are declared
 * here: PSA operations are served by the mbedtls software implementation.
 *
 * MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG is deliberately NOT defined. Instead this file follows
 * the same pattern as the other non-S2xx platforms (rw612, rt1060, rt1170): the mbedtls
 * entropy module stays in control of the RNG, satisfying the MBEDTLS_PSA_CRYPTO_C
 * prerequisite in mbedtls/check_config.h. MCXW71 has no platform entropy source, so
 * MBEDTLS_ENTROPY_HARDWARE_ALT routes entropy to mbedtls_hardware_poll(), which is
 * implemented by the SDK in middleware/mbedtls3x/port/rng/psa_mcux_entropy.c -- hence
 * CONFIG_MCUX_COMPONENT_middleware.mbedtls3x.port.rng in third_party/mcxw71_sdk/prj.conf.
 * src/mcxw/platform/entropy.c also calls it to back otPlatEntropyGet().
 *
 * Note that OpenThread itself uses OPENTHREAD_CONFIG_CRYPTO_LIB_MBEDTLS on MCXW71
 * (no OPENTHREAD_CONFIG_CRYPTO_LIB override in openthread-core-mcxw71-config.h), so
 * the PSA interface is only used internally by mbedtls via MBEDTLS_USE_PSA_CRYPTO.
 */

/* MBEDTLS_PSA_CRYPTO_C requires MBEDTLS_CTR_DRBG_C or MBEDTLS_HMAC_DRBG_C or
 * MBEDTLS_ENTROPY_C or MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG (mbedtls/check_config.h). */
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_ENTROPY_HARDWARE_ALT
/* OpenThread's mbedtls crypto backend (openthread/src/core/crypto/
 * crypto_platform_mbedtls.cpp) uses CTR_DRBG unconditionally. Only HMAC_DRBG is
 * enabled by the shared config, so enable CTR_DRBG here as rt1170 does. */
#define MBEDTLS_CTR_DRBG_C

#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PLATFORM_MEMORY

#endif /* MCXW71_MBEDTLS_PSA_CONFIG_H */
