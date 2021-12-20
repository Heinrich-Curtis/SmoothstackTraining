#ifndef TRANSACTION_H
#define TRANSACTION_H
/*
 *	Class that encapsulates a transaction, which is either a credit or debit
 *	and an amount
 */
#include <string>
#include <vector>



class Transaction{
	public:
	enum class TrType{ 
		DEBIT = 0,
		CREDIT = 1	
	};

		Transaction(TrType type, int amount){
			m_type = type;
			m_amount = amount;
			m_effectiveDate = setEffectiveDate();
		}
		
		void setType(TrType type){
			m_type = type;
		}
		
		TrType getType(){
			return m_type;
		}
		
		void setAmount(int amount){
			m_amount = amount;
		}

		int getAmount(){
			return m_amount;
		}
		std::string printType(){
			if (m_type == TrType::DEBIT){
				return "debit";
			}
			else return "credit";
		}
		//dates the transaction. Mostly for viewing now, but this
		//probably be turned into some numeric type later some we
		//can do things like search for all transactions in a date
		//range or something
		std::string setEffectiveDate(){
			std::string dateString, monString, yearString;
			time_t rawTime;
			struct tm* timeinfo;
			time(&rawTime);
			timeinfo = localtime(&rawTime);
			dateString = asctime(timeinfo);
			monString = dateString.substr(4,6);
			yearString = dateString.substr(19,5);
			dateString = monString + yearString;
			return dateString;
		}

		std::string getEffectiveDate(){
			return m_effectiveDate;
		}
	private:

		TrType m_type;
		//note the amount is an int, it should always internally be the amount
		//of cents to avoid floating point fuckery, and only represented
		//in dollars-and-cents notation when presented to a user
		int m_amount;
		std::string m_effectiveDate;

	
};

#endif
