#pragma once

#include <Wallet/WalletDB/Models/OutputDataEntity.h>
#include <Crypto/Models/Signature.h>
#include <Core/Models/Fee.h>

namespace ledger {

    // 
    struct TxCommon {

        std::vector<OutputDataEntity> inputs;
	std::vector<OutputDataEntity> outputs;
	//offset;	
	ledger::KernelParameters kernelParameters;

    };

    // 
    struct KernelParameters {
        Fee fee; // 
	uint64_t height; // 
	Signature signature; // 
    };

}