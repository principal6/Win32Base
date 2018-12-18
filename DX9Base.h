#pragma once

#ifndef DX9WINDOW_H
#define DX9WINDOW_H

#include "DX9Common.h"

class DX9Base
{
// ���� ����
private:
	int (*mpMainLoop);

// ������ ����
private:
	HWND		mhWnd;
	HINSTANCE	mhInstance;
	MSG			mMSG;

// DX9 ����
private:
	LPDIRECT3D9             mpD3D;
	LPDIRECT3DDEVICE9       mpD3DDevice;

// ���� �Լ�
public:
	DX9Base();
	~DX9Base() {};

	int DX9Base::Create(CINT X, CINT Y, CINT Width, CINT Height);
	int DX9Base::Destroy();

// ������ �Լ�
public:
	HWND DX9Base::CreateWND(const wchar_t* Name,
		CINT X, CINT Y, CINT Width, CINT Height,
		DX9WINDOW_STYLE WindowStyle, DX9COLOR BackColor);
	int DX9Base::Run(int(*pMainLoop)());
	int DX9Base::Halt();

// DX9 �Լ�
public:
	int DX9Base::InitD3D();
	int DX9Base::BeginRender();
	int DX9Base::EndRender();

// Getter
public:
	LPDIRECT3DDEVICE9	DX9Base::GetDevice() { return mpD3DDevice; };
	HINSTANCE			DX9Base::GetInstance() { return mhInstance; };
	HWND				DX9Base::GetHWND() { return mhWnd; };

private:
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

#endif