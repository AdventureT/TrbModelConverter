#pragma once
#include "Trb.h"
#include "Mat.h"
#include "Game.h"
#include <thread>
namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections::Generic;
	using namespace std;
	using namespace System::IO;
	char* _fileName = new char[256];

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			/*
			this->SetStyle(
				ControlStyles::AllPaintingInWmPaint |
				ControlStyles::DoubleBuffer,
				true);
				*/
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;
		List<System::String^>^ texName = gcnew List<System::String^>();
		List<System::String^>^ allTexNames = gcnew List<System::String^>();
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::CheckedListBox^ checkedListBox1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;


		   List<System::String^>^ meshNamebelong = gcnew List<System::String^>();

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button1
			// 
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->button1->Location = System::Drawing::Point(321, 330);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(180, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Open trb file and Convert";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::Button1_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->radioButton1->Location = System::Drawing::Point(56, 70);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(83, 17);
			this->radioButton1->TabIndex = 1;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Little Endian";
			this->radioButton1->UseVisualStyleBackColor = false;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->ForeColor = System::Drawing::SystemColors::WindowText;
			this->radioButton2->Location = System::Drawing::Point(56, 94);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(76, 17);
			this->radioButton2->TabIndex = 2;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Big Endian";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::SystemColors::Window;
			this->comboBox1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"de Blob", L"Nicktoons Attack of the Toybots",
					L"Nicktoons Battle for Volcano Island", L"Nicktoons Unite"
			});
			this->comboBox1->Location = System::Drawing::Point(56, 150);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(182, 21);
			this->comboBox1->TabIndex = 3;
			this->comboBox1->Text = L"Choose Game";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 381);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(830, 23);
			this->progressBar1->TabIndex = 4;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Form1::progressBar1_Click);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->BackColor = System::Drawing::SystemColors::Control;
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Extract Models", L"Extract Textures" });
			this->checkedListBox1->Location = System::Drawing::Point(12, 410);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(120, 94);
			this->checkedListBox1->TabIndex = 5;
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->listView1->GridLines = true;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(257, 12);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(541, 267);
			this->listView1->TabIndex = 3;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			this->listView1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listView1_SelectedIndexChanged);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"";
			this->columnHeader1->Width = 500;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(854, 518);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->button1);
			this->ForeColor = System::Drawing::SystemColors::WindowText;
			this->Name = L"Form1";
			this->Text = L"TrbModelConverter v1.5.1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		openFileDialog1->FileName = "Select a Trb Model file";
		openFileDialog1->Filter = "Trb Model file (*.trb)|*.trb|Texture (*.ttl)| *.ttl";
		openFileDialog1->Title = "Open Trb Model File";
		openFileDialog1->Multiselect = true;
		List <System::String^>^ meshName = gcnew List<System::String^>();
		//std::vector<FbxSkeleton> skeletons;
		if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			Reader::Endian e;
			Game::Type game;
			listView1->Items->Clear();
			if (radioButton1->Checked)
			{
				e = Reader::Endian::LITTLE;
			}
			else if (radioButton2->Checked)
			{
				e = Reader::Endian::BIG;
			}
			else
			{
				e = Reader::Endian::LITTLE;
			}
			if (comboBox1->SelectedItem == "de Blob")
			{
				game = Game::DEBLOB;
			}
			else if (comboBox1->SelectedItem == "Nicktoons Attack of the Toybots")
			{
				game = Game::NAOTT;
			}
			else if (comboBox1->SelectedItem == "Nicktoons Battle for Volcano Island")
			{
				game = Game::NBFVI;
			}
			else if (comboBox1->SelectedItem == "Nicktoons Unite")
			{
				game = Game::NU;
			}
			for each (String ^ file in openFileDialog1->FileNames)
			{
				_fileName = (char*)(void*)Marshal::StringToHGlobalAnsi(file);
				Trb trb(_fileName, e, progressBar1, listView1, game);
				if (MessageBox::Show("File " + file + " has been succesfully extracted!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information) == Windows::Forms::DialogResult::OK)
				{
					progressBar1->Value = 0;
				}
			}
			//BinaryReader^ br = gcnew BinaryReader(File::Open((openFileDialog1->FileName), FileMode::Open), System::Text::Encoding::ASCII);
			//long long chunk;
			//for (int i = 0; i < trb.sy.nameOffsets.size(); i++)
			//{
			//	if (trb.sy.nameOffsets[i].name == 24684) //tmat
			//	{
			//		if (e == Trb::Trb::LITTLE)
			//		{
			//			if (trb.sy.nameOffsets[i].ID == 0)
			//			{
			//				chunk = trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			else
			//			{
			//				chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			int zero = br->ReadInt32();
			//			int unknown = br->ReadInt32();
			//			zero = br->ReadInt32();
			//			int meshNameOffset = br->ReadInt32();
			//			int one = br->ReadInt32();
			//			int meshNameOffsetEnd = br->ReadInt32();
			//			br->BaseStream->Seek(meshNameOffset + chunk, SeekOrigin::Begin);
			//			meshNamebelong->Add(ReadString(br));
			//			br->BaseStream->Seek(meshNameOffsetEnd + chunk, SeekOrigin::Begin);
			//			zero = br->ReadInt32();
			//			int texNameOffset = br->ReadInt32();
			//			br->BaseStream->Seek(texNameOffset + chunk, SeekOrigin::Begin);
			//			System::String^ texname = ReadString(br);
			//			texname = texname->Remove(texname->Length - 3) + "dds";
			//			texName->Add(texname);
			//		}
			//	}
			//	else if (trb.sy.nameOffsets[i].name == 31539) //ttex
			//	{
			//		if (e == Trb::Trb::LITTLE)
			//		{
			//			if (trb.sy.nameOffsets[i].ID == 0)
			//			{
			//				chunk = trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			else
			//			{
			//				chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			br->BaseStream->Seek(4, SeekOrigin::Current);
			//			int nameOffset = br->ReadInt32() + (int)chunk;
			//			int nameEndOffset = br->ReadInt32() + (int)chunk;
			//			int ddsSize = br->ReadInt32();
			//			int ddsOffset = br->ReadInt32() + (int)chunk;
			//			br->BaseStream->Seek(nameOffset, SeekOrigin::Begin);
			//			int nameLength = nameEndOffset - nameOffset;
			//			String^ name = ReadString(br);
			//			br->BaseStream->Seek(ddsOffset, SeekOrigin::Begin);
			//			name = name->Remove(name->Length - 3) + "dds";
			//			BinaryWriter^ bw = gcnew BinaryWriter(File::Open(name, FileMode::Create), System::Text::Encoding::ASCII);
			//			bw->Write(br->ReadBytes(ddsSize));
			//			bw->Close();
			//			allTexNames->Add(name);
			//		}
			//	}
			//}
			//for (int i = 0; i < trb.sy.nameOffsets.size(); i++)
			//{
			//	if (trb.sy.nameOffsets[i].name == 23661) //Skeleton
			//	{
			//		if (e == Trb::Trb::LITTLE)
			//		{
			//			if (trb.sy.nameOffsets[i].ID == 0)
			//			{
			//				chunk = trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			else
			//			{
			//				chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			int boneCount = br->ReadInt32(); //could be short unknown too...
			//			short unknownCount = br->ReadInt16(); //maybe animation?
			//			short unknown = br->ReadInt16(); //maybe bone?
			//			br->BaseStream->Seek(44, SeekOrigin::Current); //unknown right now
			//			int boneOffset = br->ReadInt32();
			//			int boneOffsetEnd = br->ReadInt32();
			//			br->BaseStream->Seek(chunk + boneOffset, SeekOrigin::Begin);
			//			List<System::String^>^ boneNames = gcnew List<System::String^>();
			//			List<int>^ parents = gcnew List<int>();
			//			for (int i = 0; i < boneCount; i++)
			//			{
			//				br->BaseStream->Seek(12, SeekOrigin::Current); //unknown right now
			//				float matrix[16] = {
			//					br->ReadSingle(), br->ReadSingle(), br->ReadSingle(), br->ReadSingle(),
			//					br->ReadSingle(), br->ReadSingle(), br->ReadSingle(), br->ReadSingle(),
			//					br->ReadSingle(), br->ReadSingle(), br->ReadSingle(), br->ReadSingle(),
			//					br->ReadSingle(), br->ReadSingle(), br->ReadSingle(), br->ReadSingle()
			//				};
			//				/*
			//				float m11 = br->ReadSingle(); float m12 = br->ReadSingle(); float m13 = br->ReadSingle(); float m14 = br->ReadSingle();
			//				float m21 = br->ReadSingle(); float m22 = br->ReadSingle(); float m23 = br->ReadSingle(); float m24 = br->ReadSingle();
			//				float m31 = br->ReadSingle(); float m32 = br->ReadSingle(); float m33 = br->ReadSingle(); float m34 = br->ReadSingle();
			//				float m41 = br->ReadSingle(); float m42 = br->ReadSingle(); float m43 = br->ReadSingle(); float m44 = br->ReadSingle();
			//				*/
			//				float m51 = br->ReadSingle(); float m52 = br->ReadSingle(); float m53 = br->ReadSingle(); float m54 = br->ReadSingle();
			//				float m61 = br->ReadSingle(); float m62 = br->ReadSingle(); float m63 = br->ReadSingle(); float m64 = br->ReadSingle();
			//				float m71 = br->ReadSingle(); float m72 = br->ReadSingle(); float m73 = br->ReadSingle(); float m74 = br->ReadSingle();
			//				float m81 = br->ReadSingle(); float m82 = br->ReadSingle(); float m83 = br->ReadSingle(); float m84 = br->ReadSingle();
			//				float unknown = br->ReadSingle();
			//				int boneNameOffset = br->ReadInt32();
			//				short parentIndex = br->ReadInt16();
			//				parents->Add(parentIndex);
			//				int back = br->BaseStream->Position;
			//				br->BaseStream->Seek(chunk + boneNameOffset, SeekOrigin::Begin);
			//				boneNames->Add(ReadString(br));
			//				br->BaseStream->Seek(back + 26, SeekOrigin::Begin); //unknown right now
			//				double T[3];
			//				double R[3];
			//				double S[3];
			//				Matrix344ToTRS(matrix, T, R, S, 0);
			//			}
			//		}
			//		
			//	}
			//	else if (trb.sy.nameOffsets[i].name == 22891) //tkey
			//	{
			//		if (e == Trb::Trb::LITTLE)
			//		{
			//			if (trb.sy.nameOffsets[i].ID == 0)
			//			{
			//				chunk = trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			else
			//			{
			//				chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			int pos = br->BaseStream->Position;
			//			int pos2 = br->BaseStream->Position;
			//		}

			//	}
			//	else if (trb.sy.nameOffsets[i].name == 25102) //tmod
			//	{
			//		List<int>^ meshSubInfoOffsets = gcnew List<int>();
			//		List<int>^ meshDataOffsets = gcnew List<int>();
			//		List<int>^ faceIndicesCount = gcnew List<int>();
			//		List<int>^ verticesCount = gcnew List<int>();
			//		List<int>^ faceOffsets = gcnew List<int>();
			//		List<int>^ vertexOffsets = gcnew List<int>();
			//		List<float>^ vertices = gcnew List<float>();
			//		List<float>^ normals = gcnew List<float>();
			//		List<unsigned short>^ faces = gcnew List<unsigned short>();
			//		List<float>^ uvs = gcnew List<float>();
			//		System::String^ modelName;
			//		if (e == Trb::Trb::LITTLE)
			//		{
			//			if (trb.sy.nameOffsets[i].ID == 0)
			//			{
			//				chunk = trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			else
			//			{
			//				chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			int modelNameOffset = br->ReadInt32();
			//			int modelCount = br->ReadInt32(); //?
			//			br->BaseStream->Seek(modelCount * 4, SeekOrigin::Current);
			//			int unknown = br->ReadInt32(); //?
			//			long tell = br->BaseStream->Position;
			//			br->BaseStream->Seek(modelNameOffset + chunk, SeekOrigin::Begin);
			//			modelName = ReadString(br);
			//			br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//			int unknown2 = br->ReadInt32(); //?
			//			int referenceTomeshInfoOffsetBegin = br->ReadInt32(); //?
			//			int referenceToMeshInfoOffsetEnd = br->ReadInt32(); //?
			//			int meshInfoOffset = br->ReadInt32();
			//			br->BaseStream->Seek(meshInfoOffset + chunk, SeekOrigin::Begin);
			//			unknown = br->ReadInt32(); //?
			//			unknown2 = br->ReadInt32(); //?
			//			int meshCount = br->ReadInt32();


			//			for (int i = 0; i < meshCount; i++)
			//			{
			//				meshSubInfoOffsets->Add(br->ReadInt32());
			//			}
			//			for (int i = 0; i < meshSubInfoOffsets->Count; i++)
			//			{
			//				br->BaseStream->Seek(meshSubInfoOffsets[i] + chunk, SeekOrigin::Begin);
			//				int zero = br->ReadInt32(); //?
			//				int one = br->ReadInt32(); //?
			//				unknown = br->ReadInt32(); //?
			//				unknown2 = br->ReadInt32(); //?
			//				int meshNameOffset = br->ReadInt32();
			//				long tell = br->BaseStream->Position;
			//				br->BaseStream->Seek(meshNameOffset + chunk, SeekOrigin::Begin);
			//				meshName->Add(ReadString(br));
			//				br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//				int meshNameOffsetEnd = br->ReadInt32();
			//				meshDataOffsets->Add(meshNameOffsetEnd);
			//			}
			//			for (int i = 0; i < meshDataOffsets->Count; i++)
			//			{
			//				br->BaseStream->Seek(meshDataOffsets[i] + chunk, SeekOrigin::Begin);
			//				verticesCount->Add(br->ReadInt32());
			//				unknown = br->ReadInt32();
			//				faceIndicesCount->Add(br->ReadInt32());

			//				unknown2 = br->ReadInt32();
			//				int unknownlol = br->ReadInt32();
			//				vertexOffsets->Add(br->ReadInt32());
			//				faceOffsets->Add(br->ReadInt32());
			//			}
			//			for (int j = 0; j < vertexOffsets->Count; j++)
			//			{
			//				br->BaseStream->Seek(vertexOffsets[j] + chunk, SeekOrigin::Begin);
			//				for (int y = 0; y < verticesCount[j]; y++)
			//				{
			//					float vertexX = br->ReadSingle();
			//					float vertexY = br->ReadSingle();
			//					float vertexZ = br->ReadSingle();
			//					float normalX = br->ReadSingle();
			//					float normalY = br->ReadSingle();
			//					float normalZ = br->ReadSingle();
			//					br->BaseStream->Seek(8, SeekOrigin::Current);
			//					float uvU = br->ReadSingle();
			//					float uvV = br->ReadSingle();
			//					br->BaseStream->Seek(4, SeekOrigin::Current);

			//					vertices->Add(vertexX);
			//					vertices->Add(vertexY);
			//					vertices->Add(vertexZ);
			//					normals->Add(normalX);
			//					normals->Add(normalY);
			//					normals->Add(normalZ);
			//					uvs->Add(uvU);
			//					uvs->Add(-uvV);
			//				}
			//				br->BaseStream->Seek(faceOffsets[j] + chunk, SeekOrigin::Begin);
			//				for (int a = 0; a < faceIndicesCount[j] / 3; a++)
			//				{
			//					unsigned short faceA = br->ReadUInt16();
			//					unsigned short faceB = br->ReadUInt16();
			//					unsigned short faceC = br->ReadUInt16();

			//					faces->Add(faceA);
			//					faces->Add(faceB);
			//					faces->Add(faceC);
			//				}
			//			}
			//		}
			//		else
			//		{
			//			if (trb.sy.nameOffsets[i].ID == 0)
			//			{
			//				chunk = trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			else
			//			{
			//				chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//				br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//			}
			//			auto data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int modelNameOffset = BitConverter::ToInt32(data, 0);
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int modelCount = BitConverter::ToInt32(data, 0); //?
			//			br->BaseStream->Seek(modelCount * 4, SeekOrigin::Current);
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int unknown = BitConverter::ToInt32(data, 0); //?
			//			long tell = br->BaseStream->Position;
			//			br->BaseStream->Seek(modelNameOffset + chunk, SeekOrigin::Begin);
			//			modelName = ReadString(br);
			//			br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int unknown2 = BitConverter::ToInt32(data, 0); //?
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int referenceTomeshInfoOffsetBegin = BitConverter::ToInt32(data, 0); //?
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int referenceToMeshInfoOffsetEnd = BitConverter::ToInt32(data, 0); //?
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int meshInfoOffset = BitConverter::ToInt32(data, 0);
			//			br->BaseStream->Seek(meshInfoOffset + chunk, SeekOrigin::Begin);
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			unknown = BitConverter::ToInt32(data, 0); //?
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			unknown2 = BitConverter::ToInt32(data, 0); //?
			//			data = br->ReadBytes(4);
			//			Array::Reverse(data);
			//			int meshCount = BitConverter::ToInt32(data, 0);


			//			for (int i = 0; i < meshCount; i++)
			//			{
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				meshSubInfoOffsets->Add(BitConverter::ToInt32(data, 0));
			//			}
			//			for (int i = 0; i < meshSubInfoOffsets->Count; i++)
			//			{
			//				br->BaseStream->Seek(meshSubInfoOffsets[i] + chunk, SeekOrigin::Begin);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				unknown = BitConverter::ToInt32(data, 0); //?
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				int zero = BitConverter::ToInt32(data, 0); //?
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				unknown2 = BitConverter::ToInt32(data, 0); //?
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				zero = BitConverter::ToInt32(data, 0);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				int unknownOffset = BitConverter::ToInt32(data, 0);
			//				br->BaseStream->Seek(4, SeekOrigin::Current);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				int meshDataOffset = BitConverter::ToInt32(data, 0);
			//				br->BaseStream->Seek(4, SeekOrigin::Current);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				int meshNameOffset= BitConverter::ToInt32(data, 0);
			//				long tell = br->BaseStream->Position;
			//				br->BaseStream->Seek(meshNameOffset + chunk, SeekOrigin::Begin);
			//				meshName->Add(ReadString(br));
			//				br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//				meshDataOffsets->Add(meshDataOffset);
			//			}
			//			for (int i = 0; i < meshDataOffsets->Count; i++)
			//			{
			//				br->BaseStream->Seek(meshDataOffsets[i] + chunk, SeekOrigin::Begin);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				verticesCount->Add(BitConverter::ToInt32(data, 0));
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				unknown = BitConverter::ToInt32(data, 0);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				faceIndicesCount->Add(BitConverter::ToInt32(data, 0));
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				unknown2 = BitConverter::ToInt32(data, 0);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				int unknownlol = BitConverter::ToInt32(data, 0);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				unknown2 = BitConverter::ToInt32(data, 0);
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				vertexOffsets->Add(BitConverter::ToInt32(data, 0));
			//				data = br->ReadBytes(4);
			//				Array::Reverse(data);
			//				faceOffsets->Add(BitConverter::ToInt32(data, 0));
			//			}
			//			for (int j = 0; j < vertexOffsets->Count; j++)
			//			{
			//				br->BaseStream->Seek(vertexOffsets[j] + chunk, SeekOrigin::Begin);
			//				for (int y = 0; y < verticesCount[j]; y++)
			//				{
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float vertexX = BitConverter::ToSingle(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float vertexY = BitConverter::ToSingle(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float vertexZ = BitConverter::ToSingle(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float normalX = BitConverter::ToSingle(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float normalY = BitConverter::ToSingle(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float normalZ = BitConverter::ToSingle(data, 0);
			//					br->BaseStream->Seek(8, SeekOrigin::Current);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float uvU = BitConverter::ToSingle(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					float uvV = BitConverter::ToSingle(data, 0);
			//					br->BaseStream->Seek(4, SeekOrigin::Current);

			//					vertices->Add(vertexX);
			//					vertices->Add(vertexY);
			//					vertices->Add(vertexZ);
			//					normals->Add(normalX);
			//					normals->Add(normalY);
			//					normals->Add(normalZ);
			//					uvs->Add(uvU);
			//					uvs->Add(-uvV);
			//				}
			//				br->BaseStream->Seek(faceOffsets[j] + chunk, SeekOrigin::Begin);
			//				for (int a = 0; a < faceIndicesCount[j] / 3; a++)
			//				{
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					unsigned short faceA = BitConverter::ToUInt16(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					unsigned short faceB = BitConverter::ToUInt16(data, 0);
			//					data = br->ReadBytes(4);
			//					Array::Reverse(data);
			//					unsigned short faceC = BitConverter::ToUInt16(data, 0);

			//					faces->Add(faceA);
			//					faces->Add(faceB);
			//					faces->Add(faceC);
			//				}
			//			}
			//		}
			//		FbxManager* lSdkManager = FbxManager::Create();
			//		FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
			//		FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
			//		lSdkManager->SetIOSettings(ios);
			//		int sumVertices = 0;
			//		int Viord = 0;
			//		int index = 0;
			//		int rememberI = 0;
			//		int remeberU = 0;
			//		int Niord = 0;
			//		for (int z = 0; z < vertexOffsets->Count; z++)
			//		{
			//			FbxNode* lMeshNode = FbxNode::Create(lScene, (char*)(void*)Marshal::StringToHGlobalAnsi(meshName[z]));
			//			FbxMesh* lMesh = FbxMesh::Create(lScene, (char*)(void*)Marshal::StringToHGlobalAnsi(meshName[z]));
			//			lMeshNode->SetNodeAttribute(lMesh);
			//			FbxNode* lRootNode = lScene->GetRootNode();
			//			FbxNode* lPatchNode = lScene->GetRootNode();
			//			lRootNode->AddChild(lMeshNode);
			//			lMesh->InitControlPoints(verticesCount[z]);
			//			FbxVector4* lControlPoints = lMesh->GetControlPoints();
			//			FbxLayer* lLayer = lMesh->GetLayer(0);
			//			if (lLayer == NULL) {
			//				lMesh->CreateLayer();
			//				lLayer = lMesh->GetLayer(0);
			//			}
			//			int pos = 0;
			//			for (int i = 0; i < meshNamebelong->Count; i++)
			//			{
			//				if (meshName[z]->ToLower()->CompareTo(meshNamebelong[i]) == 0)
			//				{
			//					pos = i;
			//					break;
			//				}
			//			}
			//			FbxString lMaterialName = "toto";
			//			FbxSurfacePhong* lMaterial = FbxSurfacePhong::Create(lScene, lMaterialName.Buffer());
			//			lMeshNode->AddMaterial(lMaterial);
			//			FbxFileTexture* lTexture = FbxFileTexture::Create(lScene, "Texture");
			//			lTexture->SetFileName((char*)(void*)Marshal::StringToHGlobalAnsi(texName[pos])); // Resource file is in current directory.
			//			lTexture->SetTextureUse(FbxTexture::eStandard);
			//			lTexture->SetMappingType(FbxTexture::eUV);
			//			lTexture->SetMaterialUse(FbxFileTexture::eModelMaterial);
			//			lTexture->SetSwapUV(false);
			//			lTexture->SetTranslation(0.0, 0.0);
			//			lTexture->SetScale(1.0, 1.0);
			//			lTexture->SetRotation(0.0, 0.0);
			//			lMaterial->Diffuse.ConnectSrcObject(lTexture);


			//			FbxLayerElementNormal* lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
			//			FbxLayerElementUV* lLayerElementUV = FbxLayerElementUV::Create(lMesh, "");
			//			// Set its mapping mode to map each normal vector to each control point.
			//			lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
			//			lLayerElementUV->SetMappingMode(FbxLayerElement::eByControlPoint);
			//			// Set the reference mode of so that the n'th element of the normal array maps to the n'th
			//			// element of the control point array.
			//			lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
			//			lLayerElementUV->SetReferenceMode(FbxLayerElement::eDirect);
			//			for (int j = 0; j < verticesCount[z]; j++)
			//			{
			//				FbxVector4 vertex(vertices[Viord], vertices[Viord + 1], vertices[Viord + 2]);
			//				FbxVector4 normal(normals[Niord], normals[Niord + 1], normals[Niord + 2]);
			//				FbxVector2 uv(uvs[remeberU], uvs[remeberU + 1]);
			//				lLayerElementNormal->GetDirectArray().Add(normal);
			//				lLayerElementUV->GetDirectArray().Add(uv);
			//				lControlPoints[j] = vertex;
			//				Viord += 3;
			//				Niord += 3;
			//				remeberU += 2;

			//			}
			//			for (int y = 0; y < faceIndicesCount[z] / 3; y++)
			//			{
			//				lMesh->BeginPolygon();
			//				lMesh->AddPolygon(faces[rememberI]);
			//				lMesh->AddPolygon(faces[rememberI + 1]);
			//				lMesh->AddPolygon(faces[rememberI + 2]);
			//				lMesh->EndPolygon();
			//				rememberI += 3;

			//			}
			//			lLayer->SetNormals(lLayerElementNormal);
			//			lLayer->SetUVs(lLayerElementUV);
			//			lMeshNode->LclRotation.Set(FbxVector4(180, 0, 0.0)); //Right rotation

			//		}
			//		TCHAR  dir[1024] = { 0 };
			//		const char* pChar = strrchr(_fileName, 92);

			//		if (pChar == NULL)				// If no backslash is found
			//			pChar = _fileName;			// Reset pChar
			//		else
			//			pChar++;	// Skip the last backslash
			//		std::string lFilename;
			//		System::String^ path = gcnew String(_fileName);
			//		System::String^ file = System::IO::Path::GetFileNameWithoutExtension(path);
			//		System::String^ NewPath = path->Replace(file, modelName);
			//		lFilename = (char*)(void*)Marshal::StringToHGlobalAnsi(NewPath);
			//		int length = lFilename.length();
			//		lFilename.erase(length - 8);
			//		lFilename.append(".fbx");
			//		strcat_s(dir, 256, lFilename.c_str());

			//		//getDir(_fileName, dir);
			//		FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
			//		lSdkManager->GetIOSettings()->SetBoolProp(EXP_FBX_EMBEDDED, true);
			//		bool lExportStatus = lExporter->Initialize(dir, -1, lSdkManager->GetIOSettings());
			//		if (!lExportStatus) {
			//			throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
			//		}
			//		lExporter->Export(lScene);
			//		lExporter->Destroy();
			//		meshName->Clear();
			//	}
			//	else if (trb.sy.nameOffsets[i].name == 34619) //twld
			//	{
			//		if (trb.sy.nameOffsets[i].ID == 0)
			//		{
			//			chunk = trb.se.chunkOffset;
			//			br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//		}
			//		else
			//		{
			//			chunk = trb.h.chunkSizes[trb.sy.nameOffsets[i].ID - 1] + trb.se.chunkOffset;
			//			br->BaseStream->Seek(chunk + trb.sy.nameOffsets[i].dataOffset, SeekOrigin::Begin);
			//		}
			//		int modelNameOffset = br->ReadInt32();
			//		long tell = br->BaseStream->Position;
			//		br->BaseStream->Seek(modelNameOffset + chunk, SeekOrigin::Begin);
			//		System::String^ modelName = ReadString(br);
			//		br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//		int skip = br->ReadInt32();
			//		br->BaseStream->Seek(skip + chunk, SeekOrigin::Begin);
			//		br->BaseStream->Seek(8, SeekOrigin::Current); //Unknown
			//		int unknownInfoOffset = br->ReadInt32();
			//		br->BaseStream->Seek(unknownInfoOffset + chunk, SeekOrigin::Begin);
			//		int count = br->ReadInt32();
			//		if (count != 0)
			//		{
			//			br->BaseStream->Seek(4, SeekOrigin::Current); //Unknown
			//			int unknownOffset = br->ReadInt32();
			//			br->BaseStream->Seek(unknownOffset + chunk, SeekOrigin::Begin);
			//			br->BaseStream->Seek(132, SeekOrigin::Current); //Unknown
			//			int meshInfoCount = br->ReadInt32();
			//			int beginOfMeshInfoOffsets = br->ReadInt32();
			//			long firstMeshOffset = br->ReadInt32();
			//			br->BaseStream->Seek(beginOfMeshInfoOffsets + chunk, SeekOrigin::Begin);
			//			List<int>^ meshInfoOffsets = gcnew List<int>();
			//			List<int>^ faceIndicesCount = gcnew List<int>();
			//			List<int>^ verticesCount = gcnew List<int>();
			//			List<int>^ faceOffsets = gcnew List<int>();
			//			List<int>^ vertexOffsets = gcnew List<int>();
			//			List<float>^ vertices = gcnew List<float>();
			//			List<float>^ normals = gcnew List<float>();
			//			List<unsigned short>^ faces = gcnew List<unsigned short>();
			//			List<float>^ uvs = gcnew List<float>();
			//			for (int i = 0; i < meshInfoCount; i++)
			//			{
			//				int meshInfoOffset = br->ReadInt32();
			//				meshInfoOffsets->Add(meshInfoOffset);
			//			}
			//			br->BaseStream->Seek(firstMeshOffset + chunk, SeekOrigin::Begin);
			//			br->BaseStream->Seek(20, SeekOrigin::Current);
			//			int unknownCount = br->ReadInt32();
			//			if (unknownCount % 2 != 0) //Odd
			//			{
			//				br->BaseStream->Seek((unknownCount * 2) + 6, SeekOrigin::Current);
			//			}
			//			else //Even
			//			{
			//				br->BaseStream->Seek((unknownCount * 2) + 4, SeekOrigin::Current);
			//			}
			//			long vertexCount = br->ReadInt32();
			//			int unknown = br->ReadInt32();
			//			long faceCount = br->ReadInt32();
			//			int meshNameOffset = br->ReadInt32();
			//			long tell = br->BaseStream->Position;
			//			br->BaseStream->Seek(meshNameOffset + chunk, SeekOrigin::Begin);
			//			meshName->Add(ReadString(br));
			//			br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//			long vertexOffset = br->ReadInt32();
			//			long faceOffset = br->ReadInt32();
			//			faceIndicesCount->Add(faceCount);
			//			verticesCount->Add(vertexCount);
			//			faceOffsets->Add(faceOffset);
			//			vertexOffsets->Add(vertexOffset);
			//			if (meshInfoCount > 1)
			//			{
			//				for (int x = 0; x < meshInfoOffsets->Count-1; x++)
			//				{
			//					br->BaseStream->Seek(meshInfoOffsets[x] + chunk, SeekOrigin::Begin);
			//					br->BaseStream->Seek(24, SeekOrigin::Current);
			//					int vertexCount = br->ReadInt32();
			//					int unknown = br->ReadInt32();
			//					int faceCount = br->ReadInt32();
			//					int meshNameOffset = br->ReadInt32();
			//					long tell = br->BaseStream->Position;
			//					br->BaseStream->Seek(meshNameOffset + chunk, SeekOrigin::Begin);
			//					meshName->Add(ReadString(br));
			//					br->BaseStream->Seek(tell, SeekOrigin::Begin);
			//					int vertexOffset = br->ReadInt32();
			//					int faceOffset = br->ReadInt32();
			//					faceIndicesCount->Add(faceCount);
			//					verticesCount->Add(vertexCount);
			//					faceOffsets->Add(faceOffset);
			//					vertexOffsets->Add(vertexOffset);
			//				}
			//			}
			//			for (int j = 0; j < vertexOffsets->Count; j++)
			//			{
			//				br->BaseStream->Seek(vertexOffsets[j] + chunk, SeekOrigin::Begin);
			//				for (int y = 0; y < verticesCount[j]; y++)
			//				{
			//					float vertexX = br->ReadSingle();
			//					float vertexY = br->ReadSingle();
			//					float vertexZ = br->ReadSingle();
			//					float normalX = br->ReadSingle();
			//					float normalY = br->ReadSingle();
			//					float normalZ = br->ReadSingle();
			//					br->BaseStream->Seek(4, SeekOrigin::Current);
			//					float uvU = br->ReadSingle();
			//					float uvV = br->ReadSingle();
			//					br->BaseStream->Seek(16, SeekOrigin::Current);

			//					vertices->Add(vertexX);
			//					vertices->Add(vertexY);
			//					vertices->Add(vertexZ);
			//					normals->Add(normalX);
			//					normals->Add(normalY);
			//					normals->Add(normalZ);
			//					uvs->Add(uvU);
			//					uvs->Add(-uvV);
			//				}
			//				br->BaseStream->Seek(faceOffsets[j] + chunk, SeekOrigin::Begin);
			//				for (int a = 0; a < faceIndicesCount[j] / 3; a++)
			//				{
			//					unsigned short faceA = br->ReadUInt16();
			//					unsigned short faceB = br->ReadUInt16();
			//					unsigned short faceC = br->ReadUInt16();

			//					faces->Add(faceA);
			//					faces->Add(faceB);
			//					faces->Add(faceC);
			//				}
			//			}
			//			FbxManager* lSdkManager = FbxManager::Create();
			//			FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
			//			FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
			//			lSdkManager->SetIOSettings(ios);
			//			int sumVertices = 0;
			//			int Viord = 0;
			//			int index = 0;
			//			int rememberI = 0;
			//			int remeberU = 0;
			//			int Niord = 0;
			//			for (int z = 0; z < vertexOffsets->Count; z++)
			//			{
			//				FbxNode* lMeshNode = FbxNode::Create(lScene, (char*)(void*)Marshal::StringToHGlobalAnsi(meshName[z]));
			//				FbxMesh* lMesh = FbxMesh::Create(lScene, (char*)(void*)Marshal::StringToHGlobalAnsi(meshName[z]));
			//				lMeshNode->SetNodeAttribute(lMesh);
			//				FbxNode* lRootNode = lScene->GetRootNode();
			//				FbxNode* lPatchNode = lScene->GetRootNode();
			//				lRootNode->AddChild(lMeshNode);
			//				lMesh->InitControlPoints(verticesCount[z]);
			//				FbxVector4* lControlPoints = lMesh->GetControlPoints();
			//				FbxLayer* lLayer = lMesh->GetLayer(0);
			//				if (lLayer == NULL) {
			//					lMesh->CreateLayer();
			//					lLayer = lMesh->GetLayer(0);
			//				}
			//				int pos = 0;
			//				for (int i = 0; i < meshNamebelong->Count; i++)
			//				{
			//					if (meshName[z]->ToLower()->CompareTo(meshNamebelong[i]) == 0)
			//					{
			//						pos = i;
			//						break;
			//					}
			//				}
			//				FbxString lMaterialName = "toto";
			//				FbxSurfacePhong* lMaterial = FbxSurfacePhong::Create(lScene, lMaterialName.Buffer());
			//				lMeshNode->AddMaterial(lMaterial);
			//				FbxFileTexture* lTexture = FbxFileTexture::Create(lScene, "Texture");
			//				lTexture->SetFileName((char*)(void*)Marshal::StringToHGlobalAnsi(texName[pos])); // Resource file is in current directory.
			//				lTexture->SetTextureUse(FbxTexture::eStandard);
			//				lTexture->SetMappingType(FbxTexture::eUV);
			//				lTexture->SetMaterialUse(FbxFileTexture::eModelMaterial);
			//				lTexture->SetSwapUV(false);
			//				lTexture->SetTranslation(0.0, 0.0);
			//				lTexture->SetScale(1.0, 1.0);
			//				lTexture->SetRotation(0.0, 0.0);
			//				lMaterial->Diffuse.ConnectSrcObject(lTexture);

			//				FbxLayerElementNormal* lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
			//				FbxLayerElementUV* lLayerElementUV = FbxLayerElementUV::Create(lMesh, "");
			//				// Set its mapping mode to map each normal vector to each control point.
			//				lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
			//				lLayerElementUV->SetMappingMode(FbxLayerElement::eByControlPoint);
			//				// Set the reference mode of so that the n'th element of the normal array maps to the n'th
			//				// element of the control point array.
			//				lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
			//				lLayerElementUV->SetReferenceMode(FbxLayerElement::eDirect);
			//				for (int j = 0; j < verticesCount[z]; j++)
			//				{
			//					FbxVector4 vertex(vertices[Viord], vertices[Viord + 1], vertices[Viord + 2]);
			//					FbxVector4 normal(normals[Niord], normals[Niord + 1], normals[Niord + 2]);
			//					FbxVector2 uv(uvs[remeberU], uvs[remeberU + 1]);
			//					lLayerElementNormal->GetDirectArray().Add(normal);
			//					lLayerElementUV->GetDirectArray().Add(uv);
			//					lControlPoints[j] = vertex;
			//					Viord += 3;
			//					Niord += 3;
			//					remeberU += 2;

			//				}
			//				for (int y = 0; y < faceIndicesCount[z] / 3; y++)
			//				{
			//					lMesh->BeginPolygon();
			//					lMesh->AddPolygon(faces[rememberI]);
			//					lMesh->AddPolygon(faces[rememberI + 1]);
			//					lMesh->AddPolygon(faces[rememberI + 2]);
			//					lMesh->EndPolygon();
			//					rememberI += 3;

			//				}
			//				lLayer->SetNormals(lLayerElementNormal);
			//				lLayer->SetUVs(lLayerElementUV);
			//				lMeshNode->LclRotation.Set(FbxVector4(180, 0, 0.0)); //Right rotation
			//			}
			//			TCHAR  dir[1024] = { 0 };
			//			const char* pChar = strrchr(_fileName, 92);

			//			if (pChar == NULL)				// If no backslash is found
			//				pChar = _fileName;			// Reset pChar
			//			else
			//				pChar++;	// Skip the last backslash
			//			std::string lFilename;
			//			System::String^ path = gcnew String(_fileName);
			//			System::String^ file = System::IO::Path::GetFileNameWithoutExtension(path);
			//			System::String^ NewPath = path->Replace(file, modelName);
			//			lFilename = (char*)(void*)Marshal::StringToHGlobalAnsi(NewPath);
			//			int length = lFilename.length();
			//			lFilename.erase(length - 8);
			//			lFilename.append(".fbx");
			//			strcat_s(dir, 256, lFilename.c_str());

			//			//getDir(_fileName, dir);
			//			FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
			//			lSdkManager->GetIOSettings()->SetBoolProp(EXP_FBX_EMBEDDED, true);
			//			bool lExportStatus = lExporter->Initialize(dir, -1, lSdkManager->GetIOSettings());
			//			if (!lExportStatus) {
			//				throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
			//			}
			//			lExporter->Export(lScene);
			//			lExporter->Destroy();
			//			meshName->Clear();
			//		}

			//	}
			//}
			//
			/*for (int p = 0; p < allTexNames->Count; p++)
			{
				File::Delete(allTexNames[p]);
			}
			br->Close();*/

		}
		

	}
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void progressBar1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void listView1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {

}
};
}
