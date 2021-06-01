#pragma once

namespace ledger {
	struct TxMutualInfo {

		std::vector<OutputDataEntity> inputs;
		std::vector<OutputDataEntity> outputs;
		//offset;	
		//kernelParameters;

	}
}