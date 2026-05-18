#pragma once

namespace SwarmGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o OAutorach
	/// </summary>
	public ref class OAutorach : public System::Windows::Forms::Form
	{
	public:
		OAutorach(void)
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
		~OAutorach()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ autors_info;
	protected:

	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(OAutorach::typeid));
			this->autors_info = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// autors_info
			// 
			this->autors_info->Location = System::Drawing::Point(57, 50);
			this->autors_info->Multiline = true;
			this->autors_info->Name = L"autors_info";
			this->autors_info->ReadOnly = true;
			this->autors_info->Size = System::Drawing::Size(188, 171);
			this->autors_info->TabIndex = 0;
			this->autors_info->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// OAutorach
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 274);
			this->Controls->Add(this->autors_info);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"OAutorach";
			this->Text = L"OAutorach";
			this->Load += gcnew System::EventHandler(this, &OAutorach::OAutorach_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void OAutorach_Load(System::Object^ sender, System::EventArgs^ e) {
		autors_info->Text = "\r\n\r\nProgram rój robotów\r\n=====\r\nAutors: £ukasz Jaromin, Mateusz Janis, Karol Godowski\r\n=====\r\n2026";
	}
	};
}
