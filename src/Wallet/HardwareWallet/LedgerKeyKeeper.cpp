#include "Ledger.h"
#include "LedgerKeyKeeper.h"
#include <iostream>

namespace ledger {

	LedgerKeyKeeper::LedgerKeyKeeper(){

            this->device = new ledger::Ledger();

        }
	
	LedgerKeyKeeper::~LedgerKeyKeeper(){

        }
	
	int LedgerKeyKeeper::GetNumSlots(){
            // Get device
/*
            auto error = this->device->open();
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
*/
        }
	
	void LedgerKeyKeeper::SignSender(std::vector<OutputDataEntity> input)
	{
            TxCommon txCommon;
            auto ret = this->device->SignSender(txCommon);
            Error error = std::get<0>(ret);
            if(error != ledger::Error::SUCCESS){
                
                std::cout<< "Error: " + error_message(error) + "\n";
            }
        }
	
	void LedgerKeyKeeper::SignReceiver(){
/*
            TxCommon txCommon;
            auto error = this->device->SignReceiver(txCommon);
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
        }
	
	void LedgerKeyKeeper::SignFinalize(){
/*
            TxCommon txCommon;
            auto error = this->device->SignFinalize(txCommon);
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
*/
        }

}