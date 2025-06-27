/**
 * @file core.h
 * @brief Core module
 * @author Test Author
 * @version 1.0.0
 * @date 2025-06-19
 * 
 * Test library
 * 
 */

#ifndef CORE_
#define CORE_

#ifdef __cplusplus
extern "C" {
#endif

/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * @defgroup core Core Module
 * @brief Core module
 * @{
 */

/* ========================================================================== */
/* Constants and Macros                                                       */
/* ========================================================================== */


/* Error codes */
typedef enum {
    CORE_SUCCESS = 0,     /**< Operation successful */
    CORE_ERROR_NULL_PTR,  /**< Null pointer error */
    CORE_ERROR_INVALID,   /**< Invalid parameter */
    CORE_ERROR_MEMORY,    /**< Memory allocation error */
    CORE_ERROR_IO,        /**< I/O error */
    CORE_ERROR_UNKNOWN    /**< Unknown error */
} core_error_t;

/* ========================================================================== */
/* Type Definitions                                                           */
/* ========================================================================== */



/* ========================================================================== */
/* Function Declarations                                                      */
/* ========================================================================== */

/**
 * @brief Test function
 * 
 * @param value Input value
 * @return int Function result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * int result = test_func(value);
 * if (result != CORE_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
int test_func(
int value);


/**
 * @brief Get error message string
 * @param error Error code
 * @return const char* Error message string
 */
const char* core_error_string(core_error_t error);

/**
 * @brief Initialize core module
 * @return core_error_t Error code
 */
core_error_t core_init(void);

/**
 * @brief Cleanup core module
 * @return core_error_t Error code
 */
core_error_t core_cleanup(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* CORE_ */