
#include <ql/stochasticprocess.hpp>

namespace QuantLib {

   class GeneralizedBlackScholesProcess
        : public StochasticProcess1D {
      public:
        GeneralizedBlackScholesProcess(
            const Handle<Quote>& x0,
            const Handle<YieldTermStructure>& dividendTS,
            const Handle<YieldTermStructure>& riskFreeRate,
            const Handle<BlackVolTermStructure>& blackVolTS,
            const boost::shared_ptr<discretization>& d =
                                boost::shared_ptr<discretization>());
        Real x0() const {
            return x0_->value();
        }
        Real drift(Time t, Real x) const {
            Real sigma = diffusion(t,x);
            Time t1 = t + 0.0001;
            return riskFreeRate_->forwardRate(t,t1,Continuous,...)
                 - dividendYield_->forwardRate(t,t1,Continuous,...)
                 - 0.5 * sigma * sigma;
        }
        Real diffusion(Time t, Real x) const;
        Real apply(Real x0, Real dx) const {
            return x0 * std::exp(dx);
        }
        Real expectation(Time t0, Real x0, Time dt) const {
            QL_FAIL("not implemented");
        }
        Real evolve(Time t0, Real x0, Time dt, Real dw) const {
            return apply(x0, discretization_->drift(*this,t0,x0,dt) +
                             stdDeviation(t0,x0,dt)*dw);
        }
        const Handle<Quote>& stateVariable() const;
        const Handle<YieldTermStructure>& dividendYield() const;
        const Handle<YieldTermStructure>& riskFreeRate() const;
        const Handle<BlackVolTermStructure>& blackVolatility() const;
        const Handle<LocalVolTermStructure>& localVolatility() const;
    };
}

