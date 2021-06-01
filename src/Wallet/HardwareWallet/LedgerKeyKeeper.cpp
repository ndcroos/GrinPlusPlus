#include "Ledger.h"
#include "LedgerKeyKeeper.h"

namespace ledger {

	LedgerKeyKeeper::LedgerKeyKeeper(){
            this->device = new ledger::Ledger();
        }
	
	LedgerKeyKeeper::~LedgerKeyKeeper(){

        }
	
	int LedgerKeyKeeper::GetNumSlots(){
            // Get device
            auto error = dev->open();
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
        }
	
	void LedgerKeyKeeper::SignSender(
		std::vector<OutputDataEntity> inputs,
		    
        )
	{
            // Get device
            auto error = dev->SignSender();
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
        }
	
	void LedgerKeyKeeper::SignReceiver(){
            // Get device
            auto error = dev->SignReceiver();
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
        }
	
	void LedgerKeyKeeper::SignFinalize(){
            // Get device
            auto error = dev->SignFinalize();
            if(error != ledger::Error::SUCCESS){
                std::cout<< "Error: " + error_message(error) + "\n";
            }
        }

}