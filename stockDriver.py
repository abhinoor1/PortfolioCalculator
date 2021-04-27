'''
Created on April 21, 2021

@author: vinaymetlapalli
'''

from alpha_vantage.timeseries import TimeSeries
import pandas
import pandas_datareader
import numpy as np
import matplotlib.pyplot as plt
import altair as alt
import requests
import cryptocompare
import time

key = 'IQQ9SI95WFUFH5RD'


#client = Client(account_sid, auth_token)


#time.sleep(5)

file = open("ui_output.txt","r")
user_stocks = file.readline()
user_number_of_shares = file.readline()
user_purchase_price = file.readline()
user_crypto = file.readline()
user_crypto_number_of_shares = file.readline()
user_crypto_purchase_price = file.readline()
file.close()


user_stocks_final = user_stocks.split()

user_prices_final = user_purchase_price.split()

user_shares_final = user_number_of_shares.split()

user_cryptos_final = user_crypto.split()

user_cyrpto_prices_final = user_crypto_purchase_price.split()

user_crypto_shares_final = user_crypto_number_of_shares.split()

user_profits_by_stock = list()
user_detailed_reports = list()

def getStockInfo (symbol,index):
    ts = TimeSeries(key)
    test, test2 = ts.get_daily(symbol = str(symbol))
    day_info = test['2021-04-23']
    close_info = day_info.get('4. close')
    user_detailed_reports.append(day_info)
    profit_calc_1 = float(close_info)*float(user_shares_final[index])
    profit_calc_2 = float(user_prices_final[index])*float(user_shares_final[index])
    user_profits_by_stock.append(profit_calc_1-profit_calc_2)


for i in range(len(user_prices_final)):
    getStockInfo(user_stocks_final[i],i)

current_crypto_prices = list()
user_profits_by_crypto = list()

for i in range(len(user_cryptos_final)):

    price = cryptocompare.get_price(str(user_cryptos_final[i]), 'USD')
    current_price = ((price[str(user_cryptos_final[i])])['USD'])
    profit_calc_c_1 = float(current_price)*float(user_crypto_shares_final[i])
    profit_calc_c_2 = float(user_cyrpto_prices_final[i])*float(user_crypto_shares_final[i])
    user_profits_by_crypto.append(profit_calc_c_1-profit_calc_c_2)

stock_index = 0;
clean_outputs = list()
clean_outputs_crypto = list()

for i in range(len(user_detailed_reports)):
    c_output = user_stocks_final[stock_index] + " Info:" + " Open: $" + user_detailed_reports[i].get('1. open') + " High: $" + user_detailed_reports[i].get('2. high') + " Low: $" + user_detailed_reports[i].get('3. low') \
    + " Close: $" + user_detailed_reports[i].get('4. close') + " Volume: " + user_detailed_reports[i].get('5. volume') + "\n"
    clean_outputs.append(c_output)
    stock_index = stock_index + 1

crypto_index = 0

for i in range(len(current_crypto_prices)):
    c_output_crypto = user_cryptos_final[crypto_index] + " Current Price: $" + current_crypto_prices[i] + "\n"
    clean_outputs_crypto.append(c_output_crypto)
    crypto_index = crypto_index + 1



user_profits_by_stock = [round(num, 2) for num in user_profits_by_stock]
user_profits_by_crypto = [round(num, 2) for num in user_profits_by_crypto]
user_total_profits = sum(user_profits_by_stock) + sum(user_profits_by_crypto)
user_total_profits = round(user_total_profits,2)

file_out = open("python_to_ui.txt","w")
file_out.writelines(str(sum(user_profits_by_stock)))
file_out.write("\n")
file_out.writelines(str(sum(user_profits_by_crypto)))
file_out.write("\n")
file_out.writelines(str(user_total_profits))
file_out.write("\n")
for i in range(len(clean_outputs)) :
    file_out.writelines(clean_outputs[i])
    file_out.write("\n")
for i in range(len(clean_outputs_crypto)):
    file_out.writelines(clean_outputs_crypto[i])
    file_out.write("\n")
file_out.close()
