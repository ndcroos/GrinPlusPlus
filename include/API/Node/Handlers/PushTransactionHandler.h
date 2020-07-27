#pragma once

#include <Config/Config.h>
#include <Core/Validation/TransactionValidator.h>
#include <BlockChain/BlockChainServer.h>
#include <Net/Clients/RPC/RPC.h>
#include <Net/Servers/RPC/RPCMethod.h>
#include <API/Wallet/Owner/Models/Errors.h>
#include <optional>

class PushTransactionHandler : public RPCMethod
{
public:
	PushTransactionHandler(const IBlockChainServerPtr& pBlockChain)
		: m_pBlockChain(pBlockChain) { }
	~PushTransactionHandler() = default;

	RPC::Response Handle(const RPC::Request& request) const final
	{
		if (!request.GetParams().has_value()) {
			return request.BuildError(RPC::Errors::PARAMS_MISSING);
		}

		const Json::Value params = request.GetParams().value();
		if (!params.isArray() || params.size() < 1 || params[0].isNull()) {
			return request.BuildError("INVALID_PARAMS", "Expected 2 parameters: transaction, fluff");
		}

		TransactionPtr pTransaction = std::make_shared<Transaction>(Transaction::FromJSON(params[0]));

		bool fluff = false;
		if (params.size() >=2 && !params[1].isNull()) {
			fluff = params[1].asBool();
		}

		TransactionValidator().Validate(*pTransaction);

		EBlockChainStatus status = m_pBlockChain->AddTransaction(
			pTransaction,
			fluff ? EPoolType::MEMPOOL : EPoolType::STEMPOOL
		);

		if (status == EBlockChainStatus::SUCCESS) {
			Json::Value result;
			result["Ok"] = Json::Value(Json::nullValue);
			return request.BuildResult(result);
		} else {
			return request.BuildError("TX_POOL_ERROR", "Failed to submit transaction to the transaction pool");
		}
	}

	bool ContainsSecrets() const noexcept final { return false; }

private:
	IBlockChainServerPtr m_pBlockChain;
};