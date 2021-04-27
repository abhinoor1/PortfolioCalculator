# PortfolioCalculator

--- Necessary Installs for 'stockDriver.py' ---
 
 -> Install 'alpha_vantage'
    -> To install, run: pip install alpha_vantage
    -> This is the Stocks API
 -> Install 'pandas'
    -> To install, run: pip install pandas
 -> Install 'pandas_datareader'
    -> To install, run: pip install pandas_datareader
 -> Install 'numpy'
    -> To install, run: pip install numpy
 -> Install 'matplotlib'
    -> To install, run: pip install matplotlib
 -> Install 'altair'
    -> to install, run: pip install altair
 -> Install 'cryptocompare'
    -> to install, run: pip install cryptocompare
    -> This is the Cryptocurrency API
    
    
--- Necessary Installs for 'portfoliocalculator.cpp' ---
  
  -> Install SFML Graphics
  -> Include 'textbox.h'
    -> All rights to Ben Bullinger, we did NOT write this code
    -> This file is included in the Repo
    -> Link to file information: https://termspar.wordpress.com/2019/04/11/c-sfml-textbox-and-button-classes/
  -> Install 'button.h'
    -> All rights to Ben Bullinger, we did NOT write this code
    -> This file is included in the Repo
    -> Link to file information: https://termspar.wordpress.com/2019/04/11/c-sfml-textbox-and-button-classes/
 
 
--- Instructions for Using the UI ---

To get started follow these steps:
  -> If you invest in stocks only, click the "STOCKS" button and follow the below steps
  -> If you invest in Cryptocurrencies only, click the "CRYPTO" button and follow the below steps
  -> If you invest in stocks AND Cryptocurrencies, click either "STOCKS"/"CRYPTO" and follow the below steps. 
     Then click "STOCKS"/"CRYPTO" and follow the steps below again.
Click on boxes to select target input location. For example, to start inputting tickers, click "Type Tickers"
Please follow the following guidelines for entering input for Stocks:
Type Tickers: TSLA AAPL MDT
  -> Place a space in between ticker(s) with no punctuation
  -> Type in valid NASDAQ/NYSE tickers
  -> Click enter once finished entering input
Type Shares: 1 2.3 3
  -> Place a space in between input(s) with no punctuation
  -> Input number of shares in same order as ticker input
  -> For example, the 1 represents one share of TSLA. The 2.3 represents 2.3 shares of AAPL, and so on.
  -> Click enter once finished entering input
Type Purchase Price: 420 100 22
  -> Place a space in between input(s) with no punctuation
  -> Input number of shares in same order as ticker input
  -> For example, 420 represents 1 TSLA share bought at price 420. The 100 represents 2.3 AAPL shares bought
  at 100.
  -> Click enter once finished entering input
Please follow the SAME guidelines for entering input for Cryptocurrencies!


