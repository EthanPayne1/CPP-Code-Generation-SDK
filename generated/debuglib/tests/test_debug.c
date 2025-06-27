/**
 * @file test_debug.c
 * @brief Unit tests for debug module using Unity framework
 * @author Test
 * @version 1.0.0
 * @date 2025-06-19
 */

#include "unity.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================== */
/* Test Setup and Teardown                                                   */
/* ========================================================================== */

void setUp(void)
{
    /* This function is called before each test */
    debug_error_t result = debug_init();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result);
}

void tearDown(void)
{
    /* This function is called after each test */
    debug_error_t result = debug_cleanup();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result);
}

/* ========================================================================== */
/* Basic Functionality Tests                                                 */
/* ========================================================================== */

void test_debug_init_success(void)
{
    /* Test that initialization succeeds */
    debug_error_t result = debug_cleanup(); // Clean up from setUp
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result);
    
    result = debug_init();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result);
}

void test_debug_init_multiple_calls(void)
{
    /* Test that multiple init calls are handled correctly */
    debug_error_t result1 = debug_init();
    debug_error_t result2 = debug_init();
    
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result1);
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result2);
    
    /* Cleanup extra references */
    debug_cleanup();
    debug_cleanup();
}

void test_debug_cleanup_success(void)
{
    /* Test that cleanup succeeds */
    debug_error_t result = debug_cleanup();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result);
    
    /* Re-initialize for tearDown */
    result = debug_init();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result);
}

void test_debug_error_string(void)
{
    /* Test error string conversion */
    const char* success_str = debug_error_string(DEBUG_SUCCESS);
    const char* null_str = debug_error_string(DEBUG_ERROR_NULL_PTR);
    const char* invalid_str = debug_error_string(DEBUG_ERROR_INVALID);
    
    TEST_ASSERT_NOT_NULL(success_str);
    TEST_ASSERT_NOT_NULL(null_str);
    TEST_ASSERT_NOT_NULL(invalid_str);
    
    TEST_ASSERT_TRUE(strlen(success_str) > 0);
    TEST_ASSERT_TRUE(strlen(null_str) > 0);
    TEST_ASSERT_TRUE(strlen(invalid_str) > 0);
}

void test_debug_error_string_invalid_code(void)
{
    /* Test error string with invalid error code */
    const char* invalid_str = debug_error_string(-1);
    TEST_ASSERT_NOT_NULL(invalid_str);
    TEST_ASSERT_TRUE(strlen(invalid_str) > 0);
}

/* ========================================================================== */
/* Function-Specific Tests                                                   */
/* ========================================================================== */


/* ========================================================================== */
/* Edge Case Tests                                                           */
/* ========================================================================== */

void test_debug_double_cleanup(void)
{
    /* Test that double cleanup is handled gracefully */
    debug_error_t result1 = debug_cleanup();
    debug_error_t result2 = debug_cleanup();
    
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, result1);
    /* Second cleanup might return error or success depending on implementation */
    
    /* Re-initialize for tearDown */
    debug_error_t init_result = debug_init();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, init_result);
}

/* ========================================================================== */
/* Performance Tests                                                         */
/* ========================================================================== */

void test_debug_performance_init_cleanup(void)
{
    /* Test performance of multiple init/cleanup cycles */
    const int cycles = 1000;
    
    for (int i = 0; i < cycles; i++) {
        debug_error_t init_result = debug_init();
        TEST_ASSERT_EQUAL(DEBUG_SUCCESS, init_result);
        
        debug_error_t cleanup_result = debug_cleanup();
        TEST_ASSERT_EQUAL(DEBUG_SUCCESS, cleanup_result);
    }
    
    /* Re-initialize for tearDown */
    debug_error_t final_init = debug_init();
    TEST_ASSERT_EQUAL(DEBUG_SUCCESS, final_init);
}

/* ========================================================================== */
/* Main Test Runner                                                          */
/* ========================================================================== */

int main(void)
{
    UNITY_BEGIN();
    
    /* Basic functionality tests */
    RUN_TEST(test_debug_init_success);
    RUN_TEST(test_debug_init_multiple_calls);
    RUN_TEST(test_debug_cleanup_success);
    RUN_TEST(test_debug_error_string);
    RUN_TEST(test_debug_error_string_invalid_code);
    
    /* Function-specific tests */
    
    /* Edge case tests */
    RUN_TEST(test_debug_double_cleanup);
    
    /* Performance tests */
    RUN_TEST(test_debug_performance_init_cleanup);
    
    return UNITY_END();
}