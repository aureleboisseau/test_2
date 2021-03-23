#include <iostream>
#include <cstdlib>

#include <boost/test/unit_test.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <ql/quantlib.hpp>
#include <boost/format.hpp>

namespace {

using namespace QuantLib;


Real strike = 110.0;
Real timeToMaturity = .5; //years
Real spot = 100.0;
Rate riskFree = .03;
Rate dividendYield = 0.0;
Volatility sigma = .20;

//QuantLib requires sigma * sqrt(T) rather than just sigma/volatility
Real vol = sigma * std::sqrt(timeToMaturity);

//calculate dividend discount factor assuming continuous compounding (e^-rt)
DiscountFactor growth = std::exp(-dividendYield * timeToMaturity);

//calculate payoff discount factor assuming continuous compounding 
DiscountFactor discount = std::exp(-riskFree * timeToMaturity);

//instantiate payoff function for a call 
boost::shared_ptr<PlainVanillaPayoff> vanillaCallPayoff = 
    boost::shared_ptr<PlainVanillaPayoff>(new PlainVanillaPayoff(Option::Type::Call, strike));

BlackScholesCalculator bsCalculator(vanillaCallPayoff, spot, growth, vol, discount);
std::cout << boost::format("Value of 110.0 call is %.4f") % bsCalculator.value() << std::endl;
std::cout << boost::format("Delta of 110.0 call is %.4f") % bsCalculator.delta() << std::endl;
std::cout << boost::format("Gamma of 110.0 call is %.4f") % bsCalculator.gamma() << std::endl;
std::cout << boost::format("Vega of 110.0 call is %.4f") % bsCalculator.vega(timeToMaturity)/100 << std::endl;
std::cout << boost::format("Theta of 110.0 call is %.4f") % (bsCalculator.thetaPerDay(timeToMaturity)) << std::endl;
    
}
