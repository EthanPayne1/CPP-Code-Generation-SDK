/**
 * @file stream.h
 * @brief Stream processing and data transformation
 * @author Code Generator Team
 * @version 2.1.0
 * @date 2025-06-19
 * 
 * A modern C++ data processing library with stream processing and analysis capabilities
 * 
 * @license Apache-2.0
 */

#ifndef STREAM_
#define STREAM_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

#include <optional>
#include <string_view>

namespace dataproc {

/**
 * @defgroup stream Stream Module
 * @brief Stream processing and data transformation
 * @{
 */

/* ========================================================================== */
/* Constants and Macros                                                       */
/* ========================================================================== */

/**
 * @brief Default buffer size for stream operations
 */
constexpr size_t DEFAULT_BUFFER_SIZE = 8192;

/**
 * @brief Maximum number of parallel streams
 */
constexpr size_t MAX_PARALLEL_STREAMS = 16;


/* ========================================================================== */
/* Exception Classes                                                          */
/* ========================================================================== */

/**
 * @brief Base exception class for stream module
 */
class StreamException : public std::runtime_error {
public:
    explicit StreamException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Invalid argument exception
 */
class StreamInvalidArgumentException : public StreamException {
public:
    explicit StreamInvalidArgumentException(const std::string& message)
        : StreamException("Invalid argument: " + message) {}
};

/**
 * @brief Runtime error exception
 */
class StreamRuntimeException : public StreamException {
public:
    explicit StreamRuntimeException(const std::string& message)
        : StreamException("Runtime error: " + message) {}
};

/* ========================================================================== */
/* Type Definitions                                                           */
/* ========================================================================== */

/**
 * @brief Stream processing states
 */
enum class StreamState : uint8_t {
    Idle = 0,  ///< Stream is idle
    Processing = 1,  ///< Stream is actively processing
    Completed = 2,  ///< Stream processing completed
    Error = 3,  ///< Stream encountered an error
};

/**
 * @brief Convert StreamState to string
 * @param value Enum value
 * @return std::string String representation
 */
std::string to_string(StreamState value);

/**
 * @brief Data compression algorithms
 */
enum class CompressionType : int {
    None,  ///< No compression
    Lz4,  ///< LZ4 compression
    Zstd,  ///< Zstandard compression
    Gzip,  ///< GZIP compression
};

/**
 * @brief Convert CompressionType to string
 * @param value Enum value
 * @return std::string String representation
 */
std::string to_string(CompressionType value);


/**
 * @brief Configuration for stream processing
 */
struct StreamConfig {
    size_t buffer_size;  ///< Buffer size for stream operations
    size_t max_memory;  ///< Maximum memory usage
    uint32_t parallel_workers;  ///< Number of parallel workers
    CompressionType compression;  ///< Compression algorithm to use
    bool enable_checksum;  ///< Enable data integrity checksums

    /**
     * @brief Default constructor
     */
    StreamConfig() = default;

    /**
     * @brief Destructor
     */
    ~StreamConfig() = default;

    /**
     * @brief Copy constructor
     */
    StreamConfig(const StreamConfig&) = default;

    /**
     * @brief Copy assignment operator
     */
    StreamConfig& operator=(const StreamConfig&) = default;

    /**
     * @brief Move constructor
     */
    StreamConfig(StreamConfig&&) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    StreamConfig& operator=(StreamConfig&&) noexcept = default;

    /**
     * @brief Equality comparison operator
     */
    bool operator==(const StreamConfig& other) const noexcept;

    /**
     * @brief Inequality comparison operator
     */
    bool operator!=(const StreamConfig& other) const noexcept;
};

/**
 * @brief Stream processing statistics
 */
struct StreamStats {
    uint64_t bytes_processed;  ///< Total bytes processed
    uint64_t processing_time_ms;  ///< Processing time in milliseconds
    double throughput_mbps;  ///< Throughput in MB/s
    uint32_t error_count;  ///< Number of errors encountered

    /**
     * @brief Default constructor
     */
    StreamStats() = default;

    /**
     * @brief Destructor
     */
    ~StreamStats() = default;

    /**
     * @brief Copy constructor
     */
    StreamStats(const StreamStats&) = default;

    /**
     * @brief Copy assignment operator
     */
    StreamStats& operator=(const StreamStats&) = default;

    /**
     * @brief Move constructor
     */
    StreamStats(StreamStats&&) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    StreamStats& operator=(StreamStats&&) noexcept = default;

    /**
     * @brief Equality comparison operator
     */
    bool operator==(const StreamStats& other) const noexcept;

    /**
     * @brief Inequality comparison operator
     */
    bool operator!=(const StreamStats& other) const noexcept;
};


/* ========================================================================== */
/* Class Declarations                                                         */
/* ========================================================================== */

/**
 * @brief Stream class
 * 
 * Stream processing and data transformation
 * 
 * This class provides a RAII wrapper around the stream functionality.
 * It ensures proper initialization and cleanup, and provides a type-safe
 * interface to the underlying functionality.
 * 
 * Example usage:
 * @code
 * try {
 *     Stream instance;
 *     // Use instance...
 * } catch (const StreamException& e) {
 *     std::cerr << "Error: " << e.what() << std::endl;
 * }
 * @endcode
 */
class Stream {
public:
    /**
     * @brief Default constructor
     * @throws StreamException on initialization failure
     */
    Stream();

    /**
     * @brief Destructor
     */
    ~Stream();

    /**
     * @brief Copy constructor (deleted for resource safety)
     */
    Stream(const Stream&) = delete;

    /**
     * @brief Copy assignment operator (deleted for resource safety)
     */
    Stream& operator=(const Stream&) = delete;

    /**
     * @brief Move constructor
     */
    Stream(Stream&& other) noexcept;

    /**
     * @brief Move assignment operator
     */
    Stream& operator=(Stream&& other) noexcept;

    /**
     * @brief Create a new data stream processor
     * 
     * @param config Stream configuration
     * @return std::unique_ptr<StreamProcessor> Function result
     * @throws StreamException on error
     * 
     * Example usage:
     * @code
     * Stream instance;
     * auto result = instance.create_stream(config);
     * @endcode
     */
std::unique_ptr<StreamProcessor> create_stream(
const StreamConfig config    ) const;

    /**
     * @brief Process data through the stream
     * 
     * @param input Input data to process
     * @param output Output processed data
     * @return void Function result
     * @throws StreamException on error
     * 
     * Example usage:
     * @code
     * Stream instance;
     * auto result = instance.process_data(input, output);
     * @endcode
     */
void process_data(
std::span<const uint8_t> input,std::vector<uint8_t>& output    ) const;

    /**
     * @brief Get stream processing statistics
     * 
     * @return StreamStats Function result
     * @throws StreamException on error
     * 
     * Example usage:
     * @code
     * Stream instance;
     * auto result = instance.get_statistics();
     * @endcode
     */
StreamStats get_statistics(
    ) const;

    /**
     * @brief Reset stream processor state
     * 
     * @return void Function result
     * @throws StreamException on error
     * 
     * Example usage:
     * @code
     * Stream instance;
     * auto result = instance.reset();
     * @endcode
     */
void reset(
    ) const;


    /**
     * @brief Check if the instance is valid
     * @return bool True if valid, false otherwise
     */
    bool is_valid() const noexcept;

    /**
     * @brief Get the last error message
     * @return std::string Error message
     */
    std::string get_last_error() const;

private:
    struct Impl;  ///< Forward declaration for PIMPL idiom
    std::unique_ptr<Impl> pimpl_;  ///< Private implementation pointer
};

/* ========================================================================== */
/* Free Function Declarations                                                */
/* ========================================================================== */

/**
 * @brief Get library version
 * @return std::string Version string
 */
std::string get_version();

/**
 * @brief Get library build information
 * @return std::string Build information
 */
std::string get_build_info();

/**
 * @}
 */

} // namespace dataproc

#endif /* STREAM_ */