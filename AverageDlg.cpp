
// AverageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Average.h"
#include "AverageDlg.h"
#include "afxdialogex.h"

#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CAverageDlg 대화 상자

CAverageDlg::CAverageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AVERAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAverageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAverageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RUN, &CAverageDlg::OnBnClickedBtnRun)
END_MESSAGE_MAP()


// CAverageDlg 메시지 처리기

BOOL CAverageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAverageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal(); //자식대화상자 호출시 부모대화상자는 대기
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAverageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR CAverageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAverageDlg::OnBnClickedBtnRun()
{
	CString strInputFileName; // 불러올 파일 이름 (chip_00_00.txt,chip_00_01.txt,chip_00_02.txt.....chip_04_13.txt)
	CString strOutputFileName; // 저장할 파일 이름 (chip_00_00_avg.txt,chip_00_01_avg.txt,chip_00_02_avg.txt.....chip_04_13_avg.txt)

	// Chip_00_00 형식 for문으로 텍스트 갯수 정리
	for(long i = 0 ; i < 100; i++)
	{
		for(long j = 0; j < 100; j++)
		{

			if(i < 10)
			{
				if(j < 10)
					strInputFileName.Format(_T("Chip_0%d_0%d"), i, j); //10이하일때 0이 앞에붙음 ex) chip_00_1 (x) chip_00_01(o)
				else
					strInputFileName.Format(_T("Chip_0%d_%d"), i, j);
			}
			else
			{
				if(j < 10)
					strInputFileName.Format(_T("Chip_%d_0%d"), i, j);
				else
					strInputFileName.Format(_T("Chip_%d_%d"), i, j);
			}

			// 파일을 읽는다.
			FILE* fpIn = nullptr;
			fopen_s(&fpIn, CStringA(strInputFileName + _T(".txt")), "r");

			if(fpIn == nullptr) // 파일이 없을시  continue 한다.
				continue;

			strOutputFileName = strInputFileName + _T("_avg"); // 출력할 파일명

			// Average 변수들
			float xAvg[100][4] = { 0,0 }; // 모든변수 0으로 초기화
			float yAvg[100][4] = { 0, 0};
			int avgCount[100][4] = {0,};
			int avgNumber = 0;

			// , 로 구분하여 데이터를 저장
			char data[1000]; // 데이터값 char 선언
			char number[500], x[100], y[100];  // number x축 y축 char 선언
			double a, b;

			while(fscanf_s(fpIn, "%s\n", data, sizeof(data)) != EOF)
			{
				char *delimiter = " ,\n"; // 구분을 , 로 함
				char *pword = NULL;
				char *next = NULL;

				// 입력을 받고 ,\n 로 구분
				while(1)
				{
					pword = strtok_s(data, delimiter, &next); // 순번
					if(pword != NULL)
					{
						strcpy_s(number, sizeof(number), pword);
					}

					while(pword != NULL)
					{
						pword = strtok_s(NULL, delimiter, &next); // x좌표 정보
						if(pword != NULL)
						{							
							strcpy_s(x, sizeof(x), pword);
						}

						pword = strtok_s(NULL, delimiter, &next); // y좌표 정보
						if(pword != NULL)
						{
							strcpy_s(y, sizeof(y), pword);
						}
					}

					if(pword == NULL)
						break;
				}

				// 정보들을 각 변수들에 넣는다.
				
				double a= (float)atof(x);   //char을 double로 변경
				double b = (float)atof(y);  //char을 double로 변경

				if (a <= 1500 && b <= 1500) {
					avgNumber = atoi(number);
					xAvg[avgNumber][0] += a; 
				    yAvg[avgNumber][0] += b;
					avgCount[avgNumber][0]++;
				}
				else if(a > 1500 && b <= 1500)
				{
					avgNumber = atoi(number);
					xAvg[avgNumber][1] += a;
					yAvg[avgNumber][1] += b;
					avgCount[avgNumber][1]++;
				}
				else if (a <= 1500 && b > 1500) {
					avgNumber = atoi(number);
					xAvg[avgNumber][2] += a;
					yAvg[avgNumber][2] += b;
					avgCount[avgNumber][2]++;
				}
				else if (a > 1500 && b > 1500) {
					avgNumber = atoi(number);
					xAvg[avgNumber][3] += a;
					yAvg[avgNumber][3] += b;
					avgCount[avgNumber][3]++;
				}
				//xAvg[avgNumber] += (float)atof(x); 
				//yAvg[avgNumber] += (float)atof(y);
				//avgCount[avgNumber]++;   //  카운팅 
			}

			fclose(fpIn);

			// 파일 오픈
			FILE* fpOut = nullptr;
			fopen_s(&fpOut, CStringA(strOutputFileName + _T(".txt")), "w"); // 파일 쓰기 

			fprintf_s(fpOut, "[BUMP DATA]\n");
			for(int idx = 0; idx <= avgNumber; idx++)
			{
				
				for (int idx_2 = 0; idx_2 <= 3; idx_2++) {
					if (avgCount[idx][idx_2] == 0) // 카운팅x출력x --> 번호가 없는 경우
						continue;

					xAvg[idx][idx_2] /= (float)avgCount[idx][idx_2]; // 평균 계산
					yAvg[idx][idx_2] /= (float)avgCount[idx][idx_2];

					// 파일에 쓴다.					
					fprintf_s(fpOut, "x%d%d_pos=%.3f \ny%d%d_pos=%.3f\n", idx,idx_2, xAvg[idx][idx_2],idx,idx_2, yAvg[idx][idx_2]);
				}
			}

			fclose(fpOut);
		}
	}

	AfxMessageBox(_T("완료")); //완료 창
}
