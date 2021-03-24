
  #ifndef quantlib_black_scholes_process_hpp
 #define quantlib_black_scholes_process_hpp
  
 #include <ql/stochasticprocess.hpp>
 #include <ql/processes/eulerdiscretization.hpp>
 #include <ql/termstructures/yieldtermstructure.hpp>
 #include <ql/termstructures/volatility/equityfx/blackvoltermstructure.hpp>
 #include <ql/termstructures/volatility/equityfx/localvoltermstructure.hpp>
 #include <ql/quote.hpp>
  
 namespace QuantLib {
  
     class LocalConstantVol;
     class LocalVolCurve;
  
  
     class GeneralizedBlackScholesProcess : public StochasticProcess1D {
       public:
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
  
  
     class BlackScholesProcess : public GeneralizedBlackScholesProcess {
       public:
         BlackScholesProcess(
             const Handle<Quote>& x0,
             const Handle<YieldTermStructure>& riskFreeTS,
             const Handle<BlackVolTermStructure>& blackVolTS,
             const ext::shared_ptr<discretization>& d =
                   ext::shared_ptr<discretization>(new EulerDiscretization),
             bool forceDiscretization = false);
     };
  
  
     class BlackScholesMertonProcess : public GeneralizedBlackScholesProcess {
       public:
         BlackScholesMertonProcess(
             const Handle<Quote>& x0,
             const Handle<YieldTermStructure>& dividendTS,
             const Handle<YieldTermStructure>& riskFreeTS,
             const Handle<BlackVolTermStructure>& blackVolTS,
             const ext::shared_ptr<discretization>& d =
                   ext::shared_ptr<discretization>(new EulerDiscretization),
             bool forceDiscretization = false);
     };
  
  
     class BlackProcess : public GeneralizedBlackScholesProcess {
       public:
         BlackProcess(
             const Handle<Quote>& x0,
             const Handle<YieldTermStructure>& riskFreeTS,
             const Handle<BlackVolTermStructure>& blackVolTS,
             const ext::shared_ptr<discretization>& d =
                   ext::shared_ptr<discretization>(new EulerDiscretization),
             bool forceDiscretization = false);
     };
  
  
     class GarmanKohlagenProcess : public GeneralizedBlackScholesProcess {
       public:
         GarmanKohlagenProcess(
             const Handle<Quote>& x0,
             const Handle<YieldTermStructure>& foreignRiskFreeTS,
             const Handle<YieldTermStructure>& domesticRiskFreeTS,
             const Handle<BlackVolTermStructure>& blackVolTS,
             const ext::shared_ptr<discretization>& d =
                   ext::shared_ptr<discretization>(new EulerDiscretization),
             bool forceDiscretization = false);
     };
  
 }
  
  
 #endif
