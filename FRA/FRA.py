import datetime
import QuantLib as ql
from SWAP_CURVE import GET_QUOTE, SWAP_CURVE

class FRA():
	def __init__(self, todays_date, value_date, maturity_date, position, fra_rate, notional):
		self.date = todays_date
		self.curve = self.CURVE(self.date)

		self.value_date = ql.Date(value_date.day, value_date.month, value_date.year)
		self.maturity_date = ql.Date(maturity_date.day, maturity_date.month, maturity_date.year)

		if position == "Long":
			self.position = ql.Position.Long
		else:
			self.position = ql.Position.Short

		self.fra_rate = fra_rate
		self.notional = notional

		self.npv = self.PRICING(self.curve)
		self.delta = self.DELTA()
		self.theta = self.THETA()

	def CURVE(self, date):
		return SWAP_CURVE(date, GET_QUOTE(date))

	def PRICING(self, curve):
		curve_handle = ql.YieldTermStructureHandle(curve)

		libor = ql.USDLibor(ql.Period(3, ql.Months), curve_handle)

		fra = ql.ForwardRateAgreement(self.value_date,
									  self.maturity_date,
									  self.position,
									  self.fra_rate,
									  self.notional,
									  libor,
									  curve_handle)

		npv = fra.NPV()

		return npv

	def DELTA(self):
		curve_handle = ql.YieldTermStructureHandle(self.curve)

		basis_point = 0.0001

		up_curve = ql.ZeroSpreadedTermStructure(curve_handle, ql.QuoteHandle(ql.SimpleQuote(basis_point)))
		up_fra = self.PRICING(up_curve)

		down_curve = ql.ZeroSpreadedTermStructure(curve_handle, ql.QuoteHandle(ql.SimpleQuote(-basis_point)))
		down_fra = self.PRICING(down_curve)

		dv01 = (up_fra - down_fra) / 2

		return dv01

	def THETA(self):
		price_t0 = self.PRICING(self.CURVE(self.date))
		price_t1 = self.PRICING(self.CURVE(self.date + datetime.timedelta(days=1)))

		theta = price_t1 - price_t0

		return theta

if __name__=="__main__":

	todays_date = datetime.date(2020, 10, 9)

	value_date = datetime.date(2021, 1, 9)
	maturity_date = datetime.date(2021, 4, 9)
	position = "Long"
	fra_rate = 0.0022
	notional = 10000000

	fra = FRA(todays_date,
			  value_date,
			  maturity_date,
			  position,
			  fra_rate,
			  notional)

	print("Price = {}".format(round(fra.npv, 4)))
	print("Delta = {}".format(round(fra.delta, 4)))
	print("Theta = {}".format(round(fra.theta, 4)))

