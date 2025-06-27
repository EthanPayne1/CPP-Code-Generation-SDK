/**
 * @file vector.h
 * @brief Vector operations and linear algebra functions
 * @author Code Generator
 * @version 1.0.0
 * @date 2025-06-19
 * 
 * A mathematical computation library with vector operations and statistical functions
 * 
 * @license MIT
 */

#ifndef VECTOR_
#define VECTOR_

#ifdef __cplusplus
extern "C" {
#endif

/* Standard library includes */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

/**
 * @defgroup vector Vector Module
 * @brief Vector operations and linear algebra functions
 * @{
 */

/* ========================================================================== */
/* Constants and Macros                                                       */
/* ========================================================================== */

/**
 * @brief Maximum vector size
 */
#define VECTOR_MAX_SIZE (1024)

/**
 * @brief Default floating point tolerance
 */
#define VECTOR_DEFAULT_TOLERANCE (1e-9)


/* Error codes */
typedef enum {
    VECTOR_SUCCESS = 0,     /**< Operation successful */
    VECTOR_ERROR_NULL_PTR,  /**< Null pointer error */
    VECTOR_ERROR_INVALID,   /**< Invalid parameter */
    VECTOR_ERROR_MEMORY,    /**< Memory allocation error */
    VECTOR_ERROR_IO,        /**< I/O error */
    VECTOR_ERROR_UNKNOWN    /**< Unknown error */
} vector_error_t;

/* ========================================================================== */
/* Type Definitions                                                           */
/* ========================================================================== */

/**
 * @brief Vector norm types
 */
typedef enum {
    VECTOR_NORM_L1,  /**< L1 norm (Manhattan distance) */
    VECTOR_NORM_L2,  /**< L2 norm (Euclidean distance) */
    VECTOR_NORM_INF,  /**< Infinity norm (maximum element) */
} vector_norm_t;


/**
 * @brief Dynamic vector structure
 */
typedef struct vector_s {
    double* data;  /**< Vector data array */
    size_t size;  /**< Number of elements */
    size_t capacity;  /**< Allocated capacity */
} vector_t;


/* ========================================================================== */
/* Function Declarations                                                      */
/* ========================================================================== */

/**
 * @brief Create a new vector with specified size
 * 
 * @param size Initial vector size
 * @param vec Output vector pointer
 * @return vector_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * vector_error_t result = vector_create(size, vec);
 * if (result != VECTOR_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
vector_error_t vector_create(
size_t size,vector_t** vec);

/**
 * @brief Destroy a vector and free its memory
 * 
 * @param vec Vector to destroy
 * @return vector_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * vector_error_t result = vector_destroy(vec);
 * if (result != VECTOR_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
vector_error_t vector_destroy(
vector_t** vec);

/**
 * @brief Add two vectors element-wise
 * 
 * @param a First vector
 * @param b Second vector
 * @param result Result vector
 * @return vector_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * vector_error_t result = vector_add(a, b, result);
 * if (result != VECTOR_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
vector_error_t vector_add(
const vector_t** a,const vector_t** b,vector_t** result);

/**
 * @brief Calculate dot product of two vectors
 * 
 * @param a First vector
 * @param b Second vector
 * @param result Output dot product
 * @return vector_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * vector_error_t result = vector_dot_product(a, b, result);
 * if (result != VECTOR_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
vector_error_t vector_dot_product(
const vector_t** a,const vector_t** b,double** result);

/**
 * @brief Calculate vector norm
 * 
 * @param vec Input vector
 * @param norm_type Type of norm to calculate
 * @param result Output norm value
 * @return vector_error_t Error code or result
 * 
 * @note This function is not guaranteed to be thread-safe
 * 
 * Example usage:
 * @code
 * vector_error_t result = vector_norm(vec, norm_type, result);
 * if (result != VECTOR_SUCCESS) {
 *     // Handle error
 * }
 * @endcode
 */
vector_error_t vector_norm(
const vector_t** vec,vector_norm_t norm_type,double** result);


/**
 * @brief Get error message string
 * @param error Error code
 * @return const char* Error message string
 */
const char* vector_error_string(vector_error_t error);

/**
 * @brief Initialize vector module
 * @return vector_error_t Error code
 */
vector_error_t vector_init(void);

/**
 * @brief Cleanup vector module
 * @return vector_error_t Error code
 */
vector_error_t vector_cleanup(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* VECTOR_ */