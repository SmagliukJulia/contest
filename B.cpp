struct RealFunction {
    virtual double operator()(unsigned idx) const = 0;
};
double derivative(unsigned, RealFunction const &);
class DerivativeFunction final : public RealFunction {
public:
    const RealFunction &f;
    DerivativeFunction(RealFunction const &f): RealFunction(), f(f) { };

    double operator()(unsigned idx) const {
        return derivative(idx, f);
    }
};
