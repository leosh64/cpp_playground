#ifndef TIMEIT_H
#define TIMEIT_H

#include <chrono>
#include <utility>

namespace
{
auto get_timestamp() { return std::chrono::high_resolution_clock::now(); }

}  // namespace

/**
 * @brief Measure wall time of void function passed as argument
 *
 * @tparam Ratio Fraction of seconds to return runtime in (default: milliseconds, std::milli)
 * @tparam Fcn Type of the function to measure, will be inferred
 * @tparam Args Type of the arguments to pass, will be inferred
 * @param f Function to measure runtime
 * @param args Arguments to pass to the function, can be empty
 * @return double Measured wall time in fraction of a second (see Ratio template parameter)
 */
template <class Ratio = std::milli, class Fcn, class... Args,
          typename = typename std::enable_if<std::is_same<typename std::result_of<Fcn(Args...)>::type, void>::value,
                                             void>::type>
double timeit(Fcn f, Args&&... args)
{
    auto const start = get_timestamp();

    f(std::forward<Args>(args)...);

    auto const end = get_timestamp();

    return std::chrono::duration<double, Ratio>(end - start).count();
}

/**
 * @brief Measure wall time of returning function passed as argument
 *
 * Overload for non-void functions. See description of other implementation for details.
 *
 * @return std::pair<double, T> Pair of (runtime, return_value)
 */
template <class Ratio = std::milli, class Fcn, class... Args,
          typename = typename std::enable_if<!std::is_same<typename std::result_of<Fcn(Args...)>::type, void>::value,
                                             void>::type>
auto timeit(Fcn f, Args&&... args)
{
    auto const start = get_timestamp();

    auto const return_value = f(std::forward<Args>(args)...);

    auto const end = get_timestamp();
    auto const duration = std::chrono::duration<double, Ratio>(end - start).count();

    return std::make_pair(duration, return_value);
}

#endif  // TIMEIT_H
