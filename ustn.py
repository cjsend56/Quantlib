import numpy as numpy
import pandas as pd
import matplotlib.pyplot as plt
import datetime
import requests
from bs4 import BeautifulSoup
import QuantLib as ql

def GET_DATE():
	headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36'}
	req = requests.get("https://www.wsj.com/market-data/bonds", headers = headers)
	html = req.text
	soup = BeautifulSoup(html, 'html.parser')
	data = soup.find("span", class_="WSJBase--card__timestamp--3F2HxyAE")
	date = data.text
	date = datetime.datetime.strptime(date, "%m/%d/%y").date()
	return date

def GET_QUOTE(reference_date):
	headers = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36'}
	tenors = ['01M', '03M', '06M', '01Y', '02Y', '03Y', '05Y', '07Y', '10Y', '30Y']

	maturities = []
	days =[]
	prices = []
	coupons =[]

	for i, tenor in enumerate(tenors):
		req = requests.get("https://quotes.wsj.com/bond/BX/TMUBMUSD" + tenor + "?mod=md_bond_overview_quote", headers = headers)
		html = req.text
		soup = BeautifulSoup(html, 'html.parser')

		if i <= 3:
			data_src = soup.find("span", id="quote_val")
			price = data_src.text
			price = float(price[:-1])
		else:
			data_src = soup.find("span", id="price_quote_val")
			price = data_src.text
			price = price.split()
			price1 = float(price[0])
			price = price[1].split('/')
			price2 = float(price[0])
			price3 = float(price[1])
			price = price1 + (price2 / price3)

		data_src2 = soup.find_all("span", class_="data_data")

		coupon = data_src2[2].text
		if coupon != '':
			coupon = float(coupon[:-1])
		else:
			coupon = 0.0

		maturity = data_src2[3].text
		maturity = datetime.datetime.strptime(maturity, '%m/%d/%y').date()

		days.append((maturity-reference_date).days)
		prices.append(price)
		coupons.append(coupon)
		maturities.append(maturity)

	df = pd.DataFrame([maturities, days, prices, coupons]).transpose()
	headers = ['maturity', 'days', 'price', 'coupon']
	df.columns = headers	
	df.set_index('maturity', inplace=True)
	return df


ref_date = GET_DATE()
quote =GET_QUOTE(ref_date)
print(quote)