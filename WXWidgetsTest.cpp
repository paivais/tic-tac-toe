#include <wx/wxprec.h> //including the wxwidgets library
#ifdef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <string.h>

int board[3][3];

int player; //help monitor the game
int turnCounter;
int victorious;

void initBoard();
int checkBoard();

//creating the matrix for the board
void initBoard() { //function to begin the game

	int i, j;

	player = 1;
	turnCounter = 0;
	victorious = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}

int checkBoard() {
	int i, j, p1, p2;

	//verifying the lines
	for (i = 0; i < 3; i++) {
		p1 = 0;
		p2 = 0;
		for (j = 0; j < 3; j++) {
			if (board[i][j] == 1) p1++;
			else if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}
	}

	//verifying the columns
	for (j = 0; j < 3; j++) {
		p1 = 0;
		p2 = 0;
		for (i = 0; i < 3; i++) {
			if (board[i][j] == 1) p1++;
			else if (board[i][j] == 2) p2++;
		}
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}
	}

	//main diagonal
	p1 = 0;
	p2 = 0;
	for (i = 0; i < 3; i++) {
		if (board[i][j] == 1) p1++;
		else if (board[i][j] == 2) p2++;
	}
	if (p1 == 3) {
		return 1;
	}
	else if (p2 == 3) {
		return 2;
	}

	//oposite diagonal
	p1 = 0;
	p2 = 0;
	j = 2;
	for (i = 0; i < 3; i++) {
		if (board[i][j] == 1) p1++;
		else if (board[i][j] == 2) p2++;
		j--;
		if (p1 == 3) {
			return 1;
		}
		else if (p2 == 3) {
			return 2;
		}

		//if no win
		return 0;
	}
}


//inheriting wxApp class from wxwidgets library
class ticTacToe : public wxApp {
public:
	virtual bool OnInit();
};

//creating the frame for the game from wxFrame
class MainFrame : public wxFrame {
public:
	MainFrame();
protected:
	wxMenuBar* m_mainMenuBar;
	wxMenu* m_menuGame;

	wxButton* m_btnUpLeft;
	wxButton* m_btnUpMid;
	wxButton* m_btnUpRight;

	wxButton* m_btnMidLeft;
	wxButton* m_btnMidMid;
	wxButton* m_btnMidRight;

	wxButton* m_btnDownLeft;
	wxButton* m_btnDownMid;
	wxButton* m_btnDownRight;
private:
	void OnNewGame(wxCommandEvent& event);

	void EnableGrid();
	void DisableGrid();
	void EndGame();


	void OnBtnUpLeftClick(wxCommandEvent& event);
	void OnBtnUpMidClick(wxCommandEvent& event);
	void OnBtnUpRightClick(wxCommandEvent& event);

	void OnBtnMidLeftClick(wxCommandEvent& event);
	void OnBtnMidMidClick(wxCommandEvent& event);
	void OnBtnMidRightClick(wxCommandEvent& event);

	void OnBtnDownLeftClick(wxCommandEvent& event);
	void OnBtnDownMidClick(wxCommandEvent& event);
	void OnBtnDownRightClick(wxCommandEvent& event);
};

//activated everytime the method is invoked for the 1st time
bool ticTacToe::OnInit() {
	MainFrame* frame = new MainFrame();
	frame->Show();

	//initializing the table
	initBoard();

	return true;
}

enum {
	ID_NewGame = 1 //identifier for menugame
};

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "TIC TAC TOE") {
	this->SetSizeHints(600, 600);

	m_mainMenuBar = new wxMenuBar(0);
	m_menuGame = new wxMenu();

	m_mainMenuBar->Append(m_menuGame, "Game");
	m_menuGame->Append(ID_NewGame, "New Game");

	wxFont font(48, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	this->SetMenuBar(m_mainMenuBar);
	//creating the grid size
	wxGridSizer* gBoard = new wxGridSizer(3, 3, 0, 0);
	gBoard->SetMinSize(500, 500);
	//up buttons
	m_btnUpLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpLeft->SetFont(font);
	gBoard->Add(m_btnUpLeft, 0, wxALL | wxEXPAND, 5);

	m_btnUpMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpMid->SetFont(font);
	gBoard->Add(m_btnUpMid, 0, wxALL | wxEXPAND, 5);

	m_btnUpRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnUpRight->SetFont(font);
	gBoard->Add(m_btnUpRight, 0, wxALL | wxEXPAND, 5);

	//mid buttons
	m_btnMidLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidLeft->SetFont(font);
	gBoard->Add(m_btnMidLeft, 0, wxALL | wxEXPAND, 5);

	m_btnMidMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidMid->SetFont(font);
	gBoard->Add(m_btnMidMid, 0, wxALL | wxEXPAND, 5);

	m_btnMidRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnMidRight->SetFont(font);
	gBoard->Add(m_btnMidRight, 0, wxALL | wxEXPAND, 5);
	//down buttons
	m_btnDownLeft = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnDownLeft->SetFont(font);
	gBoard->Add(m_btnDownLeft, 0, wxALL | wxEXPAND, 5);

	m_btnDownMid = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnDownMid->SetFont(font);
	gBoard->Add(m_btnDownMid, 0, wxALL | wxEXPAND, 5);

	m_btnDownRight = new wxButton(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
	m_btnDownRight->SetFont(font);
	gBoard->Add(m_btnDownRight, 0, wxALL | wxEXPAND, 5);

	this->SetSizer(gBoard);
	this->Layout();

	DisableGrid();

	Bind(wxEVT_MENU, &MainFrame::OnNewGame, this, ID_NewGame);


	//click event
	m_btnUpLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpLeftClick), NULL, this);
	m_btnUpMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpMidClick), NULL, this);
	m_btnUpRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnUpRightClick), NULL, this);

	m_btnMidLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidLeftClick), NULL, this);
	m_btnMidMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidMidClick), NULL, this);
	m_btnMidRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnMidRightClick), NULL, this);

	m_btnDownLeft->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnDownLeftClick), NULL, this);
	m_btnDownMid->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnDownMidClick), NULL, this);
	m_btnDownRight->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnBtnDownRightClick), NULL, this);
}


//invoking a main using the wxwidgets lib
wxIMPLEMENT_APP(ticTacToe);



void MainFrame::EnableGrid() {
	m_btnUpLeft->Enable();
	m_btnUpMid->Enable();
	m_btnUpRight->Enable();
	m_btnMidLeft->Enable();
	m_btnMidMid->Enable();
	m_btnMidRight->Enable();
	m_btnDownLeft->Enable();
	m_btnDownMid->Enable();
	m_btnDownRight->Enable();

	m_btnUpLeft->SetLabelText("");
	m_btnUpMid->SetLabelText("");
	m_btnUpRight->SetLabelText("");
	m_btnMidLeft->SetLabelText("");
	m_btnMidMid->SetLabelText("");
	m_btnMidRight->SetLabelText("");
	m_btnDownLeft->SetLabelText("");
	m_btnDownMid->SetLabelText("");
	m_btnDownRight->SetLabelText("");

}

void MainFrame::DisableGrid() {
	m_btnUpLeft->Disable();
	m_btnUpMid->Disable();
	m_btnUpRight->Disable();
	m_btnMidLeft->Disable();
	m_btnMidMid->Disable();
	m_btnMidRight->Disable();
	m_btnDownLeft->Disable();
	m_btnDownMid->Disable();
	m_btnDownRight->Disable();

	m_btnUpLeft->SetLabelText("");
	m_btnUpMid->SetLabelText("");
	m_btnUpRight->SetLabelText("");
	m_btnMidLeft->SetLabelText("");
	m_btnMidMid->SetLabelText("");
	m_btnMidRight->SetLabelText("");
	m_btnDownLeft->SetLabelText("");
	m_btnDownMid->SetLabelText("");
	m_btnDownRight->SetLabelText("");
}


void MainFrame::EndGame() {
	char message[200] = "";
	if (victorious == 0) {
		strcpy(message, "TIE");
	}
	else {
		if (victorious == 1) {
			strcpy(message, "Player 1 wins");
		}
		else {
			if (victorious == 2) {
				strcpy(message, "Player 2 wins");
			}
		}
	}

	strcat(message, "Another game?");
	if (wxMessageBox(message, "End", wxYES_NO | wxICON_INFORMATION) == wxYES) {
		initBoard();
		EnableGrid();
	}
	else {
		_close(true);
	}
}

void MainFrame::OnNewGame(wxCommandEvent& event) {
	EnableGrid();
	initBoard();
}



void MainFrame::OnBtnUpLeftClick(wxCommandEvent& event) {
	if (m_btnUpLeft->IsEnabled()) {
		board[0][0] = player;
		m_btnUpLeft->Disable();
		if (player == 1) {
			m_btnUpLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnUpMidClick(wxCommandEvent& event) {
	if (m_btnUpMid->IsEnabled()) {
		board[0][1] = player;
		m_btnUpMid->Disable();
		if (player == 1) {
			m_btnUpMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnUpRightClick(wxCommandEvent& event) {
	if (m_btnUpRight->IsEnabled()) {
		board[0][2] = player;
		m_btnUpRight->Disable();
		if (player == 1) {
			m_btnUpRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnUpRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnMidLeftClick(wxCommandEvent& event) {
	if (m_btnMidLeft->IsEnabled()) {
		board[1][0] = player;
		m_btnMidLeft->Disable();
		if (player == 1) {
			m_btnMidLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnMidMidClick(wxCommandEvent& event) {
	if (m_btnMidMid->IsEnabled()) {
		board[1][1] = player;
		m_btnMidMid->Disable();
		if (player == 1) {
			m_btnMidMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnMidRightClick(wxCommandEvent& event) {
	if (m_btnMidRight->IsEnabled()) {
		board[1][2] = player;
		m_btnMidRight->Disable();
		if (player == 1) {
			m_btnMidRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnMidRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnDownLeftClick(wxCommandEvent& event) {
	if (m_btnDownLeft->IsEnabled()) {
		board[2][0] = player;
		m_btnDownLeft->Disable();
		if (player == 1) {
			m_btnDownLeft->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnDownLeft->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnDownMidClick(wxCommandEvent& event) {
	if (m_btnDownMid->IsEnabled()) {
		board[2][1] = player;
		m_btnDownMid->Disable();
		if (player == 1) {
			m_btnDownMid->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnDownMid->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}

void MainFrame::OnBtnDownRightClick(wxCommandEvent& event) {
	if (m_btnDownRight->IsEnabled()) {
		board[2][2] = player;
		m_btnDownRight->Disable();
		if (player == 1) {
			m_btnDownRight->SetLabelText("X");
			player = 2;
		}
		else {
			if (player == 2) {
				m_btnDownRight->SetLabelText("O");
				player = 1;
			}
		}
	}
	turnCounter++;
	//verifying if anyone won
	victorious = checkBoard();
	if (victorious != 0 || turnCounter >= 9) {
		EndGame();
	}
}