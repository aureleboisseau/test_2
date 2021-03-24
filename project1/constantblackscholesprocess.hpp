  
 #ifndef quantlib_blackscholescalculator_hpp
 #define quantlib_blackscholescalculator_hpp
  
 #include <ql/pricingengines/blackcalculator.hpp>
  
 namespace QuantLib {
  
     class BlackScholesCalculator : public BlackCalculator {
       public:
         BlackScholesCalculator(
                         const ext::shared_ptr<StrikedTypePayoff>& payoff,
                         Real spot,
                         DiscountFactor growth,
                         Real stdDev,
                         DiscountFactor discount);
         BlackScholesCalculator(Option::Type optionType,
                                Real strike,
                                Real spot,
                                DiscountFactor growth,
                                Real stdDev,
                                DiscountFactor discount);
         ~BlackScholesCalculator() override = default;
         Real delta() const;
         Real elasticity() const;
         Real gamma() const;
         Real theta(Time maturity) const;
         Real thetaPerDay(Time maturity) const;
         // also un-hide overloads taking a spot
         using BlackCalculator::delta;
         using BlackCalculator::elasticity;
         using BlackCalculator::gamma;
         using BlackCalculator::theta;
         using BlackCalculator::thetaPerDay;
       protected:
         Real spot_;
         DiscountFactor growth_;
     };
  
     // inline
     inline Real BlackScholesCalculator::delta() const {
         return BlackCalculator::delta(spot_);
     }
  
     inline Real BlackScholesCalculator::elasticity() const {
         return BlackCalculator::elasticity(spot_);
     }
  
     inline Real BlackScholesCalculator::gamma() const {
         return BlackCalculator::gamma(spot_);
     }
  
     inline Real BlackScholesCalculator::theta(Time maturity) const {
         return BlackCalculator::theta(spot_, maturity);
     }
  
     inline Real BlackScholesCalculator::thetaPerDay(Time maturity) const {
         return BlackCalculator::thetaPerDay(spot_, maturity);
     }
  
 }
  
 #endif
