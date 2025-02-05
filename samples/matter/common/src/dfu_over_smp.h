/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#pragma once

#include <platform/CHIPDeviceLayer.h>

#include <zephyr/kernel.h>

typedef void (*DFUOverSMPRestartAdvertisingHandler)(void);

class DFUOverSMP {
public:
	void Init(DFUOverSMPRestartAdvertisingHandler startAdvertisingCb);
	void ConfirmNewImage();
	void StartServer();
	void StartBLEAdvertising();
	bool IsEnabled() { return mIsEnabled; }

private:
	friend DFUOverSMP &GetDFUOverSMP(void);

	static int UploadConfirmHandler(uint32_t offset, uint32_t size, void *arg);
	static void OnBleConnect(bt_conn *conn, uint8_t err);
	static void OnBleDisconnect(bt_conn *conn, uint8_t reason);
	static void ChipEventHandler(const chip::DeviceLayer::ChipDeviceEvent *event, intptr_t arg);

	bool mIsEnabled;
	bool mIsAdvertisingEnabled;
	bt_conn_cb mBleConnCallbacks;
	k_work mFlashSleepWork;
	k_work mFlashWakeUpWork;
	DFUOverSMPRestartAdvertisingHandler restartAdvertisingCallback;

	static DFUOverSMP sDFUOverSMP;
};

inline DFUOverSMP &GetDFUOverSMP(void)
{
	return DFUOverSMP::sDFUOverSMP;
}
