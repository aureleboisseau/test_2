
 #ifndef quantlib_black_scholes_process_hpp2
 #define quantlib_black_scholes_process_hpp2
  
 #include <ql/stochasticprocess.hpp>
 #include <ql/processes/eulerdiscretization.hpp>
 #include <ql/termstructures/yieldtermstructure.hpp>
 #include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
 #include <ql/termstructures/volatility/equityfx/localvoltermstructure.hpp>
 #include <ql/quote.hpp>
  
 namespace QuantLib {
  
     class LocalConstantVol;
    
  
  
     class GeneralizedBlackScholesProcess2 : public StochasticProcess1D {
       public:
         GeneralizedBlackScholesProcess2(const Real x0,
                                         const Real dividendTS,
                                         const Real riskFreeTS,
                                         const Real blackVolTS,
                                         const ext::shared_ptr<discretization>& d =
                                             ext::shared_ptr<discretization>(new EulerDiscretization),
                                         bool forceDiscretization = false);
  
         GeneralizedBlackScholesProcess2(const Real x0,
                                        const Real dividendTS,
                                        const Real riskFreeTS,
                                        const Real blackVolTS,
                                       const Real localVolTS);
  
  
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
  
  
     class BlackScholesProcess2 : public GeneralizedBlackScholesProcess2 {
       public:
         BlackScholesProcess2(
             const Real x0,
             const Real riskFreeTS,
             const Real blackVolTS,
             const ext::shared_ptr<discretization>& d =
                   ext::shared_ptr<discretization>(new EulerDiscretization),
             bool forceDiscretization = false);
     };
  

  
 }
  
  
 #endif
