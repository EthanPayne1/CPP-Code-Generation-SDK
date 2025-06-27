/**
 * @file analyzer.h
 * @brief Data analysis and pattern detection
 * @author Code Generator Team
 * @version 2.1.0
 * @date 2025-06-19
 * 
 * A modern C++ data processing library with stream processing and analysis capabilities
 * 
 * @license Apache-2.0
 */

#ifndef ANALYZER_
#define ANALYZER_

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
 * @defgroup analyzer Analyzer Module
 * @brief Data analysis and pattern detection
 * @{
 */

/* ========================================================================== */
/* Constants and Macros                                                       */
/* ========================================================================== */


/* ========================================================================== */
/* Exception Classes                                                          */
/* ========================================================================== */

/**
 * @brief Base exception class for analyzer module
 */
class AnalyzerException : public std::runtime_error {
public:
    explicit AnalyzerException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Invalid argument exception
 */
class AnalyzerInvalidArgumentException : public AnalyzerException {
public:
    explicit AnalyzerInvalidArgumentException(const std::string& message)
        : AnalyzerException("Invalid argument: " + message) {}
};

/**
 * @brief Runtime error exception
 */
class AnalyzerRuntimeException : public AnalyzerException {
public:
    explicit AnalyzerRuntimeException(const std::string& message)
        : AnalyzerException("Runtime error: " + message) {}
};

/* ========================================================================== */
/* Type Definitions                                                           */
/* ========================================================================== */

/**
 * @brief Types of patterns to detect
 */
enum class PatternType : int {
    Periodic,  ///< Periodic patterns
    Trending,  ///< Trending patterns
    Anomaly,  ///< Anomalous patterns
    Cluster,  ///< Cluster patterns
};

/**
 * @brief Convert PatternType to string
 * @param value Enum value
 * @return std::string String representation
 */
std::string to_string(PatternType value);


/**
 * @brief Result of data analysis
 */
struct AnalysisResult {
    bool pattern_found;  ///< Whether a pattern was detected
    double confidence;  ///< Confidence level (0.0 to 1.0)
    PatternType pattern_type;  ///< Type of detected pattern
    std::unordered_map<std::string, std::string> metadata;  ///< Additional pattern metadata

    /**
     * @brief Default constructor
     */
    AnalysisResult() = default;

    /**
     * @brief Destructor
     */
    ~AnalysisResult() = default;

    /**
     * @brief Copy constructor
     */
    AnalysisResult(const AnalysisResult&) = default;

    /**
     * @brief Copy assignment operator
     */
    AnalysisResult& operator=(const AnalysisResult&) = default;

    /**
     * @brief Move constructor
     */
    AnalysisResult(AnalysisResult&&) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    AnalysisResult& operator=(AnalysisResult&&) noexcept = default;

    /**
     * @brief Equality comparison operator
     */
    bool operator==(const AnalysisResult& other) const noexcept;

    /**
     * @brief Inequality comparison operator
     */
    bool operator!=(const AnalysisResult& other) const noexcept;
};


/* ========================================================================== */
/* Class Declarations                                                         */
/* ========================================================================== */

/**
 * @brief Analyzer class
 * 
 * Data analysis and pattern detection
 * 
 * This class provides a RAII wrapper around the analyzer functionality.
 * It ensures proper initialization and cleanup, and provides a type-safe
 * interface to the underlying functionality.
 * 
 * Example usage:
 * @code
 * try {
 *     Analyzer instance;
 *     // Use instance...
 * } catch (const AnalyzerException& e) {
 *     std::cerr << "Error: " << e.what() << std::endl;
 * }
 * @endcode
 */
class Analyzer {
public:
    /**
     * @brief Default constructor
     * @throws AnalyzerException on initialization failure
     */
    Analyzer();

    /**
     * @brief Destructor
     */
    ~Analyzer();

    /**
     * @brief Copy constructor (deleted for resource safety)
     */
    Analyzer(const Analyzer&) = delete;

    /**
     * @brief Copy assignment operator (deleted for resource safety)
     */
    Analyzer& operator=(const Analyzer&) = delete;

    /**
     * @brief Move constructor
     */
    Analyzer(Analyzer&& other) noexcept;

    /**
     * @brief Move assignment operator
     */
    Analyzer& operator=(Analyzer&& other) noexcept;

    /**
     * @brief Analyze time series data for patterns
     * 
     * @param data Time series data points
     * @param timestamps Corresponding timestamps
     * @param pattern_types Pattern types to search for
     * @return AnalysisResult Function result
     * @throws AnalyzerException on error
     * 
     * Example usage:
     * @code
     * Analyzer instance;
     * auto result = instance.analyze_time_series(data, timestamps, pattern_types);
     * @endcode
     */
AnalysisResult analyze_time_series(
const std::vector<double> data,const std::vector<uint64_t> timestamps,const std::vector<PatternType> pattern_types    ) const;

    /**
     * @brief Detect anomalies in data stream
     * 
     * @param data Input data stream
     * @param sensitivity Anomaly detection sensitivity
     * @return std::vector<size_t> Function result
     * @throws AnalyzerException on error
     * 
     * Example usage:
     * @code
     * Analyzer instance;
     * auto result = instance.detect_anomalies(data, sensitivity);
     * @endcode
     */
std::vector<size_t> detect_anomalies(
const std::vector<double> data,double sensitivity = 0.95    ) const;

    /**
     * @brief Compute correlation matrix for multivariate data
     * 
     * @param data Multivariate data (each inner vector is a variable)
     * @return std::vector<std::vector<double>> Function result
     * @throws AnalyzerException on error
     * 
     * Example usage:
     * @code
     * Analyzer instance;
     * auto result = instance.compute_correlation_matrix(data);
     * @endcode
     */
std::vector<std::vector<double>> compute_correlation_matrix(
const std::vector<std::vector<double>> data    ) const;


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

#endif /* ANALYZER_ */