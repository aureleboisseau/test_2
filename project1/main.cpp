
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
        Real div = 0.05;
        Real volatility = 0.15;
        Real riskFreeRate = 0.20;
       
        Date maturity(24, May, 2021);

        ext::shared_ptr<Exercise> europeanExercise(new EuropeanExercise(maturity));
        ext::shared_ptr<StrikedTypePayoff> payoff(new PlainVanillaPayoff(type, strike));

        

        DayCounter dayCounter = Actual365Fixed();
       
        
   
       
       
      

        ext::shared_ptr<BlackScholesProcess2> bsmProcess(
                 new BlackScholesProcess2(underlying, div,  riskFreeRate, volatility, volatility));

        
        // options
        VanillaOption europeanOption(payoff, europeanExercise);

        Size timeSteps = 10;
        Size mcSeed = 42;
        ext::shared_ptr<PricingEngine> mcengine;
        mcengine = MakeMCEuropeanEngine_2<PseudoRandom>(bsmProcess)
            .withSteps(timeSteps)
            .withAbsoluteTolerance(0.01)
            .withSeed(mcSeed);
        europeanOption.setPricingEngine(mcengine);

        auto startTime = std::chrono::steady_clock::now();

        Real NPV = europeanOption.NPV();

        auto endTime = std::chrono::steady_clock::now();

        double us = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        std::cout << "NPV: " << NPV << std::endl;
        std::cout << "Elapsed time: " << us / 1000000 << " s" << std::endl;
        

        return 0;

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "unknown error" << std::endl;
        return 1;
    }
}
