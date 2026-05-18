#pragma once
#include "WrapperMap.h"
#include "OAutorach.h"


namespace SwarmGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o MainWin
	/// </summary>
	public ref class MainWin : public System::Windows::Forms::Form
	{

	private:
		WrapperMap* mapa = new WrapperMap(20, 20);

	public:
		MainWin(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MainWin()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ plikToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ zamknijToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ symulacjaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ startToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ stopToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ pomocToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ oProgramieToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ oAutorachToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^ pictureBoxMap;
	private: System::Windows::Forms::Button^ buttonStart;
	private: System::Windows::Forms::Button^ buttonStop;


	private: System::Windows::Forms::Button^ buttonReset;
	private: System::Windows::Forms::Button^ buttonStep;
	private: System::Windows::Forms::NumericUpDown^ numericX;
	private: System::Windows::Forms::NumericUpDown^ numericY;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ buttonAddRobot;
	private: System::Windows::Forms::Button^ buttonAddObstackle;
	private: System::Windows::Forms::Label^ labelStatus;
	private: System::Windows::Forms::Timer^ timerSimulation;
	private: System::Windows::Forms::Label^ labelRobotsCount;
	private: System::Windows::Forms::Label^ labelObstaclesCount;
	private: System::Windows::Forms::ToolStripMenuItem^ krokToolStripMenuItem;

	private: System::ComponentModel::IContainer^ components;





	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWin::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->plikToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zamknijToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->symulacjaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->startToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stopToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->resetToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pomocToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oProgramieToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->oAutorachToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBoxMap = (gcnew System::Windows::Forms::PictureBox());
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->buttonStop = (gcnew System::Windows::Forms::Button());
			this->buttonReset = (gcnew System::Windows::Forms::Button());
			this->buttonStep = (gcnew System::Windows::Forms::Button());
			this->numericX = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericY = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->buttonAddRobot = (gcnew System::Windows::Forms::Button());
			this->buttonAddObstackle = (gcnew System::Windows::Forms::Button());
			this->labelStatus = (gcnew System::Windows::Forms::Label());
			this->timerSimulation = (gcnew System::Windows::Forms::Timer(this->components));
			this->labelRobotsCount = (gcnew System::Windows::Forms::Label());
			this->labelObstaclesCount = (gcnew System::Windows::Forms::Label());
			this->krokToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxMap))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericY))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->plikToolStripMenuItem,
					this->symulacjaToolStripMenuItem, this->pomocToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(558, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// plikToolStripMenuItem
			// 
			this->plikToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->zamknijToolStripMenuItem });
			this->plikToolStripMenuItem->Name = L"plikToolStripMenuItem";
			this->plikToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->plikToolStripMenuItem->Text = L"Plik";
			// 
			// zamknijToolStripMenuItem
			// 
			this->zamknijToolStripMenuItem->Name = L"zamknijToolStripMenuItem";
			this->zamknijToolStripMenuItem->Size = System::Drawing::Size(117, 22);
			this->zamknijToolStripMenuItem->Text = L"Zamknij";
			this->zamknijToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::zamknijToolStripMenuItem_Click);
			// 
			// symulacjaToolStripMenuItem
			// 
			this->symulacjaToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->startToolStripMenuItem,
					this->stopToolStripMenuItem, this->resetToolStripMenuItem, this->krokToolStripMenuItem
			});
			this->symulacjaToolStripMenuItem->Name = L"symulacjaToolStripMenuItem";
			this->symulacjaToolStripMenuItem->Size = System::Drawing::Size(73, 20);
			this->symulacjaToolStripMenuItem->Text = L"Symulacja";
			// 
			// startToolStripMenuItem
			// 
			this->startToolStripMenuItem->Name = L"startToolStripMenuItem";
			this->startToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->startToolStripMenuItem->Text = L"Start";
			this->startToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::startToolStripMenuItem_Click);
			// 
			// stopToolStripMenuItem
			// 
			this->stopToolStripMenuItem->Name = L"stopToolStripMenuItem";
			this->stopToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->stopToolStripMenuItem->Text = L"Stop";
			this->stopToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::stopToolStripMenuItem_Click);
			// 
			// resetToolStripMenuItem
			// 
			this->resetToolStripMenuItem->Name = L"resetToolStripMenuItem";
			this->resetToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->resetToolStripMenuItem->Text = L"Reset";
			this->resetToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::resetToolStripMenuItem_Click);
			// 
			// pomocToolStripMenuItem
			// 
			this->pomocToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->oProgramieToolStripMenuItem,
					this->oAutorachToolStripMenuItem
			});
			this->pomocToolStripMenuItem->Name = L"pomocToolStripMenuItem";
			this->pomocToolStripMenuItem->Size = System::Drawing::Size(57, 20);
			this->pomocToolStripMenuItem->Text = L"Pomoc";
			// 
			// oProgramieToolStripMenuItem
			// 
			this->oProgramieToolStripMenuItem->Name = L"oProgramieToolStripMenuItem";
			this->oProgramieToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->oProgramieToolStripMenuItem->Text = L"O programie";
			this->oProgramieToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::oProgramieToolStripMenuItem_Click);
			// 
			// oAutorachToolStripMenuItem
			// 
			this->oAutorachToolStripMenuItem->Name = L"oAutorachToolStripMenuItem";
			this->oAutorachToolStripMenuItem->Size = System::Drawing::Size(141, 22);
			this->oAutorachToolStripMenuItem->Text = L"O autorach";
			this->oAutorachToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::oAutorachToolStripMenuItem_Click);
			// 
			// pictureBoxMap
			// 
			this->pictureBoxMap->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBoxMap->Location = System::Drawing::Point(20, 40);
			this->pictureBoxMap->Name = L"pictureBoxMap";
			this->pictureBoxMap->Size = System::Drawing::Size(500, 500);
			this->pictureBoxMap->TabIndex = 1;
			this->pictureBoxMap->TabStop = false;
			this->pictureBoxMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainWin::pictureBoxMap_Paint);
			// 
			// buttonStart
			// 
			this->buttonStart->Location = System::Drawing::Point(43, 638);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(75, 23);
			this->buttonStart->TabIndex = 2;
			this->buttonStart->Text = L"Start";
			this->buttonStart->UseVisualStyleBackColor = true;
			this->buttonStart->Click += gcnew System::EventHandler(this, &MainWin::buttonStart_Click);
			// 
			// buttonStop
			// 
			this->buttonStop->Location = System::Drawing::Point(159, 638);
			this->buttonStop->Name = L"buttonStop";
			this->buttonStop->Size = System::Drawing::Size(75, 23);
			this->buttonStop->TabIndex = 3;
			this->buttonStop->Text = L"Stop";
			this->buttonStop->UseVisualStyleBackColor = true;
			this->buttonStop->Click += gcnew System::EventHandler(this, &MainWin::buttonStop_Click);
			// 
			// buttonReset
			// 
			this->buttonReset->Location = System::Drawing::Point(278, 638);
			this->buttonReset->Name = L"buttonReset";
			this->buttonReset->Size = System::Drawing::Size(75, 23);
			this->buttonReset->TabIndex = 4;
			this->buttonReset->Text = L"Reset";
			this->buttonReset->UseVisualStyleBackColor = true;
			this->buttonReset->Click += gcnew System::EventHandler(this, &MainWin::buttonReset_Click);
			// 
			// buttonStep
			// 
			this->buttonStep->Location = System::Drawing::Point(400, 638);
			this->buttonStep->Name = L"buttonStep";
			this->buttonStep->Size = System::Drawing::Size(75, 23);
			this->buttonStep->TabIndex = 5;
			this->buttonStep->Text = L"Krok";
			this->buttonStep->UseVisualStyleBackColor = true;
			this->buttonStep->Click += gcnew System::EventHandler(this, &MainWin::buttonStep_Click);
			// 
			// numericX
			// 
			this->numericX->Location = System::Drawing::Point(82, 564);
			this->numericX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 19, 0, 0, 0 });
			this->numericX->Name = L"numericX";
			this->numericX->Size = System::Drawing::Size(120, 20);
			this->numericX->TabIndex = 6;
			this->numericX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// numericY
			// 
			this->numericY->Location = System::Drawing::Point(324, 562);
			this->numericY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 19, 0, 0, 0 });
			this->numericY->Name = L"numericY";
			this->numericY->Size = System::Drawing::Size(120, 20);
			this->numericY->TabIndex = 7;
			this->numericY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(59, 569);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(17, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"X:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(301, 566);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(17, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Y:";
			// 
			// buttonAddRobot
			// 
			this->buttonAddRobot->Location = System::Drawing::Point(82, 590);
			this->buttonAddRobot->Name = L"buttonAddRobot";
			this->buttonAddRobot->Size = System::Drawing::Size(120, 23);
			this->buttonAddRobot->TabIndex = 10;
			this->buttonAddRobot->Text = L"Dodaj robota";
			this->buttonAddRobot->UseVisualStyleBackColor = true;
			this->buttonAddRobot->Click += gcnew System::EventHandler(this, &MainWin::buttonAddRobot_Click);
			// 
			// buttonAddObstackle
			// 
			this->buttonAddObstackle->Location = System::Drawing::Point(324, 590);
			this->buttonAddObstackle->Name = L"buttonAddObstackle";
			this->buttonAddObstackle->Size = System::Drawing::Size(120, 23);
			this->buttonAddObstackle->TabIndex = 11;
			this->buttonAddObstackle->Text = L"Dodaj przeszkodê";
			this->buttonAddObstackle->UseVisualStyleBackColor = true;
			this->buttonAddObstackle->Click += gcnew System::EventHandler(this, &MainWin::buttonAddObstackle_Click);
			// 
			// labelStatus
			// 
			this->labelStatus->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->labelStatus->Location = System::Drawing::Point(20, 679);
			this->labelStatus->Name = L"labelStatus";
			this->labelStatus->Size = System::Drawing::Size(159, 18);
			this->labelStatus->TabIndex = 12;
			this->labelStatus->Text = L"Status: gotowe";
			// 
			// timerSimulation
			// 
			this->timerSimulation->Interval = 800;
			this->timerSimulation->Tick += gcnew System::EventHandler(this, &MainWin::timerSimulation_Tick);
			// 
			// labelRobotsCount
			// 
			this->labelRobotsCount->AutoSize = true;
			this->labelRobotsCount->Location = System::Drawing::Point(235, 679);
			this->labelRobotsCount->Name = L"labelRobotsCount";
			this->labelRobotsCount->Size = System::Drawing::Size(53, 13);
			this->labelRobotsCount->TabIndex = 13;
			this->labelRobotsCount->Text = L"Roboty: 0";
			// 
			// labelObstaclesCount
			// 
			this->labelObstaclesCount->AutoSize = true;
			this->labelObstaclesCount->Location = System::Drawing::Point(341, 679);
			this->labelObstaclesCount->Name = L"labelObstaclesCount";
			this->labelObstaclesCount->Size = System::Drawing::Size(73, 13);
			this->labelObstaclesCount->TabIndex = 14;
			this->labelObstaclesCount->Text = L"Przeszkody: 0";
			// 
			// krokToolStripMenuItem
			// 
			this->krokToolStripMenuItem->Name = L"krokToolStripMenuItem";
			this->krokToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->krokToolStripMenuItem->Text = L"Krok";
			this->krokToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWin::krokToolStripMenuItem_Click);
			// 
			// MainWin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(558, 706);
			this->Controls->Add(this->labelObstaclesCount);
			this->Controls->Add(this->labelRobotsCount);
			this->Controls->Add(this->labelStatus);
			this->Controls->Add(this->buttonAddObstackle);
			this->Controls->Add(this->buttonAddRobot);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->numericY);
			this->Controls->Add(this->numericX);
			this->Controls->Add(this->buttonStep);
			this->Controls->Add(this->buttonReset);
			this->Controls->Add(this->buttonStop);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->pictureBoxMap);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainWin";
			this->Text = L"SwarmGUI";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxMap))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericY))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void zamknijToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Windows::Forms::DialogResult answer;
		answer = MessageBox::Show("Czy napewno chcesz zamkn¹æ aplikacjê?",
			"Program rój robotów", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

		if (answer == System::Windows::Forms::DialogResult::Yes)
			Application::Exit();
	}




private: System::Void oAutorachToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	OAutorach^ autors_info = gcnew OAutorach();
	autors_info->Show();
}


private: System::Void buttonAddRobot_Click(System::Object^ sender, System::EventArgs^ e) {
	int x = Convert::ToInt32(numericX->Value);
	int y = Convert::ToInt32(numericY->Value);

	int wynik = mapa->placeRobot(x, y); 

		if (wynik == 0)
			labelStatus->Text = L"Dodano robota";
		else
			labelStatus->Text = L"Nie mo¿na dodaæ robota";

		pictureBoxMap->Refresh();

		labelRobotsCount->Text =
			L"Roboty: " + Convert::ToString(mapa->getRobotNum());
}

private: System::Void buttonAddObstackle_Click(System::Object^ sender, System::EventArgs^ e) {
	int x = Convert::ToInt32(numericX->Value);
	int y = Convert::ToInt32(numericY->Value);

	int wynik = mapa->placeObstacle(x, y);


	if (wynik == 0)
		labelStatus->Text = L"Dodano przeszkodê";
	else
		labelStatus->Text = L"Nie mo¿na dodaæ przeszkody";

		pictureBoxMap->Refresh();

		labelObstaclesCount->Text =
			L"Przeszkody: " + Convert::ToString(mapa->getObstacleNum());
}


private: System::Void pictureBoxMap_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;

	std::vector<std::vector<int>> obj_map = mapa->getMap();

	int sizeX = mapa->getSizeX();
	int sizeY = mapa->getSizeY();

	int cellW = pictureBoxMap->Width / sizeX;
	int cellH = pictureBoxMap->Height / sizeY;

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			Rectangle rect(x * cellW, y * cellH, cellW, cellH);

			if (obj_map[x][y] == 0)
				g->FillRectangle(Brushes::White, rect);
			else if (obj_map[x][y] == 1)
				g->FillRectangle(Brushes::Black, rect);
			else if (obj_map[x][y] == 2)
			{
				Rectangle robotRect(x * cellW + cellW / 4 , y * cellH + cellH / 4, cellW / 2, cellH / 2);
				g->FillEllipse(Brushes::Red, robotRect);
			}
			g->DrawRectangle(Pens::Gray, rect);
		}
	}
}
private: System::Void buttonStep_Click(System::Object^ sender, System::EventArgs^ e) {
	mapa->update();
	pictureBoxMap->Refresh();

	labelStatus->Text = L"Wykonano krok symulacji";
}
private: System::Void timerSimulation_Tick(System::Object^ sender, System::EventArgs^ e) {
	mapa->update();
	pictureBoxMap->Refresh();

	labelStatus->Text = L"Symulacja dzia³a";
}
private: System::Void buttonStart_Click(System::Object^ sender, System::EventArgs^ e) {
	timerSimulation->Start();
	labelStatus->Text = L"Start symulacji";
}
private: System::Void buttonStop_Click(System::Object^ sender, System::EventArgs^ e) {
	timerSimulation->Stop();
	labelStatus->Text = L"Stop symulacji";
}
private: System::Void buttonReset_Click(System::Object^ sender, System::EventArgs^ e) {
	delete mapa;

	mapa = new WrapperMap(20, 20);

	pictureBoxMap->Refresh();

	labelStatus->Text = L"Zresetowano plansze";

	labelRobotsCount->Text = L"Roboty: 0";
	labelObstaclesCount->Text = L"Przeszkody: 0";
}
private: System::Void oProgramieToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	MessageBox::Show(
		L"Nasz program sluzy do wizualizacji symulacji roju robotow na mapie.\n\n"
		L"Mo¿emy dodawaæ na planszy roboty i przeszkody w wybranych miejscach, "
		L"uruchamiaæ symulacjê, zatrzymywaæ j¹ oraz wykonywaæ pojedyncze kroki.\n\n"
		L"Plansza pokazuje:\n"
		L"- czarne pola: przeszkody i granice mapy\n"
		L"- czerwone kolka: roboty\n",
		L"O programie",
		MessageBoxButtons::OK,
		MessageBoxIcon::Information
	);
}
private: System::Void startToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	buttonStart_Click(sender, e);
}
private: System::Void stopToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	buttonStop_Click(sender, e);
}
private: System::Void resetToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	buttonReset_Click(sender, e);
}
private: System::Void krokToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	buttonStep_Click(sender, e);
}
};
}
