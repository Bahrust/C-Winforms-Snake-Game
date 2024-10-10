#include <vector>
#include <iomanip>
#include <conio.h>
#include <string>
#include <cstdlib>  
#include <ctime>    
#pragma once
namespace Snake {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>

	enum ENUM_MOVE_DIRECTION
	{
		none,
		up,
		down,
		left,
		right,
	};
	ENUM_MOVE_DIRECTION moveDirection = none;
	ENUM_MOVE_DIRECTION lastMove = none;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		int score = 0;
		int fieldWidth = 250;
		int fieldHeight = 225;
		int moveCounter;
		int applePosX;
		PictureBox^ apple = gcnew PictureBox();
	private: System::Windows::Forms::Timer^ timer;
	private: array<PictureBox^>^ snake;



	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::PictureBox^ pictureBox6;
	private: System::Windows::Forms::PictureBox^ pictureBox7;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::PictureBox^ pictureBox11;
	private: System::Windows::Forms::PictureBox^ pictureBox12;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox13;
	private: System::Windows::Forms::PictureBox^ pictureBox14;
	private: System::Windows::Forms::PictureBox^ pictureBox15;
	private: System::Windows::Forms::PictureBox^ pictureBox16;
	private: System::Windows::Forms::PictureBox^ pictureBox17;
	private: System::Windows::Forms::PictureBox^ pictureBox18;
	private: System::Windows::Forms::PictureBox^ pictureBox19;
	private: System::Windows::Forms::PictureBox^ pictureBox20;

	private: System::Windows::Forms::PictureBox^ pictureBox23;


	public:

	public:
		int applePosY;

		int RandomNum(int min, int max)
		{
			return ((rand() % (max - min + 1) + min + 12) / 25) * 25;
		}

		void AddRestartButton() {
			Button^ restart = gcnew Button();
			restart->Click::add(gcnew System::EventHandler(this, &MyForm::restart));
			restart->Location = Drawing::Point((ClientSize.Width - 99) / 2, (ClientSize.Height - 76) / 2);
			restart->Size = System::Drawing::Size(102, 52);
			restart->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			restart->Name = "restart";
			restart->Text = "Restart";
			restart->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 15));
			this->Controls->Add(restart);
			restart->BringToFront();
			this->Controls->Remove(apple);
			for (int i = 0; i <= score; i++)
			{
				this->Controls->Remove(snake[i]);
			}
		}

		void MoveSnake()
		{
			for (int i = score; i > 0; i--)
			{
				this->snake[i]->Location = Drawing::Point(snake[i - 1]->Location.X, snake[i - 1]->Location.Y);
			}
			switch (moveDirection)
			{
			case 1: // Up				
				if (snake[0]->Location.Y <= 0)
				{
					this->timer->Stop();
					AddRestartButton();
				}
				snake[0]->Location = Drawing::Point(snake[0]->Location.X, snake[0]->Location.Y - 25);
				lastMove = ENUM_MOVE_DIRECTION::up;
				break;
			case 2: // Down
				if (snake[0]->Location.Y >= fieldHeight)
				{
					this->timer->Stop();
					AddRestartButton();
				}
				snake[0]->Location = Drawing::Point(snake[0]->Location.X, snake[0]->Location.Y + 25);
				lastMove = ENUM_MOVE_DIRECTION::down;
				break;
			case 3: // Left
				if (snake[0]->Location.X <= 0)
				{
					this->timer->Stop();
					AddRestartButton();
				}
				snake[0]->Location = Drawing::Point(snake[0]->Location.X - 25, snake[0]->Location.Y);
				lastMove = ENUM_MOVE_DIRECTION::left;
				break;
			case 4: // Right
				if (snake[0]->Location.X >= fieldWidth - 25)
				{
					this->timer->Stop();
					AddRestartButton();
				}
				snake[0]->Location = Drawing::Point(snake[0]->Location.X + 25, snake[0]->Location.Y);
				lastMove = ENUM_MOVE_DIRECTION::right;
				break;

			default:
				break;
			}
			if (WasAppleEaten())
			{
				score++;
				this->timer->Interval *= 0.8;
				this->score_label->Text = "Score: " + score.ToString();
				SetNewApplePos();
				this->snake[score] = gcnew PictureBox();
				this->snake[score]->BackColor = Color::Green;
				this->snake[score]->Size = System::Drawing::Size(25, 25);
				switch (lastMove)
				{
				case 1: // Up
					this->snake[score]->Location = Drawing::Point(snake[score - 1]->Location.X, snake[score - 1]->Location.Y+25);
					break;
				case 2: // Down
					this->snake[score]->Location = Drawing::Point(snake[score - 1]->Location.X, snake[score - 1]->Location.Y - 25);
					break;
				case 3: // Left
					this->snake[score]->Location = Drawing::Point(snake[score - 1]->Location.X + 25, snake[score - 1]->Location.Y);
					break;
				case 4: // Right
					this->snake[score]->Location = Drawing::Point(snake[score - 1]->Location.X-25, snake[score - 1]->Location.Y);
					break;

				default:
					break;
				}
				this->Controls->Add(snake[score]);
			}
		}

		bool WasAppleEaten()
		{
			if (snake[0]->Location.X == apple->Location.X && snake[0]->Location.Y == apple->Location.Y)
			{
				return true;
			}

			return false;
		}

		void SetNewApplePos()
		{
			int j = 1;
			for (int i = 0; i < score; i++)
			{
				while (snake[i]->Location.X == apple->Location.X || snake[i]->Location.Y == apple->Location.Y)
				{
					apple->Location = Drawing::Point(RandomNum(0, fieldWidth), RandomNum(0, fieldHeight));
					j++;
				}
			}
		}

		void Start()
		{
				MoveSnake();
				for (int i = 3; i < score; i++)
				{
					if (snake[0]->Location.X == snake[i]->Location.X && snake[0]->Location.Y == snake[i]->Location.Y)
					{
						this->timer->Stop();
						AddRestartButton();
					}
				}
		}
		MyForm(void)
		{
			InitializeComponent();
			this->timer = gcnew Timer(this->components);
			this->timer->Interval = 300;
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			this->timer->Start();
			this->snake = gcnew array<PictureBox^, 1>(400);
			this->snake[0] = gcnew PictureBox();
			this->snake[0]->BackColor = Color::Green;
			this->snake[0]->Size = System::Drawing::Size(25, 25);
			srand(time(0));
			this->snake[0]->Location = Drawing::Point(RandomNum(0, fieldWidth), RandomNum(0, fieldHeight));
			apple->BackColor = Color::Red;
			apple->Size = System::Drawing::Size(25, 25);
			apple->Location = Drawing::Point(RandomNum(0, fieldWidth), RandomNum(0, fieldHeight));
			SetNewApplePos();
			this->Controls->Add(apple);
			this->Controls->Add(snake[0]);
			this->score_label->Text = "Score: " + score.ToString();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ score_label;
	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->score_label = (gcnew System::Windows::Forms::Label());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox14 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox15 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox16 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox17 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox18 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox19 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox20 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox23 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->BeginInit();
			this->SuspendLayout();
			// 
			// score_label
			// 
			this->score_label->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			resources->ApplyResources(this->score_label, L"score_label");
			this->score_label->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->score_label->Name = L"score_label";
			// 
			// timer
			// 
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox4, L"pictureBox4");
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox5, L"pictureBox5");
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->TabStop = false;
			this->pictureBox5->Click += gcnew System::EventHandler(this, &MyForm::pictureBox5_Click);
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox6, L"pictureBox6");
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox7, L"pictureBox7");
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox8, L"pictureBox8");
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->TabStop = false;
			this->pictureBox8->Click += gcnew System::EventHandler(this, &MyForm::pictureBox8_Click);
			// 
			// pictureBox9
			// 
			this->pictureBox9->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox9, L"pictureBox9");
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->TabStop = false;
			this->pictureBox9->Click += gcnew System::EventHandler(this, &MyForm::pictureBox5_Click);
			// 
			// pictureBox10
			// 
			this->pictureBox10->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox10, L"pictureBox10");
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->TabStop = false;
			// 
			// pictureBox11
			// 
			this->pictureBox11->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox11, L"pictureBox11");
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->TabStop = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox12, L"pictureBox12");
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox1, L"pictureBox1");
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// pictureBox13
			// 
			this->pictureBox13->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox13, L"pictureBox13");
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->TabStop = false;
			this->pictureBox13->Click += gcnew System::EventHandler(this, &MyForm::pictureBox13_Click);
			// 
			// pictureBox14
			// 
			this->pictureBox14->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox14, L"pictureBox14");
			this->pictureBox14->Name = L"pictureBox14";
			this->pictureBox14->TabStop = false;
			this->pictureBox14->Click += gcnew System::EventHandler(this, &MyForm::pictureBox14_Click);
			// 
			// pictureBox15
			// 
			this->pictureBox15->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox15, L"pictureBox15");
			this->pictureBox15->Name = L"pictureBox15";
			this->pictureBox15->TabStop = false;
			// 
			// pictureBox16
			// 
			this->pictureBox16->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox16, L"pictureBox16");
			this->pictureBox16->Name = L"pictureBox16";
			this->pictureBox16->TabStop = false;
			this->pictureBox16->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// pictureBox17
			// 
			this->pictureBox17->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox17, L"pictureBox17");
			this->pictureBox17->Name = L"pictureBox17";
			this->pictureBox17->TabStop = false;
			this->pictureBox17->Click += gcnew System::EventHandler(this, &MyForm::pictureBox14_Click);
			// 
			// pictureBox18
			// 
			this->pictureBox18->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox18, L"pictureBox18");
			this->pictureBox18->Name = L"pictureBox18";
			this->pictureBox18->TabStop = false;
			this->pictureBox18->Click += gcnew System::EventHandler(this, &MyForm::pictureBox13_Click);
			// 
			// pictureBox19
			// 
			this->pictureBox19->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox19, L"pictureBox19");
			this->pictureBox19->Name = L"pictureBox19";
			this->pictureBox19->TabStop = false;
			// 
			// pictureBox20
			// 
			this->pictureBox20->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox20, L"pictureBox20");
			this->pictureBox20->Name = L"pictureBox20";
			this->pictureBox20->TabStop = false;
			this->pictureBox20->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
			// 
			// pictureBox23
			// 
			this->pictureBox23->BackColor = System::Drawing::SystemColors::WindowFrame;
			resources->ApplyResources(this->pictureBox23, L"pictureBox23");
			this->pictureBox23->Name = L"pictureBox23";
			this->pictureBox23->TabStop = false;
			// 
			// MyForm
			// 
			this->AccessibleRole = System::Windows::Forms::AccessibleRole::None;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Controls->Add(this->pictureBox9);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox23);
			this->Controls->Add(this->pictureBox19);
			this->Controls->Add(this->pictureBox15);
			this->Controls->Add(this->pictureBox18);
			this->Controls->Add(this->pictureBox13);
			this->Controls->Add(this->pictureBox17);
			this->Controls->Add(this->pictureBox14);
			this->Controls->Add(this->pictureBox20);
			this->Controls->Add(this->pictureBox16);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox12);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox11);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox10);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->score_label);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->TransparencyKey = System::Drawing::Color::DarkGray;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox19))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox23))->EndInit();
			this->ResumeLayout(false);

		}


#pragma endregion


		private:
			void MyForm::restart(System::Object^ sender, System::EventArgs^ e) {
				Application::Restart();
			}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		Start();
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {

			if (e->KeyCode == Keys::S || e->KeyCode == Keys::Down) {
				if (moveDirection != ENUM_MOVE_DIRECTION::up && lastMove != ENUM_MOVE_DIRECTION::up)
					moveDirection = ENUM_MOVE_DIRECTION::down;
			}
			else if (e->KeyCode == Keys::W || e->KeyCode == Keys::Up) {
				if (moveDirection != ENUM_MOVE_DIRECTION::down && lastMove != ENUM_MOVE_DIRECTION::down)
					moveDirection = ENUM_MOVE_DIRECTION::up;
			}
			else if (e->KeyCode == Keys::A || e->KeyCode == Keys::Left) {
			if (moveDirection != ENUM_MOVE_DIRECTION::right && lastMove != ENUM_MOVE_DIRECTION::right)
				moveDirection = ENUM_MOVE_DIRECTION::left;

			}
			else if (e->KeyCode == Keys::D || e->KeyCode == Keys::Right) {
				if (moveDirection != ENUM_MOVE_DIRECTION::left && lastMove != ENUM_MOVE_DIRECTION::left)
					moveDirection = ENUM_MOVE_DIRECTION::right;
			}
			else if (this->timer->Enabled == false && e->KeyCode == Keys::Space || e->KeyCode == Keys::Enter) {
				Application::Restart();
			}
		
	}
	private: System::Void pictureBox5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox13_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox14_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox3_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pictureBox8_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}

