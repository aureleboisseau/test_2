
#include <ql/stochasticprocess.hpp>

namespace QuantLib {

    class ConstantBlackScholesProcess : public StochasticProcess1D {

        GeneralizedBlackScholesProcess(Handle<Quote> x0,
                                        Handle<YieldTermStructure> dividendTS,
                                        Handle<YieldTermStructure> riskFreeTS,
                                        Handle<BlackVolTermStructure> blackVolTS,
                                        const ext::shared_ptr<discretization>& d =
                                            ext::shared_ptr<discretization>(new EulerDiscretization),
                                        bool forceDiscretization = false);
  
         GeneralizedBlackScholesProcess(Handle<Quote> x0,
                                        Handle<YieldTermStructure> dividendTS,
                                        Handle<YieldTermStructure> riskFreeTS,
                                        Handle<BlackVolTermStructure> blackVolTS,
                                        Handle<LocalVolTermStructure> localVolTS);
  
  
         Real x0() const override;
         Real drift(Time t, Real x) const override;
         Real diffusion(Time t, Real x) const override;
         Real apply(Real x0, Real dx) const override;
         Real expectation(Time t0, Real x0, Time dt) const override;
         Real stdDeviation(Time t0, Real x0, Time dt) const override;
         Real variance(Time t0, Real x0, Time dt) const override;
         Real evolve(Time t0, Real x0, Time dt, Real dw) const override;
         Time time(const Date&) const override;
  
         void update() override;
  
         const Handle<Quote>& stateVariable() const;
         const Handle<YieldTermStructure>& dividendYield() const;
         const Handle<YieldTermStructure>& riskFreeRate() const;
         const Handle<BlackVolTermStructure>& blackVolatility() const;
         const Handle<LocalVolTermStructure>& localVolatility() const;
       private:
         Handle<Quote> x0_;
         Handle<YieldTermStructure> riskFreeRate_, dividendYield_;
         Handle<BlackVolTermStructure> blackVolatility_;
         Handle<LocalVolTermStructure> externalLocalVolTS_;
         bool forceDiscretization_;
         bool hasExternalLocalVol_;
         mutable RelinkableHandle<LocalVolTermStructure> localVolatility_;
         mutable bool updated_, isStrikeIndependent_;
  
        
    };

}

