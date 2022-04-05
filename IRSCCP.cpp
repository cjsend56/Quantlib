#include <ql/quantlib.hpp>
#include <ql/indexes/ibor/krwcd.hpp>

#ifdef BOOST_MSVC
#include <ql/auto_link.hpp>
#endif

#include <iostream>
#include <iomanip>

using namespace QuantLib;
using namespace std;
using namespace ext;


#if defined(QL_ENABLE_SESSIONS)
namespace QuantLib
{
	ThreadKey sessionId() { return (); }
}
#endif

int iterator(int i)
{
	return i;
}

struct CurveData
{
	ext::shared_ptr<SimpleQuote> krw01dCl;
	ext::shared_ptr<SimpleQuote> krw03mCD;
	ext::shared_ptr<SimpleQuote> krw06mSW;
	ext::shared_ptr<SimpleQuote> krw09mSW;
	ext::shared_ptr<SimpleQuote> krw01ySW;
	ext::shared_ptr<SimpleQuote> krw18mSW;
	ext::shared_ptr<SimpleQuote> krw02ySW;
	ext::shared_ptr<SimpleQuote> krw03ySW;
	ext::shared_ptr<SimpleQuote> krw04ySW;
	ext::shared_ptr<SimpleQuote> krw05ySW;
	ext::shared_ptr<SimpleQuote> krw06ySW;
	ext::shared_ptr<SimpleQuote> krw07ySW;
	ext::shared_ptr<SimpleQuote> krw08ySW;
	ext::shared_ptr<SimpleQuote> krw09ySW;
	ext::shared_ptr<SimpleQuote> krw10ySW;
	ext::shared_ptr<SimpleQuote> krw12ySW;
	ext::shared_ptr<SimpleQuote> krw15ySW;
	ext::shared_ptr<SimpleQuote> krw20ySW;



	CurveData() :
		krw01dCl(new SimpleQuote()),
		krw03mCD(new SimpleQuote()),
		krw06mSW(new SimpleQuote()),
		krw09mSW(new SimpleQuote()),
		krw01ySW(new SimpleQuote()),
		krw18mSW(new SimpleQuote()),
		krw02ySW(new SimpleQuote()),
		krw03ySW(new SimpleQuote()),
		krw04ySW(new SimpleQuote()),
		krw05ySW(new SimpleQuote()),
		krw06ySW(new SimpleQuote()),
		krw07ySW(new SimpleQuote()),
		krw08ySW(new SimpleQuote()),
		krw09ySW(new SimpleQuote()),
		krw10ySW(new SimpleQuote()),
		krw12ySW(new SimpleQuote()),
		krw15ySW(new SimpleQuote()),
		krw20ySW(new SimpleQuote())
	{
	}

	ext::shared_ptr<SimpleQuote>& operator[] (int index) { return *(&krw01dCl + index); }

};

void sampleMktData(CurveData& cd)
{
	(*cd.krw01dCl) = 0.012369916057;
	(*cd.krw03mCD) = 0.0151;
	(*cd.krw06mSW) = 0.017264285714;
	(*cd.krw09mSW) = 0.019535714286;
	(*cd.krw01ySW) = 0.021792857143;
	(*cd.krw18mSW) = 0.024542857143;
	(*cd.krw02ySW) = 0.026667857143;
	(*cd.krw03ySW) = 0.028053571429;
	(*cd.krw04ySW) = 0.028135714286;
	(*cd.krw05ySW) = 0.028035714286;
	(*cd.krw06ySW) = 0.027832142857;
	(*cd.krw07ySW) = 0.027685714286;
	(*cd.krw08ySW) = 0.027407142857;
	(*cd.krw09ySW) = 0.027303571429;
	(*cd.krw10ySW) = 0.027196428571;
	(*cd.krw12ySW) = 0.027192857143;
	(*cd.krw15ySW) = 0.026632142857;
	(*cd.krw20ySW) = 0.02435;
}

ext::shared_ptr<YieldTermStructure> buildCurve(Date todaysDate, const CurveData& cd)
{

	//Date todaysDate(8, Sep, 2021);
	Calendar calendar = SouthKorea();

	calendar.addHoliday(Date(4, Oct, 2021));
	calendar.addHoliday(Date(11, Oct, 2021));
	calendar.addHoliday(Date(10, Oct, 2021));

	calendar.addHoliday(Date(1, Jan, 2021));
	calendar.addHoliday(Date(31, Jan, 2021));
	calendar.addHoliday(Date(1, Feb, 2021));
	calendar.addHoliday(Date(2, Feb, 2021));
	calendar.addHoliday(Date(1, Mar, 2021));
	calendar.addHoliday(Date(9, Mar, 2021));
	calendar.addHoliday(Date(5, May, 2021));
	calendar.addHoliday(Date(8, May, 2021));
	calendar.addHoliday(Date(1, Jun, 2021));
	calendar.addHoliday(Date(6, Jun, 2021));
	calendar.addHoliday(Date(15, Aug, 2021));
	calendar.addHoliday(Date(12, Sep, 2021));
	calendar.addHoliday(Date(3, Oct, 2021));
	calendar.addHoliday(Date(9, Oct, 2021));
	calendar.addHoliday(Date(10, Oct, 2021));
	calendar.addHoliday(Date(25, Dec, 2021));

	calendar.addHoliday(Date(10, Oct, 2021));
	calendar.addHoliday(Date(10, Oct, 2021));


	calendar.addHoliday(Date(2, Mar, 2026));
	calendar.addHoliday(Date(3, Jun, 2026));
	calendar.addHoliday(Date(17, Aug, 2026));
	calendar.addHoliday(Date(5, Oct, 2026));
	calendar.addHoliday(Date(3, Mar, 2027));
	calendar.addHoliday(Date(16, Aug, 2027));
	calendar.addHoliday(Date(4, Oct, 2027));
	calendar.addHoliday(Date(11, Oct, 2027));
	calendar.addHoliday(Date(3, Mar, 2031));
	calendar.addHoliday(Date(16, Aug, 2032));
	calendar.addHoliday(Date(4, Oct, 2032));
	calendar.addHoliday(Date(11, Oct, 2032));
	calendar.addHoliday(Date(10, Oct, 2033));
	calendar.addHoliday(Date(3, Mar, 2036));
	calendar.addHoliday(Date(7, Oct, 2036));
	calendar.addHoliday(Date(2, Mar, 2037));
	calendar.addHoliday(Date(17, Aug, 2037));
	calendar.addHoliday(Date(5, Oct, 2037));
	calendar.addHoliday(Date(16, Aug, 2038));
	calendar.addHoliday(Date(4, Oct, 2038));
	calendar.addHoliday(Date(11, Oct, 2038));
	calendar.addHoliday(Date(10, Oct, 2039));
	// Election //
	calendar.addHoliday(Date(3, Mar, 2025));
	calendar.addHoliday(Date(12, Apr, 2028));
	calendar.addHoliday(Date(12, Jun, 2030));
	calendar.addHoliday(Date(3, Mar, 2032));
	calendar.addHoliday(Date(14, Apr, 2032));
	calendar.addHoliday(Date(31, May, 2034));
	calendar.addHoliday(Date(9, Apr, 2036));
	calendar.addHoliday(Date(4, Mar, 2037));
	calendar.addHoliday(Date(2, Jun, 2038));
	calendar.addHoliday(Date(11, Apr, 2038));

	DayCounter dayCounter = Actual365Fixed();
	Settings::instance().evaluationDate() = todaysDate;
	todaysDate = Settings::instance().evaluationDate();


	ext::shared_ptr<IborIndex> krwCD(new KrwCD3M());

	Integer fixingDays = 1;
	Date settlementDate = calendar.advance(todaysDate, fixingDays, Days);

	std::vector<pair<Period, Real> > inputVec;
	inputVec.push_back(make_pair(Period(1 * Days), cd.krw01dCl.get()->value()));
	inputVec.push_back(make_pair(Period(3 * Months), cd.krw03mCD.get()->value()));
	inputVec.push_back(make_pair(Period(6 * Months), cd.krw06mSW.get()->value()));
	inputVec.push_back(make_pair(Period(9 * Months), cd.krw09mSW.get()->value()));
	inputVec.push_back(make_pair(Period(12 * Months), cd.krw01ySW.get()->value()));
	inputVec.push_back(make_pair(Period(18 * Months), cd.krw18mSW.get()->value()));
	inputVec.push_back(make_pair(Period(24 * Months), cd.krw02ySW.get()->value()));
	inputVec.push_back(make_pair(Period(36 * Months), cd.krw03ySW.get()->value()));
	inputVec.push_back(make_pair(Period(48 * Months), cd.krw04ySW.get()->value()));
	inputVec.push_back(make_pair(Period(60 * Months), cd.krw05ySW.get()->value()));
	inputVec.push_back(make_pair(Period(72 * Months), cd.krw06ySW.get()->value()));
	inputVec.push_back(make_pair(Period(84 * Months), cd.krw07ySW.get()->value()));
	inputVec.push_back(make_pair(Period(96 * Months), cd.krw08ySW.get()->value()));
	inputVec.push_back(make_pair(Period(108 * Months), cd.krw09ySW.get()->value()));
	inputVec.push_back(make_pair(Period(120 * Months), cd.krw10ySW.get()->value()));
	inputVec.push_back(make_pair(Period(144 * Months), cd.krw12ySW.get()->value()));
	inputVec.push_back(make_pair(Period(180 * Months), cd.krw15ySW.get()->value()));
	inputVec.push_back(make_pair(Period(240 * Months), cd.krw20ySW.get()->value()));

	// Helpers & Instruments //
	krwCD->addFixing(settlementDate, cd.krw03mCD->value(), true);
	Frequency swFixedLegFrequency = Quarterly;
	BusinessDayConvention swFixedLegConvention = ModifiedFollowing;
	DayCounter swFixedLegDayCounter = Actual365Fixed();

	ext::shared_ptr<RateHelper> dp01d(new DepositRateHelper(Handle<Quote>(cd.krw01dCl), Period(1 * Days), 0, calendar, ModifiedFollowing, true, Actual365Fixed()));

	std::vector<ext::shared_ptr<RateHelper>> ccpInstruments;

	for (Size i = 0; i <= 80; i++)
	{
		for (Size j = 1; j <= inputVec.size() - 1; j++)
		{
			if (Period((i + 1) * 3 * Months) == inputVec[j].first)
			{
				ext::shared_ptr<Quote> tempPar(new SimpleQuote(inputVec[j].second));
				ext::shared_ptr<RateHelper> tempHelper(new SwapRateHelper(Handle<Quote>(tempPar), inputVec[j].first,
					calendar, swFixedLegFrequency, swFixedLegConvention, swFixedLegDayCounter, krwCD));//, krwCD, Handle<Quote>(), 0 * Days, discountingTermStucture));
				ccpInstruments.push_back(tempHelper);
			}

			if ((j < 16) && ((Period((i + 1) * 3 * Months) < inputVec[j + 1].first) && (Period((i + 1) * 3 * Months) > inputVec[j].first)))
			{
				Date tempDt1 = calendar.advance(settlementDate, inputVec[j + 1].first);
				Date tempDt0 = calendar.advance(settlementDate, inputVec[j].first);
				Date tempDtn = calendar.advance(settlementDate, (i + 1) * 3, Months);
				Rate intpl = inputVec[j].second + (inputVec[j + 1].second - inputVec[j].second) *
					(tempDtn.serialNumber() - tempDt0.serialNumber()) / (tempDt1.serialNumber() - tempDt0.serialNumber());

				ext::shared_ptr<Quote> tempPar(new SimpleQuote(intpl));
				ext::shared_ptr<RateHelper> tempHelper(new SwapRateHelper(Handle<Quote>(tempPar), (i + 1) * 3 * Months,
					calendar, swFixedLegFrequency, swFixedLegConvention, swFixedLegDayCounter, krwCD));//, krwCD, Handle<Quote>(), 0 * Days, discountingTermStucture));
				ccpInstruments.push_back(tempHelper);

			}
			// 15 ~ 20
			if ((j >= 16) && (j < 17) && (Period((i + 1) * 3 * Months) < inputVec[17].first) && (Period((i + 1) * 3 * Months) > inputVec[16].first))
			{
				Date tempDt1 = calendar.advance(settlementDate, inputVec[17].first);
				Date tempDt0 = calendar.advance(settlementDate, inputVec[16].first);
				Date tempDtn = calendar.advance(settlementDate, (i + 1) * 3, Months);

				Rate intpl = inputVec[16].second + (inputVec[17].second - inputVec[16].second) *
					(tempDtn.serialNumber() - tempDt0.serialNumber()) / (tempDt1.serialNumber() - tempDt0.serialNumber());

				ext::shared_ptr<Quote> tempPar(new SimpleQuote(intpl));
				ext::shared_ptr<RateHelper> tempHelper(new SwapRateHelper(Handle<Quote>(tempPar), (i + 1) * 3 * Months,
					calendar, swFixedLegFrequency, swFixedLegConvention, swFixedLegDayCounter, krwCD));//, krwCD, Handle<Quote>(), 0 * Days, discountingTermStucture));
				ccpInstruments.push_back(tempHelper);
			}
		}
	}
	//std::cout << ccpInstruments.size() << std::endl;

	double tolerance = 1.0e-15;
	ext::shared_ptr<YieldTermStructure> ccpTermStructure(new PiecewiseYieldCurve<Discount, LogLinear>(settlementDate, ccpInstruments, Actual365Fixed(), tolerance));
	ccpTermStructure->enableExtrapolation(true);
	return ccpTermStructure;
	//discountingTermStucture.linkTo(ccpTermStructure);
}

int main()
{
	try
	{
		std::cout << std::endl;

		/* Inputting 1. Conventions */

		Calendar calendar = SouthKorea();
		Date todaysDate(1, April, 2022);
		Settings::instance().evaluationDate() = todaysDate;
		todaysDate = Settings::instance().evaluationDate();
		Real fixingDays = 1;

		Date settlementDate = calendar.advance(todaysDate, fixingDays, Days);

		/* Inputting 2. Quotes, Helpers */
		CurveData cd;
		sampleMktData(cd);

		boost::shared_ptr<YieldTermStructure> curve = buildCurve(todaysDate, cd);
		RelinkableHandle<YieldTermStructure> discountingTermStucture;
		discountingTermStucture.linkTo(curve);


		// Swap Information //
		//
		//(*cd.krw15ySW) = 0.017025;
		//(*cd.krw20ySW) = 0.016589285714;

		Rate fixedRate = 0.0172;
		Integer lengthInYears = 0;
		VanillaSwap::Type swapType = VanillaSwap::Receiver;
		//Date maturity = settlementDate + Period(lengthInYears * Years);
		Date maturity(20, May, 2031);
		Real nominal = 10000000000;
		Spread spread = -0.00002; // down shock

		// Fixed Leg //
		DayCounter dayCounter = Actual365Fixed();
		Frequency fixedLegFrequency = Quarterly;
		BusinessDayConvention dayConvention = ModifiedFollowing;
		//DayCounter dayCounter = Actual365Fixed();
		Schedule schedule(settlementDate, maturity, Period(fixedLegFrequency), calendar, dayConvention, dayConvention, DateGeneration::Forward, true);
		ext::shared_ptr<IborIndex> krwCDsw(new KrwCD3M(discountingTermStucture));
		krwCDsw->addFixing(settlementDate, cd.krw03mCD->value(), true);

		Real NPV;
		Rate fairRate;
		VanillaSwap Swap(swapType, nominal, schedule, fixedRate, dayCounter, schedule, krwCDsw, spread, dayCounter);
		ext::shared_ptr<PricingEngine> swapEngine(new DiscountingSwapEngine(discountingTermStucture));
		Swap.setPricingEngine(swapEngine);
		NPV = Swap.NPV();

		std::cout << "Vanilla Swap Price (Korea Central Celearing Counterparty in KRX) " << std::endl;
		std::cout << "Precision : 0.E-12 " << std::endl;

		std::cout << setprecision(15) << std::endl;
		std::cout << "Settle Date " << schedule.startDate() << std::endl;
		std::cout << "Mat Date " << schedule.endDate() << std::endl;

		std::cout << setprecision(15) << std::endl;
		std::cout << "fixed Leg NPV : " << Swap.fixedLegNPV() << std::endl;
		std::cout << "floating Leg NPV : " << Swap.floatingLegNPV() << std::endl;

		std::cout << setprecision(15) << std::endl;
		std::cout << "fixed Leg BPS : " << Swap.fixedLegBPS() << std::endl;
		std::cout << "floating Leg BPS : " << Swap.floatingLegBPS() << std::endl;

		std::cout << setprecision(15) << std::endl;
		std::cout << "Swap Fair NPV  : " << Swap.NPV() << std::endl;
		std::cout << "Swap Fair Rate : " << Swap.fairRate() << std::endl;
		std::cout << "Swap Fair Spread : " << Swap.fairSpread() << std::endl;

		std::cout << std::endl;


		std::cout << "Vanilla Swap Greeks for Trading and Hedging " << std::endl;
		string Tenor[] = { "Call 1d", "CD 3 month", "Swap 6 Month", "Swap 9 Month", "Swap 1 Year", "Swap 18 Month",
							"Swap 2 Year", "Swap 3 Year", "Swap 4 Year", "Swap 5 Year", "Swap 6 Year", "Swap 7 Year",
							"Swap 8 Year", "Swap 9 Year", "Swap 10 Year", "Swap 12 Year", "Swap 15 Year", "Swap 20 Year" };
		Size TenorNum[] = { 1,2,4,6,7,8,9,11,14,15,16,17 };

		for (Size i : TenorNum)
		{
			(*cd[i]) = cd[i]->value() + 0.0001;

			boost::shared_ptr<YieldTermStructure> upbumpedCurve = buildCurve(todaysDate, cd);
			RelinkableHandle<YieldTermStructure> upBumpeddiscountingTermStucture;
			upBumpeddiscountingTermStucture.linkTo(upbumpedCurve);
			ext::shared_ptr<IborIndex> upkrwCDsw(new KrwCD3M(upBumpeddiscountingTermStucture));
			upkrwCDsw->addFixing(settlementDate, cd.krw03mCD->value(), true);
			VanillaSwap upBumpedSwap(swapType, nominal, schedule, fixedRate, dayCounter, schedule, upkrwCDsw, spread, dayCounter);
			ext::shared_ptr<PricingEngine> upswapEngine(new DiscountingSwapEngine(upBumpeddiscountingTermStucture));
			upBumpedSwap.setPricingEngine(upswapEngine);

			(*cd[i]) = cd[i]->value() - 0.0002;

			boost::shared_ptr<YieldTermStructure> dnbumpedCurve = buildCurve(todaysDate, cd);
			RelinkableHandle<YieldTermStructure> dnBumpeddiscountingTermStucture;
			dnBumpeddiscountingTermStucture.linkTo(dnbumpedCurve);
			ext::shared_ptr<IborIndex> dnkrwCDsw(new KrwCD3M(dnBumpeddiscountingTermStucture));
			dnkrwCDsw->addFixing(settlementDate, cd.krw03mCD->value(), true);
			VanillaSwap dnBumpedSwap(swapType, nominal, schedule, fixedRate, dayCounter, schedule, dnkrwCDsw, spread, dayCounter);
			ext::shared_ptr<PricingEngine> dnswapEngine(new DiscountingSwapEngine(dnBumpeddiscountingTermStucture));
			dnBumpedSwap.setPricingEngine(dnswapEngine);

			std::cout << std::endl;
			std::cout << "UP Swap Fair NPV  : " << upBumpedSwap.NPV() << std::endl;
			std::cout << "Down Swap Fair NPV  : " << dnBumpedSwap.NPV() << std::endl;
			std::cout << "Rho in " << Tenor[i] << " Tenor is " << (upBumpedSwap.NPV() - dnBumpedSwap.NPV()) / 0.0002 << endl;

			(*cd[i]) = cd[i]->value() + 0.0002;

			if ((upBumpedSwap.NPV() - Swap.NPV()) < 0.0001)
			{
				break;
			}
		}

		std::cout << std::endl;

		return 0;
	}
	catch (int e)
	{
		std::cout << e << std::endl;
		return 1;
	}



}