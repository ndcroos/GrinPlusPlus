#pragma once

namespace ledger {

    class KeyKeeper 
    {
    public:
/*
        KeyKeeper();
        ~KeyKeeper();
*/

        int GetNumSlots();
        void SignSender();
        void SignReceiver();
        void SignFinalize();

    private:

    };

}