/*
Portfolio Calculator
EC327 Prof. Carruthers
Project by Abhinoor Singh, Vinay Metlapalli, Liron Dubin, Aniket Joshi

*/

#include <SFML/Graphics.hpp>
#include "textbox.h"
#include "button.h"
#include <iostream>
#include <string>
#include <locale>
#include <vector>
#include <fstream>

using std::cout;
using std::string;
using std::vector;

bool verify_user_input(string ST, string SS, string PP) {
  string storedTickers = ST;
  string storedShares = SS;
  string storedPurchasePrice = PP;
  string delimiter = " ";

  if (storedTickers.length() == 0 || storedShares.length() == 0 || storedPurchasePrice.length() == 0) return false;

  vector<string> user_tickers;
  vector<string> user_shares;
  vector<string> user_PP;


  size_t pos = 0;
  std::string token;

  while ((pos = storedTickers.find(delimiter)) != std::string::npos) {
      token = storedTickers.substr(0, pos);
      //std::cout << token << std::endl;
      user_tickers.push_back(token);
      storedTickers.erase(0, pos + delimiter.length());
  }
  user_tickers.push_back(storedTickers);

  size_t pos_2 = 0;
  std::string token_2;

  while ((pos_2 = storedShares.find(delimiter)) != std::string::npos) {
      token_2 = storedShares.substr(0, pos_2);
      //std::cout << token << std::endl;
      user_shares.push_back(token_2);
      storedShares.erase(0, pos_2 + delimiter.length());
  }
  user_shares.push_back(storedShares);

  size_t pos_3 = 0;
  std::string token_3;

  while ((pos_3 = storedPurchasePrice.find(delimiter)) != std::string::npos) {
      token_3 = storedPurchasePrice.substr(0, pos_3);
      //std::cout << token << std::endl;
      user_PP.push_back(token_3);
      storedPurchasePrice.erase(0, pos_3 + delimiter.length());
  }
  user_PP.push_back(storedPurchasePrice);

  if (user_tickers.size() != user_shares.size()) {
    return false;
  } 
  if (user_shares.size() != user_PP.size()) {
    return false;
  } 

  std::ifstream file("tickers.txt");

  int ticker_count = 0;
  int shares_count = 0;
  int prices_count = 0;

  bool ticker_verify = false;
  bool shares_verify = false;
  bool prices_verify = false;
  //bool

  //Verify Tickers
  for (auto tick : user_tickers) {
    std::ifstream file("tickers.txt");
    std::string str;
    while (std::getline(file, str)) {
      if (str == tick) {
        cout << str << std::endl;
        ticker_count++;
      }
    }
  }

  //Verify Shares
  for (auto share : user_shares) {

    std::locale loc;
    std::string str=share;

    for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
    {
      if (std::isalpha(*it,loc)) {
        shares_count++;
      }
    }
  }

  //Verify Purchase Prices
  for (auto price : user_PP) {

    std::locale loc;
    std::string str=price;

    for (std::string::iterator it=str.begin(); it!=str.end(); ++it)
    {
      if (std::isalpha(*it,loc)) {
        prices_count++;
      }
    }
  }

  if (ticker_count == user_tickers.size()) {
    ticker_verify = true;
  }
  if (shares_count == 0){
    shares_verify = true;
  }
  if (prices_count == 0){
    prices_verify = true;
  }

  if (ticker_verify && shares_verify && prices_verify) {
    return true;
  } else {
    return false;
  }
}

int main(){
  // main window creation
  sf::RenderWindow window(sf::VideoMode(960, 540), "Portfolio Calculator", sf::Style::Close | sf::Style::Titlebar);
  window.setFramerateLimit(60);

  // GLOBAL ITEMS BEGIN
  // setting background for main
  sf::Texture background;
  background.loadFromFile("backGradient.jpg");
  sf::Sprite backSprite(background);

  // title text
  sf::Font OpenSans;
  OpenSans.loadFromFile("OpenSans.ttf");
  sf::Text mainTitle;
  mainTitle.setFont(OpenSans);
  mainTitle.setString("PCalc");
  mainTitle.setCharacterSize(24);
  mainTitle.setFillColor(sf::Color::Black);
  mainTitle.setPosition(10,10);
  mainTitle.setStyle(sf::Text::Bold);

  sf::RectangleShape titleRec(sf::Vector2f(70,30));
  titleRec.setFillColor(sf::Color::White);
  titleRec.setPosition(10,10);

  // header lines

  sf::RectangleShape headerLine(sf::Vector2f(1, 960));
  headerLine.setPosition(0,60);
  headerLine.setFillColor(sf::Color(224,224,224,200));
  headerLine.rotate(270);

  sf::RectangleShape headerLine2(sf::Vector2f(1, 960));
  headerLine2.setPosition(790,0);
  headerLine2.setFillColor(sf::Color(224,224,224,200));

  Button instructions("Instructions", {150, 40}, 24, sf::Color::White, sf::Color::Black);
  instructions.setFont(OpenSans);
  instructions.setPosition({800, 10});

  Button calculateButton("CALCULATE", {150,75}, 20, sf::Color::White, sf::Color::Black);
  calculateButton.setFont(OpenSans);


  // GLOBAL ITEMS END


  // INSTRUCTIONS ITEMS BEGINS
  Button closeInstructions("CLOSE", {150, 50}, 24, sf::Color::White, sf::Color::Black);
  closeInstructions.setFont(OpenSans);

  // INSTRUCTIONS ITEMS ENDS


  // WELCOME PAGE ITEMS BEGIN
  //main welcome
  sf::Text welcome;
  welcome.setFont(OpenSans);
  welcome.setString("Welcome to Portfolio Calculator!");
  welcome.setCharacterSize(40);
  welcome.setFillColor(sf::Color::White);
  welcome.setPosition(100,70);

  sf::Text enterNameText;
  enterNameText.setFont(OpenSans);
  enterNameText.setString("Enter your name in the box below to begin.");
  enterNameText.setCharacterSize(20);
  enterNameText.setFillColor(sf::Color::White);
  enterNameText.setPosition(200,130);

  //enter name text
  sf::Text nameText;
  nameText.setFont(OpenSans);
  nameText.setString("Name:");
  nameText.setCharacterSize(25);
  nameText.setFillColor(sf::Color::White);
  nameText.setPosition(235,200);

  Textbox nameBox(25,sf::Color::White,true);
  nameBox.setFont(OpenSans);
  nameBox.setPosition({325,200});
  nameBox.setLimit(true, 18);

  sf::Text enteredName;
  enteredName.setFont(OpenSans);
  enteredName.setString("Entered Name:");
  enteredName.setCharacterSize(25);
  enteredName.setFillColor(sf::Color::White);
  enteredName.setPosition(235,300);

  string name;
  sf::Text displayName;
  displayName.setFont(OpenSans);
  displayName.setCharacterSize(25);
  displayName.setFillColor(sf::Color::White);
  displayName.setPosition(420,300);

  Button stock("STOCKS", {150,75}, 25, sf::Color::White, sf::Color::Black);
  stock.setFont(OpenSans);
  

  Button cryptoBUTTON("CRYPTO", {150,75}, 25, sf::Color::White, sf::Color::Black);
  cryptoBUTTON.setFont(OpenSans);
  

  //WELCOME PAGE ITEMS END


  //STOCK PAGE ITEMS BEGIN

  Button tickers_select("Type Tickers:", {150,30}, 20, sf::Color::White, sf::Color::Black);
  tickers_select.setFont(OpenSans);
  tickers_select.setPosition({80,150});

  Button shares_select("Type Shares: ", {150,30}, 20, sf::Color::White, sf::Color::Black);
  shares_select.setFont(OpenSans);
  shares_select.setPosition({80,300});

  Button purchase_price_select("Type Purchase Price:", {150,30}, 15, sf::Color::White, sf::Color::Black);
  purchase_price_select.setFont(OpenSans);
  purchase_price_select.setPosition({80,450});

  Textbox tickers(22,sf::Color::White,false);
  tickers.setFont(OpenSans);
  tickers.setPosition({240,153});

  Textbox shares(20,sf::Color::White,false);
  shares.setFont(OpenSans);
  shares.setPosition({240,303});

  Textbox purchase_price(20,sf::Color::White,false);
  purchase_price.setFont(OpenSans);
  purchase_price.setPosition({240,453});

  sf::Text yourTickers;
  yourTickers.setFont(OpenSans);
  yourTickers.setString("Your Stocks:");
  yourTickers.setCharacterSize(20);
  yourTickers.setFillColor(sf::Color::White);
  yourTickers.setPosition(80,200);

  string storedTickers;
  sf::Text displayTickers;
  displayTickers.setFont(OpenSans);
  displayTickers.setCharacterSize(20);
  displayTickers.setFillColor(sf::Color::White);
  displayTickers.setPosition(200,200);

  sf::Text yourShares;
  yourShares.setFont(OpenSans);
  yourShares.setString("Your Shares:");
  yourShares.setCharacterSize(20);
  yourShares.setFillColor(sf::Color::White);
  yourShares.setPosition(80,350);

  string storedShares;
  sf::Text displayShares;
  displayShares.setFont(OpenSans);
  displayShares.setCharacterSize(20);
  displayShares.setFillColor(sf::Color::White);
  displayShares.setPosition(205,350);


  sf::Text yourPurchasePrice;
  yourPurchasePrice.setFont(OpenSans);
  yourPurchasePrice.setString("Your Purchase Price:");
  yourPurchasePrice.setCharacterSize(20);
  yourPurchasePrice.setFillColor(sf::Color::White);
  yourPurchasePrice.setPosition(80,500);

  string storedPurchasePrice;
  sf::Text displayPurchasePrice;
  displayPurchasePrice.setFont(OpenSans);
  displayPurchasePrice.setCharacterSize(20);
  displayPurchasePrice.setFillColor(sf::Color::White);
  displayPurchasePrice.setPosition(280,500);

  //STOCK PAGE ITEMS END


  // Crypto PAGE ITEMS BEGIN
  Button crypto_select("Type Crypto:", {150,30}, 20, sf::Color::White, sf::Color::Black);
  crypto_select.setFont(OpenSans);
  crypto_select.setPosition({80,150});

  Button amount_select("Type Amount: ", {150,30}, 20, sf::Color::White, sf::Color::Black);
  amount_select.setFont(OpenSans);
  amount_select.setPosition({80,300});

  Button coinPrice_select("Type Purchase Price:", {150,30}, 15, sf::Color::White, sf::Color::Black);
  coinPrice_select.setFont(OpenSans);
  coinPrice_select.setPosition({80,450});

  Textbox crypto(22,sf::Color::White,false);
  crypto.setFont(OpenSans);
  crypto.setPosition({240,153});

  Textbox amount(20,sf::Color::White,false);
  amount.setFont(OpenSans);
  amount.setPosition({240,303});

  Textbox coinPrice(20,sf::Color::White,false);
  coinPrice.setFont(OpenSans);
  coinPrice.setPosition({240,453});

  sf::Text yourCrypto;
  yourCrypto.setFont(OpenSans);
  yourCrypto.setString("Your Crypto:");
  yourCrypto.setCharacterSize(20);
  yourCrypto.setFillColor(sf::Color::White);
  yourCrypto.setPosition(80,200);

  string storedCrypto;
  sf::Text displayCrypto;
  displayCrypto.setFont(OpenSans);
  displayCrypto.setCharacterSize(20);
  displayCrypto.setFillColor(sf::Color::White);
  displayCrypto.setPosition(200,200);

  sf::Text yourAmounts;
  yourAmounts.setFont(OpenSans);
  yourAmounts.setString("Your Amounts:");
  yourAmounts.setCharacterSize(20);
  yourAmounts.setFillColor(sf::Color::White);
  yourAmounts.setPosition(80,350);

  string storedAmounts;
  sf::Text displayAmounts;
  displayAmounts.setFont(OpenSans);
  displayAmounts.setCharacterSize(20);
  displayAmounts.setFillColor(sf::Color::White);
  displayAmounts.setPosition(225,350);


  sf::Text yourCoinPrice;
  yourCoinPrice.setFont(OpenSans);
  yourCoinPrice.setString("Your Purchase Price:");
  yourCoinPrice.setCharacterSize(20);
  yourCoinPrice.setFillColor(sf::Color::White);
  yourCoinPrice.setPosition(80,500);

  string storedCoinPrice;
  sf::Text displayCoinPrice;
  displayCoinPrice.setFont(OpenSans);
  displayCoinPrice.setCharacterSize(20);
  displayCoinPrice.setFillColor(sf::Color::White);
  displayCoinPrice.setPosition(280,500);


  // Crypto PAGE ITEMS END

  // TOTALS PAGE ITEMS BEGIN
  sf::Text totalPageTitle;
  totalPageTitle.setFont(OpenSans);
  totalPageTitle.setCharacterSize(32);
  totalPageTitle.setFillColor(sf::Color::White);
  totalPageTitle.setPosition(225,10);


  sf::Text TotalStockProfits;
  TotalStockProfits.setFont(OpenSans);
  TotalStockProfits.setString("Total Stock Profits: $");
  TotalStockProfits.setCharacterSize(24);
  TotalStockProfits.setFillColor(sf::Color::White);
  TotalStockProfits.setPosition(80,75);

  string tsp;
  sf::Text displayTSP;
  displayTSP.setFont(OpenSans);
  displayTSP.setCharacterSize(24);
  displayTSP.setFillColor(sf::Color::White);
  displayTSP.setPosition(318,75);

  sf::Text TotalCryptoProfits;
  TotalCryptoProfits.setFont(OpenSans);
  TotalCryptoProfits.setString("Total Crypto Profits: $");
  TotalCryptoProfits.setCharacterSize(24);
  TotalCryptoProfits.setFillColor(sf::Color::White);
  TotalCryptoProfits.setPosition(80,225);

  string tcp;
  sf::Text displayTCP;
  displayTCP.setFont(OpenSans);
  displayTCP.setCharacterSize(24);
  displayTCP.setFillColor(sf::Color::White);
  displayTCP.setPosition(330,225);

  sf::Text TotalProfits;
  TotalProfits.setFont(OpenSans);
  TotalProfits.setString("Total Profits: $");
  TotalProfits.setCharacterSize(24);
  TotalProfits.setFillColor(sf::Color::White);
  TotalProfits.setPosition(80,375);

  string tp;
  sf::Text displayTP;
  displayTP.setFont(OpenSans);
  displayTP.setCharacterSize(24);
  displayTP.setFillColor(sf::Color::White);
  displayTP.setPosition(250,375);

  Button outPageButton("Stock Info", {150,30}, 20, sf::Color::White, sf::Color::Black);
  outPageButton.setFont(OpenSans);

  // TOTALS PAGE ITEMS END

  // ERROR PAGE ITEMS BEGIN

  sf::Text errorPageTitle;
  errorPageTitle.setString("ERROR");
  errorPageTitle.setFont(OpenSans);
  errorPageTitle.setCharacterSize(32);
  errorPageTitle.setFillColor(sf::Color::Red);
  errorPageTitle.setPosition(440,10);
  errorPageTitle.setStyle(sf::Text::Bold);

  sf::Text errorPageText;
  errorPageText.setFont(OpenSans);
  errorPageText.setString("INFORMATION TYPED IN INCORRECTLY \nPLEASE READ THE INSTRUCTIONS AGAIN!");
  errorPageText.setCharacterSize(35);
  errorPageText.setFillColor(sf::Color::White);
  errorPageText.setPosition(50,100);


  // ERROR PAGE ITEMS END

  // INSTRUCTIONS PAGE ITEMS BEGIN

  sf::Text instructionPageTitle;
  instructionPageTitle.setString("INSTRUCTIONS");
  instructionPageTitle.setFont(OpenSans);
  instructionPageTitle.setCharacterSize(32);
  instructionPageTitle.setFillColor(sf::Color::White);
  instructionPageTitle.setPosition(350,10);
  instructionPageTitle.setStyle(sf::Text::Bold);

  sf::Text instructionPageText;
  instructionPageText.setFont(OpenSans);
  instructionPageText.setCharacterSize(14);
  instructionPageText.setFillColor(sf::Color::White);

  // INSTRUCTIONS PAGE ITEMS END

  // Output PAGE ITEMS BEGIN

  sf::Text outputPageTitle;
  outputPageTitle.setFont(OpenSans);
  outputPageTitle.setCharacterSize(32);
  outputPageTitle.setFillColor(sf::Color::White);
  outputPageTitle.setPosition(250,10);
  outputPageTitle.setStyle(sf::Text::Bold);

  sf::Text outputPageText;
  outputPageText.setFont(OpenSans);
  outputPageText.setCharacterSize(20);
  outputPageText.setFillColor(sf::Color::White);

  // Output PAGE ITEMS END





  // run welcome once code
  int page = 0;
  int currentPage;
  int WelcomePage = 0;
  int InstructionsPage = 1;
  int StockInput = 2;
  int CryptoInput = 3;
  int TotalPage = 4;
  int OutputPage = 5;
  int ErrorPage = 6;

  //calculate button logic
  bool isVerifiedStock = false;
  bool isVerifiedCrypto = false;
  bool runPyOnce = true;
  bool allStockPresent = false;
  bool allCryptoPresent = false;

  int count = 0;

  // page system to control which is displayed
  while(window.isOpen()){
    sf::Event evnt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == WelcomePage) {
      name = nameBox.getText();
      displayName.setString(name);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == StockInput && tickers.isSelect()){
      storedTickers = tickers.getText();
      displayTickers.setString(storedTickers);
      //cout << storedTickers << std::endl;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == StockInput && shares.isSelect()){
      storedShares = shares.getText();
      displayShares.setString(storedShares);
      //cout << storedShares << std::endl;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == StockInput && purchase_price.isSelect()){
      storedPurchasePrice = purchase_price.getText();
      displayPurchasePrice.setString(storedPurchasePrice);
      //cout << storedPurchasePrice << std::endl;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == CryptoInput && crypto.isSelect()){
      storedCrypto = crypto.getText();
      displayCrypto.setString(storedCrypto);
      //cout << storedCrypto << std::endl;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == CryptoInput && amount.isSelect()){
      storedAmounts = amount.getText();
      displayAmounts.setString(storedAmounts);
      //cout << storedAmounts << std::endl;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && page == CryptoInput && coinPrice.isSelect()){
      storedCoinPrice = coinPrice.getText();
      displayCoinPrice.setString(storedCoinPrice);
      //cout << storedCoinPrice << std::endl;
    }

    if(storedTickers.length() > 0 && storedShares.length() > 0 && storedPurchasePrice.length() > 0){
      allStockPresent = true;
    }

    if(storedCrypto.length() > 0 && storedAmounts.length() > 0 && storedCoinPrice.length() > 0){
      allCryptoPresent = true;
    }


    while(window.pollEvent(evnt)){
      switch(evnt.type){
        case sf::Event::Closed:
          window.close();
        case sf::Event::TextEntered:
          nameBox.typedOn(evnt);
          tickers.typedOn(evnt);
          shares.typedOn(evnt);
          purchase_price.typedOn(evnt);
          crypto.typedOn(evnt);
          amount.typedOn(evnt);
          coinPrice.typedOn(evnt);
          break;

        case sf::Event::MouseMoved: //check for button colors
          //check outputpage button
          if(outPageButton.isMouseOver(window)){
            outPageButton.setBackColor(sf::Color::Blue);
          }
          else{
            outPageButton.setBackColor(sf::Color::White);
          }
          //check instructions button
          if(instructions.isMouseOver(window)){
            instructions.setBackColor(sf::Color::Blue);
          }
          else{
            instructions.setBackColor(sf::Color::White);
          }

          // check closeInstructions button
          if(closeInstructions.isMouseOver(window)){
            closeInstructions.setBackColor(sf::Color::Blue);
          }
          else{
            closeInstructions.setBackColor(sf::Color::White);
          }

          // check stock button
          if(stock.isMouseOver(window)){
            stock.setBackColor(sf::Color::Blue);
          }
          else{
            stock.setBackColor(sf::Color::White);
          }

          // check crypto button on welcome page
          if(cryptoBUTTON.isMouseOver(window)){
            cryptoBUTTON.setBackColor(sf::Color::Blue);
          }
          else{
            cryptoBUTTON.setBackColor(sf::Color::White);
          }


          //check tickers button
          if(tickers_select.isMouseOver(window)){
            tickers_select.setBackColor(sf::Color::Blue);
          }
          else if(tickers.isSelect()){
            tickers_select.setBackColor(sf::Color::Red);
          }
          else{
            tickers_select.setBackColor(sf::Color::White);
          }

          //check shares button
          if(shares_select.isMouseOver(window)){
            shares_select.setBackColor(sf::Color::Blue);
          }
          else if(shares.isSelect()){
            shares_select.setBackColor(sf::Color::Red);
          }
          else{
            shares_select.setBackColor(sf::Color::White);
          }

          //check purchase price button
          if(purchase_price_select.isMouseOver(window)){
            purchase_price_select.setBackColor(sf::Color::Blue);
          }
          else if(purchase_price.isSelect()){
            purchase_price_select.setBackColor(sf::Color::Red);
          }
          else{
            purchase_price_select.setBackColor(sf::Color::White);
          }

          //check crypto button
          if(crypto_select.isMouseOver(window)){
            crypto_select.setBackColor(sf::Color::Blue);
          }
          else if(crypto.isSelect()){
            crypto_select.setBackColor(sf::Color::Red);
          }
          else{
            crypto_select.setBackColor(sf::Color::White);
          }

          //check amount button
          if(amount_select.isMouseOver(window)){
            amount_select.setBackColor(sf::Color::Blue);
          }
          else if(amount.isSelect()){
            amount_select.setBackColor(sf::Color::Red);
          }
          else{
            amount_select.setBackColor(sf::Color::White);
          }

          //check purchase price button
          if(coinPrice_select.isMouseOver(window)){
            coinPrice_select.setBackColor(sf::Color::Blue);
          }
          else if(coinPrice.isSelect()){
            coinPrice_select.setBackColor(sf::Color::Red);
          }
          else{
            coinPrice_select.setBackColor(sf::Color::White);
          }

          //check calculate button
          if(calculateButton.isMouseOver(window)){
            calculateButton.setBackColor(sf::Color::Blue);
          }
          else{
            calculateButton.setBackColor(sf::Color::White);
          }
          break;

        case sf::Event::MouseButtonPressed: //use for button events
          // if(page == ErrorPage){
          //   if(closeInstructions.isMouseOver(window)){
          //     page = StockInput;
          //   }
          // }
          // stock button function welcomepage
          if(stock.isMouseOver(window) && name.length() > 0){
            page = StockInput;
          }
          // crypto button function welcomepage
          else if(cryptoBUTTON.isMouseOver(window) && name.length() > 0){
            page = CryptoInput;
          }
          else if(outPageButton.isMouseOver(window) && page == TotalPage){
            page = OutputPage;
          }
          // instructions button function all pages
          else if(instructions.isMouseOver(window)){
            currentPage = page;
            page = InstructionsPage;
          }
          // closeInstructions button function instructions page
          else if(closeInstructions.isMouseOver(window)){
            page = currentPage;
          }

          // tickers,shares, purchase price button function stockpage
          if(tickers_select.isMouseOver(window)){
            tickers.setSelected(true);
            shares.setSelected(false);
            purchase_price.setSelected(false);
          }

          if(shares_select.isMouseOver(window)){
            shares.setSelected(true);
            tickers.setSelected(false);
            purchase_price.setSelected(false);
          }

          if(purchase_price_select.isMouseOver(window)){
            purchase_price.setSelected(true);
            tickers.setSelected(false);
            shares.setSelected(false);
          }

          // crypto, amounts, and coinprice button function cryptopage
          if(crypto_select.isMouseOver(window)){
            crypto.setSelected(true);
            amount.setSelected(false);
            coinPrice.setSelected(false);
          }

          if(amount_select.isMouseOver(window)){
            amount.setSelected(true);
            crypto.setSelected(false);
            coinPrice.setSelected(false);
          }

          if(coinPrice_select.isMouseOver(window)){
            coinPrice.setSelected(true);
            crypto.setSelected(false);
            amount.setSelected(false);
          }

          if(calculateButton.isMouseOver(window) && (page == StockInput || page == CryptoInput)){
            isVerifiedStock = verify_user_input(storedTickers,storedShares,storedPurchasePrice);
            isVerifiedCrypto = verify_user_input(storedCrypto,storedAmounts, storedCoinPrice);
            if(isVerifiedStock && isVerifiedCrypto && allStockPresent && allCryptoPresent){
              if(runPyOnce) {
                std::ofstream table;
                table.open("ui_output.txt");
                table << storedTickers << std::endl;
                table << storedShares << std::endl;
                table << storedPurchasePrice << std::endl;
                

                table << storedCrypto << std::endl;
                table << storedAmounts << std::endl;
                table << storedCoinPrice << std::endl;
                
                string filename = "stockDriver.py";
                string command = "python ";
                command += filename;
                system(command.c_str());

                std::ifstream f("python_to_ui.txt");
                std::getline(f,tsp);
                std::getline(f,tcp);
                std::getline(f,tp);
                
                runPyOnce = false;
                page = TotalPage;
              }
            }
            else if(isVerifiedStock && allStockPresent){
              if(runPyOnce){
                std::ofstream table;
                table.open("ui_output.txt");
                table << storedTickers << std::endl;
                table << storedShares << std::endl;
                table << storedPurchasePrice << std::endl;

                string filename = "stockDriver.py";
                string command = "python ";
                command += filename;
                system(command.c_str());

                std::ifstream f("python_to_ui.txt");
                std::getline(f,tsp);
                tcp = "0";
                tp = tsp;

                runPyOnce = false;
                page = TotalPage;
              }
            }
            else if(isVerifiedCrypto && allCryptoPresent){
              if(runPyOnce){
                std::ofstream table;
                table.open("ui_output.txt");
                table << " " << std::endl;
                table << " " << std::endl;
                table << " " << std::endl;

                table << storedCrypto << std::endl;
                table << storedAmounts << std::endl;
                table << storedCoinPrice << std::endl;

                string filename = "stockDriver.py";
                string command = "python ";
                command += filename;
                system(command.c_str());

                string bogus_str;

                std::ifstream f("python_to_ui.txt");

                std::getline(f, bogus_str);

                std::getline(f,tcp);
                tsp = "0";
                tp = tcp;
                page = TotalPage;
              }
            }
            else{
              page = ErrorPage;
            }
          }
      }
    }

    if(page == WelcomePage){
      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(headerLine2);
      window.draw(mainTitle);
      window.draw(welcome);
      window.draw(enterNameText);
      window.draw(nameText);
      window.draw(enteredName);

      instructions.drawTo(window);

      nameBox.drawTo(window);
      window.draw(displayName);

      cryptoBUTTON.setPosition({800,300});
      cryptoBUTTON.drawTo(window);

      stock.setPosition({800,150});
      stock.drawTo(window);

      window.display();
    }

    if(page == InstructionsPage){
      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(headerLine2);
      window.draw(mainTitle);

      closeInstructions.setPosition({600, 480});
      closeInstructions.drawTo(window);

      if(name.length() > 0){
        cryptoBUTTON.setPosition({800,300});
        cryptoBUTTON.drawTo(window);

        stock.setPosition({800,150});
        stock.drawTo(window);

      }


      window.draw(instructionPageTitle);

      std::ifstream thisfile;
      std::string theline;
      vector<string> contents;

      thisfile.open("instructions.txt");
      while (std::getline(thisfile, theline))
        contents.push_back(theline);
      thisfile.close();

      int y = 45;
      for (auto line : contents){
        instructionPageText.setString(line);
        y += 20;
        instructionPageText.setPosition(50,y);
        window.draw(instructionPageText);
      }
      window.display();
    }

    if(page == StockInput){
      string stockHeader = name + "'s Stock Portfolio";
      displayName.setString(stockHeader);
      displayName.setPosition(225,10);
      displayName.setCharacterSize(32);

      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(headerLine2);
      window.draw(mainTitle);
      window.draw(displayName);

      instructions.drawTo(window);

      tickers_select.drawTo(window);
      shares_select.drawTo(window);
      purchase_price_select.drawTo(window);

      tickers.drawTo(window);
      shares.drawTo(window);
      purchase_price.drawTo(window);

      window.draw(yourTickers);
      window.draw(yourShares);
      window.draw(yourPurchasePrice);

      window.draw(displayTickers);
      window.draw(displayShares);
      window.draw(displayPurchasePrice);

      cryptoBUTTON.setPosition({800,300});
      cryptoBUTTON.drawTo(window);

      stock.setPosition({800,150});
      stock.drawTo(window);

      calculateButton.setPosition({800,450});
      calculateButton.drawTo(window);

      window.display();
    }

    if(page == CryptoInput){
      string cryptoHeader = name + "'s Crypto Portfolio";
      displayName.setString(cryptoHeader);
      displayName.setPosition(225,10);
      displayName.setCharacterSize(32);

      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(headerLine2);
      window.draw(mainTitle);
      window.draw(displayName);

      instructions.drawTo(window);

      crypto_select.drawTo(window);
      amount_select.drawTo(window);
      coinPrice_select.drawTo(window);

      crypto.drawTo(window);
      amount.drawTo(window);
      coinPrice.drawTo(window);

      window.draw(yourCrypto);
      window.draw(yourAmounts);
      window.draw(yourCoinPrice);

      window.draw(displayCrypto);
      window.draw(displayAmounts);
      window.draw(displayCoinPrice);

      cryptoBUTTON.setPosition({800,300});
      cryptoBUTTON.drawTo(window);

      stock.setPosition({800,150});
      stock.drawTo(window);

      calculateButton.setPosition({800,450});
      calculateButton.drawTo(window);

      window.display();
    }

    if(page == TotalPage){
      runPyOnce = true;
      totalPageTitle.setString(name + "'s Total Portfolio");
      displayTSP.setString(tsp);
      displayTCP.setString(tcp);
      displayTP.setString(tp);

      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(headerLine2);
      window.draw(mainTitle);
      window.draw(totalPageTitle);
      window.draw(TotalStockProfits);
      window.draw(TotalCryptoProfits);
      window.draw(TotalProfits);

      window.draw(displayTSP);
      window.draw(displayTCP);
      window.draw(displayTP);

      instructions.drawTo(window);

      cryptoBUTTON.setPosition({800,300});
      cryptoBUTTON.drawTo(window);

      stock.setPosition({800,150});
      stock.drawTo(window);

      calculateButton.setPosition({800,450});
      calculateButton.drawTo(window);

      outPageButton.setPosition({800,75});
      outPageButton.drawTo(window);
      window.display();
    }

    if(page == ErrorPage){
      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(headerLine2);
      window.draw(mainTitle);

      window.draw(errorPageTitle);
      window.draw(errorPageText);

      cryptoBUTTON.setPosition({800,300});
      cryptoBUTTON.drawTo(window);

      stock.setPosition({800,150});
      stock.drawTo(window);

      // closeInstructions.setPosition({50,450});
      // closeInstructions.drawTo(window);

      window.display();

    }

    if(page == OutputPage){
      outputPageTitle.setString(name + "'s Total Portfolio");

      window.clear(sf::Color::White);
      window.draw(backSprite);
      window.draw(titleRec);
      window.draw(headerLine);
      window.draw(mainTitle);

      instructions.drawTo(window);



      window.draw(outputPageTitle);

      stock.setPosition({300,420});
      cryptoBUTTON.setPosition({500,420});
      
      stock.drawTo(window);
      cryptoBUTTON.drawTo(window);

      int up = 50;
      std::ifstream stockInfoFile;
      std::string infoLine;
      vector<string> stock_contents;
      vector<string> final;
      std::string s;

      stockInfoFile.open("python_to_ui.txt");
      while (std::getline(stockInfoFile, infoLine))
        stock_contents.push_back(infoLine);
      stockInfoFile.close();

      
      stock_contents.erase(stock_contents.begin(), stock_contents.begin() +3);
      


      // for(int i = 0; i < stock_contents.size() - 6; i++){
      //   for(int j = i; j < 6; j++){
      //     s = s + stock_contents.at(j) + "\n";
      //   }
      //   final.push_back(s);
      // }

      // for(string c:final){
      //   cout << c << std::endl;
      // }

      // for (int i = 0; i < final.size(); i++){
      //   outputPageText.setString(stock_contents.at(i));
      //   up += 30;
      //   outputPageText.setPosition(50,up);
      //   if(i%2 == 0){
      //     outputPageText.setPosition(400,up);
      //   }
      //   window.draw(outputPageText);
      // }
      for (int i = 0; i < stock_contents.size(); i++){
        outputPageText.setString(stock_contents.at(i));
        up += 30;
        outputPageText.setPosition(10,up);
        window.draw(outputPageText);
      }


      window.display();
    }


  }
  return 0;
}