#include <array>
#include <initializer_list>

/**
 * @brief Perform operations on polynomials of arbitrary degree
 * 
 * @tparam N Length of coefficient array (degree + 1)
 */
template <std::size_t N>
class Polynomial
{
    static_assert(N > 0, "Coefficient array cannot be empty");

public:
    using ValueType = double;
    using CoeffsType = std::array<ValueType, N>;

    constexpr Polynomial(CoeffsType coeffs) : coeffs_{coeffs} {}

    template <typename... Ts>
    constexpr Polynomial(Ts... coeffs) : coeffs_{coeffs...} {}

    // constexpr Polynomial(std::initializer_list<ValueType> coeffs)
    // {
    //     /// TODO: Assert initializer_list size as static_assert won't work here
    //     static_assert(coeffs.size() == N, "Initializer list length doesn't match N");

    //     std::copy(coeffs.begin(), coeffs.end(), coeffs_.begin());
    // }

    constexpr ValueType evaluate(ValueType x) const noexcept
    {
        return evaluateImpl<N - 1>(x);
    }

    constexpr CoeffsType getCoeffs() const noexcept
    {
        return coeffs_;
    }

private:
    /**
     * @brief Use recursive Horner's method to evaluate polynomial at compile time
     * 
     * @tparam i Coefficient index at current recursion depth
     * @param  x Value at which the polynomial is evaluated
     * @return constexpr ValueType 
     */
    template <std::size_t i>
    constexpr ValueType evaluateImpl([[maybe_unused]] ValueType x) const noexcept
    {
        if constexpr (i == 0U)
        {
            // Warning "parameter 'x' set but not used" in this branch is suppressed by using [[maybe_unused]] above
            return coeffs_[i];
        }
        else
        {
            return evaluateImpl<i - 1>(x) * x + coeffs_[i];
        }
    }

    /**
     * @brief Array holding the polynomial coefficients in decreasing-degree order
     * 
     */
    CoeffsType coeffs_;
};
