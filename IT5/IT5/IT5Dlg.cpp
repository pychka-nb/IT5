
// IT5Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "IT5.h"
#include "IT5Dlg.h"
#include "afxdialogex.h"
#include<algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Pi 3.1415926535
// Диалоговое окно CIT5Dlg



CIT5Dlg::CIT5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IT5_DIALOG, pParent)
	, A1(4)
	, A2(2)
	, A3(3.5)
	, t01(150)
	, t02(380)
	, t03(750)
	, S1(3)
	, S2(2)
	, S3(3)
	, N(1024)
	, fd(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIT5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT2, A2);
	DDX_Text(pDX, IDC_EDIT3, A3);
	DDX_Text(pDX, IDC_EDIT4, t01);
	DDX_Text(pDX, IDC_EDIT5, t02);
	DDX_Text(pDX, IDC_EDIT6, t03);
	DDX_Text(pDX, IDC_EDIT7, S1);
	DDX_Text(pDX, IDC_EDIT8, S2);
	DDX_Text(pDX, IDC_EDIT9, S3);
	DDX_Text(pDX, IDC_EDIT11, N);
	DDX_Text(pDX, IDC_EDIT10, fd);
}

BEGIN_MESSAGE_MAP(CIT5Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CIT5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CIT5Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CIT5Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CIT5Dlg

BOOL CIT5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок
	graph1.Create(GetDlgItem(IDC_SIGN)->GetSafeHwnd());
	graph2.Create(GetDlgItem(IDC_SPECTRE)->GetSafeHwnd());
	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CIT5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CIT5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

double CIT5Dlg::FindMin(vector <double> data, int N)
{
	double min = data[0];
	for (int i = 0; i < N; i++)
	{
		if (min > data[i])
			min = data[i];
	}
	return min;
}
double CIT5Dlg::FindMax(vector <double> data, int N)
{
	double max = data[0];
	for (int i = 0; i < N; i++)
	{
		if (max < data[i])
			max = data[i];
	}
	return max;
}
/*Алгоритм БПФ*/
void fourea(struct cmplx* data, int n, int is)
{
	int i, j, istep;
	int m, mmax;
	float r, r1, theta, w_r, w_i, temp_r, temp_i;
	float pi = 3.1415926f;

	r = pi * is;
	j = 0;
	for (i = 0; i < n; i++)
	{
		if (i < j)
		{
			temp_r = data[j].real;
			temp_i = data[j].image;
			data[j].real = data[i].real;
			data[j].image = data[i].image;
			data[i].real = temp_r;
			data[i].image = temp_i;
		}
		m = n >> 1;
		while (j >= m) { j -= m; m = (m + 1) / 2; }
		j += m;
	}
	mmax = 1;
	while (mmax < n)
	{
		istep = mmax << 1;
		r1 = r / (float)mmax;
		for (m = 0; m < mmax; m++)
		{
			theta = r1 * m;
			w_r = (float)cos((double)theta);
			w_i = (float)sin((double)theta);
			for (i = m; i < n; i += istep)
			{
				j = i + mmax;
				temp_r = w_r * data[j].real - w_i * data[j].image;
				temp_i = w_r * data[j].image + w_i * data[j].real;
				data[j].real = data[i].real - temp_r;
				data[j].image = data[i].image - temp_i;
				data[i].real += temp_r;
				data[i].image += temp_i;
			}
		}
		mmax = istep;
	}
	if (is > 0)
		for (i = 0; i < n; i++)
		{
			data[i].real /= (float)n;
			data[i].image /= (float)n;
		}

}
/*Ф-ция, создающая полигармонический сигнал*/
void CIT5Dlg::CreateSignal()
{
	for (int i = 0; i < N; i++)
	{
		Sign.push_back(A1 * exp(-pow(i / fd - t01, 2) / (2 * pow(S1, 2))) + A2 * exp(-pow(i / fd - t02, 2) / (2 * pow(S2, 2))) + A3 * exp(-pow(i / fd - t03, 2) / (2 * pow(S3, 2))));
	}
}

void CIT5Dlg::Fienup() {
	double aFi;
	for (int i = 0; i < N; i++) {
		aFi = (2.0 * Pi) * rand() / RAND_MAX;
		phi.push_back(aFi);
	}
		for (int i = 0; i < N; i++) {//добавляем фазу
			data1[i].real = Ampl[i] * cos(phi[i]);
			data1[i].image = Ampl[i] * sin(phi[i]);
		}
		
		fourea(data1, N, -1);//обратное преобразование Фурье(переход в временную область)
		SignNew.clear();
		for (int i = 0; i < N; i++) {//применение условий
			if (data1[i].real < 0) {
				data1[i].real = 0;
			}
			SignNew.push_back(data1[i].real);
		}
		do
		{
			buff.clear();
			for (int i = 0; i < N; i++) {
				buff.push_back(SignNew[i]);//сигнал на предыдущем шаге
			}
			for (int i = 0; i < N; i++)
			{
				//keys.push_back(i / fd);
				data2[i].real = SignNew[i];
				data2[i].image = 0.;
			}
			fourea(data2, N, 1);
			for (int i = 0; i < N; i++)//подменяем модуль спектра на истинный
			{
				double k = (sqrt(data2[i].real * data2[i].real + data2[i].image * data2[i].image) / Ampl[i]);
				data2[i].real = data2[i].real / k;
				data2[i].image = data2[i].image / k;
			}
			fourea(data2, N, -1);
			SignNew.clear();
			for (int i = 0; i < N; i++) {//применение условий
				if (data2[i].real < 0) {
					data2[i].real = 0;
				}
				SignNew.push_back(data2[i].real);
			}
			
			 d = 0;
			for (int j = 0; j < N; j++){
				d += (SignNew[j] - buff[j]) * (SignNew[j] - buff[j]);
			}
			d = d / N;
		} while (d > 0.00000001);
		
		
}

void CIT5Dlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	srand(time(NULL));
	UpdateData(TRUE);
	graph1.DrawW();
	graph2.DrawW();
	Sign.clear();
	keys.clear();
	Ampl.clear();
	keys1.clear();
	CreateSignal();
	for (int i = 0; i < N; i++)
	{
		keys.push_back(i / fd);
		data[i].real = Sign[i];
		data[i].image = 0.;
	}

	double xmax = (N - 1) / fd,
		ymax = FindMax(Sign, N),
		ymin = FindMin(Sign, N);
	graph1.DrawOne(Sign, 0, xmax, ymin, ymax, keys);

	fourea(data, N, 1);
	for (int i = 0; i < N; i++)
	{
		Ampl.push_back(sqrt(data[i].real * data[i].real + data[i].image * data[i].image));
		keys1.push_back(fd * i / N);
	}
	ymax = FindMax(Ampl,N);
	graph2.DrawOne(Ampl, 0, fd, 0, ymax, keys1);
	Fienup();
	xmax = (N - 1) / fd;
	ymax = FindMax(Sign, N);	
		ymin = FindMin(Sign, N);
	graph1.DrawW();
	graph1.DrawTwo(Sign, SignNew, 0, xmax, ymin, ymax, keys, keys);
	//graph1.DrawW();
	//graph1.DrawTwo(Sign,SignNew, 0, xmax, ymin, ymax, keys,keys);
	phi.clear();
	//SignNew.clear();
	/*Sign.clear();
	keys.clear();
	Ampl.clear();
	keys1.clear();*/
}


void CIT5Dlg::OnBnClickedButton2()
{
	// TODO: добавьте свой код обработчика уведомлений
	reverse(SignNew.begin(), SignNew.end());
	double xmax = (N - 1) / fd,
	ymax = FindMax(Sign, N),
	ymin = FindMin(Sign, N);
	graph1.DrawW();
	graph1.DrawTwo(Sign, SignNew, 0, xmax, ymin, ymax, keys, keys);
	
}


void CIT5Dlg::OnBnClickedButton3()
{
	// TODO: добавьте свой код обработчика уведомлений
	double error = 10;
	SignBuff.clear();
	SignBuff1.clear();
	for (int i = 0; i < N; i++)
	{
		SignBuff1.push_back(SignNew[i]);
		SignBuff.push_back(SignNew[i]);
	}
	for (int j = 0; j < N; j++)
	{
		double b = 0;
		// сдвигаем график на один отсчет
		for (int i = 0; i < (N - 1); i++)
		{
			SignBuff1[i] = SignBuff[i + 1];
			b += (SignBuff1[i] - Sign[i]) * (SignBuff1[i] - Sign[i]); 
		}
		SignBuff1[N - 1] = SignBuff[0];
		b += (SignBuff1[N - 1] - Sign[N - 1]) * (SignBuff1[N - 1] - Sign[N - 1]);
		b /= N;

		for (int i = 0; i < N; i++)
		{
			SignBuff[i] = SignBuff1[i];
		}
		
		if (b < error)
		{
			error = b;
			for (int i = 0; i < N; i++)
			{
				SignNew[i] = SignBuff1[i];
			}
		}
	}
	double xmax = (N - 1) / fd,
		ymax = FindMax(Sign, N),
		ymin = FindMin(Sign, N);
	graph1.DrawW();
	graph1.DrawTwo(Sign, SignNew, 0, xmax, ymin, ymax, keys, keys);
}
