#include<string>
#include<chrono>
#include<ctime>
#include<fstream>
#include<sstream>
#include<iostream>
#include"dateFormater.h"
 
class Account {
  private:
    std::string _username = "";
    std::string _password = "";
    std::string _dateOfCreation = "";
  public:

    //Konstruktory
    Account(){
        _username = "";
        _password = "";
        _dateOfCreation = currentDate();
    }
 
    Account(std::string username, std::string password){
        _username = username;
        _password = password;
        _dateOfCreation = currentDate();
    }
 
    Account(std::string username, std::string password, std::string dateOfCreation){
        _username = username;
        _password = password;
        _dateOfCreation = dateOfCreation;
    }
 
    //Funkcje dostêpowe
    std::string& Username(){
        return this->_username;
    }
 
    std::string& Password(){
        return this->_password;
    }
 
    std::string& DateOfCreation(){
        return this->_dateOfCreation;
    }
 
    const std::string& Username() const {
        return this->_username;
    }

    const std::string& Password() const {
        return this->_password;
    }

    const std::string& DateOfCreation() const {
        return this->_dateOfCreation;
    }
};
 
class AccInterface {
  private:
    Account currentUser;
 
  public:
    //Metoda odpowiadaj¹ca za sprawdzenie czy podane dane istniej¹ w podanym zbiorze danych
    bool checkData(const std::string fileName, const int dataType, const std::string wantedString){
        std::ifstream fin;
        fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try{
            fin.open(fileName);
 
            std::string fileLine = "";
            std::string currentString = "";
 
            switch(dataType){
            case 1:
                while(std::getline(fin, fileLine)){
                    std::stringstream sin(fileLine);
 
                    sin >> currentString;
                    if(currentString == wantedString){
                        return true;
                    }
                }
                break;
            case 2:
                while(std::getline(fin, fileLine)){
                    std::stringstream sin(fileLine);
 
                    std::string ignoreMe = "";
                    sin >> ignoreMe;
 
                    sin >> currentString;
                    if(currentString == wantedString){
                        return true;
                    }
                }
                break;
            }
 
            fin.close();
        }
        catch(std::ifstream::failure const&){
            return false;
        }
        return false;
    }

    //Metoda odpowiadaj¹ca za zapisanie danych przekazanego konta do podanego zbioru danych
    bool inputData(const std::string fileName, const Account& acc) {
        std::ofstream fout;
        fout.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        try
        {
            fout.open(fileName, std::ios_base::app);
            fout << acc.Username() << ' ' << acc.Password() << ' ' << acc.DateOfCreation() << std::endl;
            fout.close();
        }
        catch (std::ofstream::failure const&)
        {
            std::cerr << "Blad strumienia plikow";
            return false;
        }
        return true;
    }

    //Metoda narzêdna metod inputData oraz checkData, nadzoruje proces tworzenia konta i obs³uguje ewentualne problemy 
    bool CreateAccount(const std::string fileName, const std::string username, const std::string password){
        if(!checkData(fileName, 1, username)){
            Account tempAcc(username, password);
            if (inputData(fileName, tempAcc)) {
                return true;
            }
            else {
                return false;
            }
        }
        else{
            return false;
        }
        return false;
    }

    bool logOnAccount(const std::string fileName, const std::string username, const std::string password) {
        if (checkData(fileName, 1, username) && checkData(fileName, 2, password)) {
            currentUser.Username() = username;
            return true;
        }
        else {
            return false;
        }
    }
};