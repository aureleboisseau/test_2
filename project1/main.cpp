#include <ql/qldefines.hpp>
#ifdef BOOST_MSVC
#  include <ql/auto_link.hpp>
#endif
#include "constantblackscholesprocess.hpp"
#include "mceuropeanengine.hpp"
#include <ql/instruments/vanillaoption.hpp>
#include <ql/instruments/payoffs.hpp>
#include <ql/exercise.hpp>
#include <ql/pricingengines/vanilla/mceuropeanengine.hpp>
#include <ql/termstructures/yield/zerocurve.hpp>
#include <ql/termstructures/volatility/equityfx/blackvariancecurve.hpp>
#include <ql/time/calendars/target.hpp>
#include <ql/utilities/dataformatters.hpp>
#include <iostream>
#include <chrono>

using namespace QuantLib;

int main() {

    try {

        // modify the sample code below to suit your project

        Calendar calendar = TARGET();
        Date today = Date(24, February, 2021);
        Settings::instance().evaluationDate() = today;

        Option::Type type(Option::Put);
        Real underlying = 36;
        Real strike = 40;
        Date maturity(24, May, 2021);

        ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));
        ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));
      
        Real timeToMaturity = .5; //years
       
        Rate riskFree = .03;
        Rate dividendYield = 0.0;
        Volatility sigma = .20;
        Real vol = sigma * std::sqrt(timeToMaturity);
        DiscountFactor growth = std::exp(-dividendYield * timeToMaturity);
        DiscountFactor discount = std::exp(-riskFree * timeToMaturity);
        VanillaOption europeanOption(payoff, europeanExercise);
        BlackScholesCalculator bsCalculator(payoff, underlying, growth, vol, discount);
        
        Real you = bsCalculator.value();
       
        std::cout << "NPV: " << you << std::endl;
       
        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}
