#pragma once

#include "Transport.h"
#include "TxCommon.h"
#include "Error.h"

namespace ledger {

    class Ledger {

    public:

        enum APDU : uint8_t {
		CLA = 0xe0,
		INS_GET_APP_CONFIGURATION = 0x01,
		INS_GET_PUBLIC_KEY = 0x02,
		INS_SIGN_SENDER = 0x03,
		INS_SIGN_RECEIVER = 0x04,
		INS_SIGN_FINALIZE = 0x05,
	};

        Ledger();
        ~Ledger();

        Error open();

/*
	std::tuple<Error, std::vector<uint8_t>> get_public_key(uint32_t account, bool confirm = false);
	std::tuple<Error, std::vector<uint8_t>> sign(uint32_t account, const std::vector<uint8_t>& msg);
*/
		
        std::tuple<Error, std::vector<uint8_t>> SignSender(TxCommon txCommon);
 
        std::tuple<Error, std::vector<uint8_t>> SignReceiver(TxCommon txCommon);

        std::tuple<Error, std::vector<uint8_t>> SignFinalize(TxCommon txCommon);

        void close();

    private:

        std::unique_ptr<Transport> transport;

    };

}
