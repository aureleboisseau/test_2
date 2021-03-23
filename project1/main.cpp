
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
#include <ql/termstructures/yieldtermstructure.hpp>
#include <ql/termstructures/yield/flatforward.hpp>
#include <iostream>
#include <cstdlib>
#define BOOST_AUTO_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <ql/quantlib.hpp>
#include <boost/format.hpp>

using namespace QuantLib;

int main() {

    try {

        // modify the sample code below to suit your project

        Calendar calendar = TARGET();
        Date today = Date(24, February, 2021);
        Settings::instance().evaluationDate() = today;

        Option::Type type(Option::Put);
        Real underlying = 36;  // Spot 
        Real strike = 40;
       
        Date maturity(24, May, 2021);

       

        DayCounter dayCounter = Actual365Fixed();
        
        
      
        Real timeToMaturity = .5; //years
      
        Rate riskFree = .03;
        Rate dividendYield = 0.01;
        Volatility sigma = .20;
        Real vol = sigma * std::sqrt(1);
       
        
        DiscountFactor growth = std::exp(-dividendYield * timeToMaturity);

        //calculate payoff discount factor assuming continuous compounding 
        DiscountFactor discount = std::exp(-riskFree * timeToMaturity);

        //instantiate payoff function for a call 
        boost::shared_ptr<PlainVanillaPayoff> vanillaCallPayoff = 
            boost::shared_ptr<PlainVanillaPayoff>(new PlainVanillaPayoff(Option::Type::Call, strike));
        
        BlackScholesCalculator bsCalculator(vanillaCallPayoff, underlying, growth, vol, discount);

        //BlackScholesCalculator bsCalculator(vanillaCallPayoff, spot, growth, vol, discount);
        std::cout << boost::format("Value of 110.0 call is %.4f") % bsCalculator.value() << std::endl;
        std::cout << boost::format("Delta of 110.0 call is %.4f") % bsCalculator.delta() << std::endl;
        std::cout << boost::format("Gamma of 110.0 call is %.4f") % bsCalculator.gamma() << std::endl;
        std::cout << boost::format("Vega of 110.0 call is %.4f") % bsCalculator.vega(timeToMaturity)/100 << std::endl;
        std::cout << boost::format("Theta of 110.0 call is %.4f") % (bsCalculator.thetaPerDay(timeToMaturity)) << std::endl;

        }
}
       
     
