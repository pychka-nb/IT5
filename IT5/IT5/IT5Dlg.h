
// IT5Dlg.h: файл заголовка
//

#pragma once
#include <vector>
#include <iostream>
#include <time.h>
#include "Drawer.h"
typedef struct cmplx { float real; float image; };

// Диалоговое окно CIT5Dlg
class CIT5Dlg : public CDialogEx
{
// Создание
public:
	CIT5Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IT5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double A1;
	double A2;
	double A3;
	double t01;
	double t02;
	double t03;
	double S1;
	double S2;
	double S3;
	int N;
	double fd;
	Drawer
		graph1,
		graph2;
	double FindMin(vector<double> data, int N);
	double FindMax(vector<double> data, int N);
	vector <double> Sign;
	vector <double> keys;
	vector <double> Ampl;
	vector <double> AmplN;
	vector <double> keys1;
	vector <double> phi;
	vector <double> SignNew;
	vector <double> buff;
	vector <double> SignBuff;
	vector <double> SignBuff1;
	void CreateSignal();
	double d;
	void Fienup();
	struct cmplx* data = new struct cmplx[N];
	struct cmplx* data1 = new struct cmplx[N];
	struct cmplx* data2 = new struct cmplx[N];
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
