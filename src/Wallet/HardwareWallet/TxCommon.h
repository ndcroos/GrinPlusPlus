#pragma once

namespace ledger {
	struct TxCommon {

		std::vector<OutputDataEntity> inputs;
		std::vector<OutputDataEntity> outputs;
		//offset;	
		//kernelParameters;

	}

	struct KernelParameters {
		fee;
		height;
		signature;
	}

}