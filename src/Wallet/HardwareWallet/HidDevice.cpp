#pragma once

#include "Error.h"
#include "HidDevice.h"
#include "Utils.h"

#include <cassert>

namespace ledger {
	Error HID::open() {
		if (!opened_) {
			auto devices = enumerate_devices(vendor_id_);
			if (devices.empty()) {
				return Error::DEVICE_NOT_FOUND;
			}

			path_ = devices.at(0);
			device_ = hid_open_path(path_.c_str());
			if (!device_) {
				return Error::DEVICE_OPEN_FAIL;
			}

			hid_set_nonblocking(device_, true);

			opened_ = true;
		}

		return Error::SUCCESS;
	}

	int HID::send(const std::vector<uint8_t>& data) {
		if (data.empty())
			return -1;

		auto data_new = utils::int_to_bytes(data.size(), 2);
		data_new.insert(data_new.end(), data.begin(), data.end());

		size_t offset = 0;
		size_t seq_idx = 0;
		size_t length = 0;

		while (offset < data_new.size()) {
			// Header: channel (0x0101), tag (0x05), sequence index
			std::vector<uint8_t> header{0x01, 0x01, 0x05};

			auto seq_idx_bytes = utils::int_to_bytes(seq_idx, 2);
			header.insert(header.end(), seq_idx_bytes.begin(), seq_idx_bytes.end());

			std::vector<uint8_t>::iterator it;
			if (data_new.size() - offset < 64 - header.size()) {
				it = data_new.end();
			} else {
				it = data_new.begin() + offset + 64 - header.size();
			}

			std::vector<uint8_t> data_chunk{data_new.begin() + offset, it};
			data_chunk.insert(data_chunk.begin(), header.begin(), header.end());
			data_chunk.insert(data_chunk.begin(), 0x00);

			if (hid_write(device_, data_chunk.data(), data_chunk.size()) == -1)
				return -1;

			length += data_chunk.size();
			offset += 64 - header.size();
			seq_idx += 1;
		}

		return length;
	}

	int HID::recv(std::vector<uint8_t>& rdata) {
		int seq_idx = 0;
		uint8_t buf[64];

		hid_set_nonblocking(device_, false);
		if (hid_read_timeout(device_, buf, sizeof(buf), timeout_ms_) <= 0)
			return -1;
		hid_set_nonblocking(device_, true);

		std::vector<uint8_t> data_chunk(buf, buf + sizeof(buf));

		assert(data_chunk[0] == 0x01);
		assert(data_chunk[1] == 0x01);
		assert(data_chunk[2] == 0x05);

		auto seq_idx_bytes = utils::int_to_bytes(seq_idx, 2);
		assert(seq_idx_bytes[0] == data_chunk[3]);
		assert(seq_idx_bytes[1] == data_chunk[4]);

		auto data_len = utils::bytes_to_int(std::vector<uint8_t>(data_chunk.begin() + 5, data_chunk.begin() + 7));
		std::vector<uint8_t> data(data_chunk.begin() + 7, data_chunk.end());

		while (data.size() < data_len) {
			uint8_t read_bytes[64];
			if (hid_read_timeout(device_, read_bytes, sizeof(read_bytes), 1000) == -1)
				return -1;
			std::vector<uint8_t> tmp(read_bytes, read_bytes + sizeof(read_bytes));
			data.insert(data.end(), tmp.begin() + 5, tmp.end());
		}

		auto sw = utils::bytes_to_int(std::vector<uint8_t>(data.begin() + data_len - 2, data.begin() + data_len));
		rdata = std::vector<uint8_t>(data.begin(), data.begin() + data_len - 2);

		return sw;
	}

	void HID::close() noexcept {
		if (opened_) {
			hid_close(device_);
			opened_ = false;
		}
		hid_exit();
	}

	bool HID::is_open() const {
		return opened_;
	}

	std::vector<std::string> HID::enumerate_devices(unsigned short vendor_id) noexcept {
		std::vector<std::string> devices;

		struct hid_device_info *devs, *cur_dev;

		devs = hid_enumerate(vendor_id, 0x0);
		cur_dev = devs;
		while (cur_dev) {
			if (cur_dev->interface_number == 0 ||
				// MacOS specific
				cur_dev->usage_page == 0xffa0)
			{
				devices.emplace_back(cur_dev->path);
			}
			cur_dev = cur_dev->next;
		}
		hid_free_enumeration(devs);

		return devices;
	}
} // namespace ledger
