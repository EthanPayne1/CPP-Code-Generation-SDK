/**
 * @file debug.c
 * @brief Implementation of debug module
 * @author Test
 * @version 1.0.0
 * @date 2025-06-19
 */

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ========================================================================== */
/* Private Constants and Macros                                              */
/* ========================================================================== */

#define DEBUG_MAGIC_NUMBER (0x12345678)

#define DEBUG_ASSERT(condition) do { (void)(condition); } while(0)

#define DEBUG_CHECK_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            return DEBUG_ERROR_NULL_PTR; \
        } \
    } while(0)

/* ========================================================================== */
/* Private Type Definitions                                                  */
/* ========================================================================== */

/**
 * @brief Module state structure
 */
typedef struct {
    bool initialized;           /**< Initialization flag */
    uint32_t magic;            /**< Magic number for validation */
    size_t reference_count;    /**< Reference count */
} debug_state_t;

/* ========================================================================== */
/* Private Variables                                                         */
/* ========================================================================== */

static debug_state_t g_debug_state = {
    .initialized = false,
    .magic = DEBUG_MAGIC_NUMBER,
    .reference_count = 0
};

static const char* g_debug_error_strings[] = {
    [DEBUG_SUCCESS]        = "Success",
    [DEBUG_ERROR_NULL_PTR] = "Null pointer error",
    [DEBUG_ERROR_INVALID]  = "Invalid parameter",
    [DEBUG_ERROR_MEMORY]   = "Memory allocation error",
    [DEBUG_ERROR_IO]       = "I/O error",
    [DEBUG_ERROR_UNKNOWN]  = "Unknown error"
};

/* ========================================================================== */
/* Private Function Declarations                                             */
/* ========================================================================== */

/**
 * @brief Validate module state
 * @return true if valid, false otherwise
 */
static bool debug_validate_state(void);

/**
 * @brief Log error message
 * @param func Function name
 * @param error Error code
 */
static void debug_log_error(const char* func, debug_error_t error);

/* ========================================================================== */
/* Public Function Implementations                                           */
/* ========================================================================== */

const char* debug_error_string(debug_error_t error)
{
    if (error < 0 || error >= (sizeof(g_debug_error_strings) / sizeof(g_debug_error_strings[0]))) {
        return "Invalid error code";
    }
    return g_debug_error_strings[error];
}

debug_error_t debug_init(void)
{
    if (g_debug_state.initialized) {
        g_debug_state.reference_count++;
        return DEBUG_SUCCESS;
    }

    /* Initialize module state */
    g_debug_state.initialized = true;
    g_debug_state.reference_count = 1;

    /* Add module-specific initialization here */
    
    return DEBUG_SUCCESS;
}

debug_error_t debug_cleanup(void)
{
    if (!debug_validate_state()) {
        return DEBUG_ERROR_INVALID;
    }

    if (g_debug_state.reference_count > 1) {
        g_debug_state.reference_count--;
        return DEBUG_SUCCESS;
    }

    /* Add module-specific cleanup here */
    
    /* Reset module state */
    g_debug_state.initialized = false;
    g_debug_state.reference_count = 0;

    return DEBUG_SUCCESS;
}


/* ========================================================================== */
/* Private Function Implementations                                          */
/* ========================================================================== */

static bool debug_validate_state(void)
{
    return (g_debug_state.magic == DEBUG_MAGIC_NUMBER) &&
           g_debug_state.initialized;
}

static void debug_log_error(const char* func, debug_error_t error)
{
    fprintf(stderr, "[DEBUG_ERROR] %s: %s\n", 
            func ? func : "unknown", 
            debug_error_string(error));
}