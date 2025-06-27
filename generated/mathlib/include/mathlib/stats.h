/**
 * @file stats.h
 * @brief Statistical analysis functions
 * @author Code Generator
 * @version 1.0.0
 * @date 2025-06-19
 * 
 * A mathematical computation library with vector operations and statistical functions
 * 
 * @license MIT
 */

#ifndef STATS_
#define STATS_

#ifdef __cplusplus
extern "C" {
#endif

/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

/**
 * @defgroup stats Stats Module
 * @brief Statistical analysis functions
 * @{
 */

/* ========================================================================== */
/* Constants and Macros                                                       */
/* ========================================================================== */


/* Error codes */
typedef enum {
    STATS_SUCCESS = 0,     /**< Operation successful */
    STATS_ERROR_NULL_PTR,  /**< Null pointer error */
    STATS_ERROR_INVALID,   /**< Invalid parameter */
    STATS_ERROR_MEMORY,    /**< Memory allocation error */
    STATS_ERROR_IO,        /**< I/O error */
    STATS_ERROR_UNKNOWN    /**< Unknown error */
} stats_error_t;

/* ========================================================================== */
/* Type Definitions                                                           */
/* ========================================================================== */



/* ========================================================================== */
/* Function Declarations                                                      */
/* ========================================================================== */

/**
 * @brief Calculate arithmetic mean of array
 * 
 * @param data Input data array
 * @param size Array size
 * @param result Output mean value
 * @return stats_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * stats_error_t result = stats_mean(data, size, result);
 * if (result != STATS_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
stats_error_t stats_mean(
const double** data,size_t size,double** result);

/**
 * @brief Calculate variance of array
 * 
 * @param data Input data array
 * @param size Array size
 * @param result Output variance value
 * @return stats_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * stats_error_t result = stats_variance(data, size, result);
 * if (result != STATS_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
stats_error_t stats_variance(
const double** data,size_t size,double** result);

/**
 * @brief Calculate correlation coefficient between two arrays
 * 
 * @param x First data array
 * @param y Second data array
 * @param size Array size
 * @param result Output correlation coefficient
 * @return stats_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * stats_error_t result = stats_correlation(x, y, size, result);
 * if (result != STATS_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
stats_error_t stats_correlation(
const double** x,const double** y,size_t size,double** result);


/**
 * @brief Get error message string
 * @param error Error code
 * @return const char* Error message string
 */
const char* stats_error_string(stats_error_t error);

/**
 * @brief Initialize stats module
 * @return stats_error_t Error code
 */
stats_error_t stats_init(void);

/**
 * @brief Cleanup stats module
 * @return stats_error_t Error code
 */
stats_error_t stats_cleanup(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* STATS_ */