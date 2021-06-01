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
        void SignSender();

        // 
        void SignReceiver();

        // 
        void SignFinalize();

    private:
        Ledger* device;
    };

}