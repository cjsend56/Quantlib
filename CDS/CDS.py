import datetime
import QuantLib as ql
from CDS_CURVE import GET_IRS_QUOTE, GET_CDS_QUOTE, SWAP_CURVE, CDS_CURVE

class CDS():
	def __init__(self, todays_date, maturity_date, spread, notional, position):
		self.todays_date = todays_date

		self.discount_curve = self.DISCOUNT_CURVE(self.todays_date)
		self.cds_curve = self.CDS_CURVE(self.todays_date)

		self.maturity_date = ql.Date(maturity_date.day, maturity_date.month, maturity_date.year)

		if position =="Long":
			self.position = ql.Protection.Buyer
		else:
			self.position = ql.Protection.Seller

		self.spread = spread
		self.notional = notional
		self.recovery_rate = 0.4

		self.tenor = ql.Period(3, ql.Months)
		self.calendar = ql.UnitedStates()
		self.convention = ql.ModifiedFollowing
		self.dateGeneratoin = ql.DateGeneration.CDS
		self.dayCount = ql.Actual360()
		self.endOfMonth = False

		self.npv = self.PRICING(self.discount_curve, self.cds_curve)
		self.ir_delta = self.IR_DELTA()
		self.cr_delta = self.CREDIT_DELTA()
		self.theta = self.THETA()

	def DISCOUNT_CURVE(self, date):
		return SWAP_CURVE(date, GET_IRS_QUOTE(date))

	def CDS_CURVE(self, date):
		return CDS_CURVE(date, GET_CDS_QUOTE(date), SWAP_CURVE(date, GET_IRS_QUOTE(date)))

	def PRICING(self, discount_curve, cds_curve):
		todays_date = ql.Date(self.todays_date.day, self.todays_date.month, self.todays_date.year)
		discount_curve_handle = ql.YieldTermStructureHandle(discount_curve)

		schedule = ql.Schedule(todays_date,
							   self.maturity_date,
							   self.tenor,
							   self.calendar,
							   self.convention,
							   self.convention,
							   self.dateGeneratoin,
							   self.endOfMonth)

		cds = ql.CreditDefaultSwap(self.position,
								   self.notional,
								   self.spread / 10000,
								   schedule,
								   self.convention,
								   self.dayCount)

		probability = ql.DefaultProbabilityTermStructureHandle(cds_curve)

		engine = ql.MidPointCdsEngine(probability,
									  self.recovery_rate,
									  discount_curve_handle)

		cds.setPricingEngine(engine)

		npv = cds.NPV()

		return npv

	def IR_DELTA(self):
		curve_handle = ql.YieldTermStructureHandle(self.discount_curve)

		basis_point = 0.0001

		up_curve = ql.ZeroSpreadedTermStructure(curve_handle, ql.QuoteHandle(ql.SimpleQuote(basis_point)))
		up_cds = self.PRICING(up_curve, self.cds_curve)

		down_curve = ql.ZeroSpreadedTermStructure(curve_handle, ql.QuoteHandle(ql.SimpleQuote(-basis_point)))
		down_cds = self.PRICING(down_curve, self.cds_curve)

		delta = (up_cds - down_cds) / 2

		return delta

	def CREDIT_DELTA(self):
		temp_cds_quote = GET_CDS_QUOTE(self.todays_date)

		temp_cds_quote['Market.Mid'] += 1
		up_curve = CDS_CURVE(self.todays_date, temp_cds_quote, self.discount_curve)
		up_cds = self.PRICING(self.discount_curve, up_curve)

		temp_cds_quote['Market.Mid'] -= 2
		down_curve = CDS_CURVE(self.todays_date, temp_cds_quote, self.discount_curve)
		down_cds = self.PRICING(self.discount_curve, down_curve)

		delta = (up_cds - down_cds) / 2

		return delta

	def THETA(self):
		price_t0 = self.PRICING(self.discount_curve, self.cds_curve)

		discount_curve_t1 = self.DISCOUNT_CURVE(self.todays_date + datetime.timedelta(days=1))
		cds_curve_t1 = self.CDS_CURVE(self.todays_date + datetime.timedelta(days=1))

		price_t1 = self.PRICING(discount_curve_t1, cds_curve_t1)

		theta = price_t1 - price_t0

		return theta

if __name__ == "__main__":

	todaysDate = datetime.date(2022, 3, 15)

	notional = 100000000
	maturity = datetime.date(2024, 12, 20)
	spread = 40
	position = "Short"

	cds = CDS(todaysDate, maturity, spread, notional, position)

	print("Price = {}".format(round(cds.npv, 4)))
	print("IR Delta = {}".format(round(cds.ir_delta, 4)))
	print("Credit Delta = {}".format(round(cds.cr_delta, 4)))
	print("Theta = {}".format(round(cds.theta, 4)))