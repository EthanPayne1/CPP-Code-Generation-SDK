/**
 * @file debug.h
 * @brief Debug module
 * @author Test
 * @version 1.0.0
 * @date 2025-06-19
 * 
 * Debug library
 * 
 */

#ifndef DEBUG_
#define DEBUG_

#ifdef __cplusplus
extern "C" {
#endif

/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * @defgroup debug Debug Module
 * @brief Debug module
 * @{
 */

/* ========================================================================== */
/* Constants and Macros                                                       */
/* ========================================================================== */

/**
 * @brief Max debug value
 */
#define DEBUG_MAX (100)


/* Error codes */
typedef enum {
    DEBUG_SUCCESS = 0,     /**< Operation successful */
    DEBUG_ERROR_NULL_PTR,  /**< Null pointer error */
    DEBUG_ERROR_INVALID,   /**< Invalid parameter */
    DEBUG_ERROR_MEMORY,    /**< Memory allocation error */
    DEBUG_ERROR_IO,        /**< I/O error */
    DEBUG_ERROR_UNKNOWN    /**< Unknown error */
} debug_error_t;

/* ========================================================================== */
/* Type Definitions                                                           */
/* ========================================================================== */

/**
 * @brief Debug levels
 */
typedef enum {
    DEBUG_LEVEL_INFO,  /**< Info level */
    DEBUG_LEVEL_WARN,  /**< Warning level */
} debug_level_t;



/* ========================================================================== */
/* Function Declarations                                                      */
/* ========================================================================== */


/**
 * @brief Get error message string
 * @param error Error code
 * @return const char* Error message string
 */
const char* debug_error_string(debug_error_t error);

/**
 * @brief Initialize debug module
 * @return debug_error_t Error code
 */
debug_error_t debug_init(void);

/**
 * @brief Cleanup debug module
 * @return debug_error_t Error code
 */
debug_error_t debug_cleanup(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_ */