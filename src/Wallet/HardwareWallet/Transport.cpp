#include "Error.h"
#include "HidDevice.h"
#include "Transport.h"

namespace ledger {

    Transport::Transport(TransportType type) {
	switch (type) {
            case TransportType::HID:
		comm_ = std::make_unique<HID>();
		break;
	}
    }

	Error Transport::open() {
		return comm_->open();
	}

	std::tuple<ledger::Error, std::vector<uint8_t>> Transport::exchange(uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, const std::vector<uint8_t> &cdata) {
		int length = this->send(cla, ins, p1, p2, cdata);
		if (length < 0)
			return {Error::DEVICE_DATA_SEND_FAIL, {}};

		std::vector<uint8_t> buffer;
		int sw = this->recv(buffer);
		if (sw < 0)
			return {Error::DEVICE_DATA_RECV_FAIL, {}};

		if (sw != 0x9000)
			return {Error::APDU_INVALID_CMD, {}};

		return {Error::SUCCESS, buffer};
	}

	void Transport::close() noexcept {
		return comm_->close();
	}

	int Transport::send(uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, const std::vector<uint8_t> &cdata) {
		if (!comm_->is_open())
			return -1;

		auto header = apdu_header(cla, ins, p1, p2, cdata.size());
		header.insert(header.end(), cdata.begin(), cdata.end());
		return comm_->send(header);
	}

	int Transport::recv(std::vector<uint8_t> &rdata) {
		if (!comm_->is_open())
			return -1;

		return comm_->recv(rdata);
	}

	std::vector<uint8_t> Transport::apdu_header(uint8_t cla, uint8_t ins, uint8_t p1, uint8_t p2, uint8_t lc) {
		return std::vector<uint8_t>{cla, ins, p1, p2, lc};
	}

} // namespace ledger
