
// GlimReportDlg.h: 헤더 파일
//

#pragma once


// CGlimReportDlg 대화 상자
class CGlimReportDlg : public CDialogEx
{
private:
	// m은 멤버변수 지역변수, n은 int 헝가리안 표기법
	CImage m_image;		//CImage 이미지 클래스 만들기

	// 생성입니다.
public:
	CGlimReportDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMREPORT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int sx;		// IDC_EDIT_NUM 의 변수
	int sy;
	int ex;
	int ey;
	// 버튼 클릭 이벤트 처리기
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	// 화면 업데이트 함수
	void UpdateDisplay();
	// 원 그리기 함수
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	// 중심에 X 모양 그리기
	void drawCenter();
	// 움직이기
	void moveCir();
	// 이미지 로드
	void imgLoad();
	// 유효한 이미지 위치 확인
	//bool validImgPos(int x, int y);
	// 원 안에 있는지 확인
	//bool isInCircle(int x, int y, int nCenterX, int nCenterY, int nRadius);

};
