import datetime
import QuantExt as qe
from SWAP_CURVE import GET_QUOTE, USDIRS_CURVE, KRWCCS_CURVE

class CCS():
	def __init__(self, todays_date, effective_date, maturity_date, ccs_rate, fx_spot, usd_notional, position):
		self.date = todays_date

		self.usd_curve = self.USD_CURVE(self.date)
		self.krw_curve = self.KRW_CURVE(self.date)

		self.fx_spot = fx_spot

		self.effective_date = qe.Date(effective_date.day, effective_date.month, effective_date.year)
		self.maturity_date = qe.Date(maturity_date.day, maturity_date.month, maturity_date.year)

		if position == 'Long':
			self.position = qe.VanillaSwap.Payer
		else:
			self.position = qe.VanillaSwap.Receiver

		self.ccs_rate = ccs_rate
		self.usd = qe.USDCurrency()
		self.usd_notional = usd_notional
		self.krw = qe.KRWCurrency()
		self.krw_notional = usd_notional * fx_spot

		self.length = 2
		self.spread = 0.0
		self.convention = qe.ModifiedFollowing
		self.calendar = qe.JointCalendar(qe.SouthKorea(), qe.UnitedStates())
		self.tenor = qe.Period(6, qe.Months)

		self.fixed_day_count = qe.Actual365Fixed()
		self.float_day_count = qe.Actual360()
		self.dateGeneration = qe.DateGeneration.Backward

		self.npv = self.PRICING(self.usd_curve, self.krw_curve, self.fx_spot)

		self.fx_delta = self.FX_DELTA()
		self.usd_curve_delta = self.USD_CURVE_DELTA()
		self.krw_curve_delta = self.KRW_CURVE_DELTA()
		self.theta = self.THETA()

	def USD_CURVE(self, date):
		return USDIRS_CURVE(date, GET_QUOTE(date, 'USD'))

	def KRW_CURVE(self, date):
		return KRWCCS_CURVE(date, GET_QUOTE(date, 'KRW'))

	def PRICING(self, usd_curve, krw_curve, fx_spot):
		usd_curve_handle = qe.YieldTermStructureHandle(usd_curve)
		krw_curve_handle = qe.YieldTermStructureHandle(krw_curve)
		fx_spot_handle = qe.QuoteHandle(qe.SimpleQuote(fx_spot))

		usd_6m_libor = qe.USDLibor(qe.Period(6, qe.Months), usd_curve_handle)

		usd_6m_libor.addFixing(qe.Date(28, 10, 2021), 0.000924)

		fixed_schedule = qe.Schedule(self.effective_date,
									 self.maturity_date,
									 self.tenor,
									 self.calendar,
									 self.convention,
									 self.convention,
									 self.dateGeneration,
									 False)

		float_schedule = qe.Schedule(self.effective_date,
									 self.maturity_date,
									 self.tenor,
									 self.calendar,
									 self.convention,
									 self.convention,
									 self.dateGeneration,
									 False)

		ccs = qe.CrossCcyFixFloatSwap(self.position,
									  self.krw_notional,
									  self.krw,
									  fixed_schedule,
									  self.ccs_rate,
									  self.fixed_day_count,
									  self.convention,
									  self.length,
									  self.calendar,
									  self.usd_notional,
									  self.usd,
									  float_schedule,
									  usd_6m_libor,
									  self.spread,
									  self.convention,
									  self.length,
									  self.calendar)

		engine = qe.CrossCcySwapEngine(self.krw,
									   krw_curve_handle,
									   self.usd,
									   usd_curve_handle,
									   fx_spot_handle)

		ccs.setPricingEngine(engine)

		npv = ccs.NPV()

		return npv

	def FX_DELTA(self):
		percentage = 0.01

		up_fx = self.fx_spot * (1 + percentage)
		up_ccs = self.PRICING(self.usd_curve, self.krw_curve, up_fx)

		down_fx = self.fx_spot * (1 - percentage)
		down_ccs = self.PRICING(self.usd_curve, self.krw_curve, down_fx)

		fx_delta = (up_ccs - down_ccs) / 2

		return fx_delta

	def USD_CURVE_DELTA(self):
		curve_handle = qe.YieldTermStructureHandle(self.usd_curve)

		basis_point = 0.0001

		up_curve = qe.ZeroSpreadedTermStructure(curve_handle, qe.QuoteHandle(qe.SimpleQuote(basis_point)))
		up_ccs = self.PRICING(up_curve, self.krw_curve, self.fx_spot)

		down_curve = qe.ZeroSpreadedTermStructure(curve_handle, qe.QuoteHandle(qe.SimpleQuote(-basis_point)))
		down_ccs = self.PRICING(down_curve, self.krw_curve, self.fx_spot)

		delta = (up_ccs - down_ccs) / 2

		return delta

	def KRW_CURVE_DELTA(self):
		curve_handle = qe.YieldTermStructureHandle(self.krw_curve)

		basis_point = 0.0001

		up_curve = qe.ZeroSpreadedTermStructure(curve_handle, qe.QuoteHandle(qe.SimpleQuote(basis_point)))
		up_ccs = self.PRICING(self.usd_curve, up_curve, self.fx_spot)

		down_curve = qe.ZeroSpreadedTermStructure(curve_handle, qe.QuoteHandle(qe.SimpleQuote(-basis_point)))
		down_ccs = self.PRICING(self.usd_curve, down_curve, self.fx_spot)

		delta = (up_ccs - down_ccs) / 2

		return delta

	def THETA(self):
		price_t0 = self.PRICING(self.usd_curve, self.krw_curve, self.fx_spot)

		usd_curve_t1 = self.USD_CURVE(self.date + datetime.timedelta(days=1))
		krw_curve_t1 = self.KRW_CURVE(self.date + datetime.timedelta(days=1))

		price_t1 = self.PRICING(usd_curve_t1, krw_curve_t1, self.fx_spot)

		theta = price_t1 - price_t0

		return theta

if __name__=="__main__":
	todays_date = datetime.date(2020, 10, 8)

	fx_spot = 1133.85

	effective_date = datetime.date(2021, 11, 1)
	maturity_date = datetime.date(2025, 11, 1)
	position = 'Long'
	ccs_rate = 0.002438
	usd_notional = 10000000

	ccs = CCS(todays_date,
			  effective_date,
			  maturity_date,
			  ccs_rate,
			  fx_spot,
			  usd_notional,
			  position)

	print("Price = {}".format(round(ccs.npv, 4)))
	print("FX Delta = {}".format(round(ccs.fx_delta, 4)))
	print("USD Curve Delta = {}".format(round(ccs.usd_curve_delta, 4)))
	print("KRW Curve delta = {}".format(round(ccs.krw_curve_delta, 4)))
	print("Theta = {}".format(round(ccs.theta, 4)))