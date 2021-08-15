#pragma once

#include <Wallet/WalletDB/Models/OutputDataEntity.h>
#include <Crypto/Models/Signature.h>
#include <Core/Models/Fee.h>

namespace ledger {

    // 
    typedef struct {
        Fee fee; // 
	uint64_t height; // 
	Signature signature; // 
    } KernelParameters;


    // 
    typedef struct {

        std::vector<OutputDataEntity> inputs;
	std::vector<OutputDataEntity> outputs;
	//offset;	
	KernelParameters kernelParameters;

    } TxCommon;

}