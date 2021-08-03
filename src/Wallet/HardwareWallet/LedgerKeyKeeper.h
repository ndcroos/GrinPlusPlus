#pragma once

#include "KeyKeeper.h"
#include "Ledger.h"
#include "Error.h"

namespace ledger {

    class LedgerKeyKeeper : public KeyKeeper
    {
    public:

        LedgerKeyKeeper();

        ~LedgerKeyKeeper();

        // 
        int GetNumSlots();

        // 
        void SignSender(std::vector<OutputDataEntity> input);

        // 
        void SignReceiver();

        // 
        void SignFinalize();

    private:

        Ledger* device;

    };

}