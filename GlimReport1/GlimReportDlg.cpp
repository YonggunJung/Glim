
// GlimReportDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimReport.h"
#include "GlimReportDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int nRadius = rand() % 20 + 10;

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

// CGlimReportDlg 대화 상자

//1. 이미지를 표시할 수 있는 다이얼로그를 생성합니다.
//2. 시작좌표(x1, y1), 종료좌표(x2, y2)를 입력 받을 수 있는 UI를 생성합니다.
CGlimReportDlg::CGlimReportDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMREPORT_DIALOG, pParent)
	, sx(0)
	, sy(0)
	, ex(0)
	, ey(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, sx);
	DDX_Text(pDX, IDC_EDIT_NUM2, sy);
	DDX_Text(pDX, IDC_EDIT_NUM3, ex);
	DDX_Text(pDX, IDC_EDIT_NUM4, ey);
}

BEGIN_MESSAGE_MAP(CGlimReportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGlimReportDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CGlimReportDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGlimReportDlg::OnBnClickedBtnAction)
END_MESSAGE_MAP()


// CGlimReportDlg 메시지 처리기

BOOL CGlimReportDlg::OnInitDialog()
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

void CGlimReportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimReportDlg::OnPaint()
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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimReportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 3. Draw 버튼 클릭시(x1, y1) 좌표를 중심으로하는 랜덤한 크기의 원을 그립니다.
void CGlimReportDlg::OnBnClickedBtnDraw()
{
	if (m_image != NULL) {
		delete m_image;
		OnBnClickedBtnDraw();
	}
		
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();

	UpdateData(TRUE);

	// 만든 이미지의 첫번째 포인터 값을 가져옴
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0, sizeof(unsigned char) * nWidth * nHeight);
	static int nSttX = sx;
	static int nSttY = sy;
	int nGray = 80;
	drawCircle(fm, sx++, sy++, nRadius, nGray);
	//int nRadius = rand() % 50 + 10;
	// 화면에 띄워주는 함수
	UpdateDisplay();
	
}

// Action 버튼 클릭시(x1, y1) 좌표에서(x2, y2) 좌표로 일정 픽셀 간격으로 원을 이동시키며, 
// 이동할 때마다 실행파일이 위치한 폴더 내의 image 폴더에 bmp 또는 jpg(jpeg) 포맷으로 저장합니다.
void CGlimReportDlg::OnBnClickedBtnAction()
{
	// 원 이동 루프를 시작하거나 다른 적절한 위치에서 moveCir 호출
	while (sx != ex || sy != ey) {
		moveCir();
		Sleep(10);

		if (sy % 50 == 0 || sy +1 == ey || sx +1 == ex) {
			// 이미지 저장
			CString g_strFileImage;
			g_strFileImage.Format(_T("res\\save%d, %d.bmp"), sx, sy);
			m_image.Save(g_strFileImage);
		}
	}
}

//Open 버튼 클릭시 탐색기 창을 통해 이미지를 1개를 선택해서 불러오고 다이얼로그에 출력합니다.
// 이 때 출력된 원의 중심 좌표에 X 모양을 그리고 좌표값을 같이 표시합니다.
void CGlimReportDlg::OnBnClickedBtnOpen()
{
	if (m_image != NULL) {
		m_image.Destroy();
	}

	// 파일 다이얼로그 설정
	CFileDialog dlg(TRUE, _T("*.bmp;*.jpg;*.jpeg"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg||"));

	if (dlg.DoModal() == IDOK) {
		CString filePath = dlg.GetPathName();

		// 이미지 로드
		if (m_image.Load(filePath) == S_OK) {
			UpdateDisplay(); // 이미지를 표시

			// 원 찾기
			drawCenter(); // 선택된 이미지에서 원 찾기
		}
	}
	
}

//void CGlimReportDlg::imgLoad()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	 // 이미지 로드 및 표시
//	
//}

// 이 때 출력된 원의 중심 좌표에 X 모양을 그리고 좌표값을 같이 표시합니다.
void CGlimReportDlg::drawCenter()
{
	int width = m_image.GetWidth();
	int height = m_image.GetHeight();

	// 가장자리를 찾기 위한 좌표 계산
	int top = height, bottom = 0;
	int left = width, right = 0;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			COLORREF pixel = m_image.GetPixel(x, y);
			// 회색 픽셀 찾기
			if (GetRValue(pixel) == 80) {
				// 픽셀이 회색인 경우
				if (y < top) top = y;
				if (y > bottom) bottom = y;
				if (x < left) left = x;
				if (x > right) right = x;
			}
		}
	}

	// 원의 중심과 반지름 계산
	if (left < right && top < bottom) {
		int x_center = (left + right) / 2 +1;
		int y_center = (top + bottom) / 2 +1;
		double r = max((right - left) / 2.0, (bottom - top) / 2.0);

		// GDI를 사용하여 원 그리기
		CDC* pDC = GetDC();
		pDC->Ellipse(x_center - (int)r, y_center - (int)r, x_center + (int)r, y_center + (int)r); // 원 그리기
		pDC->SetPixel(x_center, y_center, RGB(0, 255, 0)); // 중심 표시

		// X 모양 그리기
		int xSize = nRadius / 4; // X 모양의 크기
		pDC->MoveTo(x_center - xSize, y_center - xSize);
		pDC->LineTo(x_center + xSize, y_center + xSize); // 대각선 1
		pDC->MoveTo(x_center - xSize, y_center + xSize);
		pDC->LineTo(x_center + xSize, y_center - xSize); // 대각선 2

		// 좌표 텍스트 표시
		CString coordText;
		coordText.Format(_T("(%d, %d)"), x_center, y_center);
		pDC->TextOut(x_center + 5, y_center, coordText); // 좌표 텍스트 표시
		ReleaseDC(pDC);
	}
	else {
		AfxMessageBox(_T("이미지에서 원을 찾을 수 없습니다."));
	}
}

void CGlimReportDlg::UpdateDisplay() {
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

//일정 픽셀 간격으로 원을 이동
void CGlimReportDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray) {
	int nCenterX = sx;
	int nCenterY = sy;
	int nPitch = m_image.GetPitch();		// 한 행의 사이즈

	for (int j = nCenterY - nRadius; j <= nCenterY + nRadius; j++) {
		for (int i = nCenterX - nRadius; i <= nCenterX + nRadius; i++) {
			// 원의 방정식으로 내부 체크
			if ((i - nCenterX) * (i - nCenterX) + (j - nCenterY) * (j - nCenterY) <= nRadius * nRadius) {
				fm[j * nPitch + i] = nGray; // 픽셀 색상 설정
			}
		}
	}
}

// 사각형에서 원을 그릴때 원이 맞는지 확인하는거
//bool CGlimReportDlg::isInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius) {
//	bool bRet = false;
//	double dX = x - nCenterX;
//	double dY = y - nCenterY;
//	double dDist = dX * dX + dY * dY;
//
//	if (dDist < nRadius * nRadius) {
//		bRet = true;
//	}
//
//	return bRet;
//}

void CGlimReportDlg::moveCir() {
	static int nSttX = sx;
	static int nSttY = sy;
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();		// 한 행의 사이즈
	//int nRadius = rand() % 50 + 5;
	// 만든 이미지의 첫번째 포인터 값을 가져오겠다.
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// 원의 이동 거리 계산
	double deltaX = (ex - sx) > 0 ? 1 : -1;
	double deltaY = (ey - sy) > 0 ? 1 : -1;

	// 화면을 클리어하는거
	memset(fm, 0, sizeof(unsigned char) * nWidth * nHeight);
	// 다시 그리는거 그래서 움직이는거 처럼 보임
	//drawCircle(fm, nSttX, nSttY, nRadius, 0xff);
	//drawCircle(fm, ++sx, ++sy, nRadius, nGray);

	// 원의 현재 위치를 업데이트
	if (sx != ex || sy != ey) {
		drawCircle(fm, sx, sy, nRadius, nGray);

		// 좌표 업데이트
		if (sx != ex) {
			sx += deltaX; // x 방향으로 이동
		}
		if (sy != ey) {
			sy += deltaY; // y 방향으로 이동
		}
	}

	UpdateDisplay();		//화면을 그려주는 함수
}

